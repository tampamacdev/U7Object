cmake_minimum_required(VERSION 3.10)


message("cmake SocketCommunicationExample")

project(SocketCommunicationExample)

# Specify the C standard
set(CMAKE_C_STANDARD 99)

# MacOS specific cmake setup instructions
if(APPLE)
    if(NOT DEFINED ENV{BREW_PREFIX})
        message(FATAL_ERROR "The BREW_PREFIX environment variable is not set. Make sure to export the location of homebrew directory. Instructions are provided in the comments of the CMakeLists.txt file you are processing.")
    endif()
    set(BREW_PREFIX $ENV{BREW_PREFIX})
    # Make sure to export the location of homebrew directory.
    # For example if you cloned/installed homebrew in a directory named "github" you will
    # need to add the line below to your .zshrc file
    #   export BREW_PREFIX=~/PATH/TO/BREW/REPO/DIRECTORY
    # A typical BREW_PREFIX path would look like this
    #   export BREW_PREFIX=~/github/brew
    # 

    # Find all subdirectories within the json-glib Cellar path
    file(GLOB JSON_GLIB_VERSIONS "${BREW_PREFIX}/Cellar/json-glib/*")

    # Get the latest or highest version from the list
    list(SORT JSON_GLIB_VERSIONS)
    list(GET JSON_GLIB_VERSIONS -1 JSON_GLIB_LATEST)

    # Set the appropriate library path
    link_directories(${JSON_GLIB_LATEST}/lib)
    
endif()

# Windows-specific OpenSSL paths
if(WIN32)
    set(OPENSSL_ROOT_DIR "C:/Dev/vcpkg/installed/x64-windows")
    set(OPENSSL_INCLUDE_DIR "C:/Dev/vcpkg/installed/x64-windows/include")
    set(OPENSSL_CRYPTO_LIBRARY "C:/Dev/vcpkg/installed/x64-windows/lib/libcrypto.lib")
    set(OPENSSL_SSL_LIBRARY "C:/Dev/vcpkg/installed/x64-windows/lib/libssl.lib")
endif()


message(STATUS "GLib library dirs: ${GLIB_LIBRARY_DIRS}")


# Find OpenSSL (required on all platforms)
find_package(OpenSSL REQUIRED)

message(STATUS "checking for PkgConfig")


# On Windows, make PkgConfig optional and use fallback; on others, require it
if(WIN32)
    find_package(PkgConfig QUIET)  # Optional on Windows
else()
    find_package(PkgConfig REQUIRED)  # Required on macOS/Ubuntu
endif()

message(STATUS "PKG_CONFIG_FOUND: ${PKG_CONFIG_FOUND}")

# Try pkg-config first if available
if(PKG_CONFIG_FOUND)
    pkg_check_modules(GLIB QUIET glib-2.0)
    pkg_check_modules(JSONGLIB QUIET json-glib-1.0)
endif()


# Windows-specific fallback if pkg-config isn’t found or fails
if(WIN32 AND (NOT PKG_CONFIG_FOUND OR NOT GLIB_FOUND OR NOT JSONGLIB_FOUND))


    message(STATUS "Windows Config")
    set(CMAKE_TOOLCHAIN_FILE "C:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

    # Reset variables if pkg-config didn't work
    unset(GLIB_FOUND CACHE)
    unset(JSONGLIB_FOUND CACHE)

    # Manual paths for vcpkg on Windows
    find_library(GLIB_LIBRARY NAMES libglib-2.0 glib-2.0 PATHS "C:/Dev/vcpkg/installed/x64-windows/lib")
    find_library(JSONGLIB_LIBRARY NAMES libjson-glib-1.0 json-glib-1.0 PATHS "C:/Dev/vcpkg/installed/x64-windows/lib")
    find_path(GLIB_INCLUDE_DIR glib.h PATHS "C:/Dev/vcpkg/installed/x64-windows/include/glib-2.0")
    find_path(GLIB_CONFIG_INCLUDE_DIR glibconfig.h PATHS "C:/Dev/vcpkg/installed/x64-windows/lib/glib-2.0/include")
    find_path(JSONGLIB_INCLUDE_DIR json-glib/json-glib.h PATHS "C:/Dev/vcpkg/installed/x64-windows/include/json-glib-1.0")

    # Check if found
    if(GLIB_LIBRARY AND GLIB_INCLUDE_DIR AND GLIB_CONFIG_INCLUDE_DIR)
        set(GLIB_FOUND TRUE)
        set(GLIB_LIBRARIES ${GLIB_LIBRARY})
        set(GLIB_INCLUDE_DIRS ${GLIB_INCLUDE_DIR} ${GLIB_CONFIG_INCLUDE_DIR})
    endif()
    if(JSONGLIB_LIBRARY AND JSONGLIB_INCLUDE_DIR)
        set(JSONGLIB_FOUND TRUE)
        set(JSONGLIB_LIBRARIES ${JSONGLIB_LIBRARY})
        set(JSONGLIB_INCLUDE_DIRS ${JSONGLIB_INCLUDE_DIR})
    endif()


endif()


# Ensure libraries are found on all platforms
if(NOT GLIB_FOUND)
    message(FATAL_ERROR "GLib not found. Ensure it’s installed (e.g., via Homebrew on macOS, apt on Ubuntu, vcpkg on Windows).")
endif()
if(NOT JSONGLIB_FOUND)
    message(FATAL_ERROR "JSON-GLib not found. Ensure it’s installed (e.g., via Homebrew on macOS, apt on Ubuntu, vcpkg on Windows).")
endif()

# Helper function to link a target with GLib and JSON-GLib
function(link_libraries_with_deps target)
    target_link_libraries(${target} PRIVATE 
        $<$<PLATFORM_ID:Windows>:ws2_32>  # Windows socket library
        $<$<NOT:$<PLATFORM_ID:Windows>>:m>  # Math library only on non-Windows (e.g., macOS, Ubuntu)
        ${GLIB_LIBRARIES} 
        ${JSONGLIB_LIBRARIES}
        OpenSSL::Crypto 
        OpenSSL::SSL
    )
    target_include_directories(${target} PRIVATE ${GLIB_INCLUDE_DIRS} ${JSONGLIB_INCLUDE_DIRS})
    if(PKG_CONFIG_FOUND)
        target_compile_options(${target} PRIVATE ${GLIB_CFLAGS_OTHER} ${JSONGLIB_CFLAGS_OTHER})
    endif()
endfunction()

include_directories(${GLIB_INCLUDE_DIRS} ${JSON_GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS} ${JSON_GLIB_LIBRARY_DIRS})

# Add executable for endpoint
add_executable(endpoint endpoint.c websocketendpoint.c mongoose.c u7json.c u7mainloop.c u7glib.c u7encryption.c u7array.c u7string.c u7object.c u7websocketconnection.c mongoose_extras.c u7dictionary.c u7date.c u7data.c u7thread.c u7autoreleasepool.c u7actionqueue.c)
link_libraries_with_deps(endpoint)


message(STATUS "GLib library dirs: ${GLIB_LIBRARY_DIRS}")
message(STATUS "JSON-GLib library dirs: ${JSONGLIB_LIBRARY_DIRS}")
message(STATUS "Linker flags for JSON-GLib: ${JSONGLIB_LIBRARIES}")



