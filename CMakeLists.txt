cmake_minimum_required(VERSION 3.20)
project(endui)

# setup stuff
include_directories("include" "include/ezheap" "include/apps")
link_directories("lib/x86" "lib/armv7")

find_package(Curses)
if(NOT Curses_FOUND)
  message(SEND_ERROR "Could not find curses")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86" OR CMAKE_SYSTEM_PROCESSOR MATCHES "i386" OR CMAKE_SYSTEM_PROCESSOR MATCHES "i686" OR CMAKE_SYSTEM_PROCESSOR MATCHES "amd64")
	set(ENDUI_DEFS "YHOOK_X64")
	message(STATUS "Detected an x86 (x64) machine")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
	set(ENDUI_DEFS "YHOOK_ARM")
	message(STATUS "Detected an ARM machine")
else()
	message(FATAL_ERROR "Unknown architecture")
endif()

# compile endui
set(SOURCES "src/endui.c" "src/ezheap/ezheap.c" "src/segcatch.c")
set(LIB_SOURCES "src/endlib.c" "src/window.c" "src/vec.c" "src/drawing.c" "src/keyboard.c" "src/ezheap/ezheap.c" "src/endfs.c" "src/virtual_desktop.c")

add_library("endlib" SHARED ${LIB_SOURCES})
set_target_properties("endlib" PROPERTIES OUTPUT_NAME "endui")
target_link_libraries("endlib" "ncurses")

add_executable("endui" ${SOURCES})
target_compile_definitions("endui" PUBLIC NCURSES_WIDECHAR=1 ${ENDUI_DEFS})
target_link_libraries("endui" "ncurses" "endlib")

# compile apps
add_library("everything" SHARED "src/apps/everything.c" "src/apps/settings.c" "src/apps/endbar.c" "src/window.c" "src/endfs.c")
target_link_libraries("everything" "ncurses")
target_compile_definitions("everything" PUBLIC ${ENDUI_DEFS})
