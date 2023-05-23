cmake_minimum_required(
  VERSION
  3.25
)

set(
  CMAKE_CXX_STANDARD
  20
)

set(
  CMAKE_TRY_COMPILE_TARGET_TYPE
  STATIC_LIBRARY
)

project(
  Test
  VERSION
  0.0.1
  LANGUAGES
  C
  CXX
  ASM
)

set(
  LIBS
  ${CMAKE_SOURCE_DIR}/libs
)

set(
  EXTERNAL
  ${CMAKE_SOURCE_DIR}/external
)

set(
  WEBVIEW_PKG
  "Microsoft.Web.WebView2"
)

set(
  WEBVIEW_VER
  "1.0.1774.30"
)

set(
  WEBVIEW
  "${WEBVIEW_PKG}.${WEBVIEW_VER}"
)

set(
  WEBVIEW_LIB
  WebView2Loader.dll
)

math(
  EXPR
  BITNESS
  "${CMAKE_SIZEOF_VOID_P} * 8" OUTPUT_FORMAT DECIMAL
)

message(
  STATUS
  "${PROJECT_NAME} v${PROJECT_VERSION} (${BITNESS}-bit) [${CMAKE_BUILD_TYPE}]"
)

file(
  WRITE
  ${CMAKE_BINARY_DIR}/version.txt
  "v${PROJECT_VERSION}"
)

execute_process(
  COMMAND
  nuget install ${WEBVIEW_PKG} -Version ${WEBVIEW_VER} -OutputDirectory ${EXTERNAL}
)

add_subdirectory(
  ${LIBS}/JUCE
  EXCLUDE_FROM_ALL
)

juce_add_gui_app(
  ${PROJECT_NAME}
)

target_sources(
  ${PROJECT_NAME}
  PRIVATE
  src/Main.cpp
)

target_compile_definitions(
  ${PROJECT_NAME}
  PRIVATE
  JUCE_WEB_BROWSER=1
  JUCE_USE_WIN_WEBVIEW2=1
  JUCE_USE_CURL=0
  JUCE_DISPLAY_SPLASH_SCREEN=0
  JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
  JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>"
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${EXTERNAL}/${WEBVIEW}/build/native/include
)

if(DEFINED ENV{ASIOSDK_DIR})
  file(TO_CMAKE_PATH "$ENV{ASIOSDK_DIR}" ASIOSDK_DIR)
  target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${ASIOSDK_DIR}/common
  )
  target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC
    JUCE_ASIO=1
  )
endif()

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  juce::juce_audio_basics
  juce::juce_audio_devices
  juce::juce_audio_formats
  juce::juce_audio_processors
  juce::juce_audio_utils
  juce::juce_core
  juce::juce_data_structures
  juce::juce_events
  juce::juce_graphics
  juce::juce_gui_basics
  juce::juce_gui_extra
  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
  ${EXTERNAL}/${WEBVIEW}/build/native/x64/WebView2LoaderStatic.lib
)
