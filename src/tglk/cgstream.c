#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glk.h"
#include "tglk.h"
#include "gi_dispa.h"

strid_t glk_stream_open_file(frefid_t fileref, glui32 fmode,
    glui32 rock) {return NULL;};
strid_t glk_stream_open_memory(char *buf, glui32 buflen, glui32 fmode,
    glui32 rock) {return NULL;};

void glk_stream_close(strid_t str, stream_result_t *result)
{
    
}

strid_t glk_stream_iterate(strid_t str, glui32 *rock)
{
    return NULL;
}


glui32 glk_stream_get_rock(strid_t str) {return 0;};
void glk_stream_set_position(strid_t str, glsi32 pos, glui32 seekmode){};
glui32 glk_stream_get_position(strid_t str) {return 0;};
void glk_stream_set_current(strid_t str){};
strid_t glk_stream_get_current()
{
    return NULL;
}


void glk_put_char(unsigned char ch) {};
void glk_put_char_stream(strid_t str, unsigned char ch) {};
void glk_put_string(char *s) {};
void glk_put_string_stream(strid_t str, char *s) {};
void glk_put_buffer(char *buf, glui32 len) {};
void glk_put_buffer_stream(strid_t str, char *buf, glui32 len) {};
void glk_set_style(glui32 styl) {};
void glk_set_style_stream(strid_t str, glui32 styl) {};

glsi32 glk_get_char_stream(strid_t str) {return 0;};
glui32 glk_get_line_stream(strid_t str, char *buf, glui32 len) {return 0;};
glui32 glk_get_buffer_stream(strid_t str, char *buf, glui32 len) {return 0;};


static stream_t *gli_streamlist = NULL; /* linked list of all streams */
static stream_t *gli_currentstr = NULL; /* the current output stream */



gidispatch_rock_t (*gli_register_obj)(void *obj, glui32 objclass) = NULL;
void (*gli_unregister_obj)(void *obj, glui32 objclass, 
    gidispatch_rock_t objrock) = NULL;
gidispatch_rock_t (*gli_register_arr)(void *array, glui32 len, 
    char *typecode) = NULL;
void (*gli_unregister_arr)(void *array, glui32 len, char *typecode, 
    gidispatch_rock_t objrock) = NULL;


stream_t *gli_new_stream(int type, int readable, int writable, 
    glui32 rock)
{
    stream_t *str = (stream_t *)malloc(sizeof(stream_t));
    if (!str)
        return NULL;
    
    str->magicnum = MAGIC_STREAM_NUM;
    str->type = type;
    str->rock = rock;

    str->unicode = FALSE;
    str->isbinary = FALSE;
    
    str->win = NULL;
    str->file = NULL;
    str->lastop = 0;
    str->buf = NULL;
    str->bufptr = NULL;
    str->bufend = NULL;
    str->bufeof = NULL;
    str->ubuf = NULL;
    str->ubufptr = NULL;
    str->ubufend = NULL;
    str->ubufeof = NULL;
    str->buflen = 0;
    
    str->readcount = 0;
    str->writecount = 0;
    str->readable = readable;
    str->writable = writable;
    
    str->prev = NULL;
    str->next = gli_streamlist;
    gli_streamlist = str;
    if (str->next) {
        str->next->prev = str;
    }
    
    if (gli_register_obj)
        str->disprock = (*gli_register_obj)(str, gidisp_Class_Stream);
    else
        str->disprock.ptr = NULL;
    
    return str;
}

void gli_delete_stream(stream_t *str)
{
    window_t *win;
    stream_t *prev, *next;
    
    if (str == gli_currentstr) {
        gli_currentstr = NULL;
    }
    
    str->magicnum = 0;

    switch (str->type) {
        case strtype_Window:
            /* nothing necessary; the window is already being closed */
            break;
        case strtype_Memory: 
            if (gli_unregister_arr) {
                /* This could be a char array or a glui32 array. */
                char *typedesc = (str->unicode ? "&+#!Iu" : "&+#!Cn");
                void *buf = (str->unicode ? (void*)str->ubuf : (void*)str->buf);
                (*gli_unregister_arr)(buf, str->buflen, typedesc,
                    str->arrayrock);
            }
            break;
        case strtype_Resource: 
            /* nothing necessary; the array belongs to gi_blorb.c. */
            break;
        case strtype_File:
            /* close the FILE */
            fclose(str->file);
            str->file = NULL;
            str->lastop = 0;
            break;
    }

    if (gli_unregister_obj) {
        (*gli_unregister_obj)(str, gidisp_Class_Stream, str->disprock);
        str->disprock.ptr = NULL;
    }
    
    prev = str->prev;
    next = str->next;
    str->prev = NULL;
    str->next = NULL;

    if (prev)
        prev->next = next;
    else
        gli_streamlist = next;
    if (next)
        next->prev = prev;
    
    free(str);
}


strid_t gli_stream_open_pathname(char *pathname, int writemode, 
    int textmode, glui32 rock)
{
    char modestr[16];
    stream_t *str;
    FILE *fl;

    if (!writemode)
        strcpy(modestr, "r");
    else
        strcpy(modestr, "w");
    if (!textmode)
        strcat(modestr, "b");
        
    fl = fopen(pathname, modestr);
    if (!fl) {
        return NULL;
    }

    str = gli_new_stream(strtype_File, 
        !writemode, writemode, rock);
    if (!str) {
        fclose(fl);
        return NULL;
    }
    
    str->isbinary = !textmode;
    str->file = fl;
    str->lastop = 0;
    
    return str;
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
