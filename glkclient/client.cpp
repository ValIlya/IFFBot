#include <stdio.h>
#include <stdexcept>
#include <string>
#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

#include "glk.h"
#include "glkstart.h"
#include "gi_blorb.h"

#ifdef __cplusplus
}
#endif

glkunix_argumentlist_t glkunix_arguments[] = {
    {const_cast<char *>(""), glkunix_arg_ValueFollows, const_cast<char *>("filename: The game file to load.")},
    {NULL, glkunix_arg_End, NULL}};

int glkunix_startup_code(glkunix_startup_t *data)
{

    auto game = const_cast<char *>("");
    if (data->argc == 2)
    {
        game = const_cast<char *>(data->argv[1]);
    }
    else
    {
        printf("No file specified");
        return false;
    }
    {
        giblorb_map_t *basemap;

        auto file = glkunix_stream_open_pathname(game, 1, 0);

        if (!file)
        {
            printf("Unable to open file");
            return false;
        }

        if (giblorb_create_map(file, &basemap) != giblorb_err_None)
        {
            printf("Does not appear to be a valid Blorb file");
            return false;
        }

        return true;
    }
    return TRUE;
}

void glk_main()
{
    glui32 res = glk_gestalt(gestalt_Unicode, 0);
    res *= glk_gestalt(gestalt_DateTime, 0);
    if (res == 0)
    {
        glk_exit();
    }

    winid_t mainwin = glk_window_open(0, 0, 0, wintype_TextBuffer, 1);

    glk_set_window(mainwin);
    glk_put_string("Hello, world!\n");
    glk_put_string("Type 'quit' to exit.\n");

    
    char commandbuf[256];
    int gotline;
    event_t ev;

    glk_put_string(strdup("\n> "));
    glk_request_line_event(mainwin, commandbuf, 255, 0);

    gotline = 0;
    while (!gotline)
    {
        glk_select(&ev);
        if (ev.type == evtype_LineInput && ev.win == mainwin)
        {
            gotline = 1;
        }
    }
}
