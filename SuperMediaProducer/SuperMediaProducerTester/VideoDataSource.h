//this class use to contain video picture
//andycai_sc@163.com 2015-05-07

#ifndef VIDEODATASOURCE_H
#define VIDEODATASOURCE_H

#include <QObject>
#include <QVideoFrame>
#include "YUV420PVideoBuffer.h"

class VideoDataSource : public QObject
{
    Q_OBJECT
public:
    VideoDataSource(QObject* parent = 0);
    ~VideoDataSource();

    void push(uchar* picture, const QSize& size, int numBytes, QVideoFrame::PixelFormat format);

signals:
    void videoBufferChanged(QAbstractVideoBuffer* buffer, const QSize& size, QVideoFrame::PixelFormat format);

};

#endif // VIDEODATASOURCE_H
