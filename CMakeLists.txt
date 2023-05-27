cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)

project(
  Gooey
  VERSION 0.0.1
  LANGUAGES C CXX ASM
)

set(WEBVIEW "Microsoft.Web.WebView2")
set(WEBVIEW_VER "1.0.1774.30")
set(WEBVIEW_LIB "${WEBVIEW}.${WEBVIEW_VER}")
set(WEBVIEW_DLL WebView2Loader.dll)

math(EXPR BITNESS "${CMAKE_SIZEOF_VOID_P} * 8" OUTPUT_FORMAT DECIMAL)
message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION} (${BITNESS}-bit) [${CMAKE_BUILD_TYPE}]")
file(WRITE ${CMAKE_BINARY_DIR}/version.txt "v${PROJECT_VERSION}")

execute_process(
  COMMAND
  nuget install ${WEBVIEW} -Version ${WEBVIEW_VER} -OutputDirectory ${CMAKE_SOURCE_DIR}/external
)

add_subdirectory(
  libs/JUCE
  EXCLUDE_FROM_ALL
)

juce_add_gui_app(
  ${PROJECT_NAME}
  ICON_BIG ${CMAKE_SOURCE_DIR}/data/icon.svg
  ICON_SMALL ${CMAKE_SOURCE_DIR}/data/icon.svg
)

target_sources(
  ${PROJECT_NAME}
  PRIVATE
  src/Main.cpp
  src/MainComponent.cpp
  src/Theme.cpp
  src/WebView.cpp
  src/LookAndFeel.cpp
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
  PRIVATE
  libs/choc/platform
  external/${WEBVIEW_LIB}/build/native/include
)

if(DEFINED ENV{ASIOSDK_DIR})
  file(TO_CMAKE_PATH "$ENV{ASIOSDK_DIR}" ASIOSDK_DIR)
  target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    JUCE_ASIO=1
  )
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${ASIOSDK_DIR}/common
  )
endif()

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  juce::juce_gui_basics
  juce::juce_gui_extra
  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)
