cmake_minimum_required(VERSION 3.5)

project(FileManger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)
#find_package(Boost REQUIRED)
#find_package(Boost COMPONENTS filesystem REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets )
find_package(Boost REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)
set(PROJECT_SOURCES
        main.cpp
        view.cpp
        view.h
        view.ui
        filecontentview.h
        filecontentview.cpp
        filecontentview.ui
        controller.h
        controller.cpp
        explorer.h
        explorer.cpp
        explorermin.cpp
        explorermin.h
        fileoperations.cpp
        fileoperations.h
        Actions.h
        twopane.cpp
        twopane.h
        searchwindow.h
        searchwindow.cpp
        searchwindow.ui
        searchbar.h
        searchbar.cpp
        addonsbar.cpp
        addonsbar.h
#        identifyduplicates.cpp
#        identifyduplicates.h
#        identifyduplicatespagewidget.cpp
#        identifyduplicatespagewidget.h
#        piechartpagewidget.cpp
#        piechartpagewidget.h
#        PiechartWidget.cpp
#        PiechartWidget.h
#        propertiespagewidget.cpp
#        propertiespagewidget.h
#        statistics.cpp
#        statistics.h



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FileManger
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FileManger APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FileManger SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FileManger
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(FileManger PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Boost::filesystem)
#target_link_libraries(FileManger PRIVATE Qt${QT_VERSION_MAJOR}::Widgets boost_filesystem)

set_target_properties(FileManger PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS FileManger
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FileManger)
endif()

