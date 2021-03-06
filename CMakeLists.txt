cmake_minimum_required(VERSION 3.5)

project(stc-test-task LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}Test REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        tableview.cpp
        tableview.h
        databasethread.cpp
        databasethread.h
        tablemodel.cpp
        tablemodel.h
        dirwrapper.h dirwrapper.cpp
        database.h database.cpp
        test.h test.cpp
        fileprocessthread.h fileprocessthread.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(stc-test-task
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(stc-test-task SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(stc-test-task
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(stc-test-task PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(stc-test-task PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(stc-test-task PRIVATE Qt${QT_VERSION_MAJOR}::Test)
