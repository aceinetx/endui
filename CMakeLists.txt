cmake_minimum_required(VERSION 3.20)
project(endui)

# setup stuff
add_subdirectory("lib/dobby")
include_directories("include" "include/ezheap" "include/apps" "lib/dobby/include")
link_directories("lib/x86" "lib/armv7")

find_package(Curses)
if(NOT Curses_FOUND)
  message(SEND_ERROR "Could not find curses")
endif()

set(ENDUI_HOOK_LIB "dobby")

# compile endui
set(SOURCES "src/endui.c" "src/window.c" "src/vec.c" "src/drawing.c" "src/keyboard.c" "src/ezheap/ezheap.c" "src/segcatch.c" "src/endfs.c" "src/virtual_desktop.c")

add_executable("endui" ${SOURCES})
target_compile_definitions("endui" PUBLIC NCURSES_WIDECHAR=1)
target_link_libraries("endui" "ncurses" ${ENDUI_HOOK_LIB})

# compile apps
add_library("everything" SHARED "src/apps/everything.c" "src/apps/settings.c" "src/apps/endbar.c" "src/endapi.c" "src/window.c" "src/endfs.c")
target_link_libraries("everything" "ncurses" ${ENDUI_HOOK_LIB})
target_compile_definitions("everything" PUBLIC ${ENDUI_DEFS})
