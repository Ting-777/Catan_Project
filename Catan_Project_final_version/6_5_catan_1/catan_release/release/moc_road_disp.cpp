/****************************************************************************
** Meta object code from reading C++ file 'road_disp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../widgets/road_disp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'road_disp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Road_disp_t {
    QByteArrayData data[12];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Road_disp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Road_disp_t qt_meta_stringdata_Road_disp = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Road_disp"
QT_MOC_LITERAL(1, 10, 14), // "has_built_road"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "road_index"
QT_MOC_LITERAL(4, 37, 19), // "game_status_updated"
QT_MOC_LITERAL(5, 57, 22), // "send_build_road_signal"
QT_MOC_LITERAL(6, 80, 20), // "display_befor_decide"
QT_MOC_LITERAL(7, 101, 39), // "display_before_decide_in_open..."
QT_MOC_LITERAL(8, 141, 11), // "point_index"
QT_MOC_LITERAL(9, 153, 20), // "display_after_decide"
QT_MOC_LITERAL(10, 174, 19), // "change_circle_index"
QT_MOC_LITERAL(11, 194, 15) // "disable_display"

    },
    "Road_disp\0has_built_road\0\0road_index\0"
    "game_status_updated\0send_build_road_signal\0"
    "display_befor_decide\0"
    "display_before_decide_in_opening_status\0"
    "point_index\0display_after_decide\0"
    "change_circle_index\0disable_display"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Road_disp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    1,   60,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,
      10,    0,   66,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Road_disp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Road_disp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->has_built_road((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->game_status_updated(); break;
        case 2: _t->send_build_road_signal(); break;
        case 3: _t->display_befor_decide(); break;
        case 4: _t->display_before_decide_in_opening_status((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->display_after_decide((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->change_circle_index(); break;
        case 7: _t->disable_display(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Road_disp::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Road_disp::has_built_road)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Road_disp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Road_disp::game_status_updated)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Road_disp::staticMetaObject = { {
    QMetaObject::SuperData::link<QPushButton::staticMetaObject>(),
    qt_meta_stringdata_Road_disp.data,
    qt_meta_data_Road_disp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Road_disp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Road_disp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Road_disp.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int Road_disp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Road_disp::has_built_road(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Road_disp::game_status_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
