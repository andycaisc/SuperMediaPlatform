//implement SuperVidoeCapture
//andycai_sc@163.com 2015-05-08

#include "SuperMediaProducer/SuperVideoCapture.h"
#include "SuperMediaProducer/SupVideoCapFFmpegImpl.h"

SuperVideoCapture::SuperVideoCapture(const std::string& videoFormat) :
m_videoCaptureImpl(new SupVideoCapFFmpegImpl(videoFormat))
{
}

SuperVideoCapture::~SuperVideoCapture()
{
}

bool SuperVideoCapture::open(const std::string& device)
{
    return m_videoCaptureImpl->open(device);
}

void SuperVideoCapture::capture(SuperPictureHandler* pictureHandler)
{
    m_videoCaptureImpl->capture(pictureHandler);
}

void SuperVideoCapture::stop()
{
    m_videoCaptureImpl->stop();
}
