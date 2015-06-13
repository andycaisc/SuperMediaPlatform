//VideoWidget use to paint video picture
//andycai_sc@163.com 2015-05-06

#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include "VideoDataSource.h"
#include "VideoWidgetSurface.h"

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = 0);
    ~VideoWidget();

    QAbstractVideoSurface *videoSurface() const { return m_surface; }

    QSize sizeHint() const;

    void display(uchar* picture, const QSize& size, int numBytes, const QVideoFrame::PixelFormat& format);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

private:
    VideoWidgetSurface *m_surface;
    VideoDataSource m_videoData;
 };

#endif // VIDEOWIDGET_H
