/****************************************************************************
** Meta object code from reading C++ file 'point_disp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../widgets/point_disp.h"
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
    QByteArrayData data[13];
    char stringdata0[269];
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
QT_MOC_LITERAL(5, 66, 19), // "game_status_updated"
QT_MOC_LITERAL(6, 86, 22), // "construction_completed"
QT_MOC_LITERAL(7, 109, 29), // "send_build_small_house_signal"
QT_MOC_LITERAL(8, 139, 27), // "send_build_big_house_signal"
QT_MOC_LITERAL(9, 167, 20), // "display_befor_decide"
QT_MOC_LITERAL(10, 188, 20), // "display_after_decide"
QT_MOC_LITERAL(11, 209, 39), // "display_before_decide_in_open..."
QT_MOC_LITERAL(12, 249, 19) // "change_circle_index"

    },
    "Point_disp\0has_built_small_house\0\0"
    "point_index\0has_built_big_house\0"
    "game_status_updated\0construction_completed\0"
    "send_build_small_house_signal\0"
    "send_build_big_house_signal\0"
    "display_befor_decide\0display_after_decide\0"
    "display_before_decide_in_opening_status\0"
    "change_circle_index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Point_disp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    0,   70,    2, 0x06 /* Public */,
       6,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   72,    2, 0x0a /* Public */,
       8,    0,   73,    2, 0x0a /* Public */,
       9,    0,   74,    2, 0x0a /* Public */,
      10,    1,   75,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
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
        case 2: _t->game_status_updated(); break;
        case 3: _t->construction_completed(); break;
        case 4: _t->send_build_small_house_signal(); break;
        case 5: _t->send_build_big_house_signal(); break;
        case 6: _t->display_befor_decide(); break;
        case 7: _t->display_after_decide((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->display_before_decide_in_opening_status(); break;
        case 9: _t->change_circle_index(); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Point_disp::game_status_updated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Point_disp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Point_disp::construction_completed)) {
                *result = 3;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
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
void Point_disp::game_status_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Point_disp::construction_completed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
