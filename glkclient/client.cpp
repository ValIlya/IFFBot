#include <stdio.h>
#include <stdexcept>
#include <string>

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
    { NULL, glkunix_arg_End }
};

int glkunix_startup_code(glkunix_startup_t *data)
{
    auto game = const_cast<char *>("../stories/LostPig.zblorb");

    {
        giblorb_map_t *basemap;

        auto file = glkunix_stream_open_pathname(game, 1, 0);

        if (!file) {
            printf("Unable to open file");
            return false;
        }

        if (giblorb_create_map(file, &basemap) != giblorb_err_None) {
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
    if (res == 0) {
        glk_exit();
    }

    event_t ev;
    while (1) {
        glk_select(&ev);
        switch (ev.type) {
            default:
                /* do nothing */
                break;
        }
    }
}
