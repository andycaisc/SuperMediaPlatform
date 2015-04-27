//implment SupVideoCapFFmpegImpl
//andycai_sc@163.com

#include "SuperMediaProducer/SupVideoCapFFmpegImpl.h"

SupVideoCapFFmpegImpl::SupVideoCapFFmpegImpl(const std::string& videoFormat) :
SupVideoCaptureImpl(videoFormat), m_avFormatCtx(0), m_avInputFormat(0),m_avCodecCtx(0), m_avCodec(0),
m_swsCtx(0), m_pictureHandler(0), m_captureActivity(this, &SupVideoCapFFmpegImpl::capturing)
{
}

SupVideoCapFFmpegImpl::~SupVideoCapFFmpegImpl()
{
}

bool SupVideoCapFFmpegImpl::open(const std::string& device)
{
    m_avInputFormat = av_find_input_format(m_videoFormat.c_str());

    if (avformat_open_input(&m_avFormatCtx, device.c_str(), m_avInputFormat, 0) != 0)
        return false;


}
