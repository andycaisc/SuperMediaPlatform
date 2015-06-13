/****************************************************************************
** Meta object code from reading C++ file 'VideoDataSource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SuperMediaProducerTester/VideoDataSource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VideoDataSource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VideoDataSource_t {
    QByteArrayData data[8];
    char stringdata[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoDataSource_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoDataSource_t qt_meta_stringdata_VideoDataSource = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VideoDataSource"
QT_MOC_LITERAL(1, 16, 18), // "videoBufferChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 21), // "QAbstractVideoBuffer*"
QT_MOC_LITERAL(4, 58, 6), // "buffer"
QT_MOC_LITERAL(5, 65, 4), // "size"
QT_MOC_LITERAL(6, 70, 24), // "QVideoFrame::PixelFormat"
QT_MOC_LITERAL(7, 95, 6) // "format"

    },
    "VideoDataSource\0videoBufferChanged\0\0"
    "QAbstractVideoBuffer*\0buffer\0size\0"
    "QVideoFrame::PixelFormat\0format"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoDataSource[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSize, 0x80000000 | 6,    4,    5,    7,

       0        // eod
};

void VideoDataSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoDataSource *_t = static_cast<VideoDataSource *>(_o);
        switch (_id) {
        case 0: _t->videoBufferChanged((*reinterpret_cast< QAbstractVideoBuffer*(*)>(_a[1])),(*reinterpret_cast< const QSize(*)>(_a[2])),(*reinterpret_cast< QVideoFrame::PixelFormat(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVideoFrame::PixelFormat >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VideoDataSource::*_t)(QAbstractVideoBuffer * , const QSize & , QVideoFrame::PixelFormat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoDataSource::videoBufferChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject VideoDataSource::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VideoDataSource.data,
      qt_meta_data_VideoDataSource,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VideoDataSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoDataSource::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VideoDataSource.stringdata))
        return static_cast<void*>(const_cast< VideoDataSource*>(this));
    return QObject::qt_metacast(_clname);
}

int VideoDataSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void VideoDataSource::videoBufferChanged(QAbstractVideoBuffer * _t1, const QSize & _t2, QVideoFrame::PixelFormat _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
