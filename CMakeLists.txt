cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(Test VERSION 0.0.1 LANGUAGES C CXX ASM)

add_subdirectory(libs/JUCE EXCLUDE_FROM_ALL)

# add_subdirectory(libs/clap-juce-extensions EXCLUDE_FROM_ALL)
math(EXPR BITNESS "${CMAKE_SIZEOF_VOID_P} * 8" OUTPUT_FORMAT DECIMAL)
message(STATUS "C++${CMAKE_CXX_STANDARD}, CMake ${CMAKE_VERSION}, ${CMAKE_GENERATOR}, ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "${PROJECT_NAME} (${BITNESS}-bit) [${CMAKE_BUILD_TYPE}] v${PROJECT_VERSION}")
file(WRITE ${CMAKE_BINARY_DIR}/version.txt "v${PROJECT_VERSION}")

juce_add_gui_app(
  ${PROJECT_NAME}

  # COMPANY_NAME ${PROJECT_NAME}
  # PLUGIN_MANUFACTURER_CODE ${PROJECT_NAME}
  # PLUGIN_CODE ${PROJECT_NAME}
  # FORMATS VST3 Standalone
  # PRODUCE_NAME ${PROJECT_NAME}
  # IS_SYNTH TRUE
  # NEEDS_MIDI_INPUT TRUE
  # NEEDS_MIDI_OUTPUT TRUE
  # IS_MIDI_EFFECT FALSE
)

target_sources(
  ${PROJECT_NAME}
  PRIVATE
  src/Main.cpp
  src/MainComponent.cpp
)

target_compile_definitions(
  ${PROJECT_NAME}
  PRIVATE
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
  JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>"
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  juce::juce_gui_extra
  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)

# clap_juce_extensions_plugin(
# TARGET ${PROJECT_NAME}
# CLAP_ID "com.test.test"
# CLAP_FEATURES note-effect
# )

#[[
if(DEFINED ENV{ASIOSDK_DIR} OR POWERSHELL_ASIO)
  if(POWERSHELL_ASIO)
    execute_process(COMMAND pwsh -NoProfile -Command "& {Import-Module .\\scripts\\ASIO && asio}")
    target_compile_definitions(${PROJECT_NAME} PUBLIC JUCE_ASIO=1)
    target_include_directories(${PROJECT_NAME} PUBLIC libs/asio/common)
  else()
    message(STATUS "Checking for Steinberg ASIO SDK")

    if(EXISTS "$ENV{ASIOSDK_DIR}/readme.txt")
      file(TO_CMAKE_PATH "$ENV{ASIOSDK_DIR}" ASIOSDK_DIR)
      message(STATUS "Steinberg ASIO SDK location: ${ASIOSDK_DIR}")
      message(STATUS "The resulting standalone executables are not licensed for distribution")
      target_compile_definitions(${PROJECT_NAME} PUBLIC JUCE_ASIO=1)
      target_include_directories(${PROJECT_NAME} PUBLIC ${ASIOSDK_DIR}/common)
    else()
      message(STATUS "Steinberg ASIO SDK not found")
    endif()
  endif()
endif()
]]
