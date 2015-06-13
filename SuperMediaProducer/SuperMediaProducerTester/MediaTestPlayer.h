#ifndef MEDIATESTPLAYER_H
#define MEDIATESTPLAYER_H

#include <QDialog>
#include "VideoWidget.h"
#include "SuperMediaProducer/SuperVideoCapture.h"

class MediaTestPlayer : public QDialog, public SuperPictureHandler
{
    Q_OBJECT
public:
    MediaTestPlayer(QWidget *parent = 0);
    ~MediaTestPlayer();

    void handlePicture(PicType type, int width, int height, void* picture, int picSize);

public slots:
    void play();

private:
    VideoWidget* m_videoWdgt;
    SuperVideoCapture m_capture;
};

#endif // MEDIATESTPLAYER_H
