# General project settings.
cmake_minimum_required(VERSION 3.12.4)
project(ionshared VERSION 1.0.0 LANGUAGES CXX)

# Setup compiler flag(s) & standard(s).
set(CMAKE_CXX_STANDARD 20)

# Fix issue with Google tests adapter VSCode extension not loading test, as well as the dynamic lib. error when running executables (tests).
#set(CMAKE_EXE_LINKER_FLAGS "-static")

# General project information.
set(PROJECT_URL "https://github.com/ionlang/ionshared")

# Setup source and build directories.
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})

# TODO
#if (UNIX)
#    include(GNUInstallDirs)
#endif ()

# Setup default build flags.
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /MT")

# Option to use MD.
option(USE_MD "Use MD instead of MTd" OFF)

if(USE_MD)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    message(STATUS "Using /MD flag")
endif()

option(IONSHARED_BUILD_STATIC_LIB "Build static library" OFF)

if (IONSHARED_BUILD_STATIC_LIB)
    set(IONSHARED_OPTION_LIB_TYPE STATIC)
else()
    set(IONSHARED_OPTION_LIB_TYPE SHARED)
endif()

# Setup versioning.
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)")

# Configure and use LLVM. Also ensures LLVM is installed.
find_package(LLVM 12.0.1 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Include LLVM source directories (for lexical support, etc.). The SYSTEM symbol supposedly marks the directory to suppress warning(s).
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Disable warnings from includes.
#add_library(llvm INTERFACE)
#target_sources(llvm INTERFACE)
#target_include_directories(llvm PRIVATE include/ SYSTEM INTERFACE include/)

# Set source files.
file(
    GLOB_RECURSE SOURCES "include/${PROJECT_NAME}/*.h" "src/*.cpp" "src/*.h"
)

# Specify that this project is a library.
add_library("${PROJECT_NAME}" ${IONSHARED_OPTION_LIB_TYPE} ${SOURCES})

# Set VERSION property. Optional, but good practice.
set_target_properties("${PROJECT_NAME}" PROPERTIES VERSION ${PROJECT_VERSION})

# Link .libs (same functionality handled by llvm_map_components_to_libnames().)
#target_link_libraries(${PROJECT_NAME} ${LIB_SOURCES})

# Linux installation support.
include(GNUInstallDirs)

# Provide include directories to be used in the build command. Position in file matters.
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

    # Comment out as it's causing cannot find included file '/project_name'.
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

# Determine whether to link against LLVM static libraries
# or dynamic library (libLLVM.dll).
if(BUILD_SHARED_LIBS)
    # Find the libraries that correspond to the LLVM components
    # that we wish to use.
    llvm_map_components_to_libnames(llvm_libs all)
else()
    set(llvm_libs LLVM)
endif()

# Link against LLVM libraries.
target_link_libraries("${PROJECT_NAME}" ${llvm_libs})

# Setup unit testing using Google Test (GTest) if applicable.
# This binds the CMakeLists.txt on the test directory.
option(IONSHARED_BUILD_TESTS "Build tests" OFF)

if(IONSHARED_BUILD_TESTS)
    add_subdirectory(./libs/googletest)
    add_subdirectory(./test)
endif()

# Setup install target.
install(
    TARGETS "${PROJECT_NAME}"
    EXPORT ${PROJECT_NAME}-config LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR} # Destination is relative to ${CMAKE_INSTALL_PREFIX}.
)

install(
    EXPORT ${PROJECT_NAME}-config
#    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
    DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    FILES_MATCHING PATTERN "*.h" PATTERN "LICENSE" # Match only header files & LICENSE file.
)

# Support for CLion install target.
add_custom_target(
    install_${PROJECT_NAME}
    "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install
    DEPENDS ${PROJECT_NAME}
    COMMENT "Installing ${PROJECT_NAME}"
)
