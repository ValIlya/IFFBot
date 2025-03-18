#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glk.h"
#include "tglk.h"


int main(int argc, char *argv[])
{
    
    glk_main();
    glk_exit();
    
    /* glk_exit() doesn't return, but the compiler may kvetch if main()
        doesn't seem to return a value. */
    return 0;
}


void glk_exit()
{
    exit(0);
}


void glk_set_interrupt_handler(void (*func)(void))
{
    /* This library doesn't understand interrupts. */
}

unsigned char glk_char_to_lower(unsigned char ch)
{
    return ch;
}

unsigned char glk_char_to_upper(unsigned char ch)
{
    return ch;
}

void glk_select(event_t *event)
{
    
}

void glk_select_poll(event_t *event)
{
    /* Do nothing. */
}

void glk_tick()
{
    /* Do nothing. */
}

void glk_request_timer_events(glui32 millisecs)
{
    /* Don't make me laugh. */
}


winid_t glk_window_open(winid_t split, glui32 method, glui32 size, 
    glui32 wintype, glui32 rock)
{
    return NULL;
}

void glk_window_close(winid_t win, stream_result_t *result)
{
    
}
void glk_window_get_size(winid_t win, glui32 *widthptr,
    glui32 *heightptr)
    {

};
void glk_window_set_arrangement(winid_t win, glui32 method, glui32 size, winid_t keywin){};
void glk_window_get_arrangement(winid_t win, glui32 *methodptr, glui32 *sizeptr, winid_t *keywinptr){};
winid_t glk_window_iterate(winid_t win, glui32 *rockptr) {return 0;};
glui32 glk_window_get_rock(winid_t win){return 0;};
glui32 glk_window_get_type(winid_t win) {return 0;};
winid_t glk_window_get_parent(winid_t win) {return win;};
winid_t glk_window_get_sibling(winid_t win) {return win;};
void glk_window_clear(winid_t win){};
void glk_window_move_cursor(winid_t win, glui32 xpos, glui32 ypos){};

strid_t glk_window_get_stream(winid_t win){return NULL;};
void glk_window_set_echo_stream(winid_t win, strid_t str){};
strid_t glk_window_get_echo_stream(winid_t win){return NULL;};
void glk_set_window(winid_t win){};


#ifdef GLK_MODULE_UNICODE

glui32 glk_buffer_to_lower_case_uni(glui32 *buf, glui32 len,
    glui32 numchars)
{
    return 0;
}

glui32 glk_buffer_to_upper_case_uni(glui32 *buf, glui32 len,
    glui32 numchars)
{
    return 0;
}

glui32 glk_buffer_to_title_case_uni(glui32 *buf, glui32 len,
    glui32 numchars, glui32 lowerrest)
{
    return 0;
}

void glk_put_char_uni(glui32 ch){};
void glk_put_string_uni(glui32 *s){};
void glk_put_buffer_uni(glui32 *buf, glui32 len){};
void glk_put_char_stream_uni(strid_t str, glui32 ch){};
void glk_put_string_stream_uni(strid_t str, glui32 *s){};
void glk_put_buffer_stream_uni(strid_t str, glui32 *buf, glui32 len){};

glsi32 glk_get_char_stream_uni(strid_t str){return 0;};
glui32 glk_get_buffer_stream_uni(strid_t str, glui32 *buf, glui32 len){return 0;};
glui32 glk_get_line_stream_uni(strid_t str, glui32 *buf, glui32 len){return 0;};

strid_t glk_stream_open_file_uni(frefid_t fileref, glui32 fmode,
    glui32 rock){return NULL;};
strid_t glk_stream_open_memory_uni(glui32 *buf, glui32 buflen,
    glui32 fmode, glui32 rock){return NULL;};

void glk_request_char_event_uni(winid_t win){};
void glk_request_line_event_uni(winid_t win, glui32 *buf,
    glui32 maxlen, glui32 initlen){};

#endif /* GLK_MODULE_UNICODE */



void glk_request_line_event(winid_t win, char *buf, glui32 maxlen,
    glui32 initlen) {};
void glk_request_char_event(winid_t win) {};
void glk_request_mouse_event(winid_t win) {};

void glk_cancel_line_event(winid_t win, event_t *event) {};
void glk_cancel_char_event(winid_t win) {};
void glk_cancel_mouse_event(winid_t win) {};

#ifdef GLK_MODULE_IMAGE

glui32 glk_image_draw(winid_t win, glui32 image, glsi32 val1, glsi32 val2)
{
    gli_strict_warning("image_draw: graphics not supported.");
    return FALSE;
}

glui32 glk_image_draw_scaled(winid_t win, glui32 image, 
    glsi32 val1, glsi32 val2, glui32 width, glui32 height)
{
    gli_strict_warning("image_draw_scaled: graphics not supported.");
    return FALSE;
}

glui32 glk_image_get_info(glui32 image, glui32 *width, glui32 *height)
{
    gli_strict_warning("image_get_info: graphics not supported.");
    return FALSE;
}

void glk_window_flow_break(winid_t win)
{
    gli_strict_warning("window_flow_break: graphics not supported.");
}

void glk_window_erase_rect(winid_t win, 
    glsi32 left, glsi32 top, glui32 width, glui32 height)
{
    gli_strict_warning("window_erase_rect: graphics not supported.");
}

void glk_window_fill_rect(winid_t win, glui32 color, 
    glsi32 left, glsi32 top, glui32 width, glui32 height)
{
    gli_strict_warning("window_fill_rect: graphics not supported.");
}

void glk_window_set_background_color(winid_t win, glui32 color)
{
    gli_strict_warning("window_set_background_color: graphics not supported.");
}

#endif /* GLK_MODULE_IMAGE */

#ifdef GLK_MODULE_LINE_ECHO

void glk_set_echo_line_event(winid_t win, glui32 val)
{
    gli_strict_warning("set_echo_line_event: not supported.");
}

#endif /* GLK_MODULE_LINE_ECHO */

#ifdef GLK_MODULE_LINE_TERMINATORS

void glk_set_terminators_line_event(winid_t win, glui32 *keycodes, 
    glui32 count)
{
    gli_strict_warning("set_terminators_line_event: not supported.");
}

#endif /* GLK_MODULE_LINE_TERMINATORS */


#ifdef GLK_MODULE_UNICODE_NORM

glui32 glk_buffer_canon_decompose_uni(glui32 *buf, glui32 len,
    glui32 numchars)
{
    return numchars;
}

glui32 glk_buffer_canon_normalize_uni(glui32 *buf, glui32 len,
    glui32 numchars)
{
    
    return numchars;
}

#endif /* GLK_MODULE_UNICODE_NORM */

#ifdef GLK_MODULE_HYPERLINKS

void glk_set_hyperlink(glui32 linkval)
{
    gli_strict_warning("set_hyperlink: hyperlinks not supported.");
}

void glk_set_hyperlink_stream(strid_t str, glui32 linkval)
{
    gli_strict_warning("set_hyperlink_stream: hyperlinks not supported.");
}

void glk_request_hyperlink_event(winid_t win)
{
    gli_strict_warning("request_hyperlink_event: hyperlinks not supported.");
}

void glk_cancel_hyperlink_event(winid_t win)
{
    gli_strict_warning("cancel_hyperlink_event: hyperlinks not supported.");
}

#endif /* GLK_MODULE_HYPERLINKS */

#ifdef GLK_MODULE_RESOURCE_STREAM

strid_t glk_stream_open_resource(glui32 filenum, glui32 rock) {return 0;};
strid_t glk_stream_open_resource_uni(glui32 filenum, glui32 rock) {return 0;};

#endif /* GLK_MODULE_RESOURCE_STREAM */


winid_t glk_window_get_root()
{
    return NULL;
}
