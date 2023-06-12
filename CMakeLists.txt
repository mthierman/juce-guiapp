cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 23)

project(
  Gooey
  VERSION 0.0.1
  LANGUAGES C CXX ASM
)

math(EXPR BITNESS "${CMAKE_SIZEOF_VOID_P} * 8" OUTPUT_FORMAT DECIMAL)
message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION} (${BITNESS}-bit) [${CMAKE_BUILD_TYPE}]")
file(WRITE ${CMAKE_BINARY_DIR}/version.txt "v${PROJECT_VERSION}")

set(WEBVIEW "Microsoft.Web.WebView2")
set(WEBVIEW_VER "1.0.1823.32")

if(DEFINED ENV{WEBVIEW_PKG})
  set(WEBVIEW_PKG $ENV{WEBVIEW_PKG})
else()
  execute_process(
    COMMAND
    nuget install ${WEBVIEW} -Version ${WEBVIEW_VER} -OutputDirectory ${CMAKE_BINARY_DIR}/libs
  )
  set(WEBVIEW_PKG ${CMAKE_BINARY_DIR}/libs/${WEBVIEW}.${WEBVIEW_VER})
endif()

include(FetchContent)

if(DEFINED ENV{JUCE})
  set(JUCE_PKG $ENV{JUCE})
  add_subdirectory(
    ${JUCE_PKG}
    JUCE
    EXCLUDE_FROM_ALL
  )
else()
  FetchContent_Declare(
    JUCE
    URL https://github.com/juce-framework/JUCE/archive/refs/heads/develop.zip
  )
  FetchContent_MakeAvailable(JUCE)
endif()

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
  ${WEBVIEW_PKG}/build/native/include
)

if(DEFINED ENV{ASIOSDK_DIR})
  set(ASIOSDK_DIR $ENV{ASIOSDK_DIR})
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
