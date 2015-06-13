#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "MediaTestPlayer.h"

MediaTestPlayer::MediaTestPlayer(QWidget *parent)
    : QDialog(parent), m_capture("video4linux2")
{
    m_videoWdgt = new VideoWidget(this);

    QPushButton* playButton = new QPushButton(tr("Play"), this);

    connect(playButton, SIGNAL(clicked()),
                 this, SLOT(play()));

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(playButton);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_videoWdgt);
    layout->addLayout(controlLayout);

    setLayout(layout);
    //setMinimumSize(680, 550);
    setMinimumSize(380, 250);
}

MediaTestPlayer::~MediaTestPlayer()
{

}

void MediaTestPlayer::handlePicture(PicType type, int width, int height, void *picture, int picSize)
{
    if (YUV420P == type)
    {
        QSize frameSize(width, height);
        m_videoWdgt->display((uchar*)picture, frameSize, picSize, QVideoFrame::Format_YUV420P);
    }
}

void MediaTestPlayer::play()
{
    m_capture.open("/dev/video0");
    m_capture.capture(this);

}
