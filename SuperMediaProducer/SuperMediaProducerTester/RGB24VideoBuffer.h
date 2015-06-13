//RGB24 video data buffer
//andycai_sc@163.com 2015-05-24

#ifndef RGB24VIDEOBUFFER_H
#define RGB24VIDEOBUFFER_H

#include <QSize>
#include <QAbstractVideoBuffer>

class RGB24VideoBuffer : public QAbstractVideoBuffer
{
public:
    RGB24VideoBuffer(uchar* picture, const QSize& picSize, int numBytes, HandleType type = NoHandle);
    ~RGB24VideoBuffer();

    MapMode mapMode() const;
    uchar *map(MapMode mode, int *numBytes, int *bytesPerLine);
    void unmap();

private:
    uchar* m_picture;
    QSize m_picSize;
    int m_numBytes;
};

#endif // RGB24VIDEOBUFFER_H
