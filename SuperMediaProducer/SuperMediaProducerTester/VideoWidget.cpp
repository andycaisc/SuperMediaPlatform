//implement VideoWidget
//andycai_sc@163.com 2015-05-06

#include "VideoWidget.h"
#include <QMultimedia>
#include <QVideoSurfaceFormat>
#include <QPainter>
#include <QPaintEvent>
#include "RGB24VideoBuffer.h"

VideoWidget::VideoWidget(QWidget *parent)
     : QWidget(parent)
     , m_surface(0)
{
    setAutoFillBackground(false);
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_PaintOnScreen, true);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::black);
    setPalette(palette);

    //setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_surface = new VideoWidgetSurface(this);

    connect(&m_videoData, SIGNAL(videoBufferChanged(QAbstractVideoBuffer*,const QSize&, const QVideoFrame::PixelFormat&)),
            m_surface, SLOT(drawVideoBuffer(QAbstractVideoBuffer*, const QSize&, const QVideoFrame::PixelFormat&)));
}

VideoWidget::~VideoWidget()
{
    delete m_surface;
}

QSize VideoWidget::sizeHint() const
{
    return m_surface->surfaceFormat().sizeHint();
}

void VideoWidget::display(uchar *picture, const QSize &size, int numBytes, const QVideoFrame::PixelFormat& format)
{
    m_videoData.push(picture, size, numBytes, format);
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (m_surface->isActive())
    {
        const QRect videoRect = m_surface->videoRect();

        if (!videoRect.contains(event->rect()))
        {
            QRegion region = event->region();
            region.subtracted(videoRect);

            QBrush brush = palette().background();

            foreach (const QRect &rect, region.rects())
                painter.fillRect(rect, brush);
        }

        m_surface->paint(&painter);
    }
    else
    {
        painter.fillRect(event->rect(), palette().background());
    }
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    m_surface->updateVideoRect();
}

