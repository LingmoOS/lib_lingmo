set(SRCS "")

file(GLOB SRCS_R "*.h" "*.c" "*.cpp")
foreach(filepath ${SRCS_R})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND SRCS ${filename})
endforeach()

add_library(lingmologger_qmlplugins SHARED ${SRCS})
target_link_libraries(lingmologger_qmlplugins PRIVATE LingmoLogger Qt5::Core Qt5::Quick Qt5::Gui)
target_include_directories(lingmologger_qmlplugins PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Install QML Plugins
install(TARGETS lingmologger_qmlplugins DESTINATION ${INSTALL_QMLDIR}/Lingmo/Logger)
install(FILES qmldir DESTINATION ${INSTALL_QMLDIR}/Lingmo/Logger)
