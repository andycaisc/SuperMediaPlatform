//picture handler handle picture from capture
//andycai_sc@163.com 2015-04-22

#ifndef SUPERPICTUREHANDLER_H_INCLUDED
#define SUPERPICTUREHANDLER_H_INCLUDED

class SuperPictureHandler
{
public:
    virtual ~SuperPictureHandler() {}

    enum PicType
    {
        YUV420P,
        RGB24
    }

    virtual void handlePicture(PicType type, int width, int height, void* picture, int picSize) = 0;

protected:
    SuperPictureHandler() {}
};

#endif // SUPERPICTUREHANDLER_H_INCLUDED
