set(SRCS "")

file(GLOB SRCS_R "*.h" "*.c" "*.cpp")
foreach(filepath ${SRCS_R})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND SRCS ${filename})
endforeach()

# Create Qt6 library target
qt_add_library(lingmologger_qmlplugins SHARED)

target_link_libraries(lingmologger_qmlplugins PRIVATE LingmoLogger Qt6::Core Qt6::Quick Qt6::Gui)

target_include_directories(lingmologger_qmlplugins PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

qt_add_qml_module(lingmologger_qmlplugins
    PLUGIN_TARGET lingmologger_qmlplugins
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/temp/Lingmo/Logger
    VERSION "1.0"
    URI "Lingmo.Logger"
    TYPEINFO "plugins.qmltypes"
    SOURCES ${SRCS}
    RESOURCE_PREFIX "/lingmo/logger"
)

set_target_properties(lingmologger_qmlplugins
    PROPERTIES  VERSION 1.0.0 SOVERSION 1)

# Install QML Plugins
install(DIRECTORY ${CMAKE_BINARY_DIR}/temp/Lingmo/Logger DESTINATION ${INSTALL_QMLDIR}/Lingmo)
generate_export_header(lingmologger_qmlplugins BASE_NAME lingmologger_qmlplugins)
