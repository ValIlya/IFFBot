set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )

# cheapglk
file(GLOB_RECURSE SRC_FILES 
"cheapglk/cgfref.c"
"cheapglk/cggestal.c"
"cheapglk/cgmisc.c"
"cheapglk/cgstream.c"
"cheapglk/cgstyle.c"
"cheapglk/cgwindow.c"
"cheapglk/cgschan.c"
"cheapglk/cgdate.c"
"cheapglk/cgunicod.c" 
"cheapglk/main.c"
"cheapglk/gi_dispa.c"
"cheapglk/gi_blorb.c"
"cheapglk/gi_debug.c"
"cheapglk/cgblorb.c"
"cheapglk/glkstart.c"
)

add_library(glk ${SRC_FILES})
