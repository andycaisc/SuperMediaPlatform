//this class use capture video pictures from video device
//andycai_sc@163.com 2015-04-21

#ifndef SUPERVIDEOCAPTURE_INCLUDED
#define SUPERVIDEOCAPTURE_INCLUDED

#include <memory>
#include "SupVideoCaptureImpl.h"
#include "SupMedProducerAPI.h"

class SUPMEDPRODUCER_API SuperVideoCapture
{
public:
    SuperVideoCapture(const std::string& videoFormat = "");
    ~SuperVideoCapture();

    bool open(const std::string& device);

    void capture(SuperPictureHandler* pictureHandler);

    void stop();

private:
    std::auto_ptr<SupVideoCaptureImpl> m_videoCaptureImpl;
};


#endif // SUPERVIDEOCAPTURE_INCLUDED
