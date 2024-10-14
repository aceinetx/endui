cmake_minimum_required(VERSION 3.8)
project(endui)

# setup stuff
include_directories("include" "include/ezheap")
link_directories("lib")

find_package(Curses)
if(NOT Curses_FOUND)
  message(SEND_ERROR "Could not find curses")
endif()

# compile endui
set(SOURCES "src/endui.c" "src/window.c" "src/vec.c" "src/drawing.c" "src/keyboard.c" "src/ezheap/ezheap.c" "src/segcatch.c" "src/endfs.c")

add_executable("endui" ${SOURCES})
target_link_libraries("endui" "ncurses" "libmem") # if you don't have a x86_64 machine, you'll have to compile libmem yourself
target_compile_definitions("endui" PUBLIC NCURSES_WIDECHAR=1)

# compile apps
add_library("endbar" SHARED "src/apps/endbar.c" "src/endapi.c" "src/window.c")
add_library("settings" SHARED "src/apps/settings.c" "src/endapi.c" "src/window.c" "src/endfs.c")