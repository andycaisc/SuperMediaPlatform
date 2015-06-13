
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"

}


#include "MediaTestPlayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MediaTestPlayer w;

    av_register_all();
    avformat_network_init();
    avdevice_register_all();

    w.show();

    return a.exec();
}
