# - Find SDL2 library and headers
# 
# Find module for SDL 2.0 (http://www.libsdl.org/).
# It defines the following variables:
#  SDL2_INCLUDE_DIRS - The location of the headers, e.g., SDL.h.
#  SDL2_LIBRARIES - The libraries to link against to use SDL2.
#  SDL2_FOUND - If false, do not try to use SDL2.
#  SDL2_VERSION_STRING - Human-readable string containing the version of SDL2.

#
# Also defined, but not for general use are:
#   SDL2_INCLUDE_DIR - The directory that contains SDL.h.
#   SDL2_LIBRARY - The location of the SDL2 library.
#

find_package(PkgConfig QUIET)
pkg_check_modules(PC_SDL2 QUIET sdl2)

find_path(SDL2_INCLUDE_DIR
  NAMES SDL.h
  HINTS
    ${PC_SDL2_INCLUDEDIR}
    ${PC_SDL2_INCLUDE_DIRS}
  PATH_SUFFIXES SDL2
)

find_library(SDL2_LIBRARY
  NAMES SDL2
  HINTS
    ${PC_SDL2_LIBDIR}
    ${PC_SDL2_LIBRARY_DIRS}
  PATH_SUFFIXES x64 x86
)

if(SDL2_INCLUDE_DIR AND EXISTS "${SDL2_INCLUDE_DIR}/SDL_version.h")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_MAJOR "${SDL2_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_MINOR "${SDL2_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_PATCH "${SDL2_VERSION_PATCH_LINE}")
  set(SDL2_VERSION_STRING ${SDL2_VERSION_MAJOR}.${SDL2_VERSION_MINOR}.${SDL2_VERSION_PATCH})
  unset(SDL2_VERSION_MAJOR_LINE)
  unset(SDL2_VERSION_MINOR_LINE)
  unset(SDL2_VERSION_PATCH_LINE)
  unset(SDL2_VERSION_MAJOR)
  unset(SDL2_VERSION_MINOR)
  unset(SDL2_VERSION_PATCH)
endif()

set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
set(SDL2_LIBRARIES ${SDL2_LIBRARY})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2
                                  REQUIRED_VARS SDL2_INCLUDE_DIR SDL2_LIBRARY
                                  VERSION_VAR SDL2_VERSION_STRING)

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)
