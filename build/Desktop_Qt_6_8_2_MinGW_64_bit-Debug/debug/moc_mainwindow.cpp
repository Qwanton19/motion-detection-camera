/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../MotionDetectorProject/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "captureImage",
    "",
    "applyGrayscaleEffect",
    "value",
    "processFrame",
    "QVideoFrame",
    "frame",
    "toggleTimestamp",
    "Qt::CheckState",
    "state",
    "handleImageCaptured",
    "id",
    "image",
    "queueFrame",
    "processNextFrame",
    "toggleMotionDetection",
    "setMotionThreshold",
    "setMotionSensitivity",
    "toggleRecording",
    "updateRecordTime",
    "handleRecordingError",
    "QMediaRecorder::Error",
    "error",
    "errorString",
    "handleMotionDetected",
    "resetMotionEmailFlag",
    "toggleEmailNotifications",
    "toggleAutoSaveMotionImages",
    "handleAutoSaveMotionImage"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  122,    2, 0x08,    1 /* Private */,
       3,    1,  123,    2, 0x08,    2 /* Private */,
       5,    1,  126,    2, 0x08,    4 /* Private */,
       8,    1,  129,    2, 0x08,    6 /* Private */,
      11,    2,  132,    2, 0x08,    8 /* Private */,
      14,    1,  137,    2, 0x08,   11 /* Private */,
      15,    0,  140,    2, 0x08,   13 /* Private */,
      16,    1,  141,    2, 0x08,   14 /* Private */,
      17,    1,  144,    2, 0x08,   16 /* Private */,
      18,    1,  147,    2, 0x08,   18 /* Private */,
      19,    0,  150,    2, 0x08,   20 /* Private */,
      20,    0,  151,    2, 0x08,   21 /* Private */,
      21,    2,  152,    2, 0x08,   22 /* Private */,
      25,    0,  157,    2, 0x08,   25 /* Private */,
      26,    0,  158,    2, 0x08,   26 /* Private */,
      27,    1,  159,    2, 0x08,   27 /* Private */,
      28,    1,  162,    2, 0x08,   29 /* Private */,
      29,    0,  165,    2, 0x08,   31 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,   12,   13,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22, QMetaType::QString,   23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'captureImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyGrayscaleEffect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'processFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVideoFrame &, std::false_type>,
        // method 'toggleTimestamp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::CheckState, std::false_type>,
        // method 'handleImageCaptured'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        // method 'queueFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVideoFrame &, std::false_type>,
        // method 'processNextFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleMotionDetection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::CheckState, std::false_type>,
        // method 'setMotionThreshold'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setMotionSensitivity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'toggleRecording'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateRecordTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleRecordingError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaRecorder::Error, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleMotionDetected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetMotionEmailFlag'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleEmailNotifications'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::CheckState, std::false_type>,
        // method 'toggleAutoSaveMotionImages'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::CheckState, std::false_type>,
        // method 'handleAutoSaveMotionImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->captureImage(); break;
        case 1: _t->applyGrayscaleEffect((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->processFrame((*reinterpret_cast< std::add_pointer_t<QVideoFrame>>(_a[1]))); break;
        case 3: _t->toggleTimestamp((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 4: _t->handleImageCaptured((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QImage>>(_a[2]))); break;
        case 5: _t->queueFrame((*reinterpret_cast< std::add_pointer_t<QVideoFrame>>(_a[1]))); break;
        case 6: _t->processNextFrame(); break;
        case 7: _t->toggleMotionDetection((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 8: _t->setMotionThreshold((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->setMotionSensitivity((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->toggleRecording(); break;
        case 11: _t->updateRecordTime(); break;
        case 12: _t->handleRecordingError((*reinterpret_cast< std::add_pointer_t<QMediaRecorder::Error>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->handleMotionDetected(); break;
        case 14: _t->resetMotionEmailFlag(); break;
        case 15: _t->toggleEmailNotifications((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 16: _t->toggleAutoSaveMotionImages((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 17: _t->handleAutoSaveMotionImage(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVideoFrame >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVideoFrame >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
