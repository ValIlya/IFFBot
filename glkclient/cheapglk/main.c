#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glk.h"
#include "gi_debug.h"
#include "cheapglk.h"
#include "glkstart.h"

int gli_screenwidth = 80;
int gli_screenheight = 24; 
int gli_utf8output = FALSE;
int gli_utf8input = FALSE;
#if GIDEBUG_LIBRARY_SUPPORT
int gli_debugger = FALSE;
#endif /* GIDEBUG_LIBRARY_SUPPORT */

typedef struct dataresource_struct {
    int num;
    int isbinary;
    char *pathname;
    int len;
    void *ptr;
} dataresource_t;
static dataresource_t *dataresources = NULL;
static int numdataresources = 0;

/* Get the data for data chunk num (as specified in command-line arguments,
   if any).
   The data is read from the given pathname and stashed in memory.
   This is memory-hoggish, but so is the rest of glk_stream_open_resource();
   see comments there.
   (You might wonder why we don't call gli_stream_open_pathname() and
   handle the file as a file-based stream. Turns out that doesn't work;
   the handling of unicode streams is subtly different for resource
   streams and the file-based code won't work. Oh well.)
*/
int gli_get_dataresource_info(int num, void **ptr, glui32 *len, int *isbinary)
{
    int ix;
    /* The dataresources array isn't sorted (or even checked for duplicates),
       so we search it linearly. There probably aren't a lot of entries. */
    for (ix=0; ix<numdataresources; ix++) {
        if (dataresources[ix].num == num) {
            *isbinary = dataresources[ix].isbinary;
            *ptr = NULL;
            *len = 0;
            if (dataresources[ix].ptr) {
                /* Already loaded. */
            }
            else {
                FILE *fl = fopen(dataresources[ix].pathname, "rb");
                if (!fl) {
                    gli_strict_warning("stream_open_resource: unable to read given pathname.");
                    return FALSE;
                }
                fseek(fl, 0, SEEK_END);
                dataresources[ix].len = ftell(fl);
                dataresources[ix].ptr = malloc(dataresources[ix].len+1);
                fseek(fl, 0, SEEK_SET);
                int got = fread(dataresources[ix].ptr, 1, dataresources[ix].len, fl);
                fclose(fl);
                if (got != dataresources[ix].len) {
                    gli_strict_warning("stream_open_resource: unable to read all resource data.");
                    return FALSE;
                }
            }
            *ptr = dataresources[ix].ptr;
            *len = dataresources[ix].len;
            return TRUE;
        }
    }

    return FALSE;
}

/* This opens a file for reading or writing. (You cannot open a file
   for appending using this call.)

   This should be used only by glkunix_startup_code(). 
*/
strid_t glkunix_stream_open_pathname_gen(char *pathname, glui32 writemode,
    glui32 textmode, glui32 rock)
{
    return gli_stream_open_pathname(pathname, (writemode != 0), (textmode != 0), rock);
}

/* This opens a file for reading. It is a less-general form of 
   glkunix_stream_open_pathname_gen(), preserved for backwards 
   compatibility.

   This should be used only by glkunix_startup_code().
*/
strid_t glkunix_stream_open_pathname(char *pathname, glui32 textmode, 
    glui32 rock)
{
    return gli_stream_open_pathname(pathname, FALSE, (textmode != 0), rock);
}
