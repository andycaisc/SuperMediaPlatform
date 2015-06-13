//implement YUV420PVideoBuffer
//andycai_sc@163.com 2015-05-06

#include "YUV420PVideoBuffer.h"

YUV420PVideoBuffer::YUV420PVideoBuffer(uchar *picture, const QSize &picSize,
 int numBytes, HandleType type) : QAbstractPlanarVideoBuffer(type),
    m_picSize(picSize), m_numBytes(numBytes)
{
    m_picture = new uchar[m_numBytes];
    memcpy(m_picture, picture, m_numBytes);
}


YUV420PVideoBuffer::~YUV420PVideoBuffer()
{
    delete[] m_picture;
}

int YUV420PVideoBuffer::map(MapMode mode, int *numBytes, int bytesPerLine[], uchar *data[])
{
    if (mode == ReadOnly)
    {
        (*numBytes) = m_numBytes;

        bytesPerLine[0] = m_picSize.width();
        bytesPerLine[1] = m_picSize.width() / 4;
        bytesPerLine[2] = m_picSize.width() / 4;

        data[0] = m_picture;
        data[1] = m_picture + m_picSize.width() * m_picSize.height();
        data[2] = data[1] + m_picSize.width() * m_picSize.height() / 4;
    }

    return 3;
}

void YUV420PVideoBuffer::unmap()
{
}

QAbstractVideoBuffer::MapMode YUV420PVideoBuffer::mapMode() const
{
    return ReadOnly;
}
