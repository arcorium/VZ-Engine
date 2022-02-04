cmake_minimum_required(VERSION 3.10)

project(VZ-Engine VERSION 1.0 LANGUAGES CXX C)  # Set double languages so it wont got error when c files is included

# Set c++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# =============================================== OPTION ===============================================
option(VZ_BUILD_SHARED "Build Game Engine as shared" ON)

if(BUILD_SHARED)
    message(STATUS "Built as Shared")
    set(VZ_LIBRARY_BUILD "SHARED")
else()
    message(STATUS "Built as Static")
    set(VZ_LIBRARY_BUILD "STATIC")
endif()

option(VZ_USE_PRECOMPILED_HEADER "Use precompiled header" ON)

option(VZ_SAMPLE "Build Sample" ON)

option(VZ_USE_ASSERT "Use assert to checking" ON)
# =======================================================================================================

# File Headers
list(APPEND VZ_HEADERS
    src/vz/event/MouseEvent.h
    src/vz/event/Event.h
    src/vz/event/ApplicationEvent.h
    src/vz/event/KeyEvent.h
    src/vz/EntryPoint.h
    src/vz/Log.h
    src/vz/vz.h
    src/vz/Core.h
    src/vz/Application.h
    src/vz/Window.h
)

# Is using precompiled headers or use it as "header"
if (USE_PRECOMPILED_HEADER)
    target_precompile_headers(VZ-Engine PRIVATE src/vzpch.h)
else()
    list(APPEND VZ_HEADERS src/vzpch.h)
endif()

# File Sources
list(APPEND VZ_SOURCES
    src/vz/Application.cpp
    src/vz/Log.cpp
    thirdparty/glad/glad.c
)

# Set as library
add_library(VZ-Engine
    ${VZ_LIBRARY_BUILD}
    ${VZ_HEADERS}
    ${VZ_SOURCES}
    "src/vz/Window.cpp")

# Set properties for the library
set_target_properties(VZ-Engine
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    )

# Set properties for the library
target_include_directories(
    VZ-Engine
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spdlog/include"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLFW3/include"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"
    )

# =============================================== DEFINE ===============================================

list(APPEND
    VZ_DEFINES_PRIVATE
    VZ_BUILD
)

#if (VZ_USE_ASSERT)
    list(APPEND
        VZ_DEFINES_PUBLIC
        VZ_ASSERT_ENABLED
    )
#endif()

# Platform
if (WIN32 AND MSVC)
    message(STATUS "Platform : Windows")
    list(APPEND VZ_DEFINES_PUBLIC VZ_PLATFORM_WIN)
elseif(UNIX)
    message(STATUS "Platform : Linux")
    list(APPEND VZ_DEFINES_PUBLIC VZ_PLATFORM_UNIX)
else()
    message(WARNING "Platform is unknown")
endif()

# Single config generator
if (CMAKE_BUILD_TYPE EQUAL "Debug")
    target_compile_definitions(VZ-Engine PUBLIC VZ_DEBUG)
elseif (CMAKE_BUILD_TYPE EQUAL "Release")
    target_compile_definitions(VZ-Engine PUBLIC VZ_RELEASE)
else()
    message(STATUS "Built on multiple configuration")
    target_compile_definitions(VZ-Engine PUBLIC VZ_DEBUG)
endif()

# Build library type
if (NOT BUILD_SHARED)
    list(APPEND VZ_DEFINES_INTERFACE VZ_STATIC)
endif()

target_compile_definitions(VZ-Engine 
    PUBLIC ${VZ_DEFINES_PUBLIC}
    PRIVATE ${VZ_DEFINES_PRIVATE}
    INTERFACE ${VZ_DEFINES_INTERFACE}
    )

# =======================================================================================================

configure_file(src/config.h.in config.h)

target_link_libraries(VZ-Engine INTERFACE glfw) # Set any executable or library that consume VZ-Engine to consume glfw library

add_subdirectory(thirdparty/GLFW3)

# Build sandbox as sample of the engine
if (VZ_SAMPLE)
    add_subdirectory(Sandbox)
endif()

# =============================================== INSTALL ===============================================
install(TARGETS VZ-Engine DESTINATION lib)
install(FILES
    src/vz/event/MouseEvent.h
    src/vz/event/Event.h
    src/vz/event/ApplicationEvent.h
    src/vz/event/KeyEvent.h
    src/vz/EntryPoint.h
    src/vz/Log.h
    src/vz/vz.h
    src/vz/Core.h
    src/vz/Application.h
    DESTINATION include
    )

install (FILES ${CMAKE_BINARY_DIR}/VZ/config.h
    DESTINATION include
    )

# =======================================================================================================