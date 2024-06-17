cmake_minimum_required(VERSION 3.16)

project(liblingmo)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(QT Core Gui QuickControls2 Widgets DBus Xml Concurrent)
find_package(Qt6 COMPONENTS ${QT} REQUIRED)

set(QT_INSTALL_QMLDIR "")
get_target_property(QT_INSTALL_QMLDIR Qt6::Core IMPORTED_LOCATION)

if(NOT QT_INSTALL_QMLDIR)
    message(FATAL_ERROR "QML directory cannot be detected.")
else()
    message(STATUS "QML directory: ${QT_INSTALL_QMLDIR}")
endif()
# -------------------------------------------
add_subdirectory(accounts)
add_subdirectory(bluez)
add_subdirectory(mpris)
add_subdirectory(networkmanagement)
add_subdirectory(screen)
add_subdirectory(system)
add_subdirectory(audio)
