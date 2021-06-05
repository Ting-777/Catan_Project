/****************************************************************************
** Meta object code from reading C++ file 'point_disp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../widgets/point_disp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'point_disp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Point_disp_t {
    QByteArrayData data[11];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Point_disp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Point_disp_t qt_meta_stringdata_Point_disp = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Point_disp"
QT_MOC_LITERAL(1, 11, 21), // "has_built_small_house"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "point_index"
QT_MOC_LITERAL(4, 46, 19), // "has_built_big_house"
QT_MOC_LITERAL(5, 66, 22), // "construction_completed"
QT_MOC_LITERAL(6, 89, 29), // "send_build_small_house_signal"
QT_MOC_LITERAL(7, 119, 27), // "send_build_big_house_signal"
QT_MOC_LITERAL(8, 147, 20), // "display_befor_decide"
QT_MOC_LITERAL(9, 168, 20), // "display_after_decide"
QT_MOC_LITERAL(10, 189, 19) // "change_circle_index"

    },
    "Point_disp\0has_built_small_house\0\0"
    "point_index\0has_built_big_house\0"
    "construction_completed\0"
    "send_build_small_house_signal\0"
    "send_build_big_house_signal\0"
    "display_befor_decide\0display_after_decide\0"
    "change_circle_index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Point_disp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    0,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   61,    2, 0x0a /* Public */,
       7,    0,   62,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void Point_disp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Point_disp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->has_built_small_house((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->has_built_big_house((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->construction_completed(); break;
        case 3: _t->send_build_small_house_signal(); break;
        case 4: _t->send_build_big_house_signal(); break;
        case 5: _t->display_befor_decide(); break;
        case 6: _t->display_after_decide((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->change_circle_index(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Point_disp::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Point_disp::has_built_small_house)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Point_disp::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Point_disp::has_built_big_house)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Point_disp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Point_disp::construction_completed)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Point_disp::staticMetaObject = { {
    QMetaObject::SuperData::link<QPushButton::staticMetaObject>(),
    qt_meta_stringdata_Point_disp.data,
    qt_meta_data_Point_disp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Point_disp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Point_disp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Point_disp.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int Point_disp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Point_disp::has_built_small_house(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Point_disp::has_built_big_house(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Point_disp::construction_completed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
