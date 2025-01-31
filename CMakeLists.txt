cmake_minimum_required(VERSION 3.8)
project(endui)

# setup stuff
include_directories("include" "include/ezheap" "include/apps")
link_directories("lib/x86" "lib/armv7")

find_package(Curses)
if(NOT Curses_FOUND)
  message(SEND_ERROR "Could not find curses")
endif()

# compile endui
set(SOURCES "src/endui.c" "src/window.c" "src/vec.c" "src/drawing.c" "src/keyboard.c" "src/ezheap/ezheap.c" "src/segcatch.c" "src/endfs.c" "src/virtual_desktop.c")

add_executable("endui" ${SOURCES})
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86" OR CMAKE_SYSTEM_PROCESSOR MATCHES "i386" OR CMAKE_SYSTEM_PROCESSOR MATCHES "i686" OR CMAKE_SYSTEM_PROCESSOR MATCHES "amd64")
		# x86 based
		set(ENDUI_DEFS "ENDUI_X86")
		set(ENDUI_HOOK_LIB "libmem")
		target_compile_definitions("endui" PUBLIC ${ENDUI_DEFS})
		target_link_libraries("endui" "ncurses" ${ENDUI_HOOK_LIB})
		message(STATUS "Detected an x86 machine")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
		# arm based
		set(ENDUI_DEFS "ENDUI_ARM")
		set(ENDUI_HOOK_LIB "dobby")
		target_link_libraries("endui" "ncurses" ${ENDUI_HOOK_LIB})
		target_compile_definitions("endui" PUBLIC ${ENDUI_DEFS})
		message(STATUS "Detected an ARM machine")
else()
	message(FATAL_ERROR "Unknown architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

target_compile_definitions("endui" PUBLIC NCURSES_WIDECHAR=1)

# compile apps
add_library("everything" SHARED "src/apps/everything.c" "src/apps/settings.c" "src/apps/endbar.c" "src/endapi.c" "src/window.c" "src/endfs.c")
target_link_libraries("everything" "ncurses" ${ENDUI_HOOK_LIB})
target_compile_definitions("everything" PUBLIC ${ENDUI_DEFS})
