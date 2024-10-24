set(SRCS "")

file(GLOB SRCS_R "*.h" "*.c" "*.cpp")
foreach(filepath ${SRCS_R})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND SRCS ${filename})
endforeach()

add_library(lingmologger_qmlplugins SHARED ${SRCS})
target_link_libraries(lingmologger_qmlplugins PRIVATE LingmoLogger Qt5::Core Qt5::Quick Qt5::Gui)
target_include_directories(lingmologger_qmlplugins PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# qmlplugindump
find_program(QMLPLUGINDUMP_EXECUTABLE qmlplugindump)
set(PLUGIN_NAME "Lingmo.Logger")
set(PLUGIN_VERSION "1.0")
set(PLUGIN_PARENT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(PLUGIN_QMLTYPES_PATH ${CMAKE_CURRENT_BINARY_DIR}/plugin.qmltypes)

# Create a custom command to generate the .qmltypes file
add_custom_command(
    OUTPUT ${PLUGIN_QMLTYPES_PATH}
    COMMAND /usr/bin/mkdir /tmp/${CMAKE_CURRENT_SOURCE_DIR}/Lingmo/Logger && /usr/bin/cp -rv ${CMAKE_CURRENT_SOURCE_DIR}/* /tmp/${CMAKE_CURRENT_SOURCE_DIR}/Lingmo/Logger
    COMMAND QML_PLUGIN_PATH=/tmp/${CMAKE_CURRENT_SOURCE_DIR} ${QMLPLUGINDUMP_EXECUTABLE} -noinstantiate -nonrelocatable ${PLUGIN_NAME} ${PLUGIN_VERSION} ${PLUGIN_PARENT_PATH} > ${PLUGIN_QMLTYPES_PATH}
    COMMAND /usr/bin/rm -rfv /tmp/${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS lingmologger_qmlplugins
)

# Add a custom target to ensure the command is run
add_custom_target(generate_qmltypes ALL DEPENDS ${PLUGIN_QMLTYPES_PATH})


# Install QML Plugins
install(TARGETS lingmologger_qmlplugins DESTINATION ${INSTALL_QMLDIR}/Lingmo/Logger)
install(FILES qmldir ${PLUGIN_QMLTYPES_PATH} DESTINATION ${INSTALL_QMLDIR}/Lingmo/Logger)
