/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FileMangerQT/view.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSViewENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSViewENDCLASS = QtMocHelpers::stringData(
    "View",
    "copyFile",
    "",
    "std::string",
    "source_path",
    "destination_path",
    "delFile",
    "filePath",
    "on_treeView_clicked",
    "QModelIndex",
    "index",
    "on_tableView_clicked",
    "onCopy",
    "onPaste",
    "onDel",
    "on_treeView_pressed",
    "on_lineEditPath_textEdited",
    "arg1",
    "on_tableView_doubleClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSViewENDCLASS_t {
    uint offsetsAndSizes[38];
    char stringdata0[5];
    char stringdata1[9];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[12];
    char stringdata5[17];
    char stringdata6[8];
    char stringdata7[9];
    char stringdata8[20];
    char stringdata9[12];
    char stringdata10[6];
    char stringdata11[21];
    char stringdata12[7];
    char stringdata13[8];
    char stringdata14[6];
    char stringdata15[20];
    char stringdata16[27];
    char stringdata17[5];
    char stringdata18[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSViewENDCLASS_t qt_meta_stringdata_CLASSViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 4),  // "View"
        QT_MOC_LITERAL(5, 8),  // "copyFile"
        QT_MOC_LITERAL(14, 0),  // ""
        QT_MOC_LITERAL(15, 11),  // "std::string"
        QT_MOC_LITERAL(27, 11),  // "source_path"
        QT_MOC_LITERAL(39, 16),  // "destination_path"
        QT_MOC_LITERAL(56, 7),  // "delFile"
        QT_MOC_LITERAL(64, 8),  // "filePath"
        QT_MOC_LITERAL(73, 19),  // "on_treeView_clicked"
        QT_MOC_LITERAL(93, 11),  // "QModelIndex"
        QT_MOC_LITERAL(105, 5),  // "index"
        QT_MOC_LITERAL(111, 20),  // "on_tableView_clicked"
        QT_MOC_LITERAL(132, 6),  // "onCopy"
        QT_MOC_LITERAL(139, 7),  // "onPaste"
        QT_MOC_LITERAL(147, 5),  // "onDel"
        QT_MOC_LITERAL(153, 19),  // "on_treeView_pressed"
        QT_MOC_LITERAL(173, 26),  // "on_lineEditPath_textEdited"
        QT_MOC_LITERAL(200, 4),  // "arg1"
        QT_MOC_LITERAL(205, 26)   // "on_tableView_doubleClicked"
    },
    "View",
    "copyFile",
    "",
    "std::string",
    "source_path",
    "destination_path",
    "delFile",
    "filePath",
    "on_treeView_clicked",
    "QModelIndex",
    "index",
    "on_tableView_clicked",
    "onCopy",
    "onPaste",
    "onDel",
    "on_treeView_pressed",
    "on_lineEditPath_textEdited",
    "arg1",
    "on_tableView_doubleClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSViewENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   74,    2, 0x06,    1 /* Public */,
       6,    1,   79,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   82,    2, 0x08,    6 /* Private */,
      11,    1,   85,    2, 0x08,    8 /* Private */,
      12,    0,   88,    2, 0x08,   10 /* Private */,
      13,    0,   89,    2, 0x08,   11 /* Private */,
      14,    0,   90,    2, 0x08,   12 /* Private */,
      15,    1,   91,    2, 0x08,   13 /* Private */,
      16,    1,   94,    2, 0x08,   15 /* Private */,
      18,    1,   97,    2, 0x08,   17 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

Q_CONSTINIT const QMetaObject View::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSViewENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSViewENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSViewENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<View, std::true_type>,
        // method 'copyFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        // method 'delFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        // method 'on_treeView_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_tableView_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'onCopy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPaste'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_treeView_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_lineEditPath_textEdited'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_tableView_doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>
    >,
    nullptr
} };

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<View *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->copyFile((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2]))); break;
        case 1: _t->delFile((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 2: _t->on_treeView_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 3: _t->on_tableView_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 4: _t->onCopy(); break;
        case 5: _t->onPaste(); break;
        case 6: _t->onDel(); break;
        case 8: _t->on_lineEditPath_textEdited((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->on_tableView_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (View::*)(std::string , std::string );
            if (_t _q_method = &View::copyFile; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (View::*)(std::string );
            if (_t _q_method = &View::delFile; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSViewENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void View::copyFile(std::string _t1, std::string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void View::delFile(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
