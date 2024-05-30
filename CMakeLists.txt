cmake_minimum_required(VERSION 3.14)

project(sss LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)  # Include Widgets module
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)  # Include Widgets module


set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(sss
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/sparsematrix.h src/sparsematrix.cpp
        main.qml
        resource.qrc

    )
else()
    if(ANDROID)
        add_library(sss SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(sss
            ${PROJECT_SOURCES}
        )
    endif()
endif()
# add_executable(sss
#   src/main.cpp
#   src/sparsematrix.h src/sparsematrix.cpp
#   main.qml
#   resource.qrc
#   src/mainwindow.h src/mainwindow.cpp
# )

target_link_libraries(sss PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


include(GNUInstallDirs)
install(TARGETS sss
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(sss)
endif()
