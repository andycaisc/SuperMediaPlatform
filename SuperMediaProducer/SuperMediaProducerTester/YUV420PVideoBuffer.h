//VideoBuffer inheritied from QAbstractVideoBuffer
//andycai_sc@163.com 2015-05-04

#ifndef YUV420PVIDEOBUFFER_H
#define YUV420PVIDEOBUFFER_H

#include <QAbstractPlanarVideoBuffer>
#include <QSize>

class YUV420PVideoBuffer : public QAbstractPlanarVideoBuffer
{
public:
    YUV420PVideoBuffer(uchar* picture, const QSize& picSize, int numBytes, HandleType type = NoHandle);
    ~YUV420PVideoBuffer();

    int map(MapMode mode, int *numBytes, int bytesPerLine[4], uchar *data[4]);
    void unmap();
    MapMode mapMode() const;

private:
    uchar* m_picture;
    QSize m_picSize;
    int m_numBytes;
};

#endif // VIDEOBUFFER_H
