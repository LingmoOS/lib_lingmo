set(LIB_VERSION_MAJOR 1)
set(LIB_VERSION_MINOR 0)
set(LIB_VERSION_PATCH 0)
set(LIB_VERSION ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH})

set(SCREEN_SRCS
    common/control.cpp
    common/globals.cpp
    common/orientation_sensor.cpp
    common/utils.cpp
    confighandler.cpp
    outputmodel.cpp
    plugin.cpp
    screen.cpp
)

find_package(KF5Screen REQUIRED)
find_package(KF5KIO REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Test Sensors)

add_library(lingmoscreen_qmlplugins SHARED ${SCREEN_SRCS})

generate_export_header(lingmoscreen_qmlplugins)

target_include_directories(lingmoscreen_qmlplugins PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries (lingmoscreen_qmlplugins
    Qt5::Core
    Qt5::Quick
    Qt5::Gui
    Qt5::DBus
    Qt5::Sensors
    Qt5::Test

    KF5::Screen
    KF5::KIOCore
)

set(CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/LibLingmo/Screen")

include(GNUInstallDirs)

install(TARGETS lingmoscreen_qmlplugins EXPORT LingmoScreenTargets DESTINATION ${INSTALL_QMLDIR}/Lingmo/Screen )
install(FILES qmldir DESTINATION ${INSTALL_QMLDIR}/Lingmo/Screen)
install(EXPORT LingmoScreenTargets DESTINATION ${CMAKECONFIG_INSTALL_DIR})
install(FILES
 screen.h
 outputmodel.h
 confighandler.h
 ${CMAKE_CURRENT_BINARY_DIR}/lingmoscreen_qmlplugins_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LibLingmo/Screen
)
