//this video capture implement interface
//andycai_sc@163.com 2015-04-22

#ifndef SUPVIDEOCAPTUREIMPL_INCLUDED
#define SUPVIDEOCAPTUREIMPL_INCLUDED

#include <string>
#include "SuperPictureHandler.h"

class SupVideoCaptureImpl
{
public:
    virtual ~SupVideoCaptureImpl() {}

    virtual bool open(const std::string& device) = 0;
    virtual void capture(SuperPictureHandler* pictureHandler) = 0;

    virtual void stop() = 0;

protected:
    SupVideoCaptureImpl(const std::string& videoFormat) : m_videoFormat(videoFormat)
    {
    }
    std::string m_videoFormat;
};

#endif // SUPVIDEOCAPTUREIMPL_INCLUDED
