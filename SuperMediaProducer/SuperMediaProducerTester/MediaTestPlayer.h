#ifndef MEDIATESTPLAYER_H
#define MEDIATESTPLAYER_H

#include <QDialog>

class MediaTestPlayer : public QDialog
{
    Q_OBJECT

public:
    MediaTestPlayer(QWidget *parent = 0);
    ~MediaTestPlayer();
};

#endif // MEDIATESTPLAYER_H
