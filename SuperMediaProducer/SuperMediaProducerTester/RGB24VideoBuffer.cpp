//implement RGB24VideoBuffer
//andycai_sc@163.com 2015-05-24

#include "RGB24VideoBuffer.h"

RGB24VideoBuffer::RGB24VideoBuffer(uchar *picture, const QSize &picSize, int numBytes, HandleType type) :
    QAbstractVideoBuffer(type), m_picSize(picSize), m_numBytes(numBytes)
{
    m_picture = new uchar[m_numBytes];
    memcpy(m_picture, picture, m_numBytes);
}

RGB24VideoBuffer::~RGB24VideoBuffer()
{
    delete[] m_picture;
}

QAbstractVideoBuffer::MapMode RGB24VideoBuffer::mapMode() const
{
    return ReadOnly;
}

uchar* RGB24VideoBuffer::map(MapMode mode, int *numBytes, int *bytesPerLine)
{
    if (mode == ReadOnly)
    {
        (*numBytes) = m_numBytes;
        (*bytesPerLine) = m_picSize.width() * 3;
    }

    return m_picture;
}

void RGB24VideoBuffer::unmap()
{
}

