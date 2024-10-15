cmake_minimum_required(VERSION 3.8)
project(endui)

# setup stuff
include_directories("include" "include/ezheap" "include/apps")
link_directories("lib")

find_package(Curses)
if(NOT Curses_FOUND)
  message(SEND_ERROR "Could not find curses")
endif()

# compile endui
set(SOURCES "src/endui.c" "src/window.c" "src/vec.c" "src/drawing.c" "src/keyboard.c" "src/ezheap/ezheap.c" "src/segcatch.c" "src/endfs.c" "src/virtual_desktop.c")

add_executable("endui" ${SOURCES})
target_link_libraries("endui" "ncurses" "libmem") # if you don't have a x86_64 machine, you'll have to compile libmem yourself
target_compile_definitions("endui" PUBLIC NCURSES_WIDECHAR=1)

# compile apps
add_library("everything" SHARED "src/apps/everything.c" "src/apps/settings.c" "src/apps/endbar.c" "src/endapi.c" "src/window.c" "src/endfs.c")
target_link_libraries("everything" "libmem")