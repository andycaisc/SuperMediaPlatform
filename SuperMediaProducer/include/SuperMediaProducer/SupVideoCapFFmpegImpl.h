//use ffmpeg implement video capture
//andycai_sc@163.com 2015-04-26

#ifndef SUPVIDEOCAPFFMPEGIMPL_INCLUDED
#define SUPVIDEOCAPFFMPEGIMPL_INCLUDED


extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"

};


#include "Poco/Activity.h"
#include "Poco/Thread.h"
#include "SupVideoCaptureImpl.h"

using namespace Poco;

class SupVideoCapFFmpegImpl : public SupVideoCaptureImpl
{
public:
    SupVideoCapFFmpegImpl(const std::string& videoFormat);
    ~SupVideoCapFFmpegImpl();

    bool open(const std::string& device);
    void capture(SuperPictureHandler* pictureHandler);

    void stop();

private:
    void capturing();

    AVFormatContext * m_avFormatCtx;
	AVInputFormat*  m_avInputFormat;
	AVCodecContext* m_avCodecCtx;
	AVCodec* m_avCodec;
	struct SwsContext *m_swsCtx;

	int m_videoIndex;

    SuperPictureHandler* m_pictureHandler;

    Activity<SupVideoCapFFmpegImpl> m_captureActivity;
};

#endif // SUPVIDEOCAPFFMPEGIMPL_INCLUDED
