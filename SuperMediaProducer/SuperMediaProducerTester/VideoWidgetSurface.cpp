//implement VideoWidgetSurface
//andycai_sc@163.com 2015-05-06

#include "VideoWidgetSurface.h"
#include <QWidget>
#include <QtMultimedia>

VideoWidgetSurface::VideoWidgetSurface(QWidget *widget, QObject *parent)
    : QAbstractVideoSurface(parent)
    , imageFormat(QImage::Format_Invalid)
{
    this->widget = widget;
}

QList<QVideoFrame::PixelFormat> VideoWidgetSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle)
    {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555
                << QVideoFrame::Format_RGB24;
    }
    else
    {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool VideoWidgetSurface::isFormatSupported(
        const QVideoSurfaceFormat &format, QVideoSurfaceFormat *similar) const
{
    Q_UNUSED(similar);

    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid
            && !size.isEmpty()
            && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool VideoWidgetSurface::start(const QVideoSurfaceFormat &format)
{
    const QImage::Format imgFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    if (imgFormat != QImage::Format_Invalid && !size.isEmpty())
    {
        imageFormat = imgFormat;
        imageSize = size;
        sourceRect = format.viewport();

        QAbstractVideoSurface::start(format);

        widget->updateGeometry();
        updateVideoRect();

        return true;
    }
    else
    {
        return false;
    }
}

void VideoWidgetSurface::stop()
{
    currentFrame = QVideoFrame();
    targetRect = QRect();

    QAbstractVideoSurface::stop();

    widget->update();
}

bool VideoWidgetSurface::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat()
            || surfaceFormat().frameSize() != frame.size())
    {
        setError(IncorrectFormatError);
        stop();

        return false;
    }
    else
    {
        currentFrame = frame;

        widget->repaint(targetRect);

        return true;
    }
}

void VideoWidgetSurface::updateVideoRect()
{
    QSize size = surfaceFormat().sizeHint();
    size.scale(widget->size(), Qt::IgnoreAspectRatio);

    targetRect = QRect(QPoint(0, 0), size);
    targetRect.moveCenter(widget->rect().center());
}

void VideoWidgetSurface::paint(QPainter *painter)
{
    if (currentFrame.map(QAbstractVideoBuffer::ReadOnly))
    {
        const QTransform oldTransform = painter->transform();

        if (surfaceFormat().scanLineDirection() == QVideoSurfaceFormat::BottomToTop)
        {
           painter->scale(1, -1);
           painter->translate(0, -widget->height());
        }

        QImage image(
                currentFrame.bits(),
                currentFrame.width(),
                currentFrame.height(),
                currentFrame.bytesPerLine(),
                imageFormat);

        painter->drawImage(targetRect, image, sourceRect);

        painter->setTransform(oldTransform);

        currentFrame.unmap();
    }
}

void VideoWidgetSurface::drawVideoBuffer(QAbstractVideoBuffer *buffer, const QSize &size, const QVideoFrame::PixelFormat& format)
{
    QVideoFrame yuvFrame(buffer, size, format);
    if (!yuvFrame.isValid())
    {
        //delete buffer;
        return;
    }

    QVideoFrame frame;
    convert(frame, yuvFrame);

    //delete buffer;

    const QVideoSurfaceFormat currentFormat = surfaceFormat();

    if (frame.pixelFormat() != currentFormat.pixelFormat()
            || frame.size() != currentFormat.frameSize())
    {
        QVideoSurfaceFormat sfFormat(frame.size(), frame.pixelFormat());

        if (!start(sfFormat))
        {
            return;
        }
    }

     if (!present(frame))
        stop();
}

extern "C" {
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

void ImageCleanupHandler(void *info)
{
    uchar* data = (uchar*)info;
    delete[] data;
}

bool VideoWidgetSurface::convert(QVideoFrame& dstFrame, QVideoFrame &srcFrame)
{
    srcFrame.map(QAbstractVideoBuffer::ReadOnly);
    SwsContext* swsCtx = 0;
    AVFrame* avsrcFrame = avcodec_alloc_frame();
    AVFrame* avdstFrame = avcodec_alloc_frame();

    //int pixSize = srcFrame.size().width() * srcFrame.size().height();

    int srcSize = avpicture_get_size(AV_PIX_FMT_YUV420P, srcFrame.size().width(), srcFrame.size().height());
    uint8_t* yuvData = (uint8_t*)av_malloc(srcSize * sizeof(uint8_t));
    memcpy(yuvData, srcFrame.bits(), srcSize);
    avpicture_fill((AVPicture*)avsrcFrame, yuvData, PIX_FMT_YUV420P, srcFrame.size().width(), srcFrame.size().height());
    uint8_t* tmp = avsrcFrame->data[1];
    avsrcFrame->data[1] = avsrcFrame->data[2];
    avsrcFrame->data[2] = tmp;
    //memcpy(avsrcFrame->data[0], srcFrame.bits(), pixSize);
    //memcpy(avsrcFrame->data[2], srcFrame.bits() + pixSize, pixSize / 4);
    //memcpy(avsrcFrame->data[1], srcFrame.bits() + pixSize * 5 /4, pixSize / 4);


    int dstSize = avpicture_get_size(AV_PIX_FMT_RGB24, srcFrame.size().width(), srcFrame.size().height());
    uint8_t* rgbData = (uint8_t*)av_malloc(dstSize * sizeof(uint8_t));
    avpicture_fill((AVPicture*)avdstFrame, rgbData, PIX_FMT_RGB24, srcFrame.size().width(), srcFrame.size().height());

    swsCtx = sws_getContext(srcFrame.size().width(), srcFrame.size().height(),
         PIX_FMT_YUV420P, srcFrame.size().width(), srcFrame.size().height(),
         PIX_FMT_RGB24, SWS_BILINEAR, NULL, NULL, NULL);

    int dstHeight = sws_scale(swsCtx, avsrcFrame->data, avsrcFrame->linesize, 0, srcFrame.size().height(), avdstFrame->data, avdstFrame->linesize);
    if (!dstHeight)
    {
        av_free(rgbData);
        av_free(yuvData);

        avcodec_free_frame(&avdstFrame);
        avcodec_free_frame(&avsrcFrame);

        srcFrame.unmap();
        return false;
    }

    uchar* dstBuffer = new uchar[dstSize];
    memcpy(dstBuffer, avdstFrame->data[0], dstSize);
    QImage img(dstBuffer, srcFrame.size().width(), srcFrame.size().height(), QImage::Format_RGB888, ImageCleanupHandler, dstBuffer);

    QVideoFrame frame(img);
    dstFrame = frame;

    av_free(rgbData);
    av_free(yuvData);

    avcodec_free_frame(&avdstFrame);
    avcodec_free_frame(&avsrcFrame);

    srcFrame.unmap();

    return true;
}
