//implement VideoDataSource
//andycai_sc@163.com 2015-05-07

#include "VideoDataSource.h"

VideoDataSource::VideoDataSource(QObject *parent) : QObject(parent)
{

}

VideoDataSource::~VideoDataSource()
{
}

void VideoDataSource::push(uchar *picture, const QSize &size, int numBytes, QVideoFrame::PixelFormat format)
{
    emit videoBufferChanged(new YUV420PVideoBuffer(picture, size, numBytes), size, format);
}
