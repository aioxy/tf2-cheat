
#ifndef NK_SINGLE_FILE
  #define NK_SINGLE_FILE
#endif

#ifndef NK_NUKLEAR_H_
#define NK_NUKLEAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define NK_UNDEFINED (-1.0f)
#define NK_UTF_INVALID 0xFFFD
#define NK_UTF_SIZE 4
#ifndef NK_INPUT_MAX
  #define NK_INPUT_MAX 16
#endif
#ifndef NK_MAX_NUMBER_BUFFER
  #define NK_MAX_NUMBER_BUFFER 64
#endif
#ifndef NK_SCROLLBAR_HIDING_TIMEOUT
  #define NK_SCROLLBAR_HIDING_TIMEOUT 4.0f
#endif

#ifndef NK_API
  #ifdef NK_PRIVATE
    #if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L))
      #define NK_API static inline
    #elif defined(__cplusplus)
      #define NK_API static inline
    #else
      #define NK_API static
    #endif
  #else
    #define NK_API extern
  #endif
#endif
#ifndef NK_LIB
  #ifdef NK_SINGLE_FILE
    #define NK_LIB static
  #else
    #define NK_LIB extern
  #endif
#endif

#define NK_INTERN static
#define NK_STORAGE static
#define NK_GLOBAL static

#define NK_FLAG(x) (1 << (x))
#define NK_STRINGIFY(x) #x
#define NK_MACRO_STRINGIFY(x) NK_STRINGIFY(x)
#define NK_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2
#define NK_STRING_JOIN_DELAY(arg1, arg2) NK_STRING_JOIN_IMMEDIATE(arg1, arg2)
#define NK_STRING_JOIN(arg1, arg2) NK_STRING_JOIN_DELAY(arg1, arg2)

#ifdef _MSC_VER
  #define NK_UNIQUE_NAME(name) NK_STRING_JOIN(name,__COUNTER__)
#else
  #define NK_UNIQUE_NAME(name) NK_STRING_JOIN(name,__LINE__)
#endif

#ifndef NK_STATIC_ASSERT
  #define NK_STATIC_ASSERT(exp) typedef char NK_UNIQUE_NAME(_dummy_array)[(exp)?1:-1]
#endif

#ifndef NK_FILE_LINE
#ifdef _MSC_VER
  #define NK_FILE_LINE __FILE__ ":" NK_MACRO_STRINGIFY(__COUNTER__)
#else
  #define NK_FILE_LINE __FILE__ ":" NK_MACRO_STRINGIFY(__LINE__)
#endif
#endif

#define NK_MIN(a,b) ((a) < (b) ? (a) : (b))
#define NK_MAX(a,b) ((a) < (b) ? (b) : (a))
#define NK_CLAMP(i,v,x) (NK_MAX(NK_MIN(v,x), i))

#ifdef NK_INCLUDE_STANDARD_VARARGS
  #include <stdarg.h>
  #if defined(_MSC_VER) && (_MSC_VER >= 1600)
    #include <sal.h>
    #define NK_PRINTF_FORMAT_STRING _Printf_format_string_
  #else
    #define NK_PRINTF_FORMAT_STRING
  #endif
  #if defined(__GNUC__)
    #define NK_PRINTF_VARARG_FUNC(fmtargnumber) __attribute__((format(__printf__, fmtargnumber, fmtargnumber+1)))
    #define NK_PRINTF_VALIST_FUNC(fmtargnumber) __attribute__((format(__printf__, fmtargnumber, 0)))
  #else
    #define NK_PRINTF_VARARG_FUNC(fmtargnumber)
    #define NK_PRINTF_VALIST_FUNC(fmtargnumber)
  #endif
#endif

#ifdef NK_INCLUDE_FIXED_TYPES
 #include <stdint.h>
 #define NK_INT8 int8_t
 #define NK_UINT8 uint8_t
 #define NK_INT16 int16_t
 #define NK_UINT16 uint16_t
 #define NK_INT32 int32_t
 #define NK_UINT32 uint32_t
 #define NK_SIZE_TYPE uintptr_t
 #define NK_POINTER_TYPE uintptr_t
#else
  #ifndef NK_INT8
    #define NK_INT8 signed char
  #endif
  #ifndef NK_UINT8
    #define NK_UINT8 unsigned char
  #endif
  #ifndef NK_INT16
    #define NK_INT16 signed short
  #endif
  #ifndef NK_UINT16
    #define NK_UINT16 unsigned short
  #endif
  #ifndef NK_INT32
    #if defined(_MSC_VER)
      #define NK_INT32 __int32
    #else
      #define NK_INT32 signed int
    #endif
  #endif
  #ifndef NK_UINT32
    #if defined(_MSC_VER)
      #define NK_UINT32 unsigned __int32
    #else
      #define NK_UINT32 unsigned int
    #endif
  #endif
  #ifndef NK_SIZE_TYPE
    #if defined(_WIN64) && defined(_MSC_VER)
      #define NK_SIZE_TYPE unsigned __int64
    #elif (defined(_WIN32) || defined(WIN32)) && defined(_MSC_VER)
      #define NK_SIZE_TYPE unsigned __int32
    #elif defined(__GNUC__) || defined(__clang__)
      #if defined(__x86_64__) || defined(__ppc64__) || defined(__aarch64__)
        #define NK_SIZE_TYPE unsigned long
      #else
        #define NK_SIZE_TYPE unsigned int
      #endif
    #else
      #define NK_SIZE_TYPE unsigned long
    #endif
  #endif
  #ifndef NK_POINTER_TYPE
    #if defined(_WIN64) && defined(_MSC_VER)
      #define NK_POINTER_TYPE unsigned __int64
    #elif (defined(_WIN32) || defined(WIN32)) && defined(_MSC_VER)
      #define NK_POINTER_TYPE unsigned __int32
    #elif defined(__GNUC__) || defined(__clang__)
      #if defined(__x86_64__) || defined(__ppc64__) || defined(__aarch64__)
        #define NK_POINTER_TYPE unsigned long
      #else
        #define NK_POINTER_TYPE unsigned int
      #endif
    #else
      #define NK_POINTER_TYPE unsigned long
    #endif
  #endif
#endif

#ifndef NK_BOOL
  #ifdef NK_INCLUDE_STANDARD_BOOL
    #include <stdbool.h>
    #define NK_BOOL bool
  #else
    #define NK_BOOL int
  #endif
#endif

typedef NK_INT8 nk_char;
typedef NK_UINT8 nk_uchar;
typedef NK_UINT8 nk_byte;
typedef NK_INT16 nk_short;
typedef NK_UINT16 nk_ushort;
typedef NK_INT32 nk_int;
typedef NK_UINT32 nk_uint;
typedef NK_SIZE_TYPE nk_size;
typedef NK_POINTER_TYPE nk_ptr;
typedef NK_BOOL nk_bool;

typedef nk_uint nk_hash;
typedef nk_uint nk_flags;
typedef nk_uint nk_rune;

NK_STATIC_ASSERT(sizeof(nk_short) == 2);
NK_STATIC_ASSERT(sizeof(nk_ushort) == 2);
NK_STATIC_ASSERT(sizeof(nk_uint) == 4);
NK_STATIC_ASSERT(sizeof(nk_int) == 4);
NK_STATIC_ASSERT(sizeof(nk_byte) == 1);
NK_STATIC_ASSERT(sizeof(nk_flags) >= 4);
NK_STATIC_ASSERT(sizeof(nk_rune) >= 4);
NK_STATIC_ASSERT(sizeof(nk_size) >= sizeof(void*));
NK_STATIC_ASSERT(sizeof(nk_ptr) >= sizeof(void*));
#ifdef NK_INCLUDE_STANDARD_BOOL
NK_STATIC_ASSERT(sizeof(nk_bool) == sizeof(bool));
#else
NK_STATIC_ASSERT(sizeof(nk_bool) >= 2);
#endif

struct nk_buffer;
struct nk_allocator;
struct nk_command_buffer;
struct nk_draw_command;
struct nk_convert_config;
struct nk_style_item;
struct nk_text_edit;
struct nk_draw_list;
struct nk_user_font;
struct nk_panel;
struct nk_context;
struct nk_draw_vertex_layout_element;
struct nk_style_button;
struct nk_style_toggle;
struct nk_style_selectable;
struct nk_style_slide;
struct nk_style_progress;
struct nk_style_scrollbar;
struct nk_style_edit;
struct nk_style_property;
struct nk_style_chart;
struct nk_style_combo;
struct nk_style_tab;
struct nk_style_window_header;
struct nk_style_window;

enum {nk_false, nk_true};
struct nk_color {nk_byte r,g,b,a;};
struct nk_colorf {float r,g,b,a;};
struct nk_vec2 {float x,y;};
struct nk_vec2i {short x, y;};
struct nk_rect {float x,y,w,h;};
struct nk_recti {short x,y,w,h;};
typedef char nk_glyph[NK_UTF_SIZE];
typedef union {void *ptr; int id;} nk_handle;
struct nk_image {nk_handle handle; nk_ushort w, h; nk_ushort region[4];};
struct nk_nine_slice {struct nk_image img; nk_ushort l, t, r, b;};
struct nk_cursor {struct nk_image img; struct nk_vec2 size, offset;};
struct nk_scroll {nk_uint x, y;};

enum nk_heading         {NK_UP, NK_RIGHT, NK_DOWN, NK_LEFT};
enum nk_button_behavior {NK_BUTTON_DEFAULT, NK_BUTTON_REPEATER};
enum nk_modify          {NK_FIXED = nk_false, NK_MODIFIABLE = nk_true};
enum nk_orientation     {NK_VERTICAL, NK_HORIZONTAL};
enum nk_collapse_states {NK_MINIMIZED = nk_false, NK_MAXIMIZED = nk_true};
enum nk_show_states     {NK_HIDDEN = nk_false, NK_SHOWN = nk_true};
enum nk_chart_type      {NK_CHART_LINES, NK_CHART_COLUMN, NK_CHART_MAX};
enum nk_chart_event     {NK_CHART_HOVERING = 0x01, NK_CHART_CLICKED = 0x02};
enum nk_color_format    {NK_RGB, NK_RGBA};
enum nk_popup_type      {NK_POPUP_STATIC, NK_POPUP_DYNAMIC};
enum nk_layout_format   {NK_DYNAMIC, NK_STATIC};
enum nk_tree_type       {NK_TREE_NODE, NK_TREE_TAB};

typedef void*(*nk_plugin_alloc)(nk_handle, void *old, nk_size);
typedef void (*nk_plugin_free)(nk_handle, void *old);
typedef nk_bool(*nk_plugin_filter)(const struct nk_text_edit*, nk_rune unicode);
typedef void(*nk_plugin_paste)(nk_handle, struct nk_text_edit*);
typedef void(*nk_plugin_copy)(nk_handle, const char*, int len);

struct nk_allocator {
    nk_handle userdata;
    nk_plugin_alloc alloc;
    nk_plugin_free free;
};
enum nk_symbol_type {
    NK_SYMBOL_NONE,
    NK_SYMBOL_X,
    NK_SYMBOL_UNDERSCORE,
    NK_SYMBOL_CIRCLE_SOLID,
    NK_SYMBOL_CIRCLE_OUTLINE,
    NK_SYMBOL_RECT_SOLID,
    NK_SYMBOL_RECT_OUTLINE,
    NK_SYMBOL_TRIANGLE_UP,
    NK_SYMBOL_TRIANGLE_DOWN,
    NK_SYMBOL_TRIANGLE_LEFT,
    NK_SYMBOL_TRIANGLE_RIGHT,
    NK_SYMBOL_PLUS,
    NK_SYMBOL_MINUS,
    NK_SYMBOL_MAX
};

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR

NK_API nk_bool nk_init_default(struct nk_context*, const struct nk_user_font*);
#endif

NK_API nk_bool nk_init_fixed(struct nk_context*, void *memory, nk_size size, const struct nk_user_font*);

NK_API nk_bool nk_init(struct nk_context*, struct nk_allocator*, const struct nk_user_font*);

NK_API nk_bool nk_init_custom(struct nk_context*, struct nk_buffer *cmds, struct nk_buffer *pool, const struct nk_user_font*);

NK_API void nk_clear(struct nk_context*);

NK_API void nk_free(struct nk_context*);
#ifdef NK_INCLUDE_COMMAND_USERDATA

NK_API void nk_set_user_data(struct nk_context*, nk_handle handle);
#endif

enum nk_keys {
    NK_KEY_NONE,
    NK_KEY_SHIFT,
    NK_KEY_CTRL,
    NK_KEY_DEL,
    NK_KEY_ENTER,
    NK_KEY_TAB,
    NK_KEY_BACKSPACE,
    NK_KEY_COPY,
    NK_KEY_CUT,
    NK_KEY_PASTE,
    NK_KEY_UP,
    NK_KEY_DOWN,
    NK_KEY_LEFT,
    NK_KEY_RIGHT,

    NK_KEY_TEXT_INSERT_MODE,
    NK_KEY_TEXT_REPLACE_MODE,
    NK_KEY_TEXT_RESET_MODE,
    NK_KEY_TEXT_LINE_START,
    NK_KEY_TEXT_LINE_END,
    NK_KEY_INSERT,
    NK_KEY_TEXT_START,
    NK_KEY_TEXT_END,
    NK_KEY_TEXT_UNDO,
    NK_KEY_TEXT_REDO,
    NK_KEY_TEXT_SELECT_ALL,
    NK_KEY_TEXT_WORD_LEFT,
    NK_KEY_TEXT_WORD_RIGHT,

    NK_KEY_SCROLL_START,
    NK_KEY_SCROLL_END,
    NK_KEY_SCROLL_DOWN,
    NK_KEY_SCROLL_UP,
    NK_KEY_MAX
};
enum nk_buttons {
    NK_BUTTON_LEFT,
    NK_BUTTON_MIDDLE,
    NK_BUTTON_RIGHT,
    NK_BUTTON_DOUBLE,
    NK_BUTTON_MAX
};

NK_API void nk_input_begin(struct nk_context*);

NK_API void nk_input_motion(struct nk_context*, int x, int y);

NK_API void nk_input_key(struct nk_context*, enum nk_keys, nk_bool down);

NK_API void nk_input_button(struct nk_context*, enum nk_buttons, int x, int y, nk_bool down);

NK_API void nk_input_scroll(struct nk_context*, struct nk_vec2 val);

NK_API void nk_input_char(struct nk_context*, char);

NK_API void nk_input_glyph(struct nk_context*, const nk_glyph);

NK_API void nk_input_unicode(struct nk_context*, nk_rune);

NK_API void nk_input_end(struct nk_context*);

enum nk_anti_aliasing {NK_ANTI_ALIASING_OFF, NK_ANTI_ALIASING_ON};
enum nk_convert_result {
    NK_CONVERT_SUCCESS = 0,
    NK_CONVERT_INVALID_PARAM = 1,
    NK_CONVERT_COMMAND_BUFFER_FULL = NK_FLAG(1),
    NK_CONVERT_VERTEX_BUFFER_FULL = NK_FLAG(2),
    NK_CONVERT_ELEMENT_BUFFER_FULL = NK_FLAG(3)
};
struct nk_draw_null_texture {
    nk_handle texture;
    struct nk_vec2 uv;
};
struct nk_convert_config {
    float global_alpha;
    enum nk_anti_aliasing line_AA;
    enum nk_anti_aliasing shape_AA;
    unsigned circle_segment_count;
    unsigned arc_segment_count;
    unsigned curve_segment_count;
    struct nk_draw_null_texture tex_null;
    const struct nk_draw_vertex_layout_element *vertex_layout;
    nk_size vertex_size;
    nk_size vertex_alignment;
};

NK_API const struct nk_command* nk__begin(struct nk_context*);

NK_API const struct nk_command* nk__next(struct nk_context*, const struct nk_command*);

#define nk_foreach(c, ctx) for((c) = nk__begin(ctx); (c) != 0; (c) = nk__next(ctx,c))
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT

NK_API nk_flags nk_convert(struct nk_context*, struct nk_buffer *cmds, struct nk_buffer *vertices, struct nk_buffer *elements, const struct nk_convert_config*);

NK_API const struct nk_draw_command* nk__draw_begin(const struct nk_context*, const struct nk_buffer*);

NK_API const struct nk_draw_command* nk__draw_end(const struct nk_context*, const struct nk_buffer*);

NK_API const struct nk_draw_command* nk__draw_next(const struct nk_draw_command*, const struct nk_buffer*, const struct nk_context*);

#define nk_draw_foreach(cmd,ctx, b) for((cmd)=nk__draw_begin(ctx, b); (cmd)!=0; (cmd)=nk__draw_next(cmd, b, ctx))
#endif

enum nk_panel_flags {
    NK_WINDOW_BORDER            = NK_FLAG(0),
    NK_WINDOW_MOVABLE           = NK_FLAG(1),
    NK_WINDOW_SCALABLE          = NK_FLAG(2),
    NK_WINDOW_CLOSABLE          = NK_FLAG(3),
    NK_WINDOW_MINIMIZABLE       = NK_FLAG(4),
    NK_WINDOW_NO_SCROLLBAR      = NK_FLAG(5),
    NK_WINDOW_TITLE             = NK_FLAG(6),
    NK_WINDOW_SCROLL_AUTO_HIDE  = NK_FLAG(7),
    NK_WINDOW_BACKGROUND        = NK_FLAG(8),
    NK_WINDOW_SCALE_LEFT        = NK_FLAG(9),
    NK_WINDOW_NO_INPUT          = NK_FLAG(10)
};

NK_API nk_bool nk_begin(struct nk_context *ctx, const char *title, struct nk_rect bounds, nk_flags flags);

NK_API nk_bool nk_begin_titled(struct nk_context *ctx, const char *name, const char *title, struct nk_rect bounds, nk_flags flags);

NK_API void nk_end(struct nk_context *ctx);

NK_API struct nk_window *nk_window_find(struct nk_context *ctx, const char *name);

NK_API struct nk_rect nk_window_get_bounds(const struct nk_context *ctx);

NK_API struct nk_vec2 nk_window_get_position(const struct nk_context *ctx);

NK_API struct nk_vec2 nk_window_get_size(const struct nk_context*);

NK_API float nk_window_get_width(const struct nk_context*);

NK_API float nk_window_get_height(const struct nk_context*);

NK_API struct nk_panel* nk_window_get_panel(struct nk_context*);

NK_API struct nk_rect nk_window_get_content_region(struct nk_context*);

NK_API struct nk_vec2 nk_window_get_content_region_min(struct nk_context*);

NK_API struct nk_vec2 nk_window_get_content_region_max(struct nk_context*);

NK_API struct nk_vec2 nk_window_get_content_region_size(struct nk_context*);

NK_API struct nk_command_buffer* nk_window_get_canvas(struct nk_context*);

NK_API void nk_window_get_scroll(struct nk_context*, nk_uint *offset_x, nk_uint *offset_y);

NK_API nk_bool nk_window_has_focus(const struct nk_context*);

NK_API nk_bool nk_window_is_hovered(struct nk_context*);

NK_API nk_bool nk_window_is_collapsed(struct nk_context *ctx, const char *name);

NK_API nk_bool nk_window_is_closed(struct nk_context*, const char*);

NK_API nk_bool nk_window_is_hidden(struct nk_context*, const char*);

NK_API nk_bool nk_window_is_active(struct nk_context*, const char*);

NK_API nk_bool nk_window_is_any_hovered(struct nk_context*);

NK_API nk_bool nk_item_is_any_active(struct nk_context*);

NK_API void nk_window_set_bounds(struct nk_context*, const char *name, struct nk_rect bounds);

NK_API void nk_window_set_position(struct nk_context*, const char *name, struct nk_vec2 pos);

NK_API void nk_window_set_size(struct nk_context*, const char *name, struct nk_vec2);

NK_API void nk_window_set_focus(struct nk_context*, const char *name);

NK_API void nk_window_set_scroll(struct nk_context*, nk_uint offset_x, nk_uint offset_y);

NK_API void nk_window_close(struct nk_context *ctx, const char *name);

NK_API void nk_window_collapse(struct nk_context*, const char *name, enum nk_collapse_states state);

NK_API void nk_window_collapse_if(struct nk_context*, const char *name, enum nk_collapse_states, int cond);

NK_API void nk_window_show(struct nk_context*, const char *name, enum nk_show_states);

NK_API void nk_window_show_if(struct nk_context*, const char *name, enum nk_show_states, int cond);

NK_API void nk_layout_set_min_row_height(struct nk_context*, float height);

NK_API void nk_layout_reset_min_row_height(struct nk_context*);

NK_API struct nk_rect nk_layout_widget_bounds(struct nk_context*);

NK_API float nk_layout_ratio_from_pixel(struct nk_context*, float pixel_width);

NK_API void nk_layout_row_dynamic(struct nk_context *ctx, float height, int cols);

NK_API void nk_layout_row_static(struct nk_context *ctx, float height, int item_width, int cols);

NK_API void nk_layout_row_begin(struct nk_context *ctx, enum nk_layout_format fmt, float row_height, int cols);

NK_API void nk_layout_row_push(struct nk_context*, float value);

NK_API void nk_layout_row_end(struct nk_context*);

NK_API void nk_layout_row(struct nk_context*, enum nk_layout_format, float height, int cols, const float *ratio);

NK_API void nk_layout_row_template_begin(struct nk_context*, float row_height);

NK_API void nk_layout_row_template_push_dynamic(struct nk_context*);

NK_API void nk_layout_row_template_push_variable(struct nk_context*, float min_width);

NK_API void nk_layout_row_template_push_static(struct nk_context*, float width);

NK_API void nk_layout_row_template_end(struct nk_context*);

NK_API void nk_layout_space_begin(struct nk_context*, enum nk_layout_format, float height, int widget_count);

NK_API void nk_layout_space_push(struct nk_context*, struct nk_rect bounds);

NK_API void nk_layout_space_end(struct nk_context*);

NK_API struct nk_rect nk_layout_space_bounds(struct nk_context*);

NK_API struct nk_vec2 nk_layout_space_to_screen(struct nk_context*, struct nk_vec2);

NK_API struct nk_vec2 nk_layout_space_to_local(struct nk_context*, struct nk_vec2);

NK_API struct nk_rect nk_layout_space_rect_to_screen(struct nk_context*, struct nk_rect);

NK_API struct nk_rect nk_layout_space_rect_to_local(struct nk_context*, struct nk_rect);

NK_API void nk_spacer(struct nk_context* );

NK_API nk_bool nk_group_begin(struct nk_context*, const char *title, nk_flags);

NK_API nk_bool nk_group_begin_titled(struct nk_context*, const char *name, const char *title, nk_flags);

NK_API void nk_group_end(struct nk_context*);

NK_API nk_bool nk_group_scrolled_offset_begin(struct nk_context*, nk_uint *x_offset, nk_uint *y_offset, const char *title, nk_flags flags);

NK_API nk_bool nk_group_scrolled_begin(struct nk_context*, struct nk_scroll *off, const char *title, nk_flags);

NK_API void nk_group_scrolled_end(struct nk_context*);

NK_API void nk_group_get_scroll(struct nk_context*, const char *id, nk_uint *x_offset, nk_uint *y_offset);

NK_API void nk_group_set_scroll(struct nk_context*, const char *id, nk_uint x_offset, nk_uint y_offset);

#define nk_tree_push(ctx, type, title, state) nk_tree_push_hashed(ctx, type, title, state, NK_FILE_LINE,nk_strlen(NK_FILE_LINE),__LINE__)

#define nk_tree_push_id(ctx, type, title, state, id) nk_tree_push_hashed(ctx, type, title, state, NK_FILE_LINE,nk_strlen(NK_FILE_LINE),id)

NK_API nk_bool nk_tree_push_hashed(struct nk_context*, enum nk_tree_type, const char *title, enum nk_collapse_states initial_state, const char *hash, int len,int seed);

#define nk_tree_image_push(ctx, type, img, title, state) nk_tree_image_push_hashed(ctx, type, img, title, state, NK_FILE_LINE,nk_strlen(NK_FILE_LINE),__LINE__)

#define nk_tree_image_push_id(ctx, type, img, title, state, id) nk_tree_image_push_hashed(ctx, type, img, title, state, NK_FILE_LINE,nk_strlen(NK_FILE_LINE),id)

NK_API nk_bool nk_tree_image_push_hashed(struct nk_context*, enum nk_tree_type, struct nk_image, const char *title, enum nk_collapse_states initial_state, const char *hash, int len,int seed);

NK_API void nk_tree_pop(struct nk_context*);

NK_API nk_bool nk_tree_state_push(struct nk_context*, enum nk_tree_type, const char *title, enum nk_collapse_states *state);

NK_API nk_bool nk_tree_state_image_push(struct nk_context*, enum nk_tree_type, struct nk_image, const char *title, enum nk_collapse_states *state);

NK_API void nk_tree_state_pop(struct nk_context*);

#define nk_tree_element_push(ctx, type, title, state, sel) nk_tree_element_push_hashed(ctx, type, title, state, sel, NK_FILE_LINE,nk_strlen(NK_FILE_LINE),__LINE__)
#define nk_tree_element_push_id(ctx, type, title, state, sel, id) nk_tree_element_push_hashed(ctx, type, title, state, sel, NK_FILE_LINE,nk_strlen(NK_FILE_LINE),id)
NK_API nk_bool nk_tree_element_push_hashed(struct nk_context*, enum nk_tree_type, const char *title, enum nk_collapse_states initial_state, nk_bool *selected, const char *hash, int len, int seed);
NK_API nk_bool nk_tree_element_image_push_hashed(struct nk_context*, enum nk_tree_type, struct nk_image, const char *title, enum nk_collapse_states initial_state, nk_bool *selected, const char *hash, int len,int seed);
NK_API void nk_tree_element_pop(struct nk_context*);

struct nk_list_view {

    int begin, end, count;

    int total_height;
    struct nk_context *ctx;
    nk_uint *scroll_pointer;
    nk_uint scroll_value;
};
NK_API nk_bool nk_list_view_begin(struct nk_context*, struct nk_list_view *out, const char *id, nk_flags, int row_height, int row_count);
NK_API void nk_list_view_end(struct nk_list_view*);

enum nk_widget_layout_states {
    NK_WIDGET_INVALID,
    NK_WIDGET_VALID,
    NK_WIDGET_ROM
};
enum nk_widget_states {
    NK_WIDGET_STATE_MODIFIED    = NK_FLAG(1),
    NK_WIDGET_STATE_INACTIVE    = NK_FLAG(2),
    NK_WIDGET_STATE_ENTERED     = NK_FLAG(3),
    NK_WIDGET_STATE_HOVER       = NK_FLAG(4),
    NK_WIDGET_STATE_ACTIVED     = NK_FLAG(5),
    NK_WIDGET_STATE_LEFT        = NK_FLAG(6),
    NK_WIDGET_STATE_HOVERED     = NK_WIDGET_STATE_HOVER|NK_WIDGET_STATE_MODIFIED,
    NK_WIDGET_STATE_ACTIVE      = NK_WIDGET_STATE_ACTIVED|NK_WIDGET_STATE_MODIFIED
};
NK_API enum nk_widget_layout_states nk_widget(struct nk_rect*, const struct nk_context*);
NK_API enum nk_widget_layout_states nk_widget_fitting(struct nk_rect*, struct nk_context*, struct nk_vec2);
NK_API struct nk_rect nk_widget_bounds(struct nk_context*);
NK_API struct nk_vec2 nk_widget_position(struct nk_context*);
NK_API struct nk_vec2 nk_widget_size(struct nk_context*);
NK_API float nk_widget_width(struct nk_context*);
NK_API float nk_widget_height(struct nk_context*);
NK_API nk_bool nk_widget_is_hovered(struct nk_context*);
NK_API nk_bool nk_widget_is_mouse_clicked(struct nk_context*, enum nk_buttons);
NK_API nk_bool nk_widget_has_mouse_click_down(struct nk_context*, enum nk_buttons, nk_bool down);
NK_API void nk_spacing(struct nk_context*, int cols);

enum nk_text_align {
    NK_TEXT_ALIGN_LEFT        = 0x01,
    NK_TEXT_ALIGN_CENTERED    = 0x02,
    NK_TEXT_ALIGN_RIGHT       = 0x04,
    NK_TEXT_ALIGN_TOP         = 0x08,
    NK_TEXT_ALIGN_MIDDLE      = 0x10,
    NK_TEXT_ALIGN_BOTTOM      = 0x20
};
enum nk_text_alignment {
    NK_TEXT_LEFT        = NK_TEXT_ALIGN_MIDDLE|NK_TEXT_ALIGN_LEFT,
    NK_TEXT_CENTERED    = NK_TEXT_ALIGN_MIDDLE|NK_TEXT_ALIGN_CENTERED,
    NK_TEXT_RIGHT       = NK_TEXT_ALIGN_MIDDLE|NK_TEXT_ALIGN_RIGHT
};
NK_API void nk_text(struct nk_context*, const char*, int, nk_flags);
NK_API void nk_text_colored(struct nk_context*, const char*, int, nk_flags, struct nk_color);
NK_API void nk_text_wrap(struct nk_context*, const char*, int);
NK_API void nk_text_wrap_colored(struct nk_context*, const char*, int, struct nk_color);
NK_API void nk_label(struct nk_context*, const char*, nk_flags align);
NK_API void nk_label_colored(struct nk_context*, const char*, nk_flags align, struct nk_color);
NK_API void nk_label_wrap(struct nk_context*, const char*);
NK_API void nk_label_colored_wrap(struct nk_context*, const char*, struct nk_color);
NK_API void nk_image(struct nk_context*, struct nk_image);
NK_API void nk_image_color(struct nk_context*, struct nk_image, struct nk_color);
#ifdef NK_INCLUDE_STANDARD_VARARGS
NK_API void nk_labelf(struct nk_context*, nk_flags, NK_PRINTF_FORMAT_STRING const char*, ...) NK_PRINTF_VARARG_FUNC(3);
NK_API void nk_labelf_colored(struct nk_context*, nk_flags, struct nk_color, NK_PRINTF_FORMAT_STRING const char*,...) NK_PRINTF_VARARG_FUNC(4);
NK_API void nk_labelf_wrap(struct nk_context*, NK_PRINTF_FORMAT_STRING const char*,...) NK_PRINTF_VARARG_FUNC(2);
NK_API void nk_labelf_colored_wrap(struct nk_context*, struct nk_color, NK_PRINTF_FORMAT_STRING const char*,...) NK_PRINTF_VARARG_FUNC(3);
NK_API void nk_labelfv(struct nk_context*, nk_flags, NK_PRINTF_FORMAT_STRING const char*, va_list) NK_PRINTF_VALIST_FUNC(3);
NK_API void nk_labelfv_colored(struct nk_context*, nk_flags, struct nk_color, NK_PRINTF_FORMAT_STRING const char*, va_list) NK_PRINTF_VALIST_FUNC(4);
NK_API void nk_labelfv_wrap(struct nk_context*, NK_PRINTF_FORMAT_STRING const char*, va_list) NK_PRINTF_VALIST_FUNC(2);
NK_API void nk_labelfv_colored_wrap(struct nk_context*, struct nk_color, NK_PRINTF_FORMAT_STRING const char*, va_list) NK_PRINTF_VALIST_FUNC(3);
NK_API void nk_value_bool(struct nk_context*, const char *prefix, int);
NK_API void nk_value_int(struct nk_context*, const char *prefix, int);
NK_API void nk_value_uint(struct nk_context*, const char *prefix, unsigned int);
NK_API void nk_value_float(struct nk_context*, const char *prefix, float);
NK_API void nk_value_color_byte(struct nk_context*, const char *prefix, struct nk_color);
NK_API void nk_value_color_float(struct nk_context*, const char *prefix, struct nk_color);
NK_API void nk_value_color_hex(struct nk_context*, const char *prefix, struct nk_color);
#endif

NK_API nk_bool nk_button_text(struct nk_context*, const char *title, int len);
NK_API nk_bool nk_button_label(struct nk_context*, const char *title);
NK_API nk_bool nk_button_color(struct nk_context*, struct nk_color);
NK_API nk_bool nk_button_symbol(struct nk_context*, enum nk_symbol_type);
NK_API nk_bool nk_button_image(struct nk_context*, struct nk_image img);
NK_API nk_bool nk_button_symbol_label(struct nk_context*, enum nk_symbol_type, const char*, nk_flags text_alignment);
NK_API nk_bool nk_button_symbol_text(struct nk_context*, enum nk_symbol_type, const char*, int, nk_flags alignment);
NK_API nk_bool nk_button_image_label(struct nk_context*, struct nk_image img, const char*, nk_flags text_alignment);
NK_API nk_bool nk_button_image_text(struct nk_context*, struct nk_image img, const char*, int, nk_flags alignment);
NK_API nk_bool nk_button_text_styled(struct nk_context*, const struct nk_style_button*, const char *title, int len);
NK_API nk_bool nk_button_label_styled(struct nk_context*, const struct nk_style_button*, const char *title);
NK_API nk_bool nk_button_symbol_styled(struct nk_context*, const struct nk_style_button*, enum nk_symbol_type);
NK_API nk_bool nk_button_image_styled(struct nk_context*, const struct nk_style_button*, struct nk_image img);
NK_API nk_bool nk_button_symbol_text_styled(struct nk_context*,const struct nk_style_button*, enum nk_symbol_type, const char*, int, nk_flags alignment);
NK_API nk_bool nk_button_symbol_label_styled(struct nk_context *ctx, const struct nk_style_button *style, enum nk_symbol_type symbol, const char *title, nk_flags align);
NK_API nk_bool nk_button_image_label_styled(struct nk_context*,const struct nk_style_button*, struct nk_image img, const char*, nk_flags text_alignment);
NK_API nk_bool nk_button_image_text_styled(struct nk_context*,const struct nk_style_button*, struct nk_image img, const char*, int, nk_flags alignment);
NK_API void nk_button_set_behavior(struct nk_context*, enum nk_button_behavior);
NK_API nk_bool nk_button_push_behavior(struct nk_context*, enum nk_button_behavior);
NK_API nk_bool nk_button_pop_behavior(struct nk_context*);

NK_API nk_bool nk_check_label(struct nk_context*, const char*, nk_bool active);
NK_API nk_bool nk_check_text(struct nk_context*, const char*, int, nk_bool active);
NK_API unsigned nk_check_flags_label(struct nk_context*, const char*, unsigned int flags, unsigned int value);
NK_API unsigned nk_check_flags_text(struct nk_context*, const char*, int, unsigned int flags, unsigned int value);
NK_API nk_bool nk_checkbox_label(struct nk_context*, const char*, nk_bool *active);
NK_API nk_bool nk_checkbox_text(struct nk_context*, const char*, int, nk_bool *active);
NK_API nk_bool nk_checkbox_flags_label(struct nk_context*, const char*, unsigned int *flags, unsigned int value);
NK_API nk_bool nk_checkbox_flags_text(struct nk_context*, const char*, int, unsigned int *flags, unsigned int value);

NK_API nk_bool nk_radio_label(struct nk_context*, const char*, nk_bool *active);
NK_API nk_bool nk_radio_text(struct nk_context*, const char*, int, nk_bool *active);
NK_API nk_bool nk_option_label(struct nk_context*, const char*, nk_bool active);
NK_API nk_bool nk_option_text(struct nk_context*, const char*, int, nk_bool active);

NK_API nk_bool nk_selectable_label(struct nk_context*, const char*, nk_flags align, nk_bool *value);
NK_API nk_bool nk_selectable_text(struct nk_context*, const char*, int, nk_flags align, nk_bool *value);
NK_API nk_bool nk_selectable_image_label(struct nk_context*,struct nk_image,  const char*, nk_flags align, nk_bool *value);
NK_API nk_bool nk_selectable_image_text(struct nk_context*,struct nk_image, const char*, int, nk_flags align, nk_bool *value);
NK_API nk_bool nk_selectable_symbol_label(struct nk_context*,enum nk_symbol_type,  const char*, nk_flags align, nk_bool *value);
NK_API nk_bool nk_selectable_symbol_text(struct nk_context*,enum nk_symbol_type, const char*, int, nk_flags align, nk_bool *value);

NK_API nk_bool nk_select_label(struct nk_context*, const char*, nk_flags align, nk_bool value);
NK_API nk_bool nk_select_text(struct nk_context*, const char*, int, nk_flags align, nk_bool value);
NK_API nk_bool nk_select_image_label(struct nk_context*, struct nk_image,const char*, nk_flags align, nk_bool value);
NK_API nk_bool nk_select_image_text(struct nk_context*, struct nk_image,const char*, int, nk_flags align, nk_bool value);
NK_API nk_bool nk_select_symbol_label(struct nk_context*,enum nk_symbol_type,  const char*, nk_flags align, nk_bool value);
NK_API nk_bool nk_select_symbol_text(struct nk_context*,enum nk_symbol_type, const char*, int, nk_flags align, nk_bool value);

NK_API float nk_slide_float(struct nk_context*, float min, float val, float max, float step);
NK_API int nk_slide_int(struct nk_context*, int min, int val, int max, int step);
NK_API nk_bool nk_slider_float(struct nk_context*, float min, float *val, float max, float step);
NK_API nk_bool nk_slider_int(struct nk_context*, int min, int *val, int max, int step);

NK_API nk_bool nk_progress(struct nk_context*, nk_size *cur, nk_size max, nk_bool modifyable);
NK_API nk_size nk_prog(struct nk_context*, nk_size cur, nk_size max, nk_bool modifyable);

NK_API struct nk_colorf nk_color_picker(struct nk_context*, struct nk_colorf, enum nk_color_format);
NK_API nk_bool nk_color_pick(struct nk_context*, struct nk_colorf*, enum nk_color_format);

NK_API void nk_property_int(struct nk_context*, const char *name, int min, int *val, int max, int step, float inc_per_pixel);

NK_API void nk_property_float(struct nk_context*, const char *name, float min, float *val, float max, float step, float inc_per_pixel);

NK_API void nk_property_double(struct nk_context*, const char *name, double min, double *val, double max, double step, float inc_per_pixel);

NK_API int nk_propertyi(struct nk_context*, const char *name, int min, int val, int max, int step, float inc_per_pixel);

NK_API float nk_propertyf(struct nk_context*, const char *name, float min, float val, float max, float step, float inc_per_pixel);

NK_API double nk_propertyd(struct nk_context*, const char *name, double min, double val, double max, double step, float inc_per_pixel);

enum nk_edit_flags {
    NK_EDIT_DEFAULT                 = 0,
    NK_EDIT_READ_ONLY               = NK_FLAG(0),
    NK_EDIT_AUTO_SELECT             = NK_FLAG(1),
    NK_EDIT_SIG_ENTER               = NK_FLAG(2),
    NK_EDIT_ALLOW_TAB               = NK_FLAG(3),
    NK_EDIT_NO_CURSOR               = NK_FLAG(4),
    NK_EDIT_SELECTABLE              = NK_FLAG(5),
    NK_EDIT_CLIPBOARD               = NK_FLAG(6),
    NK_EDIT_CTRL_ENTER_NEWLINE      = NK_FLAG(7),
    NK_EDIT_NO_HORIZONTAL_SCROLL    = NK_FLAG(8),
    NK_EDIT_ALWAYS_INSERT_MODE      = NK_FLAG(9),
    NK_EDIT_MULTILINE               = NK_FLAG(10),
    NK_EDIT_GOTO_END_ON_ACTIVATE    = NK_FLAG(11)
};
enum nk_edit_types {
    NK_EDIT_SIMPLE  = NK_EDIT_ALWAYS_INSERT_MODE,
    NK_EDIT_FIELD   = NK_EDIT_SIMPLE|NK_EDIT_SELECTABLE|NK_EDIT_CLIPBOARD,
    NK_EDIT_BOX     = NK_EDIT_ALWAYS_INSERT_MODE| NK_EDIT_SELECTABLE| NK_EDIT_MULTILINE|NK_EDIT_ALLOW_TAB|NK_EDIT_CLIPBOARD,
    NK_EDIT_EDITOR  = NK_EDIT_SELECTABLE|NK_EDIT_MULTILINE|NK_EDIT_ALLOW_TAB| NK_EDIT_CLIPBOARD
};
enum nk_edit_events {
    NK_EDIT_ACTIVE      = NK_FLAG(0),
    NK_EDIT_INACTIVE    = NK_FLAG(1),
    NK_EDIT_ACTIVATED   = NK_FLAG(2),
    NK_EDIT_DEACTIVATED = NK_FLAG(3),
    NK_EDIT_COMMITED    = NK_FLAG(4)
};
NK_API nk_flags nk_edit_string(struct nk_context*, nk_flags, char *buffer, int *len, int max, nk_plugin_filter);
NK_API nk_flags nk_edit_string_zero_terminated(struct nk_context*, nk_flags, char *buffer, int max, nk_plugin_filter);
NK_API nk_flags nk_edit_buffer(struct nk_context*, nk_flags, struct nk_text_edit*, nk_plugin_filter);
NK_API void nk_edit_focus(struct nk_context*, nk_flags flags);
NK_API void nk_edit_unfocus(struct nk_context*);

NK_API nk_bool nk_chart_begin(struct nk_context*, enum nk_chart_type, int num, float min, float max);
NK_API nk_bool nk_chart_begin_colored(struct nk_context*, enum nk_chart_type, struct nk_color, struct nk_color active, int num, float min, float max);
NK_API void nk_chart_add_slot(struct nk_context *ctx, const enum nk_chart_type, int count, float min_value, float max_value);
NK_API void nk_chart_add_slot_colored(struct nk_context *ctx, const enum nk_chart_type, struct nk_color, struct nk_color active, int count, float min_value, float max_value);
NK_API nk_flags nk_chart_push(struct nk_context*, float);
NK_API nk_flags nk_chart_push_slot(struct nk_context*, float, int);
NK_API void nk_chart_end(struct nk_context*);
NK_API void nk_plot(struct nk_context*, enum nk_chart_type, const float *values, int count, int offset);
NK_API void nk_plot_function(struct nk_context*, enum nk_chart_type, void *userdata, float(*value_getter)(void* user, int index), int count, int offset);

NK_API nk_bool nk_popup_begin(struct nk_context*, enum nk_popup_type, const char*, nk_flags, struct nk_rect bounds);
NK_API void nk_popup_close(struct nk_context*);
NK_API void nk_popup_end(struct nk_context*);
NK_API void nk_popup_get_scroll(struct nk_context*, nk_uint *offset_x, nk_uint *offset_y);
NK_API void nk_popup_set_scroll(struct nk_context*, nk_uint offset_x, nk_uint offset_y);

NK_API int nk_combo(struct nk_context*, const char **items, int count, int selected, int item_height, struct nk_vec2 size);
NK_API int nk_combo_separator(struct nk_context*, const char *items_separated_by_separator, int separator, int selected, int count, int item_height, struct nk_vec2 size);
NK_API int nk_combo_string(struct nk_context*, const char *items_separated_by_zeros, int selected, int count, int item_height, struct nk_vec2 size);
NK_API int nk_combo_callback(struct nk_context*, void(*item_getter)(void*, int, const char**), void *userdata, int selected, int count, int item_height, struct nk_vec2 size);
NK_API void nk_combobox(struct nk_context*, const char **items, int count, int *selected, int item_height, struct nk_vec2 size);
NK_API void nk_combobox_string(struct nk_context*, const char *items_separated_by_zeros, int *selected, int count, int item_height, struct nk_vec2 size);
NK_API void nk_combobox_separator(struct nk_context*, const char *items_separated_by_separator, int separator, int *selected, int count, int item_height, struct nk_vec2 size);
NK_API void nk_combobox_callback(struct nk_context*, void(*item_getter)(void*, int, const char**), void*, int *selected, int count, int item_height, struct nk_vec2 size);

NK_API nk_bool nk_combo_begin_text(struct nk_context*, const char *selected, int, struct nk_vec2 size);
NK_API nk_bool nk_combo_begin_label(struct nk_context*, const char *selected, struct nk_vec2 size);
NK_API nk_bool nk_combo_begin_color(struct nk_context*, struct nk_color color, struct nk_vec2 size);
NK_API nk_bool nk_combo_begin_symbol(struct nk_context*,  enum nk_symbol_type,  struct nk_vec2 size);
NK_API nk_bool nk_combo_begin_symbol_label(struct nk_context*, const char *selected, enum nk_symbol_type, struct nk_vec2 size);
NK_API nk_bool nk_combo_begin_symbol_text(struct nk_context*, const char *selected, int, enum nk_symbol_type, struct nk_vec2 size);
NK_API nk_bool nk_combo_begin_image(struct nk_context*, struct nk_image img,  struct nk_vec2 size);
NK_API nk_bool nk_combo_begin_image_label(struct nk_context*, const char *selected, struct nk_image, struct nk_vec2 size);
NK_API nk_bool nk_combo_begin_image_text(struct nk_context*,  const char *selected, int, struct nk_image, struct nk_vec2 size);
NK_API nk_bool nk_combo_item_label(struct nk_context*, const char*, nk_flags alignment);
NK_API nk_bool nk_combo_item_text(struct nk_context*, const char*,int, nk_flags alignment);
NK_API nk_bool nk_combo_item_image_label(struct nk_context*, struct nk_image, const char*, nk_flags alignment);
NK_API nk_bool nk_combo_item_image_text(struct nk_context*, struct nk_image, const char*, int,nk_flags alignment);
NK_API nk_bool nk_combo_item_symbol_label(struct nk_context*, enum nk_symbol_type, const char*, nk_flags alignment);
NK_API nk_bool nk_combo_item_symbol_text(struct nk_context*, enum nk_symbol_type, const char*, int, nk_flags alignment);
NK_API void nk_combo_close(struct nk_context*);
NK_API void nk_combo_end(struct nk_context*);

NK_API nk_bool nk_contextual_begin(struct nk_context*, nk_flags, struct nk_vec2, struct nk_rect trigger_bounds);
NK_API nk_bool nk_contextual_item_text(struct nk_context*, const char*, int,nk_flags align);
NK_API nk_bool nk_contextual_item_label(struct nk_context*, const char*, nk_flags align);
NK_API nk_bool nk_contextual_item_image_label(struct nk_context*, struct nk_image, const char*, nk_flags alignment);
NK_API nk_bool nk_contextual_item_image_text(struct nk_context*, struct nk_image, const char*, int len, nk_flags alignment);
NK_API nk_bool nk_contextual_item_symbol_label(struct nk_context*, enum nk_symbol_type, const char*, nk_flags alignment);
NK_API nk_bool nk_contextual_item_symbol_text(struct nk_context*, enum nk_symbol_type, const char*, int, nk_flags alignment);
NK_API void nk_contextual_close(struct nk_context*);
NK_API void nk_contextual_end(struct nk_context*);

NK_API void nk_tooltip(struct nk_context*, const char*);
#ifdef NK_INCLUDE_STANDARD_VARARGS
NK_API void nk_tooltipf(struct nk_context*, NK_PRINTF_FORMAT_STRING const char*, ...) NK_PRINTF_VARARG_FUNC(2);
NK_API void nk_tooltipfv(struct nk_context*, NK_PRINTF_FORMAT_STRING const char*, va_list) NK_PRINTF_VALIST_FUNC(2);
#endif
NK_API nk_bool nk_tooltip_begin(struct nk_context*, float width);
NK_API void nk_tooltip_end(struct nk_context*);

NK_API void nk_menubar_begin(struct nk_context*);
NK_API void nk_menubar_end(struct nk_context*);
NK_API nk_bool nk_menu_begin_text(struct nk_context*, const char* title, int title_len, nk_flags align, struct nk_vec2 size);
NK_API nk_bool nk_menu_begin_label(struct nk_context*, const char*, nk_flags align, struct nk_vec2 size);
NK_API nk_bool nk_menu_begin_image(struct nk_context*, const char*, struct nk_image, struct nk_vec2 size);
NK_API nk_bool nk_menu_begin_image_text(struct nk_context*, const char*, int,nk_flags align,struct nk_image, struct nk_vec2 size);
NK_API nk_bool nk_menu_begin_image_label(struct nk_context*, const char*, nk_flags align,struct nk_image, struct nk_vec2 size);
NK_API nk_bool nk_menu_begin_symbol(struct nk_context*, const char*, enum nk_symbol_type, struct nk_vec2 size);
NK_API nk_bool nk_menu_begin_symbol_text(struct nk_context*, const char*, int,nk_flags align,enum nk_symbol_type, struct nk_vec2 size);
NK_API nk_bool nk_menu_begin_symbol_label(struct nk_context*, const char*, nk_flags align,enum nk_symbol_type, struct nk_vec2 size);
NK_API nk_bool nk_menu_item_text(struct nk_context*, const char*, int,nk_flags align);
NK_API nk_bool nk_menu_item_label(struct nk_context*, const char*, nk_flags alignment);
NK_API nk_bool nk_menu_item_image_label(struct nk_context*, struct nk_image, const char*, nk_flags alignment);
NK_API nk_bool nk_menu_item_image_text(struct nk_context*, struct nk_image, const char*, int len, nk_flags alignment);
NK_API nk_bool nk_menu_item_symbol_text(struct nk_context*, enum nk_symbol_type, const char*, int, nk_flags alignment);
NK_API nk_bool nk_menu_item_symbol_label(struct nk_context*, enum nk_symbol_type, const char*, nk_flags alignment);
NK_API void nk_menu_close(struct nk_context*);
NK_API void nk_menu_end(struct nk_context*);

enum nk_style_colors {
    NK_COLOR_TEXT,
    NK_COLOR_WINDOW,
    NK_COLOR_HEADER,
    NK_COLOR_BORDER,
    NK_COLOR_BUTTON,
    NK_COLOR_BUTTON_HOVER,
    NK_COLOR_BUTTON_ACTIVE,
    NK_COLOR_TOGGLE,
    NK_COLOR_TOGGLE_HOVER,
    NK_COLOR_TOGGLE_CURSOR,
    NK_COLOR_SELECT,
    NK_COLOR_SELECT_ACTIVE,
    NK_COLOR_SLIDER,
    NK_COLOR_SLIDER_CURSOR,
    NK_COLOR_SLIDER_CURSOR_HOVER,
    NK_COLOR_SLIDER_CURSOR_ACTIVE,
    NK_COLOR_PROPERTY,
    NK_COLOR_EDIT,
    NK_COLOR_EDIT_CURSOR,
    NK_COLOR_COMBO,
    NK_COLOR_CHART,
    NK_COLOR_CHART_COLOR,
    NK_COLOR_CHART_COLOR_HIGHLIGHT,
    NK_COLOR_SCROLLBAR,
    NK_COLOR_SCROLLBAR_CURSOR,
    NK_COLOR_SCROLLBAR_CURSOR_HOVER,
    NK_COLOR_SCROLLBAR_CURSOR_ACTIVE,
    NK_COLOR_TAB_HEADER,
    NK_COLOR_COUNT
};
enum nk_style_cursor {
    NK_CURSOR_ARROW,
    NK_CURSOR_TEXT,
    NK_CURSOR_MOVE,
    NK_CURSOR_RESIZE_VERTICAL,
    NK_CURSOR_RESIZE_HORIZONTAL,
    NK_CURSOR_RESIZE_TOP_LEFT_DOWN_RIGHT,
    NK_CURSOR_RESIZE_TOP_RIGHT_DOWN_LEFT,
    NK_CURSOR_COUNT
};
NK_API void nk_style_default(struct nk_context*);
NK_API void nk_style_from_table(struct nk_context*, const struct nk_color*);
NK_API void nk_style_load_cursor(struct nk_context*, enum nk_style_cursor, const struct nk_cursor*);
NK_API void nk_style_load_all_cursors(struct nk_context*, struct nk_cursor*);
NK_API const char* nk_style_get_color_by_name(enum nk_style_colors);
NK_API void nk_style_set_font(struct nk_context*, const struct nk_user_font*);
NK_API nk_bool nk_style_set_cursor(struct nk_context*, enum nk_style_cursor);
NK_API void nk_style_show_cursor(struct nk_context*);
NK_API void nk_style_hide_cursor(struct nk_context*);

NK_API nk_bool nk_style_push_font(struct nk_context*, const struct nk_user_font*);
NK_API nk_bool nk_style_push_float(struct nk_context*, float*, float);
NK_API nk_bool nk_style_push_vec2(struct nk_context*, struct nk_vec2*, struct nk_vec2);
NK_API nk_bool nk_style_push_style_item(struct nk_context*, struct nk_style_item*, struct nk_style_item);
NK_API nk_bool nk_style_push_flags(struct nk_context*, nk_flags*, nk_flags);
NK_API nk_bool nk_style_push_color(struct nk_context*, struct nk_color*, struct nk_color);

NK_API nk_bool nk_style_pop_font(struct nk_context*);
NK_API nk_bool nk_style_pop_float(struct nk_context*);
NK_API nk_bool nk_style_pop_vec2(struct nk_context*);
NK_API nk_bool nk_style_pop_style_item(struct nk_context*);
NK_API nk_bool nk_style_pop_flags(struct nk_context*);
NK_API nk_bool nk_style_pop_color(struct nk_context*);

NK_API struct nk_color nk_rgb(int r, int g, int b);
NK_API struct nk_color nk_rgb_iv(const int *rgb);
NK_API struct nk_color nk_rgb_bv(const nk_byte* rgb);
NK_API struct nk_color nk_rgb_f(float r, float g, float b);
NK_API struct nk_color nk_rgb_fv(const float *rgb);
NK_API struct nk_color nk_rgb_cf(struct nk_colorf c);
NK_API struct nk_color nk_rgb_hex(const char *rgb);

NK_API struct nk_color nk_rgba(int r, int g, int b, int a);
NK_API struct nk_color nk_rgba_u32(nk_uint);
NK_API struct nk_color nk_rgba_iv(const int *rgba);
NK_API struct nk_color nk_rgba_bv(const nk_byte *rgba);
NK_API struct nk_color nk_rgba_f(float r, float g, float b, float a);
NK_API struct nk_color nk_rgba_fv(const float *rgba);
NK_API struct nk_color nk_rgba_cf(struct nk_colorf c);
NK_API struct nk_color nk_rgba_hex(const char *rgb);

NK_API struct nk_colorf nk_hsva_colorf(float h, float s, float v, float a);
NK_API struct nk_colorf nk_hsva_colorfv(float *c);
NK_API void nk_colorf_hsva_f(float *out_h, float *out_s, float *out_v, float *out_a, struct nk_colorf in);
NK_API void nk_colorf_hsva_fv(float *hsva, struct nk_colorf in);

NK_API struct nk_color nk_hsv(int h, int s, int v);
NK_API struct nk_color nk_hsv_iv(const int *hsv);
NK_API struct nk_color nk_hsv_bv(const nk_byte *hsv);
NK_API struct nk_color nk_hsv_f(float h, float s, float v);
NK_API struct nk_color nk_hsv_fv(const float *hsv);

NK_API struct nk_color nk_hsva(int h, int s, int v, int a);
NK_API struct nk_color nk_hsva_iv(const int *hsva);
NK_API struct nk_color nk_hsva_bv(const nk_byte *hsva);
NK_API struct nk_color nk_hsva_f(float h, float s, float v, float a);
NK_API struct nk_color nk_hsva_fv(const float *hsva);

NK_API void nk_color_f(float *r, float *g, float *b, float *a, struct nk_color);
NK_API void nk_color_fv(float *rgba_out, struct nk_color);
NK_API struct nk_colorf nk_color_cf(struct nk_color);
NK_API void nk_color_d(double *r, double *g, double *b, double *a, struct nk_color);
NK_API void nk_color_dv(double *rgba_out, struct nk_color);

NK_API nk_uint nk_color_u32(struct nk_color);
NK_API void nk_color_hex_rgba(char *output, struct nk_color);
NK_API void nk_color_hex_rgb(char *output, struct nk_color);

NK_API void nk_color_hsv_i(int *out_h, int *out_s, int *out_v, struct nk_color);
NK_API void nk_color_hsv_b(nk_byte *out_h, nk_byte *out_s, nk_byte *out_v, struct nk_color);
NK_API void nk_color_hsv_iv(int *hsv_out, struct nk_color);
NK_API void nk_color_hsv_bv(nk_byte *hsv_out, struct nk_color);
NK_API void nk_color_hsv_f(float *out_h, float *out_s, float *out_v, struct nk_color);
NK_API void nk_color_hsv_fv(float *hsv_out, struct nk_color);

NK_API void nk_color_hsva_i(int *h, int *s, int *v, int *a, struct nk_color);
NK_API void nk_color_hsva_b(nk_byte *h, nk_byte *s, nk_byte *v, nk_byte *a, struct nk_color);
NK_API void nk_color_hsva_iv(int *hsva_out, struct nk_color);
NK_API void nk_color_hsva_bv(nk_byte *hsva_out, struct nk_color);
NK_API void nk_color_hsva_f(float *out_h, float *out_s, float *out_v, float *out_a, struct nk_color);
NK_API void nk_color_hsva_fv(float *hsva_out, struct nk_color);

NK_API nk_handle nk_handle_ptr(void*);
NK_API nk_handle nk_handle_id(int);
NK_API struct nk_image nk_image_handle(nk_handle);
NK_API struct nk_image nk_image_ptr(void*);
NK_API struct nk_image nk_image_id(int);
NK_API nk_bool nk_image_is_subimage(const struct nk_image* img);
NK_API struct nk_image nk_subimage_ptr(void*, nk_ushort w, nk_ushort h, struct nk_rect sub_region);
NK_API struct nk_image nk_subimage_id(int, nk_ushort w, nk_ushort h, struct nk_rect sub_region);
NK_API struct nk_image nk_subimage_handle(nk_handle, nk_ushort w, nk_ushort h, struct nk_rect sub_region);

NK_API struct nk_nine_slice nk_nine_slice_handle(nk_handle, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b);
NK_API struct nk_nine_slice nk_nine_slice_ptr(void*, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b);
NK_API struct nk_nine_slice nk_nine_slice_id(int, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b);
NK_API int nk_nine_slice_is_sub9slice(const struct nk_nine_slice* img);
NK_API struct nk_nine_slice nk_sub9slice_ptr(void*, nk_ushort w, nk_ushort h, struct nk_rect sub_region, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b);
NK_API struct nk_nine_slice nk_sub9slice_id(int, nk_ushort w, nk_ushort h, struct nk_rect sub_region, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b);
NK_API struct nk_nine_slice nk_sub9slice_handle(nk_handle, nk_ushort w, nk_ushort h, struct nk_rect sub_region, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b);

NK_API nk_hash nk_murmur_hash(const void *key, int len, nk_hash seed);
NK_API void nk_triangle_from_direction(struct nk_vec2 *result, struct nk_rect r, float pad_x, float pad_y, enum nk_heading);

NK_API struct nk_vec2 nk_vec2(float x, float y);
NK_API struct nk_vec2 nk_vec2i(int x, int y);
NK_API struct nk_vec2 nk_vec2v(const float *xy);
NK_API struct nk_vec2 nk_vec2iv(const int *xy);

NK_API struct nk_rect nk_get_null_rect(void);
NK_API struct nk_rect nk_rect(float x, float y, float w, float h);
NK_API struct nk_rect nk_recti(int x, int y, int w, int h);
NK_API struct nk_rect nk_recta(struct nk_vec2 pos, struct nk_vec2 size);
NK_API struct nk_rect nk_rectv(const float *xywh);
NK_API struct nk_rect nk_rectiv(const int *xywh);
NK_API struct nk_vec2 nk_rect_pos(struct nk_rect);
NK_API struct nk_vec2 nk_rect_size(struct nk_rect);

NK_API int nk_strlen(const char *str);
NK_API int nk_stricmp(const char *s1, const char *s2);
NK_API int nk_stricmpn(const char *s1, const char *s2, int n);
NK_API int nk_strtoi(const char *str, const char **endptr);
NK_API float nk_strtof(const char *str, const char **endptr);
#ifndef NK_STRTOD
#define NK_STRTOD nk_strtod
NK_API double nk_strtod(const char *str, const char **endptr);
#endif
NK_API int nk_strfilter(const char *text, const char *regexp);
NK_API int nk_strmatch_fuzzy_string(char const *str, char const *pattern, int *out_score);
NK_API int nk_strmatch_fuzzy_text(const char *txt, int txt_len, const char *pattern, int *out_score);

NK_API int nk_utf_decode(const char*, nk_rune*, int);
NK_API int nk_utf_encode(nk_rune, char*, int);
NK_API int nk_utf_len(const char*, int byte_len);
NK_API const char* nk_utf_at(const char *buffer, int length, int index, nk_rune *unicode, int *len);

struct nk_user_font_glyph;
typedef float(*nk_text_width_f)(nk_handle, float h, const char*, int len);
typedef void(*nk_query_font_glyph_f)(nk_handle handle, float font_height,
                                    struct nk_user_font_glyph *glyph,
                                    nk_rune codepoint, nk_rune next_codepoint);

#if defined(NK_INCLUDE_VERTEX_BUFFER_OUTPUT) || defined(NK_INCLUDE_SOFTWARE_FONT)
struct nk_user_font_glyph {
    struct nk_vec2 uv[2];

    struct nk_vec2 offset;

    float width, height;

    float xadvance;

};
#endif

struct nk_user_font {
    nk_handle userdata;

    float height;

    nk_text_width_f width;

#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    nk_query_font_glyph_f query;

    nk_handle texture;

#endif
};

#ifdef NK_INCLUDE_FONT_BAKING
enum nk_font_coord_type {
    NK_COORD_UV,
    NK_COORD_PIXEL
};

struct nk_font;
struct nk_baked_font {
    float height;

    float ascent, descent;

    nk_rune glyph_offset;

    nk_rune glyph_count;

    const nk_rune *ranges;

};

struct nk_font_config {
    struct nk_font_config *next;

    void *ttf_blob;

    nk_size ttf_size;

    unsigned char ttf_data_owned_by_atlas;

    unsigned char merge_mode;

    unsigned char pixel_snap;

    unsigned char oversample_v, oversample_h;

    unsigned char padding[3];

    float size;

    enum nk_font_coord_type coord_type;

    struct nk_vec2 spacing;

    const nk_rune *range;

    struct nk_baked_font *font;

    nk_rune fallback_glyph;

    struct nk_font_config *n;
    struct nk_font_config *p;
};

struct nk_font_glyph {
    nk_rune codepoint;
    float xadvance;
    float x0, y0, x1, y1, w, h;
    float u0, v0, u1, v1;
};

struct nk_font {
    struct nk_font *next;
    struct nk_user_font handle;
    struct nk_baked_font info;
    float scale;
    struct nk_font_glyph *glyphs;
    const struct nk_font_glyph *fallback;
    nk_rune fallback_codepoint;
    nk_handle texture;
    struct nk_font_config *config;
};

enum nk_font_atlas_format {
    NK_FONT_ATLAS_ALPHA8,
    NK_FONT_ATLAS_RGBA32
};

struct nk_font_atlas {
    void *pixel;
    int tex_width;
    int tex_height;

    struct nk_allocator permanent;
    struct nk_allocator temporary;

    struct nk_recti custom;
    struct nk_cursor cursors[NK_CURSOR_COUNT];

    int glyph_count;
    struct nk_font_glyph *glyphs;
    struct nk_font *default_font;
    struct nk_font *fonts;
    struct nk_font_config *config;
    int font_num;
};

NK_API const nk_rune *nk_font_default_glyph_ranges(void);
NK_API const nk_rune *nk_font_chinese_glyph_ranges(void);
NK_API const nk_rune *nk_font_cyrillic_glyph_ranges(void);
NK_API const nk_rune *nk_font_korean_glyph_ranges(void);

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void nk_font_atlas_init_default(struct nk_font_atlas*);
#endif
NK_API void nk_font_atlas_init(struct nk_font_atlas*, struct nk_allocator*);
NK_API void nk_font_atlas_init_custom(struct nk_font_atlas*, struct nk_allocator *persistent, struct nk_allocator *transient);
NK_API void nk_font_atlas_begin(struct nk_font_atlas*);
NK_API struct nk_font_config nk_font_config(float pixel_height);
NK_API struct nk_font *nk_font_atlas_add(struct nk_font_atlas*, const struct nk_font_config*);
#ifdef NK_INCLUDE_DEFAULT_FONT
NK_API struct nk_font* nk_font_atlas_add_default(struct nk_font_atlas*, float height, const struct nk_font_config*);
#endif
NK_API struct nk_font* nk_font_atlas_add_from_memory(struct nk_font_atlas *atlas, void *memory, nk_size size, float height, const struct nk_font_config *config);
#ifdef NK_INCLUDE_STANDARD_IO
NK_API struct nk_font* nk_font_atlas_add_from_file(struct nk_font_atlas *atlas, const char *file_path, float height, const struct nk_font_config*);
#endif
NK_API struct nk_font *nk_font_atlas_add_compressed(struct nk_font_atlas*, void *memory, nk_size size, float height, const struct nk_font_config*);
NK_API struct nk_font* nk_font_atlas_add_compressed_base85(struct nk_font_atlas*, const char *data, float height, const struct nk_font_config *config);
NK_API const void* nk_font_atlas_bake(struct nk_font_atlas*, int *width, int *height, enum nk_font_atlas_format);
NK_API void nk_font_atlas_end(struct nk_font_atlas*, nk_handle tex, struct nk_draw_null_texture*);
NK_API const struct nk_font_glyph* nk_font_find_glyph(struct nk_font*, nk_rune unicode);
NK_API void nk_font_atlas_cleanup(struct nk_font_atlas *atlas);
NK_API void nk_font_atlas_clear(struct nk_font_atlas*);

#endif

struct nk_memory_status {
    void *memory;
    unsigned int type;
    nk_size size;
    nk_size allocated;
    nk_size needed;
    nk_size calls;
};

enum nk_allocation_type {
    NK_BUFFER_FIXED,
    NK_BUFFER_DYNAMIC
};

enum nk_buffer_allocation_type {
    NK_BUFFER_FRONT,
    NK_BUFFER_BACK,
    NK_BUFFER_MAX
};

struct nk_buffer_marker {
    nk_bool active;
    nk_size offset;
};

struct nk_memory {void *ptr;nk_size size;};
struct nk_buffer {
    struct nk_buffer_marker marker[NK_BUFFER_MAX];

    struct nk_allocator pool;

    enum nk_allocation_type type;

    struct nk_memory memory;

    float grow_factor;

    nk_size allocated;

    nk_size needed;

    nk_size calls;

    nk_size size;

};

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void nk_buffer_init_default(struct nk_buffer*);
#endif
NK_API void nk_buffer_init(struct nk_buffer*, const struct nk_allocator*, nk_size size);
NK_API void nk_buffer_init_fixed(struct nk_buffer*, void *memory, nk_size size);
NK_API void nk_buffer_info(struct nk_memory_status*, struct nk_buffer*);
NK_API void nk_buffer_push(struct nk_buffer*, enum nk_buffer_allocation_type type, const void *memory, nk_size size, nk_size align);
NK_API void nk_buffer_mark(struct nk_buffer*, enum nk_buffer_allocation_type type);
NK_API void nk_buffer_reset(struct nk_buffer*, enum nk_buffer_allocation_type type);
NK_API void nk_buffer_clear(struct nk_buffer*);
NK_API void nk_buffer_free(struct nk_buffer*);
NK_API void *nk_buffer_memory(struct nk_buffer*);
NK_API const void *nk_buffer_memory_const(const struct nk_buffer*);
NK_API nk_size nk_buffer_total(struct nk_buffer*);

struct nk_str {
    struct nk_buffer buffer;
    int len;
};

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void nk_str_init_default(struct nk_str*);
#endif
NK_API void nk_str_init(struct nk_str*, const struct nk_allocator*, nk_size size);
NK_API void nk_str_init_fixed(struct nk_str*, void *memory, nk_size size);
NK_API void nk_str_clear(struct nk_str*);
NK_API void nk_str_free(struct nk_str*);

NK_API int nk_str_append_text_char(struct nk_str*, const char*, int);
NK_API int nk_str_append_str_char(struct nk_str*, const char*);
NK_API int nk_str_append_text_utf8(struct nk_str*, const char*, int);
NK_API int nk_str_append_str_utf8(struct nk_str*, const char*);
NK_API int nk_str_append_text_runes(struct nk_str*, const nk_rune*, int);
NK_API int nk_str_append_str_runes(struct nk_str*, const nk_rune*);

NK_API int nk_str_insert_at_char(struct nk_str*, int pos, const char*, int);
NK_API int nk_str_insert_at_rune(struct nk_str*, int pos, const char*, int);

NK_API int nk_str_insert_text_char(struct nk_str*, int pos, const char*, int);
NK_API int nk_str_insert_str_char(struct nk_str*, int pos, const char*);
NK_API int nk_str_insert_text_utf8(struct nk_str*, int pos, const char*, int);
NK_API int nk_str_insert_str_utf8(struct nk_str*, int pos, const char*);
NK_API int nk_str_insert_text_runes(struct nk_str*, int pos, const nk_rune*, int);
NK_API int nk_str_insert_str_runes(struct nk_str*, int pos, const nk_rune*);

NK_API void nk_str_remove_chars(struct nk_str*, int len);
NK_API void nk_str_remove_runes(struct nk_str *str, int len);
NK_API void nk_str_delete_chars(struct nk_str*, int pos, int len);
NK_API void nk_str_delete_runes(struct nk_str*, int pos, int len);

NK_API char *nk_str_at_char(struct nk_str*, int pos);
NK_API char *nk_str_at_rune(struct nk_str*, int pos, nk_rune *unicode, int *len);
NK_API nk_rune nk_str_rune_at(const struct nk_str*, int pos);
NK_API const char *nk_str_at_char_const(const struct nk_str*, int pos);
NK_API const char *nk_str_at_const(const struct nk_str*, int pos, nk_rune *unicode, int *len);

NK_API char *nk_str_get(struct nk_str*);
NK_API const char *nk_str_get_const(const struct nk_str*);
NK_API int nk_str_len(struct nk_str*);
NK_API int nk_str_len_char(struct nk_str*);

#ifndef NK_TEXTEDIT_UNDOSTATECOUNT
#define NK_TEXTEDIT_UNDOSTATECOUNT     99
#endif

#ifndef NK_TEXTEDIT_UNDOCHARCOUNT
#define NK_TEXTEDIT_UNDOCHARCOUNT      999
#endif

struct nk_text_edit;
struct nk_clipboard {
    nk_handle userdata;
    nk_plugin_paste paste;
    nk_plugin_copy copy;
};

struct nk_text_undo_record {
   int where;
   short insert_length;
   short delete_length;
   short char_storage;
};

struct nk_text_undo_state {
   struct nk_text_undo_record undo_rec[NK_TEXTEDIT_UNDOSTATECOUNT];
   nk_rune undo_char[NK_TEXTEDIT_UNDOCHARCOUNT];
   short undo_point;
   short redo_point;
   short undo_char_point;
   short redo_char_point;
};

enum nk_text_edit_type {
    NK_TEXT_EDIT_SINGLE_LINE,
    NK_TEXT_EDIT_MULTI_LINE
};

enum nk_text_edit_mode {
    NK_TEXT_EDIT_MODE_VIEW,
    NK_TEXT_EDIT_MODE_INSERT,
    NK_TEXT_EDIT_MODE_REPLACE
};

struct nk_text_edit {
    struct nk_clipboard clip;
    struct nk_str string;
    nk_plugin_filter filter;
    struct nk_vec2 scrollbar;

    int cursor;
    int select_start;
    int select_end;
    unsigned char mode;
    unsigned char cursor_at_end_of_line;
    unsigned char initialized;
    unsigned char has_preferred_x;
    unsigned char single_line;
    unsigned char active;
    unsigned char padding1;
    float preferred_x;
    struct nk_text_undo_state undo;
};

NK_API nk_bool nk_filter_default(const struct nk_text_edit*, nk_rune unicode);
NK_API nk_bool nk_filter_ascii(const struct nk_text_edit*, nk_rune unicode);
NK_API nk_bool nk_filter_float(const struct nk_text_edit*, nk_rune unicode);
NK_API nk_bool nk_filter_decimal(const struct nk_text_edit*, nk_rune unicode);
NK_API nk_bool nk_filter_hex(const struct nk_text_edit*, nk_rune unicode);
NK_API nk_bool nk_filter_oct(const struct nk_text_edit*, nk_rune unicode);
NK_API nk_bool nk_filter_binary(const struct nk_text_edit*, nk_rune unicode);

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void nk_textedit_init_default(struct nk_text_edit*);
#endif
NK_API void nk_textedit_init(struct nk_text_edit*, struct nk_allocator*, nk_size size);
NK_API void nk_textedit_init_fixed(struct nk_text_edit*, void *memory, nk_size size);
NK_API void nk_textedit_free(struct nk_text_edit*);
NK_API void nk_textedit_text(struct nk_text_edit*, const char*, int total_len);
NK_API void nk_textedit_delete(struct nk_text_edit*, int where, int len);
NK_API void nk_textedit_delete_selection(struct nk_text_edit*);
NK_API void nk_textedit_select_all(struct nk_text_edit*);
NK_API nk_bool nk_textedit_cut(struct nk_text_edit*);
NK_API nk_bool nk_textedit_paste(struct nk_text_edit*, char const*, int len);
NK_API void nk_textedit_undo(struct nk_text_edit*);
NK_API void nk_textedit_redo(struct nk_text_edit*);

enum nk_command_type {
    NK_COMMAND_NOP,
    NK_COMMAND_SCISSOR,
    NK_COMMAND_LINE,
    NK_COMMAND_CURVE,
    NK_COMMAND_RECT,
    NK_COMMAND_RECT_FILLED,
    NK_COMMAND_RECT_MULTI_COLOR,
    NK_COMMAND_CIRCLE,
    NK_COMMAND_CIRCLE_FILLED,
    NK_COMMAND_ARC,
    NK_COMMAND_ARC_FILLED,
    NK_COMMAND_TRIANGLE,
    NK_COMMAND_TRIANGLE_FILLED,
    NK_COMMAND_POLYGON,
    NK_COMMAND_POLYGON_FILLED,
    NK_COMMAND_POLYLINE,
    NK_COMMAND_TEXT,
    NK_COMMAND_IMAGE,
    NK_COMMAND_CUSTOM
};

struct nk_command {
    enum nk_command_type type;
    nk_size next;
#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_handle userdata;
#endif
};

struct nk_command_scissor {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
};

struct nk_command_line {
    struct nk_command header;
    unsigned short line_thickness;
    struct nk_vec2i begin;
    struct nk_vec2i end;
    struct nk_color color;
};

struct nk_command_curve {
    struct nk_command header;
    unsigned short line_thickness;
    struct nk_vec2i begin;
    struct nk_vec2i end;
    struct nk_vec2i ctrl[2];
    struct nk_color color;
};

struct nk_command_rect {
    struct nk_command header;
    unsigned short rounding;
    unsigned short line_thickness;
    short x, y;
    unsigned short w, h;
    struct nk_color color;
};

struct nk_command_rect_filled {
    struct nk_command header;
    unsigned short rounding;
    short x, y;
    unsigned short w, h;
    struct nk_color color;
};

struct nk_command_rect_multi_color {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
    struct nk_color left;
    struct nk_color top;
    struct nk_color bottom;
    struct nk_color right;
};

struct nk_command_triangle {
    struct nk_command header;
    unsigned short line_thickness;
    struct nk_vec2i a;
    struct nk_vec2i b;
    struct nk_vec2i c;
    struct nk_color color;
};

struct nk_command_triangle_filled {
    struct nk_command header;
    struct nk_vec2i a;
    struct nk_vec2i b;
    struct nk_vec2i c;
    struct nk_color color;
};

struct nk_command_circle {
    struct nk_command header;
    short x, y;
    unsigned short line_thickness;
    unsigned short w, h;
    struct nk_color color;
};

struct nk_command_circle_filled {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
    struct nk_color color;
};

struct nk_command_arc {
    struct nk_command header;
    short cx, cy;
    unsigned short r;
    unsigned short line_thickness;
    float a[2];
    struct nk_color color;
};

struct nk_command_arc_filled {
    struct nk_command header;
    short cx, cy;
    unsigned short r;
    float a[2];
    struct nk_color color;
};

struct nk_command_polygon {
    struct nk_command header;
    struct nk_color color;
    unsigned short line_thickness;
    unsigned short point_count;
    struct nk_vec2i points[1];
};

struct nk_command_polygon_filled {
    struct nk_command header;
    struct nk_color color;
    unsigned short point_count;
    struct nk_vec2i points[1];
};

struct nk_command_polyline {
    struct nk_command header;
    struct nk_color color;
    unsigned short line_thickness;
    unsigned short point_count;
    struct nk_vec2i points[1];
};

struct nk_command_image {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
    struct nk_image img;
    struct nk_color col;
};

typedef void (*nk_command_custom_callback)(void *canvas, short x,short y,
    unsigned short w, unsigned short h, nk_handle callback_data);
struct nk_command_custom {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
    nk_handle callback_data;
    nk_command_custom_callback callback;
};

struct nk_command_text {
    struct nk_command header;
    const struct nk_user_font *font;
    struct nk_color background;
    struct nk_color foreground;
    short x, y;
    unsigned short w, h;
    float height;
    int length;
    char string[1];
};

enum nk_command_clipping {
    NK_CLIPPING_OFF = nk_false,
    NK_CLIPPING_ON = nk_true
};

struct nk_command_buffer {
    struct nk_buffer *base;
    struct nk_rect clip;
    int use_clipping;
    nk_handle userdata;
    nk_size begin, end, last;
};

NK_API void nk_stroke_line(struct nk_command_buffer *b, float x0, float y0, float x1, float y1, float line_thickness, struct nk_color);
NK_API void nk_stroke_curve(struct nk_command_buffer*, float, float, float, float, float, float, float, float, float line_thickness, struct nk_color);
NK_API void nk_stroke_rect(struct nk_command_buffer*, struct nk_rect, float rounding, float line_thickness, struct nk_color);
NK_API void nk_stroke_circle(struct nk_command_buffer*, struct nk_rect, float line_thickness, struct nk_color);
NK_API void nk_stroke_arc(struct nk_command_buffer*, float cx, float cy, float radius, float a_min, float a_max, float line_thickness, struct nk_color);
NK_API void nk_stroke_triangle(struct nk_command_buffer*, float, float, float, float, float, float, float line_thichness, struct nk_color);
NK_API void nk_stroke_polyline(struct nk_command_buffer*, float *points, int point_count, float line_thickness, struct nk_color col);
NK_API void nk_stroke_polygon(struct nk_command_buffer*, float*, int point_count, float line_thickness, struct nk_color);

NK_API void nk_fill_rect(struct nk_command_buffer*, struct nk_rect, float rounding, struct nk_color);
NK_API void nk_fill_rect_multi_color(struct nk_command_buffer*, struct nk_rect, struct nk_color left, struct nk_color top, struct nk_color right, struct nk_color bottom);
NK_API void nk_fill_circle(struct nk_command_buffer*, struct nk_rect, struct nk_color);
NK_API void nk_fill_arc(struct nk_command_buffer*, float cx, float cy, float radius, float a_min, float a_max, struct nk_color);
NK_API void nk_fill_triangle(struct nk_command_buffer*, float x0, float y0, float x1, float y1, float x2, float y2, struct nk_color);
NK_API void nk_fill_polygon(struct nk_command_buffer*, float*, int point_count, struct nk_color);

NK_API void nk_draw_image(struct nk_command_buffer*, struct nk_rect, const struct nk_image*, struct nk_color);
NK_API void nk_draw_nine_slice(struct nk_command_buffer*, struct nk_rect, const struct nk_nine_slice*, struct nk_color);
NK_API void nk_draw_text(struct nk_command_buffer*, struct nk_rect, const char *text, int len, const struct nk_user_font*, struct nk_color, struct nk_color);
NK_API void nk_push_scissor(struct nk_command_buffer*, struct nk_rect);
NK_API void nk_push_custom(struct nk_command_buffer*, struct nk_rect, nk_command_custom_callback, nk_handle usr);

struct nk_mouse_button {
    nk_bool down;
    unsigned int clicked;
    struct nk_vec2 clicked_pos;
};
struct nk_mouse {
    struct nk_mouse_button buttons[NK_BUTTON_MAX];
    struct nk_vec2 pos;
#ifdef NK_BUTTON_TRIGGER_ON_RELEASE
    struct nk_vec2 down_pos;
#endif
    struct nk_vec2 prev;
    struct nk_vec2 delta;
    struct nk_vec2 scroll_delta;
    unsigned char grab;
    unsigned char grabbed;
    unsigned char ungrab;
};

struct nk_key {
    nk_bool down;
    unsigned int clicked;
};
struct nk_keyboard {
    struct nk_key keys[NK_KEY_MAX];
    char text[NK_INPUT_MAX];
    int text_len;
};

struct nk_input {
    struct nk_keyboard keyboard;
    struct nk_mouse mouse;
};

NK_API nk_bool nk_input_has_mouse_click(const struct nk_input*, enum nk_buttons);
NK_API nk_bool nk_input_has_mouse_click_in_rect(const struct nk_input*, enum nk_buttons, struct nk_rect);
NK_API nk_bool nk_input_has_mouse_click_in_button_rect(const struct nk_input*, enum nk_buttons, struct nk_rect);
NK_API nk_bool nk_input_has_mouse_click_down_in_rect(const struct nk_input*, enum nk_buttons, struct nk_rect, nk_bool down);
NK_API nk_bool nk_input_is_mouse_click_in_rect(const struct nk_input*, enum nk_buttons, struct nk_rect);
NK_API nk_bool nk_input_is_mouse_click_down_in_rect(const struct nk_input *i, enum nk_buttons id, struct nk_rect b, nk_bool down);
NK_API nk_bool nk_input_any_mouse_click_in_rect(const struct nk_input*, struct nk_rect);
NK_API nk_bool nk_input_is_mouse_prev_hovering_rect(const struct nk_input*, struct nk_rect);
NK_API nk_bool nk_input_is_mouse_hovering_rect(const struct nk_input*, struct nk_rect);
NK_API nk_bool nk_input_mouse_clicked(const struct nk_input*, enum nk_buttons, struct nk_rect);
NK_API nk_bool nk_input_is_mouse_down(const struct nk_input*, enum nk_buttons);
NK_API nk_bool nk_input_is_mouse_pressed(const struct nk_input*, enum nk_buttons);
NK_API nk_bool nk_input_is_mouse_released(const struct nk_input*, enum nk_buttons);
NK_API nk_bool nk_input_is_key_pressed(const struct nk_input*, enum nk_keys);
NK_API nk_bool nk_input_is_key_released(const struct nk_input*, enum nk_keys);
NK_API nk_bool nk_input_is_key_down(const struct nk_input*, enum nk_keys);

#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#ifdef NK_UINT_DRAW_INDEX
typedef nk_uint nk_draw_index;
#else
typedef nk_ushort nk_draw_index;
#endif
enum nk_draw_list_stroke {
    NK_STROKE_OPEN = nk_false,

    NK_STROKE_CLOSED = nk_true

};

enum nk_draw_vertex_layout_attribute {
    NK_VERTEX_POSITION,
    NK_VERTEX_COLOR,
    NK_VERTEX_TEXCOORD,
    NK_VERTEX_ATTRIBUTE_COUNT
};

enum nk_draw_vertex_layout_format {
    NK_FORMAT_SCHAR,
    NK_FORMAT_SSHORT,
    NK_FORMAT_SINT,
    NK_FORMAT_UCHAR,
    NK_FORMAT_USHORT,
    NK_FORMAT_UINT,
    NK_FORMAT_FLOAT,
    NK_FORMAT_DOUBLE,

NK_FORMAT_COLOR_BEGIN,
    NK_FORMAT_R8G8B8 = NK_FORMAT_COLOR_BEGIN,
    NK_FORMAT_R16G15B16,
    NK_FORMAT_R32G32B32,

    NK_FORMAT_R8G8B8A8,
    NK_FORMAT_B8G8R8A8,
    NK_FORMAT_R16G15B16A16,
    NK_FORMAT_R32G32B32A32,
    NK_FORMAT_R32G32B32A32_FLOAT,
    NK_FORMAT_R32G32B32A32_DOUBLE,

    NK_FORMAT_RGB32,
    NK_FORMAT_RGBA32,
NK_FORMAT_COLOR_END = NK_FORMAT_RGBA32,
    NK_FORMAT_COUNT
};

#define NK_VERTEX_LAYOUT_END NK_VERTEX_ATTRIBUTE_COUNT,NK_FORMAT_COUNT,0
struct nk_draw_vertex_layout_element {
    enum nk_draw_vertex_layout_attribute attribute;
    enum nk_draw_vertex_layout_format format;
    nk_size offset;
};

struct nk_draw_command {
    unsigned int elem_count;

    struct nk_rect clip_rect;

    nk_handle texture;

#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_handle userdata;
#endif
};

struct nk_draw_list {
    struct nk_rect clip_rect;
    struct nk_vec2 circle_vtx[12];
    struct nk_convert_config config;

    struct nk_buffer *buffer;
    struct nk_buffer *vertices;
    struct nk_buffer *elements;

    unsigned int element_count;
    unsigned int vertex_count;
    unsigned int cmd_count;
    nk_size cmd_offset;

    unsigned int path_count;
    unsigned int path_offset;

    enum nk_anti_aliasing line_AA;
    enum nk_anti_aliasing shape_AA;

#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_handle userdata;
#endif
};

NK_API void nk_draw_list_init(struct nk_draw_list*);
NK_API void nk_draw_list_setup(struct nk_draw_list*, const struct nk_convert_config*, struct nk_buffer *cmds, struct nk_buffer *vertices, struct nk_buffer *elements, enum nk_anti_aliasing line_aa,enum nk_anti_aliasing shape_aa);

#define nk_draw_list_foreach(cmd, can, b) for((cmd)=nk__draw_list_begin(can, b); (cmd)!=0; (cmd)=nk__draw_list_next(cmd, b, can))
NK_API const struct nk_draw_command* nk__draw_list_begin(const struct nk_draw_list*, const struct nk_buffer*);
NK_API const struct nk_draw_command* nk__draw_list_next(const struct nk_draw_command*, const struct nk_buffer*, const struct nk_draw_list*);
NK_API const struct nk_draw_command* nk__draw_list_end(const struct nk_draw_list*, const struct nk_buffer*);

NK_API void nk_draw_list_path_clear(struct nk_draw_list*);
NK_API void nk_draw_list_path_line_to(struct nk_draw_list*, struct nk_vec2 pos);
NK_API void nk_draw_list_path_arc_to_fast(struct nk_draw_list*, struct nk_vec2 center, float radius, int a_min, int a_max);
NK_API void nk_draw_list_path_arc_to(struct nk_draw_list*, struct nk_vec2 center, float radius, float a_min, float a_max, unsigned int segments);
NK_API void nk_draw_list_path_rect_to(struct nk_draw_list*, struct nk_vec2 a, struct nk_vec2 b, float rounding);
NK_API void nk_draw_list_path_curve_to(struct nk_draw_list*, struct nk_vec2 p2, struct nk_vec2 p3, struct nk_vec2 p4, unsigned int num_segments);
NK_API void nk_draw_list_path_fill(struct nk_draw_list*, struct nk_color);
NK_API void nk_draw_list_path_stroke(struct nk_draw_list*, struct nk_color, enum nk_draw_list_stroke closed, float thickness);

NK_API void nk_draw_list_stroke_line(struct nk_draw_list*, struct nk_vec2 a, struct nk_vec2 b, struct nk_color, float thickness);
NK_API void nk_draw_list_stroke_rect(struct nk_draw_list*, struct nk_rect rect, struct nk_color, float rounding, float thickness);
NK_API void nk_draw_list_stroke_triangle(struct nk_draw_list*, struct nk_vec2 a, struct nk_vec2 b, struct nk_vec2 c, struct nk_color, float thickness);
NK_API void nk_draw_list_stroke_circle(struct nk_draw_list*, struct nk_vec2 center, float radius, struct nk_color, unsigned int segs, float thickness);
NK_API void nk_draw_list_stroke_curve(struct nk_draw_list*, struct nk_vec2 p0, struct nk_vec2 cp0, struct nk_vec2 cp1, struct nk_vec2 p1, struct nk_color, unsigned int segments, float thickness);
NK_API void nk_draw_list_stroke_poly_line(struct nk_draw_list*, const struct nk_vec2 *pnts, const unsigned int cnt, struct nk_color, enum nk_draw_list_stroke, float thickness, enum nk_anti_aliasing);

NK_API void nk_draw_list_fill_rect(struct nk_draw_list*, struct nk_rect rect, struct nk_color, float rounding);
NK_API void nk_draw_list_fill_rect_multi_color(struct nk_draw_list*, struct nk_rect rect, struct nk_color left, struct nk_color top, struct nk_color right, struct nk_color bottom);
NK_API void nk_draw_list_fill_triangle(struct nk_draw_list*, struct nk_vec2 a, struct nk_vec2 b, struct nk_vec2 c, struct nk_color);
NK_API void nk_draw_list_fill_circle(struct nk_draw_list*, struct nk_vec2 center, float radius, struct nk_color col, unsigned int segs);
NK_API void nk_draw_list_fill_poly_convex(struct nk_draw_list*, const struct nk_vec2 *points, const unsigned int count, struct nk_color, enum nk_anti_aliasing);

NK_API void nk_draw_list_add_image(struct nk_draw_list*, struct nk_image texture, struct nk_rect rect, struct nk_color);
NK_API void nk_draw_list_add_text(struct nk_draw_list*, const struct nk_user_font*, struct nk_rect, const char *text, int len, float font_height, struct nk_color);
#ifdef NK_INCLUDE_COMMAND_USERDATA
NK_API void nk_draw_list_push_userdata(struct nk_draw_list*, nk_handle userdata);
#endif

#endif

enum nk_style_item_type {
    NK_STYLE_ITEM_COLOR,
    NK_STYLE_ITEM_IMAGE,
    NK_STYLE_ITEM_NINE_SLICE
};

union nk_style_item_data {
    struct nk_color color;
    struct nk_image image;
    struct nk_nine_slice slice;
};

struct nk_style_item {
    enum nk_style_item_type type;
    union nk_style_item_data data;
};

struct nk_style_text {
    struct nk_color color;
    struct nk_vec2 padding;
};

struct nk_style_button {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    struct nk_color text_background;
    struct nk_color text_normal;
    struct nk_color text_hover;
    struct nk_color text_active;
    nk_flags text_alignment;

    float border;
    float rounding;
    struct nk_vec2 padding;
    struct nk_vec2 image_padding;
    struct nk_vec2 touch_padding;

    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle userdata);
    void(*draw_end)(struct nk_command_buffer*, nk_handle userdata);
};

struct nk_style_toggle {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    struct nk_style_item cursor_normal;
    struct nk_style_item cursor_hover;

    struct nk_color text_normal;
    struct nk_color text_hover;
    struct nk_color text_active;
    struct nk_color text_background;
    nk_flags text_alignment;

    struct nk_vec2 padding;
    struct nk_vec2 touch_padding;
    float spacing;
    float border;

    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_selectable {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item pressed;

    struct nk_style_item normal_active;
    struct nk_style_item hover_active;
    struct nk_style_item pressed_active;

    struct nk_color text_normal;
    struct nk_color text_hover;
    struct nk_color text_pressed;

    struct nk_color text_normal_active;
    struct nk_color text_hover_active;
    struct nk_color text_pressed_active;
    struct nk_color text_background;
    nk_flags text_alignment;

    float rounding;
    struct nk_vec2 padding;
    struct nk_vec2 touch_padding;
    struct nk_vec2 image_padding;

    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_slider {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    struct nk_color bar_normal;
    struct nk_color bar_hover;
    struct nk_color bar_active;
    struct nk_color bar_filled;

    struct nk_style_item cursor_normal;
    struct nk_style_item cursor_hover;
    struct nk_style_item cursor_active;

    float border;
    float rounding;
    float bar_height;
    struct nk_vec2 padding;
    struct nk_vec2 spacing;
    struct nk_vec2 cursor_size;

    int show_buttons;
    struct nk_style_button inc_button;
    struct nk_style_button dec_button;
    enum nk_symbol_type inc_symbol;
    enum nk_symbol_type dec_symbol;

    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_progress {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    struct nk_style_item cursor_normal;
    struct nk_style_item cursor_hover;
    struct nk_style_item cursor_active;
    struct nk_color cursor_border_color;

    float rounding;
    float border;
    float cursor_border;
    float cursor_rounding;
    struct nk_vec2 padding;

    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_scrollbar {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    struct nk_style_item cursor_normal;
    struct nk_style_item cursor_hover;
    struct nk_style_item cursor_active;
    struct nk_color cursor_border_color;

    float border;
    float rounding;
    float border_cursor;
    float rounding_cursor;
    struct nk_vec2 padding;

    int show_buttons;
    struct nk_style_button inc_button;
    struct nk_style_button dec_button;
    enum nk_symbol_type inc_symbol;
    enum nk_symbol_type dec_symbol;

    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_edit {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;
    struct nk_style_scrollbar scrollbar;

    struct nk_color cursor_normal;
    struct nk_color cursor_hover;
    struct nk_color cursor_text_normal;
    struct nk_color cursor_text_hover;

    struct nk_color text_normal;
    struct nk_color text_hover;
    struct nk_color text_active;

    struct nk_color selected_normal;
    struct nk_color selected_hover;
    struct nk_color selected_text_normal;
    struct nk_color selected_text_hover;

    float border;
    float rounding;
    float cursor_size;
    struct nk_vec2 scrollbar_size;
    struct nk_vec2 padding;
    float row_padding;
};

struct nk_style_property {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    struct nk_color label_normal;
    struct nk_color label_hover;
    struct nk_color label_active;

    enum nk_symbol_type sym_left;
    enum nk_symbol_type sym_right;

    float border;
    float rounding;
    struct nk_vec2 padding;

    struct nk_style_edit edit;
    struct nk_style_button inc_button;
    struct nk_style_button dec_button;

    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_chart {

    struct nk_style_item background;
    struct nk_color border_color;
    struct nk_color selected_color;
    struct nk_color color;

    float border;
    float rounding;
    struct nk_vec2 padding;
};

struct nk_style_combo {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    struct nk_color label_normal;
    struct nk_color label_hover;
    struct nk_color label_active;

    struct nk_color symbol_normal;
    struct nk_color symbol_hover;
    struct nk_color symbol_active;

    struct nk_style_button button;
    enum nk_symbol_type sym_normal;
    enum nk_symbol_type sym_hover;
    enum nk_symbol_type sym_active;

    float border;
    float rounding;
    struct nk_vec2 content_padding;
    struct nk_vec2 button_padding;
    struct nk_vec2 spacing;
};

struct nk_style_tab {

    struct nk_style_item background;
    struct nk_color border_color;
    struct nk_color text;

    struct nk_style_button tab_maximize_button;
    struct nk_style_button tab_minimize_button;
    struct nk_style_button node_maximize_button;
    struct nk_style_button node_minimize_button;
    enum nk_symbol_type sym_minimize;
    enum nk_symbol_type sym_maximize;

    float border;
    float rounding;
    float indent;
    struct nk_vec2 padding;
    struct nk_vec2 spacing;
};

enum nk_style_header_align {
    NK_HEADER_LEFT,
    NK_HEADER_RIGHT
};
struct nk_style_window_header {

    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;

    struct nk_style_button close_button;
    struct nk_style_button minimize_button;
    enum nk_symbol_type close_symbol;
    enum nk_symbol_type minimize_symbol;
    enum nk_symbol_type maximize_symbol;

    struct nk_color label_normal;
    struct nk_color label_hover;
    struct nk_color label_active;

    enum nk_style_header_align align;
    struct nk_vec2 padding;
    struct nk_vec2 label_padding;
    struct nk_vec2 spacing;
};

struct nk_style_window {
    struct nk_style_window_header header;
    struct nk_style_item fixed_background;
    struct nk_color background;

    struct nk_color border_color;
    struct nk_color popup_border_color;
    struct nk_color combo_border_color;
    struct nk_color contextual_border_color;
    struct nk_color menu_border_color;
    struct nk_color group_border_color;
    struct nk_color tooltip_border_color;
    struct nk_style_item scaler;

    float border;
    float combo_border;
    float contextual_border;
    float menu_border;
    float group_border;
    float tooltip_border;
    float popup_border;
    float min_row_height_padding;

    float rounding;
    struct nk_vec2 spacing;
    struct nk_vec2 scrollbar_size;
    struct nk_vec2 min_size;

    struct nk_vec2 padding;
    struct nk_vec2 group_padding;
    struct nk_vec2 popup_padding;
    struct nk_vec2 combo_padding;
    struct nk_vec2 contextual_padding;
    struct nk_vec2 menu_padding;
    struct nk_vec2 tooltip_padding;
};

struct nk_style {
    const struct nk_user_font *font;
    const struct nk_cursor *cursors[NK_CURSOR_COUNT];
    const struct nk_cursor *cursor_active;
    struct nk_cursor *cursor_last;
    int cursor_visible;

    struct nk_style_text text;
    struct nk_style_button button;
    struct nk_style_button contextual_button;
    struct nk_style_button menu_button;
    struct nk_style_toggle option;
    struct nk_style_toggle checkbox;
    struct nk_style_selectable selectable;
    struct nk_style_slider slider;
    struct nk_style_progress progress;
    struct nk_style_property property;
    struct nk_style_edit edit;
    struct nk_style_chart chart;
    struct nk_style_scrollbar scrollh;
    struct nk_style_scrollbar scrollv;
    struct nk_style_tab tab;
    struct nk_style_combo combo;
    struct nk_style_window window;
};

NK_API struct nk_style_item nk_style_item_color(struct nk_color);
NK_API struct nk_style_item nk_style_item_image(struct nk_image img);
NK_API struct nk_style_item nk_style_item_nine_slice(struct nk_nine_slice slice);
NK_API struct nk_style_item nk_style_item_hide(void);

#ifndef NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS
#define NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS 16
#endif
#ifndef NK_CHART_MAX_SLOT
#define NK_CHART_MAX_SLOT 4
#endif

enum nk_panel_type {
    NK_PANEL_NONE       = 0,
    NK_PANEL_WINDOW     = NK_FLAG(0),
    NK_PANEL_GROUP      = NK_FLAG(1),
    NK_PANEL_POPUP      = NK_FLAG(2),
    NK_PANEL_CONTEXTUAL = NK_FLAG(4),
    NK_PANEL_COMBO      = NK_FLAG(5),
    NK_PANEL_MENU       = NK_FLAG(6),
    NK_PANEL_TOOLTIP    = NK_FLAG(7)
};
enum nk_panel_set {
    NK_PANEL_SET_NONBLOCK = NK_PANEL_CONTEXTUAL|NK_PANEL_COMBO|NK_PANEL_MENU|NK_PANEL_TOOLTIP,
    NK_PANEL_SET_POPUP = NK_PANEL_SET_NONBLOCK|NK_PANEL_POPUP,
    NK_PANEL_SET_SUB = NK_PANEL_SET_POPUP|NK_PANEL_GROUP
};

struct nk_chart_slot {
    enum nk_chart_type type;
    struct nk_color color;
    struct nk_color highlight;
    float min, max, range;
    int count;
    struct nk_vec2 last;
    int index;
};

struct nk_chart {
    int slot;
    float x, y, w, h;
    struct nk_chart_slot slots[NK_CHART_MAX_SLOT];
};

enum nk_panel_row_layout_type {
    NK_LAYOUT_DYNAMIC_FIXED = 0,
    NK_LAYOUT_DYNAMIC_ROW,
    NK_LAYOUT_DYNAMIC_FREE,
    NK_LAYOUT_DYNAMIC,
    NK_LAYOUT_STATIC_FIXED,
    NK_LAYOUT_STATIC_ROW,
    NK_LAYOUT_STATIC_FREE,
    NK_LAYOUT_STATIC,
    NK_LAYOUT_TEMPLATE,
    NK_LAYOUT_COUNT
};
struct nk_row_layout {
    enum nk_panel_row_layout_type type;
    int index;
    float height;
    float min_height;
    int columns;
    const float *ratio;
    float item_width;
    float item_height;
    float item_offset;
    float filled;
    struct nk_rect item;
    int tree_depth;
    float templates[NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS];
};

struct nk_popup_buffer {
    nk_size begin;
    nk_size parent;
    nk_size last;
    nk_size end;
    nk_bool active;
};

struct nk_menu_state {
    float x, y, w, h;
    struct nk_scroll offset;
};

struct nk_panel {
    enum nk_panel_type type;
    nk_flags flags;
    struct nk_rect bounds;
    nk_uint *offset_x;
    nk_uint *offset_y;
    float at_x, at_y, max_x;
    float footer_height;
    float header_height;
    float border;
    unsigned int has_scrolling;
    struct nk_rect clip;
    struct nk_menu_state menu;
    struct nk_row_layout row;
    struct nk_chart chart;
    struct nk_command_buffer *buffer;
    struct nk_panel *parent;
};

#ifndef NK_WINDOW_MAX_NAME
#define NK_WINDOW_MAX_NAME 64
#endif

struct nk_table;
enum nk_window_flags {
    NK_WINDOW_PRIVATE       = NK_FLAG(11),
    NK_WINDOW_DYNAMIC       = NK_WINDOW_PRIVATE,

    NK_WINDOW_ROM           = NK_FLAG(12),

    NK_WINDOW_NOT_INTERACTIVE = NK_WINDOW_ROM|NK_WINDOW_NO_INPUT,

    NK_WINDOW_HIDDEN        = NK_FLAG(13),

    NK_WINDOW_CLOSED        = NK_FLAG(14),

    NK_WINDOW_MINIMIZED     = NK_FLAG(15),

    NK_WINDOW_REMOVE_ROM    = NK_FLAG(16)

};

struct nk_popup_state {
    struct nk_window *win;
    enum nk_panel_type type;
    struct nk_popup_buffer buf;
    nk_hash name;
    nk_bool active;
    unsigned combo_count;
    unsigned con_count, con_old;
    unsigned active_con;
    struct nk_rect header;
};

struct nk_edit_state {
    nk_hash name;
    unsigned int seq;
    unsigned int old;
    int active, prev;
    int cursor;
    int sel_start;
    int sel_end;
    struct nk_scroll scrollbar;
    unsigned char mode;
    unsigned char single_line;
};

struct nk_property_state {
    int active, prev;
    char buffer[NK_MAX_NUMBER_BUFFER];
    int length;
    int cursor;
    int select_start;
    int select_end;
    nk_hash name;
    unsigned int seq;
    unsigned int old;
    int state;
};

struct nk_window {
    unsigned int seq;
    nk_hash name;
    char name_string[NK_WINDOW_MAX_NAME];
    nk_flags flags;

    struct nk_rect bounds;
    struct nk_scroll scrollbar;
    struct nk_command_buffer buffer;
    struct nk_panel *layout;
    float scrollbar_hiding_timer;

    struct nk_property_state property;
    struct nk_popup_state popup;
    struct nk_edit_state edit;
    unsigned int scrolled;

    struct nk_table *tables;
    unsigned int table_count;

    struct nk_window *next;
    struct nk_window *prev;
    struct nk_window *parent;
};

#ifndef NK_BUTTON_BEHAVIOR_STACK_SIZE
#define NK_BUTTON_BEHAVIOR_STACK_SIZE 8
#endif

#ifndef NK_FONT_STACK_SIZE
#define NK_FONT_STACK_SIZE 8
#endif

#ifndef NK_STYLE_ITEM_STACK_SIZE
#define NK_STYLE_ITEM_STACK_SIZE 16
#endif

#ifndef NK_FLOAT_STACK_SIZE
#define NK_FLOAT_STACK_SIZE 32
#endif

#ifndef NK_VECTOR_STACK_SIZE
#define NK_VECTOR_STACK_SIZE 16
#endif

#ifndef NK_FLAGS_STACK_SIZE
#define NK_FLAGS_STACK_SIZE 32
#endif

#ifndef NK_COLOR_STACK_SIZE
#define NK_COLOR_STACK_SIZE 32
#endif

#define NK_CONFIGURATION_STACK_TYPE(prefix, name, type)\
    struct nk_config_stack_##name##_element {\
        prefix##_##type *address;\
        prefix##_##type old_value;\
    }
#define NK_CONFIG_STACK(type,size)\
    struct nk_config_stack_##type {\
        int head;\
        struct nk_config_stack_##type##_element elements[size];\
    }

#define nk_float float
NK_CONFIGURATION_STACK_TYPE(struct nk, style_item, style_item);
NK_CONFIGURATION_STACK_TYPE(nk ,float, float);
NK_CONFIGURATION_STACK_TYPE(struct nk, vec2, vec2);
NK_CONFIGURATION_STACK_TYPE(nk ,flags, flags);
NK_CONFIGURATION_STACK_TYPE(struct nk, color, color);
NK_CONFIGURATION_STACK_TYPE(const struct nk, user_font, user_font*);
NK_CONFIGURATION_STACK_TYPE(enum nk, button_behavior, button_behavior);

NK_CONFIG_STACK(style_item, NK_STYLE_ITEM_STACK_SIZE);
NK_CONFIG_STACK(float, NK_FLOAT_STACK_SIZE);
NK_CONFIG_STACK(vec2, NK_VECTOR_STACK_SIZE);
NK_CONFIG_STACK(flags, NK_FLAGS_STACK_SIZE);
NK_CONFIG_STACK(color, NK_COLOR_STACK_SIZE);
NK_CONFIG_STACK(user_font, NK_FONT_STACK_SIZE);
NK_CONFIG_STACK(button_behavior, NK_BUTTON_BEHAVIOR_STACK_SIZE);

struct nk_configuration_stacks {
    struct nk_config_stack_style_item style_items;
    struct nk_config_stack_float floats;
    struct nk_config_stack_vec2 vectors;
    struct nk_config_stack_flags flags;
    struct nk_config_stack_color colors;
    struct nk_config_stack_user_font fonts;
    struct nk_config_stack_button_behavior button_behaviors;
};

#define NK_VALUE_PAGE_CAPACITY \
    (((NK_MAX(sizeof(struct nk_window),sizeof(struct nk_panel)) / sizeof(nk_uint))) / 2)

struct nk_table {
    unsigned int seq;
    unsigned int size;
    nk_hash keys[NK_VALUE_PAGE_CAPACITY];
    nk_uint values[NK_VALUE_PAGE_CAPACITY];
    struct nk_table *next, *prev;
};

union nk_page_data {
    struct nk_table tbl;
    struct nk_panel pan;
    struct nk_window win;
};

struct nk_page_element {
    union nk_page_data data;
    struct nk_page_element *next;
    struct nk_page_element *prev;
};

struct nk_page {
    unsigned int size;
    struct nk_page *next;
    struct nk_page_element win[1];
};

struct nk_pool {
    struct nk_allocator alloc;
    enum nk_allocation_type type;
    unsigned int page_count;
    struct nk_page *pages;
    struct nk_page_element *freelist;
    unsigned capacity;
    nk_size size;
    nk_size cap;
};

struct nk_context {

    struct nk_input input;
    struct nk_style style;
    struct nk_buffer memory;
    struct nk_clipboard clip;
    nk_flags last_widget_state;
    enum nk_button_behavior button_behavior;
    struct nk_configuration_stacks stacks;
    float delta_time_seconds;

#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    struct nk_draw_list draw_list;
#endif
#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_handle userdata;
#endif

    struct nk_text_edit text_edit;

    struct nk_command_buffer overlay;

    int build;
    int use_pool;
    struct nk_pool pool;
    struct nk_window *begin;
    struct nk_window *end;
    struct nk_window *active;
    struct nk_window *current;
    struct nk_page_element *freelist;
    unsigned int count;
    unsigned int seq;
};

#define NK_PI 3.141592654f
#define NK_UTF_INVALID 0xFFFD
#define NK_MAX_FLOAT_PRECISION 2

#define NK_UNUSED(x) ((void)(x))
#define NK_SATURATE(x) (NK_MAX(0, NK_MIN(1.0f, x)))
#define NK_LEN(a) (sizeof(a)/sizeof(a)[0])
#define NK_ABS(a) (((a) < 0) ? -(a) : (a))
#define NK_BETWEEN(x, a, b) ((a) <= (x) && (x) < (b))
#define NK_INBOX(px, py, x, y, w, h)\
    (NK_BETWEEN(px,x,x+w) && NK_BETWEEN(py,y,y+h))
#define NK_INTERSECT(x0, y0, w0, h0, x1, y1, w1, h1) \
    ((x1 < (x0 + w0)) && (x0 < (x1 + w1)) && \
    (y1 < (y0 + h0)) && (y0 < (y1 + h1)))
#define NK_CONTAINS(x, y, w, h, bx, by, bw, bh)\
    (NK_INBOX(x,y, bx, by, bw, bh) && NK_INBOX(x+w,y+h, bx, by, bw, bh))

#define nk_vec2_sub(a, b) nk_vec2((a).x - (b).x, (a).y - (b).y)
#define nk_vec2_add(a, b) nk_vec2((a).x + (b).x, (a).y + (b).y)
#define nk_vec2_len_sqr(a) ((a).x*(a).x+(a).y*(a).y)
#define nk_vec2_muls(a, t) nk_vec2((a).x * (t), (a).y * (t))

#define nk_ptr_add(t, p, i) ((t*)((void*)((nk_byte*)(p) + (i))))
#define nk_ptr_add_const(t, p, i) ((const t*)((const void*)((const nk_byte*)(p) + (i))))
#define nk_zero_struct(s) nk_zero(&s, sizeof(s))

#if defined(__PTRDIFF_TYPE__)
# define NK_UINT_TO_PTR(x) ((void*)(__PTRDIFF_TYPE__)(x))
# define NK_PTR_TO_UINT(x) ((nk_size)(__PTRDIFF_TYPE__)(x))
#elif !defined(__GNUC__)
# define NK_UINT_TO_PTR(x) ((void*)&((char*)0)[x])
# define NK_PTR_TO_UINT(x) ((nk_size)(((char*)x)-(char*)0))
#elif defined(NK_USE_FIXED_TYPES)
# define NK_UINT_TO_PTR(x) ((void*)(uintptr_t)(x))
# define NK_PTR_TO_UINT(x) ((uintptr_t)(x))
#else
# define NK_UINT_TO_PTR(x) ((void*)(x))
# define NK_PTR_TO_UINT(x) ((nk_size)(x))
#endif

#define NK_ALIGN_PTR(x, mask)\
    (NK_UINT_TO_PTR((NK_PTR_TO_UINT((nk_byte*)(x) + (mask-1)) & ~(mask-1))))
#define NK_ALIGN_PTR_BACK(x, mask)\
    (NK_UINT_TO_PTR((NK_PTR_TO_UINT((nk_byte*)(x)) & ~(mask-1))))

#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
#define NK_OFFSETOF(st,m) (__builtin_offsetof(st,m))
#else
#define NK_OFFSETOF(st,m) ((nk_ptr)&(((st*)0)->m))
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
template<typename T> struct nk_alignof;
template<typename T, int size_diff> struct nk_helper{enum {value = size_diff};};
template<typename T> struct nk_helper<T,0>{enum {value = nk_alignof<T>::value};};
template<typename T> struct nk_alignof{struct Big {T x; char c;}; enum {
    diff = sizeof(Big) - sizeof(T), value = nk_helper<Big, diff>::value};};
#define NK_ALIGNOF(t) (nk_alignof<t>::value)
#else
#define NK_ALIGNOF(t) NK_OFFSETOF(struct {char c; t _h;}, _h)
#endif

#define NK_CONTAINER_OF(ptr,type,member)\
    (type*)((void*)((char*)(1 ? (ptr): &((type*)0)->member) - NK_OFFSETOF(type, member)))

#endif

#ifdef NK_IMPLEMENTATION

#ifndef NK_INTERNAL_H
#define NK_INTERNAL_H

#ifndef NK_POOL_DEFAULT_CAPACITY
#define NK_POOL_DEFAULT_CAPACITY 16
#endif

#ifndef NK_DEFAULT_COMMAND_BUFFER_SIZE
#define NK_DEFAULT_COMMAND_BUFFER_SIZE (4*1024)
#endif

#ifndef NK_BUFFER_DEFAULT_INITIAL_SIZE
#define NK_BUFFER_DEFAULT_INITIAL_SIZE (4*1024)
#endif

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
#include <stdlib.h>
#endif
#ifdef NK_INCLUDE_STANDARD_IO
#include <stdio.h>
#endif
#ifdef NK_INCLUDE_STANDARD_VARARGS
#include <stdarg.h>
#endif
#ifndef NK_ASSERT
#include <assert.h>
#define NK_ASSERT(expr) assert(expr)
#endif

#define NK_DEFAULT (-1)

#ifndef NK_VSNPRINTF

  #if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) ||\
      (defined(__cplusplus) && (__cplusplus >= 201103L)) || \
      (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200112L)) ||\
      (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE >= 500)) ||\
       defined(_ISOC99_SOURCE) || defined(_BSD_SOURCE)
      #define NK_VSNPRINTF(s,n,f,a) vsnprintf(s,n,f,a)
  #else
    #define NK_VSNPRINTF(s,n,f,a) vsprintf(s,f,a)
  #endif
#endif

#define NK_SCHAR_MIN (-127)
#define NK_SCHAR_MAX 127
#define NK_UCHAR_MIN 0
#define NK_UCHAR_MAX 256
#define NK_SSHORT_MIN (-32767)
#define NK_SSHORT_MAX 32767
#define NK_USHORT_MIN 0
#define NK_USHORT_MAX 65535
#define NK_SINT_MIN (-2147483647)
#define NK_SINT_MAX 2147483647
#define NK_UINT_MIN 0
#define NK_UINT_MAX 4294967295u

NK_STATIC_ASSERT(sizeof(nk_size) >= sizeof(void*));
NK_STATIC_ASSERT(sizeof(nk_ptr) == sizeof(void*));
NK_STATIC_ASSERT(sizeof(nk_flags) >= 4);
NK_STATIC_ASSERT(sizeof(nk_rune) >= 4);
NK_STATIC_ASSERT(sizeof(nk_ushort) == 2);
NK_STATIC_ASSERT(sizeof(nk_short) == 2);
NK_STATIC_ASSERT(sizeof(nk_uint) == 4);
NK_STATIC_ASSERT(sizeof(nk_int) == 4);
NK_STATIC_ASSERT(sizeof(nk_byte) == 1);
#ifdef NK_INCLUDE_STANDARD_BOOL
NK_STATIC_ASSERT(sizeof(nk_bool) == sizeof(bool));
#else
NK_STATIC_ASSERT(sizeof(nk_bool) == 4);
#endif

NK_GLOBAL const struct nk_rect nk_null_rect = {-8192.0f, -8192.0f, 16384, 16384};
#define NK_FLOAT_PRECISION 0.00000000000001

NK_GLOBAL const struct nk_color nk_red = {255,0,0,255};
NK_GLOBAL const struct nk_color nk_green = {0,255,0,255};
NK_GLOBAL const struct nk_color nk_blue = {0,0,255,255};
NK_GLOBAL const struct nk_color nk_white = {255,255,255,255};
NK_GLOBAL const struct nk_color nk_black = {0,0,0,255};
NK_GLOBAL const struct nk_color nk_yellow = {255,255,0,255};

#define nk_widget_state_reset(s)\
    if ((*(s)) & NK_WIDGET_STATE_MODIFIED)\
        (*(s)) = NK_WIDGET_STATE_INACTIVE|NK_WIDGET_STATE_MODIFIED;\
    else (*(s)) = NK_WIDGET_STATE_INACTIVE;

#ifndef NK_INV_SQRT
NK_LIB float nk_inv_sqrt(float n);
#endif
#ifndef NK_SIN
NK_LIB float nk_sin(float x);
#endif
#ifndef NK_COS
NK_LIB float nk_cos(float x);
#endif
NK_LIB nk_uint nk_round_up_pow2(nk_uint v);
NK_LIB struct nk_rect nk_shrink_rect(struct nk_rect r, float amount);
NK_LIB struct nk_rect nk_pad_rect(struct nk_rect r, struct nk_vec2 pad);
NK_LIB void nk_unify(struct nk_rect *clip, const struct nk_rect *a, float x0, float y0, float x1, float y1);
NK_LIB double nk_pow(double x, int n);
NK_LIB int nk_ifloord(double x);
NK_LIB int nk_ifloorf(float x);
NK_LIB int nk_iceilf(float x);
NK_LIB int nk_log10(double n);

enum {NK_DO_NOT_STOP_ON_NEW_LINE, NK_STOP_ON_NEW_LINE};
NK_LIB nk_bool nk_is_lower(int c);
NK_LIB nk_bool nk_is_upper(int c);
NK_LIB int nk_to_upper(int c);
NK_LIB int nk_to_lower(int c);

#ifndef NK_MEMCPY
NK_LIB void* nk_memcopy(void *dst, const void *src, nk_size n);
#endif
#ifndef NK_MEMSET
NK_LIB void nk_memset(void *ptr, int c0, nk_size size);
#endif
NK_LIB void nk_zero(void *ptr, nk_size size);
NK_LIB char *nk_itoa(char *s, long n);
NK_LIB int nk_string_float_limit(char *string, int prec);
#ifndef NK_DTOA
NK_LIB char *nk_dtoa(char *s, double n);
#endif
NK_LIB int nk_text_clamp(const struct nk_user_font *font, const char *text, int text_len, float space, int *glyphs, float *text_width, nk_rune *sep_list, int sep_count);
NK_LIB struct nk_vec2 nk_text_calculate_text_bounds(const struct nk_user_font *font, const char *begin, int byte_len, float row_height, const char **remaining, struct nk_vec2 *out_offset, int *glyphs, int op);
#ifdef NK_INCLUDE_STANDARD_VARARGS
NK_LIB int nk_strfmt(char *buf, int buf_size, const char *fmt, va_list args);
#endif
#ifdef NK_INCLUDE_STANDARD_IO
NK_LIB char *nk_file_load(const char* path, nk_size* siz, struct nk_allocator *alloc);
#endif

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_LIB void* nk_malloc(nk_handle unused, void *old,nk_size size);
NK_LIB void nk_mfree(nk_handle unused, void *ptr);
#endif
NK_LIB void* nk_buffer_align(void *unaligned, nk_size align, nk_size *alignment, enum nk_buffer_allocation_type type);
NK_LIB void* nk_buffer_alloc(struct nk_buffer *b, enum nk_buffer_allocation_type type, nk_size size, nk_size align);
NK_LIB void* nk_buffer_realloc(struct nk_buffer *b, nk_size capacity, nk_size *size);

NK_LIB void nk_command_buffer_init(struct nk_command_buffer *cb, struct nk_buffer *b, enum nk_command_clipping clip);
NK_LIB void nk_command_buffer_reset(struct nk_command_buffer *b);
NK_LIB void* nk_command_buffer_push(struct nk_command_buffer* b, enum nk_command_type t, nk_size size);
NK_LIB void nk_draw_symbol(struct nk_command_buffer *out, enum nk_symbol_type type, struct nk_rect content, struct nk_color background, struct nk_color foreground, float border_width, const struct nk_user_font *font);

NK_LIB void nk_start_buffer(struct nk_context *ctx, struct nk_command_buffer *b);
NK_LIB void nk_start(struct nk_context *ctx, struct nk_window *win);
NK_LIB void nk_start_popup(struct nk_context *ctx, struct nk_window *win);
NK_LIB void nk_finish_popup(struct nk_context *ctx, struct nk_window*);
NK_LIB void nk_finish_buffer(struct nk_context *ctx, struct nk_command_buffer *b);
NK_LIB void nk_finish(struct nk_context *ctx, struct nk_window *w);
NK_LIB void nk_build(struct nk_context *ctx);

NK_LIB void nk_textedit_clear_state(struct nk_text_edit *state, enum nk_text_edit_type type, nk_plugin_filter filter);
NK_LIB void nk_textedit_click(struct nk_text_edit *state, float x, float y, const struct nk_user_font *font, float row_height);
NK_LIB void nk_textedit_drag(struct nk_text_edit *state, float x, float y, const struct nk_user_font *font, float row_height);
NK_LIB void nk_textedit_key(struct nk_text_edit *state, enum nk_keys key, int shift_mod, const struct nk_user_font *font, float row_height);

enum nk_window_insert_location {
    NK_INSERT_BACK,
    NK_INSERT_FRONT
};
NK_LIB void *nk_create_window(struct nk_context *ctx);
NK_LIB void nk_remove_window(struct nk_context*, struct nk_window*);
NK_LIB void nk_free_window(struct nk_context *ctx, struct nk_window *win);
NK_LIB struct nk_window *nk_find_window(struct nk_context *ctx, nk_hash hash, const char *name);
NK_LIB void nk_insert_window(struct nk_context *ctx, struct nk_window *win, enum nk_window_insert_location loc);

NK_LIB void nk_pool_init(struct nk_pool *pool, struct nk_allocator *alloc, unsigned int capacity);
NK_LIB void nk_pool_free(struct nk_pool *pool);
NK_LIB void nk_pool_init_fixed(struct nk_pool *pool, void *memory, nk_size size);
NK_LIB struct nk_page_element *nk_pool_alloc(struct nk_pool *pool);

NK_LIB struct nk_page_element* nk_create_page_element(struct nk_context *ctx);
NK_LIB void nk_link_page_element_into_freelist(struct nk_context *ctx, struct nk_page_element *elem);
NK_LIB void nk_free_page_element(struct nk_context *ctx, struct nk_page_element *elem);

NK_LIB struct nk_table* nk_create_table(struct nk_context *ctx);
NK_LIB void nk_remove_table(struct nk_window *win, struct nk_table *tbl);
NK_LIB void nk_free_table(struct nk_context *ctx, struct nk_table *tbl);
NK_LIB void nk_push_table(struct nk_window *win, struct nk_table *tbl);
NK_LIB nk_uint *nk_add_value(struct nk_context *ctx, struct nk_window *win, nk_hash name, nk_uint value);
NK_LIB nk_uint *nk_find_value(struct nk_window *win, nk_hash name);

NK_LIB void *nk_create_panel(struct nk_context *ctx);
NK_LIB void nk_free_panel(struct nk_context*, struct nk_panel *pan);
NK_LIB nk_bool nk_panel_has_header(nk_flags flags, const char *title);
NK_LIB struct nk_vec2 nk_panel_get_padding(const struct nk_style *style, enum nk_panel_type type);
NK_LIB float nk_panel_get_border(const struct nk_style *style, nk_flags flags, enum nk_panel_type type);
NK_LIB struct nk_color nk_panel_get_border_color(const struct nk_style *style, enum nk_panel_type type);
NK_LIB nk_bool nk_panel_is_sub(enum nk_panel_type type);
NK_LIB nk_bool nk_panel_is_nonblock(enum nk_panel_type type);
NK_LIB nk_bool nk_panel_begin(struct nk_context *ctx, const char *title, enum nk_panel_type panel_type);
NK_LIB void nk_panel_end(struct nk_context *ctx);

NK_LIB float nk_layout_row_calculate_usable_space(const struct nk_style *style, enum nk_panel_type type, float total_space, int columns);
NK_LIB void nk_panel_layout(const struct nk_context *ctx, struct nk_window *win, float height, int cols);
NK_LIB void nk_row_layout(struct nk_context *ctx, enum nk_layout_format fmt, float height, int cols, int width);
NK_LIB void nk_panel_alloc_row(const struct nk_context *ctx, struct nk_window *win);
NK_LIB void nk_layout_widget_space(struct nk_rect *bounds, const struct nk_context *ctx, struct nk_window *win, int modify);
NK_LIB void nk_panel_alloc_space(struct nk_rect *bounds, const struct nk_context *ctx);
NK_LIB void nk_layout_peek(struct nk_rect *bounds, struct nk_context *ctx);

NK_LIB nk_bool nk_nonblock_begin(struct nk_context *ctx, nk_flags flags, struct nk_rect body, struct nk_rect header, enum nk_panel_type panel_type);

struct nk_text {
    struct nk_vec2 padding;
    struct nk_color background;
    struct nk_color text;
};
NK_LIB void nk_widget_text(struct nk_command_buffer *o, struct nk_rect b, const char *string, int len, const struct nk_text *t, nk_flags a, const struct nk_user_font *f);
NK_LIB void nk_widget_text_wrap(struct nk_command_buffer *o, struct nk_rect b, const char *string, int len, const struct nk_text *t, const struct nk_user_font *f);

NK_LIB nk_bool nk_button_behavior(nk_flags *state, struct nk_rect r, const struct nk_input *i, enum nk_button_behavior behavior);
NK_LIB const struct nk_style_item* nk_draw_button(struct nk_command_buffer *out, const struct nk_rect *bounds, nk_flags state, const struct nk_style_button *style);
NK_LIB nk_bool nk_do_button(nk_flags *state, struct nk_command_buffer *out, struct nk_rect r, const struct nk_style_button *style, const struct nk_input *in, enum nk_button_behavior behavior, struct nk_rect *content);
NK_LIB void nk_draw_button_text(struct nk_command_buffer *out, const struct nk_rect *bounds, const struct nk_rect *content, nk_flags state, const struct nk_style_button *style, const char *txt, int len, nk_flags text_alignment, const struct nk_user_font *font);
NK_LIB nk_bool nk_do_button_text(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, const char *string, int len, nk_flags align, enum nk_button_behavior behavior, const struct nk_style_button *style, const struct nk_input *in, const struct nk_user_font *font);
NK_LIB void nk_draw_button_symbol(struct nk_command_buffer *out, const struct nk_rect *bounds, const struct nk_rect *content, nk_flags state, const struct nk_style_button *style, enum nk_symbol_type type, const struct nk_user_font *font);
NK_LIB nk_bool nk_do_button_symbol(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, enum nk_symbol_type symbol, enum nk_button_behavior behavior, const struct nk_style_button *style, const struct nk_input *in, const struct nk_user_font *font);
NK_LIB void nk_draw_button_image(struct nk_command_buffer *out, const struct nk_rect *bounds, const struct nk_rect *content, nk_flags state, const struct nk_style_button *style, const struct nk_image *img);
NK_LIB nk_bool nk_do_button_image(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, struct nk_image img, enum nk_button_behavior b, const struct nk_style_button *style, const struct nk_input *in);
NK_LIB void nk_draw_button_text_symbol(struct nk_command_buffer *out, const struct nk_rect *bounds, const struct nk_rect *label, const struct nk_rect *symbol, nk_flags state, const struct nk_style_button *style, const char *str, int len, enum nk_symbol_type type, const struct nk_user_font *font);
NK_LIB nk_bool nk_do_button_text_symbol(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, enum nk_symbol_type symbol, const char *str, int len, nk_flags align, enum nk_button_behavior behavior, const struct nk_style_button *style, const struct nk_user_font *font, const struct nk_input *in);
NK_LIB void nk_draw_button_text_image(struct nk_command_buffer *out, const struct nk_rect *bounds, const struct nk_rect *label, const struct nk_rect *image, nk_flags state, const struct nk_style_button *style, const char *str, int len, const struct nk_user_font *font, const struct nk_image *img);
NK_LIB nk_bool nk_do_button_text_image(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, struct nk_image img, const char* str, int len, nk_flags align, enum nk_button_behavior behavior, const struct nk_style_button *style, const struct nk_user_font *font, const struct nk_input *in);

enum nk_toggle_type {
    NK_TOGGLE_CHECK,
    NK_TOGGLE_OPTION
};
NK_LIB nk_bool nk_toggle_behavior(const struct nk_input *in, struct nk_rect select, nk_flags *state, nk_bool active);
NK_LIB void nk_draw_checkbox(struct nk_command_buffer *out, nk_flags state, const struct nk_style_toggle *style, nk_bool active, const struct nk_rect *label, const struct nk_rect *selector, const struct nk_rect *cursors, const char *string, int len, const struct nk_user_font *font);
NK_LIB void nk_draw_option(struct nk_command_buffer *out, nk_flags state, const struct nk_style_toggle *style, nk_bool active, const struct nk_rect *label, const struct nk_rect *selector, const struct nk_rect *cursors, const char *string, int len, const struct nk_user_font *font);
NK_LIB nk_bool nk_do_toggle(nk_flags *state, struct nk_command_buffer *out, struct nk_rect r, nk_bool *active, const char *str, int len, enum nk_toggle_type type, const struct nk_style_toggle *style, const struct nk_input *in, const struct nk_user_font *font);

NK_LIB nk_size nk_progress_behavior(nk_flags *state, struct nk_input *in, struct nk_rect r, struct nk_rect cursor, nk_size max, nk_size value, nk_bool modifiable);
NK_LIB void nk_draw_progress(struct nk_command_buffer *out, nk_flags state, const struct nk_style_progress *style, const struct nk_rect *bounds, const struct nk_rect *scursor, nk_size value, nk_size max);
NK_LIB nk_size nk_do_progress(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, nk_size value, nk_size max, nk_bool modifiable, const struct nk_style_progress *style, struct nk_input *in);

NK_LIB float nk_slider_behavior(nk_flags *state, struct nk_rect *logical_cursor, struct nk_rect *visual_cursor, struct nk_input *in, struct nk_rect bounds, float slider_min, float slider_max, float slider_value, float slider_step, float slider_steps);
NK_LIB void nk_draw_slider(struct nk_command_buffer *out, nk_flags state, const struct nk_style_slider *style, const struct nk_rect *bounds, const struct nk_rect *visual_cursor, float min, float value, float max);
NK_LIB float nk_do_slider(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, float min, float val, float max, float step, const struct nk_style_slider *style, struct nk_input *in, const struct nk_user_font *font);

NK_LIB float nk_scrollbar_behavior(nk_flags *state, struct nk_input *in, int has_scrolling, const struct nk_rect *scroll, const struct nk_rect *cursor, const struct nk_rect *empty0, const struct nk_rect *empty1, float scroll_offset, float target, float scroll_step, enum nk_orientation o);
NK_LIB void nk_draw_scrollbar(struct nk_command_buffer *out, nk_flags state, const struct nk_style_scrollbar *style, const struct nk_rect *bounds, const struct nk_rect *scroll);
NK_LIB float nk_do_scrollbarv(nk_flags *state, struct nk_command_buffer *out, struct nk_rect scroll, int has_scrolling, float offset, float target, float step, float button_pixel_inc, const struct nk_style_scrollbar *style, struct nk_input *in, const struct nk_user_font *font);
NK_LIB float nk_do_scrollbarh(nk_flags *state, struct nk_command_buffer *out, struct nk_rect scroll, int has_scrolling, float offset, float target, float step, float button_pixel_inc, const struct nk_style_scrollbar *style, struct nk_input *in, const struct nk_user_font *font);

NK_LIB void nk_draw_selectable(struct nk_command_buffer *out, nk_flags state, const struct nk_style_selectable *style, nk_bool active, const struct nk_rect *bounds, const struct nk_rect *icon, const struct nk_image *img, enum nk_symbol_type sym, const char *string, int len, nk_flags align, const struct nk_user_font *font);
NK_LIB nk_bool nk_do_selectable(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, const char *str, int len, nk_flags align, nk_bool *value, const struct nk_style_selectable *style, const struct nk_input *in, const struct nk_user_font *font);
NK_LIB nk_bool nk_do_selectable_image(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, const char *str, int len, nk_flags align, nk_bool *value, const struct nk_image *img, const struct nk_style_selectable *style, const struct nk_input *in, const struct nk_user_font *font);

NK_LIB void nk_edit_draw_text(struct nk_command_buffer *out, const struct nk_style_edit *style, float pos_x, float pos_y, float x_offset, const char *text, int byte_len, float row_height, const struct nk_user_font *font, struct nk_color background, struct nk_color foreground, nk_bool is_selected);
NK_LIB nk_flags nk_do_edit(nk_flags *state, struct nk_command_buffer *out, struct nk_rect bounds, nk_flags flags, nk_plugin_filter filter, struct nk_text_edit *edit, const struct nk_style_edit *style, struct nk_input *in, const struct nk_user_font *font);

NK_LIB nk_bool nk_color_picker_behavior(nk_flags *state, const struct nk_rect *bounds, const struct nk_rect *matrix, const struct nk_rect *hue_bar, const struct nk_rect *alpha_bar, struct nk_colorf *color, const struct nk_input *in);
NK_LIB void nk_draw_color_picker(struct nk_command_buffer *o, const struct nk_rect *matrix, const struct nk_rect *hue_bar, const struct nk_rect *alpha_bar, struct nk_colorf col);
NK_LIB nk_bool nk_do_color_picker(nk_flags *state, struct nk_command_buffer *out, struct nk_colorf *col, enum nk_color_format fmt, struct nk_rect bounds, struct nk_vec2 padding, const struct nk_input *in, const struct nk_user_font *font);

enum nk_property_status {
    NK_PROPERTY_DEFAULT,
    NK_PROPERTY_EDIT,
    NK_PROPERTY_DRAG
};
enum nk_property_filter {
    NK_FILTER_INT,
    NK_FILTER_FLOAT
};
enum nk_property_kind {
    NK_PROPERTY_INT,
    NK_PROPERTY_FLOAT,
    NK_PROPERTY_DOUBLE
};
union nk_property {
    int i;
    float f;
    double d;
};
struct nk_property_variant {
    enum nk_property_kind kind;
    union nk_property value;
    union nk_property min_value;
    union nk_property max_value;
    union nk_property step;
};
NK_LIB struct nk_property_variant nk_property_variant_int(int value, int min_value, int max_value, int step);
NK_LIB struct nk_property_variant nk_property_variant_float(float value, float min_value, float max_value, float step);
NK_LIB struct nk_property_variant nk_property_variant_double(double value, double min_value, double max_value, double step);

NK_LIB void nk_drag_behavior(nk_flags *state, const struct nk_input *in, struct nk_rect drag, struct nk_property_variant *variant, float inc_per_pixel);
NK_LIB void nk_property_behavior(nk_flags *ws, const struct nk_input *in, struct nk_rect property,  struct nk_rect label, struct nk_rect edit, struct nk_rect empty, int *state, struct nk_property_variant *variant, float inc_per_pixel);
NK_LIB void nk_draw_property(struct nk_command_buffer *out, const struct nk_style_property *style, const struct nk_rect *bounds, const struct nk_rect *label, nk_flags state, const char *name, int len, const struct nk_user_font *font);
NK_LIB void nk_do_property(nk_flags *ws, struct nk_command_buffer *out, struct nk_rect property, const char *name, struct nk_property_variant *variant, float inc_per_pixel, char *buffer, int *len, int *state, int *cursor, int *select_begin, int *select_end, const struct nk_style_property *style, enum nk_property_filter filter, struct nk_input *in, const struct nk_user_font *font, struct nk_text_edit *text_edit, enum nk_button_behavior behavior);
NK_LIB void nk_property(struct nk_context *ctx, const char *name, struct nk_property_variant *variant, float inc_per_pixel, const enum nk_property_filter filter);

#ifdef NK_INCLUDE_FONT_BAKING

#define STB_RECT_PACK_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#ifndef STBTT_malloc
static void*
nk_stbtt_malloc(nk_size size, void *user_data) {
	struct nk_allocator *alloc = (struct nk_allocator *) user_data;
	return alloc->alloc(alloc->userdata, 0, size);
}

static void
nk_stbtt_free(void *ptr, void *user_data) {
	struct nk_allocator *alloc = (struct nk_allocator *) user_data;
	alloc->free(alloc->userdata, ptr);
}

#define STBTT_malloc(x,u)  nk_stbtt_malloc(x,u)
#define STBTT_free(x,u)    nk_stbtt_free(x,u)

#endif

#endif

#endif

#ifndef NK_INV_SQRT
#define NK_INV_SQRT nk_inv_sqrt
NK_LIB float
nk_inv_sqrt(float n)
{
    float x2;
    const float threehalfs = 1.5f;
    union {nk_uint i; float f;} conv = {0};
    conv.f = n;
    x2 = n * 0.5f;
    conv.i = 0x5f375A84 - (conv.i >> 1);
    conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
    return conv.f;
}
#endif
#ifndef NK_SIN
#define NK_SIN nk_sin
NK_LIB float
nk_sin(float x)
{
    NK_STORAGE const float a0 = +1.91059300966915117e-31f;
    NK_STORAGE const float a1 = +1.00086760103908896f;
    NK_STORAGE const float a2 = -1.21276126894734565e-2f;
    NK_STORAGE const float a3 = -1.38078780785773762e-1f;
    NK_STORAGE const float a4 = -2.67353392911981221e-2f;
    NK_STORAGE const float a5 = +2.08026600266304389e-2f;
    NK_STORAGE const float a6 = -3.03996055049204407e-3f;
    NK_STORAGE const float a7 = +1.38235642404333740e-4f;
    return a0 + x*(a1 + x*(a2 + x*(a3 + x*(a4 + x*(a5 + x*(a6 + x*a7))))));
}
#endif
#ifndef NK_COS
#define NK_COS nk_cos
NK_LIB float
nk_cos(float x)
{

    NK_STORAGE const float a0 = 9.9995999154986614e-1f;
    NK_STORAGE const float a1 = 1.2548995793001028e-3f;
    NK_STORAGE const float a2 = -5.0648546280678015e-1f;
    NK_STORAGE const float a3 = 1.2942246466519995e-2f;
    NK_STORAGE const float a4 = 2.8668384702547972e-2f;
    NK_STORAGE const float a5 = 7.3726485210586547e-3f;
    NK_STORAGE const float a6 = -3.8510875386947414e-3f;
    NK_STORAGE const float a7 = 4.7196604604366623e-4f;
    NK_STORAGE const float a8 = -1.8776444013090451e-5f;
    return a0 + x*(a1 + x*(a2 + x*(a3 + x*(a4 + x*(a5 + x*(a6 + x*(a7 + x*a8)))))));
}
#endif
NK_LIB nk_uint
nk_round_up_pow2(nk_uint v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}
NK_LIB double
nk_pow(double x, int n)
{

    double r = 1;
    int plus = n >= 0;
    n = (plus) ? n : -n;
    while (n > 0) {
        if ((n & 1) == 1)
            r *= x;
        n /= 2;
        x *= x;
    }
    return plus ? r : 1.0 / r;
}
NK_LIB int
nk_ifloord(double x)
{
    x = (double)((int)x - ((x < 0.0) ? 1 : 0));
    return (int)x;
}
NK_LIB int
nk_ifloorf(float x)
{
    x = (float)((int)x - ((x < 0.0f) ? 1 : 0));
    return (int)x;
}
NK_LIB int
nk_iceilf(float x)
{
    if (x >= 0) {
        int i = (int)x;
        return (x > i) ? i+1: i;
    } else {
        int t = (int)x;
        float r = x - (float)t;
        return (r > 0.0f) ? t+1: t;
    }
}
NK_LIB int
nk_log10(double n)
{
    int neg;
    int ret;
    int exp = 0;

    neg = (n < 0) ? 1 : 0;
    ret = (neg) ? (int)-n : (int)n;
    while ((ret / 10) > 0) {
        ret /= 10;
        exp++;
    }
    if (neg) exp = -exp;
    return exp;
}
NK_API struct nk_rect
nk_get_null_rect(void)
{
    return nk_null_rect;
}
NK_API struct nk_rect
nk_rect(float x, float y, float w, float h)
{
    struct nk_rect r;
    r.x = x; r.y = y;
    r.w = w; r.h = h;
    return r;
}
NK_API struct nk_rect
nk_recti(int x, int y, int w, int h)
{
    struct nk_rect r;
    r.x = (float)x;
    r.y = (float)y;
    r.w = (float)w;
    r.h = (float)h;
    return r;
}
NK_API struct nk_rect
nk_recta(struct nk_vec2 pos, struct nk_vec2 size)
{
    return nk_rect(pos.x, pos.y, size.x, size.y);
}
NK_API struct nk_rect
nk_rectv(const float *r)
{
    return nk_rect(r[0], r[1], r[2], r[3]);
}
NK_API struct nk_rect
nk_rectiv(const int *r)
{
    return nk_recti(r[0], r[1], r[2], r[3]);
}
NK_API struct nk_vec2
nk_rect_pos(struct nk_rect r)
{
    struct nk_vec2 ret;
    ret.x = r.x; ret.y = r.y;
    return ret;
}
NK_API struct nk_vec2
nk_rect_size(struct nk_rect r)
{
    struct nk_vec2 ret;
    ret.x = r.w; ret.y = r.h;
    return ret;
}
NK_LIB struct nk_rect
nk_shrink_rect(struct nk_rect r, float amount)
{
    struct nk_rect res;
    r.w = NK_MAX(r.w, 2 * amount);
    r.h = NK_MAX(r.h, 2 * amount);
    res.x = r.x + amount;
    res.y = r.y + amount;
    res.w = r.w - 2 * amount;
    res.h = r.h - 2 * amount;
    return res;
}
NK_LIB struct nk_rect
nk_pad_rect(struct nk_rect r, struct nk_vec2 pad)
{
    r.w = NK_MAX(r.w, 2 * pad.x);
    r.h = NK_MAX(r.h, 2 * pad.y);
    r.x += pad.x; r.y += pad.y;
    r.w -= 2 * pad.x;
    r.h -= 2 * pad.y;
    return r;
}
NK_API struct nk_vec2
nk_vec2(float x, float y)
{
    struct nk_vec2 ret;
    ret.x = x; ret.y = y;
    return ret;
}
NK_API struct nk_vec2
nk_vec2i(int x, int y)
{
    struct nk_vec2 ret;
    ret.x = (float)x;
    ret.y = (float)y;
    return ret;
}
NK_API struct nk_vec2
nk_vec2v(const float *v)
{
    return nk_vec2(v[0], v[1]);
}
NK_API struct nk_vec2
nk_vec2iv(const int *v)
{
    return nk_vec2i(v[0], v[1]);
}
NK_LIB void
nk_unify(struct nk_rect *clip, const struct nk_rect *a, float x0, float y0,
    float x1, float y1)
{
    NK_ASSERT(a);
    NK_ASSERT(clip);
    clip->x = NK_MAX(a->x, x0);
    clip->y = NK_MAX(a->y, y0);
    clip->w = NK_MIN(a->x + a->w, x1) - clip->x;
    clip->h = NK_MIN(a->y + a->h, y1) - clip->y;
    clip->w = NK_MAX(0, clip->w);
    clip->h = NK_MAX(0, clip->h);
}

NK_API void
nk_triangle_from_direction(struct nk_vec2 *result, struct nk_rect r,
    float pad_x, float pad_y, enum nk_heading direction)
{
    float w_half, h_half;
    NK_ASSERT(result);

    r.w = NK_MAX(2 * pad_x, r.w);
    r.h = NK_MAX(2 * pad_y, r.h);
    r.w = r.w - 2 * pad_x;
    r.h = r.h - 2 * pad_y;

    r.x = r.x + pad_x;
    r.y = r.y + pad_y;

    w_half = r.w / 2.0f;
    h_half = r.h / 2.0f;

    if (direction == NK_UP) {
        result[0] = nk_vec2(r.x + w_half, r.y);
        result[1] = nk_vec2(r.x + r.w, r.y + r.h);
        result[2] = nk_vec2(r.x, r.y + r.h);
    } else if (direction == NK_RIGHT) {
        result[0] = nk_vec2(r.x, r.y);
        result[1] = nk_vec2(r.x + r.w, r.y + h_half);
        result[2] = nk_vec2(r.x, r.y + r.h);
    } else if (direction == NK_DOWN) {
        result[0] = nk_vec2(r.x, r.y);
        result[1] = nk_vec2(r.x + r.w, r.y);
        result[2] = nk_vec2(r.x + w_half, r.y + r.h);
    } else {
        result[0] = nk_vec2(r.x, r.y + h_half);
        result[1] = nk_vec2(r.x + r.w, r.y);
        result[2] = nk_vec2(r.x + r.w, r.y + r.h);
    }
}

NK_INTERN int nk_str_match_here(const char *regexp, const char *text);
NK_INTERN int nk_str_match_star(int c, const char *regexp, const char *text);
NK_LIB nk_bool nk_is_lower(int c) {return (c >= 'a' && c <= 'z') || (c >= 0xE0 && c <= 0xFF);}
NK_LIB nk_bool nk_is_upper(int c){return (c >= 'A' && c <= 'Z') || (c >= 0xC0 && c <= 0xDF);}
NK_LIB int nk_to_upper(int c) {return (c >= 'a' && c <= 'z') ? (c - ('a' - 'A')) : c;}
NK_LIB int nk_to_lower(int c) {return (c >= 'A' && c <= 'Z') ? (c - ('a' + 'A')) : c;}

#ifndef NK_MEMCPY
#define NK_MEMCPY nk_memcopy
NK_LIB void*
nk_memcopy(void *dst0, const void *src0, nk_size length)
{
    nk_ptr t;
    char *dst = (char*)dst0;
    const char *src = (const char*)src0;
    if (length == 0 || dst == src)
        goto done;

    #define nk_word int
    #define nk_wsize sizeof(nk_word)
    #define nk_wmask (nk_wsize-1)
    #define NK_TLOOP(s) if (t) NK_TLOOP1(s)
    #define NK_TLOOP1(s) do { s; } while (--t)

    if (dst < src) {
        t = (nk_ptr)src;
        if ((t | (nk_ptr)dst) & nk_wmask) {
            if ((t ^ (nk_ptr)dst) & nk_wmask || length < nk_wsize)
                t = length;
            else
                t = nk_wsize - (t & nk_wmask);
            length -= t;
            NK_TLOOP1(*dst++ = *src++);
        }
        t = length / nk_wsize;
        NK_TLOOP(*(nk_word*)(void*)dst = *(const nk_word*)(const void*)src;
            src += nk_wsize; dst += nk_wsize);
        t = length & nk_wmask;
        NK_TLOOP(*dst++ = *src++);
    } else {
        src += length;
        dst += length;
        t = (nk_ptr)src;
        if ((t | (nk_ptr)dst) & nk_wmask) {
            if ((t ^ (nk_ptr)dst) & nk_wmask || length <= nk_wsize)
                t = length;
            else
                t &= nk_wmask;
            length -= t;
            NK_TLOOP1(*--dst = *--src);
        }
        t = length / nk_wsize;
        NK_TLOOP(src -= nk_wsize; dst -= nk_wsize;
            *(nk_word*)(void*)dst = *(const nk_word*)(const void*)src);
        t = length & nk_wmask;
        NK_TLOOP(*--dst = *--src);
    }
    #undef nk_word
    #undef nk_wsize
    #undef nk_wmask
    #undef NK_TLOOP
    #undef NK_TLOOP1
done:
    return (dst0);
}
#endif
#ifndef NK_MEMSET
#define NK_MEMSET nk_memset
NK_LIB void
nk_memset(void *ptr, int c0, nk_size size)
{
    #define nk_word unsigned
    #define nk_wsize sizeof(nk_word)
    #define nk_wmask (nk_wsize - 1)
    nk_byte *dst = (nk_byte*)ptr;
    unsigned c = 0;
    nk_size t = 0;

    if ((c = (nk_byte)c0) != 0) {
        c = (c << 8) | c;
        if (sizeof(unsigned int) > 2)
            c = (c << 16) | c;
    }

    dst = (nk_byte*)ptr;
    if (size < 3 * nk_wsize) {
        while (size--) *dst++ = (nk_byte)c0;
        return;
    }

    if ((t = NK_PTR_TO_UINT(dst) & nk_wmask) != 0) {
        t = nk_wsize -t;
        size -= t;
        do {
            *dst++ = (nk_byte)c0;
        } while (--t != 0);
    }

    t = size / nk_wsize;
    do {
        *(nk_word*)((void*)dst) = c;
        dst += nk_wsize;
    } while (--t != 0);

    t = (size & nk_wmask);
    if (t != 0) {
        do {
            *dst++ = (nk_byte)c0;
        } while (--t != 0);
    }

    #undef nk_word
    #undef nk_wsize
    #undef nk_wmask
}
#endif
NK_LIB void
nk_zero(void *ptr, nk_size size)
{
    NK_ASSERT(ptr);
    NK_MEMSET(ptr, 0, size);
}
NK_API int
nk_strlen(const char *str)
{
    int siz = 0;
    NK_ASSERT(str);
    while (str && *str++ != '\0') siz++;
    return siz;
}
NK_API int
nk_strtoi(const char *str, const char **endptr)
{
    int neg = 1;
    const char *p = str;
    int value = 0;

    NK_ASSERT(str);
    if (!str) return 0;

    while (*p == ' ') p++;
    if (*p == '-') {
        neg = -1;
        p++;
    }
    while (*p && *p >= '0' && *p <= '9') {
        value = value * 10 + (int) (*p - '0');
        p++;
    }
    if (endptr)
        *endptr = p;
    return neg*value;
}
NK_API double
nk_strtod(const char *str, const char **endptr)
{
    double m;
    double neg = 1.0;
    const char *p = str;
    double value = 0;
    double number = 0;

    NK_ASSERT(str);
    if (!str) return 0;

    while (*p == ' ') p++;
    if (*p == '-') {
        neg = -1.0;
        p++;
    }

    while (*p && *p != '.' && *p != 'e') {
        value = value * 10.0 + (double) (*p - '0');
        p++;
    }

    if (*p == '.') {
        p++;
        for(m = 0.1; *p && *p != 'e'; p++ ) {
            value = value + (double) (*p - '0') * m;
            m *= 0.1;
        }
    }
    if (*p == 'e') {
        int i, pow, div;
        p++;
        if (*p == '-') {
            div = nk_true;
            p++;
        } else if (*p == '+') {
            div = nk_false;
            p++;
        } else div = nk_false;

        for (pow = 0; *p; p++)
            pow = pow * 10 + (int) (*p - '0');

        for (m = 1.0, i = 0; i < pow; i++)
            m *= 10.0;

        if (div)
            value /= m;
        else value *= m;
    }
    number = value * neg;
    if (endptr)
        *endptr = p;
    return number;
}
NK_API float
nk_strtof(const char *str, const char **endptr)
{
    float float_value;
    double double_value;
    double_value = NK_STRTOD(str, endptr);
    float_value = (float)double_value;
    return float_value;
}
NK_API int
nk_stricmp(const char *s1, const char *s2)
{
    nk_int c1,c2,d;
    do {
        c1 = *s1++;
        c2 = *s2++;
        d = c1 - c2;
        while (d) {
            if (c1 <= 'Z' && c1 >= 'A') {
                d += ('a' - 'A');
                if (!d) break;
            }
            if (c2 <= 'Z' && c2 >= 'A') {
                d -= ('a' - 'A');
                if (!d) break;
            }
            return ((d >= 0) << 1) - 1;
        }
    } while (c1);
    return 0;
}
NK_API int
nk_stricmpn(const char *s1, const char *s2, int n)
{
    int c1,c2,d;
    NK_ASSERT(n >= 0);
    do {
        c1 = *s1++;
        c2 = *s2++;
        if (!n--) return 0;

        d = c1 - c2;
        while (d) {
            if (c1 <= 'Z' && c1 >= 'A') {
                d += ('a' - 'A');
                if (!d) break;
            }
            if (c2 <= 'Z' && c2 >= 'A') {
                d -= ('a' - 'A');
                if (!d) break;
            }
            return ((d >= 0) << 1) - 1;
        }
    } while (c1);
    return 0;
}
NK_INTERN int
nk_str_match_here(const char *regexp, const char *text)
{
    if (regexp[0] == '\0')
        return 1;
    if (regexp[1] == '*')
        return nk_str_match_star(regexp[0], regexp+2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
        return nk_str_match_here(regexp+1, text+1);
    return 0;
}
NK_INTERN int
nk_str_match_star(int c, const char *regexp, const char *text)
{
    do {
        if (nk_str_match_here(regexp, text))
            return 1;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return 0;
}
NK_API int
nk_strfilter(const char *text, const char *regexp)
{

    if (regexp[0] == '^')
        return nk_str_match_here(regexp+1, text);
    do {
        if (nk_str_match_here(regexp, text))
            return 1;
    } while (*text++ != '\0');
    return 0;
}
NK_API int
nk_strmatch_fuzzy_text(const char *str, int str_len,
    const char *pattern, int *out_score)
{

    #define NK_ADJACENCY_BONUS 5

    #define NK_SEPARATOR_BONUS 10

    #define NK_CAMEL_BONUS 10

    #define NK_LEADING_LETTER_PENALTY (-3)

    #define NK_MAX_LEADING_LETTER_PENALTY (-9)

    #define NK_UNMATCHED_LETTER_PENALTY (-1)

    int score = 0;
    char const * pattern_iter = pattern;
    int str_iter = 0;
    int prev_matched = nk_false;
    int prev_lower = nk_false;

    int prev_separator = nk_true;

    char const * best_letter = 0;
    int best_letter_score = 0;

    NK_ASSERT(str);
    NK_ASSERT(pattern);
    if (!str || !str_len || !pattern) return 0;
    while (str_iter < str_len)
    {
        const char pattern_letter = *pattern_iter;
        const char str_letter = str[str_iter];

        int next_match = *pattern_iter != '\0' &&
            nk_to_lower(pattern_letter) == nk_to_lower(str_letter);
        int rematch = best_letter && nk_to_upper(*best_letter) == nk_to_upper(str_letter);

        int advanced = next_match && best_letter;
        int pattern_repeat = best_letter && *pattern_iter != '\0';
        pattern_repeat = pattern_repeat &&
            nk_to_lower(*best_letter) == nk_to_lower(pattern_letter);

        if (advanced || pattern_repeat) {
            score += best_letter_score;
            best_letter = 0;
            best_letter_score = 0;
        }

        if (next_match || rematch)
        {
            int new_score = 0;

            if (pattern_iter == pattern) {
                int count = (int)(&str[str_iter] - str);
                int penalty = NK_LEADING_LETTER_PENALTY * count;
                if (penalty < NK_MAX_LEADING_LETTER_PENALTY)
                    penalty = NK_MAX_LEADING_LETTER_PENALTY;

                score += penalty;
            }

            if (prev_matched)
                new_score += NK_ADJACENCY_BONUS;

            if (prev_separator)
                new_score += NK_SEPARATOR_BONUS;

            if (prev_lower && nk_is_upper(str_letter))
                new_score += NK_CAMEL_BONUS;

            if (next_match)
                ++pattern_iter;

            if (new_score >= best_letter_score) {

                if (best_letter != 0)
                    score += NK_UNMATCHED_LETTER_PENALTY;

                best_letter = &str[str_iter];
                best_letter_score = new_score;
            }
            prev_matched = nk_true;
        } else {
            score += NK_UNMATCHED_LETTER_PENALTY;
            prev_matched = nk_false;
        }

        prev_lower = nk_is_lower(str_letter) != 0;
        prev_separator = str_letter == '_' || str_letter == ' ';

        ++str_iter;
    }

    if (best_letter)
        score += best_letter_score;

    if (*pattern_iter != '\0')
        return nk_false;

    if (out_score)
        *out_score = score;
    return nk_true;
}
NK_API int
nk_strmatch_fuzzy_string(char const *str, char const *pattern, int *out_score)
{
    return nk_strmatch_fuzzy_text(str, nk_strlen(str), pattern, out_score);
}
NK_LIB int
nk_string_float_limit(char *string, int prec)
{
    int dot = 0;
    char *c = string;
    while (*c) {
        if (*c == '.') {
            dot = 1;
            c++;
            continue;
        }
        if (dot == (prec+1)) {
            *c = 0;
            break;
        }
        if (dot > 0) dot++;
        c++;
    }
    return (int)(c - string);
}
NK_INTERN void
nk_strrev_ascii(char *s)
{
    int len = nk_strlen(s);
    int end = len / 2;
    int i = 0;
    char t;
    for (; i < end; ++i) {
        t = s[i];
        s[i] = s[len - 1 - i];
        s[len -1 - i] = t;
    }
}
NK_LIB char*
nk_itoa(char *s, long n)
{
    long i = 0;
    if (n == 0) {
        s[i++] = '0';
        s[i] = 0;
        return s;
    }
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }
    while (n > 0) {
        s[i++] = (char)('0' + (n % 10));
        n /= 10;
    }
    s[i] = 0;
    if (s[0] == '-')
        ++s;

    nk_strrev_ascii(s);
    return s;
}
#ifndef NK_DTOA
#define NK_DTOA nk_dtoa
NK_LIB char*
nk_dtoa(char *s, double n)
{
    int useExp = 0;
    int digit = 0, m = 0, m1 = 0;
    char *c = s;
    int neg = 0;

    NK_ASSERT(s);
    if (!s) return 0;

    if (n == 0.0) {
        s[0] = '0'; s[1] = '\0';
        return s;
    }

    neg = (n < 0);
    if (neg) n = -n;

    m = nk_log10(n);
    useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
    if (neg) *(c++) = '-';

    if (useExp) {
        if (m < 0)
           m -= 1;
        n = n / (double)nk_pow(10.0, m);
        m1 = m;
        m = 0;
    }
    if (m < 1.0) {
        m = 0;
    }

    while (n > NK_FLOAT_PRECISION || m >= 0) {
        double weight = nk_pow(10.0, m);
        if (weight > 0) {
            double t = (double)n / weight;
            digit = nk_ifloord(t);
            n -= ((double)digit * weight);
            *(c++) = (char)('0' + (char)digit);
        }
        if (m == 0 && n > 0)
            *(c++) = '.';
        m--;
    }

    if (useExp) {

        int i, j;
        *(c++) = 'e';
        if (m1 > 0) {
            *(c++) = '+';
        } else {
            *(c++) = '-';
            m1 = -m1;
        }
        m = 0;
        while (m1 > 0) {
            *(c++) = (char)('0' + (char)(m1 % 10));
            m1 /= 10;
            m++;
        }
        c -= m;
        for (i = 0, j = m-1; i<j; i++, j--) {

            c[i] ^= c[j];
            c[j] ^= c[i];
            c[i] ^= c[j];
        }
        c += m;
    }
    *(c) = '\0';
    return s;
}
#endif
#ifdef NK_INCLUDE_STANDARD_VARARGS
#ifndef NK_INCLUDE_STANDARD_IO
NK_INTERN int
nk_vsnprintf(char *buf, int buf_size, const char *fmt, va_list args)
{
    enum nk_arg_type {
        NK_ARG_TYPE_CHAR,
        NK_ARG_TYPE_SHORT,
        NK_ARG_TYPE_DEFAULT,
        NK_ARG_TYPE_LONG
    };
    enum nk_arg_flags {
        NK_ARG_FLAG_LEFT = 0x01,
        NK_ARG_FLAG_PLUS = 0x02,
        NK_ARG_FLAG_SPACE = 0x04,
        NK_ARG_FLAG_NUM = 0x10,
        NK_ARG_FLAG_ZERO = 0x20
    };

    char number_buffer[NK_MAX_NUMBER_BUFFER];
    enum nk_arg_type arg_type = NK_ARG_TYPE_DEFAULT;
    int precision = NK_DEFAULT;
    int width = NK_DEFAULT;
    nk_flags flag = 0;

    int len = 0;
    int result = -1;
    const char *iter = fmt;

    NK_ASSERT(buf);
    NK_ASSERT(buf_size);
    if (!buf || !buf_size || !fmt) return 0;
    for (iter = fmt; *iter && len < buf_size; iter++) {

        while (*iter && (*iter != '%') && (len < buf_size))
            buf[len++] = *iter++;
        if (!(*iter) || len >= buf_size) break;
        iter++;

        while (*iter) {
            if (*iter == '-') flag |= NK_ARG_FLAG_LEFT;
            else if (*iter == '+') flag |= NK_ARG_FLAG_PLUS;
            else if (*iter == ' ') flag |= NK_ARG_FLAG_SPACE;
            else if (*iter == '#') flag |= NK_ARG_FLAG_NUM;
            else if (*iter == '0') flag |= NK_ARG_FLAG_ZERO;
            else break;
            iter++;
        }

        width = NK_DEFAULT;
        if (*iter >= '1' && *iter <= '9') {
            const char *end;
            width = nk_strtoi(iter, &end);
            if (end == iter)
                width = -1;
            else iter = end;
        } else if (*iter == '*') {
            width = va_arg(args, int);
            iter++;
        }

        precision = NK_DEFAULT;
        if (*iter == '.') {
            iter++;
            if (*iter == '*') {
                precision = va_arg(args, int);
                iter++;
            } else {
                const char *end;
                precision = nk_strtoi(iter, &end);
                if (end == iter)
                    precision = -1;
                else iter = end;
            }
        }

        if (*iter == 'h') {
            if (*(iter+1) == 'h') {
                arg_type = NK_ARG_TYPE_CHAR;
                iter++;
            } else arg_type = NK_ARG_TYPE_SHORT;
            iter++;
        } else if (*iter == 'l') {
            arg_type = NK_ARG_TYPE_LONG;
            iter++;
        } else arg_type = NK_ARG_TYPE_DEFAULT;

        if (*iter == '%') {
            NK_ASSERT(arg_type == NK_ARG_TYPE_DEFAULT);
            NK_ASSERT(precision == NK_DEFAULT);
            NK_ASSERT(width == NK_DEFAULT);
            if (len < buf_size)
                buf[len++] = '%';
        } else if (*iter == 's') {

            const char *str = va_arg(args, const char*);
            NK_ASSERT(str != buf && "buffer and argument are not allowed to overlap!");
            NK_ASSERT(arg_type == NK_ARG_TYPE_DEFAULT);
            NK_ASSERT(precision == NK_DEFAULT);
            NK_ASSERT(width == NK_DEFAULT);
            if (str == buf) return -1;
            while (str && *str && len < buf_size)
                buf[len++] = *str++;
        } else if (*iter == 'n') {

            signed int *n = va_arg(args, int*);
            NK_ASSERT(arg_type == NK_ARG_TYPE_DEFAULT);
            NK_ASSERT(precision == NK_DEFAULT);
            NK_ASSERT(width == NK_DEFAULT);
            if (n) *n = len;
        } else if (*iter == 'c' || *iter == 'i' || *iter == 'd') {

            long value = 0;
            const char *num_iter;
            int num_len, num_print, padding;
            int cur_precision = NK_MAX(precision, 1);
            int cur_width = NK_MAX(width, 0);

            if (arg_type == NK_ARG_TYPE_CHAR)
                value = (signed char)va_arg(args, int);
            else if (arg_type == NK_ARG_TYPE_SHORT)
                value = (signed short)va_arg(args, int);
            else if (arg_type == NK_ARG_TYPE_LONG)
                value = va_arg(args, signed long);
            else if (*iter == 'c')
                value = (unsigned char)va_arg(args, int);
            else value = va_arg(args, signed int);

            nk_itoa(number_buffer, value);
            num_len = nk_strlen(number_buffer);
            padding = NK_MAX(cur_width - NK_MAX(cur_precision, num_len), 0);
            if ((flag & NK_ARG_FLAG_PLUS) || (flag & NK_ARG_FLAG_SPACE))
                padding = NK_MAX(padding-1, 0);

            if (!(flag & NK_ARG_FLAG_LEFT)) {
                while (padding-- > 0 && (len < buf_size)) {
                    if ((flag & NK_ARG_FLAG_ZERO) && (precision == NK_DEFAULT))
                        buf[len++] = '0';
                    else buf[len++] = ' ';
                }
            }

            if ((flag & NK_ARG_FLAG_PLUS) && value >= 0 && len < buf_size)
                buf[len++] = '+';
            else if ((flag & NK_ARG_FLAG_SPACE) && value >= 0 && len < buf_size)
                buf[len++] = ' ';

            num_print = NK_MAX(cur_precision, num_len);
            while (precision && (num_print > num_len) && (len < buf_size)) {
                buf[len++] = '0';
                num_print--;
            }

            num_iter = number_buffer;
            while (precision && *num_iter && len < buf_size)
                buf[len++] = *num_iter++;

            if (flag & NK_ARG_FLAG_LEFT) {
                while ((padding-- > 0) && (len < buf_size))
                    buf[len++] = ' ';
            }
        } else if (*iter == 'o' || *iter == 'x' || *iter == 'X' || *iter == 'u') {

            unsigned long value = 0;
            int num_len = 0, num_print, padding = 0;
            int cur_precision = NK_MAX(precision, 1);
            int cur_width = NK_MAX(width, 0);
            unsigned int base = (*iter == 'o') ? 8: (*iter == 'u')? 10: 16;

            const char *upper_output_format = "0123456789ABCDEF";
            const char *lower_output_format = "0123456789abcdef";
            const char *output_format = (*iter == 'x') ?
                lower_output_format: upper_output_format;

            if (arg_type == NK_ARG_TYPE_CHAR)
                value = (unsigned char)va_arg(args, int);
            else if (arg_type == NK_ARG_TYPE_SHORT)
                value = (unsigned short)va_arg(args, int);
            else if (arg_type == NK_ARG_TYPE_LONG)
                value = va_arg(args, unsigned long);
            else value = va_arg(args, unsigned int);

            do {

                int digit = output_format[value % base];
                if (num_len < NK_MAX_NUMBER_BUFFER)
                    number_buffer[num_len++] = (char)digit;
                value /= base;
            } while (value > 0);

            num_print = NK_MAX(cur_precision, num_len);
            padding = NK_MAX(cur_width - NK_MAX(cur_precision, num_len), 0);
            if (flag & NK_ARG_FLAG_NUM)
                padding = NK_MAX(padding-1, 0);

            if (!(flag & NK_ARG_FLAG_LEFT)) {
                while ((padding-- > 0) && (len < buf_size)) {
                    if ((flag & NK_ARG_FLAG_ZERO) && (precision == NK_DEFAULT))
                        buf[len++] = '0';
                    else buf[len++] = ' ';
                }
            }

            if (num_print && (flag & NK_ARG_FLAG_NUM)) {
                if ((*iter == 'o') && (len < buf_size)) {
                    buf[len++] = '0';
                } else if ((*iter == 'x') && ((len+1) < buf_size)) {
                    buf[len++] = '0';
                    buf[len++] = 'x';
                } else if ((*iter == 'X') && ((len+1) < buf_size)) {
                    buf[len++] = '0';
                    buf[len++] = 'X';
                }
            }
            while (precision && (num_print > num_len) && (len < buf_size)) {
                buf[len++] = '0';
                num_print--;
            }

            while (num_len > 0) {
                if (precision && (len < buf_size))
                    buf[len++] = number_buffer[num_len-1];
                num_len--;
            }

            if (flag & NK_ARG_FLAG_LEFT) {
                while ((padding-- > 0) && (len < buf_size))
                    buf[len++] = ' ';
            }
        } else if (*iter == 'f') {

            const char *num_iter;
            int cur_precision = (precision < 0) ? 6: precision;
            int prefix, cur_width = NK_MAX(width, 0);
            double value = va_arg(args, double);
            int num_len = 0, frac_len = 0, dot = 0;
            int padding = 0;

            NK_ASSERT(arg_type == NK_ARG_TYPE_DEFAULT);
            NK_DTOA(number_buffer, value);
            num_len = nk_strlen(number_buffer);

            num_iter = number_buffer;
            while (*num_iter && *num_iter != '.')
                num_iter++;

            prefix = (*num_iter == '.')?(int)(num_iter - number_buffer)+1:0;
            padding = NK_MAX(cur_width - (prefix + NK_MIN(cur_precision, num_len - prefix)) , 0);
            if ((flag & NK_ARG_FLAG_PLUS) || (flag & NK_ARG_FLAG_SPACE))
                padding = NK_MAX(padding-1, 0);

            if (!(flag & NK_ARG_FLAG_LEFT)) {
                while (padding-- > 0 && (len < buf_size)) {
                    if (flag & NK_ARG_FLAG_ZERO)
                        buf[len++] = '0';
                    else buf[len++] = ' ';
                }
            }

            num_iter = number_buffer;
            if ((flag & NK_ARG_FLAG_PLUS) && (value >= 0) && (len < buf_size))
                buf[len++] = '+';
            else if ((flag & NK_ARG_FLAG_SPACE) && (value >= 0) && (len < buf_size))
                buf[len++] = ' ';
            while (*num_iter) {
                if (dot) frac_len++;
                if (len < buf_size)
                    buf[len++] = *num_iter;
                if (*num_iter == '.') dot = 1;
                if (frac_len >= cur_precision) break;
                num_iter++;
            }

            while (frac_len < cur_precision) {
                if (!dot && len < buf_size) {
                    buf[len++] = '.';
                    dot = 1;
                }
                if (len < buf_size)
                    buf[len++] = '0';
                frac_len++;
            }

            if (flag & NK_ARG_FLAG_LEFT) {
                while ((padding-- > 0) && (len < buf_size))
                    buf[len++] = ' ';
            }
        } else {

            NK_ASSERT(0 && "specifier is not supported!");
            return result;
        }
    }
    buf[(len >= buf_size)?(buf_size-1):len] = 0;
    result = (len >= buf_size)?-1:len;
    return result;
}
#endif
NK_LIB int
nk_strfmt(char *buf, int buf_size, const char *fmt, va_list args)
{
    int result = -1;
    NK_ASSERT(buf);
    NK_ASSERT(buf_size);
    if (!buf || !buf_size || !fmt) return 0;
#ifdef NK_INCLUDE_STANDARD_IO
    result = NK_VSNPRINTF(buf, (nk_size)buf_size, fmt, args);
    result = (result >= buf_size) ? -1: result;
    buf[buf_size-1] = 0;
#else
    result = nk_vsnprintf(buf, buf_size, fmt, args);
#endif
    return result;
}
#endif
NK_API nk_hash
nk_murmur_hash(const void * key, int len, nk_hash seed)
{

    #define NK_ROTL(x,r) ((x) << (r) | ((x) >> (32 - r)))

    nk_uint h1 = seed;
    nk_uint k1;
    const nk_byte *data = (const nk_byte*)key;
    const nk_byte *keyptr = data;
    nk_byte *k1ptr;
    const int bsize = sizeof(k1);
    const int nblocks = len/4;

    const nk_uint c1 = 0xcc9e2d51;
    const nk_uint c2 = 0x1b873593;
    const nk_byte *tail;
    int i;

    if (!key) return 0;
    for (i = 0; i < nblocks; ++i, keyptr += bsize) {
        k1ptr = (nk_byte*)&k1;
        k1ptr[0] = keyptr[0];
        k1ptr[1] = keyptr[1];
        k1ptr[2] = keyptr[2];
        k1ptr[3] = keyptr[3];

        k1 *= c1;
        k1 = NK_ROTL(k1,15);
        k1 *= c2;

        h1 ^= k1;
        h1 = NK_ROTL(h1,13);
        h1 = h1*5+0xe6546b64;
    }

    tail = (const nk_byte*)(data + nblocks*4);
    k1 = 0;
    switch (len & 3) {
        case 3: k1 ^= (nk_uint)(tail[2] << 16); /* fallthrough */
        case 2: k1 ^= (nk_uint)(tail[1] << 8u); /* fallthrough */
        case 1: k1 ^= tail[0];
            k1 *= c1;
            k1 = NK_ROTL(k1,15);
            k1 *= c2;
            h1 ^= k1;
            break;
        default: break;
    }

    h1 ^= (nk_uint)len;

    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    #undef NK_ROTL
    return h1;
}
#ifdef NK_INCLUDE_STANDARD_IO
NK_LIB char*
nk_file_load(const char* path, nk_size* siz, struct nk_allocator *alloc)
{
    char *buf;
    FILE *fd;
    long ret;

    NK_ASSERT(path);
    NK_ASSERT(siz);
    NK_ASSERT(alloc);
    if (!path || !siz || !alloc)
        return 0;

    fd = fopen(path, "rb");
    if (!fd) return 0;
    fseek(fd, 0, SEEK_END);
    ret = ftell(fd);
    if (ret < 0) {
        fclose(fd);
        return 0;
    }
    *siz = (nk_size)ret;
    fseek(fd, 0, SEEK_SET);
    buf = (char*)alloc->alloc(alloc->userdata,0, *siz);
    NK_ASSERT(buf);
    if (!buf) {
        fclose(fd);
        return 0;
    }
    *siz = (nk_size)fread(buf, 1,*siz, fd);
    fclose(fd);
    return buf;
}
#endif
NK_LIB int
nk_text_clamp(const struct nk_user_font *font, const char *text,
    int text_len, float space, int *glyphs, float *text_width,
    nk_rune *sep_list, int sep_count)
{
    int i = 0;
    int glyph_len = 0;
    float last_width = 0;
    nk_rune unicode = 0;
    float width = 0;
    int len = 0;
    int g = 0;
    float s;

    int sep_len = 0;
    int sep_g = 0;
    float sep_width = 0;
    sep_count = NK_MAX(sep_count,0);

    glyph_len = nk_utf_decode(text, &unicode, text_len);
    while (glyph_len && (width < space) && (len < text_len)) {
        len += glyph_len;
        s = font->width(font->userdata, font->height, text, len);
        for (i = 0; i < sep_count; ++i) {
            if (unicode != sep_list[i]) continue;
            sep_width = last_width = width;
            sep_g = g+1;
            sep_len = len;
            break;
        }
        if (i == sep_count){
            last_width = sep_width = width;
            sep_g = g+1;
        }
        width = s;
        glyph_len = nk_utf_decode(&text[len], &unicode, text_len - len);
        g++;
    }
    if (len >= text_len) {
        *glyphs = g;
        *text_width = last_width;
        return len;
    } else {
        *glyphs = sep_g;
        *text_width = sep_width;
        return (!sep_len) ? len: sep_len;
    }
}
NK_LIB struct nk_vec2
nk_text_calculate_text_bounds(const struct nk_user_font *font,
    const char *begin, int byte_len, float row_height, const char **remaining,
    struct nk_vec2 *out_offset, int *glyphs, int op)
{
    float line_height = row_height;
    struct nk_vec2 text_size = nk_vec2(0,0);
    float line_width = 0.0f;

    float glyph_width;
    int glyph_len = 0;
    nk_rune unicode = 0;
    int text_len = 0;
    if (!begin || byte_len <= 0 || !font)
        return nk_vec2(0,row_height);

    glyph_len = nk_utf_decode(begin, &unicode, byte_len);
    if (!glyph_len) return text_size;
    glyph_width = font->width(font->userdata, font->height, begin, glyph_len);

    *glyphs = 0;
    while ((text_len < byte_len) && glyph_len) {
        if (unicode == '\n') {
            text_size.x = NK_MAX(text_size.x, line_width);
            text_size.y += line_height;
            line_width = 0;
            *glyphs+=1;
            if (op == NK_STOP_ON_NEW_LINE)
                break;

            text_len++;
            glyph_len = nk_utf_decode(begin + text_len, &unicode, byte_len-text_len);
            continue;
        }

        if (unicode == '\r') {
            text_len++;
            *glyphs+=1;
            glyph_len = nk_utf_decode(begin + text_len, &unicode, byte_len-text_len);
            continue;
        }

        *glyphs = *glyphs + 1;
        text_len += glyph_len;
        line_width += (float)glyph_width;
        glyph_len = nk_utf_decode(begin + text_len, &unicode, byte_len-text_len);
        glyph_width = font->width(font->userdata, font->height, begin+text_len, glyph_len);
        continue;
    }

    if (text_size.x < line_width)
        text_size.x = line_width;
    if (out_offset)
        *out_offset = nk_vec2(line_width, text_size.y + line_height);
    if (line_width > 0 || text_size.y == 0.0f)
        text_size.y += line_height;
    if (remaining)
        *remaining = begin+text_len;
    return text_size;
}

NK_INTERN int
nk_parse_hex(const char *p, int length)
{
    int i = 0;
    int len = 0;
    while (len < length) {
        i <<= 4;
        if (p[len] >= 'a' && p[len] <= 'f')
            i += ((p[len] - 'a') + 10);
        else if (p[len] >= 'A' && p[len] <= 'F')
            i += ((p[len] - 'A') + 10);
        else i += (p[len] - '0');
        len++;
    }
    return i;
}
NK_API struct nk_color
nk_rgba(int r, int g, int b, int a)
{
    struct nk_color ret;
    ret.r = (nk_byte)NK_CLAMP(0, r, 255);
    ret.g = (nk_byte)NK_CLAMP(0, g, 255);
    ret.b = (nk_byte)NK_CLAMP(0, b, 255);
    ret.a = (nk_byte)NK_CLAMP(0, a, 255);
    return ret;
}
NK_API struct nk_color
nk_rgb_hex(const char *rgb)
{
    struct nk_color col;
    const char *c = rgb;
    if (*c == '#') c++;
    col.r = (nk_byte)nk_parse_hex(c, 2);
    col.g = (nk_byte)nk_parse_hex(c+2, 2);
    col.b = (nk_byte)nk_parse_hex(c+4, 2);
    col.a = 255;
    return col;
}
NK_API struct nk_color
nk_rgba_hex(const char *rgb)
{
    struct nk_color col;
    const char *c = rgb;
    if (*c == '#') c++;
    col.r = (nk_byte)nk_parse_hex(c, 2);
    col.g = (nk_byte)nk_parse_hex(c+2, 2);
    col.b = (nk_byte)nk_parse_hex(c+4, 2);
    col.a = (nk_byte)nk_parse_hex(c+6, 2);
    return col;
}
NK_API void
nk_color_hex_rgba(char *output, struct nk_color col)
{
    #define NK_TO_HEX(i) ((i) <= 9 ? '0' + (i): 'A' - 10 + (i))
    output[0] = (char)NK_TO_HEX((col.r & 0xF0) >> 4);
    output[1] = (char)NK_TO_HEX((col.r & 0x0F));
    output[2] = (char)NK_TO_HEX((col.g & 0xF0) >> 4);
    output[3] = (char)NK_TO_HEX((col.g & 0x0F));
    output[4] = (char)NK_TO_HEX((col.b & 0xF0) >> 4);
    output[5] = (char)NK_TO_HEX((col.b & 0x0F));
    output[6] = (char)NK_TO_HEX((col.a & 0xF0) >> 4);
    output[7] = (char)NK_TO_HEX((col.a & 0x0F));
    output[8] = '\0';
    #undef NK_TO_HEX
}
NK_API void
nk_color_hex_rgb(char *output, struct nk_color col)
{
    #define NK_TO_HEX(i) ((i) <= 9 ? '0' + (i): 'A' - 10 + (i))
    output[0] = (char)NK_TO_HEX((col.r & 0xF0) >> 4);
    output[1] = (char)NK_TO_HEX((col.r & 0x0F));
    output[2] = (char)NK_TO_HEX((col.g & 0xF0) >> 4);
    output[3] = (char)NK_TO_HEX((col.g & 0x0F));
    output[4] = (char)NK_TO_HEX((col.b & 0xF0) >> 4);
    output[5] = (char)NK_TO_HEX((col.b & 0x0F));
    output[6] = '\0';
    #undef NK_TO_HEX
}
NK_API struct nk_color
nk_rgba_iv(const int *c)
{
    return nk_rgba(c[0], c[1], c[2], c[3]);
}
NK_API struct nk_color
nk_rgba_bv(const nk_byte *c)
{
    return nk_rgba(c[0], c[1], c[2], c[3]);
}
NK_API struct nk_color
nk_rgb(int r, int g, int b)
{
    struct nk_color ret;
    ret.r = (nk_byte)NK_CLAMP(0, r, 255);
    ret.g = (nk_byte)NK_CLAMP(0, g, 255);
    ret.b = (nk_byte)NK_CLAMP(0, b, 255);
    ret.a = (nk_byte)255;
    return ret;
}
NK_API struct nk_color
nk_rgb_iv(const int *c)
{
    return nk_rgb(c[0], c[1], c[2]);
}
NK_API struct nk_color
nk_rgb_bv(const nk_byte* c)
{
    return nk_rgb(c[0], c[1], c[2]);
}
NK_API struct nk_color
nk_rgba_u32(nk_uint in)
{
    struct nk_color ret;
    ret.r = (in & 0xFF);
    ret.g = ((in >> 8) & 0xFF);
    ret.b = ((in >> 16) & 0xFF);
    ret.a = (nk_byte)((in >> 24) & 0xFF);
    return ret;
}
NK_API struct nk_color
nk_rgba_f(float r, float g, float b, float a)
{
    struct nk_color ret;
    ret.r = (nk_byte)(NK_SATURATE(r) * 255.0f);
    ret.g = (nk_byte)(NK_SATURATE(g) * 255.0f);
    ret.b = (nk_byte)(NK_SATURATE(b) * 255.0f);
    ret.a = (nk_byte)(NK_SATURATE(a) * 255.0f);
    return ret;
}
NK_API struct nk_color
nk_rgba_fv(const float *c)
{
    return nk_rgba_f(c[0], c[1], c[2], c[3]);
}
NK_API struct nk_color
nk_rgba_cf(struct nk_colorf c)
{
    return nk_rgba_f(c.r, c.g, c.b, c.a);
}
NK_API struct nk_color
nk_rgb_f(float r, float g, float b)
{
    struct nk_color ret;
    ret.r = (nk_byte)(NK_SATURATE(r) * 255.0f);
    ret.g = (nk_byte)(NK_SATURATE(g) * 255.0f);
    ret.b = (nk_byte)(NK_SATURATE(b) * 255.0f);
    ret.a = 255;
    return ret;
}
NK_API struct nk_color
nk_rgb_fv(const float *c)
{
    return nk_rgb_f(c[0], c[1], c[2]);
}
NK_API struct nk_color
nk_rgb_cf(struct nk_colorf c)
{
    return nk_rgb_f(c.r, c.g, c.b);
}
NK_API struct nk_color
nk_hsv(int h, int s, int v)
{
    return nk_hsva(h, s, v, 255);
}
NK_API struct nk_color
nk_hsv_iv(const int *c)
{
    return nk_hsv(c[0], c[1], c[2]);
}
NK_API struct nk_color
nk_hsv_bv(const nk_byte *c)
{
    return nk_hsv(c[0], c[1], c[2]);
}
NK_API struct nk_color
nk_hsv_f(float h, float s, float v)
{
    return nk_hsva_f(h, s, v, 1.0f);
}
NK_API struct nk_color
nk_hsv_fv(const float *c)
{
    return nk_hsv_f(c[0], c[1], c[2]);
}
NK_API struct nk_color
nk_hsva(int h, int s, int v, int a)
{
    float hf = ((float)NK_CLAMP(0, h, 255)) / 255.0f;
    float sf = ((float)NK_CLAMP(0, s, 255)) / 255.0f;
    float vf = ((float)NK_CLAMP(0, v, 255)) / 255.0f;
    float af = ((float)NK_CLAMP(0, a, 255)) / 255.0f;
    return nk_hsva_f(hf, sf, vf, af);
}
NK_API struct nk_color
nk_hsva_iv(const int *c)
{
    return nk_hsva(c[0], c[1], c[2], c[3]);
}
NK_API struct nk_color
nk_hsva_bv(const nk_byte *c)
{
    return nk_hsva(c[0], c[1], c[2], c[3]);
}
NK_API struct nk_colorf
nk_hsva_colorf(float h, float s, float v, float a)
{
    int i;
    float p, q, t, f;
    struct nk_colorf out = {0,0,0,0};
    if (s <= 0.0f) {
        out.r = v; out.g = v; out.b = v; out.a = a;
        return out;
    }
    h = h / (60.0f/360.0f);
    i = (int)h;
    f = h - (float)i;
    p = v * (1.0f - s);
    q = v * (1.0f - (s * f));
    t = v * (1.0f - s * (1.0f - f));

    switch (i) {
    case 0: default: out.r = v; out.g = t; out.b = p; break;
    case 1: out.r = q; out.g = v; out.b = p; break;
    case 2: out.r = p; out.g = v; out.b = t; break;
    case 3: out.r = p; out.g = q; out.b = v; break;
    case 4: out.r = t; out.g = p; out.b = v; break;
    case 5: out.r = v; out.g = p; out.b = q; break;}
    out.a = a;
    return out;
}
NK_API struct nk_colorf
nk_hsva_colorfv(float *c)
{
    return nk_hsva_colorf(c[0], c[1], c[2], c[3]);
}
NK_API struct nk_color
nk_hsva_f(float h, float s, float v, float a)
{
    struct nk_colorf c = nk_hsva_colorf(h, s, v, a);
    return nk_rgba_f(c.r, c.g, c.b, c.a);
}
NK_API struct nk_color
nk_hsva_fv(const float *c)
{
    return nk_hsva_f(c[0], c[1], c[2], c[3]);
}
NK_API nk_uint
nk_color_u32(struct nk_color in)
{
    nk_uint out = (nk_uint)in.r;
    out |= ((nk_uint)in.g << 8);
    out |= ((nk_uint)in.b << 16);
    out |= ((nk_uint)in.a << 24);
    return out;
}
NK_API void
nk_color_f(float *r, float *g, float *b, float *a, struct nk_color in)
{
    NK_STORAGE const float s = 1.0f/255.0f;
    *r = (float)in.r * s;
    *g = (float)in.g * s;
    *b = (float)in.b * s;
    *a = (float)in.a * s;
}
NK_API void
nk_color_fv(float *c, struct nk_color in)
{
    nk_color_f(&c[0], &c[1], &c[2], &c[3], in);
}
NK_API struct nk_colorf
nk_color_cf(struct nk_color in)
{
    struct nk_colorf o;
    nk_color_f(&o.r, &o.g, &o.b, &o.a, in);
    return o;
}
NK_API void
nk_color_d(double *r, double *g, double *b, double *a, struct nk_color in)
{
    NK_STORAGE const double s = 1.0/255.0;
    *r = (double)in.r * s;
    *g = (double)in.g * s;
    *b = (double)in.b * s;
    *a = (double)in.a * s;
}
NK_API void
nk_color_dv(double *c, struct nk_color in)
{
    nk_color_d(&c[0], &c[1], &c[2], &c[3], in);
}
NK_API void
nk_color_hsv_f(float *out_h, float *out_s, float *out_v, struct nk_color in)
{
    float a;
    nk_color_hsva_f(out_h, out_s, out_v, &a, in);
}
NK_API void
nk_color_hsv_fv(float *out, struct nk_color in)
{
    float a;
    nk_color_hsva_f(&out[0], &out[1], &out[2], &a, in);
}
NK_API void
nk_colorf_hsva_f(float *out_h, float *out_s,
    float *out_v, float *out_a, struct nk_colorf in)
{
    float chroma;
    float K = 0.0f;
    if (in.g < in.b) {
        const float t = in.g; in.g = in.b; in.b = t;
        K = -1.f;
    }
    if (in.r < in.g) {
        const float t = in.r; in.r = in.g; in.g = t;
        K = -2.f/6.0f - K;
    }
    chroma = in.r - ((in.g < in.b) ? in.g: in.b);
    *out_h = NK_ABS(K + (in.g - in.b)/(6.0f * chroma + 1e-20f));
    *out_s = chroma / (in.r + 1e-20f);
    *out_v = in.r;
    *out_a = in.a;

}
NK_API void
nk_colorf_hsva_fv(float *hsva, struct nk_colorf in)
{
    nk_colorf_hsva_f(&hsva[0], &hsva[1], &hsva[2], &hsva[3], in);
}
NK_API void
nk_color_hsva_f(float *out_h, float *out_s,
    float *out_v, float *out_a, struct nk_color in)
{
    struct nk_colorf col;
    nk_color_f(&col.r,&col.g,&col.b,&col.a, in);
    nk_colorf_hsva_f(out_h, out_s, out_v, out_a, col);
}
NK_API void
nk_color_hsva_fv(float *out, struct nk_color in)
{
    nk_color_hsva_f(&out[0], &out[1], &out[2], &out[3], in);
}
NK_API void
nk_color_hsva_i(int *out_h, int *out_s, int *out_v,
                int *out_a, struct nk_color in)
{
    float h,s,v,a;
    nk_color_hsva_f(&h, &s, &v, &a, in);
    *out_h = (nk_byte)(h * 255.0f);
    *out_s = (nk_byte)(s * 255.0f);
    *out_v = (nk_byte)(v * 255.0f);
    *out_a = (nk_byte)(a * 255.0f);
}
NK_API void
nk_color_hsva_iv(int *out, struct nk_color in)
{
    nk_color_hsva_i(&out[0], &out[1], &out[2], &out[3], in);
}
NK_API void
nk_color_hsva_bv(nk_byte *out, struct nk_color in)
{
    int tmp[4];
    nk_color_hsva_i(&tmp[0], &tmp[1], &tmp[2], &tmp[3], in);
    out[0] = (nk_byte)tmp[0];
    out[1] = (nk_byte)tmp[1];
    out[2] = (nk_byte)tmp[2];
    out[3] = (nk_byte)tmp[3];
}
NK_API void
nk_color_hsva_b(nk_byte *h, nk_byte *s, nk_byte *v, nk_byte *a, struct nk_color in)
{
    int tmp[4];
    nk_color_hsva_i(&tmp[0], &tmp[1], &tmp[2], &tmp[3], in);
    *h = (nk_byte)tmp[0];
    *s = (nk_byte)tmp[1];
    *v = (nk_byte)tmp[2];
    *a = (nk_byte)tmp[3];
}
NK_API void
nk_color_hsv_i(int *out_h, int *out_s, int *out_v, struct nk_color in)
{
    int a;
    nk_color_hsva_i(out_h, out_s, out_v, &a, in);
}
NK_API void
nk_color_hsv_b(nk_byte *out_h, nk_byte *out_s, nk_byte *out_v, struct nk_color in)
{
    int tmp[4];
    nk_color_hsva_i(&tmp[0], &tmp[1], &tmp[2], &tmp[3], in);
    *out_h = (nk_byte)tmp[0];
    *out_s = (nk_byte)tmp[1];
    *out_v = (nk_byte)tmp[2];
}
NK_API void
nk_color_hsv_iv(int *out, struct nk_color in)
{
    nk_color_hsv_i(&out[0], &out[1], &out[2], in);
}
NK_API void
nk_color_hsv_bv(nk_byte *out, struct nk_color in)
{
    int tmp[4];
    nk_color_hsv_i(&tmp[0], &tmp[1], &tmp[2], in);
    out[0] = (nk_byte)tmp[0];
    out[1] = (nk_byte)tmp[1];
    out[2] = (nk_byte)tmp[2];
}

NK_GLOBAL const nk_byte nk_utfbyte[NK_UTF_SIZE+1] = {0x80, 0, 0xC0, 0xE0, 0xF0};
NK_GLOBAL const nk_byte nk_utfmask[NK_UTF_SIZE+1] = {0xC0, 0x80, 0xE0, 0xF0, 0xF8};
NK_GLOBAL const nk_uint nk_utfmin[NK_UTF_SIZE+1] = {0, 0, 0x80, 0x800, 0x10000};
NK_GLOBAL const nk_uint nk_utfmax[NK_UTF_SIZE+1] = {0x10FFFF, 0x7F, 0x7FF, 0xFFFF, 0x10FFFF};

NK_INTERN int
nk_utf_validate(nk_rune *u, int i)
{
    NK_ASSERT(u);
    if (!u) return 0;
    if (!NK_BETWEEN(*u, nk_utfmin[i], nk_utfmax[i]) ||
         NK_BETWEEN(*u, 0xD800, 0xDFFF))
            *u = NK_UTF_INVALID;
    for (i = 1; *u > nk_utfmax[i]; ++i);
    return i;
}
NK_INTERN nk_rune
nk_utf_decode_byte(char c, int *i)
{
    NK_ASSERT(i);
    if (!i) return 0;
    for(*i = 0; *i < (int)NK_LEN(nk_utfmask); ++(*i)) {
        if (((nk_byte)c & nk_utfmask[*i]) == nk_utfbyte[*i])
            return (nk_byte)(c & ~nk_utfmask[*i]);
    }
    return 0;
}
NK_API int
nk_utf_decode(const char *c, nk_rune *u, int clen)
{
    int i, j, len, type=0;
    nk_rune udecoded;

    NK_ASSERT(c);
    NK_ASSERT(u);

    if (!c || !u) return 0;
    if (!clen) return 0;
    *u = NK_UTF_INVALID;

    udecoded = nk_utf_decode_byte(c[0], &len);
    if (!NK_BETWEEN(len, 1, NK_UTF_SIZE))
        return 1;

    for (i = 1, j = 1; i < clen && j < len; ++i, ++j) {
        udecoded = (udecoded << 6) | nk_utf_decode_byte(c[i], &type);
        if (type != 0)
            return j;
    }
    if (j < len)
        return 0;
    *u = udecoded;
    nk_utf_validate(u, len);
    return len;
}
NK_INTERN char
nk_utf_encode_byte(nk_rune u, int i)
{
    return (char)((nk_utfbyte[i]) | ((nk_byte)u & ~nk_utfmask[i]));
}
NK_API int
nk_utf_encode(nk_rune u, char *c, int clen)
{
    int len, i;
    len = nk_utf_validate(&u, 0);
    if (clen < len || !len || len > NK_UTF_SIZE)
        return 0;

    for (i = len - 1; i != 0; --i) {
        c[i] = nk_utf_encode_byte(u, 0);
        u >>= 6;
    }
    c[0] = nk_utf_encode_byte(u, len);
    return len;
}
NK_API int
nk_utf_len(const char *str, int len)
{
    const char *text;
    int glyphs = 0;
    int text_len;
    int glyph_len;
    int src_len = 0;
    nk_rune unicode;

    NK_ASSERT(str);
    if (!str || !len) return 0;

    text = str;
    text_len = len;
    glyph_len = nk_utf_decode(text, &unicode, text_len);
    while (glyph_len && src_len < len) {
        glyphs++;
        src_len = src_len + glyph_len;
        glyph_len = nk_utf_decode(text + src_len, &unicode, text_len - src_len);
    }
    return glyphs;
}
NK_API const char*
nk_utf_at(const char *buffer, int length, int index,
    nk_rune *unicode, int *len)
{
    int i = 0;
    int src_len = 0;
    int glyph_len = 0;
    const char *text;
    int text_len;

    NK_ASSERT(buffer);
    NK_ASSERT(unicode);
    NK_ASSERT(len);

    if (!buffer || !unicode || !len) return 0;
    if (index < 0) {
        *unicode = NK_UTF_INVALID;
        *len = 0;
        return 0;
    }

    text = buffer;
    text_len = length;
    glyph_len = nk_utf_decode(text, unicode, text_len);
    while (glyph_len) {
        if (i == index) {
            *len = glyph_len;
            break;
        }

        i++;
        src_len = src_len + glyph_len;
        glyph_len = nk_utf_decode(text + src_len, unicode, text_len - src_len);
    }
    if (i != index) return 0;
    return buffer + src_len;
}

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_LIB void*
nk_malloc(nk_handle unused, void *old,nk_size size)
{
    NK_UNUSED(unused);
    NK_UNUSED(old);
    return malloc(size);
}
NK_LIB void
nk_mfree(nk_handle unused, void *ptr)
{
    NK_UNUSED(unused);
    free(ptr);
}
NK_API void
nk_buffer_init_default(struct nk_buffer *buffer)
{
    struct nk_allocator alloc;
    alloc.userdata.ptr = 0;
    alloc.alloc = nk_malloc;
    alloc.free = nk_mfree;
    nk_buffer_init(buffer, &alloc, NK_BUFFER_DEFAULT_INITIAL_SIZE);
}
#endif

NK_API void
nk_buffer_init(struct nk_buffer *b, const struct nk_allocator *a,
    nk_size initial_size)
{
    NK_ASSERT(b);
    NK_ASSERT(a);
    NK_ASSERT(initial_size);
    if (!b || !a || !initial_size) return;

    nk_zero(b, sizeof(*b));
    b->type = NK_BUFFER_DYNAMIC;
    b->memory.ptr = a->alloc(a->userdata,0, initial_size);
    b->memory.size = initial_size;
    b->size = initial_size;
    b->grow_factor = 2.0f;
    b->pool = *a;
}
NK_API void
nk_buffer_init_fixed(struct nk_buffer *b, void *m, nk_size size)
{
    NK_ASSERT(b);
    NK_ASSERT(m);
    NK_ASSERT(size);
    if (!b || !m || !size) return;

    nk_zero(b, sizeof(*b));
    b->type = NK_BUFFER_FIXED;
    b->memory.ptr = m;
    b->memory.size = size;
    b->size = size;
}
NK_LIB void*
nk_buffer_align(void *unaligned,
    nk_size align, nk_size *alignment,
    enum nk_buffer_allocation_type type)
{
    void *memory = 0;
    switch (type) {
    default:
    case NK_BUFFER_MAX:
    case NK_BUFFER_FRONT:
        if (align) {
            memory = NK_ALIGN_PTR(unaligned, align);
            *alignment = (nk_size)((nk_byte*)memory - (nk_byte*)unaligned);
        } else {
            memory = unaligned;
            *alignment = 0;
        }
        break;
    case NK_BUFFER_BACK:
        if (align) {
            memory = NK_ALIGN_PTR_BACK(unaligned, align);
            *alignment = (nk_size)((nk_byte*)unaligned - (nk_byte*)memory);
        } else {
            memory = unaligned;
            *alignment = 0;
        }
        break;
    }
    return memory;
}
NK_LIB void*
nk_buffer_realloc(struct nk_buffer *b, nk_size capacity, nk_size *size)
{
    void *temp;
    nk_size buffer_size;

    NK_ASSERT(b);
    NK_ASSERT(size);
    if (!b || !size || !b->pool.alloc || !b->pool.free)
        return 0;

    buffer_size = b->memory.size;
    temp = b->pool.alloc(b->pool.userdata, b->memory.ptr, capacity);
    NK_ASSERT(temp);
    if (!temp) return 0;

    *size = capacity;
    if (temp != b->memory.ptr) {
        NK_MEMCPY(temp, b->memory.ptr, buffer_size);
        b->pool.free(b->pool.userdata, b->memory.ptr);
    }

    if (b->size == buffer_size) {

        b->size = capacity;
        return temp;
    } else {

        void *dst, *src;
        nk_size back_size;
        back_size = buffer_size - b->size;
        dst = nk_ptr_add(void, temp, capacity - back_size);
        src = nk_ptr_add(void, temp, b->size);
        NK_MEMCPY(dst, src, back_size);
        b->size = capacity - back_size;
    }
    return temp;
}
NK_LIB void*
nk_buffer_alloc(struct nk_buffer *b, enum nk_buffer_allocation_type type,
    nk_size size, nk_size align)
{
    int full;
    nk_size alignment;
    void *unaligned;
    void *memory;

    NK_ASSERT(b);
    NK_ASSERT(size);
    if (!b || !size) return 0;
    b->needed += size;

    if (type == NK_BUFFER_FRONT)
        unaligned = nk_ptr_add(void, b->memory.ptr, b->allocated);
    else unaligned = nk_ptr_add(void, b->memory.ptr, b->size - size);
    memory = nk_buffer_align(unaligned, align, &alignment, type);

    if (type == NK_BUFFER_FRONT)
        full = ((b->allocated + size + alignment) > b->size);
    else full = ((b->size - NK_MIN(b->size,(size + alignment))) <= b->allocated);

    if (full) {
        nk_size capacity;
        if (b->type != NK_BUFFER_DYNAMIC)
            return 0;
        NK_ASSERT(b->pool.alloc && b->pool.free);
        if (b->type != NK_BUFFER_DYNAMIC || !b->pool.alloc || !b->pool.free)
            return 0;

        capacity = (nk_size)((float)b->memory.size * b->grow_factor);
        capacity = NK_MAX(capacity, nk_round_up_pow2((nk_uint)(b->allocated + size)));
        b->memory.ptr = nk_buffer_realloc(b, capacity, &b->memory.size);
        if (!b->memory.ptr) return 0;

        if (type == NK_BUFFER_FRONT)
            unaligned = nk_ptr_add(void, b->memory.ptr, b->allocated);
        else unaligned = nk_ptr_add(void, b->memory.ptr, b->size - size);
        memory = nk_buffer_align(unaligned, align, &alignment, type);
    }
    if (type == NK_BUFFER_FRONT)
        b->allocated += size + alignment;
    else b->size -= (size + alignment);
    b->needed += alignment;
    b->calls++;
    return memory;
}
NK_API void
nk_buffer_push(struct nk_buffer *b, enum nk_buffer_allocation_type type,
    const void *memory, nk_size size, nk_size align)
{
    void *mem = nk_buffer_alloc(b, type, size, align);
    if (!mem) return;
    NK_MEMCPY(mem, memory, size);
}
NK_API void
nk_buffer_mark(struct nk_buffer *buffer, enum nk_buffer_allocation_type type)
{
    NK_ASSERT(buffer);
    if (!buffer) return;
    buffer->marker[type].active = nk_true;
    if (type == NK_BUFFER_BACK)
        buffer->marker[type].offset = buffer->size;
    else buffer->marker[type].offset = buffer->allocated;
}
NK_API void
nk_buffer_reset(struct nk_buffer *buffer, enum nk_buffer_allocation_type type)
{
    NK_ASSERT(buffer);
    if (!buffer) return;
    if (type == NK_BUFFER_BACK) {

        buffer->needed -= (buffer->memory.size - buffer->marker[type].offset);
        if (buffer->marker[type].active)
            buffer->size = buffer->marker[type].offset;
        else buffer->size = buffer->memory.size;
        buffer->marker[type].active = nk_false;
    } else {

        buffer->needed -= (buffer->allocated - buffer->marker[type].offset);
        if (buffer->marker[type].active)
            buffer->allocated = buffer->marker[type].offset;
        else buffer->allocated = 0;
        buffer->marker[type].active = nk_false;
    }
}
NK_API void
nk_buffer_clear(struct nk_buffer *b)
{
    NK_ASSERT(b);
    if (!b) return;
    b->allocated = 0;
    b->size = b->memory.size;
    b->calls = 0;
    b->needed = 0;
}
NK_API void
nk_buffer_free(struct nk_buffer *b)
{
    NK_ASSERT(b);
    if (!b || !b->memory.ptr) return;
    if (b->type == NK_BUFFER_FIXED) return;
    if (!b->pool.free) return;
    NK_ASSERT(b->pool.free);
    b->pool.free(b->pool.userdata, b->memory.ptr);
}
NK_API void
nk_buffer_info(struct nk_memory_status *s, struct nk_buffer *b)
{
    NK_ASSERT(b);
    NK_ASSERT(s);
    if (!s || !b) return;
    s->allocated = b->allocated;
    s->size =  b->memory.size;
    s->needed = b->needed;
    s->memory = b->memory.ptr;
    s->calls = b->calls;
}
NK_API void*
nk_buffer_memory(struct nk_buffer *buffer)
{
    NK_ASSERT(buffer);
    if (!buffer) return 0;
    return buffer->memory.ptr;
}
NK_API const void*
nk_buffer_memory_const(const struct nk_buffer *buffer)
{
    NK_ASSERT(buffer);
    if (!buffer) return 0;
    return buffer->memory.ptr;
}
NK_API nk_size
nk_buffer_total(struct nk_buffer *buffer)
{
    NK_ASSERT(buffer);
    if (!buffer) return 0;
    return buffer->memory.size;
}

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void
nk_str_init_default(struct nk_str *str)
{
    struct nk_allocator alloc;
    alloc.userdata.ptr = 0;
    alloc.alloc = nk_malloc;
    alloc.free = nk_mfree;
    nk_buffer_init(&str->buffer, &alloc, 32);
    str->len = 0;
}
#endif

NK_API void
nk_str_init(struct nk_str *str, const struct nk_allocator *alloc, nk_size size)
{
    nk_buffer_init(&str->buffer, alloc, size);
    str->len = 0;
}
NK_API void
nk_str_init_fixed(struct nk_str *str, void *memory, nk_size size)
{
    nk_buffer_init_fixed(&str->buffer, memory, size);
    str->len = 0;
}
NK_API int
nk_str_append_text_char(struct nk_str *s, const char *str, int len)
{
    char *mem;
    NK_ASSERT(s);
    NK_ASSERT(str);
    if (!s || !str || !len) return 0;
    mem = (char*)nk_buffer_alloc(&s->buffer, NK_BUFFER_FRONT, (nk_size)len * sizeof(char), 0);
    if (!mem) return 0;
    NK_MEMCPY(mem, str, (nk_size)len * sizeof(char));
    s->len += nk_utf_len(str, len);
    return len;
}
NK_API int
nk_str_append_str_char(struct nk_str *s, const char *str)
{
    return nk_str_append_text_char(s, str, nk_strlen(str));
}
NK_API int
nk_str_append_text_utf8(struct nk_str *str, const char *text, int len)
{
    int i = 0;
    int byte_len = 0;
    nk_rune unicode;
    if (!str || !text || !len) return 0;
    for (i = 0; i < len; ++i)
        byte_len += nk_utf_decode(text+byte_len, &unicode, 4);
    nk_str_append_text_char(str, text, byte_len);
    return len;
}
NK_API int
nk_str_append_str_utf8(struct nk_str *str, const char *text)
{
    int byte_len = 0;
    int num_runes = 0;
    int glyph_len = 0;
    nk_rune unicode;
    if (!str || !text) return 0;

    glyph_len = byte_len = nk_utf_decode(text+byte_len, &unicode, 4);
    while (unicode != '\0' && glyph_len) {
        glyph_len = nk_utf_decode(text+byte_len, &unicode, 4);
        byte_len += glyph_len;
        num_runes++;
    }
    nk_str_append_text_char(str, text, byte_len);
    return num_runes;
}
NK_API int
nk_str_append_text_runes(struct nk_str *str, const nk_rune *text, int len)
{
    int i = 0;
    int byte_len = 0;
    nk_glyph glyph;

    NK_ASSERT(str);
    if (!str || !text || !len) return 0;
    for (i = 0; i < len; ++i) {
        byte_len = nk_utf_encode(text[i], glyph, NK_UTF_SIZE);
        if (!byte_len) break;
        nk_str_append_text_char(str, glyph, byte_len);
    }
    return len;
}
NK_API int
nk_str_append_str_runes(struct nk_str *str, const nk_rune *runes)
{
    int i = 0;
    nk_glyph glyph;
    int byte_len;
    NK_ASSERT(str);
    if (!str || !runes) return 0;
    while (runes[i] != '\0') {
        byte_len = nk_utf_encode(runes[i], glyph, NK_UTF_SIZE);
        nk_str_append_text_char(str, glyph, byte_len);
        i++;
    }
    return i;
}
NK_API int
nk_str_insert_at_char(struct nk_str *s, int pos, const char *str, int len)
{
    int i;
    void *mem;
    char *src;
    char *dst;

    int copylen;
    NK_ASSERT(s);
    NK_ASSERT(str);
    NK_ASSERT(len >= 0);
    if (!s || !str || !len || (nk_size)pos > s->buffer.allocated) return 0;
    if ((s->buffer.allocated + (nk_size)len >= s->buffer.memory.size) &&
        (s->buffer.type == NK_BUFFER_FIXED)) return 0;

    copylen = (int)s->buffer.allocated - pos;
    if (!copylen) {
        nk_str_append_text_char(s, str, len);
        return 1;
    }
    mem = nk_buffer_alloc(&s->buffer, NK_BUFFER_FRONT, (nk_size)len * sizeof(char), 0);
    if (!mem) return 0;

    NK_ASSERT(((int)pos + (int)len + ((int)copylen - 1)) >= 0);
    NK_ASSERT(((int)pos + ((int)copylen - 1)) >= 0);
    dst = nk_ptr_add(char, s->buffer.memory.ptr, pos + len + (copylen - 1));
    src = nk_ptr_add(char, s->buffer.memory.ptr, pos + (copylen-1));
    for (i = 0; i < copylen; ++i) *dst-- = *src--;
    mem = nk_ptr_add(void, s->buffer.memory.ptr, pos);
    NK_MEMCPY(mem, str, (nk_size)len * sizeof(char));
    s->len = nk_utf_len((char *)s->buffer.memory.ptr, (int)s->buffer.allocated);
    return 1;
}
NK_API int
nk_str_insert_at_rune(struct nk_str *str, int pos, const char *cstr, int len)
{
    int glyph_len;
    nk_rune unicode;
    const char *begin;
    const char *buffer;

    NK_ASSERT(str);
    NK_ASSERT(cstr);
    NK_ASSERT(len);
    if (!str || !cstr || !len) return 0;
    begin = nk_str_at_rune(str, pos, &unicode, &glyph_len);
    if (!str->len)
        return nk_str_append_text_char(str, cstr, len);
    buffer = nk_str_get_const(str);
    if (!begin) return 0;
    return nk_str_insert_at_char(str, (int)(begin - buffer), cstr, len);
}
NK_API int
nk_str_insert_text_char(struct nk_str *str, int pos, const char *text, int len)
{
    return nk_str_insert_text_utf8(str, pos, text, len);
}
NK_API int
nk_str_insert_str_char(struct nk_str *str, int pos, const char *text)
{
    return nk_str_insert_text_utf8(str, pos, text, nk_strlen(text));
}
NK_API int
nk_str_insert_text_utf8(struct nk_str *str, int pos, const char *text, int len)
{
    int i = 0;
    int byte_len = 0;
    nk_rune unicode;

    NK_ASSERT(str);
    NK_ASSERT(text);
    if (!str || !text || !len) return 0;
    for (i = 0; i < len; ++i)
        byte_len += nk_utf_decode(text+byte_len, &unicode, 4);
    nk_str_insert_at_rune(str, pos, text, byte_len);
    return len;
}
NK_API int
nk_str_insert_str_utf8(struct nk_str *str, int pos, const char *text)
{
    int byte_len = 0;
    int num_runes = 0;
    int glyph_len = 0;
    nk_rune unicode;
    if (!str || !text) return 0;

    glyph_len = byte_len = nk_utf_decode(text+byte_len, &unicode, 4);
    while (unicode != '\0' && glyph_len) {
        glyph_len = nk_utf_decode(text+byte_len, &unicode, 4);
        byte_len += glyph_len;
        num_runes++;
    }
    nk_str_insert_at_rune(str, pos, text, byte_len);
    return num_runes;
}
NK_API int
nk_str_insert_text_runes(struct nk_str *str, int pos, const nk_rune *runes, int len)
{
    int i = 0;
    int byte_len = 0;
    nk_glyph glyph;

    NK_ASSERT(str);
    if (!str || !runes || !len) return 0;
    for (i = 0; i < len; ++i) {
        byte_len = nk_utf_encode(runes[i], glyph, NK_UTF_SIZE);
        if (!byte_len) break;
        nk_str_insert_at_rune(str, pos+i, glyph, byte_len);
    }
    return len;
}
NK_API int
nk_str_insert_str_runes(struct nk_str *str, int pos, const nk_rune *runes)
{
    int i = 0;
    nk_glyph glyph;
    int byte_len;
    NK_ASSERT(str);
    if (!str || !runes) return 0;
    while (runes[i] != '\0') {
        byte_len = nk_utf_encode(runes[i], glyph, NK_UTF_SIZE);
        nk_str_insert_at_rune(str, pos+i, glyph, byte_len);
        i++;
    }
    return i;
}
NK_API void
nk_str_remove_chars(struct nk_str *s, int len)
{
    NK_ASSERT(s);
    NK_ASSERT(len >= 0);
    if (!s || len < 0 || (nk_size)len > s->buffer.allocated) return;
    NK_ASSERT(((int)s->buffer.allocated - (int)len) >= 0);
    s->buffer.allocated -= (nk_size)len;
    s->len = nk_utf_len((char *)s->buffer.memory.ptr, (int)s->buffer.allocated);
}
NK_API void
nk_str_remove_runes(struct nk_str *str, int len)
{
    int index;
    const char *begin;
    const char *end;
    nk_rune unicode;

    NK_ASSERT(str);
    NK_ASSERT(len >= 0);
    if (!str || len < 0) return;
    if (len >= str->len) {
        str->len = 0;
        return;
    }

    index = str->len - len;
    begin = nk_str_at_rune(str, index, &unicode, &len);
    end = (const char*)str->buffer.memory.ptr + str->buffer.allocated;
    nk_str_remove_chars(str, (int)(end-begin)+1);
}
NK_API void
nk_str_delete_chars(struct nk_str *s, int pos, int len)
{
    NK_ASSERT(s);
    if (!s || !len || (nk_size)pos > s->buffer.allocated ||
        (nk_size)(pos + len) > s->buffer.allocated) return;

    if ((nk_size)(pos + len) < s->buffer.allocated) {

        char *dst = nk_ptr_add(char, s->buffer.memory.ptr, pos);
        char *src = nk_ptr_add(char, s->buffer.memory.ptr, pos + len);
        NK_MEMCPY(dst, src, s->buffer.allocated - (nk_size)(pos + len));
        NK_ASSERT(((int)s->buffer.allocated - (int)len) >= 0);
        s->buffer.allocated -= (nk_size)len;
    } else nk_str_remove_chars(s, len);
    s->len = nk_utf_len((char *)s->buffer.memory.ptr, (int)s->buffer.allocated);
}
NK_API void
nk_str_delete_runes(struct nk_str *s, int pos, int len)
{
    char *temp;
    nk_rune unicode;
    char *begin;
    char *end;
    int unused;

    NK_ASSERT(s);
    NK_ASSERT(s->len >= pos + len);
    if (s->len < pos + len)
        len = NK_CLAMP(0, (s->len - pos), s->len);
    if (!len) return;

    temp = (char *)s->buffer.memory.ptr;
    begin = nk_str_at_rune(s, pos, &unicode, &unused);
    if (!begin) return;
    s->buffer.memory.ptr = begin;
    end = nk_str_at_rune(s, len, &unicode, &unused);
    s->buffer.memory.ptr = temp;
    if (!end) return;
    nk_str_delete_chars(s, (int)(begin - temp), (int)(end - begin));
}
NK_API char*
nk_str_at_char(struct nk_str *s, int pos)
{
    NK_ASSERT(s);
    if (!s || pos > (int)s->buffer.allocated) return 0;
    return nk_ptr_add(char, s->buffer.memory.ptr, pos);
}
NK_API char*
nk_str_at_rune(struct nk_str *str, int pos, nk_rune *unicode, int *len)
{
    int i = 0;
    int src_len = 0;
    int glyph_len = 0;
    char *text;
    int text_len;

    NK_ASSERT(str);
    NK_ASSERT(unicode);
    NK_ASSERT(len);

    if (!str || !unicode || !len) return 0;
    if (pos < 0) {
        *unicode = 0;
        *len = 0;
        return 0;
    }

    text = (char*)str->buffer.memory.ptr;
    text_len = (int)str->buffer.allocated;
    glyph_len = nk_utf_decode(text, unicode, text_len);
    while (glyph_len) {
        if (i == pos) {
            *len = glyph_len;
            break;
        }

        i++;
        src_len = src_len + glyph_len;
        glyph_len = nk_utf_decode(text + src_len, unicode, text_len - src_len);
    }
    if (i != pos) return 0;
    return text + src_len;
}
NK_API const char*
nk_str_at_char_const(const struct nk_str *s, int pos)
{
    NK_ASSERT(s);
    if (!s || pos > (int)s->buffer.allocated) return 0;
    return nk_ptr_add(char, s->buffer.memory.ptr, pos);
}
NK_API const char*
nk_str_at_const(const struct nk_str *str, int pos, nk_rune *unicode, int *len)
{
    int i = 0;
    int src_len = 0;
    int glyph_len = 0;
    char *text;
    int text_len;

    NK_ASSERT(str);
    NK_ASSERT(unicode);
    NK_ASSERT(len);

    if (!str || !unicode || !len) return 0;
    if (pos < 0) {
        *unicode = 0;
        *len = 0;
        return 0;
    }

    text = (char*)str->buffer.memory.ptr;
    text_len = (int)str->buffer.allocated;
    glyph_len = nk_utf_decode(text, unicode, text_len);
    while (glyph_len) {
        if (i == pos) {
            *len = glyph_len;
            break;
        }

        i++;
        src_len = src_len + glyph_len;
        glyph_len = nk_utf_decode(text + src_len, unicode, text_len - src_len);
    }
    if (i != pos) return 0;
    return text + src_len;
}
NK_API nk_rune
nk_str_rune_at(const struct nk_str *str, int pos)
{
    int len;
    nk_rune unicode = 0;
    nk_str_at_const(str, pos, &unicode, &len);
    return unicode;
}
NK_API char*
nk_str_get(struct nk_str *s)
{
    NK_ASSERT(s);
    if (!s || !s->len || !s->buffer.allocated) return 0;
    return (char*)s->buffer.memory.ptr;
}
NK_API const char*
nk_str_get_const(const struct nk_str *s)
{
    NK_ASSERT(s);
    if (!s || !s->len || !s->buffer.allocated) return 0;
    return (const char*)s->buffer.memory.ptr;
}
NK_API int
nk_str_len(struct nk_str *s)
{
    NK_ASSERT(s);
    if (!s || !s->len || !s->buffer.allocated) return 0;
    return s->len;
}
NK_API int
nk_str_len_char(struct nk_str *s)
{
    NK_ASSERT(s);
    if (!s || !s->len || !s->buffer.allocated) return 0;
    return (int)s->buffer.allocated;
}
NK_API void
nk_str_clear(struct nk_str *str)
{
    NK_ASSERT(str);
    nk_buffer_clear(&str->buffer);
    str->len = 0;
}
NK_API void
nk_str_free(struct nk_str *str)
{
    NK_ASSERT(str);
    nk_buffer_free(&str->buffer);
    str->len = 0;
}

NK_LIB void
nk_command_buffer_init(struct nk_command_buffer *cb,
    struct nk_buffer *b, enum nk_command_clipping clip)
{
    NK_ASSERT(cb);
    NK_ASSERT(b);
    if (!cb || !b) return;
    cb->base = b;
    cb->use_clipping = (int)clip;
    cb->begin = b->allocated;
    cb->end = b->allocated;
    cb->last = b->allocated;
}
NK_LIB void
nk_command_buffer_reset(struct nk_command_buffer *b)
{
    NK_ASSERT(b);
    if (!b) return;
    b->begin = 0;
    b->end = 0;
    b->last = 0;
    b->clip = nk_null_rect;
#ifdef NK_INCLUDE_COMMAND_USERDATA
    b->userdata.ptr = 0;
#endif
}
NK_LIB void*
nk_command_buffer_push(struct nk_command_buffer* b,
    enum nk_command_type t, nk_size size)
{
    NK_STORAGE const nk_size align = NK_ALIGNOF(struct nk_command);
    struct nk_command *cmd;
    nk_size alignment;
    void *unaligned;
    void *memory;

    NK_ASSERT(b);
    NK_ASSERT(b->base);
    if (!b) return 0;
    cmd = (struct nk_command*)nk_buffer_alloc(b->base,NK_BUFFER_FRONT,size,align);
    if (!cmd) return 0;

    b->last = (nk_size)((nk_byte*)cmd - (nk_byte*)b->base->memory.ptr);
    unaligned = (nk_byte*)cmd + size;
    memory = NK_ALIGN_PTR(unaligned, align);
    alignment = (nk_size)((nk_byte*)memory - (nk_byte*)unaligned);
#ifdef NK_ZERO_COMMAND_MEMORY
    NK_MEMSET(cmd, 0, size + alignment);
#endif

    cmd->type = t;
    cmd->next = b->base->allocated + alignment;
#ifdef NK_INCLUDE_COMMAND_USERDATA
    cmd->userdata = b->userdata;
#endif
    b->end = cmd->next;
    return cmd;
}
NK_API void
nk_push_scissor(struct nk_command_buffer *b, struct nk_rect r)
{
    struct nk_command_scissor *cmd;
    NK_ASSERT(b);
    if (!b) return;

    b->clip.x = r.x;
    b->clip.y = r.y;
    b->clip.w = r.w;
    b->clip.h = r.h;
    cmd = (struct nk_command_scissor*)
        nk_command_buffer_push(b, NK_COMMAND_SCISSOR, sizeof(*cmd));

    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(0, r.w);
    cmd->h = (unsigned short)NK_MAX(0, r.h);
}
NK_API void
nk_stroke_line(struct nk_command_buffer *b, float x0, float y0,
    float x1, float y1, float line_thickness, struct nk_color c)
{
    struct nk_command_line *cmd;
    NK_ASSERT(b);
    if (!b || line_thickness <= 0) return;
    cmd = (struct nk_command_line*)
        nk_command_buffer_push(b, NK_COMMAND_LINE, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->begin.x = (short)x0;
    cmd->begin.y = (short)y0;
    cmd->end.x = (short)x1;
    cmd->end.y = (short)y1;
    cmd->color = c;
}
NK_API void
nk_stroke_curve(struct nk_command_buffer *b, float ax, float ay,
    float ctrl0x, float ctrl0y, float ctrl1x, float ctrl1y,
    float bx, float by, float line_thickness, struct nk_color col)
{
    struct nk_command_curve *cmd;
    NK_ASSERT(b);
    if (!b || col.a == 0 || line_thickness <= 0) return;

    cmd = (struct nk_command_curve*)
        nk_command_buffer_push(b, NK_COMMAND_CURVE, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->begin.x = (short)ax;
    cmd->begin.y = (short)ay;
    cmd->ctrl[0].x = (short)ctrl0x;
    cmd->ctrl[0].y = (short)ctrl0y;
    cmd->ctrl[1].x = (short)ctrl1x;
    cmd->ctrl[1].y = (short)ctrl1y;
    cmd->end.x = (short)bx;
    cmd->end.y = (short)by;
    cmd->color = col;
}
NK_API void
nk_stroke_rect(struct nk_command_buffer *b, struct nk_rect rect,
    float rounding, float line_thickness, struct nk_color c)
{
    struct nk_command_rect *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0 || rect.w == 0 || rect.h == 0 || line_thickness <= 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(rect.x, rect.y, rect.w, rect.h,
            clip->x, clip->y, clip->w, clip->h)) return;
    }
    cmd = (struct nk_command_rect*)
        nk_command_buffer_push(b, NK_COMMAND_RECT, sizeof(*cmd));
    if (!cmd) return;
    cmd->rounding = (unsigned short)rounding;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->x = (short)rect.x;
    cmd->y = (short)rect.y;
    cmd->w = (unsigned short)NK_MAX(0, rect.w);
    cmd->h = (unsigned short)NK_MAX(0, rect.h);
    cmd->color = c;
}
NK_API void
nk_fill_rect(struct nk_command_buffer *b, struct nk_rect rect,
    float rounding, struct nk_color c)
{
    struct nk_command_rect_filled *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0 || rect.w == 0 || rect.h == 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(rect.x, rect.y, rect.w, rect.h,
            clip->x, clip->y, clip->w, clip->h)) return;
    }

    cmd = (struct nk_command_rect_filled*)
        nk_command_buffer_push(b, NK_COMMAND_RECT_FILLED, sizeof(*cmd));
    if (!cmd) return;
    cmd->rounding = (unsigned short)rounding;
    cmd->x = (short)rect.x;
    cmd->y = (short)rect.y;
    cmd->w = (unsigned short)NK_MAX(0, rect.w);
    cmd->h = (unsigned short)NK_MAX(0, rect.h);
    cmd->color = c;
}
NK_API void
nk_fill_rect_multi_color(struct nk_command_buffer *b, struct nk_rect rect,
    struct nk_color left, struct nk_color top, struct nk_color right,
    struct nk_color bottom)
{
    struct nk_command_rect_multi_color *cmd;
    NK_ASSERT(b);
    if (!b || rect.w == 0 || rect.h == 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(rect.x, rect.y, rect.w, rect.h,
            clip->x, clip->y, clip->w, clip->h)) return;
    }

    cmd = (struct nk_command_rect_multi_color*)
        nk_command_buffer_push(b, NK_COMMAND_RECT_MULTI_COLOR, sizeof(*cmd));
    if (!cmd) return;
    cmd->x = (short)rect.x;
    cmd->y = (short)rect.y;
    cmd->w = (unsigned short)NK_MAX(0, rect.w);
    cmd->h = (unsigned short)NK_MAX(0, rect.h);
    cmd->left = left;
    cmd->top = top;
    cmd->right = right;
    cmd->bottom = bottom;
}
NK_API void
nk_stroke_circle(struct nk_command_buffer *b, struct nk_rect r,
    float line_thickness, struct nk_color c)
{
    struct nk_command_circle *cmd;
    if (!b || r.w == 0 || r.h == 0 || line_thickness <= 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(r.x, r.y, r.w, r.h, clip->x, clip->y, clip->w, clip->h))
            return;
    }

    cmd = (struct nk_command_circle*)
        nk_command_buffer_push(b, NK_COMMAND_CIRCLE, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(r.w, 0);
    cmd->h = (unsigned short)NK_MAX(r.h, 0);
    cmd->color = c;
}
NK_API void
nk_fill_circle(struct nk_command_buffer *b, struct nk_rect r, struct nk_color c)
{
    struct nk_command_circle_filled *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0 || r.w == 0 || r.h == 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(r.x, r.y, r.w, r.h, clip->x, clip->y, clip->w, clip->h))
            return;
    }

    cmd = (struct nk_command_circle_filled*)
        nk_command_buffer_push(b, NK_COMMAND_CIRCLE_FILLED, sizeof(*cmd));
    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(r.w, 0);
    cmd->h = (unsigned short)NK_MAX(r.h, 0);
    cmd->color = c;
}
NK_API void
nk_stroke_arc(struct nk_command_buffer *b, float cx, float cy, float radius,
    float a_min, float a_max, float line_thickness, struct nk_color c)
{
    struct nk_command_arc *cmd;
    if (!b || c.a == 0 || line_thickness <= 0) return;
    cmd = (struct nk_command_arc*)
        nk_command_buffer_push(b, NK_COMMAND_ARC, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->cx = (short)cx;
    cmd->cy = (short)cy;
    cmd->r = (unsigned short)radius;
    cmd->a[0] = a_min;
    cmd->a[1] = a_max;
    cmd->color = c;
}
NK_API void
nk_fill_arc(struct nk_command_buffer *b, float cx, float cy, float radius,
    float a_min, float a_max, struct nk_color c)
{
    struct nk_command_arc_filled *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0) return;
    cmd = (struct nk_command_arc_filled*)
        nk_command_buffer_push(b, NK_COMMAND_ARC_FILLED, sizeof(*cmd));
    if (!cmd) return;
    cmd->cx = (short)cx;
    cmd->cy = (short)cy;
    cmd->r = (unsigned short)radius;
    cmd->a[0] = a_min;
    cmd->a[1] = a_max;
    cmd->color = c;
}
NK_API void
nk_stroke_triangle(struct nk_command_buffer *b, float x0, float y0, float x1,
    float y1, float x2, float y2, float line_thickness, struct nk_color c)
{
    struct nk_command_triangle *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0 || line_thickness <= 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INBOX(x0, y0, clip->x, clip->y, clip->w, clip->h) &&
            !NK_INBOX(x1, y1, clip->x, clip->y, clip->w, clip->h) &&
            !NK_INBOX(x2, y2, clip->x, clip->y, clip->w, clip->h))
            return;
    }

    cmd = (struct nk_command_triangle*)
        nk_command_buffer_push(b, NK_COMMAND_TRIANGLE, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->a.x = (short)x0;
    cmd->a.y = (short)y0;
    cmd->b.x = (short)x1;
    cmd->b.y = (short)y1;
    cmd->c.x = (short)x2;
    cmd->c.y = (short)y2;
    cmd->color = c;
}
NK_API void
nk_fill_triangle(struct nk_command_buffer *b, float x0, float y0, float x1,
    float y1, float x2, float y2, struct nk_color c)
{
    struct nk_command_triangle_filled *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0) return;
    if (!b) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INBOX(x0, y0, clip->x, clip->y, clip->w, clip->h) &&
            !NK_INBOX(x1, y1, clip->x, clip->y, clip->w, clip->h) &&
            !NK_INBOX(x2, y2, clip->x, clip->y, clip->w, clip->h))
            return;
    }

    cmd = (struct nk_command_triangle_filled*)
        nk_command_buffer_push(b, NK_COMMAND_TRIANGLE_FILLED, sizeof(*cmd));
    if (!cmd) return;
    cmd->a.x = (short)x0;
    cmd->a.y = (short)y0;
    cmd->b.x = (short)x1;
    cmd->b.y = (short)y1;
    cmd->c.x = (short)x2;
    cmd->c.y = (short)y2;
    cmd->color = c;
}
NK_API void
nk_stroke_polygon(struct nk_command_buffer *b,  float *points, int point_count,
    float line_thickness, struct nk_color col)
{
    int i;
    nk_size size = 0;
    struct nk_command_polygon *cmd;

    NK_ASSERT(b);
    if (!b || col.a == 0 || line_thickness <= 0) return;
    size = sizeof(*cmd) + sizeof(short) * 2 * (nk_size)point_count;
    cmd = (struct nk_command_polygon*) nk_command_buffer_push(b, NK_COMMAND_POLYGON, size);
    if (!cmd) return;
    cmd->color = col;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->point_count = (unsigned short)point_count;
    for (i = 0; i < point_count; ++i) {
        cmd->points[i].x = (short)points[i*2];
        cmd->points[i].y = (short)points[i*2+1];
    }
}
NK_API void
nk_fill_polygon(struct nk_command_buffer *b, float *points, int point_count,
    struct nk_color col)
{
    int i;
    nk_size size = 0;
    struct nk_command_polygon_filled *cmd;

    NK_ASSERT(b);
    if (!b || col.a == 0) return;
    size = sizeof(*cmd) + sizeof(short) * 2 * (nk_size)point_count;
    cmd = (struct nk_command_polygon_filled*)
        nk_command_buffer_push(b, NK_COMMAND_POLYGON_FILLED, size);
    if (!cmd) return;
    cmd->color = col;
    cmd->point_count = (unsigned short)point_count;
    for (i = 0; i < point_count; ++i) {
        cmd->points[i].x = (short)points[i*2+0];
        cmd->points[i].y = (short)points[i*2+1];
    }
}
NK_API void
nk_stroke_polyline(struct nk_command_buffer *b, float *points, int point_count,
    float line_thickness, struct nk_color col)
{
    int i;
    nk_size size = 0;
    struct nk_command_polyline *cmd;

    NK_ASSERT(b);
    if (!b || col.a == 0 || line_thickness <= 0) return;
    size = sizeof(*cmd) + sizeof(short) * 2 * (nk_size)point_count;
    cmd = (struct nk_command_polyline*) nk_command_buffer_push(b, NK_COMMAND_POLYLINE, size);
    if (!cmd) return;
    cmd->color = col;
    cmd->point_count = (unsigned short)point_count;
    cmd->line_thickness = (unsigned short)line_thickness;
    for (i = 0; i < point_count; ++i) {
        cmd->points[i].x = (short)points[i*2];
        cmd->points[i].y = (short)points[i*2+1];
    }
}
NK_API void
nk_draw_image(struct nk_command_buffer *b, struct nk_rect r,
    const struct nk_image *img, struct nk_color col)
{
    struct nk_command_image *cmd;
    NK_ASSERT(b);
    if (!b) return;
    if (b->use_clipping) {
        const struct nk_rect *c = &b->clip;
        if (c->w == 0 || c->h == 0 || !NK_INTERSECT(r.x, r.y, r.w, r.h, c->x, c->y, c->w, c->h))
            return;
    }

    cmd = (struct nk_command_image*)
        nk_command_buffer_push(b, NK_COMMAND_IMAGE, sizeof(*cmd));
    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(0, r.w);
    cmd->h = (unsigned short)NK_MAX(0, r.h);
    cmd->img = *img;
    cmd->col = col;
}
NK_API void
nk_draw_nine_slice(struct nk_command_buffer *b, struct nk_rect r,
    const struct nk_nine_slice *slc, struct nk_color col)
{
    struct nk_image img;
    const struct nk_image *slcimg = (const struct nk_image*)slc;
    nk_ushort rgnX, rgnY, rgnW, rgnH;
    rgnX = slcimg->region[0];
    rgnY = slcimg->region[1];
    rgnW = slcimg->region[2];
    rgnH = slcimg->region[3];

    img.handle = slcimg->handle;
    img.w = slcimg->w;
    img.h = slcimg->h;
    img.region[0] = rgnX;
    img.region[1] = rgnY;
    img.region[2] = slc->l;
    img.region[3] = slc->t;

    nk_draw_image(b,
        nk_rect(r.x, r.y, (float)slc->l, (float)slc->t),
        &img, col);

#define IMG_RGN(x, y, w, h) img.region[0] = (nk_ushort)(x); img.region[1] = (nk_ushort)(y); img.region[2] = (nk_ushort)(w); img.region[3] = (nk_ushort)(h);

    IMG_RGN(rgnX + slc->l, rgnY, rgnW - slc->l - slc->r, slc->t);
    nk_draw_image(b,
        nk_rect(r.x + (float)slc->l, r.y, (float)(r.w - slc->l - slc->r), (float)slc->t),
        &img, col);

    IMG_RGN(rgnX + rgnW - slc->r, rgnY, slc->r, slc->t);
    nk_draw_image(b,
        nk_rect(r.x + r.w - (float)slc->r, r.y, (float)slc->r, (float)slc->t),
        &img, col);

    IMG_RGN(rgnX, rgnY + slc->t, slc->l, rgnH - slc->t - slc->b);
    nk_draw_image(b,
        nk_rect(r.x, r.y + (float)slc->t, (float)slc->l, (float)(r.h - slc->t - slc->b)),
        &img, col);

    IMG_RGN(rgnX + slc->l, rgnY + slc->t, rgnW - slc->l - slc->r, rgnH - slc->t - slc->b);
    nk_draw_image(b,
        nk_rect(r.x + (float)slc->l, r.y + (float)slc->t, (float)(r.w - slc->l - slc->r), (float)(r.h - slc->t - slc->b)),
        &img, col);

    IMG_RGN(rgnX + rgnW - slc->r, rgnY + slc->t, slc->r, rgnH - slc->t - slc->b);
    nk_draw_image(b,
        nk_rect(r.x + r.w - (float)slc->r, r.y + (float)slc->t, (float)slc->r, (float)(r.h - slc->t - slc->b)),
        &img, col);

    IMG_RGN(rgnX, rgnY + rgnH - slc->b, slc->l, slc->b);
    nk_draw_image(b,
        nk_rect(r.x, r.y + r.h - (float)slc->b, (float)slc->l, (float)slc->b),
        &img, col);

    IMG_RGN(rgnX + slc->l, rgnY + rgnH - slc->b, rgnW - slc->l - slc->r, slc->b);
    nk_draw_image(b,
        nk_rect(r.x + (float)slc->l, r.y + r.h - (float)slc->b, (float)(r.w - slc->l - slc->r), (float)slc->b),
        &img, col);

    IMG_RGN(rgnX + rgnW - slc->r, rgnY + rgnH - slc->b, slc->r, slc->b);
    nk_draw_image(b,
        nk_rect(r.x + r.w - (float)slc->r, r.y + r.h - (float)slc->b, (float)slc->r, (float)slc->b),
        &img, col);

#undef IMG_RGN
}
NK_API void
nk_push_custom(struct nk_command_buffer *b, struct nk_rect r,
    nk_command_custom_callback cb, nk_handle usr)
{
    struct nk_command_custom *cmd;
    NK_ASSERT(b);
    if (!b) return;
    if (b->use_clipping) {
        const struct nk_rect *c = &b->clip;
        if (c->w == 0 || c->h == 0 || !NK_INTERSECT(r.x, r.y, r.w, r.h, c->x, c->y, c->w, c->h))
            return;
    }

    cmd = (struct nk_command_custom*)
        nk_command_buffer_push(b, NK_COMMAND_CUSTOM, sizeof(*cmd));
    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(0, r.w);
    cmd->h = (unsigned short)NK_MAX(0, r.h);
    cmd->callback_data = usr;
    cmd->callback = cb;
}
NK_API void
nk_draw_text(struct nk_command_buffer *b, struct nk_rect r,
    const char *string, int length, const struct nk_user_font *font,
    struct nk_color bg, struct nk_color fg)
{
    float text_width = 0;
    struct nk_command_text *cmd;

    NK_ASSERT(b);
    NK_ASSERT(font);
    if (!b || !string || !length || (bg.a == 0 && fg.a == 0)) return;
    if (b->use_clipping) {
        const struct nk_rect *c = &b->clip;
        if (c->w == 0 || c->h == 0 || !NK_INTERSECT(r.x, r.y, r.w, r.h, c->x, c->y, c->w, c->h))
            return;
    }

    text_width = font->width(font->userdata, font->height, string, length);
    if (text_width > r.w){
        int glyphs = 0;
        float txt_width = (float)text_width;
        length = nk_text_clamp(font, string, length, r.w, &glyphs, &txt_width, 0,0);
    }

    if (!length) return;
    cmd = (struct nk_command_text*)
        nk_command_buffer_push(b, NK_COMMAND_TEXT, sizeof(*cmd) + (nk_size)(length + 1));
    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)r.w;
    cmd->h = (unsigned short)r.h;
    cmd->background = bg;
    cmd->foreground = fg;
    cmd->font = font;
    cmd->length = length;
    cmd->height = font->height;
    NK_MEMCPY(cmd->string, string, (nk_size)length);
    cmd->string[length] = '\0';
}

#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
NK_API void
nk_draw_list_init(struct nk_draw_list *list)
{
    nk_size i = 0;
    NK_ASSERT(list);
    if (!list) return;
    nk_zero(list, sizeof(*list));
    for (i = 0; i < NK_LEN(list->circle_vtx); ++i) {
        const float a = ((float)i / (float)NK_LEN(list->circle_vtx)) * 2 * NK_PI;
        list->circle_vtx[i].x = (float)NK_COS(a);
        list->circle_vtx[i].y = (float)NK_SIN(a);
    }
}
NK_API void
nk_draw_list_setup(struct nk_draw_list *canvas, const struct nk_convert_config *config,
    struct nk_buffer *cmds, struct nk_buffer *vertices, struct nk_buffer *elements,
    enum nk_anti_aliasing line_aa, enum nk_anti_aliasing shape_aa)
{
    NK_ASSERT(canvas);
    NK_ASSERT(config);
    NK_ASSERT(cmds);
    NK_ASSERT(vertices);
    NK_ASSERT(elements);
    if (!canvas || !config || !cmds || !vertices || !elements)
        return;

    canvas->buffer = cmds;
    canvas->config = *config;
    canvas->elements = elements;
    canvas->vertices = vertices;
    canvas->line_AA = line_aa;
    canvas->shape_AA = shape_aa;
    canvas->clip_rect = nk_null_rect;

    canvas->cmd_offset = 0;
    canvas->element_count = 0;
    canvas->vertex_count = 0;
    canvas->cmd_offset = 0;
    canvas->cmd_count = 0;
    canvas->path_count = 0;
}
NK_API const struct nk_draw_command*
nk__draw_list_begin(const struct nk_draw_list *canvas, const struct nk_buffer *buffer)
{
    nk_byte *memory;
    nk_size offset;
    const struct nk_draw_command *cmd;

    NK_ASSERT(buffer);
    if (!buffer || !buffer->size || !canvas->cmd_count)
        return 0;

    memory = (nk_byte*)buffer->memory.ptr;
    offset = buffer->memory.size - canvas->cmd_offset;
    cmd = nk_ptr_add(const struct nk_draw_command, memory, offset);
    return cmd;
}
NK_API const struct nk_draw_command*
nk__draw_list_end(const struct nk_draw_list *canvas, const struct nk_buffer *buffer)
{
    nk_size size;
    nk_size offset;
    nk_byte *memory;
    const struct nk_draw_command *end;

    NK_ASSERT(buffer);
    NK_ASSERT(canvas);
    if (!buffer || !canvas)
        return 0;

    memory = (nk_byte*)buffer->memory.ptr;
    size = buffer->memory.size;
    offset = size - canvas->cmd_offset;
    end = nk_ptr_add(const struct nk_draw_command, memory, offset);
    end -= (canvas->cmd_count-1);
    return end;
}
NK_API const struct nk_draw_command*
nk__draw_list_next(const struct nk_draw_command *cmd,
    const struct nk_buffer *buffer, const struct nk_draw_list *canvas)
{
    const struct nk_draw_command *end;
    NK_ASSERT(buffer);
    NK_ASSERT(canvas);
    if (!cmd || !buffer || !canvas)
        return 0;

    end = nk__draw_list_end(canvas, buffer);
    if (cmd <= end) return 0;
    return (cmd-1);
}
NK_INTERN struct nk_vec2*
nk_draw_list_alloc_path(struct nk_draw_list *list, int count)
{
    struct nk_vec2 *points;
    NK_STORAGE const nk_size point_align = NK_ALIGNOF(struct nk_vec2);
    NK_STORAGE const nk_size point_size = sizeof(struct nk_vec2);
    points = (struct nk_vec2*)
        nk_buffer_alloc(list->buffer, NK_BUFFER_FRONT,
                        point_size * (nk_size)count, point_align);

    if (!points) return 0;
    if (!list->path_offset) {
        void *memory = nk_buffer_memory(list->buffer);
        list->path_offset = (unsigned int)((nk_byte*)points - (nk_byte*)memory);
    }
    list->path_count += (unsigned int)count;
    return points;
}
NK_INTERN struct nk_vec2
nk_draw_list_path_last(struct nk_draw_list *list)
{
    void *memory;
    struct nk_vec2 *point;
    NK_ASSERT(list->path_count);
    memory = nk_buffer_memory(list->buffer);
    point = nk_ptr_add(struct nk_vec2, memory, list->path_offset);
    point += (list->path_count-1);
    return *point;
}
NK_INTERN struct nk_draw_command*
nk_draw_list_push_command(struct nk_draw_list *list, struct nk_rect clip,
    nk_handle texture)
{
    NK_STORAGE const nk_size cmd_align = NK_ALIGNOF(struct nk_draw_command);
    NK_STORAGE const nk_size cmd_size = sizeof(struct nk_draw_command);
    struct nk_draw_command *cmd;

    NK_ASSERT(list);
    cmd = (struct nk_draw_command*)
        nk_buffer_alloc(list->buffer, NK_BUFFER_BACK, cmd_size, cmd_align);

    if (!cmd) return 0;
    if (!list->cmd_count) {
        nk_byte *memory = (nk_byte*)nk_buffer_memory(list->buffer);
        nk_size total = nk_buffer_total(list->buffer);
        memory = nk_ptr_add(nk_byte, memory, total);
        list->cmd_offset = (nk_size)(memory - (nk_byte*)cmd);
    }

    cmd->elem_count = 0;
    cmd->clip_rect = clip;
    cmd->texture = texture;
#ifdef NK_INCLUDE_COMMAND_USERDATA
    cmd->userdata = list->userdata;
#endif

    list->cmd_count++;
    list->clip_rect = clip;
    return cmd;
}
NK_INTERN struct nk_draw_command*
nk_draw_list_command_last(struct nk_draw_list *list)
{
    void *memory;
    nk_size size;
    struct nk_draw_command *cmd;
    NK_ASSERT(list->cmd_count);

    memory = nk_buffer_memory(list->buffer);
    size = nk_buffer_total(list->buffer);
    cmd = nk_ptr_add(struct nk_draw_command, memory, size - list->cmd_offset);
    return (cmd - (list->cmd_count-1));
}
NK_INTERN void
nk_draw_list_add_clip(struct nk_draw_list *list, struct nk_rect rect)
{
    NK_ASSERT(list);
    if (!list) return;
    if (!list->cmd_count) {
        nk_draw_list_push_command(list, rect, list->config.tex_null.texture);
    } else {
        struct nk_draw_command *prev = nk_draw_list_command_last(list);
        if (prev->elem_count == 0)
            prev->clip_rect = rect;
        nk_draw_list_push_command(list, rect, prev->texture);
    }
}
NK_INTERN void
nk_draw_list_push_image(struct nk_draw_list *list, nk_handle texture)
{
    NK_ASSERT(list);
    if (!list) return;
    if (!list->cmd_count) {
        nk_draw_list_push_command(list, nk_null_rect, texture);
    } else {
        struct nk_draw_command *prev = nk_draw_list_command_last(list);
        if (prev->elem_count == 0) {
            prev->texture = texture;
        #ifdef NK_INCLUDE_COMMAND_USERDATA
            prev->userdata = list->userdata;
        #endif
    } else if (prev->texture.id != texture.id
        #ifdef NK_INCLUDE_COMMAND_USERDATA
            || prev->userdata.id != list->userdata.id
        #endif
        ) nk_draw_list_push_command(list, prev->clip_rect, texture);
    }
}
#ifdef NK_INCLUDE_COMMAND_USERDATA
NK_API void
nk_draw_list_push_userdata(struct nk_draw_list *list, nk_handle userdata)
{
    list->userdata = userdata;
}
#endif
NK_INTERN void*
nk_draw_list_alloc_vertices(struct nk_draw_list *list, nk_size count)
{
    void *vtx;
    NK_ASSERT(list);
    if (!list) return 0;
    vtx = nk_buffer_alloc(list->vertices, NK_BUFFER_FRONT,
        list->config.vertex_size*count, list->config.vertex_alignment);
    if (!vtx) return 0;
    list->vertex_count += (unsigned int)count;

    if(sizeof(nk_draw_index)==2) NK_ASSERT((list->vertex_count < NK_USHORT_MAX &&
        "To many vertices for 16-bit vertex indices. Please read comment above on how to solve this problem"));
    return vtx;
}
NK_INTERN nk_draw_index*
nk_draw_list_alloc_elements(struct nk_draw_list *list, nk_size count)
{
    nk_draw_index *ids;
    struct nk_draw_command *cmd;
    NK_STORAGE const nk_size elem_align = NK_ALIGNOF(nk_draw_index);
    NK_STORAGE const nk_size elem_size = sizeof(nk_draw_index);
    NK_ASSERT(list);
    if (!list) return 0;

    ids = (nk_draw_index*)
        nk_buffer_alloc(list->elements, NK_BUFFER_FRONT, elem_size*count, elem_align);
    if (!ids) return 0;
    cmd = nk_draw_list_command_last(list);
    list->element_count += (unsigned int)count;
    cmd->elem_count += (unsigned int)count;
    return ids;
}
NK_INTERN int
nk_draw_vertex_layout_element_is_end_of_layout(
    const struct nk_draw_vertex_layout_element *element)
{
    return (element->attribute == NK_VERTEX_ATTRIBUTE_COUNT ||
            element->format == NK_FORMAT_COUNT);
}
NK_INTERN void
nk_draw_vertex_color(void *attr, const float *vals,
    enum nk_draw_vertex_layout_format format)
{

    float val[4];
    NK_ASSERT(format >= NK_FORMAT_COLOR_BEGIN);
    NK_ASSERT(format <= NK_FORMAT_COLOR_END);
    if (format < NK_FORMAT_COLOR_BEGIN || format > NK_FORMAT_COLOR_END) return;

    val[0] = NK_SATURATE(vals[0]);
    val[1] = NK_SATURATE(vals[1]);
    val[2] = NK_SATURATE(vals[2]);
    val[3] = NK_SATURATE(vals[3]);

    switch (format) {
    default: NK_ASSERT(0 && "Invalid vertex layout color format"); break;
    case NK_FORMAT_R8G8B8A8:
    case NK_FORMAT_R8G8B8: {
        struct nk_color col = nk_rgba_fv(val);
        NK_MEMCPY(attr, &col.r, sizeof(col));
    } break;
    case NK_FORMAT_B8G8R8A8: {
        struct nk_color col = nk_rgba_fv(val);
        struct nk_color bgra = nk_rgba(col.b, col.g, col.r, col.a);
        NK_MEMCPY(attr, &bgra, sizeof(bgra));
    } break;
    case NK_FORMAT_R16G15B16: {
        nk_ushort col[3];
        col[0] = (nk_ushort)(val[0]*(float)NK_USHORT_MAX);
        col[1] = (nk_ushort)(val[1]*(float)NK_USHORT_MAX);
        col[2] = (nk_ushort)(val[2]*(float)NK_USHORT_MAX);
        NK_MEMCPY(attr, col, sizeof(col));
    } break;
    case NK_FORMAT_R16G15B16A16: {
        nk_ushort col[4];
        col[0] = (nk_ushort)(val[0]*(float)NK_USHORT_MAX);
        col[1] = (nk_ushort)(val[1]*(float)NK_USHORT_MAX);
        col[2] = (nk_ushort)(val[2]*(float)NK_USHORT_MAX);
        col[3] = (nk_ushort)(val[3]*(float)NK_USHORT_MAX);
        NK_MEMCPY(attr, col, sizeof(col));
    } break;
    case NK_FORMAT_R32G32B32: {
        nk_uint col[3];
        col[0] = (nk_uint)(val[0]*(float)NK_UINT_MAX);
        col[1] = (nk_uint)(val[1]*(float)NK_UINT_MAX);
        col[2] = (nk_uint)(val[2]*(float)NK_UINT_MAX);
        NK_MEMCPY(attr, col, sizeof(col));
    } break;
    case NK_FORMAT_R32G32B32A32: {
        nk_uint col[4];
        col[0] = (nk_uint)(val[0]*(float)NK_UINT_MAX);
        col[1] = (nk_uint)(val[1]*(float)NK_UINT_MAX);
        col[2] = (nk_uint)(val[2]*(float)NK_UINT_MAX);
        col[3] = (nk_uint)(val[3]*(float)NK_UINT_MAX);
        NK_MEMCPY(attr, col, sizeof(col));
    } break;
    case NK_FORMAT_R32G32B32A32_FLOAT:
        NK_MEMCPY(attr, val, sizeof(float)*4);
        break;
    case NK_FORMAT_R32G32B32A32_DOUBLE: {
        double col[4];
        col[0] = (double)val[0];
        col[1] = (double)val[1];
        col[2] = (double)val[2];
        col[3] = (double)val[3];
        NK_MEMCPY(attr, col, sizeof(col));
    } break;
    case NK_FORMAT_RGB32:
    case NK_FORMAT_RGBA32: {
        struct nk_color col = nk_rgba_fv(val);
        nk_uint color = nk_color_u32(col);
        NK_MEMCPY(attr, &color, sizeof(color));
    } break; }
}
NK_INTERN void
nk_draw_vertex_element(void *dst, const float *values, int value_count,
    enum nk_draw_vertex_layout_format format)
{
    int value_index;
    void *attribute = dst;

    NK_ASSERT(format < NK_FORMAT_COLOR_BEGIN);
    if (format >= NK_FORMAT_COLOR_BEGIN && format <= NK_FORMAT_COLOR_END) return;
    for (value_index = 0; value_index < value_count; ++value_index) {
        switch (format) {
        default: NK_ASSERT(0 && "invalid vertex layout format"); break;
        case NK_FORMAT_SCHAR: {
            char value = (char)NK_CLAMP((float)NK_SCHAR_MIN, values[value_index], (float)NK_SCHAR_MAX);
            NK_MEMCPY(attribute, &value, sizeof(value));
            attribute = (void*)((char*)attribute + sizeof(char));
        } break;
        case NK_FORMAT_SSHORT: {
            nk_short value = (nk_short)NK_CLAMP((float)NK_SSHORT_MIN, values[value_index], (float)NK_SSHORT_MAX);
            NK_MEMCPY(attribute, &value, sizeof(value));
            attribute = (void*)((char*)attribute + sizeof(value));
        } break;
        case NK_FORMAT_SINT: {
            nk_int value = (nk_int)NK_CLAMP((float)NK_SINT_MIN, values[value_index], (float)NK_SINT_MAX);
            NK_MEMCPY(attribute, &value, sizeof(value));
            attribute = (void*)((char*)attribute + sizeof(nk_int));
        } break;
        case NK_FORMAT_UCHAR: {
            unsigned char value = (unsigned char)NK_CLAMP((float)NK_UCHAR_MIN, values[value_index], (float)NK_UCHAR_MAX);
            NK_MEMCPY(attribute, &value, sizeof(value));
            attribute = (void*)((char*)attribute + sizeof(unsigned char));
        } break;
        case NK_FORMAT_USHORT: {
            nk_ushort value = (nk_ushort)NK_CLAMP((float)NK_USHORT_MIN, values[value_index], (float)NK_USHORT_MAX);
            NK_MEMCPY(attribute, &value, sizeof(value));
            attribute = (void*)((char*)attribute + sizeof(value));
            } break;
        case NK_FORMAT_UINT: {
            nk_uint value = (nk_uint)NK_CLAMP((float)NK_UINT_MIN, values[value_index], (float)NK_UINT_MAX);
            NK_MEMCPY(attribute, &value, sizeof(value));
            attribute = (void*)((char*)attribute + sizeof(nk_uint));
        } break;
        case NK_FORMAT_FLOAT:
            NK_MEMCPY(attribute, &values[value_index], sizeof(values[value_index]));
            attribute = (void*)((char*)attribute + sizeof(float));
            break;
        case NK_FORMAT_DOUBLE: {
            double value = (double)values[value_index];
            NK_MEMCPY(attribute, &value, sizeof(value));
            attribute = (void*)((char*)attribute + sizeof(double));
            } break;
        }
    }
}
NK_INTERN void*
nk_draw_vertex(void *dst, const struct nk_convert_config *config,
    struct nk_vec2 pos, struct nk_vec2 uv, struct nk_colorf color)
{
    void *result = (void*)((char*)dst + config->vertex_size);
    const struct nk_draw_vertex_layout_element *elem_iter = config->vertex_layout;
    while (!nk_draw_vertex_layout_element_is_end_of_layout(elem_iter)) {
        void *address = (void*)((char*)dst + elem_iter->offset);
        switch (elem_iter->attribute) {
        case NK_VERTEX_ATTRIBUTE_COUNT:
        default: NK_ASSERT(0 && "wrong element attribute"); break;
        case NK_VERTEX_POSITION: nk_draw_vertex_element(address, &pos.x, 2, elem_iter->format); break;
        case NK_VERTEX_TEXCOORD: nk_draw_vertex_element(address, &uv.x, 2, elem_iter->format); break;
        case NK_VERTEX_COLOR: nk_draw_vertex_color(address, &color.r, elem_iter->format); break;
        }
        elem_iter++;
    }
    return result;
}
NK_API void
nk_draw_list_stroke_poly_line(struct nk_draw_list *list, const struct nk_vec2 *points,
    const unsigned int points_count, struct nk_color color, enum nk_draw_list_stroke closed,
    float thickness, enum nk_anti_aliasing aliasing)
{
    nk_size count;
    int thick_line;
    struct nk_colorf col;
    struct nk_colorf col_trans;
    NK_ASSERT(list);
    if (!list || points_count < 2) return;

    color.a = (nk_byte)((float)color.a * list->config.global_alpha);
    count = points_count;
    if (!closed) count = points_count-1;
    thick_line = thickness > 1.0f;

#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_draw_list_push_userdata(list, list->userdata);
#endif

    color.a = (nk_byte)((float)color.a * list->config.global_alpha);
    nk_color_fv(&col.r, color);
    col_trans = col;
    col_trans.a = 0;

    if (aliasing == NK_ANTI_ALIASING_ON) {

        const float AA_SIZE = 1.0f;
        NK_STORAGE const nk_size pnt_align = NK_ALIGNOF(struct nk_vec2);
        NK_STORAGE const nk_size pnt_size = sizeof(struct nk_vec2);

        nk_size i1 = 0;
        nk_size vertex_offset;
        nk_size index = list->vertex_count;

        const nk_size idx_count = (thick_line) ?  (count * 18) : (count * 12);
        const nk_size vtx_count = (thick_line) ? (points_count * 4): (points_count *3);

        void *vtx = nk_draw_list_alloc_vertices(list, vtx_count);
        nk_draw_index *ids = nk_draw_list_alloc_elements(list, idx_count);

        nk_size size;
        struct nk_vec2 *normals, *temp;
        if (!vtx || !ids) return;

        vertex_offset = (nk_size)((nk_byte*)vtx - (nk_byte*)list->vertices->memory.ptr);
        nk_buffer_mark(list->vertices, NK_BUFFER_FRONT);
        size = pnt_size * ((thick_line) ? 5 : 3) * points_count;
        normals = (struct nk_vec2*) nk_buffer_alloc(list->vertices, NK_BUFFER_FRONT, size, pnt_align);
        if (!normals) return;
        temp = normals + points_count;

        vtx = (void*)((nk_byte*)list->vertices->memory.ptr + vertex_offset);

        for (i1 = 0; i1 < count; ++i1) {
            const nk_size i2 = ((i1 + 1) == points_count) ? 0 : (i1 + 1);
            struct nk_vec2 diff = nk_vec2_sub(points[i2], points[i1]);
            float len;

            len = nk_vec2_len_sqr(diff);
            if (len != 0.0f)
                len = NK_INV_SQRT(len);
            else len = 1.0f;

            diff = nk_vec2_muls(diff, len);
            normals[i1].x = diff.y;
            normals[i1].y = -diff.x;
        }

        if (!closed)
            normals[points_count-1] = normals[points_count-2];

        if (!thick_line) {
            nk_size idx1, i;
            if (!closed) {
                struct nk_vec2 d;
                temp[0] = nk_vec2_add(points[0], nk_vec2_muls(normals[0], AA_SIZE));
                temp[1] = nk_vec2_sub(points[0], nk_vec2_muls(normals[0], AA_SIZE));
                d = nk_vec2_muls(normals[points_count-1], AA_SIZE);
                temp[(points_count-1) * 2 + 0] = nk_vec2_add(points[points_count-1], d);
                temp[(points_count-1) * 2 + 1] = nk_vec2_sub(points[points_count-1], d);
            }

            idx1 = index;
            for (i1 = 0; i1 < count; i1++) {
                struct nk_vec2 dm;
                float dmr2;
                nk_size i2 = ((i1 + 1) == points_count) ? 0 : (i1 + 1);
                nk_size idx2 = ((i1+1) == points_count) ? index: (idx1 + 3);

                dm = nk_vec2_muls(nk_vec2_add(normals[i1], normals[i2]), 0.5f);
                dmr2 = dm.x * dm.x + dm.y* dm.y;
                if (dmr2 > 0.000001f) {
                    float scale = 1.0f/dmr2;
                    scale = NK_MIN(100.0f, scale);
                    dm = nk_vec2_muls(dm, scale);
                }

                dm = nk_vec2_muls(dm, AA_SIZE);
                temp[i2*2+0] = nk_vec2_add(points[i2], dm);
                temp[i2*2+1] = nk_vec2_sub(points[i2], dm);

                ids[0] = (nk_draw_index)(idx2 + 0); ids[1] = (nk_draw_index)(idx1+0);
                ids[2] = (nk_draw_index)(idx1 + 2); ids[3] = (nk_draw_index)(idx1+2);
                ids[4] = (nk_draw_index)(idx2 + 2); ids[5] = (nk_draw_index)(idx2+0);
                ids[6] = (nk_draw_index)(idx2 + 1); ids[7] = (nk_draw_index)(idx1+1);
                ids[8] = (nk_draw_index)(idx1 + 0); ids[9] = (nk_draw_index)(idx1+0);
                ids[10]= (nk_draw_index)(idx2 + 0); ids[11]= (nk_draw_index)(idx2+1);
                ids += 12;
                idx1 = idx2;
            }

            for (i = 0; i < points_count; ++i) {
                const struct nk_vec2 uv = list->config.tex_null.uv;
                vtx = nk_draw_vertex(vtx, &list->config, points[i], uv, col);
                vtx = nk_draw_vertex(vtx, &list->config, temp[i*2+0], uv, col_trans);
                vtx = nk_draw_vertex(vtx, &list->config, temp[i*2+1], uv, col_trans);
            }
        } else {
            nk_size idx1, i;
            const float half_inner_thickness = (thickness - AA_SIZE) * 0.5f;
            if (!closed) {
                struct nk_vec2 d1 = nk_vec2_muls(normals[0], half_inner_thickness + AA_SIZE);
                struct nk_vec2 d2 = nk_vec2_muls(normals[0], half_inner_thickness);

                temp[0] = nk_vec2_add(points[0], d1);
                temp[1] = nk_vec2_add(points[0], d2);
                temp[2] = nk_vec2_sub(points[0], d2);
                temp[3] = nk_vec2_sub(points[0], d1);

                d1 = nk_vec2_muls(normals[points_count-1], half_inner_thickness + AA_SIZE);
                d2 = nk_vec2_muls(normals[points_count-1], half_inner_thickness);

                temp[(points_count-1)*4+0] = nk_vec2_add(points[points_count-1], d1);
                temp[(points_count-1)*4+1] = nk_vec2_add(points[points_count-1], d2);
                temp[(points_count-1)*4+2] = nk_vec2_sub(points[points_count-1], d2);
                temp[(points_count-1)*4+3] = nk_vec2_sub(points[points_count-1], d1);
            }

            idx1 = index;
            for (i1 = 0; i1 < count; ++i1) {
                struct nk_vec2 dm_out, dm_in;
                const nk_size i2 = ((i1+1) == points_count) ? 0: (i1 + 1);
                nk_size idx2 = ((i1+1) == points_count) ? index: (idx1 + 4);

                struct nk_vec2 dm = nk_vec2_muls(nk_vec2_add(normals[i1], normals[i2]), 0.5f);
                float dmr2 = dm.x * dm.x + dm.y* dm.y;
                if (dmr2 > 0.000001f) {
                    float scale = 1.0f/dmr2;
                    scale = NK_MIN(100.0f, scale);
                    dm = nk_vec2_muls(dm, scale);
                }

                dm_out = nk_vec2_muls(dm, ((half_inner_thickness) + AA_SIZE));
                dm_in = nk_vec2_muls(dm, half_inner_thickness);
                temp[i2*4+0] = nk_vec2_add(points[i2], dm_out);
                temp[i2*4+1] = nk_vec2_add(points[i2], dm_in);
                temp[i2*4+2] = nk_vec2_sub(points[i2], dm_in);
                temp[i2*4+3] = nk_vec2_sub(points[i2], dm_out);

                ids[0] = (nk_draw_index)(idx2 + 1); ids[1] = (nk_draw_index)(idx1+1);
                ids[2] = (nk_draw_index)(idx1 + 2); ids[3] = (nk_draw_index)(idx1+2);
                ids[4] = (nk_draw_index)(idx2 + 2); ids[5] = (nk_draw_index)(idx2+1);
                ids[6] = (nk_draw_index)(idx2 + 1); ids[7] = (nk_draw_index)(idx1+1);
                ids[8] = (nk_draw_index)(idx1 + 0); ids[9] = (nk_draw_index)(idx1+0);
                ids[10]= (nk_draw_index)(idx2 + 0); ids[11] = (nk_draw_index)(idx2+1);
                ids[12]= (nk_draw_index)(idx2 + 2); ids[13] = (nk_draw_index)(idx1+2);
                ids[14]= (nk_draw_index)(idx1 + 3); ids[15] = (nk_draw_index)(idx1+3);
                ids[16]= (nk_draw_index)(idx2 + 3); ids[17] = (nk_draw_index)(idx2+2);
                ids += 18;
                idx1 = idx2;
            }

            for (i = 0; i < points_count; ++i) {
                const struct nk_vec2 uv = list->config.tex_null.uv;
                vtx = nk_draw_vertex(vtx, &list->config, temp[i*4+0], uv, col_trans);
                vtx = nk_draw_vertex(vtx, &list->config, temp[i*4+1], uv, col);
                vtx = nk_draw_vertex(vtx, &list->config, temp[i*4+2], uv, col);
                vtx = nk_draw_vertex(vtx, &list->config, temp[i*4+3], uv, col_trans);
            }
        }

        nk_buffer_reset(list->vertices, NK_BUFFER_FRONT);
    } else {

        nk_size i1 = 0;
        nk_size idx = list->vertex_count;
        const nk_size idx_count = count * 6;
        const nk_size vtx_count = count * 4;
        void *vtx = nk_draw_list_alloc_vertices(list, vtx_count);
        nk_draw_index *ids = nk_draw_list_alloc_elements(list, idx_count);
        if (!vtx || !ids) return;

        for (i1 = 0; i1 < count; ++i1) {
            float dx, dy;
            const struct nk_vec2 uv = list->config.tex_null.uv;
            const nk_size i2 = ((i1+1) == points_count) ? 0 : i1 + 1;
            const struct nk_vec2 p1 = points[i1];
            const struct nk_vec2 p2 = points[i2];
            struct nk_vec2 diff = nk_vec2_sub(p2, p1);
            float len;

            len = nk_vec2_len_sqr(diff);
            if (len != 0.0f)
                len = NK_INV_SQRT(len);
            else len = 1.0f;
            diff = nk_vec2_muls(diff, len);

            dx = diff.x * (thickness * 0.5f);
            dy = diff.y * (thickness * 0.5f);

            vtx = nk_draw_vertex(vtx, &list->config, nk_vec2(p1.x + dy, p1.y - dx), uv, col);
            vtx = nk_draw_vertex(vtx, &list->config, nk_vec2(p2.x + dy, p2.y - dx), uv, col);
            vtx = nk_draw_vertex(vtx, &list->config, nk_vec2(p2.x - dy, p2.y + dx), uv, col);
            vtx = nk_draw_vertex(vtx, &list->config, nk_vec2(p1.x - dy, p1.y + dx), uv, col);

            ids[0] = (nk_draw_index)(idx+0); ids[1] = (nk_draw_index)(idx+1);
            ids[2] = (nk_draw_index)(idx+2); ids[3] = (nk_draw_index)(idx+0);
            ids[4] = (nk_draw_index)(idx+2); ids[5] = (nk_draw_index)(idx+3);

            ids += 6;
            idx += 4;
        }
    }
}
NK_API void
nk_draw_list_fill_poly_convex(struct nk_draw_list *list,
    const struct nk_vec2 *points, const unsigned int points_count,
    struct nk_color color, enum nk_anti_aliasing aliasing)
{
    struct nk_colorf col;
    struct nk_colorf col_trans;

    NK_STORAGE const nk_size pnt_align = NK_ALIGNOF(struct nk_vec2);
    NK_STORAGE const nk_size pnt_size = sizeof(struct nk_vec2);
    NK_ASSERT(list);
    if (!list || points_count < 3) return;

#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_draw_list_push_userdata(list, list->userdata);
#endif

    color.a = (nk_byte)((float)color.a * list->config.global_alpha);
    nk_color_fv(&col.r, color);
    col_trans = col;
    col_trans.a = 0;

    if (aliasing == NK_ANTI_ALIASING_ON) {
        nk_size i = 0;
        nk_size i0 = 0;
        nk_size i1 = 0;

        const float AA_SIZE = 1.0f;
        nk_size vertex_offset = 0;
        nk_size index = list->vertex_count;

        const nk_size idx_count = (points_count-2)*3 + points_count*6;
        const nk_size vtx_count = (points_count*2);

        void *vtx = nk_draw_list_alloc_vertices(list, vtx_count);
        nk_draw_index *ids = nk_draw_list_alloc_elements(list, idx_count);

        nk_size size = 0;
        struct nk_vec2 *normals = 0;
        unsigned int vtx_inner_idx = (unsigned int)(index + 0);
        unsigned int vtx_outer_idx = (unsigned int)(index + 1);
        if (!vtx || !ids) return;

        vertex_offset = (nk_size)((nk_byte*)vtx - (nk_byte*)list->vertices->memory.ptr);
        nk_buffer_mark(list->vertices, NK_BUFFER_FRONT);
        size = pnt_size * points_count;
        normals = (struct nk_vec2*) nk_buffer_alloc(list->vertices, NK_BUFFER_FRONT, size, pnt_align);
        if (!normals) return;
        vtx = (void*)((nk_byte*)list->vertices->memory.ptr + vertex_offset);

        for (i = 2; i < points_count; i++) {
            ids[0] = (nk_draw_index)(vtx_inner_idx);
            ids[1] = (nk_draw_index)(vtx_inner_idx + ((i-1) << 1));
            ids[2] = (nk_draw_index)(vtx_inner_idx + (i << 1));
            ids += 3;
        }

        for (i0 = points_count-1, i1 = 0; i1 < points_count; i0 = i1++) {
            struct nk_vec2 p0 = points[i0];
            struct nk_vec2 p1 = points[i1];
            struct nk_vec2 diff = nk_vec2_sub(p1, p0);

            float len = nk_vec2_len_sqr(diff);
            if (len != 0.0f)
                len = NK_INV_SQRT(len);
            else len = 1.0f;
            diff = nk_vec2_muls(diff, len);

            normals[i0].x = diff.y;
            normals[i0].y = -diff.x;
        }

        for (i0 = points_count-1, i1 = 0; i1 < points_count; i0 = i1++) {
            const struct nk_vec2 uv = list->config.tex_null.uv;
            struct nk_vec2 n0 = normals[i0];
            struct nk_vec2 n1 = normals[i1];
            struct nk_vec2 dm = nk_vec2_muls(nk_vec2_add(n0, n1), 0.5f);
            float dmr2 = dm.x*dm.x + dm.y*dm.y;
            if (dmr2 > 0.000001f) {
                float scale = 1.0f / dmr2;
                scale = NK_MIN(scale, 100.0f);
                dm = nk_vec2_muls(dm, scale);
            }
            dm = nk_vec2_muls(dm, AA_SIZE * 0.5f);

            vtx = nk_draw_vertex(vtx, &list->config, nk_vec2_sub(points[i1], dm), uv, col);
            vtx = nk_draw_vertex(vtx, &list->config, nk_vec2_add(points[i1], dm), uv, col_trans);

            ids[0] = (nk_draw_index)(vtx_inner_idx+(i1<<1));
            ids[1] = (nk_draw_index)(vtx_inner_idx+(i0<<1));
            ids[2] = (nk_draw_index)(vtx_outer_idx+(i0<<1));
            ids[3] = (nk_draw_index)(vtx_outer_idx+(i0<<1));
            ids[4] = (nk_draw_index)(vtx_outer_idx+(i1<<1));
            ids[5] = (nk_draw_index)(vtx_inner_idx+(i1<<1));
            ids += 6;
        }

        nk_buffer_reset(list->vertices, NK_BUFFER_FRONT);
    } else {
        nk_size i = 0;
        nk_size index = list->vertex_count;
        const nk_size idx_count = (points_count-2)*3;
        const nk_size vtx_count = points_count;
        void *vtx = nk_draw_list_alloc_vertices(list, vtx_count);
        nk_draw_index *ids = nk_draw_list_alloc_elements(list, idx_count);

        if (!vtx || !ids) return;
        for (i = 0; i < vtx_count; ++i)
            vtx = nk_draw_vertex(vtx, &list->config, points[i], list->config.tex_null.uv, col);
        for (i = 2; i < points_count; ++i) {
            ids[0] = (nk_draw_index)index;
            ids[1] = (nk_draw_index)(index+ i - 1);
            ids[2] = (nk_draw_index)(index+i);
            ids += 3;
        }
    }
}
NK_API void
nk_draw_list_path_clear(struct nk_draw_list *list)
{
    NK_ASSERT(list);
    if (!list) return;
    nk_buffer_reset(list->buffer, NK_BUFFER_FRONT);
    list->path_count = 0;
    list->path_offset = 0;
}
NK_API void
nk_draw_list_path_line_to(struct nk_draw_list *list, struct nk_vec2 pos)
{
    struct nk_vec2 *points = 0;
    struct nk_draw_command *cmd = 0;
    NK_ASSERT(list);
    if (!list) return;
    if (!list->cmd_count)
        nk_draw_list_add_clip(list, nk_null_rect);

    cmd = nk_draw_list_command_last(list);
    if (cmd && cmd->texture.ptr != list->config.tex_null.texture.ptr)
        nk_draw_list_push_image(list, list->config.tex_null.texture);

    points = nk_draw_list_alloc_path(list, 1);
    if (!points) return;
    points[0] = pos;
}
NK_API void
nk_draw_list_path_arc_to_fast(struct nk_draw_list *list, struct nk_vec2 center,
    float radius, int a_min, int a_max)
{
    int a = 0;
    NK_ASSERT(list);
    if (!list) return;
    if (a_min <= a_max) {
        for (a = a_min; a <= a_max; a++) {
            const struct nk_vec2 c = list->circle_vtx[(nk_size)a % NK_LEN(list->circle_vtx)];
            const float x = center.x + c.x * radius;
            const float y = center.y + c.y * radius;
            nk_draw_list_path_line_to(list, nk_vec2(x, y));
        }
    }
}
NK_API void
nk_draw_list_path_arc_to(struct nk_draw_list *list, struct nk_vec2 center,
    float radius, float a_min, float a_max, unsigned int segments)
{
    unsigned int i = 0;
    NK_ASSERT(list);
    if (!list) return;
    if (radius == 0.0f) return;

    {const float d_angle = (a_max - a_min) / (float)segments;
    const float sin_d = (float)NK_SIN(d_angle);
    const float cos_d = (float)NK_COS(d_angle);

    float cx = (float)NK_COS(a_min) * radius;
    float cy = (float)NK_SIN(a_min) * radius;
    for(i = 0; i <= segments; ++i) {
        float new_cx, new_cy;
        const float x = center.x + cx;
        const float y = center.y + cy;
        nk_draw_list_path_line_to(list, nk_vec2(x, y));

        new_cx = cx * cos_d - cy * sin_d;
        new_cy = cy * cos_d + cx * sin_d;
        cx = new_cx;
        cy = new_cy;
    }}
}
NK_API void
nk_draw_list_path_rect_to(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 b, float rounding)
{
    float r;
    NK_ASSERT(list);
    if (!list) return;
    r = rounding;
    r = NK_MIN(r, ((b.x-a.x) < 0) ? -(b.x-a.x): (b.x-a.x));
    r = NK_MIN(r, ((b.y-a.y) < 0) ? -(b.y-a.y): (b.y-a.y));

    if (r == 0.0f) {
        nk_draw_list_path_line_to(list, a);
        nk_draw_list_path_line_to(list, nk_vec2(b.x,a.y));
        nk_draw_list_path_line_to(list, b);
        nk_draw_list_path_line_to(list, nk_vec2(a.x,b.y));
    } else {
        nk_draw_list_path_arc_to_fast(list, nk_vec2(a.x + r, a.y + r), r, 6, 9);
        nk_draw_list_path_arc_to_fast(list, nk_vec2(b.x - r, a.y + r), r, 9, 12);
        nk_draw_list_path_arc_to_fast(list, nk_vec2(b.x - r, b.y - r), r, 0, 3);
        nk_draw_list_path_arc_to_fast(list, nk_vec2(a.x + r, b.y - r), r, 3, 6);
    }
}
NK_API void
nk_draw_list_path_curve_to(struct nk_draw_list *list, struct nk_vec2 p2,
    struct nk_vec2 p3, struct nk_vec2 p4, unsigned int num_segments)
{
    float t_step;
    unsigned int i_step;
    struct nk_vec2 p1;

    NK_ASSERT(list);
    NK_ASSERT(list->path_count);
    if (!list || !list->path_count) return;
    num_segments = NK_MAX(num_segments, 1);

    p1 = nk_draw_list_path_last(list);
    t_step = 1.0f/(float)num_segments;
    for (i_step = 1; i_step <= num_segments; ++i_step) {
        float t = t_step * (float)i_step;
        float u = 1.0f - t;
        float w1 = u*u*u;
        float w2 = 3*u*u*t;
        float w3 = 3*u*t*t;
        float w4 = t * t *t;
        float x = w1 * p1.x + w2 * p2.x + w3 * p3.x + w4 * p4.x;
        float y = w1 * p1.y + w2 * p2.y + w3 * p3.y + w4 * p4.y;
        nk_draw_list_path_line_to(list, nk_vec2(x,y));
    }
}
NK_API void
nk_draw_list_path_fill(struct nk_draw_list *list, struct nk_color color)
{
    struct nk_vec2 *points;
    NK_ASSERT(list);
    if (!list) return;
    points = (struct nk_vec2*)nk_buffer_memory(list->buffer);
    nk_draw_list_fill_poly_convex(list, points, list->path_count, color, list->config.shape_AA);
    nk_draw_list_path_clear(list);
}
NK_API void
nk_draw_list_path_stroke(struct nk_draw_list *list, struct nk_color color,
    enum nk_draw_list_stroke closed, float thickness)
{
    struct nk_vec2 *points;
    NK_ASSERT(list);
    if (!list) return;
    points = (struct nk_vec2*)nk_buffer_memory(list->buffer);
    nk_draw_list_stroke_poly_line(list, points, list->path_count, color,
        closed, thickness, list->config.line_AA);
    nk_draw_list_path_clear(list);
}
NK_API void
nk_draw_list_stroke_line(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 b, struct nk_color col, float thickness)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    if (list->line_AA == NK_ANTI_ALIASING_ON) {
        nk_draw_list_path_line_to(list, a);
        nk_draw_list_path_line_to(list, b);
    } else {
        nk_draw_list_path_line_to(list, nk_vec2_sub(a,nk_vec2(0.5f,0.5f)));
        nk_draw_list_path_line_to(list, nk_vec2_sub(b,nk_vec2(0.5f,0.5f)));
    }
    nk_draw_list_path_stroke(list,  col, NK_STROKE_OPEN, thickness);
}
NK_API void
nk_draw_list_fill_rect(struct nk_draw_list *list, struct nk_rect rect,
    struct nk_color col, float rounding)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;

    if (list->line_AA == NK_ANTI_ALIASING_ON) {
        nk_draw_list_path_rect_to(list, nk_vec2(rect.x, rect.y),
            nk_vec2(rect.x + rect.w, rect.y + rect.h), rounding);
    } else {
        nk_draw_list_path_rect_to(list, nk_vec2(rect.x-0.5f, rect.y-0.5f),
            nk_vec2(rect.x + rect.w, rect.y + rect.h), rounding);
    } nk_draw_list_path_fill(list,  col);
}
NK_API void
nk_draw_list_stroke_rect(struct nk_draw_list *list, struct nk_rect rect,
    struct nk_color col, float rounding, float thickness)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    if (list->line_AA == NK_ANTI_ALIASING_ON) {
        nk_draw_list_path_rect_to(list, nk_vec2(rect.x, rect.y),
            nk_vec2(rect.x + rect.w, rect.y + rect.h), rounding);
    } else {
        nk_draw_list_path_rect_to(list, nk_vec2(rect.x-0.5f, rect.y-0.5f),
            nk_vec2(rect.x + rect.w, rect.y + rect.h), rounding);
    } nk_draw_list_path_stroke(list,  col, NK_STROKE_CLOSED, thickness);
}
NK_API void
nk_draw_list_fill_rect_multi_color(struct nk_draw_list *list, struct nk_rect rect,
    struct nk_color left, struct nk_color top, struct nk_color right,
    struct nk_color bottom)
{
    void *vtx;
    struct nk_colorf col_left, col_top;
    struct nk_colorf col_right, col_bottom;
    nk_draw_index *idx;
    nk_draw_index index;

    nk_color_fv(&col_left.r, left);
    nk_color_fv(&col_right.r, right);
    nk_color_fv(&col_top.r, top);
    nk_color_fv(&col_bottom.r, bottom);

    NK_ASSERT(list);
    if (!list) return;

    nk_draw_list_push_image(list, list->config.tex_null.texture);
    index = (nk_draw_index)list->vertex_count;
    vtx = nk_draw_list_alloc_vertices(list, 4);
    idx = nk_draw_list_alloc_elements(list, 6);
    if (!vtx || !idx) return;

    idx[0] = (nk_draw_index)(index+0); idx[1] = (nk_draw_index)(index+1);
    idx[2] = (nk_draw_index)(index+2); idx[3] = (nk_draw_index)(index+0);
    idx[4] = (nk_draw_index)(index+2); idx[5] = (nk_draw_index)(index+3);

    vtx = nk_draw_vertex(vtx, &list->config, nk_vec2(rect.x, rect.y), list->config.tex_null.uv, col_left);
    vtx = nk_draw_vertex(vtx, &list->config, nk_vec2(rect.x + rect.w, rect.y), list->config.tex_null.uv, col_top);
    vtx = nk_draw_vertex(vtx, &list->config, nk_vec2(rect.x + rect.w, rect.y + rect.h), list->config.tex_null.uv, col_right);
    vtx = nk_draw_vertex(vtx, &list->config, nk_vec2(rect.x, rect.y + rect.h), list->config.tex_null.uv, col_bottom);
}
NK_API void
nk_draw_list_fill_triangle(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 b, struct nk_vec2 c, struct nk_color col)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_line_to(list, a);
    nk_draw_list_path_line_to(list, b);
    nk_draw_list_path_line_to(list, c);
    nk_draw_list_path_fill(list, col);
}
NK_API void
nk_draw_list_stroke_triangle(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 b, struct nk_vec2 c, struct nk_color col, float thickness)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_line_to(list, a);
    nk_draw_list_path_line_to(list, b);
    nk_draw_list_path_line_to(list, c);
    nk_draw_list_path_stroke(list, col, NK_STROKE_CLOSED, thickness);
}
NK_API void
nk_draw_list_fill_circle(struct nk_draw_list *list, struct nk_vec2 center,
    float radius, struct nk_color col, unsigned int segs)
{
    float a_max;
    NK_ASSERT(list);
    if (!list || !col.a) return;
    a_max = NK_PI * 2.0f * ((float)segs - 1.0f) / (float)segs;
    nk_draw_list_path_arc_to(list, center, radius, 0.0f, a_max, segs);
    nk_draw_list_path_fill(list, col);
}
NK_API void
nk_draw_list_stroke_circle(struct nk_draw_list *list, struct nk_vec2 center,
    float radius, struct nk_color col, unsigned int segs, float thickness)
{
    float a_max;
    NK_ASSERT(list);
    if (!list || !col.a) return;
    a_max = NK_PI * 2.0f * ((float)segs - 1.0f) / (float)segs;
    nk_draw_list_path_arc_to(list, center, radius, 0.0f, a_max, segs);
    nk_draw_list_path_stroke(list, col, NK_STROKE_CLOSED, thickness);
}
NK_API void
nk_draw_list_stroke_curve(struct nk_draw_list *list, struct nk_vec2 p0,
    struct nk_vec2 cp0, struct nk_vec2 cp1, struct nk_vec2 p1,
    struct nk_color col, unsigned int segments, float thickness)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_line_to(list, p0);
    nk_draw_list_path_curve_to(list, cp0, cp1, p1, segments);
    nk_draw_list_path_stroke(list, col, NK_STROKE_OPEN, thickness);
}
NK_INTERN void
nk_draw_list_push_rect_uv(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 c, struct nk_vec2 uva, struct nk_vec2 uvc,
    struct nk_color color)
{
    void *vtx;
    struct nk_vec2 uvb;
    struct nk_vec2 uvd;
    struct nk_vec2 b;
    struct nk_vec2 d;

    struct nk_colorf col;
    nk_draw_index *idx;
    nk_draw_index index;
    NK_ASSERT(list);
    if (!list) return;

    nk_color_fv(&col.r, color);
    uvb = nk_vec2(uvc.x, uva.y);
    uvd = nk_vec2(uva.x, uvc.y);
    b = nk_vec2(c.x, a.y);
    d = nk_vec2(a.x, c.y);

    index = (nk_draw_index)list->vertex_count;
    vtx = nk_draw_list_alloc_vertices(list, 4);
    idx = nk_draw_list_alloc_elements(list, 6);
    if (!vtx || !idx) return;

    idx[0] = (nk_draw_index)(index+0); idx[1] = (nk_draw_index)(index+1);
    idx[2] = (nk_draw_index)(index+2); idx[3] = (nk_draw_index)(index+0);
    idx[4] = (nk_draw_index)(index+2); idx[5] = (nk_draw_index)(index+3);

    vtx = nk_draw_vertex(vtx, &list->config, a, uva, col);
    vtx = nk_draw_vertex(vtx, &list->config, b, uvb, col);
    vtx = nk_draw_vertex(vtx, &list->config, c, uvc, col);
    vtx = nk_draw_vertex(vtx, &list->config, d, uvd, col);
}
NK_API void
nk_draw_list_add_image(struct nk_draw_list *list, struct nk_image texture,
    struct nk_rect rect, struct nk_color color)
{
    NK_ASSERT(list);
    if (!list) return;

    nk_draw_list_push_image(list, texture.handle);
    if (nk_image_is_subimage(&texture)) {

        struct nk_vec2 uv[2];
        uv[0].x = (float)texture.region[0]/(float)texture.w;
        uv[0].y = (float)texture.region[1]/(float)texture.h;
        uv[1].x = (float)(texture.region[0] + texture.region[2])/(float)texture.w;
        uv[1].y = (float)(texture.region[1] + texture.region[3])/(float)texture.h;
        nk_draw_list_push_rect_uv(list, nk_vec2(rect.x, rect.y),
            nk_vec2(rect.x + rect.w, rect.y + rect.h),  uv[0], uv[1], color);
    } else nk_draw_list_push_rect_uv(list, nk_vec2(rect.x, rect.y),
            nk_vec2(rect.x + rect.w, rect.y + rect.h),
            nk_vec2(0.0f, 0.0f), nk_vec2(1.0f, 1.0f),color);
}
NK_API void
nk_draw_list_add_text(struct nk_draw_list *list, const struct nk_user_font *font,
    struct nk_rect rect, const char *text, int len, float font_height,
    struct nk_color fg)
{
    float x = 0;
    int text_len = 0;
    nk_rune unicode = 0;
    nk_rune next = 0;
    int glyph_len = 0;
    int next_glyph_len = 0;
    struct nk_user_font_glyph g;

    NK_ASSERT(list);
    if (!list || !len || !text) return;
    if (!NK_INTERSECT(rect.x, rect.y, rect.w, rect.h,
        list->clip_rect.x, list->clip_rect.y, list->clip_rect.w, list->clip_rect.h)) return;

    nk_draw_list_push_image(list, font->texture);
    x = rect.x;
    glyph_len = nk_utf_decode(text, &unicode, len);
    if (!glyph_len) return;

    fg.a = (nk_byte)((float)fg.a * list->config.global_alpha);
    while (text_len < len && glyph_len) {
        float gx, gy, gh, gw;
        float char_width = 0;
        if (unicode == NK_UTF_INVALID) break;

        next_glyph_len = nk_utf_decode(text + text_len + glyph_len, &next, (int)len - text_len);
        font->query(font->userdata, font_height, &g, unicode,
                    (next == NK_UTF_INVALID) ? '\0' : next);

        gx = x + g.offset.x;
        gy = rect.y + g.offset.y;
        gw = g.width; gh = g.height;
        char_width = g.xadvance;
        nk_draw_list_push_rect_uv(list, nk_vec2(gx,gy), nk_vec2(gx + gw, gy+ gh),
            g.uv[0], g.uv[1], fg);

        text_len += glyph_len;
        x += char_width;
        glyph_len = next_glyph_len;
        unicode = next;
    }
}
NK_API nk_flags
nk_convert(struct nk_context *ctx, struct nk_buffer *cmds,
    struct nk_buffer *vertices, struct nk_buffer *elements,
    const struct nk_convert_config *config)
{
    nk_flags res = NK_CONVERT_SUCCESS;
    const struct nk_command *cmd;
    NK_ASSERT(ctx);
    NK_ASSERT(cmds);
    NK_ASSERT(vertices);
    NK_ASSERT(elements);
    NK_ASSERT(config);
    NK_ASSERT(config->vertex_layout);
    NK_ASSERT(config->vertex_size);
    if (!ctx || !cmds || !vertices || !elements || !config || !config->vertex_layout)
        return NK_CONVERT_INVALID_PARAM;

    nk_draw_list_setup(&ctx->draw_list, config, cmds, vertices, elements,
        config->line_AA, config->shape_AA);
    nk_foreach(cmd, ctx)
    {
#ifdef NK_INCLUDE_COMMAND_USERDATA
        ctx->draw_list.userdata = cmd->userdata;
#endif
        switch (cmd->type) {
        case NK_COMMAND_NOP: break;
        case NK_COMMAND_SCISSOR: {
            const struct nk_command_scissor *s = (const struct nk_command_scissor*)cmd;
            nk_draw_list_add_clip(&ctx->draw_list, nk_rect(s->x, s->y, s->w, s->h));
        } break;
        case NK_COMMAND_LINE: {
            const struct nk_command_line *l = (const struct nk_command_line*)cmd;
            nk_draw_list_stroke_line(&ctx->draw_list, nk_vec2(l->begin.x, l->begin.y),
                nk_vec2(l->end.x, l->end.y), l->color, l->line_thickness);
        } break;
        case NK_COMMAND_CURVE: {
            const struct nk_command_curve *q = (const struct nk_command_curve*)cmd;
            nk_draw_list_stroke_curve(&ctx->draw_list, nk_vec2(q->begin.x, q->begin.y),
                nk_vec2(q->ctrl[0].x, q->ctrl[0].y), nk_vec2(q->ctrl[1].x,
                q->ctrl[1].y), nk_vec2(q->end.x, q->end.y), q->color,
                config->curve_segment_count, q->line_thickness);
        } break;
        case NK_COMMAND_RECT: {
            const struct nk_command_rect *r = (const struct nk_command_rect*)cmd;
            nk_draw_list_stroke_rect(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
                r->color, (float)r->rounding, r->line_thickness);
        } break;
        case NK_COMMAND_RECT_FILLED: {
            const struct nk_command_rect_filled *r = (const struct nk_command_rect_filled*)cmd;
            nk_draw_list_fill_rect(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
                r->color, (float)r->rounding);
        } break;
        case NK_COMMAND_RECT_MULTI_COLOR: {
            const struct nk_command_rect_multi_color *r = (const struct nk_command_rect_multi_color*)cmd;
            nk_draw_list_fill_rect_multi_color(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
                r->left, r->top, r->right, r->bottom);
        } break;
        case NK_COMMAND_CIRCLE: {
            const struct nk_command_circle *c = (const struct nk_command_circle*)cmd;
            nk_draw_list_stroke_circle(&ctx->draw_list, nk_vec2((float)c->x + (float)c->w/2,
                (float)c->y + (float)c->h/2), (float)c->w/2, c->color,
                config->circle_segment_count, c->line_thickness);
        } break;
        case NK_COMMAND_CIRCLE_FILLED: {
            const struct nk_command_circle_filled *c = (const struct nk_command_circle_filled *)cmd;
            nk_draw_list_fill_circle(&ctx->draw_list, nk_vec2((float)c->x + (float)c->w/2,
                (float)c->y + (float)c->h/2), (float)c->w/2, c->color,
                config->circle_segment_count);
        } break;
        case NK_COMMAND_ARC: {
            const struct nk_command_arc *c = (const struct nk_command_arc*)cmd;
            nk_draw_list_path_line_to(&ctx->draw_list, nk_vec2(c->cx, c->cy));
            nk_draw_list_path_arc_to(&ctx->draw_list, nk_vec2(c->cx, c->cy), c->r,
                c->a[0], c->a[1], config->arc_segment_count);
            nk_draw_list_path_stroke(&ctx->draw_list, c->color, NK_STROKE_CLOSED, c->line_thickness);
        } break;
        case NK_COMMAND_ARC_FILLED: {
            const struct nk_command_arc_filled *c = (const struct nk_command_arc_filled*)cmd;
            nk_draw_list_path_line_to(&ctx->draw_list, nk_vec2(c->cx, c->cy));
            nk_draw_list_path_arc_to(&ctx->draw_list, nk_vec2(c->cx, c->cy), c->r,
                c->a[0], c->a[1], config->arc_segment_count);
            nk_draw_list_path_fill(&ctx->draw_list, c->color);
        } break;
        case NK_COMMAND_TRIANGLE: {
            const struct nk_command_triangle *t = (const struct nk_command_triangle*)cmd;
            nk_draw_list_stroke_triangle(&ctx->draw_list, nk_vec2(t->a.x, t->a.y),
                nk_vec2(t->b.x, t->b.y), nk_vec2(t->c.x, t->c.y), t->color,
                t->line_thickness);
        } break;
        case NK_COMMAND_TRIANGLE_FILLED: {
            const struct nk_command_triangle_filled *t = (const struct nk_command_triangle_filled*)cmd;
            nk_draw_list_fill_triangle(&ctx->draw_list, nk_vec2(t->a.x, t->a.y),
                nk_vec2(t->b.x, t->b.y), nk_vec2(t->c.x, t->c.y), t->color);
        } break;
        case NK_COMMAND_POLYGON: {
            int i;
            const struct nk_command_polygon*p = (const struct nk_command_polygon*)cmd;
            for (i = 0; i < p->point_count; ++i) {
                struct nk_vec2 pnt = nk_vec2((float)p->points[i].x, (float)p->points[i].y);
                nk_draw_list_path_line_to(&ctx->draw_list, pnt);
            }
            nk_draw_list_path_stroke(&ctx->draw_list, p->color, NK_STROKE_CLOSED, p->line_thickness);
        } break;
        case NK_COMMAND_POLYGON_FILLED: {
            int i;
            const struct nk_command_polygon_filled *p = (const struct nk_command_polygon_filled*)cmd;
            for (i = 0; i < p->point_count; ++i) {
                struct nk_vec2 pnt = nk_vec2((float)p->points[i].x, (float)p->points[i].y);
                nk_draw_list_path_line_to(&ctx->draw_list, pnt);
            }
            nk_draw_list_path_fill(&ctx->draw_list, p->color);
        } break;
        case NK_COMMAND_POLYLINE: {
            int i;
            const struct nk_command_polyline *p = (const struct nk_command_polyline*)cmd;
            for (i = 0; i < p->point_count; ++i) {
                struct nk_vec2 pnt = nk_vec2((float)p->points[i].x, (float)p->points[i].y);
                nk_draw_list_path_line_to(&ctx->draw_list, pnt);
            }
            nk_draw_list_path_stroke(&ctx->draw_list, p->color, NK_STROKE_OPEN, p->line_thickness);
        } break;
        case NK_COMMAND_TEXT: {
            const struct nk_command_text *t = (const struct nk_command_text*)cmd;
            nk_draw_list_add_text(&ctx->draw_list, t->font, nk_rect(t->x, t->y, t->w, t->h),
                t->string, t->length, t->height, t->foreground);
        } break;
        case NK_COMMAND_IMAGE: {
            const struct nk_command_image *i = (const struct nk_command_image*)cmd;
            nk_draw_list_add_image(&ctx->draw_list, i->img, nk_rect(i->x, i->y, i->w, i->h), i->col);
        } break;
        case NK_COMMAND_CUSTOM: {
            const struct nk_command_custom *c = (const struct nk_command_custom*)cmd;
            c->callback(&ctx->draw_list, c->x, c->y, c->w, c->h, c->callback_data);
        } break;
        default: break;
        }
    }
    res |= (cmds->needed > cmds->allocated + (cmds->memory.size - cmds->size)) ? NK_CONVERT_COMMAND_BUFFER_FULL: 0;
    res |= (vertices->needed > vertices->allocated) ? NK_CONVERT_VERTEX_BUFFER_FULL: 0;
    res |= (elements->needed > elements->allocated) ? NK_CONVERT_ELEMENT_BUFFER_FULL: 0;
    return res;
}
NK_API const struct nk_draw_command*
nk__draw_begin(const struct nk_context *ctx,
    const struct nk_buffer *buffer)
{
    return nk__draw_list_begin(&ctx->draw_list, buffer);
}
NK_API const struct nk_draw_command*
nk__draw_end(const struct nk_context *ctx, const struct nk_buffer *buffer)
{
    return nk__draw_list_end(&ctx->draw_list, buffer);
}
NK_API const struct nk_draw_command*
nk__draw_next(const struct nk_draw_command *cmd,
    const struct nk_buffer *buffer, const struct nk_context *ctx)
{
    return nk__draw_list_next(cmd, buffer, &ctx->draw_list);
}
#endif

#ifndef STB_INCLUDE_STB_RECT_PACK_H
#define STB_INCLUDE_STB_RECT_PACK_H

#define STB_RECT_PACK_VERSION  1

#ifdef STBRP_STATIC
#define STBRP_DEF static
#else
#define STBRP_DEF extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stbrp_context stbrp_context;
typedef struct stbrp_node    stbrp_node;
typedef struct stbrp_rect    stbrp_rect;

typedef int            stbrp_coord;

#define STBRP__MAXVAL  0x7fffffff

STBRP_DEF int stbrp_pack_rects (stbrp_context *context, stbrp_rect *rects, int num_rects);

struct stbrp_rect
{

   int            id;

   stbrp_coord    w, h;

   stbrp_coord    x, y;
   int            was_packed;

};

STBRP_DEF void stbrp_init_target (stbrp_context *context, int width, int height, stbrp_node *nodes, int num_nodes);

STBRP_DEF void stbrp_setup_allow_out_of_mem (stbrp_context *context, int allow_out_of_mem);

STBRP_DEF void stbrp_setup_heuristic (stbrp_context *context, int heuristic);

enum
{
   STBRP_HEURISTIC_Skyline_default=0,
   STBRP_HEURISTIC_Skyline_BL_sortHeight = STBRP_HEURISTIC_Skyline_default,
   STBRP_HEURISTIC_Skyline_BF_sortHeight
};

struct stbrp_node
{
   stbrp_coord  x,y;
   stbrp_node  *next;
};

struct stbrp_context
{
   int width;
   int height;
   int align;
   int init_mode;
   int heuristic;
   int num_nodes;
   stbrp_node *active_head;
   stbrp_node *free_head;
   stbrp_node extra[2];
};

#ifdef __cplusplus
}
#endif

#endif

#ifdef STB_RECT_PACK_IMPLEMENTATION
#ifndef STBRP_SORT
#include <stdlib.h>
#define STBRP_SORT qsort
#endif

#ifndef STBRP_ASSERT
#include <assert.h>
#define STBRP_ASSERT assert
#endif

#ifdef _MSC_VER
#define STBRP__NOTUSED(v)  (void)(v)
#define STBRP__CDECL       __cdecl
#else
#define STBRP__NOTUSED(v)  (void)sizeof(v)
#define STBRP__CDECL
#endif

enum
{
   STBRP__INIT_skyline = 1
};

STBRP_DEF void stbrp_setup_heuristic(stbrp_context *context, int heuristic)
{
   switch (context->init_mode) {
      case STBRP__INIT_skyline:
         STBRP_ASSERT(heuristic == STBRP_HEURISTIC_Skyline_BL_sortHeight || heuristic == STBRP_HEURISTIC_Skyline_BF_sortHeight);
         context->heuristic = heuristic;
         break;
      default:
         STBRP_ASSERT(0);
   }
}

STBRP_DEF void stbrp_setup_allow_out_of_mem(stbrp_context *context, int allow_out_of_mem)
{
   if (allow_out_of_mem)

      context->align = 1;
   else {

      context->align = (context->width + context->num_nodes-1) / context->num_nodes;
   }
}

STBRP_DEF void stbrp_init_target(stbrp_context *context, int width, int height, stbrp_node *nodes, int num_nodes)
{
   int i;

   for (i=0; i < num_nodes-1; ++i)
      nodes[i].next = &nodes[i+1];
   nodes[i].next = NULL;
   context->init_mode = STBRP__INIT_skyline;
   context->heuristic = STBRP_HEURISTIC_Skyline_default;
   context->free_head = &nodes[0];
   context->active_head = &context->extra[0];
   context->width = width;
   context->height = height;
   context->num_nodes = num_nodes;
   stbrp_setup_allow_out_of_mem(context, 0);

   context->extra[0].x = 0;
   context->extra[0].y = 0;
   context->extra[0].next = &context->extra[1];
   context->extra[1].x = (stbrp_coord) width;
   context->extra[1].y = (1<<30);
   context->extra[1].next = NULL;
}

static int stbrp__skyline_find_min_y(stbrp_context *c, stbrp_node *first, int x0, int width, int *pwaste)
{
   stbrp_node *node = first;
   int x1 = x0 + width;
   int min_y, visited_width, waste_area;

   STBRP__NOTUSED(c);

   STBRP_ASSERT(first->x <= x0);

   #if 0

   while (node->next->x <= x0)
      ++node;
   #else
   STBRP_ASSERT(node->next->x > x0);
   #endif

   STBRP_ASSERT(node->x <= x0);

   min_y = 0;
   waste_area = 0;
   visited_width = 0;
   while (node->x < x1) {
      if (node->y > min_y) {

         waste_area += visited_width * (node->y - min_y);
         min_y = node->y;

         if (node->x < x0)
            visited_width += node->next->x - x0;
         else
            visited_width += node->next->x - node->x;
      } else {

         int under_width = node->next->x - node->x;
         if (under_width + visited_width > width)
            under_width = width - visited_width;
         waste_area += under_width * (min_y - node->y);
         visited_width += under_width;
      }
      node = node->next;
   }

   *pwaste = waste_area;
   return min_y;
}

typedef struct
{
   int x,y;
   stbrp_node **prev_link;
} stbrp__findresult;

static stbrp__findresult stbrp__skyline_find_best_pos(stbrp_context *c, int width, int height)
{
   int best_waste = (1<<30), best_x, best_y = (1 << 30);
   stbrp__findresult fr;
   stbrp_node **prev, *node, *tail, **best = NULL;

   width = (width + c->align - 1);
   width -= width % c->align;
   STBRP_ASSERT(width % c->align == 0);

   if (width > c->width || height > c->height) {
      fr.prev_link = NULL;
      fr.x = fr.y = 0;
      return fr;
   }

   node = c->active_head;
   prev = &c->active_head;
   while (node->x + width <= c->width) {
      int y,waste;
      y = stbrp__skyline_find_min_y(c, node, node->x, width, &waste);
      if (c->heuristic == STBRP_HEURISTIC_Skyline_BL_sortHeight) {

         if (y < best_y) {
            best_y = y;
            best = prev;
         }
      } else {

         if (y + height <= c->height) {

            if (y < best_y || (y == best_y && waste < best_waste)) {
               best_y = y;
               best_waste = waste;
               best = prev;
            }
         }
      }
      prev = &node->next;
      node = node->next;
   }

   best_x = (best == NULL) ? 0 : (*best)->x;

   if (c->heuristic == STBRP_HEURISTIC_Skyline_BF_sortHeight) {
      tail = c->active_head;
      node = c->active_head;
      prev = &c->active_head;

      while (tail->x < width)
         tail = tail->next;
      while (tail) {
         int xpos = tail->x - width;
         int y,waste;
         STBRP_ASSERT(xpos >= 0);

         while (node->next->x <= xpos) {
            prev = &node->next;
            node = node->next;
         }
         STBRP_ASSERT(node->next->x > xpos && node->x <= xpos);
         y = stbrp__skyline_find_min_y(c, node, xpos, width, &waste);
         if (y + height <= c->height) {
            if (y <= best_y) {
               if (y < best_y || waste < best_waste || (waste==best_waste && xpos < best_x)) {
                  best_x = xpos;
                  STBRP_ASSERT(y <= best_y);
                  best_y = y;
                  best_waste = waste;
                  best = prev;
               }
            }
         }
         tail = tail->next;
      }
   }

   fr.prev_link = best;
   fr.x = best_x;
   fr.y = best_y;
   return fr;
}

static stbrp__findresult stbrp__skyline_pack_rectangle(stbrp_context *context, int width, int height)
{

   stbrp__findresult res = stbrp__skyline_find_best_pos(context, width, height);
   stbrp_node *node, *cur;

   if (res.prev_link == NULL || res.y + height > context->height || context->free_head == NULL) {
      res.prev_link = NULL;
      return res;
   }

   node = context->free_head;
   node->x = (stbrp_coord) res.x;
   node->y = (stbrp_coord) (res.y + height);

   context->free_head = node->next;

   cur = *res.prev_link;
   if (cur->x < res.x) {

      stbrp_node *next = cur->next;
      cur->next = node;
      cur = next;
   } else {
      *res.prev_link = node;
   }

   while (cur->next && cur->next->x <= res.x + width) {
      stbrp_node *next = cur->next;

      cur->next = context->free_head;
      context->free_head = cur;
      cur = next;
   }

   node->next = cur;

   if (cur->x < res.x + width)
      cur->x = (stbrp_coord) (res.x + width);

#ifdef _DEBUG
   cur = context->active_head;
   while (cur->x < context->width) {
      STBRP_ASSERT(cur->x < cur->next->x);
      cur = cur->next;
   }
   STBRP_ASSERT(cur->next == NULL);

   {
      int count=0;
      cur = context->active_head;
      while (cur) {
         cur = cur->next;
         ++count;
      }
      cur = context->free_head;
      while (cur) {
         cur = cur->next;
         ++count;
      }
      STBRP_ASSERT(count == context->num_nodes+2);
   }
#endif

   return res;
}

static int STBRP__CDECL rect_height_compare(const void *a, const void *b)
{
   const stbrp_rect *p = (const stbrp_rect *) a;
   const stbrp_rect *q = (const stbrp_rect *) b;
   if (p->h > q->h)
      return -1;
   if (p->h < q->h)
      return  1;
   return (p->w > q->w) ? -1 : (p->w < q->w);
}

static int STBRP__CDECL rect_original_order(const void *a, const void *b)
{
   const stbrp_rect *p = (const stbrp_rect *) a;
   const stbrp_rect *q = (const stbrp_rect *) b;
   return (p->was_packed < q->was_packed) ? -1 : (p->was_packed > q->was_packed);
}

STBRP_DEF int stbrp_pack_rects(stbrp_context *context, stbrp_rect *rects, int num_rects)
{
   int i, all_rects_packed = 1;

   for (i=0; i < num_rects; ++i) {
      rects[i].was_packed = i;
   }

   STBRP_SORT(rects, num_rects, sizeof(rects[0]), rect_height_compare);

   for (i=0; i < num_rects; ++i) {
      if (rects[i].w == 0 || rects[i].h == 0) {
         rects[i].x = rects[i].y = 0;
      } else {
         stbrp__findresult fr = stbrp__skyline_pack_rectangle(context, rects[i].w, rects[i].h);
         if (fr.prev_link) {
            rects[i].x = (stbrp_coord) fr.x;
            rects[i].y = (stbrp_coord) fr.y;
         } else {
            rects[i].x = rects[i].y = STBRP__MAXVAL;
         }
      }
   }

   STBRP_SORT(rects, num_rects, sizeof(rects[0]), rect_original_order);

   for (i=0; i < num_rects; ++i) {
      rects[i].was_packed = !(rects[i].x == STBRP__MAXVAL && rects[i].y == STBRP__MAXVAL);
      if (!rects[i].was_packed)
         all_rects_packed = 0;
   }

   return all_rects_packed;
}
#endif

#if 0
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

unsigned char ttf_buffer[1<<20];
unsigned char temp_bitmap[512*512];

stbtt_bakedchar cdata[96];
GLuint ftex;

void my_stbtt_initfont(void)
{
   fread(ttf_buffer, 1, 1<<20, fopen("c:/windows/fonts/times.ttf", "rb"));
   stbtt_BakeFontBitmap(ttf_buffer,0, 32.0, temp_bitmap,512,512, 32,96, cdata);

   glGenTextures(1, &ftex);
   glBindTexture(GL_TEXTURE_2D, ftex);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void my_stbtt_print(float x, float y, char *text)
{

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, ftex);
   glBegin(GL_QUADS);
   while (*text) {
      if (*text >= 32 && *text < 128) {
         stbtt_aligned_quad q;
         stbtt_GetBakedQuad(cdata, 512,512, *text-32, &x,&y,&q,1);
         glTexCoord2f(q.s0,q.t0); glVertex2f(q.x0,q.y0);
         glTexCoord2f(q.s1,q.t0); glVertex2f(q.x1,q.y0);
         glTexCoord2f(q.s1,q.t1); glVertex2f(q.x1,q.y1);
         glTexCoord2f(q.s0,q.t1); glVertex2f(q.x0,q.y1);
      }
      ++text;
   }
   glEnd();
}
#endif

#if 0
#include <stdio.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

char ttf_buffer[1<<25];

int main(int argc, char **argv)
{
   stbtt_fontinfo font;
   unsigned char *bitmap;
   int w,h,i,j,c = (argc > 1 ? atoi(argv[1]) : 'a'), s = (argc > 2 ? atoi(argv[2]) : 20);

   fread(ttf_buffer, 1, 1<<25, fopen(argc > 3 ? argv[3] : "c:/windows/fonts/arialbd.ttf", "rb"));

   stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer,0));
   bitmap = stbtt_GetCodepointBitmap(&font, 0,stbtt_ScaleForPixelHeight(&font, s), c, &w, &h, 0,0);

   for (j=0; j < h; ++j) {
      for (i=0; i < w; ++i)
         putchar(" .:ioVM@"[bitmap[j*w+i]>>5]);
      putchar('\n');
   }
   return 0;
}
#endif

#if 0
char buffer[24<<20];
unsigned char screen[20][79];

int main(int arg, char **argv)
{
   stbtt_fontinfo font;
   int i,j,ascent,baseline,ch=0;
   float scale, xpos=2;
   char *text = "Heljo World!";

   fread(buffer, 1, 1000000, fopen("c:/windows/fonts/arialbd.ttf", "rb"));
   stbtt_InitFont(&font, buffer, 0);

   scale = stbtt_ScaleForPixelHeight(&font, 15);
   stbtt_GetFontVMetrics(&font, &ascent,0,0);
   baseline = (int) (ascent*scale);

   while (text[ch]) {
      int advance,lsb,x0,y0,x1,y1;
      float x_shift = xpos - (float) floor(xpos);
      stbtt_GetCodepointHMetrics(&font, text[ch], &advance, &lsb);
      stbtt_GetCodepointBitmapBoxSubpixel(&font, text[ch], scale,scale,x_shift,0, &x0,&y0,&x1,&y1);
      stbtt_MakeCodepointBitmapSubpixel(&font, &screen[baseline + y0][(int) xpos + x0], x1-x0,y1-y0, 79, scale,scale,x_shift,0, text[ch]);

      xpos += (advance * scale);
      if (text[ch+1])
         xpos += scale*stbtt_GetCodepointKernAdvance(&font, text[ch],text[ch+1]);
      ++ch;
   }

   for (j=0; j < 20; ++j) {
      for (i=0; i < 78; ++i)
         putchar(" .:ioVM@"[screen[j][i]>>5]);
      putchar('\n');
   }

   return 0;
}
#endif

#ifdef STB_TRUETYPE_IMPLEMENTATION

   #ifndef stbtt_uint8
   typedef unsigned char   stbtt_uint8;
   typedef signed   char   stbtt_int8;
   typedef unsigned short  stbtt_uint16;
   typedef signed   short  stbtt_int16;
   typedef unsigned int    stbtt_uint32;
   typedef signed   int    stbtt_int32;
   #endif

   typedef char stbtt__check_size32[sizeof(stbtt_int32)==4 ? 1 : -1];
   typedef char stbtt__check_size16[sizeof(stbtt_int16)==2 ? 1 : -1];

   #ifndef STBTT_ifloor
   #include <math.h>
   #define STBTT_ifloor(x)   ((int) floor(x))
   #define STBTT_iceil(x)    ((int) ceil(x))
   #endif

   #ifndef STBTT_sqrt
   #include <math.h>
   #define STBTT_sqrt(x)      sqrt(x)
   #define STBTT_pow(x,y)     pow(x,y)
   #endif

   #ifndef STBTT_fmod
   #include <math.h>
   #define STBTT_fmod(x,y)    fmod(x,y)
   #endif

   #ifndef STBTT_cos
   #include <math.h>
   #define STBTT_cos(x)       cos(x)
   #define STBTT_acos(x)      acos(x)
   #endif

   #ifndef STBTT_fabs
   #include <math.h>
   #define STBTT_fabs(x)      fabs(x)
   #endif

   #ifndef STBTT_malloc
   #include <stdlib.h>
   #define STBTT_malloc(x,u)  ((void)(u),malloc(x))
   #define STBTT_free(x,u)    ((void)(u),free(x))
   #endif

   #ifndef STBTT_assert
   #include <assert.h>
   #define STBTT_assert(x)    assert(x)
   #endif

   #ifndef STBTT_strlen
   #include <string.h>
   #define STBTT_strlen(x)    strlen(x)
   #endif

   #ifndef STBTT_memcpy
   #include <string.h>
   #define STBTT_memcpy       memcpy
   #define STBTT_memset       memset
   #endif
#endif

#ifndef __STB_INCLUDE_STB_TRUETYPE_H__
#define __STB_INCLUDE_STB_TRUETYPE_H__

#ifdef STBTT_STATIC
#define STBTT_DEF static
#else
#define STBTT_DEF extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
   unsigned char *data;
   int cursor;
   int size;
} stbtt__buf;

typedef struct
{
   unsigned short x0,y0,x1,y1;
   float xoff,yoff,xadvance;
} stbtt_bakedchar;

STBTT_DEF int stbtt_BakeFontBitmap(const unsigned char *data, int offset,
                                float pixel_height,
                                unsigned char *pixels, int pw, int ph,
                                int first_char, int num_chars,
                                stbtt_bakedchar *chardata);

typedef struct
{
   float x0,y0,s0,t0;
   float x1,y1,s1,t1;
} stbtt_aligned_quad;

STBTT_DEF void stbtt_GetBakedQuad(const stbtt_bakedchar *chardata, int pw, int ph,
                               int char_index,
                               float *xpos, float *ypos,
                               stbtt_aligned_quad *q,
                               int opengl_fillrule);

STBTT_DEF void stbtt_GetScaledFontVMetrics(const unsigned char *fontdata, int index, float size, float *ascent, float *descent, float *lineGap);

typedef struct
{
   unsigned short x0,y0,x1,y1;
   float xoff,yoff,xadvance;
   float xoff2,yoff2;
} stbtt_packedchar;

typedef struct stbtt_pack_context stbtt_pack_context;
typedef struct stbtt_fontinfo stbtt_fontinfo;
#ifndef STB_RECT_PACK_VERSION
typedef struct stbrp_rect stbrp_rect;
#endif

STBTT_DEF int  stbtt_PackBegin(stbtt_pack_context *spc, unsigned char *pixels, int width, int height, int stride_in_bytes, int padding, void *alloc_context);

STBTT_DEF void stbtt_PackEnd  (stbtt_pack_context *spc);

#define STBTT_POINT_SIZE(x)   (-(x))

STBTT_DEF int  stbtt_PackFontRange(stbtt_pack_context *spc, const unsigned char *fontdata, int font_index, float font_size,
                                int first_unicode_char_in_range, int num_chars_in_range, stbtt_packedchar *chardata_for_range);

typedef struct
{
   float font_size;
   int first_unicode_codepoint_in_range;
   int *array_of_unicode_codepoints;
   int num_chars;
   stbtt_packedchar *chardata_for_range;
   unsigned char h_oversample, v_oversample;
} stbtt_pack_range;

STBTT_DEF int  stbtt_PackFontRanges(stbtt_pack_context *spc, const unsigned char *fontdata, int font_index, stbtt_pack_range *ranges, int num_ranges);

STBTT_DEF void stbtt_PackSetOversampling(stbtt_pack_context *spc, unsigned int h_oversample, unsigned int v_oversample);

STBTT_DEF void stbtt_PackSetSkipMissingCodepoints(stbtt_pack_context *spc, int skip);

STBTT_DEF void stbtt_GetPackedQuad(const stbtt_packedchar *chardata, int pw, int ph,
                               int char_index,
                               float *xpos, float *ypos,
                               stbtt_aligned_quad *q,
                               int align_to_integer);

STBTT_DEF int  stbtt_PackFontRangesGatherRects(stbtt_pack_context *spc, const stbtt_fontinfo *info, stbtt_pack_range *ranges, int num_ranges, stbrp_rect *rects);
STBTT_DEF void stbtt_PackFontRangesPackRects(stbtt_pack_context *spc, stbrp_rect *rects, int num_rects);
STBTT_DEF int  stbtt_PackFontRangesRenderIntoRects(stbtt_pack_context *spc, const stbtt_fontinfo *info, stbtt_pack_range *ranges, int num_ranges, stbrp_rect *rects);

struct stbtt_pack_context {
   void *user_allocator_context;
   void *pack_info;
   int   width;
   int   height;
   int   stride_in_bytes;
   int   padding;
   int   skip_missing;
   unsigned int   h_oversample, v_oversample;
   unsigned char *pixels;
   void  *nodes;
};

STBTT_DEF int stbtt_GetNumberOfFonts(const unsigned char *data);

STBTT_DEF int stbtt_GetFontOffsetForIndex(const unsigned char *data, int index);

struct stbtt_fontinfo
{
   void           * userdata;
   unsigned char  * data;
   int              fontstart;

   int numGlyphs;

   int loca,head,glyf,hhea,hmtx,kern,gpos,svg;
   int index_map;
   int indexToLocFormat;

   stbtt__buf cff;
   stbtt__buf charstrings;
   stbtt__buf gsubrs;
   stbtt__buf subrs;
   stbtt__buf fontdicts;
   stbtt__buf fdselect;
};

STBTT_DEF int stbtt_InitFont(stbtt_fontinfo *info, const unsigned char *data, int offset);

STBTT_DEF int stbtt_FindGlyphIndex(const stbtt_fontinfo *info, int unicode_codepoint);

STBTT_DEF float stbtt_ScaleForPixelHeight(const stbtt_fontinfo *info, float pixels);

STBTT_DEF float stbtt_ScaleForMappingEmToPixels(const stbtt_fontinfo *info, float pixels);

STBTT_DEF void stbtt_GetFontVMetrics(const stbtt_fontinfo *info, int *ascent, int *descent, int *lineGap);

STBTT_DEF int  stbtt_GetFontVMetricsOS2(const stbtt_fontinfo *info, int *typoAscent, int *typoDescent, int *typoLineGap);

STBTT_DEF void stbtt_GetFontBoundingBox(const stbtt_fontinfo *info, int *x0, int *y0, int *x1, int *y1);

STBTT_DEF void stbtt_GetCodepointHMetrics(const stbtt_fontinfo *info, int codepoint, int *advanceWidth, int *leftSideBearing);

STBTT_DEF int  stbtt_GetCodepointKernAdvance(const stbtt_fontinfo *info, int ch1, int ch2);

STBTT_DEF int stbtt_GetCodepointBox(const stbtt_fontinfo *info, int codepoint, int *x0, int *y0, int *x1, int *y1);

STBTT_DEF void stbtt_GetGlyphHMetrics(const stbtt_fontinfo *info, int glyph_index, int *advanceWidth, int *leftSideBearing);
STBTT_DEF int  stbtt_GetGlyphKernAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2);
STBTT_DEF int  stbtt_GetGlyphBox(const stbtt_fontinfo *info, int glyph_index, int *x0, int *y0, int *x1, int *y1);

typedef struct stbtt_kerningentry
{
   int glyph1;
   int glyph2;
   int advance;
} stbtt_kerningentry;

STBTT_DEF int  stbtt_GetKerningTableLength(const stbtt_fontinfo *info);
STBTT_DEF int  stbtt_GetKerningTable(const stbtt_fontinfo *info, stbtt_kerningentry* table, int table_length);

#ifndef STBTT_vmove
   enum {
      STBTT_vmove=1,
      STBTT_vline,
      STBTT_vcurve,
      STBTT_vcubic
   };
#endif

#ifndef stbtt_vertex

   #define stbtt_vertex_type short
   typedef struct
   {
      stbtt_vertex_type x,y,cx,cy,cx1,cy1;
      unsigned char type,padding;
   } stbtt_vertex;
#endif

STBTT_DEF int stbtt_IsGlyphEmpty(const stbtt_fontinfo *info, int glyph_index);

STBTT_DEF int stbtt_GetCodepointShape(const stbtt_fontinfo *info, int unicode_codepoint, stbtt_vertex **vertices);
STBTT_DEF int stbtt_GetGlyphShape(const stbtt_fontinfo *info, int glyph_index, stbtt_vertex **vertices);

STBTT_DEF void stbtt_FreeShape(const stbtt_fontinfo *info, stbtt_vertex *vertices);

STBTT_DEF unsigned char *stbtt_FindSVGDoc(const stbtt_fontinfo *info, int gl);
STBTT_DEF int stbtt_GetCodepointSVG(const stbtt_fontinfo *info, int unicode_codepoint, const char **svg);
STBTT_DEF int stbtt_GetGlyphSVG(const stbtt_fontinfo *info, int gl, const char **svg);

STBTT_DEF void stbtt_FreeBitmap(unsigned char *bitmap, void *userdata);

STBTT_DEF unsigned char *stbtt_GetCodepointBitmap(const stbtt_fontinfo *info, float scale_x, float scale_y, int codepoint, int *width, int *height, int *xoff, int *yoff);

STBTT_DEF unsigned char *stbtt_GetCodepointBitmapSubpixel(const stbtt_fontinfo *info, float scale_x, float scale_y, float shift_x, float shift_y, int codepoint, int *width, int *height, int *xoff, int *yoff);

STBTT_DEF void stbtt_MakeCodepointBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint);

STBTT_DEF void stbtt_MakeCodepointBitmapSubpixel(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int codepoint);

STBTT_DEF void stbtt_MakeCodepointBitmapSubpixelPrefilter(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int oversample_x, int oversample_y, float *sub_x, float *sub_y, int codepoint);

STBTT_DEF void stbtt_GetCodepointBitmapBox(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1);

STBTT_DEF void stbtt_GetCodepointBitmapBoxSubpixel(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1);

STBTT_DEF unsigned char *stbtt_GetGlyphBitmap(const stbtt_fontinfo *info, float scale_x, float scale_y, int glyph, int *width, int *height, int *xoff, int *yoff);
STBTT_DEF unsigned char *stbtt_GetGlyphBitmapSubpixel(const stbtt_fontinfo *info, float scale_x, float scale_y, float shift_x, float shift_y, int glyph, int *width, int *height, int *xoff, int *yoff);
STBTT_DEF void stbtt_MakeGlyphBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int glyph);
STBTT_DEF void stbtt_MakeGlyphBitmapSubpixel(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int glyph);
STBTT_DEF void stbtt_MakeGlyphBitmapSubpixelPrefilter(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int oversample_x, int oversample_y, float *sub_x, float *sub_y, int glyph);
STBTT_DEF void stbtt_GetGlyphBitmapBox(const stbtt_fontinfo *font, int glyph, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1);
STBTT_DEF void stbtt_GetGlyphBitmapBoxSubpixel(const stbtt_fontinfo *font, int glyph, float scale_x, float scale_y,float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1);

typedef struct
{
   int w,h,stride;
   unsigned char *pixels;
} stbtt__bitmap;

STBTT_DEF void stbtt_Rasterize(stbtt__bitmap *result,
                               float flatness_in_pixels,
                               stbtt_vertex *vertices,
                               int num_verts,
                               float scale_x, float scale_y,
                               float shift_x, float shift_y,
                               int x_off, int y_off,
                               int invert,
                               void *userdata);

STBTT_DEF void stbtt_FreeSDF(unsigned char *bitmap, void *userdata);

STBTT_DEF unsigned char * stbtt_GetGlyphSDF(const stbtt_fontinfo *info, float scale, int glyph, int padding, unsigned char onedge_value, float pixel_dist_scale, int *width, int *height, int *xoff, int *yoff);
STBTT_DEF unsigned char * stbtt_GetCodepointSDF(const stbtt_fontinfo *info, float scale, int codepoint, int padding, unsigned char onedge_value, float pixel_dist_scale, int *width, int *height, int *xoff, int *yoff);

STBTT_DEF int stbtt_FindMatchingFont(const unsigned char *fontdata, const char *name, int flags);

#define STBTT_MACSTYLE_DONTCARE     0
#define STBTT_MACSTYLE_BOLD         1
#define STBTT_MACSTYLE_ITALIC       2
#define STBTT_MACSTYLE_UNDERSCORE   4
#define STBTT_MACSTYLE_NONE         8

STBTT_DEF int stbtt_CompareUTF8toUTF16_bigendian(const char *s1, int len1, const char *s2, int len2);

STBTT_DEF const char *stbtt_GetFontNameString(const stbtt_fontinfo *font, int *length, int platformID, int encodingID, int languageID, int nameID);

enum {
   STBTT_PLATFORM_ID_UNICODE   =0,
   STBTT_PLATFORM_ID_MAC       =1,
   STBTT_PLATFORM_ID_ISO       =2,
   STBTT_PLATFORM_ID_MICROSOFT =3
};

enum {
   STBTT_UNICODE_EID_UNICODE_1_0    =0,
   STBTT_UNICODE_EID_UNICODE_1_1    =1,
   STBTT_UNICODE_EID_ISO_10646      =2,
   STBTT_UNICODE_EID_UNICODE_2_0_BMP=3,
   STBTT_UNICODE_EID_UNICODE_2_0_FULL=4
};

enum {
   STBTT_MS_EID_SYMBOL        =0,
   STBTT_MS_EID_UNICODE_BMP   =1,
   STBTT_MS_EID_SHIFTJIS      =2,
   STBTT_MS_EID_UNICODE_FULL  =10
};

enum {
   STBTT_MAC_EID_ROMAN        =0,   STBTT_MAC_EID_ARABIC       =4,
   STBTT_MAC_EID_JAPANESE     =1,   STBTT_MAC_EID_HEBREW       =5,
   STBTT_MAC_EID_CHINESE_TRAD =2,   STBTT_MAC_EID_GREEK        =6,
   STBTT_MAC_EID_KOREAN       =3,   STBTT_MAC_EID_RUSSIAN      =7
};

enum {

   STBTT_MS_LANG_ENGLISH     =0x0409,   STBTT_MS_LANG_ITALIAN     =0x0410,
   STBTT_MS_LANG_CHINESE     =0x0804,   STBTT_MS_LANG_JAPANESE    =0x0411,
   STBTT_MS_LANG_DUTCH       =0x0413,   STBTT_MS_LANG_KOREAN      =0x0412,
   STBTT_MS_LANG_FRENCH      =0x040c,   STBTT_MS_LANG_RUSSIAN     =0x0419,
   STBTT_MS_LANG_GERMAN      =0x0407,   STBTT_MS_LANG_SPANISH     =0x0409,
   STBTT_MS_LANG_HEBREW      =0x040d,   STBTT_MS_LANG_SWEDISH     =0x041D
};

enum {
   STBTT_MAC_LANG_ENGLISH      =0 ,   STBTT_MAC_LANG_JAPANESE     =11,
   STBTT_MAC_LANG_ARABIC       =12,   STBTT_MAC_LANG_KOREAN       =23,
   STBTT_MAC_LANG_DUTCH        =4 ,   STBTT_MAC_LANG_RUSSIAN      =32,
   STBTT_MAC_LANG_FRENCH       =1 ,   STBTT_MAC_LANG_SPANISH      =6 ,
   STBTT_MAC_LANG_GERMAN       =2 ,   STBTT_MAC_LANG_SWEDISH      =5 ,
   STBTT_MAC_LANG_HEBREW       =10,   STBTT_MAC_LANG_CHINESE_SIMPLIFIED =33,
   STBTT_MAC_LANG_ITALIAN      =3 ,   STBTT_MAC_LANG_CHINESE_TRAD =19
};

#ifdef __cplusplus
}
#endif

#endif

#ifdef STB_TRUETYPE_IMPLEMENTATION

#ifndef STBTT_MAX_OVERSAMPLE
#define STBTT_MAX_OVERSAMPLE   8
#endif

#if STBTT_MAX_OVERSAMPLE > 255
#error "STBTT_MAX_OVERSAMPLE cannot be > 255"
#endif

typedef int stbtt__test_oversample_pow2[(STBTT_MAX_OVERSAMPLE & (STBTT_MAX_OVERSAMPLE-1)) == 0 ? 1 : -1];

#ifndef STBTT_RASTERIZER_VERSION
#define STBTT_RASTERIZER_VERSION 2
#endif

#ifdef _MSC_VER
#define STBTT__NOTUSED(v)  (void)(v)
#else
#define STBTT__NOTUSED(v)  (void)sizeof(v)
#endif

static stbtt_uint8 stbtt__buf_get8(stbtt__buf *b)
{
   if (b->cursor >= b->size)
      return 0;
   return b->data[b->cursor++];
}

static stbtt_uint8 stbtt__buf_peek8(stbtt__buf *b)
{
   if (b->cursor >= b->size)
      return 0;
   return b->data[b->cursor];
}

static void stbtt__buf_seek(stbtt__buf *b, int o)
{
   STBTT_assert(!(o > b->size || o < 0));
   b->cursor = (o > b->size || o < 0) ? b->size : o;
}

static void stbtt__buf_skip(stbtt__buf *b, int o)
{
   stbtt__buf_seek(b, b->cursor + o);
}

static stbtt_uint32 stbtt__buf_get(stbtt__buf *b, int n)
{
   stbtt_uint32 v = 0;
   int i;
   STBTT_assert(n >= 1 && n <= 4);
   for (i = 0; i < n; i++)
      v = (v << 8) | stbtt__buf_get8(b);
   return v;
}

static stbtt__buf stbtt__new_buf(const void *p, size_t size)
{
   stbtt__buf r;
   STBTT_assert(size < 0x40000000);
   r.data = (stbtt_uint8*) p;
   r.size = (int) size;
   r.cursor = 0;
   return r;
}

#define stbtt__buf_get16(b)  stbtt__buf_get((b), 2)
#define stbtt__buf_get32(b)  stbtt__buf_get((b), 4)

static stbtt__buf stbtt__buf_range(const stbtt__buf *b, int o, int s)
{
   stbtt__buf r = stbtt__new_buf(NULL, 0);
   if (o < 0 || s < 0 || o > b->size || s > b->size - o) return r;
   r.data = b->data + o;
   r.size = s;
   return r;
}

static stbtt__buf stbtt__cff_get_index(stbtt__buf *b)
{
   int count, start, offsize;
   start = b->cursor;
   count = stbtt__buf_get16(b);
   if (count) {
      offsize = stbtt__buf_get8(b);
      STBTT_assert(offsize >= 1 && offsize <= 4);
      stbtt__buf_skip(b, offsize * count);
      stbtt__buf_skip(b, stbtt__buf_get(b, offsize) - 1);
   }
   return stbtt__buf_range(b, start, b->cursor - start);
}

static stbtt_uint32 stbtt__cff_int(stbtt__buf *b)
{
   int b0 = stbtt__buf_get8(b);
   if (b0 >= 32 && b0 <= 246)       return b0 - 139;
   else if (b0 >= 247 && b0 <= 250) return (b0 - 247)*256 + stbtt__buf_get8(b) + 108;
   else if (b0 >= 251 && b0 <= 254) return -(b0 - 251)*256 - stbtt__buf_get8(b) - 108;
   else if (b0 == 28)               return stbtt__buf_get16(b);
   else if (b0 == 29)               return stbtt__buf_get32(b);
   STBTT_assert(0);
   return 0;
}

static void stbtt__cff_skip_operand(stbtt__buf *b) {
   int v, b0 = stbtt__buf_peek8(b);
   STBTT_assert(b0 >= 28);
   if (b0 == 30) {
      stbtt__buf_skip(b, 1);
      while (b->cursor < b->size) {
         v = stbtt__buf_get8(b);
         if ((v & 0xF) == 0xF || (v >> 4) == 0xF)
            break;
      }
   } else {
      stbtt__cff_int(b);
   }
}

static stbtt__buf stbtt__dict_get(stbtt__buf *b, int key)
{
   stbtt__buf_seek(b, 0);
   while (b->cursor < b->size) {
      int start = b->cursor, end, op;
      while (stbtt__buf_peek8(b) >= 28)
         stbtt__cff_skip_operand(b);
      end = b->cursor;
      op = stbtt__buf_get8(b);
      if (op == 12)  op = stbtt__buf_get8(b) | 0x100;
      if (op == key) return stbtt__buf_range(b, start, end-start);
   }
   return stbtt__buf_range(b, 0, 0);
}

static void stbtt__dict_get_ints(stbtt__buf *b, int key, int outcount, stbtt_uint32 *out)
{
   int i;
   stbtt__buf operands = stbtt__dict_get(b, key);
   for (i = 0; i < outcount && operands.cursor < operands.size; i++)
      out[i] = stbtt__cff_int(&operands);
}

static int stbtt__cff_index_count(stbtt__buf *b)
{
   stbtt__buf_seek(b, 0);
   return stbtt__buf_get16(b);
}

static stbtt__buf stbtt__cff_index_get(stbtt__buf b, int i)
{
   int count, offsize, start, end;
   stbtt__buf_seek(&b, 0);
   count = stbtt__buf_get16(&b);
   offsize = stbtt__buf_get8(&b);
   STBTT_assert(i >= 0 && i < count);
   STBTT_assert(offsize >= 1 && offsize <= 4);
   stbtt__buf_skip(&b, i*offsize);
   start = stbtt__buf_get(&b, offsize);
   end = stbtt__buf_get(&b, offsize);
   return stbtt__buf_range(&b, 2+(count+1)*offsize+start, end - start);
}

#define ttBYTE(p)     (* (stbtt_uint8 *) (p))
#define ttCHAR(p)     (* (stbtt_int8 *) (p))
#define ttFixed(p)    ttLONG(p)

static stbtt_uint16 ttUSHORT(stbtt_uint8 *p) { return p[0]*256 + p[1]; }
static stbtt_int16 ttSHORT(stbtt_uint8 *p)   { return p[0]*256 + p[1]; }
static stbtt_uint32 ttULONG(stbtt_uint8 *p)  { return (p[0]<<24) + (p[1]<<16) + (p[2]<<8) + p[3]; }
static stbtt_int32 ttLONG(stbtt_uint8 *p)    { return (p[0]<<24) + (p[1]<<16) + (p[2]<<8) + p[3]; }

#define stbtt_tag4(p,c0,c1,c2,c3) ((p)[0] == (c0) && (p)[1] == (c1) && (p)[2] == (c2) && (p)[3] == (c3))
#define stbtt_tag(p,str)           stbtt_tag4(p,str[0],str[1],str[2],str[3])

static int stbtt__isfont(stbtt_uint8 *font)
{

   if (stbtt_tag4(font, '1',0,0,0))  return 1;
   if (stbtt_tag(font, "typ1"))   return 1;
   if (stbtt_tag(font, "OTTO"))   return 1;
   if (stbtt_tag4(font, 0,1,0,0)) return 1;
   if (stbtt_tag(font, "true"))   return 1;
   return 0;
}

static stbtt_uint32 stbtt__find_table(stbtt_uint8 *data, stbtt_uint32 fontstart, const char *tag)
{
   stbtt_int32 num_tables = ttUSHORT(data+fontstart+4);
   stbtt_uint32 tabledir = fontstart + 12;
   stbtt_int32 i;
   for (i=0; i < num_tables; ++i) {
      stbtt_uint32 loc = tabledir + 16*i;
      if (stbtt_tag(data+loc+0, tag))
         return ttULONG(data+loc+8);
   }
   return 0;
}

static int stbtt_GetFontOffsetForIndex_internal(unsigned char *font_collection, int index)
{

   if (stbtt__isfont(font_collection))
      return index == 0 ? 0 : -1;

   if (stbtt_tag(font_collection, "ttcf")) {

      if (ttULONG(font_collection+4) == 0x00010000 || ttULONG(font_collection+4) == 0x00020000) {
         stbtt_int32 n = ttLONG(font_collection+8);
         if (index >= n)
            return -1;
         return ttULONG(font_collection+12+index*4);
      }
   }
   return -1;
}

static int stbtt_GetNumberOfFonts_internal(unsigned char *font_collection)
{

   if (stbtt__isfont(font_collection))
      return 1;

   if (stbtt_tag(font_collection, "ttcf")) {

      if (ttULONG(font_collection+4) == 0x00010000 || ttULONG(font_collection+4) == 0x00020000) {
         return ttLONG(font_collection+8);
      }
   }
   return 0;
}

static stbtt__buf stbtt__get_subrs(stbtt__buf cff, stbtt__buf fontdict)
{
   stbtt_uint32 subrsoff = 0, private_loc[2] = { 0, 0 };
   stbtt__buf pdict;
   stbtt__dict_get_ints(&fontdict, 18, 2, private_loc);
   if (!private_loc[1] || !private_loc[0]) return stbtt__new_buf(NULL, 0);
   pdict = stbtt__buf_range(&cff, private_loc[1], private_loc[0]);
   stbtt__dict_get_ints(&pdict, 19, 1, &subrsoff);
   if (!subrsoff) return stbtt__new_buf(NULL, 0);
   stbtt__buf_seek(&cff, private_loc[1]+subrsoff);
   return stbtt__cff_get_index(&cff);
}

static int stbtt__get_svg(stbtt_fontinfo *info)
{
   stbtt_uint32 t;
   if (info->svg < 0) {
      t = stbtt__find_table(info->data, info->fontstart, "SVG ");
      if (t) {
         stbtt_uint32 offset = ttULONG(info->data + t + 2);
         info->svg = t + offset;
      } else {
         info->svg = 0;
      }
   }
   return info->svg;
}

static int stbtt_InitFont_internal(stbtt_fontinfo *info, unsigned char *data, int fontstart)
{
   stbtt_uint32 cmap, t;
   stbtt_int32 i,numTables;

   info->data = data;
   info->fontstart = fontstart;
   info->cff = stbtt__new_buf(NULL, 0);

   cmap = stbtt__find_table(data, fontstart, "cmap");
   info->loca = stbtt__find_table(data, fontstart, "loca");
   info->head = stbtt__find_table(data, fontstart, "head");
   info->glyf = stbtt__find_table(data, fontstart, "glyf");
   info->hhea = stbtt__find_table(data, fontstart, "hhea");
   info->hmtx = stbtt__find_table(data, fontstart, "hmtx");
   info->kern = stbtt__find_table(data, fontstart, "kern");
   info->gpos = stbtt__find_table(data, fontstart, "GPOS");

   if (!cmap || !info->head || !info->hhea || !info->hmtx)
      return 0;
   if (info->glyf) {

      if (!info->loca) return 0;
   } else {

      stbtt__buf b, topdict, topdictidx;
      stbtt_uint32 cstype = 2, charstrings = 0, fdarrayoff = 0, fdselectoff = 0;
      stbtt_uint32 cff;

      cff = stbtt__find_table(data, fontstart, "CFF ");
      if (!cff) return 0;

      info->fontdicts = stbtt__new_buf(NULL, 0);
      info->fdselect = stbtt__new_buf(NULL, 0);

      info->cff = stbtt__new_buf(data+cff, 512*1024*1024);
      b = info->cff;

      stbtt__buf_skip(&b, 2);
      stbtt__buf_seek(&b, stbtt__buf_get8(&b));

      stbtt__cff_get_index(&b);
      topdictidx = stbtt__cff_get_index(&b);
      topdict = stbtt__cff_index_get(topdictidx, 0);
      stbtt__cff_get_index(&b);
      info->gsubrs = stbtt__cff_get_index(&b);

      stbtt__dict_get_ints(&topdict, 17, 1, &charstrings);
      stbtt__dict_get_ints(&topdict, 0x100 | 6, 1, &cstype);
      stbtt__dict_get_ints(&topdict, 0x100 | 36, 1, &fdarrayoff);
      stbtt__dict_get_ints(&topdict, 0x100 | 37, 1, &fdselectoff);
      info->subrs = stbtt__get_subrs(b, topdict);

      if (cstype != 2) return 0;
      if (charstrings == 0) return 0;

      if (fdarrayoff) {

         if (!fdselectoff) return 0;
         stbtt__buf_seek(&b, fdarrayoff);
         info->fontdicts = stbtt__cff_get_index(&b);
         info->fdselect = stbtt__buf_range(&b, fdselectoff, b.size-fdselectoff);
      }

      stbtt__buf_seek(&b, charstrings);
      info->charstrings = stbtt__cff_get_index(&b);
   }

   t = stbtt__find_table(data, fontstart, "maxp");
   if (t)
      info->numGlyphs = ttUSHORT(data+t+4);
   else
      info->numGlyphs = 0xffff;

   info->svg = -1;

   numTables = ttUSHORT(data + cmap + 2);
   info->index_map = 0;
   for (i=0; i < numTables; ++i) {
      stbtt_uint32 encoding_record = cmap + 4 + 8 * i;

      switch(ttUSHORT(data+encoding_record)) {
         case STBTT_PLATFORM_ID_MICROSOFT:
            switch (ttUSHORT(data+encoding_record+2)) {
               case STBTT_MS_EID_UNICODE_BMP:
               case STBTT_MS_EID_UNICODE_FULL:

                  info->index_map = cmap + ttULONG(data+encoding_record+4);
                  break;
            }
            break;
        case STBTT_PLATFORM_ID_UNICODE:

            info->index_map = cmap + ttULONG(data+encoding_record+4);
            break;
      }
   }
   if (info->index_map == 0)
      return 0;

   info->indexToLocFormat = ttUSHORT(data+info->head + 50);
   return 1;
}

STBTT_DEF int stbtt_FindGlyphIndex(const stbtt_fontinfo *info, int unicode_codepoint)
{
   stbtt_uint8 *data = info->data;
   stbtt_uint32 index_map = info->index_map;

   stbtt_uint16 format = ttUSHORT(data + index_map + 0);
   if (format == 0) {
      stbtt_int32 bytes = ttUSHORT(data + index_map + 2);
      if (unicode_codepoint < bytes-6)
         return ttBYTE(data + index_map + 6 + unicode_codepoint);
      return 0;
   } else if (format == 6) {
      stbtt_uint32 first = ttUSHORT(data + index_map + 6);
      stbtt_uint32 count = ttUSHORT(data + index_map + 8);
      if ((stbtt_uint32) unicode_codepoint >= first && (stbtt_uint32) unicode_codepoint < first+count)
         return ttUSHORT(data + index_map + 10 + (unicode_codepoint - first)*2);
      return 0;
   } else if (format == 2) {
      STBTT_assert(0);
      return 0;
   } else if (format == 4) {
      stbtt_uint16 segcount = ttUSHORT(data+index_map+6) >> 1;
      stbtt_uint16 searchRange = ttUSHORT(data+index_map+8) >> 1;
      stbtt_uint16 entrySelector = ttUSHORT(data+index_map+10);
      stbtt_uint16 rangeShift = ttUSHORT(data+index_map+12) >> 1;

      stbtt_uint32 endCount = index_map + 14;
      stbtt_uint32 search = endCount;

      if (unicode_codepoint > 0xffff)
         return 0;

      if (unicode_codepoint >= ttUSHORT(data + search + rangeShift*2))
         search += rangeShift*2;

      search -= 2;
      while (entrySelector) {
         stbtt_uint16 end;
         searchRange >>= 1;
         end = ttUSHORT(data + search + searchRange*2);
         if (unicode_codepoint > end)
            search += searchRange*2;
         --entrySelector;
      }
      search += 2;

      {
         stbtt_uint16 offset, start, last;
         stbtt_uint16 item = (stbtt_uint16) ((search - endCount) >> 1);

         start = ttUSHORT(data + index_map + 14 + segcount*2 + 2 + 2*item);
         last = ttUSHORT(data + endCount + 2*item);
         if (unicode_codepoint < start || unicode_codepoint > last)
            return 0;

         offset = ttUSHORT(data + index_map + 14 + segcount*6 + 2 + 2*item);
         if (offset == 0)
            return (stbtt_uint16) (unicode_codepoint + ttSHORT(data + index_map + 14 + segcount*4 + 2 + 2*item));

         return ttUSHORT(data + offset + (unicode_codepoint-start)*2 + index_map + 14 + segcount*6 + 2 + 2*item);
      }
   } else if (format == 12 || format == 13) {
      stbtt_uint32 ngroups = ttULONG(data+index_map+12);
      stbtt_int32 low,high;
      low = 0; high = (stbtt_int32)ngroups;

      while (low < high) {
         stbtt_int32 mid = low + ((high-low) >> 1);
         stbtt_uint32 start_char = ttULONG(data+index_map+16+mid*12);
         stbtt_uint32 end_char = ttULONG(data+index_map+16+mid*12+4);
         if ((stbtt_uint32) unicode_codepoint < start_char)
            high = mid;
         else if ((stbtt_uint32) unicode_codepoint > end_char)
            low = mid+1;
         else {
            stbtt_uint32 start_glyph = ttULONG(data+index_map+16+mid*12+8);
            if (format == 12)
               return start_glyph + unicode_codepoint-start_char;
            else
               return start_glyph;
         }
      }
      return 0;
   }

   STBTT_assert(0);
   return 0;
}

STBTT_DEF int stbtt_GetCodepointShape(const stbtt_fontinfo *info, int unicode_codepoint, stbtt_vertex **vertices)
{
   return stbtt_GetGlyphShape(info, stbtt_FindGlyphIndex(info, unicode_codepoint), vertices);
}

static void stbtt_setvertex(stbtt_vertex *v, stbtt_uint8 type, stbtt_int32 x, stbtt_int32 y, stbtt_int32 cx, stbtt_int32 cy)
{
   v->type = type;
   v->x = (stbtt_int16) x;
   v->y = (stbtt_int16) y;
   v->cx = (stbtt_int16) cx;
   v->cy = (stbtt_int16) cy;
}

static int stbtt__GetGlyfOffset(const stbtt_fontinfo *info, int glyph_index)
{
   int g1,g2;

   STBTT_assert(!info->cff.size);

   if (glyph_index >= info->numGlyphs) return -1;
   if (info->indexToLocFormat >= 2)    return -1;

   if (info->indexToLocFormat == 0) {
      g1 = info->glyf + ttUSHORT(info->data + info->loca + glyph_index * 2) * 2;
      g2 = info->glyf + ttUSHORT(info->data + info->loca + glyph_index * 2 + 2) * 2;
   } else {
      g1 = info->glyf + ttULONG (info->data + info->loca + glyph_index * 4);
      g2 = info->glyf + ttULONG (info->data + info->loca + glyph_index * 4 + 4);
   }

   return g1==g2 ? -1 : g1;
}

static int stbtt__GetGlyphInfoT2(const stbtt_fontinfo *info, int glyph_index, int *x0, int *y0, int *x1, int *y1);

STBTT_DEF int stbtt_GetGlyphBox(const stbtt_fontinfo *info, int glyph_index, int *x0, int *y0, int *x1, int *y1)
{
   if (info->cff.size) {
      stbtt__GetGlyphInfoT2(info, glyph_index, x0, y0, x1, y1);
   } else {
      int g = stbtt__GetGlyfOffset(info, glyph_index);
      if (g < 0) return 0;

      if (x0) *x0 = ttSHORT(info->data + g + 2);
      if (y0) *y0 = ttSHORT(info->data + g + 4);
      if (x1) *x1 = ttSHORT(info->data + g + 6);
      if (y1) *y1 = ttSHORT(info->data + g + 8);
   }
   return 1;
}

STBTT_DEF int stbtt_GetCodepointBox(const stbtt_fontinfo *info, int codepoint, int *x0, int *y0, int *x1, int *y1)
{
   return stbtt_GetGlyphBox(info, stbtt_FindGlyphIndex(info,codepoint), x0,y0,x1,y1);
}

STBTT_DEF int stbtt_IsGlyphEmpty(const stbtt_fontinfo *info, int glyph_index)
{
   stbtt_int16 numberOfContours;
   int g;
   if (info->cff.size)
      return stbtt__GetGlyphInfoT2(info, glyph_index, NULL, NULL, NULL, NULL) == 0;
   g = stbtt__GetGlyfOffset(info, glyph_index);
   if (g < 0) return 1;
   numberOfContours = ttSHORT(info->data + g);
   return numberOfContours == 0;
}

static int stbtt__close_shape(stbtt_vertex *vertices, int num_vertices, int was_off, int start_off,
    stbtt_int32 sx, stbtt_int32 sy, stbtt_int32 scx, stbtt_int32 scy, stbtt_int32 cx, stbtt_int32 cy)
{
   if (start_off) {
      if (was_off)
         stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, (cx+scx)>>1, (cy+scy)>>1, cx,cy);
      stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, sx,sy,scx,scy);
   } else {
      if (was_off)
         stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve,sx,sy,cx,cy);
      else
         stbtt_setvertex(&vertices[num_vertices++], STBTT_vline,sx,sy,0,0);
   }
   return num_vertices;
}

static int stbtt__GetGlyphShapeTT(const stbtt_fontinfo *info, int glyph_index, stbtt_vertex **pvertices)
{
   stbtt_int16 numberOfContours;
   stbtt_uint8 *endPtsOfContours;
   stbtt_uint8 *data = info->data;
   stbtt_vertex *vertices=0;
   int num_vertices=0;
   int g = stbtt__GetGlyfOffset(info, glyph_index);

   *pvertices = NULL;

   if (g < 0) return 0;

   numberOfContours = ttSHORT(data + g);

   if (numberOfContours > 0) {
      stbtt_uint8 flags=0,flagcount;
      stbtt_int32 ins, i,j=0,m,n, next_move, was_off=0, off, start_off=0;
      stbtt_int32 x,y,cx,cy,sx,sy, scx,scy;
      stbtt_uint8 *points;
      endPtsOfContours = (data + g + 10);
      ins = ttUSHORT(data + g + 10 + numberOfContours * 2);
      points = data + g + 10 + numberOfContours * 2 + 2 + ins;

      n = 1+ttUSHORT(endPtsOfContours + numberOfContours*2-2);

      m = n + 2*numberOfContours;
      vertices = (stbtt_vertex *) STBTT_malloc(m * sizeof(vertices[0]), info->userdata);
      if (vertices == 0)
         return 0;

      next_move = 0;
      flagcount=0;

      off = m - n;

      for (i=0; i < n; ++i) {
         if (flagcount == 0) {
            flags = *points++;
            if (flags & 8)
               flagcount = *points++;
         } else
            --flagcount;
         vertices[off+i].type = flags;
      }

      x=0;
      for (i=0; i < n; ++i) {
         flags = vertices[off+i].type;
         if (flags & 2) {
            stbtt_int16 dx = *points++;
            x += (flags & 16) ? dx : -dx;
         } else {
            if (!(flags & 16)) {
               x = x + (stbtt_int16) (points[0]*256 + points[1]);
               points += 2;
            }
         }
         vertices[off+i].x = (stbtt_int16) x;
      }

      y=0;
      for (i=0; i < n; ++i) {
         flags = vertices[off+i].type;
         if (flags & 4) {
            stbtt_int16 dy = *points++;
            y += (flags & 32) ? dy : -dy;
         } else {
            if (!(flags & 32)) {
               y = y + (stbtt_int16) (points[0]*256 + points[1]);
               points += 2;
            }
         }
         vertices[off+i].y = (stbtt_int16) y;
      }

      num_vertices=0;
      sx = sy = cx = cy = scx = scy = 0;
      for (i=0; i < n; ++i) {
         flags = vertices[off+i].type;
         x     = (stbtt_int16) vertices[off+i].x;
         y     = (stbtt_int16) vertices[off+i].y;

         if (next_move == i) {
            if (i != 0)
               num_vertices = stbtt__close_shape(vertices, num_vertices, was_off, start_off, sx,sy,scx,scy,cx,cy);

            start_off = !(flags & 1);
            if (start_off) {

               scx = x;
               scy = y;
               if (!(vertices[off+i+1].type & 1)) {

                  sx = (x + (stbtt_int32) vertices[off+i+1].x) >> 1;
                  sy = (y + (stbtt_int32) vertices[off+i+1].y) >> 1;
               } else {

                  sx = (stbtt_int32) vertices[off+i+1].x;
                  sy = (stbtt_int32) vertices[off+i+1].y;
                  ++i;
               }
            } else {
               sx = x;
               sy = y;
            }
            stbtt_setvertex(&vertices[num_vertices++], STBTT_vmove,sx,sy,0,0);
            was_off = 0;
            next_move = 1 + ttUSHORT(endPtsOfContours+j*2);
            ++j;
         } else {
            if (!(flags & 1)) {
               if (was_off)
                  stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, (cx+x)>>1, (cy+y)>>1, cx, cy);
               cx = x;
               cy = y;
               was_off = 1;
            } else {
               if (was_off)
                  stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, x,y, cx, cy);
               else
                  stbtt_setvertex(&vertices[num_vertices++], STBTT_vline, x,y,0,0);
               was_off = 0;
            }
         }
      }
      num_vertices = stbtt__close_shape(vertices, num_vertices, was_off, start_off, sx,sy,scx,scy,cx,cy);
   } else if (numberOfContours < 0) {

      int more = 1;
      stbtt_uint8 *comp = data + g + 10;
      num_vertices = 0;
      vertices = 0;
      while (more) {
         stbtt_uint16 flags, gidx;
         int comp_num_verts = 0, i;
         stbtt_vertex *comp_verts = 0, *tmp = 0;
         float mtx[6] = {1,0,0,1,0,0}, m, n;

         flags = ttSHORT(comp); comp+=2;
         gidx = ttSHORT(comp); comp+=2;

         if (flags & 2) {
            if (flags & 1) {
               mtx[4] = ttSHORT(comp); comp+=2;
               mtx[5] = ttSHORT(comp); comp+=2;
            } else {
               mtx[4] = ttCHAR(comp); comp+=1;
               mtx[5] = ttCHAR(comp); comp+=1;
            }
         }
         else {

            STBTT_assert(0);
         }
         if (flags & (1<<3)) {
            mtx[0] = mtx[3] = ttSHORT(comp)/16384.0f; comp+=2;
            mtx[1] = mtx[2] = 0;
         } else if (flags & (1<<6)) {
            mtx[0] = ttSHORT(comp)/16384.0f; comp+=2;
            mtx[1] = mtx[2] = 0;
            mtx[3] = ttSHORT(comp)/16384.0f; comp+=2;
         } else if (flags & (1<<7)) {
            mtx[0] = ttSHORT(comp)/16384.0f; comp+=2;
            mtx[1] = ttSHORT(comp)/16384.0f; comp+=2;
            mtx[2] = ttSHORT(comp)/16384.0f; comp+=2;
            mtx[3] = ttSHORT(comp)/16384.0f; comp+=2;
         }

         m = (float) STBTT_sqrt(mtx[0]*mtx[0] + mtx[1]*mtx[1]);
         n = (float) STBTT_sqrt(mtx[2]*mtx[2] + mtx[3]*mtx[3]);

         comp_num_verts = stbtt_GetGlyphShape(info, gidx, &comp_verts);
         if (comp_num_verts > 0) {

            for (i = 0; i < comp_num_verts; ++i) {
               stbtt_vertex* v = &comp_verts[i];
               stbtt_vertex_type x,y;
               x=v->x; y=v->y;
               v->x = (stbtt_vertex_type)(m * (mtx[0]*x + mtx[2]*y + mtx[4]));
               v->y = (stbtt_vertex_type)(n * (mtx[1]*x + mtx[3]*y + mtx[5]));
               x=v->cx; y=v->cy;
               v->cx = (stbtt_vertex_type)(m * (mtx[0]*x + mtx[2]*y + mtx[4]));
               v->cy = (stbtt_vertex_type)(n * (mtx[1]*x + mtx[3]*y + mtx[5]));
            }

            tmp = (stbtt_vertex*)STBTT_malloc((num_vertices+comp_num_verts)*sizeof(stbtt_vertex), info->userdata);
            if (!tmp) {
               if (vertices) STBTT_free(vertices, info->userdata);
               if (comp_verts) STBTT_free(comp_verts, info->userdata);
               return 0;
            }
            if (num_vertices > 0 && vertices) STBTT_memcpy(tmp, vertices, num_vertices*sizeof(stbtt_vertex));
            STBTT_memcpy(tmp+num_vertices, comp_verts, comp_num_verts*sizeof(stbtt_vertex));
            if (vertices) STBTT_free(vertices, info->userdata);
            vertices = tmp;
            STBTT_free(comp_verts, info->userdata);
            num_vertices += comp_num_verts;
         }

         more = flags & (1<<5);
      }
   } else {

   }

   *pvertices = vertices;
   return num_vertices;
}

typedef struct
{
   int bounds;
   int started;
   float first_x, first_y;
   float x, y;
   stbtt_int32 min_x, max_x, min_y, max_y;

   stbtt_vertex *pvertices;
   int num_vertices;
} stbtt__csctx;

#define STBTT__CSCTX_INIT(bounds) {bounds,0, 0,0, 0,0, 0,0,0,0, NULL, 0}

static void stbtt__track_vertex(stbtt__csctx *c, stbtt_int32 x, stbtt_int32 y)
{
   if (x > c->max_x || !c->started) c->max_x = x;
   if (y > c->max_y || !c->started) c->max_y = y;
   if (x < c->min_x || !c->started) c->min_x = x;
   if (y < c->min_y || !c->started) c->min_y = y;
   c->started = 1;
}

static void stbtt__csctx_v(stbtt__csctx *c, stbtt_uint8 type, stbtt_int32 x, stbtt_int32 y, stbtt_int32 cx, stbtt_int32 cy, stbtt_int32 cx1, stbtt_int32 cy1)
{
   if (c->bounds) {
      stbtt__track_vertex(c, x, y);
      if (type == STBTT_vcubic) {
         stbtt__track_vertex(c, cx, cy);
         stbtt__track_vertex(c, cx1, cy1);
      }
   } else {
      stbtt_setvertex(&c->pvertices[c->num_vertices], type, x, y, cx, cy);
      c->pvertices[c->num_vertices].cx1 = (stbtt_int16) cx1;
      c->pvertices[c->num_vertices].cy1 = (stbtt_int16) cy1;
   }
   c->num_vertices++;
}

static void stbtt__csctx_close_shape(stbtt__csctx *ctx)
{
   if (ctx->first_x != ctx->x || ctx->first_y != ctx->y)
      stbtt__csctx_v(ctx, STBTT_vline, (int)ctx->first_x, (int)ctx->first_y, 0, 0, 0, 0);
}

static void stbtt__csctx_rmove_to(stbtt__csctx *ctx, float dx, float dy)
{
   stbtt__csctx_close_shape(ctx);
   ctx->first_x = ctx->x = ctx->x + dx;
   ctx->first_y = ctx->y = ctx->y + dy;
   stbtt__csctx_v(ctx, STBTT_vmove, (int)ctx->x, (int)ctx->y, 0, 0, 0, 0);
}

static void stbtt__csctx_rline_to(stbtt__csctx *ctx, float dx, float dy)
{
   ctx->x += dx;
   ctx->y += dy;
   stbtt__csctx_v(ctx, STBTT_vline, (int)ctx->x, (int)ctx->y, 0, 0, 0, 0);
}

static void stbtt__csctx_rccurve_to(stbtt__csctx *ctx, float dx1, float dy1, float dx2, float dy2, float dx3, float dy3)
{
   float cx1 = ctx->x + dx1;
   float cy1 = ctx->y + dy1;
   float cx2 = cx1 + dx2;
   float cy2 = cy1 + dy2;
   ctx->x = cx2 + dx3;
   ctx->y = cy2 + dy3;
   stbtt__csctx_v(ctx, STBTT_vcubic, (int)ctx->x, (int)ctx->y, (int)cx1, (int)cy1, (int)cx2, (int)cy2);
}

static stbtt__buf stbtt__get_subr(stbtt__buf idx, int n)
{
   int count = stbtt__cff_index_count(&idx);
   int bias = 107;
   if (count >= 33900)
      bias = 32768;
   else if (count >= 1240)
      bias = 1131;
   n += bias;
   if (n < 0 || n >= count)
      return stbtt__new_buf(NULL, 0);
   return stbtt__cff_index_get(idx, n);
}

static stbtt__buf stbtt__cid_get_glyph_subrs(const stbtt_fontinfo *info, int glyph_index)
{
   stbtt__buf fdselect = info->fdselect;
   int nranges, start, end, v, fmt, fdselector = -1, i;

   stbtt__buf_seek(&fdselect, 0);
   fmt = stbtt__buf_get8(&fdselect);
   if (fmt == 0) {

      stbtt__buf_skip(&fdselect, glyph_index);
      fdselector = stbtt__buf_get8(&fdselect);
   } else if (fmt == 3) {
      nranges = stbtt__buf_get16(&fdselect);
      start = stbtt__buf_get16(&fdselect);
      for (i = 0; i < nranges; i++) {
         v = stbtt__buf_get8(&fdselect);
         end = stbtt__buf_get16(&fdselect);
         if (glyph_index >= start && glyph_index < end) {
            fdselector = v;
            break;
         }
         start = end;
      }
   }
   if (fdselector == -1) stbtt__new_buf(NULL, 0);
   return stbtt__get_subrs(info->cff, stbtt__cff_index_get(info->fontdicts, fdselector));
}

static int stbtt__run_charstring(const stbtt_fontinfo *info, int glyph_index, stbtt__csctx *c)
{
   int in_header = 1, maskbits = 0, subr_stack_height = 0, sp = 0, v, i, b0;
   int has_subrs = 0, clear_stack;
   float s[48];
   stbtt__buf subr_stack[10], subrs = info->subrs, b;
   float f;

#define STBTT__CSERR(s) (0)

   b = stbtt__cff_index_get(info->charstrings, glyph_index);
   while (b.cursor < b.size) {
      i = 0;
      clear_stack = 1;
      b0 = stbtt__buf_get8(&b);
      switch (b0) {

      case 0x13:
      case 0x14:
         if (in_header)
            maskbits += (sp / 2);
         in_header = 0;
         stbtt__buf_skip(&b, (maskbits + 7) / 8);
         break;

      case 0x01:
      case 0x03:
      case 0x12:
      case 0x17:
         maskbits += (sp / 2);
         break;

      case 0x15:
         in_header = 0;
         if (sp < 2) return STBTT__CSERR("rmoveto stack");
         stbtt__csctx_rmove_to(c, s[sp-2], s[sp-1]);
         break;
      case 0x04:
         in_header = 0;
         if (sp < 1) return STBTT__CSERR("vmoveto stack");
         stbtt__csctx_rmove_to(c, 0, s[sp-1]);
         break;
      case 0x16:
         in_header = 0;
         if (sp < 1) return STBTT__CSERR("hmoveto stack");
         stbtt__csctx_rmove_to(c, s[sp-1], 0);
         break;

      case 0x05:
         if (sp < 2) return STBTT__CSERR("rlineto stack");
         for (; i + 1 < sp; i += 2)
            stbtt__csctx_rline_to(c, s[i], s[i+1]);
         break;

      case 0x07:
         if (sp < 1) return STBTT__CSERR("vlineto stack");
         goto vlineto;
      case 0x06:
         if (sp < 1) return STBTT__CSERR("hlineto stack");
         for (;;) {
            if (i >= sp) break;
            stbtt__csctx_rline_to(c, s[i], 0);
            i++;
      vlineto:
            if (i >= sp) break;
            stbtt__csctx_rline_to(c, 0, s[i]);
            i++;
         }
         break;

      case 0x1F:
         if (sp < 4) return STBTT__CSERR("hvcurveto stack");
         goto hvcurveto;
      case 0x1E:
         if (sp < 4) return STBTT__CSERR("vhcurveto stack");
         for (;;) {
            if (i + 3 >= sp) break;
            stbtt__csctx_rccurve_to(c, 0, s[i], s[i+1], s[i+2], s[i+3], (sp - i == 5) ? s[i + 4] : 0.0f);
            i += 4;
      hvcurveto:
            if (i + 3 >= sp) break;
            stbtt__csctx_rccurve_to(c, s[i], 0, s[i+1], s[i+2], (sp - i == 5) ? s[i+4] : 0.0f, s[i+3]);
            i += 4;
         }
         break;

      case 0x08:
         if (sp < 6) return STBTT__CSERR("rcurveline stack");
         for (; i + 5 < sp; i += 6)
            stbtt__csctx_rccurve_to(c, s[i], s[i+1], s[i+2], s[i+3], s[i+4], s[i+5]);
         break;

      case 0x18:
         if (sp < 8) return STBTT__CSERR("rcurveline stack");
         for (; i + 5 < sp - 2; i += 6)
            stbtt__csctx_rccurve_to(c, s[i], s[i+1], s[i+2], s[i+3], s[i+4], s[i+5]);
         if (i + 1 >= sp) return STBTT__CSERR("rcurveline stack");
         stbtt__csctx_rline_to(c, s[i], s[i+1]);
         break;

      case 0x19:
         if (sp < 8) return STBTT__CSERR("rlinecurve stack");
         for (; i + 1 < sp - 6; i += 2)
            stbtt__csctx_rline_to(c, s[i], s[i+1]);
         if (i + 5 >= sp) return STBTT__CSERR("rlinecurve stack");
         stbtt__csctx_rccurve_to(c, s[i], s[i+1], s[i+2], s[i+3], s[i+4], s[i+5]);
         break;

      case 0x1A:
      case 0x1B:
         if (sp < 4) return STBTT__CSERR("(vv|hh)curveto stack");
         f = 0.0;
         if (sp & 1) { f = s[i]; i++; }
         for (; i + 3 < sp; i += 4) {
            if (b0 == 0x1B)
               stbtt__csctx_rccurve_to(c, s[i], f, s[i+1], s[i+2], s[i+3], 0.0);
            else
               stbtt__csctx_rccurve_to(c, f, s[i], s[i+1], s[i+2], 0.0, s[i+3]);
            f = 0.0;
         }
         break;

      case 0x0A:
         if (!has_subrs) {
            if (info->fdselect.size)
               subrs = stbtt__cid_get_glyph_subrs(info, glyph_index);
            has_subrs = 1;
         }
         /* FALLTHROUGH */
      case 0x1D:
         if (sp < 1) return STBTT__CSERR("call(g|)subr stack");
         v = (int) s[--sp];
         if (subr_stack_height >= 10) return STBTT__CSERR("recursion limit");
         subr_stack[subr_stack_height++] = b;
         b = stbtt__get_subr(b0 == 0x0A ? subrs : info->gsubrs, v);
         if (b.size == 0) return STBTT__CSERR("subr not found");
         b.cursor = 0;
         clear_stack = 0;
         break;

      case 0x0B:
         if (subr_stack_height <= 0) return STBTT__CSERR("return outside subr");
         b = subr_stack[--subr_stack_height];
         clear_stack = 0;
         break;

      case 0x0E:
         stbtt__csctx_close_shape(c);
         return 1;

      case 0x0C: {
         float dx1, dx2, dx3, dx4, dx5, dx6, dy1, dy2, dy3, dy4, dy5, dy6;
         float dx, dy;
         int b1 = stbtt__buf_get8(&b);
         switch (b1) {

         case 0x22:
            if (sp < 7) return STBTT__CSERR("hflex stack");
            dx1 = s[0];
            dx2 = s[1];
            dy2 = s[2];
            dx3 = s[3];
            dx4 = s[4];
            dx5 = s[5];
            dx6 = s[6];
            stbtt__csctx_rccurve_to(c, dx1, 0, dx2, dy2, dx3, 0);
            stbtt__csctx_rccurve_to(c, dx4, 0, dx5, -dy2, dx6, 0);
            break;

         case 0x23:
            if (sp < 13) return STBTT__CSERR("flex stack");
            dx1 = s[0];
            dy1 = s[1];
            dx2 = s[2];
            dy2 = s[3];
            dx3 = s[4];
            dy3 = s[5];
            dx4 = s[6];
            dy4 = s[7];
            dx5 = s[8];
            dy5 = s[9];
            dx6 = s[10];
            dy6 = s[11];

            stbtt__csctx_rccurve_to(c, dx1, dy1, dx2, dy2, dx3, dy3);
            stbtt__csctx_rccurve_to(c, dx4, dy4, dx5, dy5, dx6, dy6);
            break;

         case 0x24:
            if (sp < 9) return STBTT__CSERR("hflex1 stack");
            dx1 = s[0];
            dy1 = s[1];
            dx2 = s[2];
            dy2 = s[3];
            dx3 = s[4];
            dx4 = s[5];
            dx5 = s[6];
            dy5 = s[7];
            dx6 = s[8];
            stbtt__csctx_rccurve_to(c, dx1, dy1, dx2, dy2, dx3, 0);
            stbtt__csctx_rccurve_to(c, dx4, 0, dx5, dy5, dx6, -(dy1+dy2+dy5));
            break;

         case 0x25:
            if (sp < 11) return STBTT__CSERR("flex1 stack");
            dx1 = s[0];
            dy1 = s[1];
            dx2 = s[2];
            dy2 = s[3];
            dx3 = s[4];
            dy3 = s[5];
            dx4 = s[6];
            dy4 = s[7];
            dx5 = s[8];
            dy5 = s[9];
            dx6 = dy6 = s[10];
            dx = dx1+dx2+dx3+dx4+dx5;
            dy = dy1+dy2+dy3+dy4+dy5;
            if (STBTT_fabs(dx) > STBTT_fabs(dy))
               dy6 = -dy;
            else
               dx6 = -dx;
            stbtt__csctx_rccurve_to(c, dx1, dy1, dx2, dy2, dx3, dy3);
            stbtt__csctx_rccurve_to(c, dx4, dy4, dx5, dy5, dx6, dy6);
            break;

         default:
            return STBTT__CSERR("unimplemented");
         }
      } break;

      default:
         if (b0 != 255 && b0 != 28 && b0 < 32)
            return STBTT__CSERR("reserved operator");

         if (b0 == 255) {
            f = (float)(stbtt_int32)stbtt__buf_get32(&b) / 0x10000;
         } else {
            stbtt__buf_skip(&b, -1);
            f = (float)(stbtt_int16)stbtt__cff_int(&b);
         }
         if (sp >= 48) return STBTT__CSERR("push stack overflow");
         s[sp++] = f;
         clear_stack = 0;
         break;
      }
      if (clear_stack) sp = 0;
   }
   return STBTT__CSERR("no endchar");

#undef STBTT__CSERR
}

static int stbtt__GetGlyphShapeT2(const stbtt_fontinfo *info, int glyph_index, stbtt_vertex **pvertices)
{

   stbtt__csctx count_ctx = STBTT__CSCTX_INIT(1);
   stbtt__csctx output_ctx = STBTT__CSCTX_INIT(0);
   if (stbtt__run_charstring(info, glyph_index, &count_ctx)) {
      *pvertices = (stbtt_vertex*)STBTT_malloc(count_ctx.num_vertices*sizeof(stbtt_vertex), info->userdata);
      output_ctx.pvertices = *pvertices;
      if (stbtt__run_charstring(info, glyph_index, &output_ctx)) {
         STBTT_assert(output_ctx.num_vertices == count_ctx.num_vertices);
         return output_ctx.num_vertices;
      }
   }
   *pvertices = NULL;
   return 0;
}

static int stbtt__GetGlyphInfoT2(const stbtt_fontinfo *info, int glyph_index, int *x0, int *y0, int *x1, int *y1)
{
   stbtt__csctx c = STBTT__CSCTX_INIT(1);
   int r = stbtt__run_charstring(info, glyph_index, &c);
   if (x0)  *x0 = r ? c.min_x : 0;
   if (y0)  *y0 = r ? c.min_y : 0;
   if (x1)  *x1 = r ? c.max_x : 0;
   if (y1)  *y1 = r ? c.max_y : 0;
   return r ? c.num_vertices : 0;
}

STBTT_DEF int stbtt_GetGlyphShape(const stbtt_fontinfo *info, int glyph_index, stbtt_vertex **pvertices)
{
   if (!info->cff.size)
      return stbtt__GetGlyphShapeTT(info, glyph_index, pvertices);
   else
      return stbtt__GetGlyphShapeT2(info, glyph_index, pvertices);
}

STBTT_DEF void stbtt_GetGlyphHMetrics(const stbtt_fontinfo *info, int glyph_index, int *advanceWidth, int *leftSideBearing)
{
   stbtt_uint16 numOfLongHorMetrics = ttUSHORT(info->data+info->hhea + 34);
   if (glyph_index < numOfLongHorMetrics) {
      if (advanceWidth)     *advanceWidth    = ttSHORT(info->data + info->hmtx + 4*glyph_index);
      if (leftSideBearing)  *leftSideBearing = ttSHORT(info->data + info->hmtx + 4*glyph_index + 2);
   } else {
      if (advanceWidth)     *advanceWidth    = ttSHORT(info->data + info->hmtx + 4*(numOfLongHorMetrics-1));
      if (leftSideBearing)  *leftSideBearing = ttSHORT(info->data + info->hmtx + 4*numOfLongHorMetrics + 2*(glyph_index - numOfLongHorMetrics));
   }
}

STBTT_DEF int  stbtt_GetKerningTableLength(const stbtt_fontinfo *info)
{
   stbtt_uint8 *data = info->data + info->kern;

   if (!info->kern)
      return 0;
   if (ttUSHORT(data+2) < 1)
      return 0;
   if (ttUSHORT(data+8) != 1)
      return 0;

   return ttUSHORT(data+10);
}

STBTT_DEF int stbtt_GetKerningTable(const stbtt_fontinfo *info, stbtt_kerningentry* table, int table_length)
{
   stbtt_uint8 *data = info->data + info->kern;
   int k, length;

   if (!info->kern)
      return 0;
   if (ttUSHORT(data+2) < 1)
      return 0;
   if (ttUSHORT(data+8) != 1)
      return 0;

   length = ttUSHORT(data+10);
   if (table_length < length)
      length = table_length;

   for (k = 0; k < length; k++)
   {
      table[k].glyph1 = ttUSHORT(data+18+(k*6));
      table[k].glyph2 = ttUSHORT(data+20+(k*6));
      table[k].advance = ttSHORT(data+22+(k*6));
   }

   return length;
}

static int stbtt__GetGlyphKernInfoAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2)
{
   stbtt_uint8 *data = info->data + info->kern;
   stbtt_uint32 needle, straw;
   int l, r, m;

   if (!info->kern)
      return 0;
   if (ttUSHORT(data+2) < 1)
      return 0;
   if (ttUSHORT(data+8) != 1)
      return 0;

   l = 0;
   r = ttUSHORT(data+10) - 1;
   needle = glyph1 << 16 | glyph2;
   while (l <= r) {
      m = (l + r) >> 1;
      straw = ttULONG(data+18+(m*6));
      if (needle < straw)
         r = m - 1;
      else if (needle > straw)
         l = m + 1;
      else
         return ttSHORT(data+22+(m*6));
   }
   return 0;
}

static stbtt_int32 stbtt__GetCoverageIndex(stbtt_uint8 *coverageTable, int glyph)
{
   stbtt_uint16 coverageFormat = ttUSHORT(coverageTable);
   switch (coverageFormat) {
      case 1: {
         stbtt_uint16 glyphCount = ttUSHORT(coverageTable + 2);

         stbtt_int32 l=0, r=glyphCount-1, m;
         int straw, needle=glyph;
         while (l <= r) {
            stbtt_uint8 *glyphArray = coverageTable + 4;
            stbtt_uint16 glyphID;
            m = (l + r) >> 1;
            glyphID = ttUSHORT(glyphArray + 2 * m);
            straw = glyphID;
            if (needle < straw)
               r = m - 1;
            else if (needle > straw)
               l = m + 1;
            else {
               return m;
            }
         }
         break;
      }

      case 2: {
         stbtt_uint16 rangeCount = ttUSHORT(coverageTable + 2);
         stbtt_uint8 *rangeArray = coverageTable + 4;

         stbtt_int32 l=0, r=rangeCount-1, m;
         int strawStart, strawEnd, needle=glyph;
         while (l <= r) {
            stbtt_uint8 *rangeRecord;
            m = (l + r) >> 1;
            rangeRecord = rangeArray + 6 * m;
            strawStart = ttUSHORT(rangeRecord);
            strawEnd = ttUSHORT(rangeRecord + 2);
            if (needle < strawStart)
               r = m - 1;
            else if (needle > strawEnd)
               l = m + 1;
            else {
               stbtt_uint16 startCoverageIndex = ttUSHORT(rangeRecord + 4);
               return startCoverageIndex + glyph - strawStart;
            }
         }
         break;
      }

      default: return -1;
   }

   return -1;
}

static stbtt_int32  stbtt__GetGlyphClass(stbtt_uint8 *classDefTable, int glyph)
{
   stbtt_uint16 classDefFormat = ttUSHORT(classDefTable);
   switch (classDefFormat)
   {
      case 1: {
         stbtt_uint16 startGlyphID = ttUSHORT(classDefTable + 2);
         stbtt_uint16 glyphCount = ttUSHORT(classDefTable + 4);
         stbtt_uint8 *classDef1ValueArray = classDefTable + 6;

         if (glyph >= startGlyphID && glyph < startGlyphID + glyphCount)
            return (stbtt_int32)ttUSHORT(classDef1ValueArray + 2 * (glyph - startGlyphID));
         break;
      }

      case 2: {
         stbtt_uint16 classRangeCount = ttUSHORT(classDefTable + 2);
         stbtt_uint8 *classRangeRecords = classDefTable + 4;

         stbtt_int32 l=0, r=classRangeCount-1, m;
         int strawStart, strawEnd, needle=glyph;
         while (l <= r) {
            stbtt_uint8 *classRangeRecord;
            m = (l + r) >> 1;
            classRangeRecord = classRangeRecords + 6 * m;
            strawStart = ttUSHORT(classRangeRecord);
            strawEnd = ttUSHORT(classRangeRecord + 2);
            if (needle < strawStart)
               r = m - 1;
            else if (needle > strawEnd)
               l = m + 1;
            else
               return (stbtt_int32)ttUSHORT(classRangeRecord + 4);
         }
         break;
      }

      default:
         return -1;
   }

   return 0;
}

#define STBTT_GPOS_TODO_assert(x)

static stbtt_int32 stbtt__GetGlyphGPOSInfoAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2)
{
   stbtt_uint16 lookupListOffset;
   stbtt_uint8 *lookupList;
   stbtt_uint16 lookupCount;
   stbtt_uint8 *data;
   stbtt_int32 i, sti;

   if (!info->gpos) return 0;

   data = info->data + info->gpos;

   if (ttUSHORT(data+0) != 1) return 0;
   if (ttUSHORT(data+2) != 0) return 0;

   lookupListOffset = ttUSHORT(data+8);
   lookupList = data + lookupListOffset;
   lookupCount = ttUSHORT(lookupList);

   for (i=0; i<lookupCount; ++i) {
      stbtt_uint16 lookupOffset = ttUSHORT(lookupList + 2 + 2 * i);
      stbtt_uint8 *lookupTable = lookupList + lookupOffset;

      stbtt_uint16 lookupType = ttUSHORT(lookupTable);
      stbtt_uint16 subTableCount = ttUSHORT(lookupTable + 4);
      stbtt_uint8 *subTableOffsets = lookupTable + 6;
      if (lookupType != 2)
         continue;

      for (sti=0; sti<subTableCount; sti++) {
         stbtt_uint16 subtableOffset = ttUSHORT(subTableOffsets + 2 * sti);
         stbtt_uint8 *table = lookupTable + subtableOffset;
         stbtt_uint16 posFormat = ttUSHORT(table);
         stbtt_uint16 coverageOffset = ttUSHORT(table + 2);
         stbtt_int32 coverageIndex = stbtt__GetCoverageIndex(table + coverageOffset, glyph1);
         if (coverageIndex == -1) continue;

         switch (posFormat) {
            case 1: {
               stbtt_int32 l, r, m;
               int straw, needle;
               stbtt_uint16 valueFormat1 = ttUSHORT(table + 4);
               stbtt_uint16 valueFormat2 = ttUSHORT(table + 6);
               if (valueFormat1 == 4 && valueFormat2 == 0) {
                  stbtt_int32 valueRecordPairSizeInBytes = 2;
                  stbtt_uint16 pairSetCount = ttUSHORT(table + 8);
                  stbtt_uint16 pairPosOffset = ttUSHORT(table + 10 + 2 * coverageIndex);
                  stbtt_uint8 *pairValueTable = table + pairPosOffset;
                  stbtt_uint16 pairValueCount = ttUSHORT(pairValueTable);
                  stbtt_uint8 *pairValueArray = pairValueTable + 2;

                  if (coverageIndex >= pairSetCount) return 0;

                  needle=glyph2;
                  r=pairValueCount-1;
                  l=0;

                  while (l <= r) {
                     stbtt_uint16 secondGlyph;
                     stbtt_uint8 *pairValue;
                     m = (l + r) >> 1;
                     pairValue = pairValueArray + (2 + valueRecordPairSizeInBytes) * m;
                     secondGlyph = ttUSHORT(pairValue);
                     straw = secondGlyph;
                     if (needle < straw)
                        r = m - 1;
                     else if (needle > straw)
                        l = m + 1;
                     else {
                        stbtt_int16 xAdvance = ttSHORT(pairValue + 2);
                        return xAdvance;
                     }
                  }
               } else
                  return 0;
               break;
            }

            case 2: {
               stbtt_uint16 valueFormat1 = ttUSHORT(table + 4);
               stbtt_uint16 valueFormat2 = ttUSHORT(table + 6);
               if (valueFormat1 == 4 && valueFormat2 == 0) {
                  stbtt_uint16 classDef1Offset = ttUSHORT(table + 8);
                  stbtt_uint16 classDef2Offset = ttUSHORT(table + 10);
                  int glyph1class = stbtt__GetGlyphClass(table + classDef1Offset, glyph1);
                  int glyph2class = stbtt__GetGlyphClass(table + classDef2Offset, glyph2);

                  stbtt_uint16 class1Count = ttUSHORT(table + 12);
                  stbtt_uint16 class2Count = ttUSHORT(table + 14);
                  stbtt_uint8 *class1Records, *class2Records;
                  stbtt_int16 xAdvance;

                  if (glyph1class < 0 || glyph1class >= class1Count) return 0;
                  if (glyph2class < 0 || glyph2class >= class2Count) return 0;

                  class1Records = table + 16;
                  class2Records = class1Records + 2 * (glyph1class * class2Count);
                  xAdvance = ttSHORT(class2Records + 2 * glyph2class);
                  return xAdvance;
               } else
                  return 0;
               break;
            }

            default:
               return 0;
         }
      }
   }

   return 0;
}

STBTT_DEF int  stbtt_GetGlyphKernAdvance(const stbtt_fontinfo *info, int g1, int g2)
{
   int xAdvance = 0;

   if (info->gpos)
      xAdvance += stbtt__GetGlyphGPOSInfoAdvance(info, g1, g2);
   else if (info->kern)
      xAdvance += stbtt__GetGlyphKernInfoAdvance(info, g1, g2);

   return xAdvance;
}

STBTT_DEF int  stbtt_GetCodepointKernAdvance(const stbtt_fontinfo *info, int ch1, int ch2)
{
   if (!info->kern && !info->gpos)
      return 0;
   return stbtt_GetGlyphKernAdvance(info, stbtt_FindGlyphIndex(info,ch1), stbtt_FindGlyphIndex(info,ch2));
}

STBTT_DEF void stbtt_GetCodepointHMetrics(const stbtt_fontinfo *info, int codepoint, int *advanceWidth, int *leftSideBearing)
{
   stbtt_GetGlyphHMetrics(info, stbtt_FindGlyphIndex(info,codepoint), advanceWidth, leftSideBearing);
}

STBTT_DEF void stbtt_GetFontVMetrics(const stbtt_fontinfo *info, int *ascent, int *descent, int *lineGap)
{
   if (ascent ) *ascent  = ttSHORT(info->data+info->hhea + 4);
   if (descent) *descent = ttSHORT(info->data+info->hhea + 6);
   if (lineGap) *lineGap = ttSHORT(info->data+info->hhea + 8);
}

STBTT_DEF int  stbtt_GetFontVMetricsOS2(const stbtt_fontinfo *info, int *typoAscent, int *typoDescent, int *typoLineGap)
{
   int tab = stbtt__find_table(info->data, info->fontstart, "OS/2");
   if (!tab)
      return 0;
   if (typoAscent ) *typoAscent  = ttSHORT(info->data+tab + 68);
   if (typoDescent) *typoDescent = ttSHORT(info->data+tab + 70);
   if (typoLineGap) *typoLineGap = ttSHORT(info->data+tab + 72);
   return 1;
}

STBTT_DEF void stbtt_GetFontBoundingBox(const stbtt_fontinfo *info, int *x0, int *y0, int *x1, int *y1)
{
   *x0 = ttSHORT(info->data + info->head + 36);
   *y0 = ttSHORT(info->data + info->head + 38);
   *x1 = ttSHORT(info->data + info->head + 40);
   *y1 = ttSHORT(info->data + info->head + 42);
}

STBTT_DEF float stbtt_ScaleForPixelHeight(const stbtt_fontinfo *info, float height)
{
   int fheight = ttSHORT(info->data + info->hhea + 4) - ttSHORT(info->data + info->hhea + 6);
   return (float) height / fheight;
}

STBTT_DEF float stbtt_ScaleForMappingEmToPixels(const stbtt_fontinfo *info, float pixels)
{
   int unitsPerEm = ttUSHORT(info->data + info->head + 18);
   return pixels / unitsPerEm;
}

STBTT_DEF void stbtt_FreeShape(const stbtt_fontinfo *info, stbtt_vertex *v)
{
   STBTT_free(v, info->userdata);
}

STBTT_DEF stbtt_uint8 *stbtt_FindSVGDoc(const stbtt_fontinfo *info, int gl)
{
   int i;
   stbtt_uint8 *data = info->data;
   stbtt_uint8 *svg_doc_list = data + stbtt__get_svg((stbtt_fontinfo *) info);

   int numEntries = ttUSHORT(svg_doc_list);
   stbtt_uint8 *svg_docs = svg_doc_list + 2;

   for(i=0; i<numEntries; i++) {
      stbtt_uint8 *svg_doc = svg_docs + (12 * i);
      if ((gl >= ttUSHORT(svg_doc)) && (gl <= ttUSHORT(svg_doc + 2)))
         return svg_doc;
   }
   return 0;
}

STBTT_DEF int stbtt_GetGlyphSVG(const stbtt_fontinfo *info, int gl, const char **svg)
{
   stbtt_uint8 *data = info->data;
   stbtt_uint8 *svg_doc;

   if (info->svg == 0)
      return 0;

   svg_doc = stbtt_FindSVGDoc(info, gl);
   if (svg_doc != NULL) {
      *svg = (char *) data + info->svg + ttULONG(svg_doc + 4);
      return ttULONG(svg_doc + 8);
   } else {
      return 0;
   }
}

STBTT_DEF int stbtt_GetCodepointSVG(const stbtt_fontinfo *info, int unicode_codepoint, const char **svg)
{
   return stbtt_GetGlyphSVG(info, stbtt_FindGlyphIndex(info, unicode_codepoint), svg);
}

STBTT_DEF void stbtt_GetGlyphBitmapBoxSubpixel(const stbtt_fontinfo *font, int glyph, float scale_x, float scale_y,float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
   int x0=0,y0=0,x1,y1;
   if (!stbtt_GetGlyphBox(font, glyph, &x0,&y0,&x1,&y1)) {

      if (ix0) *ix0 = 0;
      if (iy0) *iy0 = 0;
      if (ix1) *ix1 = 0;
      if (iy1) *iy1 = 0;
   } else {

      if (ix0) *ix0 = STBTT_ifloor( x0 * scale_x + shift_x);
      if (iy0) *iy0 = STBTT_ifloor(-y1 * scale_y + shift_y);
      if (ix1) *ix1 = STBTT_iceil ( x1 * scale_x + shift_x);
      if (iy1) *iy1 = STBTT_iceil (-y0 * scale_y + shift_y);
   }
}

STBTT_DEF void stbtt_GetGlyphBitmapBox(const stbtt_fontinfo *font, int glyph, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
   stbtt_GetGlyphBitmapBoxSubpixel(font, glyph, scale_x, scale_y,0.0f,0.0f, ix0, iy0, ix1, iy1);
}

STBTT_DEF void stbtt_GetCodepointBitmapBoxSubpixel(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
   stbtt_GetGlyphBitmapBoxSubpixel(font, stbtt_FindGlyphIndex(font,codepoint), scale_x, scale_y,shift_x,shift_y, ix0,iy0,ix1,iy1);
}

STBTT_DEF void stbtt_GetCodepointBitmapBox(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
   stbtt_GetCodepointBitmapBoxSubpixel(font, codepoint, scale_x, scale_y,0.0f,0.0f, ix0,iy0,ix1,iy1);
}

typedef struct stbtt__hheap_chunk
{
   struct stbtt__hheap_chunk *next;
} stbtt__hheap_chunk;

typedef struct stbtt__hheap
{
   struct stbtt__hheap_chunk *head;
   void   *first_free;
   int    num_remaining_in_head_chunk;
} stbtt__hheap;

static void *stbtt__hheap_alloc(stbtt__hheap *hh, size_t size, void *userdata)
{
   if (hh->first_free) {
      void *p = hh->first_free;
      hh->first_free = * (void **) p;
      return p;
   } else {
      if (hh->num_remaining_in_head_chunk == 0) {
         int count = (size < 32 ? 2000 : size < 128 ? 800 : 100);
         stbtt__hheap_chunk *c = (stbtt__hheap_chunk *) STBTT_malloc(sizeof(stbtt__hheap_chunk) + size * count, userdata);
         if (c == NULL)
            return NULL;
         c->next = hh->head;
         hh->head = c;
         hh->num_remaining_in_head_chunk = count;
      }
      --hh->num_remaining_in_head_chunk;
      return (char *) (hh->head) + sizeof(stbtt__hheap_chunk) + size * hh->num_remaining_in_head_chunk;
   }
}

static void stbtt__hheap_free(stbtt__hheap *hh, void *p)
{
   *(void **) p = hh->first_free;
   hh->first_free = p;
}

static void stbtt__hheap_cleanup(stbtt__hheap *hh, void *userdata)
{
   stbtt__hheap_chunk *c = hh->head;
   while (c) {
      stbtt__hheap_chunk *n = c->next;
      STBTT_free(c, userdata);
      c = n;
   }
}

typedef struct stbtt__edge {
   float x0,y0, x1,y1;
   int invert;
} stbtt__edge;

typedef struct stbtt__active_edge
{
   struct stbtt__active_edge *next;
   #if STBTT_RASTERIZER_VERSION==1
   int x,dx;
   float ey;
   int direction;
   #elif STBTT_RASTERIZER_VERSION==2
   float fx,fdx,fdy;
   float direction;
   float sy;
   float ey;
   #else
   #error "Unrecognized value of STBTT_RASTERIZER_VERSION"
   #endif
} stbtt__active_edge;

#if STBTT_RASTERIZER_VERSION == 1
#define STBTT_FIXSHIFT   10
#define STBTT_FIX        (1 << STBTT_FIXSHIFT)
#define STBTT_FIXMASK    (STBTT_FIX-1)

static stbtt__active_edge *stbtt__new_active(stbtt__hheap *hh, stbtt__edge *e, int off_x, float start_point, void *userdata)
{
   stbtt__active_edge *z = (stbtt__active_edge *) stbtt__hheap_alloc(hh, sizeof(*z), userdata);
   float dxdy = (e->x1 - e->x0) / (e->y1 - e->y0);
   STBTT_assert(z != NULL);
   if (!z) return z;

   if (dxdy < 0)
      z->dx = -STBTT_ifloor(STBTT_FIX * -dxdy);
   else
      z->dx = STBTT_ifloor(STBTT_FIX * dxdy);

   z->x = STBTT_ifloor(STBTT_FIX * e->x0 + z->dx * (start_point - e->y0));
   z->x -= off_x * STBTT_FIX;

   z->ey = e->y1;
   z->next = 0;
   z->direction = e->invert ? 1 : -1;
   return z;
}
#elif STBTT_RASTERIZER_VERSION == 2
static stbtt__active_edge *stbtt__new_active(stbtt__hheap *hh, stbtt__edge *e, int off_x, float start_point, void *userdata)
{
   stbtt__active_edge *z = (stbtt__active_edge *) stbtt__hheap_alloc(hh, sizeof(*z), userdata);
   float dxdy = (e->x1 - e->x0) / (e->y1 - e->y0);
   STBTT_assert(z != NULL);

   if (!z) return z;
   z->fdx = dxdy;
   z->fdy = dxdy != 0.0f ? (1.0f/dxdy) : 0.0f;
   z->fx = e->x0 + dxdy * (start_point - e->y0);
   z->fx -= off_x;
   z->direction = e->invert ? 1.0f : -1.0f;
   z->sy = e->y0;
   z->ey = e->y1;
   z->next = 0;
   return z;
}
#else
#error "Unrecognized value of STBTT_RASTERIZER_VERSION"
#endif

#if STBTT_RASTERIZER_VERSION == 1

static void stbtt__fill_active_edges(unsigned char *scanline, int len, stbtt__active_edge *e, int max_weight)
{

   int x0=0, w=0;

   while (e) {
      if (w == 0) {

         x0 = e->x; w += e->direction;
      } else {
         int x1 = e->x; w += e->direction;

         if (w == 0) {
            int i = x0 >> STBTT_FIXSHIFT;
            int j = x1 >> STBTT_FIXSHIFT;

            if (i < len && j >= 0) {
               if (i == j) {

                  scanline[i] = scanline[i] + (stbtt_uint8) ((x1 - x0) * max_weight >> STBTT_FIXSHIFT);
               } else {
                  if (i >= 0)
                     scanline[i] = scanline[i] + (stbtt_uint8) (((STBTT_FIX - (x0 & STBTT_FIXMASK)) * max_weight) >> STBTT_FIXSHIFT);
                  else
                     i = -1;

                  if (j < len)
                     scanline[j] = scanline[j] + (stbtt_uint8) (((x1 & STBTT_FIXMASK) * max_weight) >> STBTT_FIXSHIFT);
                  else
                     j = len;

                  for (++i; i < j; ++i)
                     scanline[i] = scanline[i] + (stbtt_uint8) max_weight;
               }
            }
         }
      }

      e = e->next;
   }
}

static void stbtt__rasterize_sorted_edges(stbtt__bitmap *result, stbtt__edge *e, int n, int vsubsample, int off_x, int off_y, void *userdata)
{
   stbtt__hheap hh = { 0, 0, 0 };
   stbtt__active_edge *active = NULL;
   int y,j=0;
   int max_weight = (255 / vsubsample);
   int s;
   unsigned char scanline_data[512], *scanline;

   if (result->w > 512)
      scanline = (unsigned char *) STBTT_malloc(result->w, userdata);
   else
      scanline = scanline_data;

   y = off_y * vsubsample;
   e[n].y0 = (off_y + result->h) * (float) vsubsample + 1;

   while (j < result->h) {
      STBTT_memset(scanline, 0, result->w);
      for (s=0; s < vsubsample; ++s) {

         float scan_y = y + 0.5f;
         stbtt__active_edge **step = &active;

         while (*step) {
            stbtt__active_edge * z = *step;
            if (z->ey <= scan_y) {
               *step = z->next;
               STBTT_assert(z->direction);
               z->direction = 0;
               stbtt__hheap_free(&hh, z);
            } else {
               z->x += z->dx;
               step = &((*step)->next);
            }
         }

         for(;;) {
            int changed=0;
            step = &active;
            while (*step && (*step)->next) {
               if ((*step)->x > (*step)->next->x) {
                  stbtt__active_edge *t = *step;
                  stbtt__active_edge *q = t->next;

                  t->next = q->next;
                  q->next = t;
                  *step = q;
                  changed = 1;
               }
               step = &(*step)->next;
            }
            if (!changed) break;
         }

         while (e->y0 <= scan_y) {
            if (e->y1 > scan_y) {
               stbtt__active_edge *z = stbtt__new_active(&hh, e, off_x, scan_y, userdata);
               if (z != NULL) {

                  if (active == NULL)
                     active = z;
                  else if (z->x < active->x) {

                     z->next = active;
                     active = z;
                  } else {

                     stbtt__active_edge *p = active;
                     while (p->next && p->next->x < z->x)
                        p = p->next;

                     z->next = p->next;
                     p->next = z;
                  }
               }
            }
            ++e;
         }

         if (active)
            stbtt__fill_active_edges(scanline, result->w, active, max_weight);

         ++y;
      }
      STBTT_memcpy(result->pixels + j * result->stride, scanline, result->w);
      ++j;
   }

   stbtt__hheap_cleanup(&hh, userdata);

   if (scanline != scanline_data)
      STBTT_free(scanline, userdata);
}

#elif STBTT_RASTERIZER_VERSION == 2

static void stbtt__handle_clipped_edge(float *scanline, int x, stbtt__active_edge *e, float x0, float y0, float x1, float y1)
{
   if (y0 == y1) return;
   STBTT_assert(y0 < y1);
   STBTT_assert(e->sy <= e->ey);
   if (y0 > e->ey) return;
   if (y1 < e->sy) return;
   if (y0 < e->sy) {
      x0 += (x1-x0) * (e->sy - y0) / (y1-y0);
      y0 = e->sy;
   }
   if (y1 > e->ey) {
      x1 += (x1-x0) * (e->ey - y1) / (y1-y0);
      y1 = e->ey;
   }

   if (x0 == x)
      STBTT_assert(x1 <= x+1);
   else if (x0 == x+1)
      STBTT_assert(x1 >= x);
   else if (x0 <= x)
      STBTT_assert(x1 <= x);
   else if (x0 >= x+1)
      STBTT_assert(x1 >= x+1);
   else
      STBTT_assert(x1 >= x && x1 <= x+1);

   if (x0 <= x && x1 <= x)
      scanline[x] += e->direction * (y1-y0);
   else if (x0 >= x+1 && x1 >= x+1)
      ;
   else {
      STBTT_assert(x0 >= x && x0 <= x+1 && x1 >= x && x1 <= x+1);
      scanline[x] += e->direction * (y1-y0) * (1-((x0-x)+(x1-x))/2);
   }
}

static float stbtt__sized_trapezoid_area(float height, float top_width, float bottom_width)
{
   STBTT_assert(top_width >= 0);
   STBTT_assert(bottom_width >= 0);
   return (top_width + bottom_width) / 2.0f * height;
}

static float stbtt__position_trapezoid_area(float height, float tx0, float tx1, float bx0, float bx1)
{
   return stbtt__sized_trapezoid_area(height, tx1 - tx0, bx1 - bx0);
}

static float stbtt__sized_triangle_area(float height, float width)
{
   return height * width / 2;
}

static void stbtt__fill_active_edges_new(float *scanline, float *scanline_fill, int len, stbtt__active_edge *e, float y_top)
{
   float y_bottom = y_top+1;

   while (e) {

      STBTT_assert(e->ey >= y_top);

      if (e->fdx == 0) {
         float x0 = e->fx;
         if (x0 < len) {
            if (x0 >= 0) {
               stbtt__handle_clipped_edge(scanline,(int) x0,e, x0,y_top, x0,y_bottom);
               stbtt__handle_clipped_edge(scanline_fill-1,(int) x0+1,e, x0,y_top, x0,y_bottom);
            } else {
               stbtt__handle_clipped_edge(scanline_fill-1,0,e, x0,y_top, x0,y_bottom);
            }
         }
      } else {
         float x0 = e->fx;
         float dx = e->fdx;
         float xb = x0 + dx;
         float x_top, x_bottom;
         float sy0,sy1;
         float dy = e->fdy;
         STBTT_assert(e->sy <= y_bottom && e->ey >= y_top);

         if (e->sy > y_top) {
            x_top = x0 + dx * (e->sy - y_top);
            sy0 = e->sy;
         } else {
            x_top = x0;
            sy0 = y_top;
         }
         if (e->ey < y_bottom) {
            x_bottom = x0 + dx * (e->ey - y_top);
            sy1 = e->ey;
         } else {
            x_bottom = xb;
            sy1 = y_bottom;
         }

         if (x_top >= 0 && x_bottom >= 0 && x_top < len && x_bottom < len) {

            if ((int) x_top == (int) x_bottom) {
               float height;

               int x = (int) x_top;
               height = (sy1 - sy0) * e->direction;
               STBTT_assert(x >= 0 && x < len);
               scanline[x]      += stbtt__position_trapezoid_area(height, x_top, x+1.0f, x_bottom, x+1.0f);
               scanline_fill[x] += height;
            } else {
               int x,x1,x2;
               float y_crossing, y_final, step, sign, area;

               if (x_top > x_bottom) {

                  float t;
                  sy0 = y_bottom - (sy0 - y_top);
                  sy1 = y_bottom - (sy1 - y_top);
                  t = sy0, sy0 = sy1, sy1 = t;
                  t = x_bottom, x_bottom = x_top, x_top = t;
                  dx = -dx;
                  dy = -dy;
                  t = x0, x0 = xb, xb = t;
               }
               STBTT_assert(dy >= 0);
               STBTT_assert(dx >= 0);

               x1 = (int) x_top;
               x2 = (int) x_bottom;

               y_crossing = y_top + dy * (x1+1 - x0);

               y_final = y_top + dy * (x2 - x0);

               if (y_crossing > y_bottom)
                  y_crossing = y_bottom;

               sign = e->direction;

               area = sign * (y_crossing-sy0);

               scanline[x1] += stbtt__sized_triangle_area(area, x1+1 - x_top);

               if (y_final > y_bottom) {
                  y_final = y_bottom;
                  dy = (y_final - y_crossing ) / (x2 - (x1+1));
               }

               step = sign * dy * 1;

               for (x = x1+1; x < x2; ++x) {
                  scanline[x] += area + step/2;
                  area += step;
               }
               STBTT_assert(STBTT_fabs(area) <= 1.01f);
               STBTT_assert(sy1 > y_final-0.01f);

               scanline[x2] += area + sign * stbtt__position_trapezoid_area(sy1-y_final, (float) x2, x2+1.0f, x_bottom, x2+1.0f);

               scanline_fill[x2] += sign * (sy1-sy0);
            }
         } else {

            int x;
            for (x=0; x < len; ++x) {

               float y0 = y_top;
               float x1 = (float) (x);
               float x2 = (float) (x+1);
               float x3 = xb;
               float y3 = y_bottom;

               float y1 = (x - x0) / dx + y_top;
               float y2 = (x+1 - x0) / dx + y_top;

               if (x0 < x1 && x3 > x2) {
                  stbtt__handle_clipped_edge(scanline,x,e, x0,y0, x1,y1);
                  stbtt__handle_clipped_edge(scanline,x,e, x1,y1, x2,y2);
                  stbtt__handle_clipped_edge(scanline,x,e, x2,y2, x3,y3);
               } else if (x3 < x1 && x0 > x2) {
                  stbtt__handle_clipped_edge(scanline,x,e, x0,y0, x2,y2);
                  stbtt__handle_clipped_edge(scanline,x,e, x2,y2, x1,y1);
                  stbtt__handle_clipped_edge(scanline,x,e, x1,y1, x3,y3);
               } else if (x0 < x1 && x3 > x1) {
                  stbtt__handle_clipped_edge(scanline,x,e, x0,y0, x1,y1);
                  stbtt__handle_clipped_edge(scanline,x,e, x1,y1, x3,y3);
               } else if (x3 < x1 && x0 > x1) {
                  stbtt__handle_clipped_edge(scanline,x,e, x0,y0, x1,y1);
                  stbtt__handle_clipped_edge(scanline,x,e, x1,y1, x3,y3);
               } else if (x0 < x2 && x3 > x2) {
                  stbtt__handle_clipped_edge(scanline,x,e, x0,y0, x2,y2);
                  stbtt__handle_clipped_edge(scanline,x,e, x2,y2, x3,y3);
               } else if (x3 < x2 && x0 > x2) {
                  stbtt__handle_clipped_edge(scanline,x,e, x0,y0, x2,y2);
                  stbtt__handle_clipped_edge(scanline,x,e, x2,y2, x3,y3);
               } else {
                  stbtt__handle_clipped_edge(scanline,x,e, x0,y0, x3,y3);
               }
            }
         }
      }
      e = e->next;
   }
}

static void stbtt__rasterize_sorted_edges(stbtt__bitmap *result, stbtt__edge *e, int n, int vsubsample, int off_x, int off_y, void *userdata)
{
   stbtt__hheap hh = { 0, 0, 0 };
   stbtt__active_edge *active = NULL;
   int y,j=0, i;
   float scanline_data[129], *scanline, *scanline2;

   STBTT__NOTUSED(vsubsample);

   if (result->w > 64)
      scanline = (float *) STBTT_malloc((result->w*2+1) * sizeof(float), userdata);
   else
      scanline = scanline_data;

   scanline2 = scanline + result->w;

   y = off_y;
   e[n].y0 = (float) (off_y + result->h) + 1;

   while (j < result->h) {

      float scan_y_top    = y + 0.0f;
      float scan_y_bottom = y + 1.0f;
      stbtt__active_edge **step = &active;

      STBTT_memset(scanline , 0, result->w*sizeof(scanline[0]));
      STBTT_memset(scanline2, 0, (result->w+1)*sizeof(scanline[0]));

      while (*step) {
         stbtt__active_edge * z = *step;
         if (z->ey <= scan_y_top) {
            *step = z->next;
            STBTT_assert(z->direction);
            z->direction = 0;
            stbtt__hheap_free(&hh, z);
         } else {
            step = &((*step)->next);
         }
      }

      while (e->y0 <= scan_y_bottom) {
         if (e->y0 != e->y1) {
            stbtt__active_edge *z = stbtt__new_active(&hh, e, off_x, scan_y_top, userdata);
            if (z != NULL) {
               if (j == 0 && off_y != 0) {
                  if (z->ey < scan_y_top) {

                     z->ey = scan_y_top;
                  }
               }
               STBTT_assert(z->ey >= scan_y_top);

               z->next = active;
               active = z;
            }
         }
         ++e;
      }

      if (active)
         stbtt__fill_active_edges_new(scanline, scanline2+1, result->w, active, scan_y_top);

      {
         float sum = 0;
         for (i=0; i < result->w; ++i) {
            float k;
            int m;
            sum += scanline2[i];
            k = scanline[i] + sum;
            k = (float) STBTT_fabs(k)*255 + 0.5f;
            m = (int) k;
            if (m > 255) m = 255;
            result->pixels[j*result->stride + i] = (unsigned char) m;
         }
      }

      step = &active;
      while (*step) {
         stbtt__active_edge *z = *step;
         z->fx += z->fdx;
         step = &((*step)->next);
      }

      ++y;
      ++j;
   }

   stbtt__hheap_cleanup(&hh, userdata);

   if (scanline != scanline_data)
      STBTT_free(scanline, userdata);
}
#else
#error "Unrecognized value of STBTT_RASTERIZER_VERSION"
#endif

#define STBTT__COMPARE(a,b)  ((a)->y0 < (b)->y0)

static void stbtt__sort_edges_ins_sort(stbtt__edge *p, int n)
{
   int i,j;
   for (i=1; i < n; ++i) {
      stbtt__edge t = p[i], *a = &t;
      j = i;
      while (j > 0) {
         stbtt__edge *b = &p[j-1];
         int c = STBTT__COMPARE(a,b);
         if (!c) break;
         p[j] = p[j-1];
         --j;
      }
      if (i != j)
         p[j] = t;
   }
}

static void stbtt__sort_edges_quicksort(stbtt__edge *p, int n)
{

   while (n > 12) {
      stbtt__edge t;
      int c01,c12,c,m,i,j;

      m = n >> 1;
      c01 = STBTT__COMPARE(&p[0],&p[m]);
      c12 = STBTT__COMPARE(&p[m],&p[n-1]);

      if (c01 != c12) {

         int z;
         c = STBTT__COMPARE(&p[0],&p[n-1]);

         z = (c == c12) ? 0 : n-1;
         t = p[z];
         p[z] = p[m];
         p[m] = t;
      }

      t = p[0];
      p[0] = p[m];
      p[m] = t;

      i=1;
      j=n-1;
      for(;;) {

         for (;;++i) {
            if (!STBTT__COMPARE(&p[i], &p[0])) break;
         }
         for (;;--j) {
            if (!STBTT__COMPARE(&p[0], &p[j])) break;
         }

         if (i >= j) break;
         t = p[i];
         p[i] = p[j];
         p[j] = t;

         ++i;
         --j;
      }

      if (j < (n-i)) {
         stbtt__sort_edges_quicksort(p,j);
         p = p+i;
         n = n-i;
      } else {
         stbtt__sort_edges_quicksort(p+i, n-i);
         n = j;
      }
   }
}

static void stbtt__sort_edges(stbtt__edge *p, int n)
{
   stbtt__sort_edges_quicksort(p, n);
   stbtt__sort_edges_ins_sort(p, n);
}

typedef struct
{
   float x,y;
} stbtt__point;

static void stbtt__rasterize(stbtt__bitmap *result, stbtt__point *pts, int *wcount, int windings, float scale_x, float scale_y, float shift_x, float shift_y, int off_x, int off_y, int invert, void *userdata)
{
   float y_scale_inv = invert ? -scale_y : scale_y;
   stbtt__edge *e;
   int n,i,j,k,m;
#if STBTT_RASTERIZER_VERSION == 1
   int vsubsample = result->h < 8 ? 15 : 5;
#elif STBTT_RASTERIZER_VERSION == 2
   int vsubsample = 1;
#else
   #error "Unrecognized value of STBTT_RASTERIZER_VERSION"
#endif

   n = 0;
   for (i=0; i < windings; ++i)
      n += wcount[i];

   e = (stbtt__edge *) STBTT_malloc(sizeof(*e) * (n+1), userdata);
   if (e == 0) return;
   n = 0;

   m=0;
   for (i=0; i < windings; ++i) {
      stbtt__point *p = pts + m;
      m += wcount[i];
      j = wcount[i]-1;
      for (k=0; k < wcount[i]; j=k++) {
         int a=k,b=j;

         if (p[j].y == p[k].y)
            continue;

         e[n].invert = 0;
         if (invert ? p[j].y > p[k].y : p[j].y < p[k].y) {
            e[n].invert = 1;
            a=j,b=k;
         }
         e[n].x0 = p[a].x * scale_x + shift_x;
         e[n].y0 = (p[a].y * y_scale_inv + shift_y) * vsubsample;
         e[n].x1 = p[b].x * scale_x + shift_x;
         e[n].y1 = (p[b].y * y_scale_inv + shift_y) * vsubsample;
         ++n;
      }
   }

   stbtt__sort_edges(e, n);

   stbtt__rasterize_sorted_edges(result, e, n, vsubsample, off_x, off_y, userdata);

   STBTT_free(e, userdata);
}

static void stbtt__add_point(stbtt__point *points, int n, float x, float y)
{
   if (!points) return;
   points[n].x = x;
   points[n].y = y;
}

static int stbtt__tesselate_curve(stbtt__point *points, int *num_points, float x0, float y0, float x1, float y1, float x2, float y2, float objspace_flatness_squared, int n)
{

   float mx = (x0 + 2*x1 + x2)/4;
   float my = (y0 + 2*y1 + y2)/4;

   float dx = (x0+x2)/2 - mx;
   float dy = (y0+y2)/2 - my;
   if (n > 16)
      return 1;
   if (dx*dx+dy*dy > objspace_flatness_squared) {
      stbtt__tesselate_curve(points, num_points, x0,y0, (x0+x1)/2.0f,(y0+y1)/2.0f, mx,my, objspace_flatness_squared,n+1);
      stbtt__tesselate_curve(points, num_points, mx,my, (x1+x2)/2.0f,(y1+y2)/2.0f, x2,y2, objspace_flatness_squared,n+1);
   } else {
      stbtt__add_point(points, *num_points,x2,y2);
      *num_points = *num_points+1;
   }
   return 1;
}

static void stbtt__tesselate_cubic(stbtt__point *points, int *num_points, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, float objspace_flatness_squared, int n)
{

   float dx0 = x1-x0;
   float dy0 = y1-y0;
   float dx1 = x2-x1;
   float dy1 = y2-y1;
   float dx2 = x3-x2;
   float dy2 = y3-y2;
   float dx = x3-x0;
   float dy = y3-y0;
   float longlen = (float) (STBTT_sqrt(dx0*dx0+dy0*dy0)+STBTT_sqrt(dx1*dx1+dy1*dy1)+STBTT_sqrt(dx2*dx2+dy2*dy2));
   float shortlen = (float) STBTT_sqrt(dx*dx+dy*dy);
   float flatness_squared = longlen*longlen-shortlen*shortlen;

   if (n > 16)
      return;

   if (flatness_squared > objspace_flatness_squared) {
      float x01 = (x0+x1)/2;
      float y01 = (y0+y1)/2;
      float x12 = (x1+x2)/2;
      float y12 = (y1+y2)/2;
      float x23 = (x2+x3)/2;
      float y23 = (y2+y3)/2;

      float xa = (x01+x12)/2;
      float ya = (y01+y12)/2;
      float xb = (x12+x23)/2;
      float yb = (y12+y23)/2;

      float mx = (xa+xb)/2;
      float my = (ya+yb)/2;

      stbtt__tesselate_cubic(points, num_points, x0,y0, x01,y01, xa,ya, mx,my, objspace_flatness_squared,n+1);
      stbtt__tesselate_cubic(points, num_points, mx,my, xb,yb, x23,y23, x3,y3, objspace_flatness_squared,n+1);
   } else {
      stbtt__add_point(points, *num_points,x3,y3);
      *num_points = *num_points+1;
   }
}

static stbtt__point *stbtt_FlattenCurves(stbtt_vertex *vertices, int num_verts, float objspace_flatness, int **contour_lengths, int *num_contours, void *userdata)
{
   stbtt__point *points=0;
   int num_points=0;

   float objspace_flatness_squared = objspace_flatness * objspace_flatness;
   int i,n=0,start=0, pass;

   for (i=0; i < num_verts; ++i)
      if (vertices[i].type == STBTT_vmove)
         ++n;

   *num_contours = n;
   if (n == 0) return 0;

   *contour_lengths = (int *) STBTT_malloc(sizeof(**contour_lengths) * n, userdata);

   if (*contour_lengths == 0) {
      *num_contours = 0;
      return 0;
   }

   for (pass=0; pass < 2; ++pass) {
      float x=0,y=0;
      if (pass == 1) {
         points = (stbtt__point *) STBTT_malloc(num_points * sizeof(points[0]), userdata);
         if (points == NULL) goto error;
      }
      num_points = 0;
      n= -1;
      for (i=0; i < num_verts; ++i) {
         switch (vertices[i].type) {
            case STBTT_vmove:

               if (n >= 0)
                  (*contour_lengths)[n] = num_points - start;
               ++n;
               start = num_points;

               x = vertices[i].x, y = vertices[i].y;
               stbtt__add_point(points, num_points++, x,y);
               break;
            case STBTT_vline:
               x = vertices[i].x, y = vertices[i].y;
               stbtt__add_point(points, num_points++, x, y);
               break;
            case STBTT_vcurve:
               stbtt__tesselate_curve(points, &num_points, x,y,
                                        vertices[i].cx, vertices[i].cy,
                                        vertices[i].x,  vertices[i].y,
                                        objspace_flatness_squared, 0);
               x = vertices[i].x, y = vertices[i].y;
               break;
            case STBTT_vcubic:
               stbtt__tesselate_cubic(points, &num_points, x,y,
                                        vertices[i].cx, vertices[i].cy,
                                        vertices[i].cx1, vertices[i].cy1,
                                        vertices[i].x,  vertices[i].y,
                                        objspace_flatness_squared, 0);
               x = vertices[i].x, y = vertices[i].y;
               break;
         }
      }
      (*contour_lengths)[n] = num_points - start;
   }

   return points;
error:
   STBTT_free(points, userdata);
   STBTT_free(*contour_lengths, userdata);
   *contour_lengths = 0;
   *num_contours = 0;
   return NULL;
}

STBTT_DEF void stbtt_Rasterize(stbtt__bitmap *result, float flatness_in_pixels, stbtt_vertex *vertices, int num_verts, float scale_x, float scale_y, float shift_x, float shift_y, int x_off, int y_off, int invert, void *userdata)
{
   float scale            = scale_x > scale_y ? scale_y : scale_x;
   int winding_count      = 0;
   int *winding_lengths   = NULL;
   stbtt__point *windings = stbtt_FlattenCurves(vertices, num_verts, flatness_in_pixels / scale, &winding_lengths, &winding_count, userdata);
   if (windings) {
      stbtt__rasterize(result, windings, winding_lengths, winding_count, scale_x, scale_y, shift_x, shift_y, x_off, y_off, invert, userdata);
      STBTT_free(winding_lengths, userdata);
      STBTT_free(windings, userdata);
   }
}

STBTT_DEF void stbtt_FreeBitmap(unsigned char *bitmap, void *userdata)
{
   STBTT_free(bitmap, userdata);
}

STBTT_DEF unsigned char *stbtt_GetGlyphBitmapSubpixel(const stbtt_fontinfo *info, float scale_x, float scale_y, float shift_x, float shift_y, int glyph, int *width, int *height, int *xoff, int *yoff)
{
   int ix0,iy0,ix1,iy1;
   stbtt__bitmap gbm;
   stbtt_vertex *vertices;
   int num_verts = stbtt_GetGlyphShape(info, glyph, &vertices);

   if (scale_x == 0) scale_x = scale_y;
   if (scale_y == 0) {
      if (scale_x == 0) {
         STBTT_free(vertices, info->userdata);
         return NULL;
      }
      scale_y = scale_x;
   }

   stbtt_GetGlyphBitmapBoxSubpixel(info, glyph, scale_x, scale_y, shift_x, shift_y, &ix0,&iy0,&ix1,&iy1);

   gbm.w = (ix1 - ix0);
   gbm.h = (iy1 - iy0);
   gbm.pixels = NULL;

   if (width ) *width  = gbm.w;
   if (height) *height = gbm.h;
   if (xoff  ) *xoff   = ix0;
   if (yoff  ) *yoff   = iy0;

   if (gbm.w && gbm.h) {
      gbm.pixels = (unsigned char *) STBTT_malloc(gbm.w * gbm.h, info->userdata);
      if (gbm.pixels) {
         gbm.stride = gbm.w;

         stbtt_Rasterize(&gbm, 0.35f, vertices, num_verts, scale_x, scale_y, shift_x, shift_y, ix0, iy0, 1, info->userdata);
      }
   }
   STBTT_free(vertices, info->userdata);
   return gbm.pixels;
}

STBTT_DEF unsigned char *stbtt_GetGlyphBitmap(const stbtt_fontinfo *info, float scale_x, float scale_y, int glyph, int *width, int *height, int *xoff, int *yoff)
{
   return stbtt_GetGlyphBitmapSubpixel(info, scale_x, scale_y, 0.0f, 0.0f, glyph, width, height, xoff, yoff);
}

STBTT_DEF void stbtt_MakeGlyphBitmapSubpixel(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int glyph)
{
   int ix0,iy0;
   stbtt_vertex *vertices;
   int num_verts = stbtt_GetGlyphShape(info, glyph, &vertices);
   stbtt__bitmap gbm;

   stbtt_GetGlyphBitmapBoxSubpixel(info, glyph, scale_x, scale_y, shift_x, shift_y, &ix0,&iy0,0,0);
   gbm.pixels = output;
   gbm.w = out_w;
   gbm.h = out_h;
   gbm.stride = out_stride;

   if (gbm.w && gbm.h)
      stbtt_Rasterize(&gbm, 0.35f, vertices, num_verts, scale_x, scale_y, shift_x, shift_y, ix0,iy0, 1, info->userdata);

   STBTT_free(vertices, info->userdata);
}

STBTT_DEF void stbtt_MakeGlyphBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int glyph)
{
   stbtt_MakeGlyphBitmapSubpixel(info, output, out_w, out_h, out_stride, scale_x, scale_y, 0.0f,0.0f, glyph);
}

STBTT_DEF unsigned char *stbtt_GetCodepointBitmapSubpixel(const stbtt_fontinfo *info, float scale_x, float scale_y, float shift_x, float shift_y, int codepoint, int *width, int *height, int *xoff, int *yoff)
{
   return stbtt_GetGlyphBitmapSubpixel(info, scale_x, scale_y,shift_x,shift_y, stbtt_FindGlyphIndex(info,codepoint), width,height,xoff,yoff);
}

STBTT_DEF void stbtt_MakeCodepointBitmapSubpixelPrefilter(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int oversample_x, int oversample_y, float *sub_x, float *sub_y, int codepoint)
{
   stbtt_MakeGlyphBitmapSubpixelPrefilter(info, output, out_w, out_h, out_stride, scale_x, scale_y, shift_x, shift_y, oversample_x, oversample_y, sub_x, sub_y, stbtt_FindGlyphIndex(info,codepoint));
}

STBTT_DEF void stbtt_MakeCodepointBitmapSubpixel(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int codepoint)
{
   stbtt_MakeGlyphBitmapSubpixel(info, output, out_w, out_h, out_stride, scale_x, scale_y, shift_x, shift_y, stbtt_FindGlyphIndex(info,codepoint));
}

STBTT_DEF unsigned char *stbtt_GetCodepointBitmap(const stbtt_fontinfo *info, float scale_x, float scale_y, int codepoint, int *width, int *height, int *xoff, int *yoff)
{
   return stbtt_GetCodepointBitmapSubpixel(info, scale_x, scale_y, 0.0f,0.0f, codepoint, width,height,xoff,yoff);
}

STBTT_DEF void stbtt_MakeCodepointBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint)
{
   stbtt_MakeCodepointBitmapSubpixel(info, output, out_w, out_h, out_stride, scale_x, scale_y, 0.0f,0.0f, codepoint);
}

static int stbtt_BakeFontBitmap_internal(unsigned char *data, int offset,
                                float pixel_height,
                                unsigned char *pixels, int pw, int ph,
                                int first_char, int num_chars,
                                stbtt_bakedchar *chardata)
{
   float scale;
   int x,y,bottom_y, i;
   stbtt_fontinfo f;
   f.userdata = NULL;
   if (!stbtt_InitFont(&f, data, offset))
      return -1;
   STBTT_memset(pixels, 0, pw*ph);
   x=y=1;
   bottom_y = 1;

   scale = stbtt_ScaleForPixelHeight(&f, pixel_height);

   for (i=0; i < num_chars; ++i) {
      int advance, lsb, x0,y0,x1,y1,gw,gh;
      int g = stbtt_FindGlyphIndex(&f, first_char + i);
      stbtt_GetGlyphHMetrics(&f, g, &advance, &lsb);
      stbtt_GetGlyphBitmapBox(&f, g, scale,scale, &x0,&y0,&x1,&y1);
      gw = x1-x0;
      gh = y1-y0;
      if (x + gw + 1 >= pw)
         y = bottom_y, x = 1;
      if (y + gh + 1 >= ph)
         return -i;
      STBTT_assert(x+gw < pw);
      STBTT_assert(y+gh < ph);
      stbtt_MakeGlyphBitmap(&f, pixels+x+y*pw, gw,gh,pw, scale,scale, g);
      chardata[i].x0 = (stbtt_int16) x;
      chardata[i].y0 = (stbtt_int16) y;
      chardata[i].x1 = (stbtt_int16) (x + gw);
      chardata[i].y1 = (stbtt_int16) (y + gh);
      chardata[i].xadvance = scale * advance;
      chardata[i].xoff     = (float) x0;
      chardata[i].yoff     = (float) y0;
      x = x + gw + 1;
      if (y+gh+1 > bottom_y)
         bottom_y = y+gh+1;
   }
   return bottom_y;
}

STBTT_DEF void stbtt_GetBakedQuad(const stbtt_bakedchar *chardata, int pw, int ph, int char_index, float *xpos, float *ypos, stbtt_aligned_quad *q, int opengl_fillrule)
{
   float d3d_bias = opengl_fillrule ? 0 : -0.5f;
   float ipw = 1.0f / pw, iph = 1.0f / ph;
   const stbtt_bakedchar *b = chardata + char_index;
   int round_x = STBTT_ifloor((*xpos + b->xoff) + 0.5f);
   int round_y = STBTT_ifloor((*ypos + b->yoff) + 0.5f);

   q->x0 = round_x + d3d_bias;
   q->y0 = round_y + d3d_bias;
   q->x1 = round_x + b->x1 - b->x0 + d3d_bias;
   q->y1 = round_y + b->y1 - b->y0 + d3d_bias;

   q->s0 = b->x0 * ipw;
   q->t0 = b->y0 * iph;
   q->s1 = b->x1 * ipw;
   q->t1 = b->y1 * iph;

   *xpos += b->xadvance;
}

#ifndef STB_RECT_PACK_VERSION

typedef int stbrp_coord;

typedef struct
{
   int width,height;
   int x,y,bottom_y;
} stbrp_context;

typedef struct
{
   unsigned char x;
} stbrp_node;

struct stbrp_rect
{
   stbrp_coord x,y;
   int id,w,h,was_packed;
};

static void stbrp_init_target(stbrp_context *con, int pw, int ph, stbrp_node *nodes, int num_nodes)
{
   con->width  = pw;
   con->height = ph;
   con->x = 0;
   con->y = 0;
   con->bottom_y = 0;
   STBTT__NOTUSED(nodes);
   STBTT__NOTUSED(num_nodes);
}

static void stbrp_pack_rects(stbrp_context *con, stbrp_rect *rects, int num_rects)
{
   int i;
   for (i=0; i < num_rects; ++i) {
      if (con->x + rects[i].w > con->width) {
         con->x = 0;
         con->y = con->bottom_y;
      }
      if (con->y + rects[i].h > con->height)
         break;
      rects[i].x = con->x;
      rects[i].y = con->y;
      rects[i].was_packed = 1;
      con->x += rects[i].w;
      if (con->y + rects[i].h > con->bottom_y)
         con->bottom_y = con->y + rects[i].h;
   }
   for (   ; i < num_rects; ++i)
      rects[i].was_packed = 0;
}
#endif

STBTT_DEF int stbtt_PackBegin(stbtt_pack_context *spc, unsigned char *pixels, int pw, int ph, int stride_in_bytes, int padding, void *alloc_context)
{
   stbrp_context *context = (stbrp_context *) STBTT_malloc(sizeof(*context)            ,alloc_context);
   int            num_nodes = pw - padding;
   stbrp_node    *nodes   = (stbrp_node    *) STBTT_malloc(sizeof(*nodes  ) * num_nodes,alloc_context);

   if (context == NULL || nodes == NULL) {
      if (context != NULL) STBTT_free(context, alloc_context);
      if (nodes   != NULL) STBTT_free(nodes  , alloc_context);
      return 0;
   }

   spc->user_allocator_context = alloc_context;
   spc->width = pw;
   spc->height = ph;
   spc->pixels = pixels;
   spc->pack_info = context;
   spc->nodes = nodes;
   spc->padding = padding;
   spc->stride_in_bytes = stride_in_bytes != 0 ? stride_in_bytes : pw;
   spc->h_oversample = 1;
   spc->v_oversample = 1;
   spc->skip_missing = 0;

   stbrp_init_target(context, pw-padding, ph-padding, nodes, num_nodes);

   if (pixels)
      STBTT_memset(pixels, 0, pw*ph);

   return 1;
}

STBTT_DEF void stbtt_PackEnd  (stbtt_pack_context *spc)
{
   STBTT_free(spc->nodes    , spc->user_allocator_context);
   STBTT_free(spc->pack_info, spc->user_allocator_context);
}

STBTT_DEF void stbtt_PackSetOversampling(stbtt_pack_context *spc, unsigned int h_oversample, unsigned int v_oversample)
{
   STBTT_assert(h_oversample <= STBTT_MAX_OVERSAMPLE);
   STBTT_assert(v_oversample <= STBTT_MAX_OVERSAMPLE);
   if (h_oversample <= STBTT_MAX_OVERSAMPLE)
      spc->h_oversample = h_oversample;
   if (v_oversample <= STBTT_MAX_OVERSAMPLE)
      spc->v_oversample = v_oversample;
}

STBTT_DEF void stbtt_PackSetSkipMissingCodepoints(stbtt_pack_context *spc, int skip)
{
   spc->skip_missing = skip;
}

#define STBTT__OVER_MASK  (STBTT_MAX_OVERSAMPLE-1)

static void stbtt__h_prefilter(unsigned char *pixels, int w, int h, int stride_in_bytes, unsigned int kernel_width)
{
   unsigned char buffer[STBTT_MAX_OVERSAMPLE];
   int safe_w = w - kernel_width;
   int j;
   STBTT_memset(buffer, 0, STBTT_MAX_OVERSAMPLE);
   for (j=0; j < h; ++j) {
      int i;
      unsigned int total;
      STBTT_memset(buffer, 0, kernel_width);

      total = 0;

      switch (kernel_width) {
         case 2:
            for (i=0; i <= safe_w; ++i) {
               total += pixels[i] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i];
               pixels[i] = (unsigned char) (total / 2);
            }
            break;
         case 3:
            for (i=0; i <= safe_w; ++i) {
               total += pixels[i] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i];
               pixels[i] = (unsigned char) (total / 3);
            }
            break;
         case 4:
            for (i=0; i <= safe_w; ++i) {
               total += pixels[i] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i];
               pixels[i] = (unsigned char) (total / 4);
            }
            break;
         case 5:
            for (i=0; i <= safe_w; ++i) {
               total += pixels[i] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i];
               pixels[i] = (unsigned char) (total / 5);
            }
            break;
         default:
            for (i=0; i <= safe_w; ++i) {
               total += pixels[i] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i];
               pixels[i] = (unsigned char) (total / kernel_width);
            }
            break;
      }

      for (; i < w; ++i) {
         STBTT_assert(pixels[i] == 0);
         total -= buffer[i & STBTT__OVER_MASK];
         pixels[i] = (unsigned char) (total / kernel_width);
      }

      pixels += stride_in_bytes;
   }
}

static void stbtt__v_prefilter(unsigned char *pixels, int w, int h, int stride_in_bytes, unsigned int kernel_width)
{
   unsigned char buffer[STBTT_MAX_OVERSAMPLE];
   int safe_h = h - kernel_width;
   int j;
   STBTT_memset(buffer, 0, STBTT_MAX_OVERSAMPLE);
   for (j=0; j < w; ++j) {
      int i;
      unsigned int total;
      STBTT_memset(buffer, 0, kernel_width);

      total = 0;

      switch (kernel_width) {
         case 2:
            for (i=0; i <= safe_h; ++i) {
               total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
               pixels[i*stride_in_bytes] = (unsigned char) (total / 2);
            }
            break;
         case 3:
            for (i=0; i <= safe_h; ++i) {
               total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
               pixels[i*stride_in_bytes] = (unsigned char) (total / 3);
            }
            break;
         case 4:
            for (i=0; i <= safe_h; ++i) {
               total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
               pixels[i*stride_in_bytes] = (unsigned char) (total / 4);
            }
            break;
         case 5:
            for (i=0; i <= safe_h; ++i) {
               total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
               pixels[i*stride_in_bytes] = (unsigned char) (total / 5);
            }
            break;
         default:
            for (i=0; i <= safe_h; ++i) {
               total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
               buffer[(i+kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
               pixels[i*stride_in_bytes] = (unsigned char) (total / kernel_width);
            }
            break;
      }

      for (; i < h; ++i) {
         STBTT_assert(pixels[i*stride_in_bytes] == 0);
         total -= buffer[i & STBTT__OVER_MASK];
         pixels[i*stride_in_bytes] = (unsigned char) (total / kernel_width);
      }

      pixels += 1;
   }
}

static float stbtt__oversample_shift(int oversample)
{
   if (!oversample)
      return 0.0f;

   return (float)-(oversample - 1) / (2.0f * (float)oversample);
}

STBTT_DEF int stbtt_PackFontRangesGatherRects(stbtt_pack_context *spc, const stbtt_fontinfo *info, stbtt_pack_range *ranges, int num_ranges, stbrp_rect *rects)
{
   int i,j,k;
   int missing_glyph_added = 0;

   k=0;
   for (i=0; i < num_ranges; ++i) {
      float fh = ranges[i].font_size;
      float scale = fh > 0 ? stbtt_ScaleForPixelHeight(info, fh) : stbtt_ScaleForMappingEmToPixels(info, -fh);
      ranges[i].h_oversample = (unsigned char) spc->h_oversample;
      ranges[i].v_oversample = (unsigned char) spc->v_oversample;
      for (j=0; j < ranges[i].num_chars; ++j) {
         int x0,y0,x1,y1;
         int codepoint = ranges[i].array_of_unicode_codepoints == NULL ? ranges[i].first_unicode_codepoint_in_range + j : ranges[i].array_of_unicode_codepoints[j];
         int glyph = stbtt_FindGlyphIndex(info, codepoint);
         if (glyph == 0 && (spc->skip_missing || missing_glyph_added)) {
            rects[k].w = rects[k].h = 0;
         } else {
            stbtt_GetGlyphBitmapBoxSubpixel(info,glyph,
                                            scale * spc->h_oversample,
                                            scale * spc->v_oversample,
                                            0,0,
                                            &x0,&y0,&x1,&y1);
            rects[k].w = (stbrp_coord) (x1-x0 + spc->padding + spc->h_oversample-1);
            rects[k].h = (stbrp_coord) (y1-y0 + spc->padding + spc->v_oversample-1);
            if (glyph == 0)
               missing_glyph_added = 1;
         }
         ++k;
      }
   }

   return k;
}

STBTT_DEF void stbtt_MakeGlyphBitmapSubpixelPrefilter(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int prefilter_x, int prefilter_y, float *sub_x, float *sub_y, int glyph)
{
   stbtt_MakeGlyphBitmapSubpixel(info,
                                 output,
                                 out_w - (prefilter_x - 1),
                                 out_h - (prefilter_y - 1),
                                 out_stride,
                                 scale_x,
                                 scale_y,
                                 shift_x,
                                 shift_y,
                                 glyph);

   if (prefilter_x > 1)
      stbtt__h_prefilter(output, out_w, out_h, out_stride, prefilter_x);

   if (prefilter_y > 1)
      stbtt__v_prefilter(output, out_w, out_h, out_stride, prefilter_y);

   *sub_x = stbtt__oversample_shift(prefilter_x);
   *sub_y = stbtt__oversample_shift(prefilter_y);
}

STBTT_DEF int stbtt_PackFontRangesRenderIntoRects(stbtt_pack_context *spc, const stbtt_fontinfo *info, stbtt_pack_range *ranges, int num_ranges, stbrp_rect *rects)
{
   int i,j,k, missing_glyph = -1, return_value = 1;

   int old_h_over = spc->h_oversample;
   int old_v_over = spc->v_oversample;

   k = 0;
   for (i=0; i < num_ranges; ++i) {
      float fh = ranges[i].font_size;
      float scale = fh > 0 ? stbtt_ScaleForPixelHeight(info, fh) : stbtt_ScaleForMappingEmToPixels(info, -fh);
      float recip_h,recip_v,sub_x,sub_y;
      spc->h_oversample = ranges[i].h_oversample;
      spc->v_oversample = ranges[i].v_oversample;
      recip_h = 1.0f / spc->h_oversample;
      recip_v = 1.0f / spc->v_oversample;
      sub_x = stbtt__oversample_shift(spc->h_oversample);
      sub_y = stbtt__oversample_shift(spc->v_oversample);
      for (j=0; j < ranges[i].num_chars; ++j) {
         stbrp_rect *r = &rects[k];
         if (r->was_packed && r->w != 0 && r->h != 0) {
            stbtt_packedchar *bc = &ranges[i].chardata_for_range[j];
            int advance, lsb, x0,y0,x1,y1;
            int codepoint = ranges[i].array_of_unicode_codepoints == NULL ? ranges[i].first_unicode_codepoint_in_range + j : ranges[i].array_of_unicode_codepoints[j];
            int glyph = stbtt_FindGlyphIndex(info, codepoint);
            stbrp_coord pad = (stbrp_coord) spc->padding;

            r->x += pad;
            r->y += pad;
            r->w -= pad;
            r->h -= pad;
            stbtt_GetGlyphHMetrics(info, glyph, &advance, &lsb);
            stbtt_GetGlyphBitmapBox(info, glyph,
                                    scale * spc->h_oversample,
                                    scale * spc->v_oversample,
                                    &x0,&y0,&x1,&y1);
            stbtt_MakeGlyphBitmapSubpixel(info,
                                          spc->pixels + r->x + r->y*spc->stride_in_bytes,
                                          r->w - spc->h_oversample+1,
                                          r->h - spc->v_oversample+1,
                                          spc->stride_in_bytes,
                                          scale * spc->h_oversample,
                                          scale * spc->v_oversample,
                                          0,0,
                                          glyph);

            if (spc->h_oversample > 1)
               stbtt__h_prefilter(spc->pixels + r->x + r->y*spc->stride_in_bytes,
                                  r->w, r->h, spc->stride_in_bytes,
                                  spc->h_oversample);

            if (spc->v_oversample > 1)
               stbtt__v_prefilter(spc->pixels + r->x + r->y*spc->stride_in_bytes,
                                  r->w, r->h, spc->stride_in_bytes,
                                  spc->v_oversample);

            bc->x0       = (stbtt_int16)  r->x;
            bc->y0       = (stbtt_int16)  r->y;
            bc->x1       = (stbtt_int16) (r->x + r->w);
            bc->y1       = (stbtt_int16) (r->y + r->h);
            bc->xadvance =                scale * advance;
            bc->xoff     =       (float)  x0 * recip_h + sub_x;
            bc->yoff     =       (float)  y0 * recip_v + sub_y;
            bc->xoff2    =                (x0 + r->w) * recip_h + sub_x;
            bc->yoff2    =                (y0 + r->h) * recip_v + sub_y;

            if (glyph == 0)
               missing_glyph = j;
         } else if (spc->skip_missing) {
            return_value = 0;
         } else if (r->was_packed && r->w == 0 && r->h == 0 && missing_glyph >= 0) {
            ranges[i].chardata_for_range[j] = ranges[i].chardata_for_range[missing_glyph];
         } else {
            return_value = 0;
         }

         ++k;
      }
   }

   spc->h_oversample = old_h_over;
   spc->v_oversample = old_v_over;

   return return_value;
}

STBTT_DEF void stbtt_PackFontRangesPackRects(stbtt_pack_context *spc, stbrp_rect *rects, int num_rects)
{
   stbrp_pack_rects((stbrp_context *) spc->pack_info, rects, num_rects);
}

STBTT_DEF int stbtt_PackFontRanges(stbtt_pack_context *spc, const unsigned char *fontdata, int font_index, stbtt_pack_range *ranges, int num_ranges)
{
   stbtt_fontinfo info;
   int i,j,n, return_value = 1;

   stbrp_rect    *rects;

   for (i=0; i < num_ranges; ++i)
      for (j=0; j < ranges[i].num_chars; ++j)
         ranges[i].chardata_for_range[j].x0 =
         ranges[i].chardata_for_range[j].y0 =
         ranges[i].chardata_for_range[j].x1 =
         ranges[i].chardata_for_range[j].y1 = 0;

   n = 0;
   for (i=0; i < num_ranges; ++i)
      n += ranges[i].num_chars;

   rects = (stbrp_rect *) STBTT_malloc(sizeof(*rects) * n, spc->user_allocator_context);
   if (rects == NULL)
      return 0;

   info.userdata = spc->user_allocator_context;
   stbtt_InitFont(&info, fontdata, stbtt_GetFontOffsetForIndex(fontdata,font_index));

   n = stbtt_PackFontRangesGatherRects(spc, &info, ranges, num_ranges, rects);

   stbtt_PackFontRangesPackRects(spc, rects, n);

   return_value = stbtt_PackFontRangesRenderIntoRects(spc, &info, ranges, num_ranges, rects);

   STBTT_free(rects, spc->user_allocator_context);
   return return_value;
}

STBTT_DEF int stbtt_PackFontRange(stbtt_pack_context *spc, const unsigned char *fontdata, int font_index, float font_size,
            int first_unicode_codepoint_in_range, int num_chars_in_range, stbtt_packedchar *chardata_for_range)
{
   stbtt_pack_range range;
   range.first_unicode_codepoint_in_range = first_unicode_codepoint_in_range;
   range.array_of_unicode_codepoints = NULL;
   range.num_chars                   = num_chars_in_range;
   range.chardata_for_range          = chardata_for_range;
   range.font_size                   = font_size;
   return stbtt_PackFontRanges(spc, fontdata, font_index, &range, 1);
}

STBTT_DEF void stbtt_GetScaledFontVMetrics(const unsigned char *fontdata, int index, float size, float *ascent, float *descent, float *lineGap)
{
   int i_ascent, i_descent, i_lineGap;
   float scale;
   stbtt_fontinfo info;
   stbtt_InitFont(&info, fontdata, stbtt_GetFontOffsetForIndex(fontdata, index));
   scale = size > 0 ? stbtt_ScaleForPixelHeight(&info, size) : stbtt_ScaleForMappingEmToPixels(&info, -size);
   stbtt_GetFontVMetrics(&info, &i_ascent, &i_descent, &i_lineGap);
   *ascent  = (float) i_ascent  * scale;
   *descent = (float) i_descent * scale;
   *lineGap = (float) i_lineGap * scale;
}

STBTT_DEF void stbtt_GetPackedQuad(const stbtt_packedchar *chardata, int pw, int ph, int char_index, float *xpos, float *ypos, stbtt_aligned_quad *q, int align_to_integer)
{
   float ipw = 1.0f / pw, iph = 1.0f / ph;
   const stbtt_packedchar *b = chardata + char_index;

   if (align_to_integer) {
      float x = (float) STBTT_ifloor((*xpos + b->xoff) + 0.5f);
      float y = (float) STBTT_ifloor((*ypos + b->yoff) + 0.5f);
      q->x0 = x;
      q->y0 = y;
      q->x1 = x + b->xoff2 - b->xoff;
      q->y1 = y + b->yoff2 - b->yoff;
   } else {
      q->x0 = *xpos + b->xoff;
      q->y0 = *ypos + b->yoff;
      q->x1 = *xpos + b->xoff2;
      q->y1 = *ypos + b->yoff2;
   }

   q->s0 = b->x0 * ipw;
   q->t0 = b->y0 * iph;
   q->s1 = b->x1 * ipw;
   q->t1 = b->y1 * iph;

   *xpos += b->xadvance;
}

#define STBTT_min(a,b)  ((a) < (b) ? (a) : (b))
#define STBTT_max(a,b)  ((a) < (b) ? (b) : (a))

static int stbtt__ray_intersect_bezier(float orig[2], float ray[2], float q0[2], float q1[2], float q2[2], float hits[2][2])
{
   float q0perp = q0[1]*ray[0] - q0[0]*ray[1];
   float q1perp = q1[1]*ray[0] - q1[0]*ray[1];
   float q2perp = q2[1]*ray[0] - q2[0]*ray[1];
   float roperp = orig[1]*ray[0] - orig[0]*ray[1];

   float a = q0perp - 2*q1perp + q2perp;
   float b = q1perp - q0perp;
   float c = q0perp - roperp;

   float s0 = 0., s1 = 0.;
   int num_s = 0;

   if (a != 0.0) {
      float discr = b*b - a*c;
      if (discr > 0.0) {
         float rcpna = -1 / a;
         float d = (float) STBTT_sqrt(discr);
         s0 = (b+d) * rcpna;
         s1 = (b-d) * rcpna;
         if (s0 >= 0.0 && s0 <= 1.0)
            num_s = 1;
         if (d > 0.0 && s1 >= 0.0 && s1 <= 1.0) {
            if (num_s == 0) s0 = s1;
            ++num_s;
         }
      }
   } else {

      s0 = c / (-2 * b);
      if (s0 >= 0.0 && s0 <= 1.0)
         num_s = 1;
   }

   if (num_s == 0)
      return 0;
   else {
      float rcp_len2 = 1 / (ray[0]*ray[0] + ray[1]*ray[1]);
      float rayn_x = ray[0] * rcp_len2, rayn_y = ray[1] * rcp_len2;

      float q0d =   q0[0]*rayn_x +   q0[1]*rayn_y;
      float q1d =   q1[0]*rayn_x +   q1[1]*rayn_y;
      float q2d =   q2[0]*rayn_x +   q2[1]*rayn_y;
      float rod = orig[0]*rayn_x + orig[1]*rayn_y;

      float q10d = q1d - q0d;
      float q20d = q2d - q0d;
      float q0rd = q0d - rod;

      hits[0][0] = q0rd + s0*(2.0f - 2.0f*s0)*q10d + s0*s0*q20d;
      hits[0][1] = a*s0+b;

      if (num_s > 1) {
         hits[1][0] = q0rd + s1*(2.0f - 2.0f*s1)*q10d + s1*s1*q20d;
         hits[1][1] = a*s1+b;
         return 2;
      } else {
         return 1;
      }
   }
}

static int equal(float *a, float *b)
{
   return (a[0] == b[0] && a[1] == b[1]);
}

static int stbtt__compute_crossings_x(float x, float y, int nverts, stbtt_vertex *verts)
{
   int i;
   float orig[2], ray[2] = { 1, 0 };
   float y_frac;
   int winding = 0;

   y_frac = (float) STBTT_fmod(y, 1.0f);
   if (y_frac < 0.01f)
      y += 0.01f;
   else if (y_frac > 0.99f)
      y -= 0.01f;

   orig[0] = x;
   orig[1] = y;

   for (i=0; i < nverts; ++i) {
      if (verts[i].type == STBTT_vline) {
         int x0 = (int) verts[i-1].x, y0 = (int) verts[i-1].y;
         int x1 = (int) verts[i  ].x, y1 = (int) verts[i  ].y;
         if (y > STBTT_min(y0,y1) && y < STBTT_max(y0,y1) && x > STBTT_min(x0,x1)) {
            float x_inter = (y - y0) / (y1 - y0) * (x1-x0) + x0;
            if (x_inter < x)
               winding += (y0 < y1) ? 1 : -1;
         }
      }
      if (verts[i].type == STBTT_vcurve) {
         int x0 = (int) verts[i-1].x , y0 = (int) verts[i-1].y ;
         int x1 = (int) verts[i  ].cx, y1 = (int) verts[i  ].cy;
         int x2 = (int) verts[i  ].x , y2 = (int) verts[i  ].y ;
         int ax = STBTT_min(x0,STBTT_min(x1,x2)), ay = STBTT_min(y0,STBTT_min(y1,y2));
         int by = STBTT_max(y0,STBTT_max(y1,y2));
         if (y > ay && y < by && x > ax) {
            float q0[2],q1[2],q2[2];
            float hits[2][2];
            q0[0] = (float)x0;
            q0[1] = (float)y0;
            q1[0] = (float)x1;
            q1[1] = (float)y1;
            q2[0] = (float)x2;
            q2[1] = (float)y2;
            if (equal(q0,q1) || equal(q1,q2)) {
               x0 = (int)verts[i-1].x;
               y0 = (int)verts[i-1].y;
               x1 = (int)verts[i  ].x;
               y1 = (int)verts[i  ].y;
               if (y > STBTT_min(y0,y1) && y < STBTT_max(y0,y1) && x > STBTT_min(x0,x1)) {
                  float x_inter = (y - y0) / (y1 - y0) * (x1-x0) + x0;
                  if (x_inter < x)
                     winding += (y0 < y1) ? 1 : -1;
               }
            } else {
               int num_hits = stbtt__ray_intersect_bezier(orig, ray, q0, q1, q2, hits);
               if (num_hits >= 1)
                  if (hits[0][0] < 0)
                     winding += (hits[0][1] < 0 ? -1 : 1);
               if (num_hits >= 2)
                  if (hits[1][0] < 0)
                     winding += (hits[1][1] < 0 ? -1 : 1);
            }
         }
      }
   }
   return winding;
}

static float stbtt__cuberoot( float x )
{
   if (x<0)
      return -(float) STBTT_pow(-x,1.0f/3.0f);
   else
      return  (float) STBTT_pow( x,1.0f/3.0f);
}

static int stbtt__solve_cubic(float a, float b, float c, float* r)
{
   float s = -a / 3;
   float p = b - a*a / 3;
   float q = a * (2*a*a - 9*b) / 27 + c;
   float p3 = p*p*p;
   float d = q*q + 4*p3 / 27;
   if (d >= 0) {
      float z = (float) STBTT_sqrt(d);
      float u = (-q + z) / 2;
      float v = (-q - z) / 2;
      u = stbtt__cuberoot(u);
      v = stbtt__cuberoot(v);
      r[0] = s + u + v;
      return 1;
   } else {
      float u = (float) STBTT_sqrt(-p/3);
      float v = (float) STBTT_acos(-STBTT_sqrt(-27/p3) * q / 2) / 3;
      float m = (float) STBTT_cos(v);
      float n = (float) STBTT_cos(v-3.141592/2)*1.732050808f;
      r[0] = s + u * 2 * m;
      r[1] = s - u * (m + n);
      r[2] = s - u * (m - n);

      return 3;
   }
}

STBTT_DEF unsigned char * stbtt_GetGlyphSDF(const stbtt_fontinfo *info, float scale, int glyph, int padding, unsigned char onedge_value, float pixel_dist_scale, int *width, int *height, int *xoff, int *yoff)
{
   float scale_x = scale, scale_y = scale;
   int ix0,iy0,ix1,iy1;
   int w,h;
   unsigned char *data;

   if (scale == 0) return NULL;

   stbtt_GetGlyphBitmapBoxSubpixel(info, glyph, scale, scale, 0.0f,0.0f, &ix0,&iy0,&ix1,&iy1);

   if (ix0 == ix1 || iy0 == iy1)
      return NULL;

   ix0 -= padding;
   iy0 -= padding;
   ix1 += padding;
   iy1 += padding;

   w = (ix1 - ix0);
   h = (iy1 - iy0);

   if (width ) *width  = w;
   if (height) *height = h;
   if (xoff  ) *xoff   = ix0;
   if (yoff  ) *yoff   = iy0;

   scale_y = -scale_y;

   {
      int x,y,i,j;
      float *precompute;
      stbtt_vertex *verts;
      int num_verts = stbtt_GetGlyphShape(info, glyph, &verts);
      data = (unsigned char *) STBTT_malloc(w * h, info->userdata);
      precompute = (float *) STBTT_malloc(num_verts * sizeof(float), info->userdata);

      for (i=0,j=num_verts-1; i < num_verts; j=i++) {
         if (verts[i].type == STBTT_vline) {
            float x0 = verts[i].x*scale_x, y0 = verts[i].y*scale_y;
            float x1 = verts[j].x*scale_x, y1 = verts[j].y*scale_y;
            float dist = (float) STBTT_sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
            precompute[i] = (dist == 0) ? 0.0f : 1.0f / dist;
         } else if (verts[i].type == STBTT_vcurve) {
            float x2 = verts[j].x *scale_x, y2 = verts[j].y *scale_y;
            float x1 = verts[i].cx*scale_x, y1 = verts[i].cy*scale_y;
            float x0 = verts[i].x *scale_x, y0 = verts[i].y *scale_y;
            float bx = x0 - 2*x1 + x2, by = y0 - 2*y1 + y2;
            float len2 = bx*bx + by*by;
            if (len2 != 0.0f)
               precompute[i] = 1.0f / (bx*bx + by*by);
            else
               precompute[i] = 0.0f;
         } else
            precompute[i] = 0.0f;
      }

      for (y=iy0; y < iy1; ++y) {
         for (x=ix0; x < ix1; ++x) {
            float val;
            float min_dist = 999999.0f;
            float sx = (float) x + 0.5f;
            float sy = (float) y + 0.5f;
            float x_gspace = (sx / scale_x);
            float y_gspace = (sy / scale_y);

            int winding = stbtt__compute_crossings_x(x_gspace, y_gspace, num_verts, verts);

            for (i=0; i < num_verts; ++i) {
               float x0 = verts[i].x*scale_x, y0 = verts[i].y*scale_y;

               if (verts[i].type == STBTT_vline && precompute[i] != 0.0f) {
                  float x1 = verts[i-1].x*scale_x, y1 = verts[i-1].y*scale_y;

                  float dist,dist2 = (x0-sx)*(x0-sx) + (y0-sy)*(y0-sy);
                  if (dist2 < min_dist*min_dist)
                     min_dist = (float) STBTT_sqrt(dist2);

                  dist = (float) STBTT_fabs((x1-x0)*(y0-sy) - (y1-y0)*(x0-sx)) * precompute[i];
                  STBTT_assert(i != 0);
                  if (dist < min_dist) {

                     float dx = x1-x0, dy = y1-y0;
                     float px = x0-sx, py = y0-sy;

                     float t = -(px*dx + py*dy) / (dx*dx + dy*dy);
                     if (t >= 0.0f && t <= 1.0f)
                        min_dist = dist;
                  }
               } else if (verts[i].type == STBTT_vcurve) {
                  float x2 = verts[i-1].x *scale_x, y2 = verts[i-1].y *scale_y;
                  float x1 = verts[i  ].cx*scale_x, y1 = verts[i  ].cy*scale_y;
                  float box_x0 = STBTT_min(STBTT_min(x0,x1),x2);
                  float box_y0 = STBTT_min(STBTT_min(y0,y1),y2);
                  float box_x1 = STBTT_max(STBTT_max(x0,x1),x2);
                  float box_y1 = STBTT_max(STBTT_max(y0,y1),y2);

                  if (sx > box_x0-min_dist && sx < box_x1+min_dist && sy > box_y0-min_dist && sy < box_y1+min_dist) {
                     int num=0;
                     float ax = x1-x0, ay = y1-y0;
                     float bx = x0 - 2*x1 + x2, by = y0 - 2*y1 + y2;
                     float mx = x0 - sx, my = y0 - sy;
                     float res[3] = {0.f,0.f,0.f};
                     float px,py,t,it,dist2;
                     float a_inv = precompute[i];
                     if (a_inv == 0.0) {
                        float a = 3*(ax*bx + ay*by);
                        float b = 2*(ax*ax + ay*ay) + (mx*bx+my*by);
                        float c = mx*ax+my*ay;
                        if (a == 0.0) {
                           if (b != 0.0) {
                              res[num++] = -c/b;
                           }
                        } else {
                           float discriminant = b*b - 4*a*c;
                           if (discriminant < 0)
                              num = 0;
                           else {
                              float root = (float) STBTT_sqrt(discriminant);
                              res[0] = (-b - root)/(2*a);
                              res[1] = (-b + root)/(2*a);
                              num = 2;
                           }
                        }
                     } else {
                        float b = 3*(ax*bx + ay*by) * a_inv;
                        float c = (2*(ax*ax + ay*ay) + (mx*bx+my*by)) * a_inv;
                        float d = (mx*ax+my*ay) * a_inv;
                        num = stbtt__solve_cubic(b, c, d, res);
                     }
                     dist2 = (x0-sx)*(x0-sx) + (y0-sy)*(y0-sy);
                     if (dist2 < min_dist*min_dist)
                        min_dist = (float) STBTT_sqrt(dist2);

                     if (num >= 1 && res[0] >= 0.0f && res[0] <= 1.0f) {
                        t = res[0], it = 1.0f - t;
                        px = it*it*x0 + 2*t*it*x1 + t*t*x2;
                        py = it*it*y0 + 2*t*it*y1 + t*t*y2;
                        dist2 = (px-sx)*(px-sx) + (py-sy)*(py-sy);
                        if (dist2 < min_dist * min_dist)
                           min_dist = (float) STBTT_sqrt(dist2);
                     }
                     if (num >= 2 && res[1] >= 0.0f && res[1] <= 1.0f) {
                        t = res[1], it = 1.0f - t;
                        px = it*it*x0 + 2*t*it*x1 + t*t*x2;
                        py = it*it*y0 + 2*t*it*y1 + t*t*y2;
                        dist2 = (px-sx)*(px-sx) + (py-sy)*(py-sy);
                        if (dist2 < min_dist * min_dist)
                           min_dist = (float) STBTT_sqrt(dist2);
                     }
                     if (num >= 3 && res[2] >= 0.0f && res[2] <= 1.0f) {
                        t = res[2], it = 1.0f - t;
                        px = it*it*x0 + 2*t*it*x1 + t*t*x2;
                        py = it*it*y0 + 2*t*it*y1 + t*t*y2;
                        dist2 = (px-sx)*(px-sx) + (py-sy)*(py-sy);
                        if (dist2 < min_dist * min_dist)
                           min_dist = (float) STBTT_sqrt(dist2);
                     }
                  }
               }
            }
            if (winding == 0)
               min_dist = -min_dist;
            val = onedge_value + pixel_dist_scale * min_dist;
            if (val < 0)
               val = 0;
            else if (val > 255)
               val = 255;
            data[(y-iy0)*w+(x-ix0)] = (unsigned char) val;
         }
      }
      STBTT_free(precompute, info->userdata);
      STBTT_free(verts, info->userdata);
   }
   return data;
}

STBTT_DEF unsigned char * stbtt_GetCodepointSDF(const stbtt_fontinfo *info, float scale, int codepoint, int padding, unsigned char onedge_value, float pixel_dist_scale, int *width, int *height, int *xoff, int *yoff)
{
   return stbtt_GetGlyphSDF(info, scale, stbtt_FindGlyphIndex(info, codepoint), padding, onedge_value, pixel_dist_scale, width, height, xoff, yoff);
}

STBTT_DEF void stbtt_FreeSDF(unsigned char *bitmap, void *userdata)
{
   STBTT_free(bitmap, userdata);
}

static stbtt_int32 stbtt__CompareUTF8toUTF16_bigendian_prefix(stbtt_uint8 *s1, stbtt_int32 len1, stbtt_uint8 *s2, stbtt_int32 len2)
{
   stbtt_int32 i=0;

   while (len2) {
      stbtt_uint16 ch = s2[0]*256 + s2[1];
      if (ch < 0x80) {
         if (i >= len1) return -1;
         if (s1[i++] != ch) return -1;
      } else if (ch < 0x800) {
         if (i+1 >= len1) return -1;
         if (s1[i++] != 0xc0 + (ch >> 6)) return -1;
         if (s1[i++] != 0x80 + (ch & 0x3f)) return -1;
      } else if (ch >= 0xd800 && ch < 0xdc00) {
         stbtt_uint32 c;
         stbtt_uint16 ch2 = s2[2]*256 + s2[3];
         if (i+3 >= len1) return -1;
         c = ((ch - 0xd800) << 10) + (ch2 - 0xdc00) + 0x10000;
         if (s1[i++] != 0xf0 + (c >> 18)) return -1;
         if (s1[i++] != 0x80 + ((c >> 12) & 0x3f)) return -1;
         if (s1[i++] != 0x80 + ((c >>  6) & 0x3f)) return -1;
         if (s1[i++] != 0x80 + ((c      ) & 0x3f)) return -1;
         s2 += 2;
         len2 -= 2;
      } else if (ch >= 0xdc00 && ch < 0xe000) {
         return -1;
      } else {
         if (i+2 >= len1) return -1;
         if (s1[i++] != 0xe0 + (ch >> 12)) return -1;
         if (s1[i++] != 0x80 + ((ch >> 6) & 0x3f)) return -1;
         if (s1[i++] != 0x80 + ((ch     ) & 0x3f)) return -1;
      }
      s2 += 2;
      len2 -= 2;
   }
   return i;
}

static int stbtt_CompareUTF8toUTF16_bigendian_internal(char *s1, int len1, char *s2, int len2)
{
   return len1 == stbtt__CompareUTF8toUTF16_bigendian_prefix((stbtt_uint8*) s1, len1, (stbtt_uint8*) s2, len2);
}

STBTT_DEF const char *stbtt_GetFontNameString(const stbtt_fontinfo *font, int *length, int platformID, int encodingID, int languageID, int nameID)
{
   stbtt_int32 i,count,stringOffset;
   stbtt_uint8 *fc = font->data;
   stbtt_uint32 offset = font->fontstart;
   stbtt_uint32 nm = stbtt__find_table(fc, offset, "name");
   if (!nm) return NULL;

   count = ttUSHORT(fc+nm+2);
   stringOffset = nm + ttUSHORT(fc+nm+4);
   for (i=0; i < count; ++i) {
      stbtt_uint32 loc = nm + 6 + 12 * i;
      if (platformID == ttUSHORT(fc+loc+0) && encodingID == ttUSHORT(fc+loc+2)
          && languageID == ttUSHORT(fc+loc+4) && nameID == ttUSHORT(fc+loc+6)) {
         *length = ttUSHORT(fc+loc+8);
         return (const char *) (fc+stringOffset+ttUSHORT(fc+loc+10));
      }
   }
   return NULL;
}

static int stbtt__matchpair(stbtt_uint8 *fc, stbtt_uint32 nm, stbtt_uint8 *name, stbtt_int32 nlen, stbtt_int32 target_id, stbtt_int32 next_id)
{
   stbtt_int32 i;
   stbtt_int32 count = ttUSHORT(fc+nm+2);
   stbtt_int32 stringOffset = nm + ttUSHORT(fc+nm+4);

   for (i=0; i < count; ++i) {
      stbtt_uint32 loc = nm + 6 + 12 * i;
      stbtt_int32 id = ttUSHORT(fc+loc+6);
      if (id == target_id) {

         stbtt_int32 platform = ttUSHORT(fc+loc+0), encoding = ttUSHORT(fc+loc+2), language = ttUSHORT(fc+loc+4);

         if (platform == 0 || (platform == 3 && encoding == 1) || (platform == 3 && encoding == 10)) {
            stbtt_int32 slen = ttUSHORT(fc+loc+8);
            stbtt_int32 off = ttUSHORT(fc+loc+10);

            stbtt_int32 matchlen = stbtt__CompareUTF8toUTF16_bigendian_prefix(name, nlen, fc+stringOffset+off,slen);
            if (matchlen >= 0) {

               if (i+1 < count && ttUSHORT(fc+loc+12+6) == next_id && ttUSHORT(fc+loc+12) == platform && ttUSHORT(fc+loc+12+2) == encoding && ttUSHORT(fc+loc+12+4) == language) {
                  slen = ttUSHORT(fc+loc+12+8);
                  off = ttUSHORT(fc+loc+12+10);
                  if (slen == 0) {
                     if (matchlen == nlen)
                        return 1;
                  } else if (matchlen < nlen && name[matchlen] == ' ') {
                     ++matchlen;
                     if (stbtt_CompareUTF8toUTF16_bigendian_internal((char*) (name+matchlen), nlen-matchlen, (char*)(fc+stringOffset+off),slen))
                        return 1;
                  }
               } else {

                  if (matchlen == nlen)
                     return 1;
               }
            }
         }

      }
   }
   return 0;
}

static int stbtt__matches(stbtt_uint8 *fc, stbtt_uint32 offset, stbtt_uint8 *name, stbtt_int32 flags)
{
   stbtt_int32 nlen = (stbtt_int32) STBTT_strlen((char *) name);
   stbtt_uint32 nm,hd;
   if (!stbtt__isfont(fc+offset)) return 0;

   if (flags) {
      hd = stbtt__find_table(fc, offset, "head");
      if ((ttUSHORT(fc+hd+44) & 7) != (flags & 7)) return 0;
   }

   nm = stbtt__find_table(fc, offset, "name");
   if (!nm) return 0;

   if (flags) {

      if (stbtt__matchpair(fc, nm, name, nlen, 16, -1))  return 1;
      if (stbtt__matchpair(fc, nm, name, nlen,  1, -1))  return 1;
      if (stbtt__matchpair(fc, nm, name, nlen,  3, -1))  return 1;
   } else {
      if (stbtt__matchpair(fc, nm, name, nlen, 16, 17))  return 1;
      if (stbtt__matchpair(fc, nm, name, nlen,  1,  2))  return 1;
      if (stbtt__matchpair(fc, nm, name, nlen,  3, -1))  return 1;
   }

   return 0;
}

static int stbtt_FindMatchingFont_internal(unsigned char *font_collection, char *name_utf8, stbtt_int32 flags)
{
   stbtt_int32 i;
   for (i=0;;++i) {
      stbtt_int32 off = stbtt_GetFontOffsetForIndex(font_collection, i);
      if (off < 0) return off;
      if (stbtt__matches((stbtt_uint8 *) font_collection, off, (stbtt_uint8*) name_utf8, flags))
         return off;
   }
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif

STBTT_DEF int stbtt_BakeFontBitmap(const unsigned char *data, int offset,
                                float pixel_height, unsigned char *pixels, int pw, int ph,
                                int first_char, int num_chars, stbtt_bakedchar *chardata)
{
   return stbtt_BakeFontBitmap_internal((unsigned char *) data, offset, pixel_height, pixels, pw, ph, first_char, num_chars, chardata);
}

STBTT_DEF int stbtt_GetFontOffsetForIndex(const unsigned char *data, int index)
{
   return stbtt_GetFontOffsetForIndex_internal((unsigned char *) data, index);
}

STBTT_DEF int stbtt_GetNumberOfFonts(const unsigned char *data)
{
   return stbtt_GetNumberOfFonts_internal((unsigned char *) data);
}

STBTT_DEF int stbtt_InitFont(stbtt_fontinfo *info, const unsigned char *data, int offset)
{
   return stbtt_InitFont_internal(info, (unsigned char *) data, offset);
}

STBTT_DEF int stbtt_FindMatchingFont(const unsigned char *fontdata, const char *name, int flags)
{
   return stbtt_FindMatchingFont_internal((unsigned char *) fontdata, (char *) name, flags);
}

STBTT_DEF int stbtt_CompareUTF8toUTF16_bigendian(const char *s1, int len1, const char *s2, int len2)
{
   return stbtt_CompareUTF8toUTF16_bigendian_internal((char *) s1, len1, (char *) s2, len2);
}

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#endif

#ifdef NK_INCLUDE_FONT_BAKING

#define STBTT_MAX_OVERSAMPLE   8

struct nk_font_bake_data {
    struct stbtt_fontinfo info;
    struct stbrp_rect *rects;
    stbtt_pack_range *ranges;
    nk_rune range_count;
};

struct nk_font_baker {
    struct nk_allocator alloc;
    struct stbtt_pack_context spc;
    struct nk_font_bake_data *build;
    stbtt_packedchar *packed_chars;
    struct stbrp_rect *rects;
    stbtt_pack_range *ranges;
};

NK_GLOBAL const nk_size nk_rect_align = NK_ALIGNOF(struct stbrp_rect);
NK_GLOBAL const nk_size nk_range_align = NK_ALIGNOF(stbtt_pack_range);
NK_GLOBAL const nk_size nk_char_align = NK_ALIGNOF(stbtt_packedchar);
NK_GLOBAL const nk_size nk_build_align = NK_ALIGNOF(struct nk_font_bake_data);
NK_GLOBAL const nk_size nk_baker_align = NK_ALIGNOF(struct nk_font_baker);

NK_INTERN int
nk_range_count(const nk_rune *range)
{
    const nk_rune *iter = range;
    NK_ASSERT(range);
    if (!range) return 0;
    while (*(iter++) != 0);
    return (iter == range) ? 0 : (int)((iter - range)/2);
}
NK_INTERN int
nk_range_glyph_count(const nk_rune *range, int count)
{
    int i = 0;
    int total_glyphs = 0;
    for (i = 0; i < count; ++i) {
        int diff;
        nk_rune f = range[(i*2)+0];
        nk_rune t = range[(i*2)+1];
        NK_ASSERT(t >= f);
        diff = (int)((t - f) + 1);
        total_glyphs += diff;
    }
    return total_glyphs;
}
NK_API const nk_rune*
nk_font_default_glyph_ranges(void)
{
    NK_STORAGE const nk_rune ranges[] = {0x0020, 0x00FF, 0};
    return ranges;
}
NK_API const nk_rune*
nk_font_chinese_glyph_ranges(void)
{
    NK_STORAGE const nk_rune ranges[] = {
        0x0020, 0x00FF,
        0x3000, 0x30FF,
        0x31F0, 0x31FF,
        0xFF00, 0xFFEF,
        0x4E00, 0x9FAF,
        0
    };
    return ranges;
}
NK_API const nk_rune*
nk_font_cyrillic_glyph_ranges(void)
{
    NK_STORAGE const nk_rune ranges[] = {
        0x0020, 0x00FF,
        0x0400, 0x052F,
        0x2DE0, 0x2DFF,
        0xA640, 0xA69F,
        0
    };
    return ranges;
}
NK_API const nk_rune*
nk_font_korean_glyph_ranges(void)
{
    NK_STORAGE const nk_rune ranges[] = {
        0x0020, 0x00FF,
        0x3131, 0x3163,
        0xAC00, 0xD79D,
        0
    };
    return ranges;
}
NK_INTERN void
nk_font_baker_memory(nk_size *temp, int *glyph_count,
    struct nk_font_config *config_list, int count)
{
    int range_count = 0;
    int total_range_count = 0;
    struct nk_font_config *iter, *i;

    NK_ASSERT(config_list);
    NK_ASSERT(glyph_count);
    if (!config_list) {
        *temp = 0;
        *glyph_count = 0;
        return;
    }
    *glyph_count = 0;
    for (iter = config_list; iter; iter = iter->next) {
        i = iter;
        do {if (!i->range) iter->range = nk_font_default_glyph_ranges();
            range_count = nk_range_count(i->range);
            total_range_count += range_count;
            *glyph_count += nk_range_glyph_count(i->range, range_count);
        } while ((i = i->n) != iter);
    }
    *temp = (nk_size)*glyph_count * sizeof(struct stbrp_rect);
    *temp += (nk_size)total_range_count * sizeof(stbtt_pack_range);
    *temp += (nk_size)*glyph_count * sizeof(stbtt_packedchar);
    *temp += (nk_size)count * sizeof(struct nk_font_bake_data);
    *temp += sizeof(struct nk_font_baker);
    *temp += nk_rect_align + nk_range_align + nk_char_align;
    *temp += nk_build_align + nk_baker_align;
}
NK_INTERN struct nk_font_baker*
nk_font_baker(void *memory, int glyph_count, int count, struct nk_allocator *alloc)
{
    struct nk_font_baker *baker;
    if (!memory) return 0;

    baker = (struct nk_font_baker*)NK_ALIGN_PTR(memory, nk_baker_align);
    baker->build = (struct nk_font_bake_data*)NK_ALIGN_PTR((baker + 1), nk_build_align);
    baker->packed_chars = (stbtt_packedchar*)NK_ALIGN_PTR((baker->build + count), nk_char_align);
    baker->rects = (struct stbrp_rect*)NK_ALIGN_PTR((baker->packed_chars + glyph_count), nk_rect_align);
    baker->ranges = (stbtt_pack_range*)NK_ALIGN_PTR((baker->rects + glyph_count), nk_range_align);
    baker->alloc = *alloc;
    return baker;
}
NK_INTERN int
nk_font_bake_pack(struct nk_font_baker *baker,
    nk_size *image_memory, int *width, int *height, struct nk_recti *custom,
    const struct nk_font_config *config_list, int count,
    struct nk_allocator *alloc)
{
    NK_STORAGE const nk_size max_height = 1024 * 32;
    const struct nk_font_config *config_iter, *it;
    int total_glyph_count = 0;
    int total_range_count = 0;
    int range_count = 0;
    int i = 0;

    NK_ASSERT(image_memory);
    NK_ASSERT(width);
    NK_ASSERT(height);
    NK_ASSERT(config_list);
    NK_ASSERT(count);
    NK_ASSERT(alloc);

    if (!image_memory || !width || !height || !config_list || !count) return nk_false;
    for (config_iter = config_list; config_iter; config_iter = config_iter->next) {
        it = config_iter;
        do {range_count = nk_range_count(it->range);
            total_range_count += range_count;
            total_glyph_count += nk_range_glyph_count(it->range, range_count);
        } while ((it = it->n) != config_iter);
    }

    for (config_iter = config_list; config_iter; config_iter = config_iter->next) {
        it = config_iter;
        do {
            struct stbtt_fontinfo *font_info = &baker->build[i++].info;
            font_info->userdata = alloc;

            if (!stbtt_InitFont(font_info, (const unsigned char*)it->ttf_blob, stbtt_GetFontOffsetForIndex((const unsigned char*)it->ttf_blob, 0)))
                return nk_false;
        } while ((it = it->n) != config_iter);
    }
    *height = 0;
    *width = (total_glyph_count > 1000) ? 1024 : 512;
    stbtt_PackBegin(&baker->spc, 0, (int)*width, (int)max_height, 0, 1, alloc);
    {
        int input_i = 0;
        int range_n = 0;
        int rect_n = 0;
        int char_n = 0;

        if (custom) {

            struct stbrp_rect custom_space;
            nk_zero(&custom_space, sizeof(custom_space));
            custom_space.w = (stbrp_coord)(custom->w);
            custom_space.h = (stbrp_coord)(custom->h);

            stbtt_PackSetOversampling(&baker->spc, 1, 1);
            stbrp_pack_rects((struct stbrp_context*)baker->spc.pack_info, &custom_space, 1);
            *height = NK_MAX(*height, (int)(custom_space.y + custom_space.h));

            custom->x = (short)custom_space.x;
            custom->y = (short)custom_space.y;
            custom->w = (short)custom_space.w;
            custom->h = (short)custom_space.h;
        }

        for (input_i = 0, config_iter = config_list; input_i < count && config_iter;
            config_iter = config_iter->next) {
            it = config_iter;
            do {int n = 0;
                int glyph_count;
                const nk_rune *in_range;
                const struct nk_font_config *cfg = it;
                struct nk_font_bake_data *tmp = &baker->build[input_i++];

                glyph_count = 0; range_count = 0;
                for (in_range = cfg->range; in_range[0] && in_range[1]; in_range += 2) {
                    glyph_count += (int)(in_range[1] - in_range[0]) + 1;
                    range_count++;
                }

                tmp->ranges = baker->ranges + range_n;
                tmp->range_count = (nk_rune)range_count;
                range_n += range_count;
                for (i = 0; i < range_count; ++i) {
                    in_range = &cfg->range[i * 2];
                    tmp->ranges[i].font_size = cfg->size;
                    tmp->ranges[i].first_unicode_codepoint_in_range = (int)in_range[0];
                    tmp->ranges[i].num_chars = (int)(in_range[1]- in_range[0]) + 1;
                    tmp->ranges[i].chardata_for_range = baker->packed_chars + char_n;
                    char_n += tmp->ranges[i].num_chars;
                }

                tmp->rects = baker->rects + rect_n;
                rect_n += glyph_count;
                stbtt_PackSetOversampling(&baker->spc, cfg->oversample_h, cfg->oversample_v);
                n = stbtt_PackFontRangesGatherRects(&baker->spc, &tmp->info,
                    tmp->ranges, (int)tmp->range_count, tmp->rects);
                stbrp_pack_rects((struct stbrp_context*)baker->spc.pack_info, tmp->rects, (int)n);

                for (i = 0; i < n; ++i) {
                    if (tmp->rects[i].was_packed)
                        *height = NK_MAX(*height, tmp->rects[i].y + tmp->rects[i].h);
                }
            } while ((it = it->n) != config_iter);
        }
        NK_ASSERT(rect_n == total_glyph_count);
        NK_ASSERT(char_n == total_glyph_count);
        NK_ASSERT(range_n == total_range_count);
    }
    *height = (int)nk_round_up_pow2((nk_uint)*height);
    *image_memory = (nk_size)(*width) * (nk_size)(*height);
    return nk_true;
}
NK_INTERN void
nk_font_bake(struct nk_font_baker *baker, void *image_memory, int width, int height,
    struct nk_font_glyph *glyphs, int glyphs_count,
    const struct nk_font_config *config_list, int font_count)
{
    int input_i = 0;
    nk_rune glyph_n = 0;
    const struct nk_font_config *config_iter;
    const struct nk_font_config *it;

    NK_ASSERT(image_memory);
    NK_ASSERT(width);
    NK_ASSERT(height);
    NK_ASSERT(config_list);
    NK_ASSERT(baker);
    NK_ASSERT(font_count);
    NK_ASSERT(glyphs_count);
    if (!image_memory || !width || !height || !config_list ||
        !font_count || !glyphs || !glyphs_count)
        return;

    nk_zero(image_memory, (nk_size)((nk_size)width * (nk_size)height));
    baker->spc.pixels = (unsigned char*)image_memory;
    baker->spc.height = (int)height;
    for (input_i = 0, config_iter = config_list; input_i < font_count && config_iter;
        config_iter = config_iter->next) {
        it = config_iter;
        do {const struct nk_font_config *cfg = it;
            struct nk_font_bake_data *tmp = &baker->build[input_i++];
            stbtt_PackSetOversampling(&baker->spc, cfg->oversample_h, cfg->oversample_v);
            stbtt_PackFontRangesRenderIntoRects(&baker->spc, &tmp->info, tmp->ranges, (int)tmp->range_count, tmp->rects);
        } while ((it = it->n) != config_iter);
    } stbtt_PackEnd(&baker->spc);

    for (input_i = 0, config_iter = config_list; input_i < font_count && config_iter;
        config_iter = config_iter->next) {
        it = config_iter;
        do {nk_size i = 0;
            int char_idx = 0;
            nk_rune glyph_count = 0;
            const struct nk_font_config *cfg = it;
            struct nk_font_bake_data *tmp = &baker->build[input_i++];
            struct nk_baked_font *dst_font = cfg->font;

            float font_scale = stbtt_ScaleForPixelHeight(&tmp->info, cfg->size);
            int unscaled_ascent, unscaled_descent, unscaled_line_gap;
            stbtt_GetFontVMetrics(&tmp->info, &unscaled_ascent, &unscaled_descent,
                                    &unscaled_line_gap);

            if (!cfg->merge_mode) {
                dst_font->ranges = cfg->range;
                dst_font->height = cfg->size;
                dst_font->ascent = ((float)unscaled_ascent * font_scale);
                dst_font->descent = ((float)unscaled_descent * font_scale);
                dst_font->glyph_offset = glyph_n;

                dst_font->glyph_count = 0;
            }

            for (i = 0; i < tmp->range_count; ++i) {
                stbtt_pack_range *range = &tmp->ranges[i];
                for (char_idx = 0; char_idx < range->num_chars; char_idx++)
                {
                    nk_rune codepoint = 0;
                    float dummy_x = 0, dummy_y = 0;
                    stbtt_aligned_quad q;
                    struct nk_font_glyph *glyph;

                    const stbtt_packedchar *pc = &range->chardata_for_range[char_idx];
                    codepoint = (nk_rune)(range->first_unicode_codepoint_in_range + char_idx);
                    stbtt_GetPackedQuad(range->chardata_for_range, (int)width,
                        (int)height, char_idx, &dummy_x, &dummy_y, &q, 0);

                    glyph = &glyphs[dst_font->glyph_offset + dst_font->glyph_count + (unsigned int)glyph_count];
                    glyph->codepoint = codepoint;
                    glyph->x0 = q.x0; glyph->y0 = q.y0;
                    glyph->x1 = q.x1; glyph->y1 = q.y1;
                    glyph->y0 += (dst_font->ascent + 0.5f);
                    glyph->y1 += (dst_font->ascent + 0.5f);
                    glyph->w = glyph->x1 - glyph->x0 + 0.5f;
                    glyph->h = glyph->y1 - glyph->y0;

                    if (cfg->coord_type == NK_COORD_PIXEL) {
                        glyph->u0 = q.s0 * (float)width;
                        glyph->v0 = q.t0 * (float)height;
                        glyph->u1 = q.s1 * (float)width;
                        glyph->v1 = q.t1 * (float)height;
                    } else {
                        glyph->u0 = q.s0;
                        glyph->v0 = q.t0;
                        glyph->u1 = q.s1;
                        glyph->v1 = q.t1;
                    }
                    glyph->xadvance = (pc->xadvance + cfg->spacing.x);
                    if (cfg->pixel_snap)
                        glyph->xadvance = (float)(int)(glyph->xadvance + 0.5f);
                    glyph_count++;
                }
            }
            dst_font->glyph_count += glyph_count;
            glyph_n += glyph_count;
        } while ((it = it->n) != config_iter);
    }
}
NK_INTERN void
nk_font_bake_custom_data(void *img_memory, int img_width, int img_height,
    struct nk_recti img_dst, const char *texture_data_mask, int tex_width,
    int tex_height, char white, char black)
{
    nk_byte *pixels;
    int y = 0;
    int x = 0;
    int n = 0;

    NK_ASSERT(img_memory);
    NK_ASSERT(img_width);
    NK_ASSERT(img_height);
    NK_ASSERT(texture_data_mask);
    NK_UNUSED(tex_height);
    if (!img_memory || !img_width || !img_height || !texture_data_mask)
        return;

    pixels = (nk_byte*)img_memory;
    for (y = 0, n = 0; y < tex_height; ++y) {
        for (x = 0; x < tex_width; ++x, ++n) {
            const int off0 = ((img_dst.x + x) + (img_dst.y + y) * img_width);
            const int off1 = off0 + 1 + tex_width;
            pixels[off0] = (texture_data_mask[n] == white) ? 0xFF : 0x00;
            pixels[off1] = (texture_data_mask[n] == black) ? 0xFF : 0x00;
        }
    }
}
NK_INTERN void
nk_font_bake_convert(void *out_memory, int img_width, int img_height,
    const void *in_memory)
{
    int n = 0;
    nk_rune *dst;
    const nk_byte *src;

    NK_ASSERT(out_memory);
    NK_ASSERT(in_memory);
    NK_ASSERT(img_width);
    NK_ASSERT(img_height);
    if (!out_memory || !in_memory || !img_height || !img_width) return;

    dst = (nk_rune*)out_memory;
    src = (const nk_byte*)in_memory;
    for (n = (int)(img_width * img_height); n > 0; n--)
        *dst++ = ((nk_rune)(*src++) << 24) | 0x00FFFFFF;
}

NK_INTERN float
nk_font_text_width(nk_handle handle, float height, const char *text, int len)
{
    nk_rune unicode;
    int text_len  = 0;
    float text_width = 0;
    int glyph_len = 0;
    float scale = 0;

    struct nk_font *font = (struct nk_font*)handle.ptr;
    NK_ASSERT(font);
    NK_ASSERT(font->glyphs);
    if (!font || !text || !len)
        return 0;

    scale = height/font->info.height;
    glyph_len = text_len = nk_utf_decode(text, &unicode, (int)len);
    if (!glyph_len) return 0;
    while (text_len <= (int)len && glyph_len) {
        const struct nk_font_glyph *g;
        if (unicode == NK_UTF_INVALID) break;

        g = nk_font_find_glyph(font, unicode);
        text_width += g->xadvance * scale;

        glyph_len = nk_utf_decode(text + text_len, &unicode, (int)len - text_len);
        text_len += glyph_len;
    }
    return text_width;
}
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
NK_INTERN void
nk_font_query_font_glyph(nk_handle handle, float height,
    struct nk_user_font_glyph *glyph, nk_rune codepoint, nk_rune next_codepoint)
{
    float scale;
    const struct nk_font_glyph *g;
    struct nk_font *font;

    NK_ASSERT(glyph);
    NK_UNUSED(next_codepoint);

    font = (struct nk_font*)handle.ptr;
    NK_ASSERT(font);
    NK_ASSERT(font->glyphs);
    if (!font || !glyph)
        return;

    scale = height/font->info.height;
    g = nk_font_find_glyph(font, codepoint);
    glyph->width = (g->x1 - g->x0) * scale;
    glyph->height = (g->y1 - g->y0) * scale;
    glyph->offset = nk_vec2(g->x0 * scale, g->y0 * scale);
    glyph->xadvance = (g->xadvance * scale);
    glyph->uv[0] = nk_vec2(g->u0, g->v0);
    glyph->uv[1] = nk_vec2(g->u1, g->v1);
}
#endif
NK_API const struct nk_font_glyph*
nk_font_find_glyph(struct nk_font *font, nk_rune unicode)
{
    int i = 0;
    int count;
    int total_glyphs = 0;
    const struct nk_font_glyph *glyph = 0;
    const struct nk_font_config *iter = 0;

    NK_ASSERT(font);
    NK_ASSERT(font->glyphs);
    NK_ASSERT(font->info.ranges);
    if (!font || !font->glyphs) return 0;

    glyph = font->fallback;
    iter = font->config;
    do {count = nk_range_count(iter->range);
        for (i = 0; i < count; ++i) {
            nk_rune f = iter->range[(i*2)+0];
            nk_rune t = iter->range[(i*2)+1];
            int diff = (int)((t - f) + 1);
            if (unicode >= f && unicode <= t)
                return &font->glyphs[((nk_rune)total_glyphs + (unicode - f))];
            total_glyphs += diff;
        }
    } while ((iter = iter->n) != font->config);
    return glyph;
}
NK_INTERN void
nk_font_init(struct nk_font *font, float pixel_height,
    nk_rune fallback_codepoint, struct nk_font_glyph *glyphs,
    const struct nk_baked_font *baked_font, nk_handle atlas)
{
    struct nk_baked_font baked;
    NK_ASSERT(font);
    NK_ASSERT(glyphs);
    NK_ASSERT(baked_font);
    if (!font || !glyphs || !baked_font)
        return;

    baked = *baked_font;
    font->fallback = 0;
    font->info = baked;
    font->scale = (float)pixel_height / (float)font->info.height;
    font->glyphs = &glyphs[baked_font->glyph_offset];
    font->texture = atlas;
    font->fallback_codepoint = fallback_codepoint;
    font->fallback = nk_font_find_glyph(font, fallback_codepoint);

    font->handle.height = font->info.height * font->scale;
    font->handle.width = nk_font_text_width;
    font->handle.userdata.ptr = font;
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    font->handle.query = nk_font_query_font_glyph;
    font->handle.texture = font->texture;
#endif
}

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverlength-strings"
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverlength-strings"
#endif

#ifdef NK_INCLUDE_DEFAULT_FONT

NK_GLOBAL const char nk_proggy_clean_ttf_compressed_data_base85[11980+1] =
    "7])#######hV0qs'/###[),##/l:$#Q6>##5[n42>c-TH`->>#/e>11NNV=Bv(*:.F?uu#(gRU.o0XGH`$vhLG1hxt9?W`#,5LsCp#-i>.r$<$6pD>Lb';9Crc6tgXmKVeU2cD4Eo3R/"
    "2*>]b(MC;$jPfY.;h^`IWM9<Lh2TlS+f-s$o6Q<BWH`YiU.xfLq$N;$0iR/GX:U(jcW2p/W*q?-qmnUCI;jHSAiFWM.R*kU@C=GH?a9wp8f$e.-4^Qg1)Q-GL(lf(r/7GrRgwV%MS=C#"
    "`8ND>Qo#t'X#(v#Y9w0#1D$CIf;W'#pWUPXOuxXuU(H9M(1<q-UE31#^-V'8IRUo7Qf./L>=Ke$$'5F%)]0^#0X@U.a<r:QLtFsLcL6##lOj)#.Y5<-R&KgLwqJfLgN&;Q?gI^#DY2uL"
    "i@^rMl9t=cWq6##weg>$FBjVQTSDgEKnIS7EM9>ZY9w0#L;>>#Mx&4Mvt//L[MkA#W@lK.N'[0#7RL_&#w+F%HtG9M#XL`N&.,GM4Pg;-<nLENhvx>-VsM.M0rJfLH2eTM`*oJMHRC`N"
    "kfimM2J,W-jXS:)r0wK#@Fge$U>`w'N7G#$#fB#$E^$#:9:hk+eOe--6x)F7*E%?76%^GMHePW-Z5l'&GiF#$956:rS?dA#fiK:)Yr+`&#0j@'DbG&#^$PG.Ll+DNa<XCMKEV*N)LN/N"
    "*b=%Q6pia-Xg8I$<MR&,VdJe$<(7G;Ckl'&hF;;$<_=X(b.RS%%)###MPBuuE1V:v&cX&#2m#(&cV]`k9OhLMbn%s$G2,B$BfD3X*sp5#l,$R#]x_X1xKX%b5U*[r5iMfUo9U`N99hG)"
    "tm+/Us9pG)XPu`<0s-)WTt(gCRxIg(%6sfh=ktMKn3j)<6<b5Sk_/0(^]AaN#(p/L>&VZ>1i%h1S9u5o@YaaW$e+b<TWFn/Z:Oh(Cx2$lNEoN^e)#CFY@@I;BOQ*sRwZtZxRcU7uW6CX"
    "ow0i(?$Q[cjOd[P4d)]>ROPOpxTO7Stwi1::iB1q)C_=dV26J;2,]7op$]uQr@_V7$q^%lQwtuHY]=DX,n3L#0PHDO4f9>dC@O>HBuKPpP*E,N+b3L#lpR/MrTEH.IAQk.a>D[.e;mc."
    "x]Ip.PH^'/aqUO/$1WxLoW0[iLA<QT;5HKD+@qQ'NQ(3_PLhE48R.qAPSwQ0/WK?Z,[x?-J;jQTWA0X@KJ(_Y8N-:/M74:/-ZpKrUss?d#dZq]DAbkU*JqkL+nwX@@47`5>w=4h(9.`G"
    "CRUxHPeR`5Mjol(dUWxZa(>STrPkrJiWx`5U7F#.g*jrohGg`cg:lSTvEY/EV_7H4Q9[Z%cnv;JQYZ5q.l7Zeas:HOIZOB?G<Nald$qs]@]L<J7bR*>gv:[7MI2k).'2($5FNP&EQ(,)"
    "U]W]+fh18.vsai00);D3@4ku5P?DP8aJt+;qUM]=+b'8@;mViBKx0DE[-auGl8:PJ&Dj+M6OC]O^((##]`0i)drT;-7X`=-H3[igUnPG-NZlo.#k@h#=Ork$m>a>$-?Tm$UV(?#P6YY#"
    "'/###xe7q.73rI3*pP/$1>s9)W,JrM7SN]'/4C#v$U`0#V.[0>xQsH$fEmPMgY2u7Kh(G%siIfLSoS+MK2eTM$=5,M8p`A.;_R%#u[K#$x4AG8.kK/HSB==-'Ie/QTtG?-.*^N-4B/ZM"
    "_3YlQC7(p7q)&](`6_c)$/*JL(L-^(]$wIM`dPtOdGA,U3:w2M-0<q-]L_?^)1vw'.,MRsqVr.L;aN&#/EgJ)PBc[-f>+WomX2u7lqM2iEumMTcsF?-aT=Z-97UEnXglEn1K-bnEO`gu"
    "Ft(c%=;Am_Qs@jLooI&NX;]0#j4#F14;gl8-GQpgwhrq8'=l_f-b49'UOqkLu7-##oDY2L(te+Mch&gLYtJ,MEtJfLh'x'M=$CS-ZZ%P]8bZ>#S?YY#%Q&q'3^Fw&?D)UDNrocM3A76/"
    "/oL?#h7gl85[qW/NDOk%16ij;+:1a'iNIdb-ou8.P*w,v5#EI$TWS>Pot-R*H'-SEpA:g)f+O$%%`kA#G=8RMmG1&O`>to8bC]T&$,n.LoO>29sp3dt-52U%VM#q7'DHpg+#Z9%H[K<L"
    "%a2E-grWVM3@2=-k22tL]4$##6We'8UJCKE[d_=%wI;'6X-GsLX4j^SgJ$##R*w,vP3wK#iiW&#*h^D&R?jp7+/u&#(AP##XU8c$fSYW-J95_-Dp[g9wcO&#M-h1OcJlc-*vpw0xUX&#"
    "OQFKNX@QI'IoPp7nb,QU//MQ&ZDkKP)X<WSVL(68uVl&#c'[0#(s1X&xm$Y%B7*K:eDA323j998GXbA#pwMs-jgD$9QISB-A_(aN4xoFM^@C58D0+Q+q3n0#3U1InDjF682-SjMXJK)("
    "h$hxua_K]ul92%'BOU&#BRRh-slg8KDlr:%L71Ka:.A;%YULjDPmL<LYs8i#XwJOYaKPKc1h:'9Ke,g)b),78=I39B;xiY$bgGw-&.Zi9InXDuYa%G*f2Bq7mn9^#p1vv%#(Wi-;/Z5h"
    "o;#2:;%d&#x9v68C5g?ntX0X)pT`;%pB3q7mgGN)3%(P8nTd5L7GeA-GL@+%J3u2:(Yf>et`e;)f#Km8&+DC$I46>#Kr]]u-[=99tts1.qb#q72g1WJO81q+eN'03'eM>&1XxY-caEnO"
    "j%2n8)),?ILR5^.Ibn<-X-Mq7[a82Lq:F&#ce+S9wsCK*x`569E8ew'He]h:sI[2LM$[guka3ZRd6:t%IG:;$%YiJ:Nq=?eAw;/:nnDq0(CYcMpG)qLN4$##&J<j$UpK<Q4a1]MupW^-"
    "sj_$%[HK%'F####QRZJ::Y3EGl4'@%FkiAOg#p[##O`gukTfBHagL<LHw%q&OV0##F=6/:chIm0@eCP8X]:kFI%hl8hgO@RcBhS-@Qb$%+m=hPDLg*%K8ln(wcf3/'DW-$.lR?n[nCH-"
    "eXOONTJlh:.RYF%3'p6sq:UIMA945&^HFS87@$EP2iG<-lCO$%c`uKGD3rC$x0BL8aFn--`ke%#HMP'vh1/R&O_J9'um,.<tx[@%wsJk&bUT2`0uMv7gg#qp/ij.L56'hl;.s5CUrxjO"
    "M7-##.l+Au'A&O:-T72L]P`&=;ctp'XScX*rU.>-XTt,%OVU4)S1+R-#dg0/Nn?Ku1^0f$B*P:Rowwm-`0PKjYDDM'3]d39VZHEl4,.j']Pk-M.h^&:0FACm$maq-&sgw0t7/6(^xtk%"
    "LuH88Fj-ekm>GA#_>568x6(OFRl-IZp`&b,_P'$M<Jnq79VsJW/mWS*PUiq76;]/NM_>hLbxfc$mj`,O;&%W2m`Zh:/)Uetw:aJ%]K9h:TcF]u_-Sj9,VK3M.*'&0D[Ca]J9gp8,kAW]"
    "%(?A%R$f<->Zts'^kn=-^@c4%-pY6qI%J%1IGxfLU9CP8cbPlXv);C=b),<2mOvP8up,UVf3839acAWAW-W?#ao/^#%KYo8fRULNd2.>%m]UK:n%r$'sw]J;5pAoO_#2mO3n,'=H5(et"
    "Hg*`+RLgv>=4U8guD$I%D:W>-r5V*%j*W:Kvej.Lp$<M-SGZ':+Q_k+uvOSLiEo(<aD/K<CCc`'Lx>'?;++O'>()jLR-^u68PHm8ZFWe+ej8h:9r6L*0//c&iH&R8pRbA#Kjm%upV1g:"
    "a_#Ur7FuA#(tRh#.Y5K+@?3<-8m0$PEn;J:rh6?I6uG<-`wMU'ircp0LaE_OtlMb&1#6T.#FDKu#1Lw%u%+GM+X'e?YLfjM[VO0MbuFp7;>Q&#WIo)0@F%q7c#4XAXN-U&VB<HFF*qL("
    "$/V,;(kXZejWO`<[5?\?ewY(*9=%wDc;,u<'9t3W-(H1th3+G]ucQ]kLs7df($/*JL]@*t7Bu_G3_7mp7<iaQjO@.kLg;x3B0lqp7Hf,^Ze7-##@/c58Mo(3;knp0%)A7?-W+eI'o8)b<"
    "nKnw'Ho8C=Y>pqB>0ie&jhZ[?iLR@@_AvA-iQC(=ksRZRVp7`.=+NpBC%rh&3]R:8XDmE5^V8O(x<<aG/1N$#FX$0V5Y6x'aErI3I$7x%E`v<-BY,)%-?Psf*l?%C3.mM(=/M0:JxG'?"
    "7WhH%o'a<-80g0NBxoO(GH<dM]n.+%q@jH?f.UsJ2Ggs&4<-e47&Kl+f//9@`b+?.TeN_&B8Ss?v;^Trk;f#YvJkl&w$]>-+k?'(<S:68tq*WoDfZu';mM?8X[ma8W%*`-=;D.(nc7/;"
    ")g:T1=^J$&BRV(-lTmNB6xqB[@0*o.erM*<SWF]u2=st-*(6v>^](H.aREZSi,#1:[IXaZFOm<-ui#qUq2$##Ri;u75OK#(RtaW-K-F`S+cF]uN`-KMQ%rP/Xri.LRcB##=YL3BgM/3M"
    "D?@f&1'BW-)Ju<L25gl8uhVm1hL$##*8###'A3/LkKW+(^rWX?5W_8g)a(m&K8P>#bmmWCMkk&#TR`C,5d>g)F;t,4:@_l8G/5h4vUd%&%950:VXD'QdWoY-F$BtUwmfe$YqL'8(PWX("
    "P?^@Po3$##`MSs?DWBZ/S>+4%>fX,VWv/w'KD`LP5IbH;rTV>n3cEK8U#bX]l-/V+^lj3;vlMb&[5YQ8#pekX9JP3XUC72L,,?+Ni&co7ApnO*5NK,((W-i:$,kp'UDAO(G0Sq7MVjJs"
    "bIu)'Z,*[>br5fX^:FPAWr-m2KgL<LUN098kTF&#lvo58=/vjDo;.;)Ka*hLR#/k=rKbxuV`>Q_nN6'8uTG&#1T5g)uLv:873UpTLgH+#FgpH'_o1780Ph8KmxQJ8#H72L4@768@Tm&Q"
    "h4CB/5OvmA&,Q&QbUoi$a_%3M01H)4x7I^&KQVgtFnV+;[Pc>[m4k//,]1?#`VY[Jr*3&&slRfLiVZJ:]?=K3Sw=[$=uRB?3xk48@aeg<Z'<$#4H)6,>e0jT6'N#(q%.O=?2S]u*(m<-"
    "V8J'(1)G][68hW$5'q[GC&5j`TE?m'esFGNRM)j,ffZ?-qx8;->g4t*:CIP/[Qap7/9'#(1sao7w-.qNUdkJ)tCF&#B^;xGvn2r9FEPFFFcL@.iFNkTve$m%#QvQS8U@)2Z+3K:AKM5i"
    "sZ88+dKQ)W6>J%CL<KE>`.d*(B`-n8D9oK<Up]c$X$(,)M8Zt7/[rdkqTgl-0cuGMv'?>-XV1q['-5k'cAZ69e;D_?$ZPP&s^+7])$*$#@QYi9,5P&#9r+$%CE=68>K8r0=dSC%%(@p7"
    ".m7jilQ02'0-VWAg<a/''3u.=4L$Y)6k/K:_[3=&jvL<L0C/2'v:^;-DIBW,B4E68:kZ;%?8(Q8BH=kO65BW?xSG&#@uU,DS*,?.+(o(#1vCS8#CHF>TlGW'b)Tq7VT9q^*^$$.:&N@@"
    "$&)WHtPm*5_rO0&e%K&#-30j(E4#'Zb.o/(Tpm$>K'f@[PvFl,hfINTNU6u'0pao7%XUp9]5.>%h`8_=VYbxuel.NTSsJfLacFu3B'lQSu/m6-Oqem8T+oE--$0a/k]uj9EwsG>%veR*"
    "hv^BFpQj:K'#SJ,sB-'#](j.Lg92rTw-*n%@/;39rrJF,l#qV%OrtBeC6/,;qB3ebNW[?,Hqj2L.1NP&GjUR=1D8QaS3Up&@*9wP?+lo7b?@%'k4`p0Z$22%K3+iCZj?XJN4Nm&+YF]u"
    "@-W$U%VEQ/,,>>#)D<h#`)h0:<Q6909ua+&VU%n2:cG3FJ-%@Bj-DgLr`Hw&HAKjKjseK</xKT*)B,N9X3]krc12t'pgTV(Lv-tL[xg_%=M_q7a^x?7Ubd>#%8cY#YZ?=,`Wdxu/ae&#"
    "w6)R89tI#6@s'(6Bf7a&?S=^ZI_kS&ai`&=tE72L_D,;^R)7[$s<Eh#c&)q.MXI%#v9ROa5FZO%sF7q7Nwb&#ptUJ:aqJe$Sl68%.D###EC><?-aF&#RNQv>o8lKN%5/$(vdfq7+ebA#"
    "u1p]ovUKW&Y%q]'>$1@-[xfn$7ZTp7mM,G,Ko7a&Gu%G[RMxJs[0MM%wci.LFDK)(<c`Q8N)jEIF*+?P2a8g%)$q]o2aH8C&<SibC/q,(e:v;-b#6[$NtDZ84Je2KNvB#$P5?tQ3nt(0"
    "d=j.LQf./Ll33+(;q3L-w=8dX$#WF&uIJ@-bfI>%:_i2B5CsR8&9Z&#=mPEnm0f`<&c)QL5uJ#%u%lJj+D-r;BoF&#4DoS97h5g)E#o:&S4weDF,9^Hoe`h*L+_a*NrLW-1pG_&2UdB8"
    "6e%B/:=>)N4xeW.*wft-;$'58-ESqr<b?UI(_%@[P46>#U`'6AQ]m&6/`Z>#S?YY#Vc;r7U2&326d=w&H####?TZ`*4?&.MK?LP8Vxg>$[QXc%QJv92.(Db*B)gb*BM9dM*hJMAo*c&#"
    "b0v=Pjer]$gG&JXDf->'StvU7505l9$AFvgYRI^&<^b68?j#q9QX4SM'RO#&sL1IM.rJfLUAj221]d##DW=m83u5;'bYx,*Sl0hL(W;;$doB&O/TQ:(Z^xBdLjL<Lni;''X.`$#8+1GD"
    ":k$YUWsbn8ogh6rxZ2Z9]%nd+>V#*8U_72Lh+2Q8Cj0i:6hp&$C/:p(HK>T8Y[gHQ4`4)'$Ab(Nof%V'8hL&#<NEdtg(n'=S1A(Q1/I&4([%dM`,Iu'1:_hL>SfD07&6D<fp8dHM7/g+"
    "tlPN9J*rKaPct&?'uBCem^jn%9_K)<,C5K3s=5g&GmJb*[SYq7K;TRLGCsM-$$;S%:Y@r7AK0pprpL<Lrh,q7e/%KWK:50I^+m'vi`3?%Zp+<-d+$L-Sv:@.o19n$s0&39;kn;S%BSq*"
    "$3WoJSCLweV[aZ'MQIjO<7;X-X;&+dMLvu#^UsGEC9WEc[X(wI7#2.(F0jV*eZf<-Qv3J-c+J5AlrB#$p(H68LvEA'q3n0#m,[`*8Ft)FcYgEud]CWfm68,(aLA$@EFTgLXoBq/UPlp7"
    ":d[/;r_ix=:TF`S5H-b<LI&HY(K=h#)]Lk$K14lVfm:x$H<3^Ql<M`$OhapBnkup'D#L$Pb_`N*g]2e;X/Dtg,bsj&K#2[-:iYr'_wgH)NUIR8a1n#S?Yej'h8^58UbZd+^FKD*T@;6A"
    "7aQC[K8d-(v6GI$x:T<&'Gp5Uf>@M.*J:;$-rv29'M]8qMv-tLp,'886iaC=Hb*YJoKJ,(j%K=H`K.v9HggqBIiZu'QvBT.#=)0ukruV&.)3=(^1`o*Pj4<-<aN((^7('#Z0wK#5GX@7"
    "u][`*S^43933A4rl][`*O4CgLEl]v$1Q3AeF37dbXk,.)vj#x'd`;qgbQR%FW,2(?LO=s%Sc68%NP'##Aotl8x=BE#j1UD([3$M(]UI2LX3RpKN@;/#f'f/&_mt&F)XdF<9t4)Qa.*kT"
    "LwQ'(TTB9.xH'>#MJ+gLq9-##@HuZPN0]u:h7.T..G:;$/Usj(T7`Q8tT72LnYl<-qx8;-HV7Q-&Xdx%1a,hC=0u+HlsV>nuIQL-5<N?)NBS)QN*_I,?&)2'IM%L3I)X((e/dl2&8'<M"
    ":^#M*Q+[T.Xri.LYS3v%fF`68h;b-X[/En'CR.q7E)p'/kle2HM,u;^%OKC-N+Ll%F9CF<Nf'^#t2L,;27W:0O@6##U6W7:$rJfLWHj$#)woqBefIZ.PK<b*t7ed;p*_m;4ExK#h@&]>"
    "_>@kXQtMacfD.m-VAb8;IReM3$wf0''hra*so568'Ip&vRs849'MRYSp%:t:h5qSgwpEr$B>Q,;s(C#$)`svQuF$##-D,##,g68@2[T;.XSdN9Qe)rpt._K-#5wF)sP'##p#C0c%-Gb%"
    "hd+<-j'Ai*x&&HMkT]C'OSl##5RG[JXaHN;d'uA#x._U;.`PU@(Z3dt4r152@:v,'R.Sj'w#0<-;kPI)FfJ&#AYJ&#//)>-k=m=*XnK$>=)72L]0I%>.G690a:$##<,);?;72#?x9+d;"
    "^V'9;jY@;)br#q^YQpx:X#Te$Z^'=-=bGhLf:D6&bNwZ9-ZD#n^9HhLMr5G;']d&6'wYmTFmL<LD)F^%[tC'8;+9E#C$g%#5Y>q9wI>P(9mI[>kC-ekLC/R&CH+s'B;K-M6$EB%is00:"
    "+A4[7xks.LrNk0&E)wILYF@2L'0Nb$+pv<(2.768/FrY&h$^3i&@+G%JT'<-,v`3;_)I9M^AE]CN?Cl2AZg+%4iTpT3<n-&%H%b<FDj2M<hH=&Eh<2Len$b*aTX=-8QxN)k11IM1c^j%"
    "9s<L<NFSo)B?+<-(GxsF,^-Eh@$4dXhN$+#rxK8'je'D7k`e;)2pYwPA'_p9&@^18ml1^[@g4t*[JOa*[=Qp7(qJ_oOL^('7fB&Hq-:sf,sNj8xq^>$U4O]GKx'm9)b@p7YsvK3w^YR-"
    "CdQ*:Ir<($u&)#(&?L9Rg3H)4fiEp^iI9O8KnTj,]H?D*r7'M;PwZ9K0E^k&-cpI;.p/6_vwoFMV<->#%Xi.LxVnrU(4&8/P+:hLSKj$#U%]49t'I:rgMi'FL@a:0Y-uA[39',(vbma*"
    "hU%<-SRF`Tt:542R_VV$p@[p8DV[A,?1839FWdF<TddF<9Ah-6&9tWoDlh]&1SpGMq>Ti1O*H&#(AL8[_P%.M>v^-))qOT*F5Cq0`Ye%+$B6i:7@0IX<N+T+0MlMBPQ*Vj>SsD<U4JHY"
    "8kD2)2fU/M#$e.)T4,_=8hLim[&);?UkK'-x?'(:siIfL<$pFM`i<?%W(mGDHM%>iWP,##P`%/L<eXi:@Z9C.7o=@(pXdAO/NLQ8lPl+HPOQa8wD8=^GlPa8TKI1CjhsCTSLJM'/Wl>-"
    "S(qw%sf/@%#B6;/U7K]uZbi^Oc^2n<bhPmUkMw>%t<)'mEVE''n`WnJra$^TKvX5B>;_aSEK',(hwa0:i4G?.Bci.(X[?b*($,=-n<.Q%`(X=?+@Am*Js0&=3bh8K]mL<LoNs'6,'85`"
    "0?t/'_U59@]ddF<#LdF<eWdF<OuN/45rY<-L@&#+fm>69=Lb,OcZV/);TTm8VI;?%OtJ<(b4mq7M6:u?KRdF<gR@2L=FNU-<b[(9c/ML3m;Z[$oF3g)GAWqpARc=<ROu7cL5l;-[A]%/"
    "+fsd;l#SafT/f*W]0=O'$(Tb<[)*@e775R-:Yob%g*>l*:xP?Yb.5)%w_I?7uk5JC+FS(m#i'k.'a0i)9<7b'fs'59hq$*5Uhv##pi^8+hIEBF`nvo`;'l0.^S1<-wUK2/Coh58KKhLj"
    "M=SO*rfO`+qC`W-On.=AJ56>>i2@2LH6A:&5q`?9I3@@'04&p2/LVa*T-4<-i3;M9UvZd+N7>b*eIwg:CC)c<>nO&#<IGe;__.thjZl<%w(Wk2xmp4Q@I#I9,DF]u7-P=.-_:YJ]aS@V"
    "?6*C()dOp7:WL,b&3Rg/.cmM9&r^>$(>.Z-I&J(Q0Hd5Q%7Co-b`-c<N(6r@ip+AurK<m86QIth*#v;-OBqi+L7wDE-Ir8K['m+DDSLwK&/.?-V%U_%3:qKNu$_b*B-kp7NaD'QdWQPK"
    "Yq[@>P)hI;*_F]u`Rb[.j8_Q/<&>uu+VsH$sM9TA%?)(vmJ80),P7E>)tjD%2L=-t#fK[%`v=Q8<FfNkgg^oIbah*#8/Qt$F&:K*-(N/'+1vMB,u()-a.VUU*#[e%gAAO(S>WlA2);Sa"
    ">gXm8YB`1d@K#n]76-a$U,mF<fX]idqd)<3,]J7JmW4`6]uks=4-72L(jEk+:bJ0M^q-8Dm_Z?0olP1C9Sa&H[d&c$ooQUj]Exd*3ZM@-WGW2%s',B-_M%>%Ul:#/'xoFM9QX-$.QN'>"
    "[%$Z$uF6pA6Ki2O5:8w*vP1<-1`[G,)-m#>0`P&#eb#.3i)rtB61(o'$?X3B</R90;eZ]%Ncq;-Tl]#F>2Qft^ae_5tKL9MUe9b*sLEQ95C&`=G?@Mj=wh*'3E>=-<)Gt*Iw)'QG:`@I"
    "wOf7&]1i'S01B+Ev/Nac#9S;=;YQpg_6U`*kVY39xK,[/6Aj7:'1Bm-_1EYfa1+o&o4hp7KN_Q(OlIo@S%;jVdn0'1<Vc52=u`3^o-n1'g4v58Hj&6_t7$##?M)c<$bgQ_'SY((-xkA#"
    "Y(,p'H9rIVY-b,'%bCPF7.J<Up^,(dU1VY*5#WkTU>h19w,WQhLI)3S#f$2(eb,jr*b;3Vw]*7NH%$c4Vs,eD9>XW8?N]o+(*pgC%/72LV-u<Hp,3@e^9UB1J+ak9-TN/mhKPg+AJYd$"
    "MlvAF_jCK*.O-^(63adMT->W%iewS8W6m2rtCpo'RS1R84=@paTKt)>=%&1[)*vp'u+x,VrwN;&]kuO9JDbg=pO$J*.jVe;u'm0dr9l,<*wMK*Oe=g8lV_KEBFkO'oU]^=[-792#ok,)"
    "i]lR8qQ2oA8wcRCZ^7w/Njh;?.stX?Q1>S1q4Bn$)K1<-rGdO'$Wr.Lc.CG)$/*JL4tNR/,SVO3,aUw'DJN:)Ss;wGn9A32ijw%FL+Z0Fn.U9;reSq)bmI32U==5ALuG&#Vf1398/pVo"
    "1*c-(aY168o<`JsSbk-,1N;$>0:OUas(3:8Z972LSfF8eb=c-;>SPw7.6hn3m`9^Xkn(r.qS[0;T%&Qc=+STRxX'q1BNk3&*eu2;&8q$&x>Q#Q7^Tf+6<(d%ZVmj2bDi%.3L2n+4W'$P"
    "iDDG)g,r%+?,$@?uou5tSe2aN_AQU*<h`e-GI7)?OK2A.d7_c)?wQ5AS@DL3r#7fSkgl6-++D:'A,uq7SvlB$pcpH'q3n0#_%dY#xCpr-l<F0NR@-##FEV6NTF6##$l84N1w?AO>'IAO"
    "URQ##V^Fv-XFbGM7Fl(N<3DhLGF%q.1rC$#:T__&Pi68%0xi_&[qFJ(77j_&JWoF.V735&T,[R*:xFR*K5>>#`bW-?4Ne_&6Ne_&6Ne_&n`kr-#GJcM6X;uM6X;uM(.a..^2TkL%oR(#"
    ";u.T%fAr%4tJ8&><1=GHZ_+m9/#H1F^R#SC#*N=BA9(D?v[UiFY>>^8p,KKF.W]L29uLkLlu/+4T<XoIB&hx=T1PcDaB&;HH+-AFr?(m9HZV)FKS8JCw;SD=6[^/DZUL`EUDf]GGlG&>"
    "w$)F./^n3+rlo+DB;5sIYGNk+i1t-69Jg--0pao7Sm#K)pdHW&;LuDNH@H>#/X-TI(;P>#,Gc>#0Su>#4`1?#8lC?#<xU?#@.i?#D:%@#HF7@#LRI@#P_[@#Tkn@#Xw*A#]-=A#a9OA#"
    "d<F&#*;G##.GY##2Sl##6`($#:l:$#>xL$#B.`$#F:r$#JF.%#NR@%#R_R%#Vke%#Zww%#_-4&#3^Rh%Sflr-k'MS.o?.5/sWel/wpEM0%3'/1)K^f1-d>G21&v(35>V`39V7A4=onx4"
    "A1OY5EI0;6Ibgr6M$HS7Q<)58C5w,;WoA*#[%T*#`1g*#d=#+#hI5+#lUG+#pbY+#tnl+#x$),#&1;,#*=M,#.I`,#2Ur,#6b.-#;w[H#iQtA#m^0B#qjBB#uvTB##-hB#'9$C#+E6C#"
    "/QHC#3^ZC#7jmC#;v)D#?,<D#C8ND#GDaD#KPsD#O]/E#g1A5#KA*1#gC17#MGd;#8(02#L-d3#rWM4#Hga1#,<w0#T.j<#O#'2#CYN1#qa^:#_4m3#o@/=#eG8=#t8J5#`+78#4uI-#"
    "m3B2#SB[8#Q0@8#i[*9#iOn8#1Nm;#^sN9#qh<9#:=x-#P;K2#$%X9#bC+.#Rg;<#mN=.#MTF.#RZO.#2?)4#Y#(/#[)1/#b;L/#dAU/#0Sv;#lY$0#n`-0#sf60#(F24#wrH0#%/e0#"
    "TmD<#%JSMFove:CTBEXI:<eh2g)B,3h2^G3i;#d3jD>)4kMYD4lVu`4m`:&5niUA5@(A5BA1]PBB:xlBCC=2CDLXMCEUtiCf&0g2'tN?PGT4CPGT4CPGT4CPGT4CPGT4CPGT4CPGT4CP"
    "GT4CPGT4CPGT4CPGT4CPGT4CPGT4CP-qekC`.9kEg^+F$kwViFJTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5o,^<-28ZI'O?;xp"
    "O?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xp;7q-#lLYI:xvD=#";

#endif

#define NK_CURSOR_DATA_W 90
#define NK_CURSOR_DATA_H 27
NK_GLOBAL const char nk_custom_cursor_data[NK_CURSOR_DATA_W * NK_CURSOR_DATA_H + 1] =
{
    "..-         -XXXXXXX-    X    -           X           -XXXXXXX          -          XXXXXXX"
    "..-         -X.....X-   X.X   -          X.X          -X.....X          -          X.....X"
    "---         -XXX.XXX-  X...X  -         X...X         -X....X           -           X....X"
    "X           -  X.X  - X.....X -        X.....X        -X...X            -            X...X"
    "XX          -  X.X  -X.......X-       X.......X       -X..X.X           -           X.X..X"
    "X.X         -  X.X  -XXXX.XXXX-       XXXX.XXXX       -X.X X.X          -          X.X X.X"
    "X..X        -  X.X  -   X.X   -          X.X          -XX   X.X         -         X.X   XX"
    "X...X       -  X.X  -   X.X   -    XX    X.X    XX    -      X.X        -        X.X      "
    "X....X      -  X.X  -   X.X   -   X.X    X.X    X.X   -       X.X       -       X.X       "
    "X.....X     -  X.X  -   X.X   -  X..X    X.X    X..X  -        X.X      -      X.X        "
    "X......X    -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -         X.X   XX-XX   X.X         "
    "X.......X   -  X.X  -   X.X   -X.....................X-          X.X X.X-X.X X.X          "
    "X........X  -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -           X.X..X-X..X.X           "
    "X.........X -XXX.XXX-   X.X   -  X..X    X.X    X..X  -            X...X-X...X            "
    "X..........X-X.....X-   X.X   -   X.X    X.X    X.X   -           X....X-X....X           "
    "X......XXXXX-XXXXXXX-   X.X   -    XX    X.X    XX    -          X.....X-X.....X          "
    "X...X..X    ---------   X.X   -          X.X          -          XXXXXXX-XXXXXXX          "
    "X..X X..X   -       -XXXX.XXXX-       XXXX.XXXX       ------------------------------------"
    "X.X  X..X   -       -X.......X-       X.......X       -    XX           XX    -           "
    "XX    X..X  -       - X.....X -        X.....X        -   X.X           X.X   -           "
    "      X..X          -  X...X  -         X...X         -  X..X           X..X  -           "
    "       XX           -   X.X   -          X.X          - X...XXXXXXXXXXXXX...X -           "
    "------------        -    X    -           X           -X.....................X-           "
    "                    ----------------------------------- X...XXXXXXXXXXXXX...X -           "
    "                                                      -  X..X           X..X  -           "
    "                                                      -   X.X           X.X   -           "
    "                                                      -    XX           XX    -           "
};

#ifdef __clang__
#pragma clang diagnostic pop
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

NK_GLOBAL unsigned char *nk__barrier;
NK_GLOBAL unsigned char *nk__barrier2;
NK_GLOBAL unsigned char *nk__barrier3;
NK_GLOBAL unsigned char *nk__barrier4;
NK_GLOBAL unsigned char *nk__dout;

NK_INTERN unsigned int
nk_decompress_length(unsigned char *input)
{
    return (unsigned int)((input[8] << 24) + (input[9] << 16) + (input[10] << 8) + input[11]);
}
NK_INTERN void
nk__match(unsigned char *data, unsigned int length)
{

    NK_ASSERT (nk__dout + length <= nk__barrier);
    if (nk__dout + length > nk__barrier) { nk__dout += length; return; }
    if (data < nk__barrier4) { nk__dout = nk__barrier+1; return; }
    while (length--) *nk__dout++ = *data++;
}
NK_INTERN void
nk__lit(unsigned char *data, unsigned int length)
{
    NK_ASSERT (nk__dout + length <= nk__barrier);
    if (nk__dout + length > nk__barrier) { nk__dout += length; return; }
    if (data < nk__barrier2) { nk__dout = nk__barrier+1; return; }
    NK_MEMCPY(nk__dout, data, length);
    nk__dout += length;
}
NK_INTERN unsigned char*
nk_decompress_token(unsigned char *i)
{
    #define nk__in2(x)   ((i[x] << 8) + i[(x)+1])
    #define nk__in3(x)   ((i[x] << 16) + nk__in2((x)+1))
    #define nk__in4(x)   ((i[x] << 24) + nk__in3((x)+1))

    if (*i >= 0x20) {
        if (*i >= 0x80)       nk__match(nk__dout-i[1]-1, (unsigned int)i[0] - 0x80 + 1), i += 2;
        else if (*i >= 0x40)  nk__match(nk__dout-(nk__in2(0) - 0x4000 + 1), (unsigned int)i[2]+1), i += 3;
        else   nk__lit(i+1, (unsigned int)i[0] - 0x20 + 1), i += 1 + (i[0] - 0x20 + 1);
    } else {
        if (*i >= 0x18)       nk__match(nk__dout-(unsigned int)(nk__in3(0) - 0x180000 + 1), (unsigned int)i[3]+1), i += 4;
        else if (*i >= 0x10)  nk__match(nk__dout-(unsigned int)(nk__in3(0) - 0x100000 + 1), (unsigned int)nk__in2(3)+1), i += 5;
        else if (*i >= 0x08)  nk__lit(i+2, (unsigned int)nk__in2(0) - 0x0800 + 1), i += 2 + (nk__in2(0) - 0x0800 + 1);
        else if (*i == 0x07)  nk__lit(i+3, (unsigned int)nk__in2(1) + 1), i += 3 + (nk__in2(1) + 1);
        else if (*i == 0x06)  nk__match(nk__dout-(unsigned int)(nk__in3(1)+1), i[4]+1u), i += 5;
        else if (*i == 0x04)  nk__match(nk__dout-(unsigned int)(nk__in3(1)+1), (unsigned int)nk__in2(4)+1u), i += 6;
    }
    return i;
}
NK_INTERN unsigned int
nk_adler32(unsigned int adler32, unsigned char *buffer, unsigned int buflen)
{
    const unsigned long ADLER_MOD = 65521;
    unsigned long s1 = adler32 & 0xffff, s2 = adler32 >> 16;
    unsigned long blocklen, i;

    blocklen = buflen % 5552;
    while (buflen) {
        for (i=0; i + 7 < blocklen; i += 8) {
            s1 += buffer[0]; s2 += s1;
            s1 += buffer[1]; s2 += s1;
            s1 += buffer[2]; s2 += s1;
            s1 += buffer[3]; s2 += s1;
            s1 += buffer[4]; s2 += s1;
            s1 += buffer[5]; s2 += s1;
            s1 += buffer[6]; s2 += s1;
            s1 += buffer[7]; s2 += s1;
            buffer += 8;
        }
        for (; i < blocklen; ++i) {
            s1 += *buffer++; s2 += s1;
        }

        s1 %= ADLER_MOD; s2 %= ADLER_MOD;
        buflen -= (unsigned int)blocklen;
        blocklen = 5552;
    }
    return (unsigned int)(s2 << 16) + (unsigned int)s1;
}
NK_INTERN unsigned int
nk_decompress(unsigned char *output, unsigned char *i, unsigned int length)
{
    unsigned int olen;
    if (nk__in4(0) != 0x57bC0000) return 0;
    if (nk__in4(4) != 0)          return 0;
    olen = nk_decompress_length(i);
    nk__barrier2 = i;
    nk__barrier3 = i+length;
    nk__barrier = output + olen;
    nk__barrier4 = output;
    i += 16;

    nk__dout = output;
    for (;;) {
        unsigned char *old_i = i;
        i = nk_decompress_token(i);
        if (i == old_i) {
            if (*i == 0x05 && i[1] == 0xfa) {
                NK_ASSERT(nk__dout == output + olen);
                if (nk__dout != output + olen) return 0;
                if (nk_adler32(1, output, olen) != (unsigned int) nk__in4(2))
                    return 0;
                return olen;
            } else {
                NK_ASSERT(0);
                return 0;
            }
        }
        NK_ASSERT(nk__dout <= output + olen);
        if (nk__dout > output + olen)
            return 0;
    }
}
NK_INTERN unsigned int
nk_decode_85_byte(char c)
{
    return (unsigned int)((c >= '\\') ? c-36 : c-35);
}
NK_INTERN void
nk_decode_85(unsigned char* dst, const unsigned char* src)
{
    while (*src)
    {
        unsigned int tmp =
            nk_decode_85_byte((char)src[0]) +
            85 * (nk_decode_85_byte((char)src[1]) +
            85 * (nk_decode_85_byte((char)src[2]) +
            85 * (nk_decode_85_byte((char)src[3]) +
            85 * nk_decode_85_byte((char)src[4]))));

        dst[0] = (unsigned char)((tmp >> 0) & 0xFF);
        dst[1] = (unsigned char)((tmp >> 8) & 0xFF);
        dst[2] = (unsigned char)((tmp >> 16) & 0xFF);
        dst[3] = (unsigned char)((tmp >> 24) & 0xFF);

        src += 5;
        dst += 4;
    }
}

NK_API struct nk_font_config
nk_font_config(float pixel_height)
{
    struct nk_font_config cfg;
    nk_zero_struct(cfg);
    cfg.ttf_blob = 0;
    cfg.ttf_size = 0;
    cfg.ttf_data_owned_by_atlas = 0;
    cfg.size = pixel_height;
    cfg.oversample_h = 3;
    cfg.oversample_v = 1;
    cfg.pixel_snap = 0;
    cfg.coord_type = NK_COORD_UV;
    cfg.spacing = nk_vec2(0,0);
    cfg.range = nk_font_default_glyph_ranges();
    cfg.merge_mode = 0;
    cfg.fallback_glyph = '?';
    cfg.font = 0;
    cfg.n = 0;
    return cfg;
}
#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void
nk_font_atlas_init_default(struct nk_font_atlas *atlas)
{
    NK_ASSERT(atlas);
    if (!atlas) return;
    nk_zero_struct(*atlas);
    atlas->temporary.userdata.ptr = 0;
    atlas->temporary.alloc = nk_malloc;
    atlas->temporary.free = nk_mfree;
    atlas->permanent.userdata.ptr = 0;
    atlas->permanent.alloc = nk_malloc;
    atlas->permanent.free = nk_mfree;
}
#endif
NK_API void
nk_font_atlas_init(struct nk_font_atlas *atlas, struct nk_allocator *alloc)
{
    NK_ASSERT(atlas);
    NK_ASSERT(alloc);
    if (!atlas || !alloc) return;
    nk_zero_struct(*atlas);
    atlas->permanent = *alloc;
    atlas->temporary = *alloc;
}
NK_API void
nk_font_atlas_init_custom(struct nk_font_atlas *atlas,
    struct nk_allocator *permanent, struct nk_allocator *temporary)
{
    NK_ASSERT(atlas);
    NK_ASSERT(permanent);
    NK_ASSERT(temporary);
    if (!atlas || !permanent || !temporary) return;
    nk_zero_struct(*atlas);
    atlas->permanent = *permanent;
    atlas->temporary = *temporary;
}
NK_API void
nk_font_atlas_begin(struct nk_font_atlas *atlas)
{
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc && atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc && atlas->permanent.free);
    if (!atlas || !atlas->permanent.alloc || !atlas->permanent.free ||
        !atlas->temporary.alloc || !atlas->temporary.free) return;
    if (atlas->glyphs) {
        atlas->permanent.free(atlas->permanent.userdata, atlas->glyphs);
        atlas->glyphs = 0;
    }
    if (atlas->pixel) {
        atlas->permanent.free(atlas->permanent.userdata, atlas->pixel);
        atlas->pixel = 0;
    }
}
NK_API struct nk_font*
nk_font_atlas_add(struct nk_font_atlas *atlas, const struct nk_font_config *config)
{
    struct nk_font *font = 0;
    struct nk_font_config *cfg;

    NK_ASSERT(atlas);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);

    NK_ASSERT(config);
    NK_ASSERT(config->ttf_blob);
    NK_ASSERT(config->ttf_size);
    NK_ASSERT(config->size > 0.0f);

    if (!atlas || !config || !config->ttf_blob || !config->ttf_size || config->size <= 0.0f||
        !atlas->permanent.alloc || !atlas->permanent.free ||
        !atlas->temporary.alloc || !atlas->temporary.free)
        return 0;

    cfg = (struct nk_font_config*)
        atlas->permanent.alloc(atlas->permanent.userdata,0, sizeof(struct nk_font_config));
    NK_MEMCPY(cfg, config, sizeof(*config));
    cfg->n = cfg;
    cfg->p = cfg;

    if (!config->merge_mode) {

        if (!atlas->config) {
            atlas->config = cfg;
            cfg->next = 0;
        } else {
            struct nk_font_config *i = atlas->config;
            while (i->next) i = i->next;
            i->next = cfg;
            cfg->next = 0;
        }

        font = (struct nk_font*)
            atlas->permanent.alloc(atlas->permanent.userdata,0, sizeof(struct nk_font));
        NK_ASSERT(font);
        nk_zero(font, sizeof(*font));
        if (!font) return 0;
        font->config = cfg;

        if (!atlas->fonts) {
            atlas->fonts = font;
            font->next = 0;
        } else {
            struct nk_font *i = atlas->fonts;
            while (i->next) i = i->next;
            i->next = font;
            font->next = 0;
        }
        cfg->font = &font->info;
    } else {

        struct nk_font *f = 0;
        struct nk_font_config *c = 0;
        NK_ASSERT(atlas->font_num);
        f = atlas->fonts;
        c = f->config;
        cfg->font = &f->info;

        cfg->n = c;
        cfg->p = c->p;
        c->p->n = cfg;
        c->p = cfg;
    }

    if (!config->ttf_data_owned_by_atlas) {
        cfg->ttf_blob = atlas->permanent.alloc(atlas->permanent.userdata,0, cfg->ttf_size);
        NK_ASSERT(cfg->ttf_blob);
        if (!cfg->ttf_blob) {
            atlas->font_num++;
            return 0;
        }
        NK_MEMCPY(cfg->ttf_blob, config->ttf_blob, cfg->ttf_size);
        cfg->ttf_data_owned_by_atlas = 1;
    }
    atlas->font_num++;
    return font;
}
NK_API struct nk_font*
nk_font_atlas_add_from_memory(struct nk_font_atlas *atlas, void *memory,
    nk_size size, float height, const struct nk_font_config *config)
{
    struct nk_font_config cfg;
    NK_ASSERT(memory);
    NK_ASSERT(size);

    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);
    if (!atlas || !atlas->temporary.alloc || !atlas->temporary.free || !memory || !size ||
        !atlas->permanent.alloc || !atlas->permanent.free)
        return 0;

    cfg = (config) ? *config: nk_font_config(height);
    cfg.ttf_blob = memory;
    cfg.ttf_size = size;
    cfg.size = height;
    cfg.ttf_data_owned_by_atlas = 0;
    return nk_font_atlas_add(atlas, &cfg);
}
#ifdef NK_INCLUDE_STANDARD_IO
NK_API struct nk_font*
nk_font_atlas_add_from_file(struct nk_font_atlas *atlas, const char *file_path,
    float height, const struct nk_font_config *config)
{
    nk_size size;
    char *memory;
    struct nk_font_config cfg;

    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);

    if (!atlas || !file_path) return 0;
    memory = nk_file_load(file_path, &size, &atlas->permanent);
    if (!memory) return 0;

    cfg = (config) ? *config: nk_font_config(height);
    cfg.ttf_blob = memory;
    cfg.ttf_size = size;
    cfg.size = height;
    cfg.ttf_data_owned_by_atlas = 1;
    return nk_font_atlas_add(atlas, &cfg);
}
#endif
NK_API struct nk_font*
nk_font_atlas_add_compressed(struct nk_font_atlas *atlas,
    void *compressed_data, nk_size compressed_size, float height,
    const struct nk_font_config *config)
{
    unsigned int decompressed_size;
    void *decompressed_data;
    struct nk_font_config cfg;

    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);

    NK_ASSERT(compressed_data);
    NK_ASSERT(compressed_size);
    if (!atlas || !compressed_data || !atlas->temporary.alloc || !atlas->temporary.free ||
        !atlas->permanent.alloc || !atlas->permanent.free)
        return 0;

    decompressed_size = nk_decompress_length((unsigned char*)compressed_data);
    decompressed_data = atlas->permanent.alloc(atlas->permanent.userdata,0,decompressed_size);
    NK_ASSERT(decompressed_data);
    if (!decompressed_data) return 0;
    nk_decompress((unsigned char*)decompressed_data, (unsigned char*)compressed_data,
        (unsigned int)compressed_size);

    cfg = (config) ? *config: nk_font_config(height);
    cfg.ttf_blob = decompressed_data;
    cfg.ttf_size = decompressed_size;
    cfg.size = height;
    cfg.ttf_data_owned_by_atlas = 1;
    return nk_font_atlas_add(atlas, &cfg);
}
NK_API struct nk_font*
nk_font_atlas_add_compressed_base85(struct nk_font_atlas *atlas,
    const char *data_base85, float height, const struct nk_font_config *config)
{
    int compressed_size;
    void *compressed_data;
    struct nk_font *font;

    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);

    NK_ASSERT(data_base85);
    if (!atlas || !data_base85 || !atlas->temporary.alloc || !atlas->temporary.free ||
        !atlas->permanent.alloc || !atlas->permanent.free)
        return 0;

    compressed_size = (((int)nk_strlen(data_base85) + 4) / 5) * 4;
    compressed_data = atlas->temporary.alloc(atlas->temporary.userdata,0, (nk_size)compressed_size);
    NK_ASSERT(compressed_data);
    if (!compressed_data) return 0;
    nk_decode_85((unsigned char*)compressed_data, (const unsigned char*)data_base85);
    font = nk_font_atlas_add_compressed(atlas, compressed_data,
                    (nk_size)compressed_size, height, config);
    atlas->temporary.free(atlas->temporary.userdata, compressed_data);
    return font;
}

#ifdef NK_INCLUDE_DEFAULT_FONT
NK_API struct nk_font*
nk_font_atlas_add_default(struct nk_font_atlas *atlas,
    float pixel_height, const struct nk_font_config *config)
{
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);
    return nk_font_atlas_add_compressed_base85(atlas,
        nk_proggy_clean_ttf_compressed_data_base85, pixel_height, config);
}
#endif
NK_API const void*
nk_font_atlas_bake(struct nk_font_atlas *atlas, int *width, int *height,
    enum nk_font_atlas_format fmt)
{
    int i = 0;
    void *tmp = 0;
    nk_size tmp_size, img_size;
    struct nk_font *font_iter;
    struct nk_font_baker *baker;

    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);

    NK_ASSERT(width);
    NK_ASSERT(height);
    if (!atlas || !width || !height ||
        !atlas->temporary.alloc || !atlas->temporary.free ||
        !atlas->permanent.alloc || !atlas->permanent.free)
        return 0;

#ifdef NK_INCLUDE_DEFAULT_FONT

    if (!atlas->font_num)
        atlas->default_font = nk_font_atlas_add_default(atlas, 13.0f, 0);
#endif
    NK_ASSERT(atlas->font_num);
    if (!atlas->font_num) return 0;

    nk_font_baker_memory(&tmp_size, &atlas->glyph_count, atlas->config, atlas->font_num);
    tmp = atlas->temporary.alloc(atlas->temporary.userdata,0, tmp_size);
    NK_ASSERT(tmp);
    if (!tmp) goto failed;
    NK_MEMSET(tmp,0,tmp_size);

    baker = nk_font_baker(tmp, atlas->glyph_count, atlas->font_num, &atlas->temporary);
    atlas->glyphs = (struct nk_font_glyph*)atlas->permanent.alloc(
        atlas->permanent.userdata,0, sizeof(struct nk_font_glyph)*(nk_size)atlas->glyph_count);
    NK_ASSERT(atlas->glyphs);
    if (!atlas->glyphs)
        goto failed;

    atlas->custom.w = (NK_CURSOR_DATA_W*2)+1;
    atlas->custom.h = NK_CURSOR_DATA_H + 1;
    if (!nk_font_bake_pack(baker, &img_size, width, height, &atlas->custom,
        atlas->config, atlas->font_num, &atlas->temporary))
        goto failed;

    atlas->pixel = atlas->temporary.alloc(atlas->temporary.userdata,0, img_size);
    NK_ASSERT(atlas->pixel);
    if (!atlas->pixel)
        goto failed;

    nk_font_bake(baker, atlas->pixel, *width, *height,
        atlas->glyphs, atlas->glyph_count, atlas->config, atlas->font_num);
    nk_font_bake_custom_data(atlas->pixel, *width, *height, atlas->custom,
            nk_custom_cursor_data, NK_CURSOR_DATA_W, NK_CURSOR_DATA_H, '.', 'X');

    if (fmt == NK_FONT_ATLAS_RGBA32) {

        void *img_rgba = atlas->temporary.alloc(atlas->temporary.userdata,0,
                            (nk_size)(*width * *height * 4));
        NK_ASSERT(img_rgba);
        if (!img_rgba) goto failed;
        nk_font_bake_convert(img_rgba, *width, *height, atlas->pixel);
        atlas->temporary.free(atlas->temporary.userdata, atlas->pixel);
        atlas->pixel = img_rgba;
    }
    atlas->tex_width = *width;
    atlas->tex_height = *height;

    for (font_iter = atlas->fonts; font_iter; font_iter = font_iter->next) {
        struct nk_font *font = font_iter;
        struct nk_font_config *config = font->config;
        nk_font_init(font, config->size, config->fallback_glyph, atlas->glyphs,
            config->font, nk_handle_ptr(0));
    }

    {NK_STORAGE const struct nk_vec2 nk_cursor_data[NK_CURSOR_COUNT][3] = {

        {{ 0, 3},   {12,19},    { 0, 0}},
        {{13, 0},   { 7,16},    { 4, 8}},
        {{31, 0},   {23,23},    {11,11}},
        {{21, 0},   { 9, 23},   { 5,11}},
        {{55,18},   {23, 9},    {11, 5}},
        {{73, 0},   {17,17},    { 9, 9}},
        {{55, 0},   {17,17},    { 9, 9}}
    };
    for (i = 0; i < NK_CURSOR_COUNT; ++i) {
        struct nk_cursor *cursor = &atlas->cursors[i];
        cursor->img.w = (unsigned short)*width;
        cursor->img.h = (unsigned short)*height;
        cursor->img.region[0] = (unsigned short)(atlas->custom.x + nk_cursor_data[i][0].x);
        cursor->img.region[1] = (unsigned short)(atlas->custom.y + nk_cursor_data[i][0].y);
        cursor->img.region[2] = (unsigned short)nk_cursor_data[i][1].x;
        cursor->img.region[3] = (unsigned short)nk_cursor_data[i][1].y;
        cursor->size = nk_cursor_data[i][1];
        cursor->offset = nk_cursor_data[i][2];
    }}

    atlas->temporary.free(atlas->temporary.userdata, tmp);
    return atlas->pixel;

failed:

    if (tmp) atlas->temporary.free(atlas->temporary.userdata, tmp);
    if (atlas->glyphs) {
        atlas->permanent.free(atlas->permanent.userdata, atlas->glyphs);
        atlas->glyphs = 0;
    }
    if (atlas->pixel) {
        atlas->temporary.free(atlas->temporary.userdata, atlas->pixel);
        atlas->pixel = 0;
    }
    return 0;
}
NK_API void
nk_font_atlas_end(struct nk_font_atlas *atlas, nk_handle texture,
    struct nk_draw_null_texture *tex_null)
{
    int i = 0;
    struct nk_font *font_iter;
    NK_ASSERT(atlas);
    if (!atlas) {
        if (!tex_null) return;
        tex_null->texture = texture;
        tex_null->uv = nk_vec2(0.5f,0.5f);
    }
    if (tex_null) {
        tex_null->texture = texture;
        tex_null->uv.x = (atlas->custom.x + 0.5f)/(float)atlas->tex_width;
        tex_null->uv.y = (atlas->custom.y + 0.5f)/(float)atlas->tex_height;
    }
    for (font_iter = atlas->fonts; font_iter; font_iter = font_iter->next) {
        font_iter->texture = texture;
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
        font_iter->handle.texture = texture;
#endif
    }
    for (i = 0; i < NK_CURSOR_COUNT; ++i)
        atlas->cursors[i].img.handle = texture;

    atlas->temporary.free(atlas->temporary.userdata, atlas->pixel);
    atlas->pixel = 0;
    atlas->tex_width = 0;
    atlas->tex_height = 0;
    atlas->custom.x = 0;
    atlas->custom.y = 0;
    atlas->custom.w = 0;
    atlas->custom.h = 0;
}
NK_API void
nk_font_atlas_cleanup(struct nk_font_atlas *atlas)
{
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);
    if (!atlas || !atlas->permanent.alloc || !atlas->permanent.free) return;
    if (atlas->config) {
        struct nk_font_config *iter;
        for (iter = atlas->config; iter; iter = iter->next) {
            struct nk_font_config *i;
            for (i = iter->n; i != iter; i = i->n) {
                atlas->permanent.free(atlas->permanent.userdata, i->ttf_blob);
                i->ttf_blob = 0;
            }
            atlas->permanent.free(atlas->permanent.userdata, iter->ttf_blob);
            iter->ttf_blob = 0;
        }
    }
}
NK_API void
nk_font_atlas_clear(struct nk_font_atlas *atlas)
{
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->temporary.alloc);
    NK_ASSERT(atlas->temporary.free);
    NK_ASSERT(atlas->permanent.alloc);
    NK_ASSERT(atlas->permanent.free);
    if (!atlas || !atlas->permanent.alloc || !atlas->permanent.free) return;

    if (atlas->config) {
        struct nk_font_config *iter, *next;
        for (iter = atlas->config; iter; iter = next) {
            struct nk_font_config *i, *n;
            for (i = iter->n; i != iter; i = n) {
                n = i->n;
                if (i->ttf_blob)
                    atlas->permanent.free(atlas->permanent.userdata, i->ttf_blob);
                atlas->permanent.free(atlas->permanent.userdata, i);
            }
            next = iter->next;
            if (i->ttf_blob)
                atlas->permanent.free(atlas->permanent.userdata, iter->ttf_blob);
            atlas->permanent.free(atlas->permanent.userdata, iter);
        }
        atlas->config = 0;
    }
    if (atlas->fonts) {
        struct nk_font *iter, *next;
        for (iter = atlas->fonts; iter; iter = next) {
            next = iter->next;
            atlas->permanent.free(atlas->permanent.userdata, iter);
        }
        atlas->fonts = 0;
    }
    if (atlas->glyphs)
        atlas->permanent.free(atlas->permanent.userdata, atlas->glyphs);
    nk_zero_struct(*atlas);
}
#endif

NK_API void
nk_input_begin(struct nk_context *ctx)
{
    int i;
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
    for (i = 0; i < NK_BUTTON_MAX; ++i)
        in->mouse.buttons[i].clicked = 0;

    in->keyboard.text_len = 0;
    in->mouse.scroll_delta = nk_vec2(0,0);
    in->mouse.prev.x = in->mouse.pos.x;
    in->mouse.prev.y = in->mouse.pos.y;
    in->mouse.delta.x = 0;
    in->mouse.delta.y = 0;
    for (i = 0; i < NK_KEY_MAX; i++)
        in->keyboard.keys[i].clicked = 0;
}
NK_API void
nk_input_end(struct nk_context *ctx)
{
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
    if (in->mouse.grab)
        in->mouse.grab = 0;
    if (in->mouse.ungrab) {
        in->mouse.grabbed = 0;
        in->mouse.ungrab = 0;
        in->mouse.grab = 0;
    }
}
NK_API void
nk_input_motion(struct nk_context *ctx, int x, int y)
{
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
    in->mouse.pos.x = (float)x;
    in->mouse.pos.y = (float)y;
    in->mouse.delta.x = in->mouse.pos.x - in->mouse.prev.x;
    in->mouse.delta.y = in->mouse.pos.y - in->mouse.prev.y;
}
NK_API void
nk_input_key(struct nk_context *ctx, enum nk_keys key, nk_bool down)
{
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
#ifdef NK_KEYSTATE_BASED_INPUT
    if (in->keyboard.keys[key].down != down)
        in->keyboard.keys[key].clicked++;
#else
    in->keyboard.keys[key].clicked++;
#endif
    in->keyboard.keys[key].down = down;
}
NK_API void
nk_input_button(struct nk_context *ctx, enum nk_buttons id, int x, int y, nk_bool down)
{
    struct nk_mouse_button *btn;
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
    if (in->mouse.buttons[id].down == down) return;

    btn = &in->mouse.buttons[id];
    btn->clicked_pos.x = (float)x;
    btn->clicked_pos.y = (float)y;
    btn->down = down;
    btn->clicked++;

    in->mouse.delta.x = 0;
    in->mouse.delta.y = 0;
#ifdef NK_BUTTON_TRIGGER_ON_RELEASE
    if (down == 1 && id == NK_BUTTON_LEFT)
    {
        in->mouse.down_pos.x = btn->clicked_pos.x;
        in->mouse.down_pos.y = btn->clicked_pos.y;
    }
#endif
}
NK_API void
nk_input_scroll(struct nk_context *ctx, struct nk_vec2 val)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    ctx->input.mouse.scroll_delta.x += val.x;
    ctx->input.mouse.scroll_delta.y += val.y;
}
NK_API void
nk_input_glyph(struct nk_context *ctx, const nk_glyph glyph)
{
    int len = 0;
    nk_rune unicode;
    struct nk_input *in;

    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;

    len = nk_utf_decode(glyph, &unicode, NK_UTF_SIZE);
    if (len && ((in->keyboard.text_len + len) < NK_INPUT_MAX)) {
        nk_utf_encode(unicode, &in->keyboard.text[in->keyboard.text_len],
            NK_INPUT_MAX - in->keyboard.text_len);
        in->keyboard.text_len += len;
    }
}
NK_API void
nk_input_char(struct nk_context *ctx, char c)
{
    nk_glyph glyph;
    NK_ASSERT(ctx);
    if (!ctx) return;
    glyph[0] = c;
    nk_input_glyph(ctx, glyph);
}
NK_API void
nk_input_unicode(struct nk_context *ctx, nk_rune unicode)
{
    nk_glyph rune;
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_utf_encode(unicode, rune, NK_UTF_SIZE);
    nk_input_glyph(ctx, rune);
}
NK_API nk_bool
nk_input_has_mouse_click(const struct nk_input *i, enum nk_buttons id)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    return (btn->clicked && btn->down == nk_false) ? nk_true : nk_false;
}
NK_API nk_bool
nk_input_has_mouse_click_in_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    if (!NK_INBOX(btn->clicked_pos.x,btn->clicked_pos.y,b.x,b.y,b.w,b.h))
        return nk_false;
    return nk_true;
}
NK_API nk_bool
nk_input_has_mouse_click_in_button_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
#ifdef NK_BUTTON_TRIGGER_ON_RELEASE
    if (!NK_INBOX(btn->clicked_pos.x,btn->clicked_pos.y,b.x,b.y,b.w,b.h)
        || !NK_INBOX(i->mouse.down_pos.x,i->mouse.down_pos.y,b.x,b.y,b.w,b.h))
#else
    if (!NK_INBOX(btn->clicked_pos.x,btn->clicked_pos.y,b.x,b.y,b.w,b.h))
#endif
        return nk_false;
    return nk_true;
}
NK_API nk_bool
nk_input_has_mouse_click_down_in_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b, nk_bool down)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    return nk_input_has_mouse_click_in_rect(i, id, b) && (btn->down == down);
}
NK_API nk_bool
nk_input_is_mouse_click_in_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    return (nk_input_has_mouse_click_down_in_rect(i, id, b, nk_false) &&
            btn->clicked) ? nk_true : nk_false;
}
NK_API nk_bool
nk_input_is_mouse_click_down_in_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b, nk_bool down)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    return (nk_input_has_mouse_click_down_in_rect(i, id, b, down) &&
            btn->clicked) ? nk_true : nk_false;
}
NK_API nk_bool
nk_input_any_mouse_click_in_rect(const struct nk_input *in, struct nk_rect b)
{
    int i, down = 0;
    for (i = 0; i < NK_BUTTON_MAX; ++i)
        down = down || nk_input_is_mouse_click_in_rect(in, (enum nk_buttons)i, b);
    return down;
}
NK_API nk_bool
nk_input_is_mouse_hovering_rect(const struct nk_input *i, struct nk_rect rect)
{
    if (!i) return nk_false;
    return NK_INBOX(i->mouse.pos.x, i->mouse.pos.y, rect.x, rect.y, rect.w, rect.h);
}
NK_API nk_bool
nk_input_is_mouse_prev_hovering_rect(const struct nk_input *i, struct nk_rect rect)
{
    if (!i) return nk_false;
    return NK_INBOX(i->mouse.prev.x, i->mouse.prev.y, rect.x, rect.y, rect.w, rect.h);
}
NK_API nk_bool
nk_input_mouse_clicked(const struct nk_input *i, enum nk_buttons id, struct nk_rect rect)
{
    if (!i) return nk_false;
    if (!nk_input_is_mouse_hovering_rect(i, rect)) return nk_false;
    return nk_input_is_mouse_click_in_rect(i, id, rect);
}
NK_API nk_bool
nk_input_is_mouse_down(const struct nk_input *i, enum nk_buttons id)
{
    if (!i) return nk_false;
    return i->mouse.buttons[id].down;
}
NK_API nk_bool
nk_input_is_mouse_pressed(const struct nk_input *i, enum nk_buttons id)
{
    const struct nk_mouse_button *b;
    if (!i) return nk_false;
    b = &i->mouse.buttons[id];
    if (b->down && b->clicked)
        return nk_true;
    return nk_false;
}
NK_API nk_bool
nk_input_is_mouse_released(const struct nk_input *i, enum nk_buttons id)
{
    if (!i) return nk_false;
    return (!i->mouse.buttons[id].down && i->mouse.buttons[id].clicked);
}
NK_API nk_bool
nk_input_is_key_pressed(const struct nk_input *i, enum nk_keys key)
{
    const struct nk_key *k;
    if (!i) return nk_false;
    k = &i->keyboard.keys[key];
    if ((k->down && k->clicked) || (!k->down && k->clicked >= 2))
        return nk_true;
    return nk_false;
}
NK_API nk_bool
nk_input_is_key_released(const struct nk_input *i, enum nk_keys key)
{
    const struct nk_key *k;
    if (!i) return nk_false;
    k = &i->keyboard.keys[key];
    if ((!k->down && k->clicked) || (k->down && k->clicked >= 2))
        return nk_true;
    return nk_false;
}
NK_API nk_bool
nk_input_is_key_down(const struct nk_input *i, enum nk_keys key)
{
    const struct nk_key *k;
    if (!i) return nk_false;
    k = &i->keyboard.keys[key];
    if (k->down) return nk_true;
    return nk_false;
}

NK_API void nk_style_default(struct nk_context *ctx){nk_style_from_table(ctx, 0);}
#define NK_COLOR_MAP(NK_COLOR)\
    NK_COLOR(NK_COLOR_TEXT,                     175,175,175,255) \
    NK_COLOR(NK_COLOR_WINDOW,                   45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_HEADER,                   40, 40, 40, 255) \
    NK_COLOR(NK_COLOR_BORDER,                   65, 65, 65, 255) \
    NK_COLOR(NK_COLOR_BUTTON,                   50, 50, 50, 255) \
    NK_COLOR(NK_COLOR_BUTTON_HOVER,             40, 40, 40, 255) \
    NK_COLOR(NK_COLOR_BUTTON_ACTIVE,            35, 35, 35, 255) \
    NK_COLOR(NK_COLOR_TOGGLE,                   100,100,100,255) \
    NK_COLOR(NK_COLOR_TOGGLE_HOVER,             120,120,120,255) \
    NK_COLOR(NK_COLOR_TOGGLE_CURSOR,            45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_SELECT,                   45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_SELECT_ACTIVE,            35, 35, 35,255) \
    NK_COLOR(NK_COLOR_SLIDER,                   38, 38, 38, 255) \
    NK_COLOR(NK_COLOR_SLIDER_CURSOR,            100,100,100,255) \
    NK_COLOR(NK_COLOR_SLIDER_CURSOR_HOVER,      120,120,120,255) \
    NK_COLOR(NK_COLOR_SLIDER_CURSOR_ACTIVE,     150,150,150,255) \
    NK_COLOR(NK_COLOR_PROPERTY,                 38, 38, 38, 255) \
    NK_COLOR(NK_COLOR_EDIT,                     38, 38, 38, 255)  \
    NK_COLOR(NK_COLOR_EDIT_CURSOR,              175,175,175,255) \
    NK_COLOR(NK_COLOR_COMBO,                    45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_CHART,                    120,120,120,255) \
    NK_COLOR(NK_COLOR_CHART_COLOR,              45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_CHART_COLOR_HIGHLIGHT,    255, 0,  0, 255) \
    NK_COLOR(NK_COLOR_SCROLLBAR,                40, 40, 40, 255) \
    NK_COLOR(NK_COLOR_SCROLLBAR_CURSOR,         100,100,100,255) \
    NK_COLOR(NK_COLOR_SCROLLBAR_CURSOR_HOVER,   120,120,120,255) \
    NK_COLOR(NK_COLOR_SCROLLBAR_CURSOR_ACTIVE,  150,150,150,255) \
    NK_COLOR(NK_COLOR_TAB_HEADER,               40, 40, 40,255)

NK_GLOBAL const struct nk_color
nk_default_color_style[NK_COLOR_COUNT] = {
#define NK_COLOR(a,b,c,d,e) {b,c,d,e},
    NK_COLOR_MAP(NK_COLOR)
#undef NK_COLOR
};
NK_GLOBAL const char *nk_color_names[NK_COLOR_COUNT] = {
#define NK_COLOR(a,b,c,d,e) #a,
    NK_COLOR_MAP(NK_COLOR)
#undef NK_COLOR
};

NK_API const char*
nk_style_get_color_by_name(enum nk_style_colors c)
{
    return nk_color_names[c];
}
NK_API struct nk_style_item
nk_style_item_color(struct nk_color col)
{
    struct nk_style_item i;
    i.type = NK_STYLE_ITEM_COLOR;
    i.data.color = col;
    return i;
}
NK_API struct nk_style_item
nk_style_item_image(struct nk_image img)
{
    struct nk_style_item i;
    i.type = NK_STYLE_ITEM_IMAGE;
    i.data.image = img;
    return i;
}
NK_API struct nk_style_item
nk_style_item_nine_slice(struct nk_nine_slice slice)
{
    struct nk_style_item i;
    i.type = NK_STYLE_ITEM_NINE_SLICE;
    i.data.slice = slice;
    return i;
}
NK_API struct nk_style_item
nk_style_item_hide(void)
{
    struct nk_style_item i;
    i.type = NK_STYLE_ITEM_COLOR;
    i.data.color = nk_rgba(0,0,0,0);
    return i;
}
NK_API void
nk_style_from_table(struct nk_context *ctx, const struct nk_color *table)
{
    struct nk_style *style;
    struct nk_style_text *text;
    struct nk_style_button *button;
    struct nk_style_toggle *toggle;
    struct nk_style_selectable *select;
    struct nk_style_slider *slider;
    struct nk_style_progress *prog;
    struct nk_style_scrollbar *scroll;
    struct nk_style_edit *edit;
    struct nk_style_property *property;
    struct nk_style_combo *combo;
    struct nk_style_chart *chart;
    struct nk_style_tab *tab;
    struct nk_style_window *win;

    NK_ASSERT(ctx);
    if (!ctx) return;
    style = &ctx->style;
    table = (!table) ? nk_default_color_style: table;

    text = &style->text;
    text->color = table[NK_COLOR_TEXT];
    text->padding = nk_vec2(0,0);

    button = &style->button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_BUTTON]);
    button->hover           = nk_style_item_color(table[NK_COLOR_BUTTON_HOVER]);
    button->active          = nk_style_item_color(table[NK_COLOR_BUTTON_ACTIVE]);
    button->border_color    = table[NK_COLOR_BORDER];
    button->text_background = table[NK_COLOR_BUTTON];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->image_padding   = nk_vec2(0.0f,0.0f);
    button->touch_padding   = nk_vec2(0.0f, 0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 1.0f;
    button->rounding        = 4.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    button = &style->contextual_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->hover           = nk_style_item_color(table[NK_COLOR_BUTTON_HOVER]);
    button->active          = nk_style_item_color(table[NK_COLOR_BUTTON_ACTIVE]);
    button->border_color    = table[NK_COLOR_WINDOW];
    button->text_background = table[NK_COLOR_WINDOW];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    button = &style->menu_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->hover           = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->active          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->border_color    = table[NK_COLOR_WINDOW];
    button->text_background = table[NK_COLOR_WINDOW];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 1.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    toggle = &style->checkbox;
    nk_zero_struct(*toggle);
    toggle->normal          = nk_style_item_color(table[NK_COLOR_TOGGLE]);
    toggle->hover           = nk_style_item_color(table[NK_COLOR_TOGGLE_HOVER]);
    toggle->active          = nk_style_item_color(table[NK_COLOR_TOGGLE_HOVER]);
    toggle->cursor_normal   = nk_style_item_color(table[NK_COLOR_TOGGLE_CURSOR]);
    toggle->cursor_hover    = nk_style_item_color(table[NK_COLOR_TOGGLE_CURSOR]);
    toggle->userdata        = nk_handle_ptr(0);
    toggle->text_background = table[NK_COLOR_WINDOW];
    toggle->text_normal     = table[NK_COLOR_TEXT];
    toggle->text_hover      = table[NK_COLOR_TEXT];
    toggle->text_active     = table[NK_COLOR_TEXT];
    toggle->padding         = nk_vec2(2.0f, 2.0f);
    toggle->touch_padding   = nk_vec2(0,0);
    toggle->border_color    = nk_rgba(0,0,0,0);
    toggle->border          = 0.0f;
    toggle->spacing         = 4;

    toggle = &style->option;
    nk_zero_struct(*toggle);
    toggle->normal          = nk_style_item_color(table[NK_COLOR_TOGGLE]);
    toggle->hover           = nk_style_item_color(table[NK_COLOR_TOGGLE_HOVER]);
    toggle->active          = nk_style_item_color(table[NK_COLOR_TOGGLE_HOVER]);
    toggle->cursor_normal   = nk_style_item_color(table[NK_COLOR_TOGGLE_CURSOR]);
    toggle->cursor_hover    = nk_style_item_color(table[NK_COLOR_TOGGLE_CURSOR]);
    toggle->userdata        = nk_handle_ptr(0);
    toggle->text_background = table[NK_COLOR_WINDOW];
    toggle->text_normal     = table[NK_COLOR_TEXT];
    toggle->text_hover      = table[NK_COLOR_TEXT];
    toggle->text_active     = table[NK_COLOR_TEXT];
    toggle->padding         = nk_vec2(3.0f, 3.0f);
    toggle->touch_padding   = nk_vec2(0,0);
    toggle->border_color    = nk_rgba(0,0,0,0);
    toggle->border          = 0.0f;
    toggle->spacing         = 4;

    select = &style->selectable;
    nk_zero_struct(*select);
    select->normal          = nk_style_item_color(table[NK_COLOR_SELECT]);
    select->hover           = nk_style_item_color(table[NK_COLOR_SELECT]);
    select->pressed         = nk_style_item_color(table[NK_COLOR_SELECT]);
    select->normal_active   = nk_style_item_color(table[NK_COLOR_SELECT_ACTIVE]);
    select->hover_active    = nk_style_item_color(table[NK_COLOR_SELECT_ACTIVE]);
    select->pressed_active  = nk_style_item_color(table[NK_COLOR_SELECT_ACTIVE]);
    select->text_normal     = table[NK_COLOR_TEXT];
    select->text_hover      = table[NK_COLOR_TEXT];
    select->text_pressed    = table[NK_COLOR_TEXT];
    select->text_normal_active  = table[NK_COLOR_TEXT];
    select->text_hover_active   = table[NK_COLOR_TEXT];
    select->text_pressed_active = table[NK_COLOR_TEXT];
    select->padding         = nk_vec2(2.0f,2.0f);
    select->image_padding   = nk_vec2(2.0f,2.0f);
    select->touch_padding   = nk_vec2(0,0);
    select->userdata        = nk_handle_ptr(0);
    select->rounding        = 0.0f;
    select->draw_begin      = 0;
    select->draw_end        = 0;

    slider = &style->slider;
    nk_zero_struct(*slider);
    slider->normal          = nk_style_item_hide();
    slider->hover           = nk_style_item_hide();
    slider->active          = nk_style_item_hide();
    slider->bar_normal      = table[NK_COLOR_SLIDER];
    slider->bar_hover       = table[NK_COLOR_SLIDER];
    slider->bar_active      = table[NK_COLOR_SLIDER];
    slider->bar_filled      = table[NK_COLOR_SLIDER_CURSOR];
    slider->cursor_normal   = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR]);
    slider->cursor_hover    = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR_HOVER]);
    slider->cursor_active   = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR_ACTIVE]);
    slider->inc_symbol      = NK_SYMBOL_TRIANGLE_RIGHT;
    slider->dec_symbol      = NK_SYMBOL_TRIANGLE_LEFT;
    slider->cursor_size     = nk_vec2(16,16);
    slider->padding         = nk_vec2(2,2);
    slider->spacing         = nk_vec2(2,2);
    slider->userdata        = nk_handle_ptr(0);
    slider->show_buttons    = nk_false;
    slider->bar_height      = 8;
    slider->rounding        = 0;
    slider->draw_begin      = 0;
    slider->draw_end        = 0;

    button = &style->slider.inc_button;
    button->normal          = nk_style_item_color(nk_rgb(40,40,40));
    button->hover           = nk_style_item_color(nk_rgb(42,42,42));
    button->active          = nk_style_item_color(nk_rgb(44,44,44));
    button->border_color    = nk_rgb(65,65,65);
    button->text_background = nk_rgb(40,40,40);
    button->text_normal     = nk_rgb(175,175,175);
    button->text_hover      = nk_rgb(175,175,175);
    button->text_active     = nk_rgb(175,175,175);
    button->padding         = nk_vec2(8.0f,8.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 1.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;
    style->slider.dec_button = style->slider.inc_button;

    prog = &style->progress;
    nk_zero_struct(*prog);
    prog->normal            = nk_style_item_color(table[NK_COLOR_SLIDER]);
    prog->hover             = nk_style_item_color(table[NK_COLOR_SLIDER]);
    prog->active            = nk_style_item_color(table[NK_COLOR_SLIDER]);
    prog->cursor_normal     = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR]);
    prog->cursor_hover      = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR_HOVER]);
    prog->cursor_active     = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR_ACTIVE]);
    prog->border_color      = nk_rgba(0,0,0,0);
    prog->cursor_border_color = nk_rgba(0,0,0,0);
    prog->userdata          = nk_handle_ptr(0);
    prog->padding           = nk_vec2(4,4);
    prog->rounding          = 0;
    prog->border            = 0;
    prog->cursor_rounding   = 0;
    prog->cursor_border     = 0;
    prog->draw_begin        = 0;
    prog->draw_end          = 0;

    scroll = &style->scrollh;
    nk_zero_struct(*scroll);
    scroll->normal          = nk_style_item_color(table[NK_COLOR_SCROLLBAR]);
    scroll->hover           = nk_style_item_color(table[NK_COLOR_SCROLLBAR]);
    scroll->active          = nk_style_item_color(table[NK_COLOR_SCROLLBAR]);
    scroll->cursor_normal   = nk_style_item_color(table[NK_COLOR_SCROLLBAR_CURSOR]);
    scroll->cursor_hover    = nk_style_item_color(table[NK_COLOR_SCROLLBAR_CURSOR_HOVER]);
    scroll->cursor_active   = nk_style_item_color(table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE]);
    scroll->dec_symbol      = NK_SYMBOL_CIRCLE_SOLID;
    scroll->inc_symbol      = NK_SYMBOL_CIRCLE_SOLID;
    scroll->userdata        = nk_handle_ptr(0);
    scroll->border_color    = table[NK_COLOR_SCROLLBAR];
    scroll->cursor_border_color = table[NK_COLOR_SCROLLBAR];
    scroll->padding         = nk_vec2(0,0);
    scroll->show_buttons    = nk_false;
    scroll->border          = 0;
    scroll->rounding        = 0;
    scroll->border_cursor   = 0;
    scroll->rounding_cursor = 0;
    scroll->draw_begin      = 0;
    scroll->draw_end        = 0;
    style->scrollv = style->scrollh;

    button = &style->scrollh.inc_button;
    button->normal          = nk_style_item_color(nk_rgb(40,40,40));
    button->hover           = nk_style_item_color(nk_rgb(42,42,42));
    button->active          = nk_style_item_color(nk_rgb(44,44,44));
    button->border_color    = nk_rgb(65,65,65);
    button->text_background = nk_rgb(40,40,40);
    button->text_normal     = nk_rgb(175,175,175);
    button->text_hover      = nk_rgb(175,175,175);
    button->text_active     = nk_rgb(175,175,175);
    button->padding         = nk_vec2(4.0f,4.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 1.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;
    style->scrollh.dec_button = style->scrollh.inc_button;
    style->scrollv.inc_button = style->scrollh.inc_button;
    style->scrollv.dec_button = style->scrollh.inc_button;

    edit = &style->edit;
    nk_zero_struct(*edit);
    edit->normal            = nk_style_item_color(table[NK_COLOR_EDIT]);
    edit->hover             = nk_style_item_color(table[NK_COLOR_EDIT]);
    edit->active            = nk_style_item_color(table[NK_COLOR_EDIT]);
    edit->cursor_normal     = table[NK_COLOR_TEXT];
    edit->cursor_hover      = table[NK_COLOR_TEXT];
    edit->cursor_text_normal= table[NK_COLOR_EDIT];
    edit->cursor_text_hover = table[NK_COLOR_EDIT];
    edit->border_color      = table[NK_COLOR_BORDER];
    edit->text_normal       = table[NK_COLOR_TEXT];
    edit->text_hover        = table[NK_COLOR_TEXT];
    edit->text_active       = table[NK_COLOR_TEXT];
    edit->selected_normal   = table[NK_COLOR_TEXT];
    edit->selected_hover    = table[NK_COLOR_TEXT];
    edit->selected_text_normal  = table[NK_COLOR_EDIT];
    edit->selected_text_hover   = table[NK_COLOR_EDIT];
    edit->scrollbar_size    = nk_vec2(10,10);
    edit->scrollbar         = style->scrollv;
    edit->padding           = nk_vec2(4,4);
    edit->row_padding       = 2;
    edit->cursor_size       = 4;
    edit->border            = 1;
    edit->rounding          = 0;

    property = &style->property;
    nk_zero_struct(*property);
    property->normal        = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    property->hover         = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    property->active        = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    property->border_color  = table[NK_COLOR_BORDER];
    property->label_normal  = table[NK_COLOR_TEXT];
    property->label_hover   = table[NK_COLOR_TEXT];
    property->label_active  = table[NK_COLOR_TEXT];
    property->sym_left      = NK_SYMBOL_TRIANGLE_LEFT;
    property->sym_right     = NK_SYMBOL_TRIANGLE_RIGHT;
    property->userdata      = nk_handle_ptr(0);
    property->padding       = nk_vec2(4,4);
    property->border        = 1;
    property->rounding      = 10;
    property->draw_begin    = 0;
    property->draw_end      = 0;

    button = &style->property.dec_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    button->hover           = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    button->active          = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_PROPERTY];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(0.0f,0.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;
    style->property.inc_button = style->property.dec_button;

    edit = &style->property.edit;
    nk_zero_struct(*edit);
    edit->normal            = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    edit->hover             = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    edit->active            = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    edit->border_color      = nk_rgba(0,0,0,0);
    edit->cursor_normal     = table[NK_COLOR_TEXT];
    edit->cursor_hover      = table[NK_COLOR_TEXT];
    edit->cursor_text_normal= table[NK_COLOR_EDIT];
    edit->cursor_text_hover = table[NK_COLOR_EDIT];
    edit->text_normal       = table[NK_COLOR_TEXT];
    edit->text_hover        = table[NK_COLOR_TEXT];
    edit->text_active       = table[NK_COLOR_TEXT];
    edit->selected_normal   = table[NK_COLOR_TEXT];
    edit->selected_hover    = table[NK_COLOR_TEXT];
    edit->selected_text_normal  = table[NK_COLOR_EDIT];
    edit->selected_text_hover   = table[NK_COLOR_EDIT];
    edit->padding           = nk_vec2(0,0);
    edit->cursor_size       = 8;
    edit->border            = 0;
    edit->rounding          = 0;

    chart = &style->chart;
    nk_zero_struct(*chart);
    chart->background       = nk_style_item_color(table[NK_COLOR_CHART]);
    chart->border_color     = table[NK_COLOR_BORDER];
    chart->selected_color   = table[NK_COLOR_CHART_COLOR_HIGHLIGHT];
    chart->color            = table[NK_COLOR_CHART_COLOR];
    chart->padding          = nk_vec2(4,4);
    chart->border           = 0;
    chart->rounding         = 0;

    combo = &style->combo;
    combo->normal           = nk_style_item_color(table[NK_COLOR_COMBO]);
    combo->hover            = nk_style_item_color(table[NK_COLOR_COMBO]);
    combo->active           = nk_style_item_color(table[NK_COLOR_COMBO]);
    combo->border_color     = table[NK_COLOR_BORDER];
    combo->label_normal     = table[NK_COLOR_TEXT];
    combo->label_hover      = table[NK_COLOR_TEXT];
    combo->label_active     = table[NK_COLOR_TEXT];
    combo->sym_normal       = NK_SYMBOL_TRIANGLE_DOWN;
    combo->sym_hover        = NK_SYMBOL_TRIANGLE_DOWN;
    combo->sym_active       = NK_SYMBOL_TRIANGLE_DOWN;
    combo->content_padding  = nk_vec2(4,4);
    combo->button_padding   = nk_vec2(0,4);
    combo->spacing          = nk_vec2(4,0);
    combo->border           = 1;
    combo->rounding         = 0;

    button = &style->combo.button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_COMBO]);
    button->hover           = nk_style_item_color(table[NK_COLOR_COMBO]);
    button->active          = nk_style_item_color(table[NK_COLOR_COMBO]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_COMBO];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    tab = &style->tab;
    tab->background         = nk_style_item_color(table[NK_COLOR_TAB_HEADER]);
    tab->border_color       = table[NK_COLOR_BORDER];
    tab->text               = table[NK_COLOR_TEXT];
    tab->sym_minimize       = NK_SYMBOL_TRIANGLE_RIGHT;
    tab->sym_maximize       = NK_SYMBOL_TRIANGLE_DOWN;
    tab->padding            = nk_vec2(4,4);
    tab->spacing            = nk_vec2(4,4);
    tab->indent             = 10.0f;
    tab->border             = 1;
    tab->rounding           = 0;

    button = &style->tab.tab_minimize_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_TAB_HEADER]);
    button->hover           = nk_style_item_color(table[NK_COLOR_TAB_HEADER]);
    button->active          = nk_style_item_color(table[NK_COLOR_TAB_HEADER]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_TAB_HEADER];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;
    style->tab.tab_maximize_button =*button;

    button = &style->tab.node_minimize_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->hover           = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->active          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_TAB_HEADER];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;
    style->tab.node_maximize_button =*button;

    win = &style->window;
    win->header.align = NK_HEADER_RIGHT;
    win->header.close_symbol = NK_SYMBOL_X;
    win->header.minimize_symbol = NK_SYMBOL_MINUS;
    win->header.maximize_symbol = NK_SYMBOL_PLUS;
    win->header.normal = nk_style_item_color(table[NK_COLOR_HEADER]);
    win->header.hover = nk_style_item_color(table[NK_COLOR_HEADER]);
    win->header.active = nk_style_item_color(table[NK_COLOR_HEADER]);
    win->header.label_normal = table[NK_COLOR_TEXT];
    win->header.label_hover = table[NK_COLOR_TEXT];
    win->header.label_active = table[NK_COLOR_TEXT];
    win->header.label_padding = nk_vec2(4,4);
    win->header.padding = nk_vec2(4,4);
    win->header.spacing = nk_vec2(0,0);

    button = &style->window.header.close_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->hover           = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->active          = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_HEADER];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(0.0f,0.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    button = &style->window.header.minimize_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->hover           = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->active          = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_HEADER];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(0.0f,0.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    win->background = table[NK_COLOR_WINDOW];
    win->fixed_background = nk_style_item_color(table[NK_COLOR_WINDOW]);
    win->border_color = table[NK_COLOR_BORDER];
    win->popup_border_color = table[NK_COLOR_BORDER];
    win->combo_border_color = table[NK_COLOR_BORDER];
    win->contextual_border_color = table[NK_COLOR_BORDER];
    win->menu_border_color = table[NK_COLOR_BORDER];
    win->group_border_color = table[NK_COLOR_BORDER];
    win->tooltip_border_color = table[NK_COLOR_BORDER];
    win->scaler = nk_style_item_color(table[NK_COLOR_TEXT]);

    win->rounding = 0.0f;
    win->spacing = nk_vec2(4,4);
    win->scrollbar_size = nk_vec2(10,10);
    win->min_size = nk_vec2(64,64);

    win->combo_border = 1.0f;
    win->contextual_border = 1.0f;
    win->menu_border = 1.0f;
    win->group_border = 1.0f;
    win->tooltip_border = 1.0f;
    win->popup_border = 1.0f;
    win->border = 2.0f;
    win->min_row_height_padding = 8;

    win->padding = nk_vec2(4,4);
    win->group_padding = nk_vec2(4,4);
    win->popup_padding = nk_vec2(4,4);
    win->combo_padding = nk_vec2(4,4);
    win->contextual_padding = nk_vec2(4,4);
    win->menu_padding = nk_vec2(4,4);
    win->tooltip_padding = nk_vec2(4,4);
}
NK_API void
nk_style_set_font(struct nk_context *ctx, const struct nk_user_font *font)
{
    struct nk_style *style;
    NK_ASSERT(ctx);

    if (!ctx) return;
    style = &ctx->style;
    style->font = font;
    ctx->stacks.fonts.head = 0;
    if (ctx->current)
        nk_layout_reset_min_row_height(ctx);
}
NK_API nk_bool
nk_style_push_font(struct nk_context *ctx, const struct nk_user_font *font)
{
    struct nk_config_stack_user_font *font_stack;
    struct nk_config_stack_user_font_element *element;

    NK_ASSERT(ctx);
    if (!ctx) return 0;

    font_stack = &ctx->stacks.fonts;
    NK_ASSERT(font_stack->head < (int)NK_LEN(font_stack->elements));
    if (font_stack->head >= (int)NK_LEN(font_stack->elements))
        return 0;

    element = &font_stack->elements[font_stack->head++];
    element->address = &ctx->style.font;
    element->old_value = ctx->style.font;
    ctx->style.font = font;
    return 1;
}
NK_API nk_bool
nk_style_pop_font(struct nk_context *ctx)
{
    struct nk_config_stack_user_font *font_stack;
    struct nk_config_stack_user_font_element *element;

    NK_ASSERT(ctx);
    if (!ctx) return 0;

    font_stack = &ctx->stacks.fonts;
    NK_ASSERT(font_stack->head > 0);
    if (font_stack->head < 1)
        return 0;

    element = &font_stack->elements[--font_stack->head];
    *element->address = element->old_value;
    return 1;
}
#define NK_STYLE_PUSH_IMPLEMENATION(prefix, type, stack) \
nk_style_push_##type(struct nk_context *ctx, prefix##_##type *address, prefix##_##type value)\
{\
    struct nk_config_stack_##type * type_stack;\
    struct nk_config_stack_##type##_element *element;\
    NK_ASSERT(ctx);\
    if (!ctx) return 0;\
    type_stack = &ctx->stacks.stack;\
    NK_ASSERT(type_stack->head < (int)NK_LEN(type_stack->elements));\
    if (type_stack->head >= (int)NK_LEN(type_stack->elements))\
        return 0;\
    element = &type_stack->elements[type_stack->head++];\
    element->address = address;\
    element->old_value = *address;\
    *address = value;\
    return 1;\
}
#define NK_STYLE_POP_IMPLEMENATION(type, stack) \
nk_style_pop_##type(struct nk_context *ctx)\
{\
    struct nk_config_stack_##type *type_stack;\
    struct nk_config_stack_##type##_element *element;\
    NK_ASSERT(ctx);\
    if (!ctx) return 0;\
    type_stack = &ctx->stacks.stack;\
    NK_ASSERT(type_stack->head > 0);\
    if (type_stack->head < 1)\
        return 0;\
    element = &type_stack->elements[--type_stack->head];\
    *element->address = element->old_value;\
    return 1;\
}
NK_API nk_bool NK_STYLE_PUSH_IMPLEMENATION(struct nk, style_item, style_items)
NK_API nk_bool NK_STYLE_PUSH_IMPLEMENATION(nk,float, floats)
NK_API nk_bool NK_STYLE_PUSH_IMPLEMENATION(struct nk, vec2, vectors)
NK_API nk_bool NK_STYLE_PUSH_IMPLEMENATION(nk,flags, flags)
NK_API nk_bool NK_STYLE_PUSH_IMPLEMENATION(struct nk,color, colors)

NK_API nk_bool NK_STYLE_POP_IMPLEMENATION(style_item, style_items)
NK_API nk_bool NK_STYLE_POP_IMPLEMENATION(float,floats)
NK_API nk_bool NK_STYLE_POP_IMPLEMENATION(vec2, vectors)
NK_API nk_bool NK_STYLE_POP_IMPLEMENATION(flags,flags)
NK_API nk_bool NK_STYLE_POP_IMPLEMENATION(color,colors)

NK_API nk_bool
nk_style_set_cursor(struct nk_context *ctx, enum nk_style_cursor c)
{
    struct nk_style *style;
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    style = &ctx->style;
    if (style->cursors[c]) {
        style->cursor_active = style->cursors[c];
        return 1;
    }
    return 0;
}
NK_API void
nk_style_show_cursor(struct nk_context *ctx)
{
    ctx->style.cursor_visible = nk_true;
}
NK_API void
nk_style_hide_cursor(struct nk_context *ctx)
{
    ctx->style.cursor_visible = nk_false;
}
NK_API void
nk_style_load_cursor(struct nk_context *ctx, enum nk_style_cursor cursor,
    const struct nk_cursor *c)
{
    struct nk_style *style;
    NK_ASSERT(ctx);
    if (!ctx) return;
    style = &ctx->style;
    style->cursors[cursor] = c;
}
NK_API void
nk_style_load_all_cursors(struct nk_context *ctx, struct nk_cursor *cursors)
{
    int i = 0;
    struct nk_style *style;
    NK_ASSERT(ctx);
    if (!ctx) return;
    style = &ctx->style;
    for (i = 0; i < NK_CURSOR_COUNT; ++i)
        style->cursors[i] = &cursors[i];
    style->cursor_visible = nk_true;
}

NK_INTERN void
nk_setup(struct nk_context *ctx, const struct nk_user_font *font)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_zero_struct(*ctx);
    nk_style_default(ctx);
    ctx->seq = 1;
    if (font) ctx->style.font = font;
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    nk_draw_list_init(&ctx->draw_list);
#endif
}
#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API nk_bool
nk_init_default(struct nk_context *ctx, const struct nk_user_font *font)
{
    struct nk_allocator alloc;
    alloc.userdata.ptr = 0;
    alloc.alloc = nk_malloc;
    alloc.free = nk_mfree;
    return nk_init(ctx, &alloc, font);
}
#endif
NK_API nk_bool
nk_init_fixed(struct nk_context *ctx, void *memory, nk_size size,
    const struct nk_user_font *font)
{
    NK_ASSERT(memory);
    if (!memory) return 0;
    nk_setup(ctx, font);
    nk_buffer_init_fixed(&ctx->memory, memory, size);
    ctx->use_pool = nk_false;
    return 1;
}
NK_API nk_bool
nk_init_custom(struct nk_context *ctx, struct nk_buffer *cmds,
    struct nk_buffer *pool, const struct nk_user_font *font)
{
    NK_ASSERT(cmds);
    NK_ASSERT(pool);
    if (!cmds || !pool) return 0;

    nk_setup(ctx, font);
    ctx->memory = *cmds;
    if (pool->type == NK_BUFFER_FIXED) {

        nk_pool_init_fixed(&ctx->pool, pool->memory.ptr, pool->memory.size);
    } else {

        struct nk_allocator *alloc = &pool->pool;
        nk_pool_init(&ctx->pool, alloc, NK_POOL_DEFAULT_CAPACITY);
    }
    ctx->use_pool = nk_true;
    return 1;
}
NK_API nk_bool
nk_init(struct nk_context *ctx, struct nk_allocator *alloc,
    const struct nk_user_font *font)
{
    NK_ASSERT(alloc);
    if (!alloc) return 0;
    nk_setup(ctx, font);
    nk_buffer_init(&ctx->memory, alloc, NK_DEFAULT_COMMAND_BUFFER_SIZE);
    nk_pool_init(&ctx->pool, alloc, NK_POOL_DEFAULT_CAPACITY);
    ctx->use_pool = nk_true;
    return 1;
}
#ifdef NK_INCLUDE_COMMAND_USERDATA
NK_API void
nk_set_user_data(struct nk_context *ctx, nk_handle handle)
{
    if (!ctx) return;
    ctx->userdata = handle;
    if (ctx->current)
        ctx->current->buffer.userdata = handle;
}
#endif
NK_API void
nk_free(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_buffer_free(&ctx->memory);
    if (ctx->use_pool)
        nk_pool_free(&ctx->pool);

    nk_zero(&ctx->input, sizeof(ctx->input));
    nk_zero(&ctx->style, sizeof(ctx->style));
    nk_zero(&ctx->memory, sizeof(ctx->memory));

    ctx->seq = 0;
    ctx->build = 0;
    ctx->begin = 0;
    ctx->end = 0;
    ctx->active = 0;
    ctx->current = 0;
    ctx->freelist = 0;
    ctx->count = 0;
}
NK_API void
nk_clear(struct nk_context *ctx)
{
    struct nk_window *iter;
    struct nk_window *next;
    NK_ASSERT(ctx);

    if (!ctx) return;
    if (ctx->use_pool)
        nk_buffer_clear(&ctx->memory);
    else nk_buffer_reset(&ctx->memory, NK_BUFFER_FRONT);

    ctx->build = 0;
    ctx->memory.calls = 0;
    ctx->last_widget_state = 0;
    ctx->style.cursor_active = ctx->style.cursors[NK_CURSOR_ARROW];
    NK_MEMSET(&ctx->overlay, 0, sizeof(ctx->overlay));

    iter = ctx->begin;
    while (iter) {

        if ((iter->flags & NK_WINDOW_MINIMIZED) &&
            !(iter->flags & NK_WINDOW_CLOSED) &&
            iter->seq == ctx->seq) {
            iter = iter->next;
            continue;
        }

        if (((iter->flags & NK_WINDOW_HIDDEN) ||
            (iter->flags & NK_WINDOW_CLOSED)) &&
            iter == ctx->active) {
            ctx->active = iter->prev;
            ctx->end = iter->prev;
            if (!ctx->end)
                ctx->begin = 0;
            if (ctx->active)
                ctx->active->flags &= ~(unsigned)NK_WINDOW_ROM;
        }

        if (iter->popup.win && iter->popup.win->seq != ctx->seq) {
            nk_free_window(ctx, iter->popup.win);
            iter->popup.win = 0;
        }

        {struct nk_table *n, *it = iter->tables;
        while (it) {
            n = it->next;
            if (it->seq != ctx->seq) {
                nk_remove_table(iter, it);
                nk_zero(it, sizeof(union nk_page_data));
                nk_free_table(ctx, it);
                if (it == iter->tables)
                    iter->tables = n;
            } it = n;
        }}

        if (iter->seq != ctx->seq || iter->flags & NK_WINDOW_CLOSED) {
            next = iter->next;
            nk_remove_window(ctx, iter);
            nk_free_window(ctx, iter);
            iter = next;
        } else iter = iter->next;
    }
    ctx->seq++;
}
NK_LIB void
nk_start_buffer(struct nk_context *ctx, struct nk_command_buffer *buffer)
{
    NK_ASSERT(ctx);
    NK_ASSERT(buffer);
    if (!ctx || !buffer) return;
    buffer->begin = ctx->memory.allocated;
    buffer->end = buffer->begin;
    buffer->last = buffer->begin;
    buffer->clip = nk_null_rect;
}
NK_LIB void
nk_start(struct nk_context *ctx, struct nk_window *win)
{
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    nk_start_buffer(ctx, &win->buffer);
}
NK_LIB void
nk_start_popup(struct nk_context *ctx, struct nk_window *win)
{
    struct nk_popup_buffer *buf;
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!ctx || !win) return;

    buf = &win->popup.buf;
    buf->begin = win->buffer.end;
    buf->end = win->buffer.end;
    buf->parent = win->buffer.last;
    buf->last = buf->begin;
    buf->active = nk_true;
}
NK_LIB void
nk_finish_popup(struct nk_context *ctx, struct nk_window *win)
{
    struct nk_popup_buffer *buf;
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!ctx || !win) return;

    buf = &win->popup.buf;
    buf->last = win->buffer.last;
    buf->end = win->buffer.end;
}
NK_LIB void
nk_finish_buffer(struct nk_context *ctx, struct nk_command_buffer *buffer)
{
    NK_ASSERT(ctx);
    NK_ASSERT(buffer);
    if (!ctx || !buffer) return;
    buffer->end = ctx->memory.allocated;
}
NK_LIB void
nk_finish(struct nk_context *ctx, struct nk_window *win)
{
    struct nk_popup_buffer *buf;
    struct nk_command *parent_last;
    void *memory;

    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!ctx || !win) return;
    nk_finish_buffer(ctx, &win->buffer);
    if (!win->popup.buf.active) return;

    buf = &win->popup.buf;
    memory = ctx->memory.memory.ptr;
    parent_last = nk_ptr_add(struct nk_command, memory, buf->parent);
    parent_last->next = buf->end;
}
NK_LIB void
nk_build(struct nk_context *ctx)
{
    struct nk_window *it = 0;
    struct nk_command *cmd = 0;
    nk_byte *buffer = 0;

    if (!ctx->style.cursor_active)
        ctx->style.cursor_active = ctx->style.cursors[NK_CURSOR_ARROW];
    if (ctx->style.cursor_active && !ctx->input.mouse.grabbed && ctx->style.cursor_visible) {
        struct nk_rect mouse_bounds;
        const struct nk_cursor *cursor = ctx->style.cursor_active;
        nk_command_buffer_init(&ctx->overlay, &ctx->memory, NK_CLIPPING_OFF);
        nk_start_buffer(ctx, &ctx->overlay);

        mouse_bounds.x = ctx->input.mouse.pos.x - cursor->offset.x;
        mouse_bounds.y = ctx->input.mouse.pos.y - cursor->offset.y;
        mouse_bounds.w = cursor->size.x;
        mouse_bounds.h = cursor->size.y;

        nk_draw_image(&ctx->overlay, mouse_bounds, &cursor->img, nk_white);
        nk_finish_buffer(ctx, &ctx->overlay);
    }

    it = ctx->begin;
    buffer = (nk_byte*)ctx->memory.memory.ptr;
    while (it != 0) {
        struct nk_window *next = it->next;
        if (it->buffer.last == it->buffer.begin || (it->flags & NK_WINDOW_HIDDEN)||
            it->seq != ctx->seq)
            goto cont;

        cmd = nk_ptr_add(struct nk_command, buffer, it->buffer.last);
        while (next && ((next->buffer.last == next->buffer.begin) ||
            (next->flags & NK_WINDOW_HIDDEN) || next->seq != ctx->seq))
            next = next->next;

        if (next) cmd->next = next->buffer.begin;
        cont: it = next;
    }

    it = ctx->begin;
    while (it != 0) {
        struct nk_window *next = it->next;
        struct nk_popup_buffer *buf;
        if (!it->popup.buf.active)
            goto skip;

        buf = &it->popup.buf;
        cmd->next = buf->begin;
        cmd = nk_ptr_add(struct nk_command, buffer, buf->last);
        buf->active = nk_false;
        skip: it = next;
    }
    if (cmd) {

        if (ctx->overlay.end != ctx->overlay.begin)
            cmd->next = ctx->overlay.begin;
        else cmd->next = ctx->memory.allocated;
    }
}
NK_API const struct nk_command*
nk__begin(struct nk_context *ctx)
{
    struct nk_window *iter;
    nk_byte *buffer;
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    if (!ctx->count) return 0;

    buffer = (nk_byte*)ctx->memory.memory.ptr;
    if (!ctx->build) {
        nk_build(ctx);
        ctx->build = nk_true;
    }
    iter = ctx->begin;
    while (iter && ((iter->buffer.begin == iter->buffer.end) ||
        (iter->flags & NK_WINDOW_HIDDEN) || iter->seq != ctx->seq))
        iter = iter->next;
    if (!iter) return 0;
    return nk_ptr_add_const(struct nk_command, buffer, iter->buffer.begin);
}

NK_API const struct nk_command*
nk__next(struct nk_context *ctx, const struct nk_command *cmd)
{
    nk_byte *buffer;
    const struct nk_command *next;
    NK_ASSERT(ctx);
    if (!ctx || !cmd || !ctx->count) return 0;
    if (cmd->next >= ctx->memory.allocated) return 0;
    buffer = (nk_byte*)ctx->memory.memory.ptr;
    next = nk_ptr_add_const(struct nk_command, buffer, cmd->next);
    return next;
}

NK_LIB void
nk_pool_init(struct nk_pool *pool, struct nk_allocator *alloc,
    unsigned int capacity)
{
    NK_ASSERT(capacity >= 1);
    nk_zero(pool, sizeof(*pool));
    pool->alloc = *alloc;
    pool->capacity = capacity;
    pool->type = NK_BUFFER_DYNAMIC;
    pool->pages = 0;
}
NK_LIB void
nk_pool_free(struct nk_pool *pool)
{
    struct nk_page *iter;
    if (!pool) return;
    iter = pool->pages;
    if (pool->type == NK_BUFFER_FIXED) return;
    while (iter) {
        struct nk_page *next = iter->next;
        pool->alloc.free(pool->alloc.userdata, iter);
        iter = next;
    }
}
NK_LIB void
nk_pool_init_fixed(struct nk_pool *pool, void *memory, nk_size size)
{
    nk_zero(pool, sizeof(*pool));
    NK_ASSERT(size >= sizeof(struct nk_page));
    if (size < sizeof(struct nk_page)) return;

    pool->capacity = (unsigned)(1 + (size - sizeof(struct nk_page)) / sizeof(struct nk_page_element));
    pool->pages = (struct nk_page*)memory;
    pool->type = NK_BUFFER_FIXED;
    pool->size = size;
}
NK_LIB struct nk_page_element*
nk_pool_alloc(struct nk_pool *pool)
{
    if (!pool->pages || pool->pages->size >= pool->capacity) {

        struct nk_page *page;
        if (pool->type == NK_BUFFER_FIXED) {
            NK_ASSERT(pool->pages);
            if (!pool->pages) return 0;
            NK_ASSERT(pool->pages->size < pool->capacity);
            return 0;
        } else {
            nk_size size = sizeof(struct nk_page);
            size += (pool->capacity - 1) * sizeof(struct nk_page_element);
            page = (struct nk_page*)pool->alloc.alloc(pool->alloc.userdata,0, size);
            page->next = pool->pages;
            pool->pages = page;
            page->size = 0;
        }
    } return &pool->pages->win[pool->pages->size++];
}

NK_LIB struct nk_page_element*
nk_create_page_element(struct nk_context *ctx)
{
    struct nk_page_element *elem;
    if (ctx->freelist) {

        elem = ctx->freelist;
        ctx->freelist = elem->next;
    } else if (ctx->use_pool) {

        elem = nk_pool_alloc(&ctx->pool);
        NK_ASSERT(elem);
        if (!elem) return 0;
    } else {

        NK_STORAGE const nk_size size = sizeof(struct nk_page_element);
        NK_STORAGE const nk_size align = NK_ALIGNOF(struct nk_page_element);
        elem = (struct nk_page_element*)nk_buffer_alloc(&ctx->memory, NK_BUFFER_BACK, size, align);
        NK_ASSERT(elem);
        if (!elem) return 0;
    }
    nk_zero_struct(*elem);
    elem->next = 0;
    elem->prev = 0;
    return elem;
}
NK_LIB void
nk_link_page_element_into_freelist(struct nk_context *ctx,
    struct nk_page_element *elem)
{

    if (!ctx->freelist) {
        ctx->freelist = elem;
    } else {
        elem->next = ctx->freelist;
        ctx->freelist = elem;
    }
}
NK_LIB void
nk_free_page_element(struct nk_context *ctx, struct nk_page_element *elem)
{

    if (ctx->use_pool) {
        nk_link_page_element_into_freelist(ctx, elem);
        return;
    }

    {void *elem_end = (void*)(elem + 1);
    void *buffer_end = (nk_byte*)ctx->memory.memory.ptr + ctx->memory.size;
    if (elem_end == buffer_end)
        ctx->memory.size -= sizeof(struct nk_page_element);
    else nk_link_page_element_into_freelist(ctx, elem);}
}

NK_LIB struct nk_table*
nk_create_table(struct nk_context *ctx)
{
    struct nk_page_element *elem;
    elem = nk_create_page_element(ctx);
    if (!elem) return 0;
    nk_zero_struct(*elem);
    return &elem->data.tbl;
}
NK_LIB void
nk_free_table(struct nk_context *ctx, struct nk_table *tbl)
{
    union nk_page_data *pd = NK_CONTAINER_OF(tbl, union nk_page_data, tbl);
    struct nk_page_element *pe = NK_CONTAINER_OF(pd, struct nk_page_element, data);
    nk_free_page_element(ctx, pe);
}
NK_LIB void
nk_push_table(struct nk_window *win, struct nk_table *tbl)
{
    if (!win->tables) {
        win->tables = tbl;
        tbl->next = 0;
        tbl->prev = 0;
        tbl->size = 0;
        win->table_count = 1;
        return;
    }
    win->tables->prev = tbl;
    tbl->next = win->tables;
    tbl->prev = 0;
    tbl->size = 0;
    win->tables = tbl;
    win->table_count++;
}
NK_LIB void
nk_remove_table(struct nk_window *win, struct nk_table *tbl)
{
    if (win->tables == tbl)
        win->tables = tbl->next;
    if (tbl->next)
        tbl->next->prev = tbl->prev;
    if (tbl->prev)
        tbl->prev->next = tbl->next;
    tbl->next = 0;
    tbl->prev = 0;
}
NK_LIB nk_uint*
nk_add_value(struct nk_context *ctx, struct nk_window *win,
            nk_hash name, nk_uint value)
{
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!win || !ctx) return 0;
    if (!win->tables || win->tables->size >= NK_VALUE_PAGE_CAPACITY) {
        struct nk_table *tbl = nk_create_table(ctx);
        NK_ASSERT(tbl);
        if (!tbl) return 0;
        nk_push_table(win, tbl);
    }
    win->tables->seq = win->seq;
    win->tables->keys[win->tables->size] = name;
    win->tables->values[win->tables->size] = value;
    return &win->tables->values[win->tables->size++];
}
NK_LIB nk_uint*
nk_find_value(struct nk_window *win, nk_hash name)
{
    struct nk_table *iter = win->tables;
    while (iter) {
        unsigned int i = 0;
        unsigned int size = iter->size;
        for (i = 0; i < size; ++i) {
            if (iter->keys[i] == name) {
                iter->seq = win->seq;
                return &iter->values[i];
            }
        } size = NK_VALUE_PAGE_CAPACITY;
        iter = iter->next;
    }
    return 0;
}

NK_LIB void*
nk_create_panel(struct nk_context *ctx)
{
    struct nk_page_element *elem;
    elem = nk_create_page_element(ctx);
    if (!elem) return 0;
    nk_zero_struct(*elem);
    return &elem->data.pan;
}
NK_LIB void
nk_free_panel(struct nk_context *ctx, struct nk_panel *pan)
{
    union nk_page_data *pd = NK_CONTAINER_OF(pan, union nk_page_data, pan);
    struct nk_page_element *pe = NK_CONTAINER_OF(pd, struct nk_page_element, data);
    nk_free_page_element(ctx, pe);
}
NK_LIB nk_bool
nk_panel_has_header(nk_flags flags, const char *title)
{
    nk_bool active = 0;
    active = (flags & (NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE));
    active = active || (flags & NK_WINDOW_TITLE);
    active = active && !(flags & NK_WINDOW_HIDDEN) && title;
    return active;
}
NK_LIB struct nk_vec2
nk_panel_get_padding(const struct nk_style *style, enum nk_panel_type type)
{
    switch (type) {
    default:
    case NK_PANEL_WINDOW: return style->window.padding;
    case NK_PANEL_GROUP: return style->window.group_padding;
    case NK_PANEL_POPUP: return style->window.popup_padding;
    case NK_PANEL_CONTEXTUAL: return style->window.contextual_padding;
    case NK_PANEL_COMBO: return style->window.combo_padding;
    case NK_PANEL_MENU: return style->window.menu_padding;
    case NK_PANEL_TOOLTIP: return style->window.menu_padding;}
}
NK_LIB float
nk_panel_get_border(const struct nk_style *style, nk_flags flags,
    enum nk_panel_type type)
{
    if (flags & NK_WINDOW_BORDER) {
        switch (type) {
        default:
        case NK_PANEL_WINDOW: return style->window.border;
        case NK_PANEL_GROUP: return style->window.group_border;
        case NK_PANEL_POPUP: return style->window.popup_border;
        case NK_PANEL_CONTEXTUAL: return style->window.contextual_border;
        case NK_PANEL_COMBO: return style->window.combo_border;
        case NK_PANEL_MENU: return style->window.menu_border;
        case NK_PANEL_TOOLTIP: return style->window.menu_border;
    }} else return 0;
}
NK_LIB struct nk_color
nk_panel_get_border_color(const struct nk_style *style, enum nk_panel_type type)
{
    switch (type) {
    default:
    case NK_PANEL_WINDOW: return style->window.border_color;
    case NK_PANEL_GROUP: return style->window.group_border_color;
    case NK_PANEL_POPUP: return style->window.popup_border_color;
    case NK_PANEL_CONTEXTUAL: return style->window.contextual_border_color;
    case NK_PANEL_COMBO: return style->window.combo_border_color;
    case NK_PANEL_MENU: return style->window.menu_border_color;
    case NK_PANEL_TOOLTIP: return style->window.menu_border_color;}
}
NK_LIB nk_bool
nk_panel_is_sub(enum nk_panel_type type)
{
    return (type & NK_PANEL_SET_SUB)?1:0;
}
NK_LIB nk_bool
nk_panel_is_nonblock(enum nk_panel_type type)
{
    return (type & NK_PANEL_SET_NONBLOCK)?1:0;
}
NK_LIB nk_bool
nk_panel_begin(struct nk_context *ctx, const char *title, enum nk_panel_type panel_type)
{
    struct nk_input *in;
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_command_buffer *out;
    const struct nk_style *style;
    const struct nk_user_font *font;

    struct nk_vec2 scrollbar_size;
    struct nk_vec2 panel_padding;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return 0;
    nk_zero(ctx->current->layout, sizeof(*ctx->current->layout));
    if ((ctx->current->flags & NK_WINDOW_HIDDEN) || (ctx->current->flags & NK_WINDOW_CLOSED)) {
        nk_zero(ctx->current->layout, sizeof(struct nk_panel));
        ctx->current->layout->type = panel_type;
        return 0;
    }

    style = &ctx->style;
    font = style->font;
    win = ctx->current;
    layout = win->layout;
    out = &win->buffer;
    in = (win->flags & NK_WINDOW_NO_INPUT) ? 0: &ctx->input;
#ifdef NK_INCLUDE_COMMAND_USERDATA
    win->buffer.userdata = ctx->userdata;
#endif

    scrollbar_size = style->window.scrollbar_size;
    panel_padding = nk_panel_get_padding(style, panel_type);

    if ((win->flags & NK_WINDOW_MOVABLE) && !(win->flags & NK_WINDOW_ROM)) {
        nk_bool left_mouse_down;
        unsigned int left_mouse_clicked;
        int left_mouse_click_in_cursor;

        struct nk_rect header;
        header.x = win->bounds.x;
        header.y = win->bounds.y;
        header.w = win->bounds.w;
        if (nk_panel_has_header(win->flags, title)) {
            header.h = font->height + 2.0f * style->window.header.padding.y;
            header.h += 2.0f * style->window.header.label_padding.y;
        } else header.h = panel_padding.y;

        left_mouse_down = in->mouse.buttons[NK_BUTTON_LEFT].down;
        left_mouse_clicked = in->mouse.buttons[NK_BUTTON_LEFT].clicked;
        left_mouse_click_in_cursor = nk_input_has_mouse_click_down_in_rect(in,
            NK_BUTTON_LEFT, header, nk_true);
        if (left_mouse_down && left_mouse_click_in_cursor && !left_mouse_clicked) {
            win->bounds.x = win->bounds.x + in->mouse.delta.x;
            win->bounds.y = win->bounds.y + in->mouse.delta.y;
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.x += in->mouse.delta.x;
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.y += in->mouse.delta.y;
            ctx->style.cursor_active = ctx->style.cursors[NK_CURSOR_MOVE];
        }
    }

    layout->type = panel_type;
    layout->flags = win->flags;
    layout->bounds = win->bounds;
    layout->bounds.x += panel_padding.x;
    layout->bounds.w -= 2*panel_padding.x;
    if (win->flags & NK_WINDOW_BORDER) {
        layout->border = nk_panel_get_border(style, win->flags, panel_type);
        layout->bounds = nk_shrink_rect(layout->bounds, layout->border);
    } else layout->border = 0;
    layout->at_y = layout->bounds.y;
    layout->at_x = layout->bounds.x;
    layout->max_x = 0;
    layout->header_height = 0;
    layout->footer_height = 0;
    nk_layout_reset_min_row_height(ctx);
    layout->row.index = 0;
    layout->row.columns = 0;
    layout->row.ratio = 0;
    layout->row.item_width = 0;
    layout->row.tree_depth = 0;
    layout->row.height = panel_padding.y;
    layout->has_scrolling = nk_true;
    if (!(win->flags & NK_WINDOW_NO_SCROLLBAR))
        layout->bounds.w -= scrollbar_size.x;
    if (!nk_panel_is_nonblock(panel_type)) {
        layout->footer_height = 0;
        if (!(win->flags & NK_WINDOW_NO_SCROLLBAR) || win->flags & NK_WINDOW_SCALABLE)
            layout->footer_height = scrollbar_size.y;
        layout->bounds.h -= layout->footer_height;
    }

    if (nk_panel_has_header(win->flags, title))
    {
        struct nk_text text;
        struct nk_rect header;
        const struct nk_style_item *background = 0;

        header.x = win->bounds.x;
        header.y = win->bounds.y;
        header.w = win->bounds.w;
        header.h = font->height + 2.0f * style->window.header.padding.y;
        header.h += (2.0f * style->window.header.label_padding.y);

        layout->header_height = header.h;
        layout->bounds.y += header.h;
        layout->bounds.h -= header.h;
        layout->at_y += header.h;

        if (ctx->active == win) {
            background = &style->window.header.active;
            text.text = style->window.header.label_active;
        } else if (nk_input_is_mouse_hovering_rect(&ctx->input, header)) {
            background = &style->window.header.hover;
            text.text = style->window.header.label_hover;
        } else {
            background = &style->window.header.normal;
            text.text = style->window.header.label_normal;
        }

        header.h += 1.0f;

        switch(background->type) {
            case NK_STYLE_ITEM_IMAGE:
                text.background = nk_rgba(0,0,0,0);
                nk_draw_image(&win->buffer, header, &background->data.image, nk_white);
                break;
            case NK_STYLE_ITEM_NINE_SLICE:
                text.background = nk_rgba(0, 0, 0, 0);
                nk_draw_nine_slice(&win->buffer, header, &background->data.slice, nk_white);
                break;
            case NK_STYLE_ITEM_COLOR:
                text.background = background->data.color;
                nk_fill_rect(out, header, 0, background->data.color);
                break;
        }

        {struct nk_rect button;
        button.y = header.y + style->window.header.padding.y;
        button.h = header.h - 2 * style->window.header.padding.y;
        button.w = button.h;
        if (win->flags & NK_WINDOW_CLOSABLE) {
            nk_flags ws = 0;
            if (style->window.header.align == NK_HEADER_RIGHT) {
                button.x = (header.w + header.x) - (button.w + style->window.header.padding.x);
                header.w -= button.w + style->window.header.spacing.x + style->window.header.padding.x;
            } else {
                button.x = header.x + style->window.header.padding.x;
                header.x += button.w + style->window.header.spacing.x + style->window.header.padding.x;
            }

            if (nk_do_button_symbol(&ws, &win->buffer, button,
                style->window.header.close_symbol, NK_BUTTON_DEFAULT,
                &style->window.header.close_button, in, style->font) && !(win->flags & NK_WINDOW_ROM))
            {
                layout->flags |= NK_WINDOW_HIDDEN;
                layout->flags &= (nk_flags)~NK_WINDOW_MINIMIZED;
            }
        }

        if (win->flags & NK_WINDOW_MINIMIZABLE) {
            nk_flags ws = 0;
            if (style->window.header.align == NK_HEADER_RIGHT) {
                button.x = (header.w + header.x) - button.w;
                if (!(win->flags & NK_WINDOW_CLOSABLE)) {
                    button.x -= style->window.header.padding.x;
                    header.w -= style->window.header.padding.x;
                }
                header.w -= button.w + style->window.header.spacing.x;
            } else {
                button.x = header.x;
                header.x += button.w + style->window.header.spacing.x + style->window.header.padding.x;
            }
            if (nk_do_button_symbol(&ws, &win->buffer, button, (layout->flags & NK_WINDOW_MINIMIZED)?
                style->window.header.maximize_symbol: style->window.header.minimize_symbol,
                NK_BUTTON_DEFAULT, &style->window.header.minimize_button, in, style->font) && !(win->flags & NK_WINDOW_ROM))
                layout->flags = (layout->flags & NK_WINDOW_MINIMIZED) ?
                    layout->flags & (nk_flags)~NK_WINDOW_MINIMIZED:
                    layout->flags | NK_WINDOW_MINIMIZED;
        }}

        {
        int text_len = nk_strlen(title);
        struct nk_rect label = {0,0,0,0};
        float t = font->width(font->userdata, font->height, title, text_len);
        text.padding = nk_vec2(0,0);

        label.x = header.x + style->window.header.padding.x;
        label.x += style->window.header.label_padding.x;
        label.y = header.y + style->window.header.label_padding.y;
        label.h = font->height + 2 * style->window.header.label_padding.y;
        label.w = t + 2 * style->window.header.spacing.x;
        label.w = NK_CLAMP(0, label.w, header.x + header.w - label.x);
        nk_widget_text(out, label, (const char*)title, text_len, &text, NK_TEXT_LEFT, font);}
    }

    if (!(layout->flags & NK_WINDOW_MINIMIZED) && !(layout->flags & NK_WINDOW_DYNAMIC)) {
        struct nk_rect body;
        body.x = win->bounds.x;
        body.w = win->bounds.w;
        body.y = (win->bounds.y + layout->header_height);
        body.h = (win->bounds.h - layout->header_height);

        switch(style->window.fixed_background.type) {
            case NK_STYLE_ITEM_IMAGE:
                nk_draw_image(out, body, &style->window.fixed_background.data.image, nk_white);
                break;
            case NK_STYLE_ITEM_NINE_SLICE:
                nk_draw_nine_slice(out, body, &style->window.fixed_background.data.slice, nk_white);
                break;
            case NK_STYLE_ITEM_COLOR:
                nk_fill_rect(out, body, 0, style->window.fixed_background.data.color);
                break;
        }
    }

    {struct nk_rect clip;
    layout->clip = layout->bounds;
    nk_unify(&clip, &win->buffer.clip, layout->clip.x, layout->clip.y,
        layout->clip.x + layout->clip.w, layout->clip.y + layout->clip.h);
    nk_push_scissor(out, clip);
    layout->clip = clip;}
    return !(layout->flags & NK_WINDOW_HIDDEN) && !(layout->flags & NK_WINDOW_MINIMIZED);
}
NK_LIB void
nk_panel_end(struct nk_context *ctx)
{
    struct nk_input *in;
    struct nk_window *window;
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_command_buffer *out;

    struct nk_vec2 scrollbar_size;
    struct nk_vec2 panel_padding;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    window = ctx->current;
    layout = window->layout;
    style = &ctx->style;
    out = &window->buffer;
    in = (layout->flags & NK_WINDOW_ROM || layout->flags & NK_WINDOW_NO_INPUT) ? 0 :&ctx->input;
    if (!nk_panel_is_sub(layout->type))
        nk_push_scissor(out, nk_null_rect);

    scrollbar_size = style->window.scrollbar_size;
    panel_padding = nk_panel_get_padding(style, layout->type);

    layout->at_y += layout->row.height;

    if (layout->flags & NK_WINDOW_DYNAMIC && !(layout->flags & NK_WINDOW_MINIMIZED))
    {

        struct nk_rect empty_space;
        if (layout->at_y < (layout->bounds.y + layout->bounds.h))
            layout->bounds.h = layout->at_y - layout->bounds.y;

        empty_space.x = window->bounds.x;
        empty_space.y = layout->bounds.y;
        empty_space.h = panel_padding.y;
        empty_space.w = window->bounds.w;
        nk_fill_rect(out, empty_space, 0, style->window.background);

        empty_space.x = window->bounds.x;
        empty_space.y = layout->bounds.y;
        empty_space.w = panel_padding.x + layout->border;
        empty_space.h = layout->bounds.h;
        nk_fill_rect(out, empty_space, 0, style->window.background);

        empty_space.x = layout->bounds.x + layout->bounds.w;
        empty_space.y = layout->bounds.y;
        empty_space.w = panel_padding.x + layout->border;
        empty_space.h = layout->bounds.h;
        if (*layout->offset_y == 0 && !(layout->flags & NK_WINDOW_NO_SCROLLBAR))
            empty_space.w += scrollbar_size.x;
        nk_fill_rect(out, empty_space, 0, style->window.background);

        if (layout->footer_height > 0) {
            empty_space.x = window->bounds.x;
            empty_space.y = layout->bounds.y + layout->bounds.h;
            empty_space.w = window->bounds.w;
            empty_space.h = layout->footer_height;
            nk_fill_rect(out, empty_space, 0, style->window.background);
        }
    }

    if (!(layout->flags & NK_WINDOW_NO_SCROLLBAR) &&
        !(layout->flags & NK_WINDOW_MINIMIZED) &&
        window->scrollbar_hiding_timer < NK_SCROLLBAR_HIDING_TIMEOUT)
    {
        struct nk_rect scroll;
        int scroll_has_scrolling;
        float scroll_target;
        float scroll_offset;
        float scroll_step;
        float scroll_inc;

        if (nk_panel_is_sub(layout->type))
        {

            struct nk_window *root_window = window;
            struct nk_panel *root_panel = window->layout;
            while (root_panel->parent)
                root_panel = root_panel->parent;
            while (root_window->parent)
                root_window = root_window->parent;

            scroll_has_scrolling = 0;
            if ((root_window == ctx->active) && layout->has_scrolling) {

                if (nk_input_is_mouse_hovering_rect(in, layout->bounds) &&
                    NK_INTERSECT(layout->bounds.x, layout->bounds.y, layout->bounds.w, layout->bounds.h,
                        root_panel->clip.x, root_panel->clip.y, root_panel->clip.w, root_panel->clip.h))
                {

                    root_panel = window->layout;
                    while (root_panel->parent) {
                        root_panel->has_scrolling = nk_false;
                        root_panel = root_panel->parent;
                    }
                    root_panel->has_scrolling = nk_false;
                    scroll_has_scrolling = nk_true;
                }
            }
        } else if (!nk_panel_is_sub(layout->type)) {

            scroll_has_scrolling = (window == ctx->active) && layout->has_scrolling;
            if (in && (in->mouse.scroll_delta.y > 0 || in->mouse.scroll_delta.x > 0) && scroll_has_scrolling)
                window->scrolled = nk_true;
            else window->scrolled = nk_false;
        } else scroll_has_scrolling = nk_false;

        {

            nk_flags state = 0;
            scroll.x = layout->bounds.x + layout->bounds.w + panel_padding.x;
            scroll.y = layout->bounds.y;
            scroll.w = scrollbar_size.x;
            scroll.h = layout->bounds.h;

            scroll_offset = (float)*layout->offset_y;
            scroll_step = scroll.h * 0.10f;
            scroll_inc = scroll.h * 0.01f;
            scroll_target = (float)(int)(layout->at_y - scroll.y);
            scroll_offset = nk_do_scrollbarv(&state, out, scroll, scroll_has_scrolling,
                scroll_offset, scroll_target, scroll_step, scroll_inc,
                &ctx->style.scrollv, in, style->font);
            *layout->offset_y = (nk_uint)scroll_offset;
            if (in && scroll_has_scrolling)
                in->mouse.scroll_delta.y = 0;
        }
        {

            nk_flags state = 0;
            scroll.x = layout->bounds.x;
            scroll.y = layout->bounds.y + layout->bounds.h;
            scroll.w = layout->bounds.w;
            scroll.h = scrollbar_size.y;

            scroll_offset = (float)*layout->offset_x;
            scroll_target = (float)(int)(layout->max_x - scroll.x);
            scroll_step = layout->max_x * 0.05f;
            scroll_inc = layout->max_x * 0.005f;
            scroll_offset = nk_do_scrollbarh(&state, out, scroll, scroll_has_scrolling,
                scroll_offset, scroll_target, scroll_step, scroll_inc,
                &ctx->style.scrollh, in, style->font);
            *layout->offset_x = (nk_uint)scroll_offset;
        }
    }

    if (window->flags & NK_WINDOW_SCROLL_AUTO_HIDE) {
        int has_input = ctx->input.mouse.delta.x != 0 || ctx->input.mouse.delta.y != 0 || ctx->input.mouse.scroll_delta.y != 0;
        int is_window_hovered = nk_window_is_hovered(ctx);
        int any_item_active = (ctx->last_widget_state & NK_WIDGET_STATE_MODIFIED);
        if ((!has_input && is_window_hovered) || (!is_window_hovered && !any_item_active))
            window->scrollbar_hiding_timer += ctx->delta_time_seconds;
        else window->scrollbar_hiding_timer = 0;
    } else window->scrollbar_hiding_timer = 0;

    if (layout->flags & NK_WINDOW_BORDER)
    {
        struct nk_color border_color = nk_panel_get_border_color(style, layout->type);
        const float padding_y = (layout->flags & NK_WINDOW_MINIMIZED)
            ? (style->window.border + window->bounds.y + layout->header_height)
            : ((layout->flags & NK_WINDOW_DYNAMIC)
                ? (layout->bounds.y + layout->bounds.h + layout->footer_height)
                : (window->bounds.y + window->bounds.h));
        struct nk_rect b = window->bounds;
        b.h = padding_y - window->bounds.y;
        nk_stroke_rect(out, b, 0, layout->border, border_color);
    }

    if ((layout->flags & NK_WINDOW_SCALABLE) && in && !(layout->flags & NK_WINDOW_MINIMIZED))
    {

        struct nk_rect scaler;
        scaler.w = scrollbar_size.x;
        scaler.h = scrollbar_size.y;
        scaler.y = layout->bounds.y + layout->bounds.h;
        if (layout->flags & NK_WINDOW_SCALE_LEFT)
            scaler.x = layout->bounds.x - panel_padding.x * 0.5f;
        else scaler.x = layout->bounds.x + layout->bounds.w + panel_padding.x;
        if (layout->flags & NK_WINDOW_NO_SCROLLBAR)
            scaler.x -= scaler.w;

        {const struct nk_style_item *item = &style->window.scaler;
        if (item->type == NK_STYLE_ITEM_IMAGE)
            nk_draw_image(out, scaler, &item->data.image, nk_white);
        else {
            if (layout->flags & NK_WINDOW_SCALE_LEFT) {
                nk_fill_triangle(out, scaler.x, scaler.y, scaler.x,
                    scaler.y + scaler.h, scaler.x + scaler.w,
                    scaler.y + scaler.h, item->data.color);
            } else {
                nk_fill_triangle(out, scaler.x + scaler.w, scaler.y, scaler.x + scaler.w,
                    scaler.y + scaler.h, scaler.x, scaler.y + scaler.h, item->data.color);
            }
        }}

        if (!(window->flags & NK_WINDOW_ROM)) {
            struct nk_vec2 window_size = style->window.min_size;
            int left_mouse_down = in->mouse.buttons[NK_BUTTON_LEFT].down;
            int left_mouse_click_in_scaler = nk_input_has_mouse_click_down_in_rect(in,
                    NK_BUTTON_LEFT, scaler, nk_true);

            if (left_mouse_down && left_mouse_click_in_scaler) {
                float delta_x = in->mouse.delta.x;
                if (layout->flags & NK_WINDOW_SCALE_LEFT) {
                    delta_x = -delta_x;
                    window->bounds.x += in->mouse.delta.x;
                }

                if (window->bounds.w + delta_x >= window_size.x) {
                    if ((delta_x < 0) || (delta_x > 0 && in->mouse.pos.x >= scaler.x)) {
                        window->bounds.w = window->bounds.w + delta_x;
                        scaler.x += in->mouse.delta.x;
                    }
                }

                if (!(layout->flags & NK_WINDOW_DYNAMIC)) {
                    if (window_size.y < window->bounds.h + in->mouse.delta.y) {
                        if ((in->mouse.delta.y < 0) || (in->mouse.delta.y > 0 && in->mouse.pos.y >= scaler.y)) {
                            window->bounds.h = window->bounds.h + in->mouse.delta.y;
                            scaler.y += in->mouse.delta.y;
                        }
                    }
                }
                ctx->style.cursor_active = ctx->style.cursors[NK_CURSOR_RESIZE_TOP_RIGHT_DOWN_LEFT];
                in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.x = scaler.x + scaler.w/2.0f;
                in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.y = scaler.y + scaler.h/2.0f;
            }
        }
    }
    if (!nk_panel_is_sub(layout->type)) {

        if (layout->flags & NK_WINDOW_HIDDEN)
            nk_command_buffer_reset(&window->buffer);

        else nk_finish(ctx, window);
    }

    if (layout->flags & NK_WINDOW_REMOVE_ROM) {
        layout->flags &= ~(nk_flags)NK_WINDOW_ROM;
        layout->flags &= ~(nk_flags)NK_WINDOW_REMOVE_ROM;
    }
    window->flags = layout->flags;

    if (window->property.active && window->property.old != window->property.seq &&
        window->property.active == window->property.prev) {
        nk_zero(&window->property, sizeof(window->property));
    } else {
        window->property.old = window->property.seq;
        window->property.prev = window->property.active;
        window->property.seq = 0;
    }

    if (window->edit.active && window->edit.old != window->edit.seq &&
       window->edit.active == window->edit.prev) {
        nk_zero(&window->edit, sizeof(window->edit));
    } else {
        window->edit.old = window->edit.seq;
        window->edit.prev = window->edit.active;
        window->edit.seq = 0;
    }

    if (window->popup.active_con && window->popup.con_old != window->popup.con_count) {
        window->popup.con_count = 0;
        window->popup.con_old = 0;
        window->popup.active_con = 0;
    } else {
        window->popup.con_old = window->popup.con_count;
        window->popup.con_count = 0;
    }
    window->popup.combo_count = 0;

    NK_ASSERT(!layout->row.tree_depth);
}

NK_LIB void*
nk_create_window(struct nk_context *ctx)
{
    struct nk_page_element *elem;
    elem = nk_create_page_element(ctx);
    if (!elem) return 0;
    elem->data.win.seq = ctx->seq;
    return &elem->data.win;
}
NK_LIB void
nk_free_window(struct nk_context *ctx, struct nk_window *win)
{

    struct nk_table *it = win->tables;
    if (win->popup.win) {
        nk_free_window(ctx, win->popup.win);
        win->popup.win = 0;
    }
    win->next = 0;
    win->prev = 0;

    while (it) {

        struct nk_table *n = it->next;
        nk_remove_table(win, it);
        nk_free_table(ctx, it);
        if (it == win->tables)
            win->tables = n;
        it = n;
    }

    {union nk_page_data *pd = NK_CONTAINER_OF(win, union nk_page_data, win);
    struct nk_page_element *pe = NK_CONTAINER_OF(pd, struct nk_page_element, data);
    nk_free_page_element(ctx, pe);}
}
NK_LIB struct nk_window*
nk_find_window(struct nk_context *ctx, nk_hash hash, const char *name)
{
    struct nk_window *iter;
    iter = ctx->begin;
    while (iter) {
        NK_ASSERT(iter != iter->next);
        if (iter->name == hash) {
            int max_len = nk_strlen(iter->name_string);
            if (!nk_stricmpn(iter->name_string, name, max_len))
                return iter;
        }
        iter = iter->next;
    }
    return 0;
}
NK_LIB void
nk_insert_window(struct nk_context *ctx, struct nk_window *win,
    enum nk_window_insert_location loc)
{
    const struct nk_window *iter;
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!win || !ctx) return;

    iter = ctx->begin;
    while (iter) {
        NK_ASSERT(iter != iter->next);
        NK_ASSERT(iter != win);
        if (iter == win) return;
        iter = iter->next;
    }

    if (!ctx->begin) {
        win->next = 0;
        win->prev = 0;
        ctx->begin = win;
        ctx->end = win;
        ctx->count = 1;
        return;
    }
    if (loc == NK_INSERT_BACK) {
        struct nk_window *end;
        end = ctx->end;
        end->flags |= NK_WINDOW_ROM;
        end->next = win;
        win->prev = ctx->end;
        win->next = 0;
        ctx->end = win;
        ctx->active = ctx->end;
        ctx->end->flags &= ~(nk_flags)NK_WINDOW_ROM;
    } else {

        ctx->begin->prev = win;
        win->next = ctx->begin;
        win->prev = 0;
        ctx->begin = win;
        ctx->begin->flags &= ~(nk_flags)NK_WINDOW_ROM;
    }
    ctx->count++;
}
NK_LIB void
nk_remove_window(struct nk_context *ctx, struct nk_window *win)
{
    if (win == ctx->begin || win == ctx->end) {
        if (win == ctx->begin) {
            ctx->begin = win->next;
            if (win->next)
                win->next->prev = 0;
        }
        if (win == ctx->end) {
            ctx->end = win->prev;
            if (win->prev)
                win->prev->next = 0;
        }
    } else {
        if (win->next)
            win->next->prev = win->prev;
        if (win->prev)
            win->prev->next = win->next;
    }
    if (win == ctx->active || !ctx->active) {
        ctx->active = ctx->end;
        if (ctx->end)
            ctx->end->flags &= ~(nk_flags)NK_WINDOW_ROM;
    }
    win->next = 0;
    win->prev = 0;
    ctx->count--;
}
NK_API nk_bool
nk_begin(struct nk_context *ctx, const char *title,
    struct nk_rect bounds, nk_flags flags)
{
    return nk_begin_titled(ctx, title, title, bounds, flags);
}
NK_API nk_bool
nk_begin_titled(struct nk_context *ctx, const char *name, const char *title,
    struct nk_rect bounds, nk_flags flags)
{
    struct nk_window *win;
    struct nk_style *style;
    nk_hash name_hash;
    int name_len;
    int ret = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(name);
    NK_ASSERT(title);
    NK_ASSERT(ctx->style.font && ctx->style.font->width && "if this triggers you forgot to add a font");
    NK_ASSERT(!ctx->current && "if this triggers you missed a `nk_end` call");
    if (!ctx || ctx->current || !title || !name)
        return 0;

    style = &ctx->style;
    name_len = (int)nk_strlen(name);
    name_hash = nk_murmur_hash(name, (int)name_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, name_hash, name);
    if (!win) {

        nk_size name_length = (nk_size)name_len;
        win = (struct nk_window*)nk_create_window(ctx);
        NK_ASSERT(win);
        if (!win) return 0;

        if (flags & NK_WINDOW_BACKGROUND)
            nk_insert_window(ctx, win, NK_INSERT_FRONT);
        else nk_insert_window(ctx, win, NK_INSERT_BACK);
        nk_command_buffer_init(&win->buffer, &ctx->memory, NK_CLIPPING_ON);

        win->flags = flags;
        win->bounds = bounds;
        win->name = name_hash;
        name_length = NK_MIN(name_length, NK_WINDOW_MAX_NAME-1);
        NK_MEMCPY(win->name_string, name, name_length);
        win->name_string[name_length] = 0;
        win->popup.win = 0;
        if (!ctx->active)
            ctx->active = win;
    } else {

        win->flags &= ~(nk_flags)(NK_WINDOW_PRIVATE-1);
        win->flags |= flags;
        if (!(win->flags & (NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE)))
            win->bounds = bounds;

        NK_ASSERT(win->seq != ctx->seq);
        win->seq = ctx->seq;
        if (!ctx->active && !(win->flags & NK_WINDOW_HIDDEN)) {
            ctx->active = win;
            ctx->end = win;
        }
    }
    if (win->flags & NK_WINDOW_HIDDEN) {
        ctx->current = win;
        win->layout = 0;
        return 0;
    } else nk_start(ctx, win);

    if (!(win->flags & NK_WINDOW_HIDDEN) && !(win->flags & NK_WINDOW_NO_INPUT))
    {
        int inpanel, ishovered;
        struct nk_window *iter = win;
        float h = ctx->style.font->height + 2.0f * style->window.header.padding.y +
            (2.0f * style->window.header.label_padding.y);
        struct nk_rect win_bounds = (!(win->flags & NK_WINDOW_MINIMIZED))?
            win->bounds: nk_rect(win->bounds.x, win->bounds.y, win->bounds.w, h);

        inpanel = nk_input_has_mouse_click_down_in_rect(&ctx->input, NK_BUTTON_LEFT, win_bounds, nk_true);
        inpanel = inpanel && ctx->input.mouse.buttons[NK_BUTTON_LEFT].clicked;
        ishovered = nk_input_is_mouse_hovering_rect(&ctx->input, win_bounds);
        if ((win != ctx->active) && ishovered && !ctx->input.mouse.buttons[NK_BUTTON_LEFT].down) {
            iter = win->next;
            while (iter) {
                struct nk_rect iter_bounds = (!(iter->flags & NK_WINDOW_MINIMIZED))?
                    iter->bounds: nk_rect(iter->bounds.x, iter->bounds.y, iter->bounds.w, h);
                if (NK_INTERSECT(win_bounds.x, win_bounds.y, win_bounds.w, win_bounds.h,
                    iter_bounds.x, iter_bounds.y, iter_bounds.w, iter_bounds.h) &&
                    (!(iter->flags & NK_WINDOW_HIDDEN)))
                    break;

                if (iter->popup.win && iter->popup.active && !(iter->flags & NK_WINDOW_HIDDEN) &&
                    NK_INTERSECT(win->bounds.x, win_bounds.y, win_bounds.w, win_bounds.h,
                    iter->popup.win->bounds.x, iter->popup.win->bounds.y,
                    iter->popup.win->bounds.w, iter->popup.win->bounds.h))
                    break;
                iter = iter->next;
            }
        }

        if (iter && inpanel && (win != ctx->end)) {
            iter = win->next;
            while (iter) {

                struct nk_rect iter_bounds = (!(iter->flags & NK_WINDOW_MINIMIZED))?
                iter->bounds: nk_rect(iter->bounds.x, iter->bounds.y, iter->bounds.w, h);
                if (NK_INBOX(ctx->input.mouse.pos.x, ctx->input.mouse.pos.y,
                    iter_bounds.x, iter_bounds.y, iter_bounds.w, iter_bounds.h) &&
                    !(iter->flags & NK_WINDOW_HIDDEN))
                    break;
                if (iter->popup.win && iter->popup.active && !(iter->flags & NK_WINDOW_HIDDEN) &&
                    NK_INTERSECT(win_bounds.x, win_bounds.y, win_bounds.w, win_bounds.h,
                    iter->popup.win->bounds.x, iter->popup.win->bounds.y,
                    iter->popup.win->bounds.w, iter->popup.win->bounds.h))
                    break;
                iter = iter->next;
            }
        }
        if (iter && !(win->flags & NK_WINDOW_ROM) && (win->flags & NK_WINDOW_BACKGROUND)) {
            win->flags |= (nk_flags)NK_WINDOW_ROM;
            iter->flags &= ~(nk_flags)NK_WINDOW_ROM;
            ctx->active = iter;
            if (!(iter->flags & NK_WINDOW_BACKGROUND)) {

                nk_remove_window(ctx, iter);
                nk_insert_window(ctx, iter, NK_INSERT_BACK);
            }
        } else {
            if (!iter && ctx->end != win) {
                if (!(win->flags & NK_WINDOW_BACKGROUND)) {

                    nk_remove_window(ctx, win);
                    nk_insert_window(ctx, win, NK_INSERT_BACK);
                }
                win->flags &= ~(nk_flags)NK_WINDOW_ROM;
                ctx->active = win;
            }
            if (ctx->end != win && !(win->flags & NK_WINDOW_BACKGROUND))
                win->flags |= NK_WINDOW_ROM;
        }
    }
    win->layout = (struct nk_panel*)nk_create_panel(ctx);
    ctx->current = win;
    ret = nk_panel_begin(ctx, title, NK_PANEL_WINDOW);
    win->layout->offset_x = &win->scrollbar.x;
    win->layout->offset_y = &win->scrollbar.y;
    return ret;
}
NK_API void
nk_end(struct nk_context *ctx)
{
    struct nk_panel *layout;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current && "if this triggers you forgot to call `nk_begin`");
    if (!ctx || !ctx->current)
        return;

    layout = ctx->current->layout;
    if (!layout || (layout->type == NK_PANEL_WINDOW && (ctx->current->flags & NK_WINDOW_HIDDEN))) {
        ctx->current = 0;
        return;
    }
    nk_panel_end(ctx);
    nk_free_panel(ctx, ctx->current->layout);
    ctx->current = 0;
}
NK_API struct nk_rect
nk_window_get_bounds(const struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return nk_rect(0,0,0,0);
    return ctx->current->bounds;
}
NK_API struct nk_vec2
nk_window_get_position(const struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->bounds.x, ctx->current->bounds.y);
}
NK_API struct nk_vec2
nk_window_get_size(const struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->bounds.w, ctx->current->bounds.h);
}
NK_API float
nk_window_get_width(const struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return 0;
    return ctx->current->bounds.w;
}
NK_API float
nk_window_get_height(const struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return 0;
    return ctx->current->bounds.h;
}
NK_API struct nk_rect
nk_window_get_content_region(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return nk_rect(0,0,0,0);
    return ctx->current->layout->clip;
}
NK_API struct nk_vec2
nk_window_get_content_region_min(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->layout->clip.x, ctx->current->layout->clip.y);
}
NK_API struct nk_vec2
nk_window_get_content_region_max(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->layout->clip.x + ctx->current->layout->clip.w,
        ctx->current->layout->clip.y + ctx->current->layout->clip.h);
}
NK_API struct nk_vec2
nk_window_get_content_region_size(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->layout->clip.w, ctx->current->layout->clip.h);
}
NK_API struct nk_command_buffer*
nk_window_get_canvas(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return 0;
    return &ctx->current->buffer;
}
NK_API struct nk_panel*
nk_window_get_panel(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return 0;
    return ctx->current->layout;
}
NK_API void
nk_window_get_scroll(struct nk_context *ctx, nk_uint *offset_x, nk_uint *offset_y)
{
    struct nk_window *win;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return ;
    win = ctx->current;
    if (offset_x)
      *offset_x = win->scrollbar.x;
    if (offset_y)
      *offset_y = win->scrollbar.y;
}
NK_API nk_bool
nk_window_has_focus(const struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return 0;
    return ctx->current == ctx->active;
}
NK_API nk_bool
nk_window_is_hovered(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current || (ctx->current->flags & NK_WINDOW_HIDDEN))
        return 0;
    else {
        struct nk_rect actual_bounds = ctx->current->bounds;
        if (ctx->begin->flags & NK_WINDOW_MINIMIZED) {
            actual_bounds.h = ctx->current->layout->header_height;
        }
        return nk_input_is_mouse_hovering_rect(&ctx->input, actual_bounds);
    }
}
NK_API nk_bool
nk_window_is_any_hovered(struct nk_context *ctx)
{
    struct nk_window *iter;
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    iter = ctx->begin;
    while (iter) {

        if(!(iter->flags & NK_WINDOW_HIDDEN)) {

            if (iter->popup.active && iter->popup.win && nk_input_is_mouse_hovering_rect(&ctx->input, iter->popup.win->bounds))
                return 1;

            if (iter->flags & NK_WINDOW_MINIMIZED) {
                struct nk_rect header = iter->bounds;
                header.h = ctx->style.font->height + 2 * ctx->style.window.header.padding.y;
                if (nk_input_is_mouse_hovering_rect(&ctx->input, header))
                    return 1;
            } else if (nk_input_is_mouse_hovering_rect(&ctx->input, iter->bounds)) {
                return 1;
            }
        }
        iter = iter->next;
    }
    return 0;
}
NK_API nk_bool
nk_item_is_any_active(struct nk_context *ctx)
{
    int any_hovered = nk_window_is_any_hovered(ctx);
    int any_active = (ctx->last_widget_state & NK_WIDGET_STATE_MODIFIED);
    return any_hovered || any_active;
}
NK_API nk_bool
nk_window_is_collapsed(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return 0;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash, name);
    if (!win) return 0;
    return win->flags & NK_WINDOW_MINIMIZED;
}
NK_API nk_bool
nk_window_is_closed(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return 1;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash, name);
    if (!win) return 1;
    return (win->flags & NK_WINDOW_CLOSED);
}
NK_API nk_bool
nk_window_is_hidden(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return 1;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash, name);
    if (!win) return 1;
    return (win->flags & NK_WINDOW_HIDDEN);
}
NK_API nk_bool
nk_window_is_active(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return 0;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash, name);
    if (!win) return 0;
    return win == ctx->active;
}
NK_API struct nk_window*
nk_window_find(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    return nk_find_window(ctx, title_hash, name);
}
NK_API void
nk_window_close(struct nk_context *ctx, const char *name)
{
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;
    win = nk_window_find(ctx, name);
    if (!win) return;
    NK_ASSERT(ctx->current != win && "You cannot close a currently active window");
    if (ctx->current == win) return;
    win->flags |= NK_WINDOW_HIDDEN;
    win->flags |= NK_WINDOW_CLOSED;
}
NK_API void
nk_window_set_bounds(struct nk_context *ctx,
    const char *name, struct nk_rect bounds)
{
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;
    win = nk_window_find(ctx, name);
    if (!win) return;
    NK_ASSERT(ctx->current != win && "You cannot update a currently in procecss window");
    win->bounds = bounds;
}
NK_API void
nk_window_set_position(struct nk_context *ctx,
    const char *name, struct nk_vec2 pos)
{
    struct nk_window *win = nk_window_find(ctx, name);
    if (!win) return;
    win->bounds.x = pos.x;
    win->bounds.y = pos.y;
}
NK_API void
nk_window_set_size(struct nk_context *ctx,
    const char *name, struct nk_vec2 size)
{
    struct nk_window *win = nk_window_find(ctx, name);
    if (!win) return;
    win->bounds.w = size.x;
    win->bounds.h = size.y;
}
NK_API void
nk_window_set_scroll(struct nk_context *ctx, nk_uint offset_x, nk_uint offset_y)
{
    struct nk_window *win;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return;
    win = ctx->current;
    win->scrollbar.x = offset_x;
    win->scrollbar.y = offset_y;
}
NK_API void
nk_window_collapse(struct nk_context *ctx, const char *name,
                    enum nk_collapse_states c)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash, name);
    if (!win) return;
    if (c == NK_MINIMIZED)
        win->flags |= NK_WINDOW_MINIMIZED;
    else win->flags &= ~(nk_flags)NK_WINDOW_MINIMIZED;
}
NK_API void
nk_window_collapse_if(struct nk_context *ctx, const char *name,
    enum nk_collapse_states c, int cond)
{
    NK_ASSERT(ctx);
    if (!ctx || !cond) return;
    nk_window_collapse(ctx, name, c);
}
NK_API void
nk_window_show(struct nk_context *ctx, const char *name, enum nk_show_states s)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash, name);
    if (!win) return;
    if (s == NK_HIDDEN) {
        win->flags |= NK_WINDOW_HIDDEN;
    } else win->flags &= ~(nk_flags)NK_WINDOW_HIDDEN;
}
NK_API void
nk_window_show_if(struct nk_context *ctx, const char *name,
    enum nk_show_states s, int cond)
{
    NK_ASSERT(ctx);
    if (!ctx || !cond) return;
    nk_window_show(ctx, name, s);
}

NK_API void
nk_window_set_focus(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash, name);
    if (win && ctx->end != win) {
        nk_remove_window(ctx, win);
        nk_insert_window(ctx, win, NK_INSERT_BACK);
    }
    ctx->active = win;
}

NK_API nk_bool
nk_popup_begin(struct nk_context *ctx, enum nk_popup_type type,
    const char *title, nk_flags flags, struct nk_rect rect)
{
    struct nk_window *popup;
    struct nk_window *win;
    struct nk_panel *panel;

    int title_len;
    nk_hash title_hash;
    nk_size allocated;

    NK_ASSERT(ctx);
    NK_ASSERT(title);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    panel = win->layout;
    NK_ASSERT(!(panel->type & NK_PANEL_SET_POPUP) && "popups are not allowed to have popups");
    (void)panel;
    title_len = (int)nk_strlen(title);
    title_hash = nk_murmur_hash(title, (int)title_len, NK_PANEL_POPUP);

    popup = win->popup.win;
    if (!popup) {
        popup = (struct nk_window*)nk_create_window(ctx);
        popup->parent = win;
        win->popup.win = popup;
        win->popup.active = 0;
        win->popup.type = NK_PANEL_POPUP;
    }

    if (win->popup.name != title_hash) {
        if (!win->popup.active) {
            nk_zero(popup, sizeof(*popup));
            win->popup.name = title_hash;
            win->popup.active = 1;
            win->popup.type = NK_PANEL_POPUP;
        } else return 0;
    }

    ctx->current = popup;
    rect.x += win->layout->clip.x;
    rect.y += win->layout->clip.y;

    popup->parent = win;
    popup->bounds = rect;
    popup->seq = ctx->seq;
    popup->layout = (struct nk_panel*)nk_create_panel(ctx);
    popup->flags = flags;
    popup->flags |= NK_WINDOW_BORDER;
    if (type == NK_POPUP_DYNAMIC)
        popup->flags |= NK_WINDOW_DYNAMIC;

    popup->buffer = win->buffer;
    nk_start_popup(ctx, win);
    allocated = ctx->memory.allocated;
    nk_push_scissor(&popup->buffer, nk_null_rect);

    if (nk_panel_begin(ctx, title, NK_PANEL_POPUP)) {

        struct nk_panel *root;
        root = win->layout;
        while (root) {
            root->flags |= NK_WINDOW_ROM;
            root->flags &= ~(nk_flags)NK_WINDOW_REMOVE_ROM;
            root = root->parent;
        }
        win->popup.active = 1;
        popup->layout->offset_x = &popup->scrollbar.x;
        popup->layout->offset_y = &popup->scrollbar.y;
        popup->layout->parent = win->layout;
        return 1;
    } else {

        struct nk_panel *root;
        root = win->layout;
        while (root) {
            root->flags |= NK_WINDOW_REMOVE_ROM;
            root = root->parent;
        }
        win->popup.buf.active = 0;
        win->popup.active = 0;
        ctx->memory.allocated = allocated;
        ctx->current = win;
        nk_free_panel(ctx, popup->layout);
        popup->layout = 0;
        return 0;
    }
}
NK_LIB nk_bool
nk_nonblock_begin(struct nk_context *ctx,
    nk_flags flags, struct nk_rect body, struct nk_rect header,
    enum nk_panel_type panel_type)
{
    struct nk_window *popup;
    struct nk_window *win;
    struct nk_panel *panel;
    int is_active = nk_true;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    panel = win->layout;
    NK_ASSERT(!(panel->type & NK_PANEL_SET_POPUP));
    (void)panel;
    popup = win->popup.win;
    if (!popup) {

        popup = (struct nk_window*)nk_create_window(ctx);
        popup->parent = win;
        win->popup.win = popup;
        win->popup.type = panel_type;
        nk_command_buffer_init(&popup->buffer, &ctx->memory, NK_CLIPPING_ON);
    } else {

        int pressed, in_body, in_header;
#ifdef NK_BUTTON_TRIGGER_ON_RELEASE
        pressed = nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT);
#else
        pressed = nk_input_is_mouse_pressed(&ctx->input, NK_BUTTON_LEFT);
#endif
        in_body = nk_input_is_mouse_hovering_rect(&ctx->input, body);
        in_header = nk_input_is_mouse_hovering_rect(&ctx->input, header);
        if (pressed && (!in_body || in_header))
            is_active = nk_false;
    }
    win->popup.header = header;

    if (!is_active) {

        struct nk_panel *root = win->layout;
        while (root) {
            root->flags |= NK_WINDOW_REMOVE_ROM;
            root = root->parent;
        }
        return is_active;
    }
    popup->bounds = body;
    popup->parent = win;
    popup->layout = (struct nk_panel*)nk_create_panel(ctx);
    popup->flags = flags;
    popup->flags |= NK_WINDOW_BORDER;
    popup->flags |= NK_WINDOW_DYNAMIC;
    popup->seq = ctx->seq;
    win->popup.active = 1;
    NK_ASSERT(popup->layout);

    nk_start_popup(ctx, win);
    popup->buffer = win->buffer;
    nk_push_scissor(&popup->buffer, nk_null_rect);
    ctx->current = popup;

    nk_panel_begin(ctx, 0, panel_type);
    win->buffer = popup->buffer;
    popup->layout->parent = win->layout;
    popup->layout->offset_x = &popup->scrollbar.x;
    popup->layout->offset_y = &popup->scrollbar.y;

    {struct nk_panel *root;
    root = win->layout;
    while (root) {
        root->flags |= NK_WINDOW_ROM;
        root = root->parent;
    }}
    return is_active;
}
NK_API void
nk_popup_close(struct nk_context *ctx)
{
    struct nk_window *popup;
    NK_ASSERT(ctx);
    if (!ctx || !ctx->current) return;

    popup = ctx->current;
    NK_ASSERT(popup->parent);
    NK_ASSERT(popup->layout->type & NK_PANEL_SET_POPUP);
    popup->flags |= NK_WINDOW_HIDDEN;
}
NK_API void
nk_popup_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_window *popup;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    popup = ctx->current;
    if (!popup->parent) return;
    win = popup->parent;
    if (popup->flags & NK_WINDOW_HIDDEN) {
        struct nk_panel *root;
        root = win->layout;
        while (root) {
            root->flags |= NK_WINDOW_REMOVE_ROM;
            root = root->parent;
        }
        win->popup.active = 0;
    }
    nk_push_scissor(&popup->buffer, nk_null_rect);
    nk_end(ctx);

    win->buffer = popup->buffer;
    nk_finish_popup(ctx, win);
    ctx->current = win;
    nk_push_scissor(&win->buffer, win->layout->clip);
}
NK_API void
nk_popup_get_scroll(struct nk_context *ctx, nk_uint *offset_x, nk_uint *offset_y)
{
    struct nk_window *popup;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    popup = ctx->current;
    if (offset_x)
      *offset_x = popup->scrollbar.x;
    if (offset_y)
      *offset_y = popup->scrollbar.y;
}
NK_API void
nk_popup_set_scroll(struct nk_context *ctx, nk_uint offset_x, nk_uint offset_y)
{
    struct nk_window *popup;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    popup = ctx->current;
    popup->scrollbar.x = offset_x;
    popup->scrollbar.y = offset_y;
}

NK_API nk_bool
nk_contextual_begin(struct nk_context *ctx, nk_flags flags, struct nk_vec2 size,
    struct nk_rect trigger_bounds)
{
    struct nk_window *win;
    struct nk_window *popup;
    struct nk_rect body;

    NK_STORAGE const struct nk_rect null_rect = {-1,-1,0,0};
    int is_clicked = 0;
    int is_open = 0;
    int ret = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    ++win->popup.con_count;
    if (ctx->current != ctx->active)
        return 0;

    popup = win->popup.win;
    is_open = (popup && win->popup.type == NK_PANEL_CONTEXTUAL);
    is_clicked = nk_input_mouse_clicked(&ctx->input, NK_BUTTON_RIGHT, trigger_bounds);
    if (win->popup.active_con && win->popup.con_count != win->popup.active_con)
        return 0;
    if (!is_open && win->popup.active_con)
        win->popup.active_con = 0;
    if ((!is_open && !is_clicked))
        return 0;

    win->popup.active_con = win->popup.con_count;
    if (is_clicked) {
        body.x = ctx->input.mouse.pos.x;
        body.y = ctx->input.mouse.pos.y;
    } else {
        body.x = popup->bounds.x;
        body.y = popup->bounds.y;
    }
    body.w = size.x;
    body.h = size.y;

    ret = nk_nonblock_begin(ctx, flags|NK_WINDOW_NO_SCROLLBAR, body,
            null_rect, NK_PANEL_CONTEXTUAL);
    if (ret) win->popup.type = NK_PANEL_CONTEXTUAL;
    else {
        win->popup.active_con = 0;
        win->popup.type = NK_PANEL_NONE;
        if (win->popup.win)
            win->popup.win->flags = 0;
    }
    return ret;
}
NK_API nk_bool
nk_contextual_item_text(struct nk_context *ctx, const char *text, int len,
    nk_flags alignment)
{
    struct nk_window *win;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    state = nk_widget_fitting(&bounds, ctx, style->contextual_button.padding);
    if (!state) return nk_false;

    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text(&ctx->last_widget_state, &win->buffer, bounds,
        text, len, alignment, NK_BUTTON_DEFAULT, &style->contextual_button, in, style->font)) {
        nk_contextual_close(ctx);
        return nk_true;
    }
    return nk_false;
}
NK_API nk_bool
nk_contextual_item_label(struct nk_context *ctx, const char *label, nk_flags align)
{
    return nk_contextual_item_text(ctx, label, nk_strlen(label), align);
}
NK_API nk_bool
nk_contextual_item_image_text(struct nk_context *ctx, struct nk_image img,
    const char *text, int len, nk_flags align)
{
    struct nk_window *win;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    state = nk_widget_fitting(&bounds, ctx, style->contextual_button.padding);
    if (!state) return nk_false;

    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text_image(&ctx->last_widget_state, &win->buffer, bounds,
        img, text, len, align, NK_BUTTON_DEFAULT, &style->contextual_button, style->font, in)){
        nk_contextual_close(ctx);
        return nk_true;
    }
    return nk_false;
}
NK_API nk_bool
nk_contextual_item_image_label(struct nk_context *ctx, struct nk_image img,
    const char *label, nk_flags align)
{
    return nk_contextual_item_image_text(ctx, img, label, nk_strlen(label), align);
}
NK_API nk_bool
nk_contextual_item_symbol_text(struct nk_context *ctx, enum nk_symbol_type symbol,
    const char *text, int len, nk_flags align)
{
    struct nk_window *win;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    state = nk_widget_fitting(&bounds, ctx, style->contextual_button.padding);
    if (!state) return nk_false;

    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text_symbol(&ctx->last_widget_state, &win->buffer, bounds,
        symbol, text, len, align, NK_BUTTON_DEFAULT, &style->contextual_button, style->font, in)) {
        nk_contextual_close(ctx);
        return nk_true;
    }
    return nk_false;
}
NK_API nk_bool
nk_contextual_item_symbol_label(struct nk_context *ctx, enum nk_symbol_type symbol,
    const char *text, nk_flags align)
{
    return nk_contextual_item_symbol_text(ctx, symbol, text, nk_strlen(text), align);
}
NK_API void
nk_contextual_close(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return;
    nk_popup_close(ctx);
}
NK_API void
nk_contextual_end(struct nk_context *ctx)
{
    struct nk_window *popup;
    struct nk_panel *panel;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return;

    popup = ctx->current;
    panel = popup->layout;
    NK_ASSERT(popup->parent);
    NK_ASSERT(panel->type & NK_PANEL_SET_POPUP);
    if (panel->flags & NK_WINDOW_DYNAMIC) {

        struct nk_rect body = {0,0,0,0};
        if (panel->at_y < (panel->bounds.y + panel->bounds.h)) {
            struct nk_vec2 padding = nk_panel_get_padding(&ctx->style, panel->type);
            body = panel->bounds;
            body.y = (panel->at_y + panel->footer_height + panel->border + padding.y + panel->row.height);
            body.h = (panel->bounds.y + panel->bounds.h) - body.y;
        }
        {int pressed = nk_input_is_mouse_pressed(&ctx->input, NK_BUTTON_LEFT);
        int in_body = nk_input_is_mouse_hovering_rect(&ctx->input, body);
        if (pressed && in_body)
            popup->flags |= NK_WINDOW_HIDDEN;
        }
    }
    if (popup->flags & NK_WINDOW_HIDDEN)
        popup->seq = 0;
    nk_popup_end(ctx);
    return;
}

NK_API void
nk_menubar_begin(struct nk_context *ctx)
{
    struct nk_panel *layout;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    layout = ctx->current->layout;
    NK_ASSERT(layout->at_y == layout->bounds.y);

    if (layout->flags & NK_WINDOW_HIDDEN || layout->flags & NK_WINDOW_MINIMIZED)
        return;

    layout->menu.x = layout->at_x;
    layout->menu.y = layout->at_y + layout->row.height;
    layout->menu.w = layout->bounds.w;
    layout->menu.offset.x = *layout->offset_x;
    layout->menu.offset.y = *layout->offset_y;
    *layout->offset_y = 0;
}
NK_API void
nk_menubar_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_command_buffer *out;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    out = &win->buffer;
    layout = win->layout;
    if (layout->flags & NK_WINDOW_HIDDEN || layout->flags & NK_WINDOW_MINIMIZED)
        return;

    layout->menu.h  = layout->at_y - layout->menu.y;
    layout->menu.h += layout->row.height + ctx->style.window.spacing.y;

    layout->bounds.y += layout->menu.h;
    layout->bounds.h -= layout->menu.h;

    *layout->offset_x = layout->menu.offset.x;
    *layout->offset_y = layout->menu.offset.y;
    layout->at_y      = layout->bounds.y - layout->row.height;

    layout->clip.y = layout->bounds.y;
    layout->clip.h = layout->bounds.h;
    nk_push_scissor(out, layout->clip);
}
NK_INTERN int
nk_menu_begin(struct nk_context *ctx, struct nk_window *win,
    const char *id, int is_clicked, struct nk_rect header, struct nk_vec2 size)
{
    int is_open = 0;
    int is_active = 0;
    struct nk_rect body;
    struct nk_window *popup;
    nk_hash hash = nk_murmur_hash(id, (int)nk_strlen(id), NK_PANEL_MENU);

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    body.x = header.x;
    body.w = size.x;
    body.y = header.y + header.h;
    body.h = size.y;

    popup = win->popup.win;
    is_open = popup ? nk_true : nk_false;
    is_active = (popup && (win->popup.name == hash) && win->popup.type == NK_PANEL_MENU);
    if ((is_clicked && is_open && !is_active) || (is_open && !is_active) ||
        (!is_open && !is_active && !is_clicked)) return 0;
    if (!nk_nonblock_begin(ctx, NK_WINDOW_NO_SCROLLBAR, body, header, NK_PANEL_MENU))
        return 0;

    win->popup.type = NK_PANEL_MENU;
    win->popup.name = hash;
    return 1;
}
NK_API nk_bool
nk_menu_begin_text(struct nk_context *ctx, const char *title, int len,
    nk_flags align, struct nk_vec2 size)
{
    struct nk_window *win;
    const struct nk_input *in;
    struct nk_rect header;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || win->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text(&ctx->last_widget_state, &win->buffer, header,
        title, len, align, NK_BUTTON_DEFAULT, &ctx->style.menu_button, in, ctx->style.font))
        is_clicked = nk_true;
    return nk_menu_begin(ctx, win, title, is_clicked, header, size);
}
NK_API nk_bool nk_menu_begin_label(struct nk_context *ctx,
    const char *text, nk_flags align, struct nk_vec2 size)
{
    return nk_menu_begin_text(ctx, text, nk_strlen(text), align, size);
}
NK_API nk_bool
nk_menu_begin_image(struct nk_context *ctx, const char *id, struct nk_image img,
    struct nk_vec2 size)
{
    struct nk_window *win;
    struct nk_rect header;
    const struct nk_input *in;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_image(&ctx->last_widget_state, &win->buffer, header,
        img, NK_BUTTON_DEFAULT, &ctx->style.menu_button, in))
        is_clicked = nk_true;
    return nk_menu_begin(ctx, win, id, is_clicked, header, size);
}
NK_API nk_bool
nk_menu_begin_symbol(struct nk_context *ctx, const char *id,
    enum nk_symbol_type sym, struct nk_vec2 size)
{
    struct nk_window *win;
    const struct nk_input *in;
    struct nk_rect header;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_symbol(&ctx->last_widget_state,  &win->buffer, header,
        sym, NK_BUTTON_DEFAULT, &ctx->style.menu_button, in, ctx->style.font))
        is_clicked = nk_true;
    return nk_menu_begin(ctx, win, id, is_clicked, header, size);
}
NK_API nk_bool
nk_menu_begin_image_text(struct nk_context *ctx, const char *title, int len,
    nk_flags align, struct nk_image img, struct nk_vec2 size)
{
    struct nk_window *win;
    struct nk_rect header;
    const struct nk_input *in;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text_image(&ctx->last_widget_state, &win->buffer,
        header, img, title, len, align, NK_BUTTON_DEFAULT, &ctx->style.menu_button,
        ctx->style.font, in))
        is_clicked = nk_true;
    return nk_menu_begin(ctx, win, title, is_clicked, header, size);
}
NK_API nk_bool
nk_menu_begin_image_label(struct nk_context *ctx,
    const char *title, nk_flags align, struct nk_image img, struct nk_vec2 size)
{
    return nk_menu_begin_image_text(ctx, title, nk_strlen(title), align, img, size);
}
NK_API nk_bool
nk_menu_begin_symbol_text(struct nk_context *ctx, const char *title, int len,
    nk_flags align, enum nk_symbol_type sym, struct nk_vec2 size)
{
    struct nk_window *win;
    struct nk_rect header;
    const struct nk_input *in;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;

    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text_symbol(&ctx->last_widget_state, &win->buffer,
        header, sym, title, len, align, NK_BUTTON_DEFAULT, &ctx->style.menu_button,
        ctx->style.font, in)) is_clicked = nk_true;
    return nk_menu_begin(ctx, win, title, is_clicked, header, size);
}
NK_API nk_bool
nk_menu_begin_symbol_label(struct nk_context *ctx,
    const char *title, nk_flags align, enum nk_symbol_type sym, struct nk_vec2 size )
{
    return nk_menu_begin_symbol_text(ctx, title, nk_strlen(title), align,sym,size);
}
NK_API nk_bool
nk_menu_item_text(struct nk_context *ctx, const char *title, int len, nk_flags align)
{
    return nk_contextual_item_text(ctx, title, len, align);
}
NK_API nk_bool
nk_menu_item_label(struct nk_context *ctx, const char *label, nk_flags align)
{
    return nk_contextual_item_label(ctx, label, align);
}
NK_API nk_bool
nk_menu_item_image_label(struct nk_context *ctx, struct nk_image img,
    const char *label, nk_flags align)
{
    return nk_contextual_item_image_label(ctx, img, label, align);
}
NK_API nk_bool
nk_menu_item_image_text(struct nk_context *ctx, struct nk_image img,
    const char *text, int len, nk_flags align)
{
    return nk_contextual_item_image_text(ctx, img, text, len, align);
}
NK_API nk_bool nk_menu_item_symbol_text(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *text, int len, nk_flags align)
{
    return nk_contextual_item_symbol_text(ctx, sym, text, len, align);
}
NK_API nk_bool nk_menu_item_symbol_label(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *label, nk_flags align)
{
    return nk_contextual_item_symbol_label(ctx, sym, label, align);
}
NK_API void nk_menu_close(struct nk_context *ctx)
{
    nk_contextual_close(ctx);
}
NK_API void
nk_menu_end(struct nk_context *ctx)
{
    nk_contextual_end(ctx);
}

NK_API void
nk_layout_set_min_row_height(struct nk_context *ctx, float height)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    layout->row.min_height = height;
}
NK_API void
nk_layout_reset_min_row_height(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    layout->row.min_height = ctx->style.font->height;
    layout->row.min_height += ctx->style.text.padding.y*2;
    layout->row.min_height += ctx->style.window.min_row_height_padding*2;
}
NK_LIB float
nk_layout_row_calculate_usable_space(const struct nk_style *style, enum nk_panel_type type,
    float total_space, int columns)
{
    float panel_spacing;
    float panel_space;

    struct nk_vec2 spacing;

    NK_UNUSED(type);

    spacing = style->window.spacing;

    panel_spacing = (float)NK_MAX(columns - 1, 0) * spacing.x;
    panel_space  = total_space - panel_spacing;
    return panel_space;
}
NK_LIB void
nk_panel_layout(const struct nk_context *ctx, struct nk_window *win,
    float height, int cols)
{
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_command_buffer *out;

    struct nk_vec2 item_spacing;
    struct nk_color color;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    layout = win->layout;
    style = &ctx->style;
    out = &win->buffer;
    color = style->window.background;
    item_spacing = style->window.spacing;

    NK_ASSERT(!(layout->flags & NK_WINDOW_MINIMIZED));
    NK_ASSERT(!(layout->flags & NK_WINDOW_HIDDEN));
    NK_ASSERT(!(layout->flags & NK_WINDOW_CLOSED));

    layout->row.index = 0;
    layout->at_y += layout->row.height;
    layout->row.columns = cols;
    if (height == 0.0f)
        layout->row.height = NK_MAX(height, layout->row.min_height) + item_spacing.y;
    else layout->row.height = height + item_spacing.y;

    layout->row.item_offset = 0;
    if (layout->flags & NK_WINDOW_DYNAMIC) {

        struct nk_rect background;
        background.x = win->bounds.x;
        background.w = win->bounds.w;
        background.y = layout->at_y - 1.0f;
        background.h = layout->row.height + 1.0f;
        nk_fill_rect(out, background, 0, color);
    }
}
NK_LIB void
nk_row_layout(struct nk_context *ctx, enum nk_layout_format fmt,
    float height, int cols, int width)
{

    struct nk_window *win;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    nk_panel_layout(ctx, win, height, cols);
    if (fmt == NK_DYNAMIC)
        win->layout->row.type = NK_LAYOUT_DYNAMIC_FIXED;
    else win->layout->row.type = NK_LAYOUT_STATIC_FIXED;

    win->layout->row.ratio = 0;
    win->layout->row.filled = 0;
    win->layout->row.item_offset = 0;
    win->layout->row.item_width = (float)width;
}
NK_API float
nk_layout_ratio_from_pixel(struct nk_context *ctx, float pixel_width)
{
    struct nk_window *win;
    NK_ASSERT(ctx);
    NK_ASSERT(pixel_width);
    if (!ctx || !ctx->current || !ctx->current->layout) return 0;
    win = ctx->current;
    return NK_CLAMP(0.0f, pixel_width/win->bounds.x, 1.0f);
}
NK_API void
nk_layout_row_dynamic(struct nk_context *ctx, float height, int cols)
{
    nk_row_layout(ctx, NK_DYNAMIC, height, cols, 0);
}
NK_API void
nk_layout_row_static(struct nk_context *ctx, float height, int item_width, int cols)
{
    nk_row_layout(ctx, NK_STATIC, height, cols, item_width);
}
NK_API void
nk_layout_row_begin(struct nk_context *ctx, enum nk_layout_format fmt,
    float row_height, int cols)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    nk_panel_layout(ctx, win, row_height, cols);
    if (fmt == NK_DYNAMIC)
        layout->row.type = NK_LAYOUT_DYNAMIC_ROW;
    else layout->row.type = NK_LAYOUT_STATIC_ROW;

    layout->row.ratio = 0;
    layout->row.filled = 0;
    layout->row.item_width = 0;
    layout->row.item_offset = 0;
    layout->row.columns = cols;
}
NK_API void
nk_layout_row_push(struct nk_context *ctx, float ratio_or_width)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    NK_ASSERT(layout->row.type == NK_LAYOUT_STATIC_ROW || layout->row.type == NK_LAYOUT_DYNAMIC_ROW);
    if (layout->row.type != NK_LAYOUT_STATIC_ROW && layout->row.type != NK_LAYOUT_DYNAMIC_ROW)
        return;

    if (layout->row.type == NK_LAYOUT_DYNAMIC_ROW) {
        float ratio = ratio_or_width;
        if ((ratio + layout->row.filled) > 1.0f) return;
        if (ratio > 0.0f)
            layout->row.item_width = NK_SATURATE(ratio);
        else layout->row.item_width = 1.0f - layout->row.filled;
    } else layout->row.item_width = ratio_or_width;
}
NK_API void
nk_layout_row_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    NK_ASSERT(layout->row.type == NK_LAYOUT_STATIC_ROW || layout->row.type == NK_LAYOUT_DYNAMIC_ROW);
    if (layout->row.type != NK_LAYOUT_STATIC_ROW && layout->row.type != NK_LAYOUT_DYNAMIC_ROW)
        return;
    layout->row.item_width = 0;
    layout->row.item_offset = 0;
}
NK_API void
nk_layout_row(struct nk_context *ctx, enum nk_layout_format fmt,
    float height, int cols, const float *ratio)
{
    int i;
    int n_undef = 0;
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    nk_panel_layout(ctx, win, height, cols);
    if (fmt == NK_DYNAMIC) {

        float r = 0;
        layout->row.ratio = ratio;
        for (i = 0; i < cols; ++i) {
            if (ratio[i] < 0.0f)
                n_undef++;
            else r += ratio[i];
        }
        r = NK_SATURATE(1.0f - r);
        layout->row.type = NK_LAYOUT_DYNAMIC;
        layout->row.item_width = (r > 0 && n_undef > 0) ? (r / (float)n_undef):0;
    } else {
        layout->row.ratio = ratio;
        layout->row.type = NK_LAYOUT_STATIC;
        layout->row.item_width = 0;
        layout->row.item_offset = 0;
    }
    layout->row.item_offset = 0;
    layout->row.filled = 0;
}
NK_API void
nk_layout_row_template_begin(struct nk_context *ctx, float height)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    nk_panel_layout(ctx, win, height, 1);
    layout->row.type = NK_LAYOUT_TEMPLATE;
    layout->row.columns = 0;
    layout->row.ratio = 0;
    layout->row.item_width = 0;
    layout->row.item_height = 0;
    layout->row.item_offset = 0;
    layout->row.filled = 0;
    layout->row.item.x = 0;
    layout->row.item.y = 0;
    layout->row.item.w = 0;
    layout->row.item.h = 0;
}
NK_API void
nk_layout_row_template_push_dynamic(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    NK_ASSERT(layout->row.type == NK_LAYOUT_TEMPLATE);
    NK_ASSERT(layout->row.columns < NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS);
    if (layout->row.type != NK_LAYOUT_TEMPLATE) return;
    if (layout->row.columns >= NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS) return;
    layout->row.templates[layout->row.columns++] = -1.0f;
}
NK_API void
nk_layout_row_template_push_variable(struct nk_context *ctx, float min_width)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    NK_ASSERT(layout->row.type == NK_LAYOUT_TEMPLATE);
    NK_ASSERT(layout->row.columns < NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS);
    if (layout->row.type != NK_LAYOUT_TEMPLATE) return;
    if (layout->row.columns >= NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS) return;
    layout->row.templates[layout->row.columns++] = -min_width;
}
NK_API void
nk_layout_row_template_push_static(struct nk_context *ctx, float width)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    NK_ASSERT(layout->row.type == NK_LAYOUT_TEMPLATE);
    NK_ASSERT(layout->row.columns < NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS);
    if (layout->row.type != NK_LAYOUT_TEMPLATE) return;
    if (layout->row.columns >= NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS) return;
    layout->row.templates[layout->row.columns++] = width;
}
NK_API void
nk_layout_row_template_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    int i = 0;
    int variable_count = 0;
    int min_variable_count = 0;
    float min_fixed_width = 0.0f;
    float total_fixed_width = 0.0f;
    float max_variable_width = 0.0f;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    NK_ASSERT(layout->row.type == NK_LAYOUT_TEMPLATE);
    if (layout->row.type != NK_LAYOUT_TEMPLATE) return;
    for (i = 0; i < layout->row.columns; ++i) {
        float width = layout->row.templates[i];
        if (width >= 0.0f) {
            total_fixed_width += width;
            min_fixed_width += width;
        } else if (width < -1.0f) {
            width = -width;
            total_fixed_width += width;
            max_variable_width = NK_MAX(max_variable_width, width);
            variable_count++;
        } else {
            min_variable_count++;
            variable_count++;
        }
    }
    if (variable_count) {
        float space = nk_layout_row_calculate_usable_space(&ctx->style, layout->type,
                            layout->bounds.w, layout->row.columns);
        float var_width = (NK_MAX(space-min_fixed_width,0.0f)) / (float)variable_count;
        int enough_space = var_width >= max_variable_width;
        if (!enough_space)
            var_width = (NK_MAX(space-total_fixed_width,0)) / (float)min_variable_count;
        for (i = 0; i < layout->row.columns; ++i) {
            float *width = &layout->row.templates[i];
            *width = (*width >= 0.0f)? *width: (*width < -1.0f && !enough_space)? -(*width): var_width;
        }
    }
}
NK_API void
nk_layout_space_begin(struct nk_context *ctx, enum nk_layout_format fmt,
    float height, int widget_count)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    nk_panel_layout(ctx, win, height, widget_count);
    if (fmt == NK_STATIC)
        layout->row.type = NK_LAYOUT_STATIC_FREE;
    else layout->row.type = NK_LAYOUT_DYNAMIC_FREE;

    layout->row.ratio = 0;
    layout->row.filled = 0;
    layout->row.item_width = 0;
    layout->row.item_offset = 0;
}
NK_API void
nk_layout_space_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    layout->row.item_width = 0;
    layout->row.item_height = 0;
    layout->row.item_offset = 0;
    nk_zero(&layout->row.item, sizeof(layout->row.item));
}
NK_API void
nk_layout_space_push(struct nk_context *ctx, struct nk_rect rect)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    layout->row.item = rect;
}
NK_API struct nk_rect
nk_layout_space_bounds(struct nk_context *ctx)
{
    struct nk_rect ret;
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x = layout->clip.x;
    ret.y = layout->clip.y;
    ret.w = layout->clip.w;
    ret.h = layout->row.height;
    return ret;
}
NK_API struct nk_rect
nk_layout_widget_bounds(struct nk_context *ctx)
{
    struct nk_rect ret;
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x = layout->at_x;
    ret.y = layout->at_y;
    ret.w = layout->bounds.w - NK_MAX(layout->at_x - layout->bounds.x,0);
    ret.h = layout->row.height;
    return ret;
}
NK_API struct nk_vec2
nk_layout_space_to_screen(struct nk_context *ctx, struct nk_vec2 ret)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x += layout->at_x - (float)*layout->offset_x;
    ret.y += layout->at_y - (float)*layout->offset_y;
    return ret;
}
NK_API struct nk_vec2
nk_layout_space_to_local(struct nk_context *ctx, struct nk_vec2 ret)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x += -layout->at_x + (float)*layout->offset_x;
    ret.y += -layout->at_y + (float)*layout->offset_y;
    return ret;
}
NK_API struct nk_rect
nk_layout_space_rect_to_screen(struct nk_context *ctx, struct nk_rect ret)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x += layout->at_x - (float)*layout->offset_x;
    ret.y += layout->at_y - (float)*layout->offset_y;
    return ret;
}
NK_API struct nk_rect
nk_layout_space_rect_to_local(struct nk_context *ctx, struct nk_rect ret)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x += -layout->at_x + (float)*layout->offset_x;
    ret.y += -layout->at_y + (float)*layout->offset_y;
    return ret;
}
NK_LIB void
nk_panel_alloc_row(const struct nk_context *ctx, struct nk_window *win)
{
    struct nk_panel *layout = win->layout;
    struct nk_vec2 spacing = ctx->style.window.spacing;
    const float row_height = layout->row.height - spacing.y;
    nk_panel_layout(ctx, win, row_height, layout->row.columns);
}
NK_LIB void
nk_layout_widget_space(struct nk_rect *bounds, const struct nk_context *ctx,
    struct nk_window *win, int modify)
{
    struct nk_panel *layout;
    const struct nk_style *style;

    struct nk_vec2 spacing;

    float item_offset = 0;
    float item_width = 0;
    float item_spacing = 0;
    float panel_space = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    style = &ctx->style;
    NK_ASSERT(bounds);

    spacing = style->window.spacing;
    panel_space = nk_layout_row_calculate_usable_space(&ctx->style, layout->type,
                                            layout->bounds.w, layout->row.columns);

    #define NK_FRAC(x) (x - (float)(int)x)

    switch (layout->row.type) {
    case NK_LAYOUT_DYNAMIC_FIXED: {

        float w = NK_MAX(1.0f,panel_space) / (float)layout->row.columns;
        item_offset = (float)layout->row.index * w;
        item_width = w + NK_FRAC(item_offset);
        item_spacing = (float)layout->row.index * spacing.x;
    } break;
    case NK_LAYOUT_DYNAMIC_ROW: {

        float w = layout->row.item_width * panel_space;
        item_offset = layout->row.item_offset;
        item_width = w + NK_FRAC(item_offset);
        item_spacing = 0;

        if (modify) {
            layout->row.item_offset += w + spacing.x;
            layout->row.filled += layout->row.item_width;
            layout->row.index = 0;
        }
    } break;
    case NK_LAYOUT_DYNAMIC_FREE: {

        bounds->x = layout->at_x + (layout->bounds.w * layout->row.item.x);
        bounds->x -= (float)*layout->offset_x;
        bounds->y = layout->at_y + (layout->row.height * layout->row.item.y);
        bounds->y -= (float)*layout->offset_y;
        bounds->w = layout->bounds.w  * layout->row.item.w + NK_FRAC(bounds->x);
        bounds->h = layout->row.height * layout->row.item.h + NK_FRAC(bounds->y);
        return;
    }
    case NK_LAYOUT_DYNAMIC: {

        float ratio, w;
        NK_ASSERT(layout->row.ratio);
        ratio = (layout->row.ratio[layout->row.index] < 0) ?
            layout->row.item_width : layout->row.ratio[layout->row.index];

        w = (ratio * panel_space);
        item_spacing = (float)layout->row.index * spacing.x;
        item_offset = layout->row.item_offset;
        item_width = w + NK_FRAC(item_offset);

        if (modify) {
            layout->row.item_offset += w;
            layout->row.filled += ratio;
        }
    } break;
    case NK_LAYOUT_STATIC_FIXED: {

        item_width = layout->row.item_width;
        item_offset = (float)layout->row.index * item_width;
        item_spacing = (float)layout->row.index * spacing.x;
    } break;
    case NK_LAYOUT_STATIC_ROW: {

        item_width = layout->row.item_width;
        item_offset = layout->row.item_offset;
        item_spacing = (float)layout->row.index * spacing.x;
        if (modify) layout->row.item_offset += item_width;
    } break;
    case NK_LAYOUT_STATIC_FREE: {

        bounds->x = layout->at_x + layout->row.item.x;
        bounds->w = layout->row.item.w;
        if (((bounds->x + bounds->w) > layout->max_x) && modify)
            layout->max_x = (bounds->x + bounds->w);
        bounds->x -= (float)*layout->offset_x;
        bounds->y = layout->at_y + layout->row.item.y;
        bounds->y -= (float)*layout->offset_y;
        bounds->h = layout->row.item.h;
        return;
    }
    case NK_LAYOUT_STATIC: {

        item_spacing = (float)layout->row.index * spacing.x;
        item_width = layout->row.ratio[layout->row.index];
        item_offset = layout->row.item_offset;
        if (modify) layout->row.item_offset += item_width;
    } break;
    case NK_LAYOUT_TEMPLATE: {

        float w;
        NK_ASSERT(layout->row.index < layout->row.columns);
        NK_ASSERT(layout->row.index < NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS);
        w = layout->row.templates[layout->row.index];
        item_offset = layout->row.item_offset;
        item_width = w + NK_FRAC(item_offset);
        item_spacing = (float)layout->row.index * spacing.x;
        if (modify) layout->row.item_offset += w;
    } break;
    #undef NK_FRAC
    default: NK_ASSERT(0); break;
    };

    bounds->w = item_width;
    bounds->h = layout->row.height - spacing.y;
    bounds->y = layout->at_y - (float)*layout->offset_y;
    bounds->x = layout->at_x + item_offset + item_spacing;
    if (((bounds->x + bounds->w) > layout->max_x) && modify)
        layout->max_x = bounds->x + bounds->w;
    bounds->x -= (float)*layout->offset_x;
}
NK_LIB void
nk_panel_alloc_space(struct nk_rect *bounds, const struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    if (layout->row.index >= layout->row.columns)
        nk_panel_alloc_row(ctx, win);

    nk_layout_widget_space(bounds, ctx, win, nk_true);
    layout->row.index++;
}
NK_LIB void
nk_layout_peek(struct nk_rect *bounds, struct nk_context *ctx)
{
    float y;
    int index;
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) {
        *bounds = nk_rect(0,0,0,0);
        return;
    }

    win = ctx->current;
    layout = win->layout;
    y = layout->at_y;
    index = layout->row.index;
    if (layout->row.index >= layout->row.columns) {
        layout->at_y += layout->row.height;
        layout->row.index = 0;
    }
    nk_layout_widget_space(bounds, ctx, win, nk_false);
    if (!layout->row.index) {
        bounds->x -= layout->row.item_offset;
    }
    layout->at_y = y;
    layout->row.index = index;
}
NK_API void
nk_spacer(struct nk_context *ctx )
{
    struct nk_rect dummy_rect = { 0, 0, 0, 0 };
    nk_panel_alloc_space( &dummy_rect, ctx );
}

NK_INTERN int
nk_tree_state_base(struct nk_context *ctx, enum nk_tree_type type,
    struct nk_image *img, const char *title, enum nk_collapse_states *state)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_command_buffer *out;
    const struct nk_input *in;
    const struct nk_style_button *button;
    enum nk_symbol_type symbol;
    float row_height;

    struct nk_vec2 item_spacing;
    struct nk_rect header = {0,0,0,0};
    struct nk_rect sym = {0,0,0,0};
    struct nk_text text;

    nk_flags ws = 0;
    enum nk_widget_layout_states widget_state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    layout = win->layout;
    out = &win->buffer;
    style = &ctx->style;
    item_spacing = style->window.spacing;

    row_height = style->font->height + 2 * style->tab.padding.y;
    nk_layout_set_min_row_height(ctx, row_height);
    nk_layout_row_dynamic(ctx, row_height, 1);
    nk_layout_reset_min_row_height(ctx);

    widget_state = nk_widget(&header, ctx);
    if (type == NK_TREE_TAB) {
        const struct nk_style_item *background = &style->tab.background;

        switch(background->type) {
            case NK_STYLE_ITEM_IMAGE:
                nk_draw_image(out, header, &background->data.image, nk_white);
                break;
            case NK_STYLE_ITEM_NINE_SLICE:
                nk_draw_nine_slice(out, header, &background->data.slice, nk_white);
                break;
            case NK_STYLE_ITEM_COLOR:
                nk_fill_rect(out, header, 0, style->tab.border_color);
                nk_fill_rect(out, nk_shrink_rect(header, style->tab.border),
                    style->tab.rounding, background->data.color);
                break;
        }
    } else text.background = style->window.background;

    in = (!(layout->flags & NK_WINDOW_ROM)) ? &ctx->input: 0;
    in = (in && widget_state == NK_WIDGET_VALID) ? &ctx->input : 0;
    if (nk_button_behavior(&ws, header, in, NK_BUTTON_DEFAULT))
        *state = (*state == NK_MAXIMIZED) ? NK_MINIMIZED : NK_MAXIMIZED;

    if (*state == NK_MAXIMIZED) {
        symbol = style->tab.sym_maximize;
        if (type == NK_TREE_TAB)
            button = &style->tab.tab_maximize_button;
        else button = &style->tab.node_maximize_button;
    } else {
        symbol = style->tab.sym_minimize;
        if (type == NK_TREE_TAB)
            button = &style->tab.tab_minimize_button;
        else button = &style->tab.node_minimize_button;
    }

    {
    sym.w = sym.h = style->font->height;
    sym.y = header.y + style->tab.padding.y;
    sym.x = header.x + style->tab.padding.x;
    nk_do_button_symbol(&ws, &win->buffer, sym, symbol, NK_BUTTON_DEFAULT,
        button, 0, style->font);

    if (img) {

        sym.x = sym.x + sym.w + 4 * item_spacing.x;
        nk_draw_image(&win->buffer, sym, img, nk_white);
        sym.w = style->font->height + style->tab.spacing.x;}
    }

    {
    struct nk_rect label;
    header.w = NK_MAX(header.w, sym.w + item_spacing.x);
    label.x = sym.x + sym.w + item_spacing.x;
    label.y = sym.y;
    label.w = header.w - (sym.w + item_spacing.y + style->tab.indent);
    label.h = style->font->height;
    text.text = style->tab.text;
    text.padding = nk_vec2(0,0);
    nk_widget_text(out, label, title, nk_strlen(title), &text,
        NK_TEXT_LEFT, style->font);}

    if (*state == NK_MAXIMIZED) {
        layout->at_x = header.x + (float)*layout->offset_x + style->tab.indent;
        layout->bounds.w = NK_MAX(layout->bounds.w, style->tab.indent);
        layout->bounds.w -= (style->tab.indent + style->window.padding.x);
        layout->row.tree_depth++;
        return nk_true;
    } else return nk_false;
}
NK_INTERN int
nk_tree_base(struct nk_context *ctx, enum nk_tree_type type,
    struct nk_image *img, const char *title, enum nk_collapse_states initial_state,
    const char *hash, int len, int line)
{
    struct nk_window *win = ctx->current;
    int title_len = 0;
    nk_hash tree_hash = 0;
    nk_uint *state = 0;

    if (!hash) {
        title_len = (int)nk_strlen(title);
        tree_hash = nk_murmur_hash(title, (int)title_len, (nk_hash)line);
    } else tree_hash = nk_murmur_hash(hash, len, (nk_hash)line);
    state = nk_find_value(win, tree_hash);
    if (!state) {
        state = nk_add_value(ctx, win, tree_hash, 0);
        *state = initial_state;
    }
    return nk_tree_state_base(ctx, type, img, title, (enum nk_collapse_states*)state);
}
NK_API nk_bool
nk_tree_state_push(struct nk_context *ctx, enum nk_tree_type type,
    const char *title, enum nk_collapse_states *state)
{
    return nk_tree_state_base(ctx, type, 0, title, state);
}
NK_API nk_bool
nk_tree_state_image_push(struct nk_context *ctx, enum nk_tree_type type,
    struct nk_image img, const char *title, enum nk_collapse_states *state)
{
    return nk_tree_state_base(ctx, type, &img, title, state);
}
NK_API void
nk_tree_state_pop(struct nk_context *ctx)
{
    struct nk_window *win = 0;
    struct nk_panel *layout = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    layout->at_x -= ctx->style.tab.indent + (float)*layout->offset_x;
    layout->bounds.w += ctx->style.tab.indent + ctx->style.window.padding.x;
    NK_ASSERT(layout->row.tree_depth);
    layout->row.tree_depth--;
}
NK_API nk_bool
nk_tree_push_hashed(struct nk_context *ctx, enum nk_tree_type type,
    const char *title, enum nk_collapse_states initial_state,
    const char *hash, int len, int line)
{
    return nk_tree_base(ctx, type, 0, title, initial_state, hash, len, line);
}
NK_API nk_bool
nk_tree_image_push_hashed(struct nk_context *ctx, enum nk_tree_type type,
    struct nk_image img, const char *title, enum nk_collapse_states initial_state,
    const char *hash, int len,int seed)
{
    return nk_tree_base(ctx, type, &img, title, initial_state, hash, len, seed);
}
NK_API void
nk_tree_pop(struct nk_context *ctx)
{
    nk_tree_state_pop(ctx);
}
NK_INTERN int
nk_tree_element_image_push_hashed_base(struct nk_context *ctx, enum nk_tree_type type,
    struct nk_image *img, const char *title, int title_len,
    enum nk_collapse_states *state, nk_bool *selected)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_command_buffer *out;
    const struct nk_input *in;
    const struct nk_style_button *button;
    enum nk_symbol_type symbol;
    float row_height;
    struct nk_vec2 padding;

    int text_len;
    float text_width;

    struct nk_vec2 item_spacing;
    struct nk_rect header = {0,0,0,0};
    struct nk_rect sym = {0,0,0,0};

    nk_flags ws = 0;
    enum nk_widget_layout_states widget_state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    layout = win->layout;
    out = &win->buffer;
    style = &ctx->style;
    item_spacing = style->window.spacing;
    padding = style->selectable.padding;

    row_height = style->font->height + 2 * style->tab.padding.y;
    nk_layout_set_min_row_height(ctx, row_height);
    nk_layout_row_dynamic(ctx, row_height, 1);
    nk_layout_reset_min_row_height(ctx);

    widget_state = nk_widget(&header, ctx);
    if (type == NK_TREE_TAB) {
        const struct nk_style_item *background = &style->tab.background;

        switch (background->type) {
            case NK_STYLE_ITEM_IMAGE:
                nk_draw_image(out, header, &background->data.image, nk_white);
                break;
            case NK_STYLE_ITEM_NINE_SLICE:
                nk_draw_nine_slice(out, header, &background->data.slice, nk_white);
                break;
            case NK_STYLE_ITEM_COLOR:
                nk_fill_rect(out, header, 0, style->tab.border_color);
                nk_fill_rect(out, nk_shrink_rect(header, style->tab.border),
                    style->tab.rounding, background->data.color);
                break;
        }
    }

    in = (!(layout->flags & NK_WINDOW_ROM)) ? &ctx->input: 0;
    in = (in && widget_state == NK_WIDGET_VALID) ? &ctx->input : 0;

    if (*state == NK_MAXIMIZED) {
        symbol = style->tab.sym_maximize;
        if (type == NK_TREE_TAB)
            button = &style->tab.tab_maximize_button;
        else button = &style->tab.node_maximize_button;
    } else {
        symbol = style->tab.sym_minimize;
        if (type == NK_TREE_TAB)
            button = &style->tab.tab_minimize_button;
        else button = &style->tab.node_minimize_button;
    }
    {
    sym.w = sym.h = style->font->height;
    sym.y = header.y + style->tab.padding.y;
    sym.x = header.x + style->tab.padding.x;
    if (nk_do_button_symbol(&ws, &win->buffer, sym, symbol, NK_BUTTON_DEFAULT, button, in, style->font))
        *state = (*state == NK_MAXIMIZED) ? NK_MINIMIZED : NK_MAXIMIZED;}

    {nk_flags dummy = 0;
    struct nk_rect label;

    text_len = nk_strlen(title);
    text_width = style->font->width(style->font->userdata, style->font->height, title, text_len);
    text_width += (4 * padding.x);

    header.w = NK_MAX(header.w, sym.w + item_spacing.x);
    label.x = sym.x + sym.w + item_spacing.x;
    label.y = sym.y;
    label.w = NK_MIN(header.w - (sym.w + item_spacing.y + style->tab.indent), text_width);
    label.h = style->font->height;

    if (img) {
        nk_do_selectable_image(&dummy, &win->buffer, label, title, title_len, NK_TEXT_LEFT,
            selected, img, &style->selectable, in, style->font);
    } else nk_do_selectable(&dummy, &win->buffer, label, title, title_len, NK_TEXT_LEFT,
            selected, &style->selectable, in, style->font);
    }

    if (*state == NK_MAXIMIZED) {
        layout->at_x = header.x + (float)*layout->offset_x + style->tab.indent;
        layout->bounds.w = NK_MAX(layout->bounds.w, style->tab.indent);
        layout->bounds.w -= (style->tab.indent + style->window.padding.x);
        layout->row.tree_depth++;
        return nk_true;
    } else return nk_false;
}
NK_INTERN int
nk_tree_element_base(struct nk_context *ctx, enum nk_tree_type type,
    struct nk_image *img, const char *title, enum nk_collapse_states initial_state,
    nk_bool *selected, const char *hash, int len, int line)
{
    struct nk_window *win = ctx->current;
    int title_len = 0;
    nk_hash tree_hash = 0;
    nk_uint *state = 0;

    if (!hash) {
        title_len = (int)nk_strlen(title);
        tree_hash = nk_murmur_hash(title, (int)title_len, (nk_hash)line);
    } else tree_hash = nk_murmur_hash(hash, len, (nk_hash)line);
    state = nk_find_value(win, tree_hash);
    if (!state) {
        state = nk_add_value(ctx, win, tree_hash, 0);
        *state = initial_state;
    } return nk_tree_element_image_push_hashed_base(ctx, type, img, title,
        nk_strlen(title), (enum nk_collapse_states*)state, selected);
}
NK_API nk_bool
nk_tree_element_push_hashed(struct nk_context *ctx, enum nk_tree_type type,
    const char *title, enum nk_collapse_states initial_state,
    nk_bool *selected, const char *hash, int len, int seed)
{
    return nk_tree_element_base(ctx, type, 0, title, initial_state, selected, hash, len, seed);
}
NK_API nk_bool
nk_tree_element_image_push_hashed(struct nk_context *ctx, enum nk_tree_type type,
    struct nk_image img, const char *title, enum nk_collapse_states initial_state,
    nk_bool *selected, const char *hash, int len,int seed)
{
    return nk_tree_element_base(ctx, type, &img, title, initial_state, selected, hash, len, seed);
}
NK_API void
nk_tree_element_pop(struct nk_context *ctx)
{
    nk_tree_state_pop(ctx);
}

NK_API nk_bool
nk_group_scrolled_offset_begin(struct nk_context *ctx,
    nk_uint *x_offset, nk_uint *y_offset, const char *title, nk_flags flags)
{
    struct nk_rect bounds;
    struct nk_window panel;
    struct nk_window *win;

    win = ctx->current;
    nk_panel_alloc_space(&bounds, ctx);
    {const struct nk_rect *c = &win->layout->clip;
    if (!NK_INTERSECT(c->x, c->y, c->w, c->h, bounds.x, bounds.y, bounds.w, bounds.h) &&
        !(flags & NK_WINDOW_MOVABLE)) {
        return 0;
    }}
    if (win->flags & NK_WINDOW_ROM)
        flags |= NK_WINDOW_ROM;

    nk_zero(&panel, sizeof(panel));
    panel.bounds = bounds;
    panel.flags = flags;
    panel.scrollbar.x = *x_offset;
    panel.scrollbar.y = *y_offset;
    panel.buffer = win->buffer;
    panel.layout = (struct nk_panel*)nk_create_panel(ctx);
    ctx->current = &panel;
    nk_panel_begin(ctx, (flags & NK_WINDOW_TITLE) ? title: 0, NK_PANEL_GROUP);

    win->buffer = panel.buffer;
    win->buffer.clip = panel.layout->clip;
    panel.layout->offset_x = x_offset;
    panel.layout->offset_y = y_offset;
    panel.layout->parent = win->layout;
    win->layout = panel.layout;

    ctx->current = win;
    if ((panel.layout->flags & NK_WINDOW_CLOSED) ||
        (panel.layout->flags & NK_WINDOW_MINIMIZED))
    {
        nk_flags f = panel.layout->flags;
        nk_group_scrolled_end(ctx);
        if (f & NK_WINDOW_CLOSED)
            return NK_WINDOW_CLOSED;
        if (f & NK_WINDOW_MINIMIZED)
            return NK_WINDOW_MINIMIZED;
    }
    return 1;
}
NK_API void
nk_group_scrolled_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *parent;
    struct nk_panel *g;

    struct nk_rect clip;
    struct nk_window pan;
    struct nk_vec2 panel_padding;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return;

    NK_ASSERT(ctx->current);
    win = ctx->current;
    NK_ASSERT(win->layout);
    g = win->layout;
    NK_ASSERT(g->parent);
    parent = g->parent;

    nk_zero_struct(pan);
    panel_padding = nk_panel_get_padding(&ctx->style, NK_PANEL_GROUP);
    pan.bounds.y = g->bounds.y - (g->header_height + g->menu.h);
    pan.bounds.x = g->bounds.x - panel_padding.x;
    pan.bounds.w = g->bounds.w + 2 * panel_padding.x;
    pan.bounds.h = g->bounds.h + g->header_height + g->menu.h;
    if (g->flags & NK_WINDOW_BORDER) {
        pan.bounds.x -= g->border;
        pan.bounds.y -= g->border;
        pan.bounds.w += 2*g->border;
        pan.bounds.h += 2*g->border;
    }
    if (!(g->flags & NK_WINDOW_NO_SCROLLBAR)) {
        pan.bounds.w += ctx->style.window.scrollbar_size.x;
        pan.bounds.h += ctx->style.window.scrollbar_size.y;
    }
    pan.scrollbar.x = *g->offset_x;
    pan.scrollbar.y = *g->offset_y;
    pan.flags = g->flags;
    pan.buffer = win->buffer;
    pan.layout = g;
    pan.parent = win;
    ctx->current = &pan;

    nk_unify(&clip, &parent->clip, pan.bounds.x, pan.bounds.y,
        pan.bounds.x + pan.bounds.w, pan.bounds.y + pan.bounds.h + panel_padding.x);
    nk_push_scissor(&pan.buffer, clip);
    nk_end(ctx);

    win->buffer = pan.buffer;
    nk_push_scissor(&win->buffer, parent->clip);
    ctx->current = win;
    win->layout = parent;
    g->bounds = pan.bounds;
    return;
}
NK_API nk_bool
nk_group_scrolled_begin(struct nk_context *ctx,
    struct nk_scroll *scroll, const char *title, nk_flags flags)
{
    return nk_group_scrolled_offset_begin(ctx, &scroll->x, &scroll->y, title, flags);
}
NK_API nk_bool
nk_group_begin_titled(struct nk_context *ctx, const char *id,
    const char *title, nk_flags flags)
{
    int id_len;
    nk_hash id_hash;
    struct nk_window *win;
    nk_uint *x_offset;
    nk_uint *y_offset;

    NK_ASSERT(ctx);
    NK_ASSERT(id);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !id)
        return 0;

    win = ctx->current;
    id_len = (int)nk_strlen(id);
    id_hash = nk_murmur_hash(id, (int)id_len, NK_PANEL_GROUP);
    x_offset = nk_find_value(win, id_hash);
    if (!x_offset) {
        x_offset = nk_add_value(ctx, win, id_hash, 0);
        y_offset = nk_add_value(ctx, win, id_hash+1, 0);

        NK_ASSERT(x_offset);
        NK_ASSERT(y_offset);
        if (!x_offset || !y_offset) return 0;
        *x_offset = *y_offset = 0;
    } else y_offset = nk_find_value(win, id_hash+1);
    return nk_group_scrolled_offset_begin(ctx, x_offset, y_offset, title, flags);
}
NK_API nk_bool
nk_group_begin(struct nk_context *ctx, const char *title, nk_flags flags)
{
    return nk_group_begin_titled(ctx, title, title, flags);
}
NK_API void
nk_group_end(struct nk_context *ctx)
{
    nk_group_scrolled_end(ctx);
}
NK_API void
nk_group_get_scroll(struct nk_context *ctx, const char *id, nk_uint *x_offset, nk_uint *y_offset)
{
    int id_len;
    nk_hash id_hash;
    struct nk_window *win;
    nk_uint *x_offset_ptr;
    nk_uint *y_offset_ptr;

    NK_ASSERT(ctx);
    NK_ASSERT(id);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !id)
        return;

    win = ctx->current;
    id_len = (int)nk_strlen(id);
    id_hash = nk_murmur_hash(id, (int)id_len, NK_PANEL_GROUP);
    x_offset_ptr = nk_find_value(win, id_hash);
    if (!x_offset_ptr) {
        x_offset_ptr = nk_add_value(ctx, win, id_hash, 0);
        y_offset_ptr = nk_add_value(ctx, win, id_hash+1, 0);

        NK_ASSERT(x_offset_ptr);
        NK_ASSERT(y_offset_ptr);
        if (!x_offset_ptr || !y_offset_ptr) return;
        *x_offset_ptr = *y_offset_ptr = 0;
    } else y_offset_ptr = nk_find_value(win, id_hash+1);
    if (x_offset)
      *x_offset = *x_offset_ptr;
    if (y_offset)
      *y_offset = *y_offset_ptr;
}
NK_API void
nk_group_set_scroll(struct nk_context *ctx, const char *id, nk_uint x_offset, nk_uint y_offset)
{
    int id_len;
    nk_hash id_hash;
    struct nk_window *win;
    nk_uint *x_offset_ptr;
    nk_uint *y_offset_ptr;

    NK_ASSERT(ctx);
    NK_ASSERT(id);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !id)
        return;

    win = ctx->current;
    id_len = (int)nk_strlen(id);
    id_hash = nk_murmur_hash(id, (int)id_len, NK_PANEL_GROUP);
    x_offset_ptr = nk_find_value(win, id_hash);
    if (!x_offset_ptr) {
        x_offset_ptr = nk_add_value(ctx, win, id_hash, 0);
        y_offset_ptr = nk_add_value(ctx, win, id_hash+1, 0);

        NK_ASSERT(x_offset_ptr);
        NK_ASSERT(y_offset_ptr);
        if (!x_offset_ptr || !y_offset_ptr) return;
        *x_offset_ptr = *y_offset_ptr = 0;
    } else y_offset_ptr = nk_find_value(win, id_hash+1);
    *x_offset_ptr = x_offset;
    *y_offset_ptr = y_offset;
}

NK_API nk_bool
nk_list_view_begin(struct nk_context *ctx, struct nk_list_view *view,
    const char *title, nk_flags flags, int row_height, int row_count)
{
    int title_len;
    nk_hash title_hash;
    nk_uint *x_offset;
    nk_uint *y_offset;

    int result;
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_vec2 item_spacing;

    NK_ASSERT(ctx);
    NK_ASSERT(view);
    NK_ASSERT(title);
    if (!ctx || !view || !title) return 0;

    win = ctx->current;
    style = &ctx->style;
    item_spacing = style->window.spacing;
    row_height += NK_MAX(0, (int)item_spacing.y);

    title_len = (int)nk_strlen(title);
    title_hash = nk_murmur_hash(title, (int)title_len, NK_PANEL_GROUP);
    x_offset = nk_find_value(win, title_hash);
    if (!x_offset) {
        x_offset = nk_add_value(ctx, win, title_hash, 0);
        y_offset = nk_add_value(ctx, win, title_hash+1, 0);

        NK_ASSERT(x_offset);
        NK_ASSERT(y_offset);
        if (!x_offset || !y_offset) return 0;
        *x_offset = *y_offset = 0;
    } else y_offset = nk_find_value(win, title_hash+1);
    view->scroll_value = *y_offset;
    view->scroll_pointer = y_offset;

    *y_offset = 0;
    result = nk_group_scrolled_offset_begin(ctx, x_offset, y_offset, title, flags);
    win = ctx->current;
    layout = win->layout;

    view->total_height = row_height * NK_MAX(row_count,1);
    view->begin = (int)NK_MAX(((float)view->scroll_value / (float)row_height), 0.0f);
    view->count = (int)NK_MAX(nk_iceilf((layout->clip.h)/(float)row_height),0);
    view->count = NK_MIN(view->count, row_count - view->begin);
    view->end = view->begin + view->count;
    view->ctx = ctx;
    return result;
}
NK_API void
nk_list_view_end(struct nk_list_view *view)
{
    struct nk_context *ctx;
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(view);
    NK_ASSERT(view->ctx);
    NK_ASSERT(view->scroll_pointer);
    if (!view || !view->ctx) return;

    ctx = view->ctx;
    win = ctx->current;
    layout = win->layout;
    layout->at_y = layout->bounds.y + (float)view->total_height;
    *view->scroll_pointer = *view->scroll_pointer + view->scroll_value;
    nk_group_end(view->ctx);
}

NK_API struct nk_rect
nk_widget_bounds(struct nk_context *ctx)
{
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return nk_rect(0,0,0,0);
    nk_layout_peek(&bounds, ctx);
    return bounds;
}
NK_API struct nk_vec2
nk_widget_position(struct nk_context *ctx)
{
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return nk_vec2(0,0);

    nk_layout_peek(&bounds, ctx);
    return nk_vec2(bounds.x, bounds.y);
}
NK_API struct nk_vec2
nk_widget_size(struct nk_context *ctx)
{
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return nk_vec2(0,0);

    nk_layout_peek(&bounds, ctx);
    return nk_vec2(bounds.w, bounds.h);
}
NK_API float
nk_widget_width(struct nk_context *ctx)
{
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return 0;

    nk_layout_peek(&bounds, ctx);
    return bounds.w;
}
NK_API float
nk_widget_height(struct nk_context *ctx)
{
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return 0;

    nk_layout_peek(&bounds, ctx);
    return bounds.h;
}
NK_API nk_bool
nk_widget_is_hovered(struct nk_context *ctx)
{
    struct nk_rect c, v;
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current || ctx->active != ctx->current)
        return 0;

    c = ctx->current->layout->clip;
    c.x = (float)((int)c.x);
    c.y = (float)((int)c.y);
    c.w = (float)((int)c.w);
    c.h = (float)((int)c.h);

    nk_layout_peek(&bounds, ctx);
    nk_unify(&v, &c, bounds.x, bounds.y, bounds.x + bounds.w, bounds.y + bounds.h);
    if (!NK_INTERSECT(c.x, c.y, c.w, c.h, bounds.x, bounds.y, bounds.w, bounds.h))
        return 0;
    return nk_input_is_mouse_hovering_rect(&ctx->input, bounds);
}
NK_API nk_bool
nk_widget_is_mouse_clicked(struct nk_context *ctx, enum nk_buttons btn)
{
    struct nk_rect c, v;
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current || ctx->active != ctx->current)
        return 0;

    c = ctx->current->layout->clip;
    c.x = (float)((int)c.x);
    c.y = (float)((int)c.y);
    c.w = (float)((int)c.w);
    c.h = (float)((int)c.h);

    nk_layout_peek(&bounds, ctx);
    nk_unify(&v, &c, bounds.x, bounds.y, bounds.x + bounds.w, bounds.y + bounds.h);
    if (!NK_INTERSECT(c.x, c.y, c.w, c.h, bounds.x, bounds.y, bounds.w, bounds.h))
        return 0;
    return nk_input_mouse_clicked(&ctx->input, btn, bounds);
}
NK_API nk_bool
nk_widget_has_mouse_click_down(struct nk_context *ctx, enum nk_buttons btn, nk_bool down)
{
    struct nk_rect c, v;
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current || ctx->active != ctx->current)
        return 0;

    c = ctx->current->layout->clip;
    c.x = (float)((int)c.x);
    c.y = (float)((int)c.y);
    c.w = (float)((int)c.w);
    c.h = (float)((int)c.h);

    nk_layout_peek(&bounds, ctx);
    nk_unify(&v, &c, bounds.x, bounds.y, bounds.x + bounds.w, bounds.y + bounds.h);
    if (!NK_INTERSECT(c.x, c.y, c.w, c.h, bounds.x, bounds.y, bounds.w, bounds.h))
        return 0;
    return nk_input_has_mouse_click_down_in_rect(&ctx->input, btn, bounds, down);
}
NK_API enum nk_widget_layout_states
nk_widget(struct nk_rect *bounds, const struct nk_context *ctx)
{
    struct nk_rect c, v;
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return NK_WIDGET_INVALID;

    nk_panel_alloc_space(bounds, ctx);
    win = ctx->current;
    layout = win->layout;
    in = &ctx->input;
    c = layout->clip;

    NK_ASSERT(!(layout->flags & NK_WINDOW_MINIMIZED));
    NK_ASSERT(!(layout->flags & NK_WINDOW_HIDDEN));
    NK_ASSERT(!(layout->flags & NK_WINDOW_CLOSED));

    bounds->x = (float)((int)bounds->x);
    bounds->y = (float)((int)bounds->y);
    bounds->w = (float)((int)bounds->w);
    bounds->h = (float)((int)bounds->h);

    c.x = (float)((int)c.x);
    c.y = (float)((int)c.y);
    c.w = (float)((int)c.w);
    c.h = (float)((int)c.h);

    nk_unify(&v, &c, bounds->x, bounds->y, bounds->x + bounds->w, bounds->y + bounds->h);
    if (!NK_INTERSECT(c.x, c.y, c.w, c.h, bounds->x, bounds->y, bounds->w, bounds->h))
        return NK_WIDGET_INVALID;
    if (!NK_INBOX(in->mouse.pos.x, in->mouse.pos.y, v.x, v.y, v.w, v.h))
        return NK_WIDGET_ROM;
    return NK_WIDGET_VALID;
}
NK_API enum nk_widget_layout_states
nk_widget_fitting(struct nk_rect *bounds, struct nk_context *ctx,
    struct nk_vec2 item_padding)
{

    enum nk_widget_layout_states state;
    NK_UNUSED(item_padding);

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return NK_WIDGET_INVALID;

    state = nk_widget(bounds, ctx);
    return state;
}
NK_API void
nk_spacing(struct nk_context *ctx, int cols)
{
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_rect none;
    int i, index, rows;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    index = (layout->row.index + cols) % layout->row.columns;
    rows = (layout->row.index + cols) / layout->row.columns;
    if (rows) {
        for (i = 0; i < rows; ++i)
            nk_panel_alloc_row(ctx, win);
        cols = index;
    }

    if (layout->row.type != NK_LAYOUT_DYNAMIC_FIXED &&
        layout->row.type != NK_LAYOUT_STATIC_FIXED) {
        for (i = 0; i < cols; ++i)
            nk_panel_alloc_space(&none, ctx);
    } layout->row.index = index;
}

NK_LIB void
nk_widget_text(struct nk_command_buffer *o, struct nk_rect b,
    const char *string, int len, const struct nk_text *t,
    nk_flags a, const struct nk_user_font *f)
{
    struct nk_rect label;
    float text_width;

    NK_ASSERT(o);
    NK_ASSERT(t);
    if (!o || !t) return;

    b.h = NK_MAX(b.h, 2 * t->padding.y);
    label.x = 0; label.w = 0;
    label.y = b.y + t->padding.y;
    label.h = NK_MIN(f->height, b.h - 2 * t->padding.y);

    text_width = f->width(f->userdata, f->height, (const char*)string, len);
    text_width += (2.0f * t->padding.x);

    if (a & NK_TEXT_ALIGN_LEFT) {
        label.x = b.x + t->padding.x;
        label.w = NK_MAX(0, b.w - 2 * t->padding.x);
    } else if (a & NK_TEXT_ALIGN_CENTERED) {
        label.w = NK_MAX(1, 2 * t->padding.x + (float)text_width);
        label.x = (b.x + t->padding.x + ((b.w - 2 * t->padding.x) - label.w) / 2);
        label.x = NK_MAX(b.x + t->padding.x, label.x);
        label.w = NK_MIN(b.x + b.w, label.x + label.w);
        if (label.w >= label.x) label.w -= label.x;
    } else if (a & NK_TEXT_ALIGN_RIGHT) {
        label.x = NK_MAX(b.x + t->padding.x, (b.x + b.w) - (2 * t->padding.x + (float)text_width));
        label.w = (float)text_width + 2 * t->padding.x;
    } else return;

    if (a & NK_TEXT_ALIGN_MIDDLE) {
        label.y = b.y + b.h/2.0f - (float)f->height/2.0f;
        label.h = NK_MAX(b.h/2.0f, b.h - (b.h/2.0f + f->height/2.0f));
    } else if (a & NK_TEXT_ALIGN_BOTTOM) {
        label.y = b.y + b.h - f->height;
        label.h = f->height;
    }
    nk_draw_text(o, label, (const char*)string, len, f, t->background, t->text);
}
NK_LIB void
nk_widget_text_wrap(struct nk_command_buffer *o, struct nk_rect b,
    const char *string, int len, const struct nk_text *t,
    const struct nk_user_font *f)
{
    float width;
    int glyphs = 0;
    int fitting = 0;
    int done = 0;
    struct nk_rect line;
    struct nk_text text;
    NK_INTERN nk_rune seperator[] = {' '};

    NK_ASSERT(o);
    NK_ASSERT(t);
    if (!o || !t) return;

    text.padding = nk_vec2(0,0);
    text.background = t->background;
    text.text = t->text;

    b.w = NK_MAX(b.w, 2 * t->padding.x);
    b.h = NK_MAX(b.h, 2 * t->padding.y);
    b.h = b.h - 2 * t->padding.y;

    line.x = b.x + t->padding.x;
    line.y = b.y + t->padding.y;
    line.w = b.w - 2 * t->padding.x;
    line.h = 2 * t->padding.y + f->height;

    fitting = nk_text_clamp(f, string, len, line.w, &glyphs, &width, seperator,NK_LEN(seperator));
    while (done < len) {
        if (!fitting || line.y + line.h >= (b.y + b.h)) break;
        nk_widget_text(o, line, &string[done], fitting, &text, NK_TEXT_LEFT, f);
        done += fitting;
        line.y += f->height + 2 * t->padding.y;
        fitting = nk_text_clamp(f, &string[done], len - done, line.w, &glyphs, &width, seperator,NK_LEN(seperator));
    }
}
NK_API void
nk_text_colored(struct nk_context *ctx, const char *str, int len,
    nk_flags alignment, struct nk_color color)
{
    struct nk_window *win;
    const struct nk_style *style;

    struct nk_vec2 item_padding;
    struct nk_rect bounds;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return;

    win = ctx->current;
    style = &ctx->style;
    nk_panel_alloc_space(&bounds, ctx);
    item_padding = style->text.padding;

    text.padding.x = item_padding.x;
    text.padding.y = item_padding.y;
    text.background = style->window.background;
    text.text = color;
    nk_widget_text(&win->buffer, bounds, str, len, &text, alignment, style->font);
}
NK_API void
nk_text_wrap_colored(struct nk_context *ctx, const char *str,
    int len, struct nk_color color)
{
    struct nk_window *win;
    const struct nk_style *style;

    struct nk_vec2 item_padding;
    struct nk_rect bounds;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return;

    win = ctx->current;
    style = &ctx->style;
    nk_panel_alloc_space(&bounds, ctx);
    item_padding = style->text.padding;

    text.padding.x = item_padding.x;
    text.padding.y = item_padding.y;
    text.background = style->window.background;
    text.text = color;
    nk_widget_text_wrap(&win->buffer, bounds, str, len, &text, style->font);
}
#ifdef NK_INCLUDE_STANDARD_VARARGS
NK_API void
nk_labelf_colored(struct nk_context *ctx, nk_flags flags,
    struct nk_color color, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    nk_labelfv_colored(ctx, flags, color, fmt, args);
    va_end(args);
}
NK_API void
nk_labelf_colored_wrap(struct nk_context *ctx, struct nk_color color,
    const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    nk_labelfv_colored_wrap(ctx, color, fmt, args);
    va_end(args);
}
NK_API void
nk_labelf(struct nk_context *ctx, nk_flags flags, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    nk_labelfv(ctx, flags, fmt, args);
    va_end(args);
}
NK_API void
nk_labelf_wrap(struct nk_context *ctx, const char *fmt,...)
{
    va_list args;
    va_start(args, fmt);
    nk_labelfv_wrap(ctx, fmt, args);
    va_end(args);
}
NK_API void
nk_labelfv_colored(struct nk_context *ctx, nk_flags flags,
    struct nk_color color, const char *fmt, va_list args)
{
    char buf[256];
    nk_strfmt(buf, NK_LEN(buf), fmt, args);
    nk_label_colored(ctx, buf, flags, color);
}

NK_API void
nk_labelfv_colored_wrap(struct nk_context *ctx, struct nk_color color,
    const char *fmt, va_list args)
{
    char buf[256];
    nk_strfmt(buf, NK_LEN(buf), fmt, args);
    nk_label_colored_wrap(ctx, buf, color);
}

NK_API void
nk_labelfv(struct nk_context *ctx, nk_flags flags, const char *fmt, va_list args)
{
    char buf[256];
    nk_strfmt(buf, NK_LEN(buf), fmt, args);
    nk_label(ctx, buf, flags);
}

NK_API void
nk_labelfv_wrap(struct nk_context *ctx, const char *fmt, va_list args)
{
    char buf[256];
    nk_strfmt(buf, NK_LEN(buf), fmt, args);
    nk_label_wrap(ctx, buf);
}

NK_API void
nk_value_bool(struct nk_context *ctx, const char *prefix, int value)
{
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: %s", prefix, ((value) ? "true": "false"));
}
NK_API void
nk_value_int(struct nk_context *ctx, const char *prefix, int value)
{
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: %d", prefix, value);
}
NK_API void
nk_value_uint(struct nk_context *ctx, const char *prefix, unsigned int value)
{
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: %u", prefix, value);
}
NK_API void
nk_value_float(struct nk_context *ctx, const char *prefix, float value)
{
    double double_value = (double)value;
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: %.3f", prefix, double_value);
}
NK_API void
nk_value_color_byte(struct nk_context *ctx, const char *p, struct nk_color c)
{
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: (%d, %d, %d, %d)", p, c.r, c.g, c.b, c.a);
}
NK_API void
nk_value_color_float(struct nk_context *ctx, const char *p, struct nk_color color)
{
    double c[4]; nk_color_dv(c, color);
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: (%.2f, %.2f, %.2f, %.2f)",
        p, c[0], c[1], c[2], c[3]);
}
NK_API void
nk_value_color_hex(struct nk_context *ctx, const char *prefix, struct nk_color color)
{
    char hex[16];
    nk_color_hex_rgba(hex, color);
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: %s", prefix, hex);
}
#endif
NK_API void
nk_text(struct nk_context *ctx, const char *str, int len, nk_flags alignment)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_text_colored(ctx, str, len, alignment, ctx->style.text.color);
}
NK_API void
nk_text_wrap(struct nk_context *ctx, const char *str, int len)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_text_wrap_colored(ctx, str, len, ctx->style.text.color);
}
NK_API void
nk_label(struct nk_context *ctx, const char *str, nk_flags alignment)
{
    nk_text(ctx, str, nk_strlen(str), alignment);
}
NK_API void
nk_label_colored(struct nk_context *ctx, const char *str, nk_flags align,
    struct nk_color color)
{
    nk_text_colored(ctx, str, nk_strlen(str), align, color);
}
NK_API void
nk_label_wrap(struct nk_context *ctx, const char *str)
{
    nk_text_wrap(ctx, str, nk_strlen(str));
}
NK_API void
nk_label_colored_wrap(struct nk_context *ctx, const char *str, struct nk_color color)
{
    nk_text_wrap_colored(ctx, str, nk_strlen(str), color);
}

NK_API nk_handle
nk_handle_ptr(void *ptr)
{
    nk_handle handle = {0};
    handle.ptr = ptr;
    return handle;
}
NK_API nk_handle
nk_handle_id(int id)
{
    nk_handle handle;
    nk_zero_struct(handle);
    handle.id = id;
    return handle;
}
NK_API struct nk_image
nk_subimage_ptr(void *ptr, nk_ushort w, nk_ushort h, struct nk_rect r)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    s.handle.ptr = ptr;
    s.w = w; s.h = h;
    s.region[0] = (nk_ushort)r.x;
    s.region[1] = (nk_ushort)r.y;
    s.region[2] = (nk_ushort)r.w;
    s.region[3] = (nk_ushort)r.h;
    return s;
}
NK_API struct nk_image
nk_subimage_id(int id, nk_ushort w, nk_ushort h, struct nk_rect r)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    s.handle.id = id;
    s.w = w; s.h = h;
    s.region[0] = (nk_ushort)r.x;
    s.region[1] = (nk_ushort)r.y;
    s.region[2] = (nk_ushort)r.w;
    s.region[3] = (nk_ushort)r.h;
    return s;
}
NK_API struct nk_image
nk_subimage_handle(nk_handle handle, nk_ushort w, nk_ushort h, struct nk_rect r)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    s.handle = handle;
    s.w = w; s.h = h;
    s.region[0] = (nk_ushort)r.x;
    s.region[1] = (nk_ushort)r.y;
    s.region[2] = (nk_ushort)r.w;
    s.region[3] = (nk_ushort)r.h;
    return s;
}
NK_API struct nk_image
nk_image_handle(nk_handle handle)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    s.handle = handle;
    s.w = 0; s.h = 0;
    s.region[0] = 0;
    s.region[1] = 0;
    s.region[2] = 0;
    s.region[3] = 0;
    return s;
}
NK_API struct nk_image
nk_image_ptr(void *ptr)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    NK_ASSERT(ptr);
    s.handle.ptr = ptr;
    s.w = 0; s.h = 0;
    s.region[0] = 0;
    s.region[1] = 0;
    s.region[2] = 0;
    s.region[3] = 0;
    return s;
}
NK_API struct nk_image
nk_image_id(int id)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    s.handle.id = id;
    s.w = 0; s.h = 0;
    s.region[0] = 0;
    s.region[1] = 0;
    s.region[2] = 0;
    s.region[3] = 0;
    return s;
}
NK_API nk_bool
nk_image_is_subimage(const struct nk_image* img)
{
    NK_ASSERT(img);
    return !(img->w == 0 && img->h == 0);
}
NK_API void
nk_image(struct nk_context *ctx, struct nk_image img)
{
    struct nk_window *win;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return;

    win = ctx->current;
    if (!nk_widget(&bounds, ctx)) return;
    nk_draw_image(&win->buffer, bounds, &img, nk_white);
}
NK_API void
nk_image_color(struct nk_context *ctx, struct nk_image img, struct nk_color col)
{
    struct nk_window *win;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return;

    win = ctx->current;
    if (!nk_widget(&bounds, ctx)) return;
    nk_draw_image(&win->buffer, bounds, &img, col);
}

NK_API struct nk_nine_slice
nk_sub9slice_ptr(void *ptr, nk_ushort w, nk_ushort h, struct nk_rect rgn, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b)
{
    struct nk_nine_slice s;
    struct nk_image *i = &s.img;
    nk_zero(&s, sizeof(s));
    i->handle.ptr = ptr;
    i->w = w; i->h = h;
    i->region[0] = (nk_ushort)rgn.x;
    i->region[1] = (nk_ushort)rgn.y;
    i->region[2] = (nk_ushort)rgn.w;
    i->region[3] = (nk_ushort)rgn.h;
    s.l = l; s.t = t; s.r = r; s.b = b;
    return s;
}
NK_API struct nk_nine_slice
nk_sub9slice_id(int id, nk_ushort w, nk_ushort h, struct nk_rect rgn, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b)
{
    struct nk_nine_slice s;
    struct nk_image *i = &s.img;
    nk_zero(&s, sizeof(s));
    i->handle.id = id;
    i->w = w; i->h = h;
    i->region[0] = (nk_ushort)rgn.x;
    i->region[1] = (nk_ushort)rgn.y;
    i->region[2] = (nk_ushort)rgn.w;
    i->region[3] = (nk_ushort)rgn.h;
    s.l = l; s.t = t; s.r = r; s.b = b;
    return s;
}
NK_API struct nk_nine_slice
nk_sub9slice_handle(nk_handle handle, nk_ushort w, nk_ushort h, struct nk_rect rgn, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b)
{
    struct nk_nine_slice s;
    struct nk_image *i = &s.img;
    nk_zero(&s, sizeof(s));
    i->handle = handle;
    i->w = w; i->h = h;
    i->region[0] = (nk_ushort)rgn.x;
    i->region[1] = (nk_ushort)rgn.y;
    i->region[2] = (nk_ushort)rgn.w;
    i->region[3] = (nk_ushort)rgn.h;
    s.l = l; s.t = t; s.r = r; s.b = b;
    return s;
}
NK_API struct nk_nine_slice
nk_nine_slice_handle(nk_handle handle, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b)
{
    struct nk_nine_slice s;
    struct nk_image *i = &s.img;
    nk_zero(&s, sizeof(s));
    i->handle = handle;
    i->w = 0; i->h = 0;
    i->region[0] = 0;
    i->region[1] = 0;
    i->region[2] = 0;
    i->region[3] = 0;
    s.l = l; s.t = t; s.r = r; s.b = b;
    return s;
}
NK_API struct nk_nine_slice
nk_nine_slice_ptr(void *ptr, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b)
{
    struct nk_nine_slice s;
    struct nk_image *i = &s.img;
    nk_zero(&s, sizeof(s));
    NK_ASSERT(ptr);
    i->handle.ptr = ptr;
    i->w = 0; i->h = 0;
    i->region[0] = 0;
    i->region[1] = 0;
    i->region[2] = 0;
    i->region[3] = 0;
    s.l = l; s.t = t; s.r = r; s.b = b;
    return s;
}
NK_API struct nk_nine_slice
nk_nine_slice_id(int id, nk_ushort l, nk_ushort t, nk_ushort r, nk_ushort b)
{
    struct nk_nine_slice s;
    struct nk_image *i = &s.img;
    nk_zero(&s, sizeof(s));
    i->handle.id = id;
    i->w = 0; i->h = 0;
    i->region[0] = 0;
    i->region[1] = 0;
    i->region[2] = 0;
    i->region[3] = 0;
    s.l = l; s.t = t; s.r = r; s.b = b;
    return s;
}
NK_API int
nk_nine_slice_is_sub9slice(const struct nk_nine_slice* slice)
{
    NK_ASSERT(slice);
    return !(slice->img.w == 0 && slice->img.h == 0);
}

NK_LIB void
nk_draw_symbol(struct nk_command_buffer *out, enum nk_symbol_type type,
    struct nk_rect content, struct nk_color background, struct nk_color foreground,
    float border_width, const struct nk_user_font *font)
{
    switch (type) {
    case NK_SYMBOL_X:
    case NK_SYMBOL_UNDERSCORE:
    case NK_SYMBOL_PLUS:
    case NK_SYMBOL_MINUS: {

        const char *X = (type == NK_SYMBOL_X) ? "x":
            (type == NK_SYMBOL_UNDERSCORE) ? "_":
            (type == NK_SYMBOL_PLUS) ? "+": "-";
        struct nk_text text;
        text.padding = nk_vec2(0,0);
        text.background = background;
        text.text = foreground;
        nk_widget_text(out, content, X, 1, &text, NK_TEXT_CENTERED, font);
    } break;
    case NK_SYMBOL_CIRCLE_SOLID:
    case NK_SYMBOL_CIRCLE_OUTLINE:
    case NK_SYMBOL_RECT_SOLID:
    case NK_SYMBOL_RECT_OUTLINE: {

        if (type == NK_SYMBOL_RECT_SOLID || type == NK_SYMBOL_RECT_OUTLINE) {
            nk_fill_rect(out, content,  0, foreground);
            if (type == NK_SYMBOL_RECT_OUTLINE)
                nk_fill_rect(out, nk_shrink_rect(content, border_width), 0, background);
        } else {
            nk_fill_circle(out, content, foreground);
            if (type == NK_SYMBOL_CIRCLE_OUTLINE)
                nk_fill_circle(out, nk_shrink_rect(content, 1), background);
        }
    } break;
    case NK_SYMBOL_TRIANGLE_UP:
    case NK_SYMBOL_TRIANGLE_DOWN:
    case NK_SYMBOL_TRIANGLE_LEFT:
    case NK_SYMBOL_TRIANGLE_RIGHT: {
        enum nk_heading heading;
        struct nk_vec2 points[3];
        heading = (type == NK_SYMBOL_TRIANGLE_RIGHT) ? NK_RIGHT :
            (type == NK_SYMBOL_TRIANGLE_LEFT) ? NK_LEFT:
            (type == NK_SYMBOL_TRIANGLE_UP) ? NK_UP: NK_DOWN;
        nk_triangle_from_direction(points, content, 0, 0, heading);
        nk_fill_triangle(out, points[0].x, points[0].y, points[1].x, points[1].y,
            points[2].x, points[2].y, foreground);
    } break;
    default:
    case NK_SYMBOL_NONE:
    case NK_SYMBOL_MAX: break;
    }
}
NK_LIB nk_bool
nk_button_behavior(nk_flags *state, struct nk_rect r,
    const struct nk_input *i, enum nk_button_behavior behavior)
{
    int ret = 0;
    nk_widget_state_reset(state);
    if (!i) return 0;
    if (nk_input_is_mouse_hovering_rect(i, r)) {
        *state = NK_WIDGET_STATE_HOVERED;
        if (nk_input_is_mouse_down(i, NK_BUTTON_LEFT))
            *state = NK_WIDGET_STATE_ACTIVE;
        if (nk_input_has_mouse_click_in_button_rect(i, NK_BUTTON_LEFT, r)) {
            ret = (behavior != NK_BUTTON_DEFAULT) ?
                nk_input_is_mouse_down(i, NK_BUTTON_LEFT):
#ifdef NK_BUTTON_TRIGGER_ON_RELEASE
                nk_input_is_mouse_released(i, NK_BUTTON_LEFT);
#else
                nk_input_is_mouse_pressed(i, NK_BUTTON_LEFT);
#endif
        }
    }
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(i, r))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(i, r))
        *state |= NK_WIDGET_STATE_LEFT;
    return ret;
}
NK_LIB const struct nk_style_item*
nk_draw_button(struct nk_command_buffer *out,
    const struct nk_rect *bounds, nk_flags state,
    const struct nk_style_button *style)
{
    const struct nk_style_item *background;
    if (state & NK_WIDGET_STATE_HOVER)
        background = &style->hover;
    else if (state & NK_WIDGET_STATE_ACTIVED)
        background = &style->active;
    else background = &style->normal;

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(out, *bounds, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(out, *bounds, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(out, *bounds, style->rounding, background->data.color);
            nk_stroke_rect(out, *bounds, style->rounding, style->border, style->border_color);
            break;
    }
    return background;
}
NK_LIB nk_bool
nk_do_button(nk_flags *state, struct nk_command_buffer *out, struct nk_rect r,
    const struct nk_style_button *style, const struct nk_input *in,
    enum nk_button_behavior behavior, struct nk_rect *content)
{
    struct nk_rect bounds;
    NK_ASSERT(style);
    NK_ASSERT(state);
    NK_ASSERT(out);
    if (!out || !style)
        return nk_false;

    content->x = r.x + style->padding.x + style->border + style->rounding;
    content->y = r.y + style->padding.y + style->border + style->rounding;
    content->w = r.w - (2 * style->padding.x + style->border + style->rounding*2);
    content->h = r.h - (2 * style->padding.y + style->border + style->rounding*2);

    bounds.x = r.x - style->touch_padding.x;
    bounds.y = r.y - style->touch_padding.y;
    bounds.w = r.w + 2 * style->touch_padding.x;
    bounds.h = r.h + 2 * style->touch_padding.y;
    return nk_button_behavior(state, bounds, in, behavior);
}
NK_LIB void
nk_draw_button_text(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *content, nk_flags state,
    const struct nk_style_button *style, const char *txt, int len,
    nk_flags text_alignment, const struct nk_user_font *font)
{
    struct nk_text text;
    const struct nk_style_item *background;
    background = nk_draw_button(out, bounds, state, style);

    if (background->type == NK_STYLE_ITEM_COLOR)
        text.background = background->data.color;
    else text.background = style->text_background;
    if (state & NK_WIDGET_STATE_HOVER)
        text.text = style->text_hover;
    else if (state & NK_WIDGET_STATE_ACTIVED)
        text.text = style->text_active;
    else text.text = style->text_normal;

    text.padding = nk_vec2(0,0);
    nk_widget_text(out, *content, txt, len, &text, text_alignment, font);
}
NK_LIB nk_bool
nk_do_button_text(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    const char *string, int len, nk_flags align, enum nk_button_behavior behavior,
    const struct nk_style_button *style, const struct nk_input *in,
    const struct nk_user_font *font)
{
    struct nk_rect content;
    int ret = nk_false;

    NK_ASSERT(state);
    NK_ASSERT(style);
    NK_ASSERT(out);
    NK_ASSERT(string);
    NK_ASSERT(font);
    if (!out || !style || !font || !string)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, behavior, &content);
    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_button_text(out, &bounds, &content, *state, style, string, len, align, font);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return ret;
}
NK_LIB void
nk_draw_button_symbol(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *content,
    nk_flags state, const struct nk_style_button *style,
    enum nk_symbol_type type, const struct nk_user_font *font)
{
    struct nk_color sym, bg;
    const struct nk_style_item *background;

    background = nk_draw_button(out, bounds, state, style);
    if (background->type == NK_STYLE_ITEM_COLOR)
        bg = background->data.color;
    else bg = style->text_background;

    if (state & NK_WIDGET_STATE_HOVER)
        sym = style->text_hover;
    else if (state & NK_WIDGET_STATE_ACTIVED)
        sym = style->text_active;
    else sym = style->text_normal;
    nk_draw_symbol(out, type, *content, bg, sym, 1, font);
}
NK_LIB nk_bool
nk_do_button_symbol(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    enum nk_symbol_type symbol, enum nk_button_behavior behavior,
    const struct nk_style_button *style, const struct nk_input *in,
    const struct nk_user_font *font)
{
    int ret;
    struct nk_rect content;

    NK_ASSERT(state);
    NK_ASSERT(style);
    NK_ASSERT(font);
    NK_ASSERT(out);
    if (!out || !style || !font || !state)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, behavior, &content);
    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_button_symbol(out, &bounds, &content, *state, style, symbol, font);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return ret;
}
NK_LIB void
nk_draw_button_image(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *content,
    nk_flags state, const struct nk_style_button *style, const struct nk_image *img)
{
    nk_draw_button(out, bounds, state, style);
    nk_draw_image(out, *content, img, nk_white);
}
NK_LIB nk_bool
nk_do_button_image(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    struct nk_image img, enum nk_button_behavior b,
    const struct nk_style_button *style, const struct nk_input *in)
{
    int ret;
    struct nk_rect content;

    NK_ASSERT(state);
    NK_ASSERT(style);
    NK_ASSERT(out);
    if (!out || !style || !state)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, b, &content);
    content.x += style->image_padding.x;
    content.y += style->image_padding.y;
    content.w -= 2 * style->image_padding.x;
    content.h -= 2 * style->image_padding.y;

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_button_image(out, &bounds, &content, *state, style, &img);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return ret;
}
NK_LIB void
nk_draw_button_text_symbol(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *label,
    const struct nk_rect *symbol, nk_flags state, const struct nk_style_button *style,
    const char *str, int len, enum nk_symbol_type type,
    const struct nk_user_font *font)
{
    struct nk_color sym;
    struct nk_text text;
    const struct nk_style_item *background;

    background = nk_draw_button(out, bounds, state, style);
    if (background->type == NK_STYLE_ITEM_COLOR)
        text.background = background->data.color;
    else text.background = style->text_background;

    if (state & NK_WIDGET_STATE_HOVER) {
        sym = style->text_hover;
        text.text = style->text_hover;
    } else if (state & NK_WIDGET_STATE_ACTIVED) {
        sym = style->text_active;
        text.text = style->text_active;
    } else {
        sym = style->text_normal;
        text.text = style->text_normal;
    }

    text.padding = nk_vec2(0,0);
    nk_draw_symbol(out, type, *symbol, style->text_background, sym, 0, font);
    nk_widget_text(out, *label, str, len, &text, NK_TEXT_CENTERED, font);
}
NK_LIB nk_bool
nk_do_button_text_symbol(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    enum nk_symbol_type symbol, const char *str, int len, nk_flags align,
    enum nk_button_behavior behavior, const struct nk_style_button *style,
    const struct nk_user_font *font, const struct nk_input *in)
{
    int ret;
    struct nk_rect tri = {0,0,0,0};
    struct nk_rect content;

    NK_ASSERT(style);
    NK_ASSERT(out);
    NK_ASSERT(font);
    if (!out || !style || !font)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, behavior, &content);
    tri.y = content.y + (content.h/2) - font->height/2;
    tri.w = font->height; tri.h = font->height;
    if (align & NK_TEXT_ALIGN_LEFT) {
        tri.x = (content.x + content.w) - (2 * style->padding.x + tri.w);
        tri.x = NK_MAX(tri.x, 0);
    } else tri.x = content.x + 2 * style->padding.x;

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_button_text_symbol(out, &bounds, &content, &tri,
        *state, style, str, len, symbol, font);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return ret;
}
NK_LIB void
nk_draw_button_text_image(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *label,
    const struct nk_rect *image, nk_flags state, const struct nk_style_button *style,
    const char *str, int len, const struct nk_user_font *font,
    const struct nk_image *img)
{
    struct nk_text text;
    const struct nk_style_item *background;
    background = nk_draw_button(out, bounds, state, style);

    if (background->type == NK_STYLE_ITEM_COLOR)
        text.background = background->data.color;
    else text.background = style->text_background;
    if (state & NK_WIDGET_STATE_HOVER)
        text.text = style->text_hover;
    else if (state & NK_WIDGET_STATE_ACTIVED)
        text.text = style->text_active;
    else text.text = style->text_normal;

    text.padding = nk_vec2(0,0);
    nk_widget_text(out, *label, str, len, &text, NK_TEXT_CENTERED, font);
    nk_draw_image(out, *image, img, nk_white);
}
NK_LIB nk_bool
nk_do_button_text_image(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    struct nk_image img, const char* str, int len, nk_flags align,
    enum nk_button_behavior behavior, const struct nk_style_button *style,
    const struct nk_user_font *font, const struct nk_input *in)
{
    int ret;
    struct nk_rect icon;
    struct nk_rect content;

    NK_ASSERT(style);
    NK_ASSERT(state);
    NK_ASSERT(font);
    NK_ASSERT(out);
    if (!out || !font || !style || !str)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, behavior, &content);
    icon.y = bounds.y + style->padding.y;
    icon.w = icon.h = bounds.h - 2 * style->padding.y;
    if (align & NK_TEXT_ALIGN_LEFT) {
        icon.x = (bounds.x + bounds.w) - (2 * style->padding.x + icon.w);
        icon.x = NK_MAX(icon.x, 0);
    } else icon.x = bounds.x + 2 * style->padding.x;

    icon.x += style->image_padding.x;
    icon.y += style->image_padding.y;
    icon.w -= 2 * style->image_padding.x;
    icon.h -= 2 * style->image_padding.y;

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_button_text_image(out, &bounds, &content, &icon, *state, style, str, len, font, &img);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return ret;
}
NK_API void
nk_button_set_behavior(struct nk_context *ctx, enum nk_button_behavior behavior)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    ctx->button_behavior = behavior;
}
NK_API nk_bool
nk_button_push_behavior(struct nk_context *ctx, enum nk_button_behavior behavior)
{
    struct nk_config_stack_button_behavior *button_stack;
    struct nk_config_stack_button_behavior_element *element;

    NK_ASSERT(ctx);
    if (!ctx) return 0;

    button_stack = &ctx->stacks.button_behaviors;
    NK_ASSERT(button_stack->head < (int)NK_LEN(button_stack->elements));
    if (button_stack->head >= (int)NK_LEN(button_stack->elements))
        return 0;

    element = &button_stack->elements[button_stack->head++];
    element->address = &ctx->button_behavior;
    element->old_value = ctx->button_behavior;
    ctx->button_behavior = behavior;
    return 1;
}
NK_API nk_bool
nk_button_pop_behavior(struct nk_context *ctx)
{
    struct nk_config_stack_button_behavior *button_stack;
    struct nk_config_stack_button_behavior_element *element;

    NK_ASSERT(ctx);
    if (!ctx) return 0;

    button_stack = &ctx->stacks.button_behaviors;
    NK_ASSERT(button_stack->head > 0);
    if (button_stack->head < 1)
        return 0;

    element = &button_stack->elements[--button_stack->head];
    *element->address = element->old_value;
    return 1;
}
NK_API nk_bool
nk_button_text_styled(struct nk_context *ctx,
    const struct nk_style_button *style, const char *title, int len)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(style);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!style || !ctx || !ctx->current || !ctx->current->layout) return 0;

    win = ctx->current;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);

    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_text(&ctx->last_widget_state, &win->buffer, bounds,
                    title, len, style->text_alignment, ctx->button_behavior,
                    style, in, ctx->style.font);
}
NK_API nk_bool
nk_button_text(struct nk_context *ctx, const char *title, int len)
{
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    return nk_button_text_styled(ctx, &ctx->style.button, title, len);
}
NK_API nk_bool nk_button_label_styled(struct nk_context *ctx,
    const struct nk_style_button *style, const char *title)
{
    return nk_button_text_styled(ctx, style, title, nk_strlen(title));
}
NK_API nk_bool nk_button_label(struct nk_context *ctx, const char *title)
{
    return nk_button_text(ctx, title, nk_strlen(title));
}
NK_API nk_bool
nk_button_color(struct nk_context *ctx, struct nk_color color)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    struct nk_style_button button;

    int ret = 0;
    struct nk_rect bounds;
    struct nk_rect content;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;

    button = ctx->style.button;
    button.normal = nk_style_item_color(color);
    button.hover = nk_style_item_color(color);
    button.active = nk_style_item_color(color);
    ret = nk_do_button(&ctx->last_widget_state, &win->buffer, bounds,
                &button, in, ctx->button_behavior, &content);
    nk_draw_button(&win->buffer, &bounds, ctx->last_widget_state, &button);
    return ret;
}
NK_API nk_bool
nk_button_symbol_styled(struct nk_context *ctx,
    const struct nk_style_button *style, enum nk_symbol_type symbol)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_symbol(&ctx->last_widget_state, &win->buffer, bounds,
            symbol, ctx->button_behavior, style, in, ctx->style.font);
}
NK_API nk_bool
nk_button_symbol(struct nk_context *ctx, enum nk_symbol_type symbol)
{
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    return nk_button_symbol_styled(ctx, &ctx->style.button, symbol);
}
NK_API nk_bool
nk_button_image_styled(struct nk_context *ctx, const struct nk_style_button *style,
    struct nk_image img)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_image(&ctx->last_widget_state, &win->buffer, bounds,
                img, ctx->button_behavior, style, in);
}
NK_API nk_bool
nk_button_image(struct nk_context *ctx, struct nk_image img)
{
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    return nk_button_image_styled(ctx, &ctx->style.button, img);
}
NK_API nk_bool
nk_button_symbol_text_styled(struct nk_context *ctx,
    const struct nk_style_button *style, enum nk_symbol_type symbol,
    const char *text, int len, nk_flags align)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_text_symbol(&ctx->last_widget_state, &win->buffer, bounds,
                symbol, text, len, align, ctx->button_behavior,
                style, ctx->style.font, in);
}
NK_API nk_bool
nk_button_symbol_text(struct nk_context *ctx, enum nk_symbol_type symbol,
    const char* text, int len, nk_flags align)
{
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    return nk_button_symbol_text_styled(ctx, &ctx->style.button, symbol, text, len, align);
}
NK_API nk_bool nk_button_symbol_label(struct nk_context *ctx, enum nk_symbol_type symbol,
    const char *label, nk_flags align)
{
    return nk_button_symbol_text(ctx, symbol, label, nk_strlen(label), align);
}
NK_API nk_bool nk_button_symbol_label_styled(struct nk_context *ctx,
    const struct nk_style_button *style, enum nk_symbol_type symbol,
    const char *title, nk_flags align)
{
    return nk_button_symbol_text_styled(ctx, style, symbol, title, nk_strlen(title), align);
}
NK_API nk_bool
nk_button_image_text_styled(struct nk_context *ctx,
    const struct nk_style_button *style, struct nk_image img, const char *text,
    int len, nk_flags align)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_text_image(&ctx->last_widget_state, &win->buffer,
            bounds, img, text, len, align, ctx->button_behavior,
            style, ctx->style.font, in);
}
NK_API nk_bool
nk_button_image_text(struct nk_context *ctx, struct nk_image img,
    const char *text, int len, nk_flags align)
{
    return nk_button_image_text_styled(ctx, &ctx->style.button,img, text, len, align);
}
NK_API nk_bool nk_button_image_label(struct nk_context *ctx, struct nk_image img,
    const char *label, nk_flags align)
{
    return nk_button_image_text(ctx, img, label, nk_strlen(label), align);
}
NK_API nk_bool nk_button_image_label_styled(struct nk_context *ctx,
    const struct nk_style_button *style, struct nk_image img,
    const char *label, nk_flags text_alignment)
{
    return nk_button_image_text_styled(ctx, style, img, label, nk_strlen(label), text_alignment);
}

NK_LIB nk_bool
nk_toggle_behavior(const struct nk_input *in, struct nk_rect select,
    nk_flags *state, nk_bool active)
{
    nk_widget_state_reset(state);
    if (nk_button_behavior(state, select, in, NK_BUTTON_DEFAULT)) {
        *state = NK_WIDGET_STATE_ACTIVE;
        active = !active;
    }
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, select))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, select))
        *state |= NK_WIDGET_STATE_LEFT;
    return active;
}
NK_LIB void
nk_draw_checkbox(struct nk_command_buffer *out,
    nk_flags state, const struct nk_style_toggle *style, nk_bool active,
    const struct nk_rect *label, const struct nk_rect *selector,
    const struct nk_rect *cursors, const char *string, int len,
    const struct nk_user_font *font)
{
    const struct nk_style_item *background;
    const struct nk_style_item *cursor;
    struct nk_text text;

    if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        cursor = &style->cursor_hover;
        text.text = style->text_hover;
    } else if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->hover;
        cursor = &style->cursor_hover;
        text.text = style->text_active;
    } else {
        background = &style->normal;
        cursor = &style->cursor_normal;
        text.text = style->text_normal;
    }

    if (background->type == NK_STYLE_ITEM_COLOR) {
        nk_fill_rect(out, *selector, 0, style->border_color);
        nk_fill_rect(out, nk_shrink_rect(*selector, style->border), 0, background->data.color);
    } else nk_draw_image(out, *selector, &background->data.image, nk_white);
    if (active) {
        if (cursor->type == NK_STYLE_ITEM_IMAGE)
            nk_draw_image(out, *cursors, &cursor->data.image, nk_white);
        else nk_fill_rect(out, *cursors, 0, cursor->data.color);
    }

    text.padding.x = 0;
    text.padding.y = 0;
    text.background = style->text_background;
    nk_widget_text(out, *label, string, len, &text, NK_TEXT_LEFT, font);
}
NK_LIB void
nk_draw_option(struct nk_command_buffer *out,
    nk_flags state, const struct nk_style_toggle *style, nk_bool active,
    const struct nk_rect *label, const struct nk_rect *selector,
    const struct nk_rect *cursors, const char *string, int len,
    const struct nk_user_font *font)
{
    const struct nk_style_item *background;
    const struct nk_style_item *cursor;
    struct nk_text text;

    if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        cursor = &style->cursor_hover;
        text.text = style->text_hover;
    } else if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->hover;
        cursor = &style->cursor_hover;
        text.text = style->text_active;
    } else {
        background = &style->normal;
        cursor = &style->cursor_normal;
        text.text = style->text_normal;
    }

    if (background->type == NK_STYLE_ITEM_COLOR) {
        nk_fill_circle(out, *selector, style->border_color);
        nk_fill_circle(out, nk_shrink_rect(*selector, style->border), background->data.color);
    } else nk_draw_image(out, *selector, &background->data.image, nk_white);
    if (active) {
        if (cursor->type == NK_STYLE_ITEM_IMAGE)
            nk_draw_image(out, *cursors, &cursor->data.image, nk_white);
        else nk_fill_circle(out, *cursors, cursor->data.color);
    }

    text.padding.x = 0;
    text.padding.y = 0;
    text.background = style->text_background;
    nk_widget_text(out, *label, string, len, &text, NK_TEXT_LEFT, font);
}
NK_LIB nk_bool
nk_do_toggle(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect r,
    nk_bool *active, const char *str, int len, enum nk_toggle_type type,
    const struct nk_style_toggle *style, const struct nk_input *in,
    const struct nk_user_font *font)
{
    int was_active;
    struct nk_rect bounds;
    struct nk_rect select;
    struct nk_rect cursor;
    struct nk_rect label;

    NK_ASSERT(style);
    NK_ASSERT(out);
    NK_ASSERT(font);
    if (!out || !style || !font || !active)
        return 0;

    r.w = NK_MAX(r.w, font->height + 2 * style->padding.x);
    r.h = NK_MAX(r.h, font->height + 2 * style->padding.y);

    bounds.x = r.x - style->touch_padding.x;
    bounds.y = r.y - style->touch_padding.y;
    bounds.w = r.w + 2 * style->touch_padding.x;
    bounds.h = r.h + 2 * style->touch_padding.y;

    select.w = font->height;
    select.h = select.w;
    select.y = r.y + r.h/2.0f - select.h/2.0f;
    select.x = r.x;

    cursor.x = select.x + style->padding.x + style->border;
    cursor.y = select.y + style->padding.y + style->border;
    cursor.w = select.w - (2 * style->padding.x + 2 * style->border);
    cursor.h = select.h - (2 * style->padding.y + 2 * style->border);

    label.x = select.x + select.w + style->spacing;
    label.y = select.y;
    label.w = NK_MAX(r.x + r.w, label.x) - label.x;
    label.h = select.w;

    was_active = *active;
    *active = nk_toggle_behavior(in, bounds, state, *active);

    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (type == NK_TOGGLE_CHECK) {
        nk_draw_checkbox(out, *state, style, *active, &label, &select, &cursor, str, len, font);
    } else {
        nk_draw_option(out, *state, style, *active, &label, &select, &cursor, str, len, font);
    }
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return (was_active != *active);
}

NK_API nk_bool
nk_check_text(struct nk_context *ctx, const char *text, int len, nk_bool active)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return active;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return active;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    nk_do_toggle(&ctx->last_widget_state, &win->buffer, bounds, &active,
        text, len, NK_TOGGLE_CHECK, &style->checkbox, in, style->font);
    return active;
}
NK_API unsigned int
nk_check_flags_text(struct nk_context *ctx, const char *text, int len,
    unsigned int flags, unsigned int value)
{
    int old_active;
    NK_ASSERT(ctx);
    NK_ASSERT(text);
    if (!ctx || !text) return flags;
    old_active = (int)((flags & value) & value);
    if (nk_check_text(ctx, text, len, old_active))
        flags |= value;
    else flags &= ~value;
    return flags;
}
NK_API nk_bool
nk_checkbox_text(struct nk_context *ctx, const char *text, int len, nk_bool *active)
{
    int old_val;
    NK_ASSERT(ctx);
    NK_ASSERT(text);
    NK_ASSERT(active);
    if (!ctx || !text || !active) return 0;
    old_val = *active;
    *active = nk_check_text(ctx, text, len, *active);
    return old_val != *active;
}
NK_API nk_bool
nk_checkbox_flags_text(struct nk_context *ctx, const char *text, int len,
    unsigned int *flags, unsigned int value)
{
    nk_bool active;
    NK_ASSERT(ctx);
    NK_ASSERT(text);
    NK_ASSERT(flags);
    if (!ctx || !text || !flags) return 0;

    active = (int)((*flags & value) & value);
    if (nk_checkbox_text(ctx, text, len, &active)) {
        if (active) *flags |= value;
        else *flags &= ~value;
        return 1;
    }
    return 0;
}
NK_API nk_bool nk_check_label(struct nk_context *ctx, const char *label, nk_bool active)
{
    return nk_check_text(ctx, label, nk_strlen(label), active);
}
NK_API unsigned int nk_check_flags_label(struct nk_context *ctx, const char *label,
    unsigned int flags, unsigned int value)
{
    return nk_check_flags_text(ctx, label, nk_strlen(label), flags, value);
}
NK_API nk_bool nk_checkbox_label(struct nk_context *ctx, const char *label, nk_bool *active)
{
    return nk_checkbox_text(ctx, label, nk_strlen(label), active);
}
NK_API nk_bool nk_checkbox_flags_label(struct nk_context *ctx, const char *label,
    unsigned int *flags, unsigned int value)
{
    return nk_checkbox_flags_text(ctx, label, nk_strlen(label), flags, value);
}

NK_API nk_bool
nk_option_text(struct nk_context *ctx, const char *text, int len, nk_bool is_active)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return is_active;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return (int)state;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    nk_do_toggle(&ctx->last_widget_state, &win->buffer, bounds, &is_active,
        text, len, NK_TOGGLE_OPTION, &style->option, in, style->font);
    return is_active;
}
NK_API nk_bool
nk_radio_text(struct nk_context *ctx, const char *text, int len, nk_bool *active)
{
    int old_value;
    NK_ASSERT(ctx);
    NK_ASSERT(text);
    NK_ASSERT(active);
    if (!ctx || !text || !active) return 0;
    old_value = *active;
    *active = nk_option_text(ctx, text, len, old_value);
    return old_value != *active;
}
NK_API nk_bool
nk_option_label(struct nk_context *ctx, const char *label, nk_bool active)
{
    return nk_option_text(ctx, label, nk_strlen(label), active);
}
NK_API nk_bool
nk_radio_label(struct nk_context *ctx, const char *label, nk_bool *active)
{
    return nk_radio_text(ctx, label, nk_strlen(label), active);
}

NK_LIB void
nk_draw_selectable(struct nk_command_buffer *out,
    nk_flags state, const struct nk_style_selectable *style, nk_bool active,
    const struct nk_rect *bounds,
    const struct nk_rect *icon, const struct nk_image *img, enum nk_symbol_type sym,
    const char *string, int len, nk_flags align, const struct nk_user_font *font)
{
    const struct nk_style_item *background;
    struct nk_text text;
    text.padding = style->padding;

    if (!active) {
        if (state & NK_WIDGET_STATE_ACTIVED) {
            background = &style->pressed;
            text.text = style->text_pressed;
        } else if (state & NK_WIDGET_STATE_HOVER) {
            background = &style->hover;
            text.text = style->text_hover;
        } else {
            background = &style->normal;
            text.text = style->text_normal;
        }
    } else {
        if (state & NK_WIDGET_STATE_ACTIVED) {
            background = &style->pressed_active;
            text.text = style->text_pressed_active;
        } else if (state & NK_WIDGET_STATE_HOVER) {
            background = &style->hover_active;
            text.text = style->text_hover_active;
        } else {
            background = &style->normal_active;
            text.text = style->text_normal_active;
        }
    }

    switch (background->type) {
        case NK_STYLE_ITEM_IMAGE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_image(out, *bounds, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_nine_slice(out, *bounds, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            text.background = background->data.color;
            nk_fill_rect(out, *bounds, style->rounding, background->data.color);
            break;
    }
    if (icon) {
        if (img) nk_draw_image(out, *icon, img, nk_white);
        else nk_draw_symbol(out, sym, *icon, text.background, text.text, 1, font);
    }
    nk_widget_text(out, *bounds, string, len, &text, align, font);
}
NK_LIB nk_bool
nk_do_selectable(nk_flags *state, struct nk_command_buffer *out,
    struct nk_rect bounds, const char *str, int len, nk_flags align, nk_bool *value,
    const struct nk_style_selectable *style, const struct nk_input *in,
    const struct nk_user_font *font)
{
    int old_value;
    struct nk_rect touch;

    NK_ASSERT(state);
    NK_ASSERT(out);
    NK_ASSERT(str);
    NK_ASSERT(len);
    NK_ASSERT(value);
    NK_ASSERT(style);
    NK_ASSERT(font);

    if (!state || !out || !str || !len || !value || !style || !font) return 0;
    old_value = *value;

    touch.x = bounds.x - style->touch_padding.x;
    touch.y = bounds.y - style->touch_padding.y;
    touch.w = bounds.w + style->touch_padding.x * 2;
    touch.h = bounds.h + style->touch_padding.y * 2;

    if (nk_button_behavior(state, touch, in, NK_BUTTON_DEFAULT))
        *value = !(*value);

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_selectable(out, *state, style, *value, &bounds, 0,0,NK_SYMBOL_NONE, str, len, align, font);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return old_value != *value;
}
NK_LIB nk_bool
nk_do_selectable_image(nk_flags *state, struct nk_command_buffer *out,
    struct nk_rect bounds, const char *str, int len, nk_flags align, nk_bool *value,
    const struct nk_image *img, const struct nk_style_selectable *style,
    const struct nk_input *in, const struct nk_user_font *font)
{
    nk_bool old_value;
    struct nk_rect touch;
    struct nk_rect icon;

    NK_ASSERT(state);
    NK_ASSERT(out);
    NK_ASSERT(str);
    NK_ASSERT(len);
    NK_ASSERT(value);
    NK_ASSERT(style);
    NK_ASSERT(font);

    if (!state || !out || !str || !len || !value || !style || !font) return 0;
    old_value = *value;

    touch.x = bounds.x - style->touch_padding.x;
    touch.y = bounds.y - style->touch_padding.y;
    touch.w = bounds.w + style->touch_padding.x * 2;
    touch.h = bounds.h + style->touch_padding.y * 2;
    if (nk_button_behavior(state, touch, in, NK_BUTTON_DEFAULT))
        *value = !(*value);

    icon.y = bounds.y + style->padding.y;
    icon.w = icon.h = bounds.h - 2 * style->padding.y;
    if (align & NK_TEXT_ALIGN_LEFT) {
        icon.x = (bounds.x + bounds.w) - (2 * style->padding.x + icon.w);
        icon.x = NK_MAX(icon.x, 0);
    } else icon.x = bounds.x + 2 * style->padding.x;

    icon.x += style->image_padding.x;
    icon.y += style->image_padding.y;
    icon.w -= 2 * style->image_padding.x;
    icon.h -= 2 * style->image_padding.y;

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_selectable(out, *state, style, *value, &bounds, &icon, img, NK_SYMBOL_NONE, str, len, align, font);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return old_value != *value;
}
NK_LIB nk_bool
nk_do_selectable_symbol(nk_flags *state, struct nk_command_buffer *out,
    struct nk_rect bounds, const char *str, int len, nk_flags align, nk_bool *value,
    enum nk_symbol_type sym, const struct nk_style_selectable *style,
    const struct nk_input *in, const struct nk_user_font *font)
{
    int old_value;
    struct nk_rect touch;
    struct nk_rect icon;

    NK_ASSERT(state);
    NK_ASSERT(out);
    NK_ASSERT(str);
    NK_ASSERT(len);
    NK_ASSERT(value);
    NK_ASSERT(style);
    NK_ASSERT(font);

    if (!state || !out || !str || !len || !value || !style || !font) return 0;
    old_value = *value;

    touch.x = bounds.x - style->touch_padding.x;
    touch.y = bounds.y - style->touch_padding.y;
    touch.w = bounds.w + style->touch_padding.x * 2;
    touch.h = bounds.h + style->touch_padding.y * 2;
    if (nk_button_behavior(state, touch, in, NK_BUTTON_DEFAULT))
        *value = !(*value);

    icon.y = bounds.y + style->padding.y;
    icon.w = icon.h = bounds.h - 2 * style->padding.y;
    if (align & NK_TEXT_ALIGN_LEFT) {
        icon.x = (bounds.x + bounds.w) - (2 * style->padding.x + icon.w);
        icon.x = NK_MAX(icon.x, 0);
    } else icon.x = bounds.x + 2 * style->padding.x;

    icon.x += style->image_padding.x;
    icon.y += style->image_padding.y;
    icon.w -= 2 * style->image_padding.x;
    icon.h -= 2 * style->image_padding.y;

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_selectable(out, *state, style, *value, &bounds, &icon, 0, sym, str, len, align, font);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return old_value != *value;
}

NK_API nk_bool
nk_selectable_text(struct nk_context *ctx, const char *str, int len,
    nk_flags align, nk_bool *value)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    enum nk_widget_layout_states state;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(value);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !value)
        return 0;

    win = ctx->current;
    layout = win->layout;
    style = &ctx->style;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_selectable(&ctx->last_widget_state, &win->buffer, bounds,
                str, len, align, value, &style->selectable, in, style->font);
}
NK_API nk_bool
nk_selectable_image_text(struct nk_context *ctx, struct nk_image img,
    const char *str, int len, nk_flags align, nk_bool *value)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    enum nk_widget_layout_states state;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(value);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !value)
        return 0;

    win = ctx->current;
    layout = win->layout;
    style = &ctx->style;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_selectable_image(&ctx->last_widget_state, &win->buffer, bounds,
                str, len, align, value, &img, &style->selectable, in, style->font);
}
NK_API nk_bool
nk_selectable_symbol_text(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *str, int len, nk_flags align, nk_bool *value)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    enum nk_widget_layout_states state;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(value);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !value)
        return 0;

    win = ctx->current;
    layout = win->layout;
    style = &ctx->style;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_selectable_symbol(&ctx->last_widget_state, &win->buffer, bounds,
                str, len, align, value, sym, &style->selectable, in, style->font);
}
NK_API nk_bool
nk_selectable_symbol_label(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *title, nk_flags align, nk_bool *value)
{
    return nk_selectable_symbol_text(ctx, sym, title, nk_strlen(title), align, value);
}
NK_API nk_bool nk_select_text(struct nk_context *ctx, const char *str, int len,
    nk_flags align, nk_bool value)
{
    nk_selectable_text(ctx, str, len, align, &value);return value;
}
NK_API nk_bool nk_selectable_label(struct nk_context *ctx, const char *str, nk_flags align, nk_bool *value)
{
    return nk_selectable_text(ctx, str, nk_strlen(str), align, value);
}
NK_API nk_bool nk_selectable_image_label(struct nk_context *ctx,struct nk_image img,
    const char *str, nk_flags align, nk_bool *value)
{
    return nk_selectable_image_text(ctx, img, str, nk_strlen(str), align, value);
}
NK_API nk_bool nk_select_label(struct nk_context *ctx, const char *str, nk_flags align, nk_bool value)
{
    nk_selectable_text(ctx, str, nk_strlen(str), align, &value);return value;
}
NK_API nk_bool nk_select_image_label(struct nk_context *ctx, struct nk_image img,
    const char *str, nk_flags align, nk_bool value)
{
    nk_selectable_image_text(ctx, img, str, nk_strlen(str), align, &value);return value;
}
NK_API nk_bool nk_select_image_text(struct nk_context *ctx, struct nk_image img,
    const char *str, int len, nk_flags align, nk_bool value)
{
    nk_selectable_image_text(ctx, img, str, len, align, &value);return value;
}
NK_API nk_bool
nk_select_symbol_text(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *title, int title_len, nk_flags align, nk_bool value)
{
    nk_selectable_symbol_text(ctx, sym, title, title_len, align, &value);return value;
}
NK_API nk_bool
nk_select_symbol_label(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *title, nk_flags align, nk_bool value)
{
    return nk_select_symbol_text(ctx, sym, title, nk_strlen(title), align, value);
}

NK_LIB float
nk_slider_behavior(nk_flags *state, struct nk_rect *logical_cursor,
    struct nk_rect *visual_cursor, struct nk_input *in,
    struct nk_rect bounds, float slider_min, float slider_max, float slider_value,
    float slider_step, float slider_steps)
{
    int left_mouse_down;
    int left_mouse_click_in_cursor;

    nk_widget_state_reset(state);
    left_mouse_down = in && in->mouse.buttons[NK_BUTTON_LEFT].down;
    left_mouse_click_in_cursor = in && nk_input_has_mouse_click_down_in_rect(in,
            NK_BUTTON_LEFT, *visual_cursor, nk_true);

    if (left_mouse_down && left_mouse_click_in_cursor) {
        float ratio = 0;
        const float d = in->mouse.pos.x - (visual_cursor->x+visual_cursor->w*0.5f);
        const float pxstep = bounds.w / slider_steps;

        *state = NK_WIDGET_STATE_ACTIVE;
        if (NK_ABS(d) >= pxstep) {
            const float steps = (float)((int)(NK_ABS(d) / pxstep));
            slider_value += (d > 0) ? (slider_step*steps) : -(slider_step*steps);
            slider_value = NK_CLAMP(slider_min, slider_value, slider_max);
            ratio = (slider_value - slider_min)/slider_step;
            logical_cursor->x = bounds.x + (logical_cursor->w * ratio);
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.x = logical_cursor->x;
        }
    }

    if (nk_input_is_mouse_hovering_rect(in, bounds))
        *state = NK_WIDGET_STATE_HOVERED;
    if (*state & NK_WIDGET_STATE_HOVER &&
        !nk_input_is_mouse_prev_hovering_rect(in, bounds))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, bounds))
        *state |= NK_WIDGET_STATE_LEFT;
    return slider_value;
}
NK_LIB void
nk_draw_slider(struct nk_command_buffer *out, nk_flags state,
    const struct nk_style_slider *style, const struct nk_rect *bounds,
    const struct nk_rect *visual_cursor, float min, float value, float max)
{
    struct nk_rect fill;
    struct nk_rect bar;
    const struct nk_style_item *background;

    struct nk_color bar_color;
    const struct nk_style_item *cursor;

    NK_UNUSED(min);
    NK_UNUSED(max);
    NK_UNUSED(value);

    if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->active;
        bar_color = style->bar_active;
        cursor = &style->cursor_active;
    } else if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        bar_color = style->bar_hover;
        cursor = &style->cursor_hover;
    } else {
        background = &style->normal;
        bar_color = style->bar_normal;
        cursor = &style->cursor_normal;
    }

    bar.x = bounds->x;
    bar.y = (visual_cursor->y + visual_cursor->h/2) - bounds->h/12;
    bar.w = bounds->w;
    bar.h = bounds->h/6;

    fill.w = (visual_cursor->x + (visual_cursor->w/2.0f)) - bar.x;
    fill.x = bar.x;
    fill.y = bar.y;
    fill.h = bar.h;

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(out, *bounds, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(out, *bounds, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(out, *bounds, style->rounding, background->data.color);
            nk_stroke_rect(out, *bounds, style->rounding, style->border, style->border_color);
            break;
    }

    nk_fill_rect(out, bar, style->rounding, bar_color);
    nk_fill_rect(out, fill, style->rounding, style->bar_filled);

    if (cursor->type == NK_STYLE_ITEM_IMAGE)
        nk_draw_image(out, *visual_cursor, &cursor->data.image, nk_white);
    else
        nk_fill_circle(out, *visual_cursor, cursor->data.color);
}
NK_LIB float
nk_do_slider(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    float min, float val, float max, float step,
    const struct nk_style_slider *style, struct nk_input *in,
    const struct nk_user_font *font)
{
    float slider_range;
    float slider_min;
    float slider_max;
    float slider_value;
    float slider_steps;
    float cursor_offset;

    struct nk_rect visual_cursor;
    struct nk_rect logical_cursor;

    NK_ASSERT(style);
    NK_ASSERT(out);
    if (!out || !style)
        return 0;

    bounds.x = bounds.x + style->padding.x;
    bounds.y = bounds.y + style->padding.y;
    bounds.h = NK_MAX(bounds.h, 2*style->padding.y);
    bounds.w = NK_MAX(bounds.w, 2*style->padding.x + style->cursor_size.x);
    bounds.w -= 2 * style->padding.x;
    bounds.h -= 2 * style->padding.y;

    if (style->show_buttons) {
        nk_flags ws;
        struct nk_rect button;
        button.y = bounds.y;
        button.w = bounds.h;
        button.h = bounds.h;

        button.x = bounds.x;
        if (nk_do_button_symbol(&ws, out, button, style->dec_symbol, NK_BUTTON_DEFAULT,
            &style->dec_button, in, font))
            val -= step;

        button.x = (bounds.x + bounds.w) - button.w;
        if (nk_do_button_symbol(&ws, out, button, style->inc_symbol, NK_BUTTON_DEFAULT,
            &style->inc_button, in, font))
            val += step;

        bounds.x = bounds.x + button.w + style->spacing.x;
        bounds.w = bounds.w - (2*button.w + 2*style->spacing.x);
    }

    bounds.x += style->cursor_size.x*0.5f;
    bounds.w -= style->cursor_size.x;

    slider_max = NK_MAX(min, max);
    slider_min = NK_MIN(min, max);
    slider_value = NK_CLAMP(slider_min, val, slider_max);
    slider_range = slider_max - slider_min;
    slider_steps = slider_range / step;
    cursor_offset = (slider_value - slider_min) / step;

    logical_cursor.h = bounds.h;
    logical_cursor.w = bounds.w / slider_steps;
    logical_cursor.x = bounds.x + (logical_cursor.w * cursor_offset);
    logical_cursor.y = bounds.y;

    visual_cursor.h = style->cursor_size.y;
    visual_cursor.w = style->cursor_size.x;
    visual_cursor.y = (bounds.y + bounds.h*0.5f) - visual_cursor.h*0.5f;
    visual_cursor.x = logical_cursor.x - visual_cursor.w*0.5f;

    slider_value = nk_slider_behavior(state, &logical_cursor, &visual_cursor,
        in, bounds, slider_min, slider_max, slider_value, step, slider_steps);
    visual_cursor.x = logical_cursor.x - visual_cursor.w*0.5f;

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_slider(out, *state, style, &bounds, &visual_cursor, slider_min, slider_value, slider_max);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return slider_value;
}
NK_API nk_bool
nk_slider_float(struct nk_context *ctx, float min_value, float *value, float max_value,
    float value_step)
{
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_input *in;
    const struct nk_style *style;

    int ret = 0;
    float old_value;
    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    NK_ASSERT(value);
    if (!ctx || !ctx->current || !ctx->current->layout || !value)
        return ret;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return ret;
    in = (  layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;

    old_value = *value;
    *value = nk_do_slider(&ctx->last_widget_state, &win->buffer, bounds, min_value,
                old_value, max_value, value_step, &style->slider, in, style->font);
    return (old_value > *value || old_value < *value);
}
NK_API float
nk_slide_float(struct nk_context *ctx, float min, float val, float max, float step)
{
    nk_slider_float(ctx, min, &val, max, step); return val;
}
NK_API int
nk_slide_int(struct nk_context *ctx, int min, int val, int max, int step)
{
    float value = (float)val;
    nk_slider_float(ctx, (float)min, &value, (float)max, (float)step);
    return (int)value;
}
NK_API nk_bool
nk_slider_int(struct nk_context *ctx, int min, int *val, int max, int step)
{
    int ret;
    float value = (float)*val;
    ret = nk_slider_float(ctx, (float)min, &value, (float)max, (float)step);
    *val =  (int)value;
    return ret;
}

NK_LIB nk_size
nk_progress_behavior(nk_flags *state, struct nk_input *in,
    struct nk_rect r, struct nk_rect cursor, nk_size max, nk_size value, nk_bool modifiable)
{
    int left_mouse_down = 0;
    int left_mouse_click_in_cursor = 0;

    nk_widget_state_reset(state);
    if (!in || !modifiable) return value;
    left_mouse_down = in && in->mouse.buttons[NK_BUTTON_LEFT].down;
    left_mouse_click_in_cursor = in && nk_input_has_mouse_click_down_in_rect(in,
            NK_BUTTON_LEFT, cursor, nk_true);
    if (nk_input_is_mouse_hovering_rect(in, r))
        *state = NK_WIDGET_STATE_HOVERED;

    if (in && left_mouse_down && left_mouse_click_in_cursor) {
        if (left_mouse_down && left_mouse_click_in_cursor) {
            float ratio = NK_MAX(0, (float)(in->mouse.pos.x - cursor.x)) / (float)cursor.w;
            value = (nk_size)NK_CLAMP(0, (float)max * ratio, (float)max);
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.x = cursor.x + cursor.w/2.0f;
            *state |= NK_WIDGET_STATE_ACTIVE;
        }
    }

    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, r))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, r))
        *state |= NK_WIDGET_STATE_LEFT;
    return value;
}
NK_LIB void
nk_draw_progress(struct nk_command_buffer *out, nk_flags state,
    const struct nk_style_progress *style, const struct nk_rect *bounds,
    const struct nk_rect *scursor, nk_size value, nk_size max)
{
    const struct nk_style_item *background;
    const struct nk_style_item *cursor;

    NK_UNUSED(max);
    NK_UNUSED(value);

    if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->active;
        cursor = &style->cursor_active;
    } else if (state & NK_WIDGET_STATE_HOVER){
        background = &style->hover;
        cursor = &style->cursor_hover;
    } else {
        background = &style->normal;
        cursor = &style->cursor_normal;
    }

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(out, *bounds, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(out, *bounds, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(out, *bounds, style->rounding, background->data.color);
            nk_stroke_rect(out, *bounds, style->rounding, style->border, style->border_color);
            break;
    }

    switch(cursor->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(out, *scursor, &cursor->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(out, *scursor, &cursor->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(out, *scursor, style->rounding, cursor->data.color);
            nk_stroke_rect(out, *scursor, style->rounding, style->border, style->border_color);
            break;
    }
}
NK_LIB nk_size
nk_do_progress(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    nk_size value, nk_size max, nk_bool modifiable,
    const struct nk_style_progress *style, struct nk_input *in)
{
    float prog_scale;
    nk_size prog_value;
    struct nk_rect cursor;

    NK_ASSERT(style);
    NK_ASSERT(out);
    if (!out || !style) return 0;

    cursor.w = NK_MAX(bounds.w, 2 * style->padding.x + 2 * style->border);
    cursor.h = NK_MAX(bounds.h, 2 * style->padding.y + 2 * style->border);
    cursor = nk_pad_rect(bounds, nk_vec2(style->padding.x + style->border, style->padding.y + style->border));
    prog_scale = (float)value / (float)max;

    prog_value = NK_MIN(value, max);
    prog_value = nk_progress_behavior(state, in, bounds, cursor,max, prog_value, modifiable);
    cursor.w = cursor.w * prog_scale;

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_progress(out, *state, style, &bounds, &cursor, value, max);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return prog_value;
}
NK_API nk_bool
nk_progress(struct nk_context *ctx, nk_size *cur, nk_size max, nk_bool is_modifyable)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_input *in;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;
    nk_size old_value;

    NK_ASSERT(ctx);
    NK_ASSERT(cur);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !cur)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);
    if (!state) return 0;

    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    old_value = *cur;
    *cur = nk_do_progress(&ctx->last_widget_state, &win->buffer, bounds,
            *cur, max, is_modifyable, &style->progress, in);
    return (*cur != old_value);
}
NK_API nk_size
nk_prog(struct nk_context *ctx, nk_size cur, nk_size max, nk_bool modifyable)
{
    nk_progress(ctx, &cur, max, modifyable);
    return cur;
}

NK_LIB float
nk_scrollbar_behavior(nk_flags *state, struct nk_input *in,
    int has_scrolling, const struct nk_rect *scroll,
    const struct nk_rect *cursor, const struct nk_rect *empty0,
    const struct nk_rect *empty1, float scroll_offset,
    float target, float scroll_step, enum nk_orientation o)
{
    nk_flags ws = 0;
    int left_mouse_down;
    unsigned int left_mouse_clicked;
    int left_mouse_click_in_cursor;
    float scroll_delta;

    nk_widget_state_reset(state);
    if (!in) return scroll_offset;

    left_mouse_down = in->mouse.buttons[NK_BUTTON_LEFT].down;
    left_mouse_clicked = in->mouse.buttons[NK_BUTTON_LEFT].clicked;
    left_mouse_click_in_cursor = nk_input_has_mouse_click_down_in_rect(in,
        NK_BUTTON_LEFT, *cursor, nk_true);
    if (nk_input_is_mouse_hovering_rect(in, *scroll))
        *state = NK_WIDGET_STATE_HOVERED;

    scroll_delta = (o == NK_VERTICAL) ? in->mouse.scroll_delta.y: in->mouse.scroll_delta.x;
    if (left_mouse_down && left_mouse_click_in_cursor && !left_mouse_clicked) {

        float pixel, delta;
        *state = NK_WIDGET_STATE_ACTIVE;
        if (o == NK_VERTICAL) {
            float cursor_y;
            pixel = in->mouse.delta.y;
            delta = (pixel / scroll->h) * target;
            scroll_offset = NK_CLAMP(0, scroll_offset + delta, target - scroll->h);
            cursor_y = scroll->y + ((scroll_offset/target) * scroll->h);
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.y = cursor_y + cursor->h/2.0f;
        } else {
            float cursor_x;
            pixel = in->mouse.delta.x;
            delta = (pixel / scroll->w) * target;
            scroll_offset = NK_CLAMP(0, scroll_offset + delta, target - scroll->w);
            cursor_x = scroll->x + ((scroll_offset/target) * scroll->w);
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.x = cursor_x + cursor->w/2.0f;
        }
    } else if ((nk_input_is_key_pressed(in, NK_KEY_SCROLL_UP) && o == NK_VERTICAL && has_scrolling)||
            nk_button_behavior(&ws, *empty0, in, NK_BUTTON_DEFAULT)) {

        if (o == NK_VERTICAL)
            scroll_offset = NK_MAX(0, scroll_offset - scroll->h);
        else scroll_offset = NK_MAX(0, scroll_offset - scroll->w);
    } else if ((nk_input_is_key_pressed(in, NK_KEY_SCROLL_DOWN) && o == NK_VERTICAL && has_scrolling) ||
        nk_button_behavior(&ws, *empty1, in, NK_BUTTON_DEFAULT)) {

        if (o == NK_VERTICAL)
            scroll_offset = NK_MIN(scroll_offset + scroll->h, target - scroll->h);
        else scroll_offset = NK_MIN(scroll_offset + scroll->w, target - scroll->w);
    } else if (has_scrolling) {
        if ((scroll_delta < 0 || (scroll_delta > 0))) {

            scroll_offset = scroll_offset + scroll_step * (-scroll_delta);
            if (o == NK_VERTICAL)
                scroll_offset = NK_CLAMP(0, scroll_offset, target - scroll->h);
            else scroll_offset = NK_CLAMP(0, scroll_offset, target - scroll->w);
        } else if (nk_input_is_key_pressed(in, NK_KEY_SCROLL_START)) {

            if (o == NK_VERTICAL) scroll_offset = 0;
        } else if (nk_input_is_key_pressed(in, NK_KEY_SCROLL_END)) {

            if (o == NK_VERTICAL) scroll_offset = target - scroll->h;
        }
    }
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, *scroll))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, *scroll))
        *state |= NK_WIDGET_STATE_LEFT;
    return scroll_offset;
}
NK_LIB void
nk_draw_scrollbar(struct nk_command_buffer *out, nk_flags state,
    const struct nk_style_scrollbar *style, const struct nk_rect *bounds,
    const struct nk_rect *scroll)
{
    const struct nk_style_item *background;
    const struct nk_style_item *cursor;

    if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->active;
        cursor = &style->cursor_active;
    } else if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        cursor = &style->cursor_hover;
    } else {
        background = &style->normal;
        cursor = &style->cursor_normal;
    }

    switch (background->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(out, *bounds, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(out, *bounds, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(out, *bounds, style->rounding, background->data.color);
            nk_stroke_rect(out, *bounds, style->rounding, style->border, style->border_color);
            break;
    }

    switch (cursor->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(out, *scroll, &cursor->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(out, *scroll, &cursor->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(out, *scroll, style->rounding_cursor, cursor->data.color);
            nk_stroke_rect(out, *scroll, style->rounding_cursor, style->border_cursor, style->cursor_border_color);
            break;
    }
}
NK_LIB float
nk_do_scrollbarv(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect scroll, int has_scrolling,
    float offset, float target, float step, float button_pixel_inc,
    const struct nk_style_scrollbar *style, struct nk_input *in,
    const struct nk_user_font *font)
{
    struct nk_rect empty_north;
    struct nk_rect empty_south;
    struct nk_rect cursor;

    float scroll_step;
    float scroll_offset;
    float scroll_off;
    float scroll_ratio;

    NK_ASSERT(out);
    NK_ASSERT(style);
    NK_ASSERT(state);
    if (!out || !style) return 0;

    scroll.w = NK_MAX(scroll.w, 1);
    scroll.h = NK_MAX(scroll.h, 0);
    if (target <= scroll.h) return 0;

    if (style->show_buttons) {
        nk_flags ws;
        float scroll_h;
        struct nk_rect button;

        button.x = scroll.x;
        button.w = scroll.w;
        button.h = scroll.w;

        scroll_h = NK_MAX(scroll.h - 2 * button.h,0);
        scroll_step = NK_MIN(step, button_pixel_inc);

        button.y = scroll.y;
        if (nk_do_button_symbol(&ws, out, button, style->dec_symbol,
            NK_BUTTON_REPEATER, &style->dec_button, in, font))
            offset = offset - scroll_step;

        button.y = scroll.y + scroll.h - button.h;
        if (nk_do_button_symbol(&ws, out, button, style->inc_symbol,
            NK_BUTTON_REPEATER, &style->inc_button, in, font))
            offset = offset + scroll_step;

        scroll.y = scroll.y + button.h;
        scroll.h = scroll_h;
    }

    scroll_step = NK_MIN(step, scroll.h);
    scroll_offset = NK_CLAMP(0, offset, target - scroll.h);
    scroll_ratio = scroll.h / target;
    scroll_off = scroll_offset / target;

    cursor.h = NK_MAX((scroll_ratio * scroll.h) - (2*style->border + 2*style->padding.y), 0);
    cursor.y = scroll.y + (scroll_off * scroll.h) + style->border + style->padding.y;
    cursor.w = scroll.w - (2 * style->border + 2 * style->padding.x);
    cursor.x = scroll.x + style->border + style->padding.x;

    empty_north.x = scroll.x;
    empty_north.y = scroll.y;
    empty_north.w = scroll.w;
    empty_north.h = NK_MAX(cursor.y - scroll.y, 0);

    empty_south.x = scroll.x;
    empty_south.y = cursor.y + cursor.h;
    empty_south.w = scroll.w;
    empty_south.h = NK_MAX((scroll.y + scroll.h) - (cursor.y + cursor.h), 0);

    scroll_offset = nk_scrollbar_behavior(state, in, has_scrolling, &scroll, &cursor,
        &empty_north, &empty_south, scroll_offset, target, scroll_step, NK_VERTICAL);
    scroll_off = scroll_offset / target;
    cursor.y = scroll.y + (scroll_off * scroll.h) + style->border_cursor + style->padding.y;

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_scrollbar(out, *state, style, &scroll, &cursor);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return scroll_offset;
}
NK_LIB float
nk_do_scrollbarh(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect scroll, int has_scrolling,
    float offset, float target, float step, float button_pixel_inc,
    const struct nk_style_scrollbar *style, struct nk_input *in,
    const struct nk_user_font *font)
{
    struct nk_rect cursor;
    struct nk_rect empty_west;
    struct nk_rect empty_east;

    float scroll_step;
    float scroll_offset;
    float scroll_off;
    float scroll_ratio;

    NK_ASSERT(out);
    NK_ASSERT(style);
    if (!out || !style) return 0;

    scroll.h = NK_MAX(scroll.h, 1);
    scroll.w = NK_MAX(scroll.w, 2 * scroll.h);
    if (target <= scroll.w) return 0;

    if (style->show_buttons) {
        nk_flags ws;
        float scroll_w;
        struct nk_rect button;
        button.y = scroll.y;
        button.w = scroll.h;
        button.h = scroll.h;

        scroll_w = scroll.w - 2 * button.w;
        scroll_step = NK_MIN(step, button_pixel_inc);

        button.x = scroll.x;
        if (nk_do_button_symbol(&ws, out, button, style->dec_symbol,
            NK_BUTTON_REPEATER, &style->dec_button, in, font))
            offset = offset - scroll_step;

        button.x = scroll.x + scroll.w - button.w;
        if (nk_do_button_symbol(&ws, out, button, style->inc_symbol,
            NK_BUTTON_REPEATER, &style->inc_button, in, font))
            offset = offset + scroll_step;

        scroll.x = scroll.x + button.w;
        scroll.w = scroll_w;
    }

    scroll_step = NK_MIN(step, scroll.w);
    scroll_offset = NK_CLAMP(0, offset, target - scroll.w);
    scroll_ratio = scroll.w / target;
    scroll_off = scroll_offset / target;

    cursor.w = (scroll_ratio * scroll.w) - (2*style->border + 2*style->padding.x);
    cursor.x = scroll.x + (scroll_off * scroll.w) + style->border + style->padding.x;
    cursor.h = scroll.h - (2 * style->border + 2 * style->padding.y);
    cursor.y = scroll.y + style->border + style->padding.y;

    empty_west.x = scroll.x;
    empty_west.y = scroll.y;
    empty_west.w = cursor.x - scroll.x;
    empty_west.h = scroll.h;

    empty_east.x = cursor.x + cursor.w;
    empty_east.y = scroll.y;
    empty_east.w = (scroll.x + scroll.w) - (cursor.x + cursor.w);
    empty_east.h = scroll.h;

    scroll_offset = nk_scrollbar_behavior(state, in, has_scrolling, &scroll, &cursor,
        &empty_west, &empty_east, scroll_offset, target, scroll_step, NK_HORIZONTAL);
    scroll_off = scroll_offset / target;
    cursor.x = scroll.x + (scroll_off * scroll.w);

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_scrollbar(out, *state, style, &scroll, &cursor);
    if (style->draw_end) style->draw_end(out, style->userdata);
    return scroll_offset;
}

struct nk_text_find {
   float x,y;
   float height;
   int first_char, length;
   int prev_first;
};

struct nk_text_edit_row {
   float x0,x1;

   float baseline_y_delta;

   float ymin,ymax;

   int num_chars;
};

NK_INTERN void nk_textedit_makeundo_delete(struct nk_text_edit*, int, int);
NK_INTERN void nk_textedit_makeundo_insert(struct nk_text_edit*, int, int);
NK_INTERN void nk_textedit_makeundo_replace(struct nk_text_edit*, int, int, int);
#define NK_TEXT_HAS_SELECTION(s)   ((s)->select_start != (s)->select_end)

NK_INTERN float
nk_textedit_get_width(const struct nk_text_edit *edit, int line_start, int char_id,
    const struct nk_user_font *font)
{
    int len = 0;
    nk_rune unicode = 0;
    const char *str = nk_str_at_const(&edit->string, line_start + char_id, &unicode, &len);
    return font->width(font->userdata, font->height, str, len);
}
NK_INTERN void
nk_textedit_layout_row(struct nk_text_edit_row *r, struct nk_text_edit *edit,
    int line_start_id, float row_height, const struct nk_user_font *font)
{
    int l;
    int glyphs = 0;
    nk_rune unicode;
    const char *remaining;
    int len = nk_str_len_char(&edit->string);
    const char *end = nk_str_get_const(&edit->string) + len;
    const char *text = nk_str_at_const(&edit->string, line_start_id, &unicode, &l);
    const struct nk_vec2 size = nk_text_calculate_text_bounds(font,
        text, (int)(end - text), row_height, &remaining, 0, &glyphs, NK_STOP_ON_NEW_LINE);

    r->x0 = 0.0f;
    r->x1 = size.x;
    r->baseline_y_delta = size.y;
    r->ymin = 0.0f;
    r->ymax = size.y;
    r->num_chars = glyphs;
}
NK_INTERN int
nk_textedit_locate_coord(struct nk_text_edit *edit, float x, float y,
    const struct nk_user_font *font, float row_height)
{
    struct nk_text_edit_row r;
    int n = edit->string.len;
    float base_y = 0, prev_x;
    int i=0, k;

    r.x0 = r.x1 = 0;
    r.ymin = r.ymax = 0;
    r.num_chars = 0;

    while (i < n) {
        nk_textedit_layout_row(&r, edit, i, row_height, font);
        if (r.num_chars <= 0)
            return n;

        if (i==0 && y < base_y + r.ymin)
            return 0;

        if (y < base_y + r.ymax)
            break;

        i += r.num_chars;
        base_y += r.baseline_y_delta;
    }

    if (i >= n)
        return n;

    if (x < r.x0)
        return i;

    if (x < r.x1) {

        k = i;
        prev_x = r.x0;
        for (i=0; i < r.num_chars; ++i) {
            float w = nk_textedit_get_width(edit, k, i, font);
            if (x < prev_x+w) {
                if (x < prev_x+w/2)
                    return k+i;
                else return k+i+1;
            }
            prev_x += w;
        }

    }

    if (nk_str_rune_at(&edit->string, i+r.num_chars-1) == '\n')
        return i+r.num_chars-1;
    else return i+r.num_chars;
}
NK_LIB void
nk_textedit_click(struct nk_text_edit *state, float x, float y,
    const struct nk_user_font *font, float row_height)
{

    state->cursor = nk_textedit_locate_coord(state, x, y, font, row_height);
    state->select_start = state->cursor;
    state->select_end = state->cursor;
    state->has_preferred_x = 0;
}
NK_LIB void
nk_textedit_drag(struct nk_text_edit *state, float x, float y,
    const struct nk_user_font *font, float row_height)
{

    int p = nk_textedit_locate_coord(state, x, y, font, row_height);
    if (state->select_start == state->select_end)
        state->select_start = state->cursor;
    state->cursor = state->select_end = p;
}
NK_INTERN void
nk_textedit_find_charpos(struct nk_text_find *find, struct nk_text_edit *state,
    int n, int single_line, const struct nk_user_font *font, float row_height)
{

    struct nk_text_edit_row r;
    int prev_start = 0;
    int z = state->string.len;
    int i=0, first;

    nk_zero_struct(r);
    if (n == z) {

        nk_textedit_layout_row(&r, state, 0, row_height, font);
        if (single_line) {
            find->first_char = 0;
            find->length = z;
        } else {
            while (i < z) {
                prev_start = i;
                i += r.num_chars;
                nk_textedit_layout_row(&r, state, i, row_height, font);
            }

            find->first_char = i;
            find->length = r.num_chars;
        }
        find->x = r.x1;
        find->y = r.ymin;
        find->height = r.ymax - r.ymin;
        find->prev_first = prev_start;
        return;
    }

    find->y = 0;

    for(;;) {
        nk_textedit_layout_row(&r, state, i, row_height, font);
        if (n < i + r.num_chars) break;
        prev_start = i;
        i += r.num_chars;
        find->y += r.baseline_y_delta;
    }

    find->first_char = first = i;
    find->length = r.num_chars;
    find->height = r.ymax - r.ymin;
    find->prev_first = prev_start;

    find->x = r.x0;
    for (i=0; first+i < n; ++i)
        find->x += nk_textedit_get_width(state, first, i, font);
}
NK_INTERN void
nk_textedit_clamp(struct nk_text_edit *state)
{

    int n = state->string.len;
    if (NK_TEXT_HAS_SELECTION(state)) {
        if (state->select_start > n) state->select_start = n;
        if (state->select_end   > n) state->select_end = n;

        if (state->select_start == state->select_end)
            state->cursor = state->select_start;
    }
    if (state->cursor > n) state->cursor = n;
}
NK_API void
nk_textedit_delete(struct nk_text_edit *state, int where, int len)
{

    nk_textedit_makeundo_delete(state, where, len);
    nk_str_delete_runes(&state->string, where, len);
    state->has_preferred_x = 0;
}
NK_API void
nk_textedit_delete_selection(struct nk_text_edit *state)
{

    nk_textedit_clamp(state);
    if (NK_TEXT_HAS_SELECTION(state)) {
        if (state->select_start < state->select_end) {
            nk_textedit_delete(state, state->select_start,
                state->select_end - state->select_start);
            state->select_end = state->cursor = state->select_start;
        } else {
            nk_textedit_delete(state, state->select_end,
                state->select_start - state->select_end);
            state->select_start = state->cursor = state->select_end;
        }
        state->has_preferred_x = 0;
    }
}
NK_INTERN void
nk_textedit_sortselection(struct nk_text_edit *state)
{

    if (state->select_end < state->select_start) {
        int temp = state->select_end;
        state->select_end = state->select_start;
        state->select_start = temp;
    }
}
NK_INTERN void
nk_textedit_move_to_first(struct nk_text_edit *state)
{

    if (NK_TEXT_HAS_SELECTION(state)) {
        nk_textedit_sortselection(state);
        state->cursor = state->select_start;
        state->select_end = state->select_start;
        state->has_preferred_x = 0;
    }
}
NK_INTERN void
nk_textedit_move_to_last(struct nk_text_edit *state)
{

    if (NK_TEXT_HAS_SELECTION(state)) {
        nk_textedit_sortselection(state);
        nk_textedit_clamp(state);
        state->cursor = state->select_end;
        state->select_start = state->select_end;
        state->has_preferred_x = 0;
    }
}
NK_INTERN int
nk_is_word_boundary( struct nk_text_edit *state, int idx)
{
    int len;
    nk_rune c;
    if (idx <= 0) return 1;
    if (!nk_str_at_rune(&state->string, idx, &c, &len)) return 1;
    return (c == ' ' || c == '\t' ||c == 0x3000 || c == ',' || c == ';' ||
            c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ||
            c == '|');
}
NK_INTERN int
nk_textedit_move_to_word_previous(struct nk_text_edit *state)
{
   int c = state->cursor - 1;
   while( c >= 0 && !nk_is_word_boundary(state, c))
      --c;

   if( c < 0 )
      c = 0;

   return c;
}
NK_INTERN int
nk_textedit_move_to_word_next(struct nk_text_edit *state)
{
   const int len = state->string.len;
   int c = state->cursor+1;
   while( c < len && !nk_is_word_boundary(state, c))
      ++c;

   if( c > len )
      c = len;

   return c;
}
NK_INTERN void
nk_textedit_prep_selection_at_cursor(struct nk_text_edit *state)
{

    if (!NK_TEXT_HAS_SELECTION(state))
        state->select_start = state->select_end = state->cursor;
    else state->cursor = state->select_end;
}
NK_API nk_bool
nk_textedit_cut(struct nk_text_edit *state)
{

    if (state->mode == NK_TEXT_EDIT_MODE_VIEW)
        return 0;
    if (NK_TEXT_HAS_SELECTION(state)) {
        nk_textedit_delete_selection(state);
        state->has_preferred_x = 0;
        return 1;
    }
   return 0;
}
NK_API nk_bool
nk_textedit_paste(struct nk_text_edit *state, char const *ctext, int len)
{

    int glyphs;
    const char *text = (const char *) ctext;
    if (state->mode == NK_TEXT_EDIT_MODE_VIEW) return 0;

    nk_textedit_clamp(state);
    nk_textedit_delete_selection(state);

    glyphs = nk_utf_len(ctext, len);
    if (nk_str_insert_text_char(&state->string, state->cursor, text, len)) {
        nk_textedit_makeundo_insert(state, state->cursor, glyphs);
        state->cursor += len;
        state->has_preferred_x = 0;
        return 1;
    }

    if (state->undo.undo_point)
        --state->undo.undo_point;
    return 0;
}
NK_API void
nk_textedit_text(struct nk_text_edit *state, const char *text, int total_len)
{
    nk_rune unicode;
    int glyph_len;
    int text_len = 0;

    NK_ASSERT(state);
    NK_ASSERT(text);
    if (!text || !total_len || state->mode == NK_TEXT_EDIT_MODE_VIEW) return;

    glyph_len = nk_utf_decode(text, &unicode, total_len);
    while ((text_len < total_len) && glyph_len)
    {

        if (unicode == 127) goto next;

        if (unicode == '\n' && state->single_line) goto next;

        if (state->filter && !state->filter(state, unicode)) goto next;

        if (!NK_TEXT_HAS_SELECTION(state) &&
            state->cursor < state->string.len)
        {
            if (state->mode == NK_TEXT_EDIT_MODE_REPLACE) {
                nk_textedit_makeundo_replace(state, state->cursor, 1, 1);
                nk_str_delete_runes(&state->string, state->cursor, 1);
            }
            if (nk_str_insert_text_utf8(&state->string, state->cursor,
                                        text+text_len, 1))
            {
                ++state->cursor;
                state->has_preferred_x = 0;
            }
        } else {
            nk_textedit_delete_selection(state);
            if (nk_str_insert_text_utf8(&state->string, state->cursor,
                                        text+text_len, 1))
            {
                nk_textedit_makeundo_insert(state, state->cursor, 1);
                state->cursor = NK_MIN(state->cursor + 1, state->string.len);
                state->has_preferred_x = 0;
            }
        }
        next:
        text_len += glyph_len;
        glyph_len = nk_utf_decode(text + text_len, &unicode, total_len-text_len);
    }
}
NK_LIB void
nk_textedit_key(struct nk_text_edit *state, enum nk_keys key, int shift_mod,
    const struct nk_user_font *font, float row_height)
{
retry:
    switch (key)
    {
    case NK_KEY_NONE:
    case NK_KEY_CTRL:
    case NK_KEY_ENTER:
    case NK_KEY_SHIFT:
    case NK_KEY_TAB:
    case NK_KEY_COPY:
    case NK_KEY_CUT:
    case NK_KEY_PASTE:
    case NK_KEY_MAX:
    default: break;
    case NK_KEY_TEXT_UNDO:
         nk_textedit_undo(state);
         state->has_preferred_x = 0;
         break;

    case NK_KEY_TEXT_REDO:
        nk_textedit_redo(state);
        state->has_preferred_x = 0;
        break;

    case NK_KEY_TEXT_SELECT_ALL:
        nk_textedit_select_all(state);
        state->has_preferred_x = 0;
        break;

    case NK_KEY_TEXT_INSERT_MODE:
        if (state->mode == NK_TEXT_EDIT_MODE_VIEW)
            state->mode = NK_TEXT_EDIT_MODE_INSERT;
        break;
    case NK_KEY_TEXT_REPLACE_MODE:
        if (state->mode == NK_TEXT_EDIT_MODE_VIEW)
            state->mode = NK_TEXT_EDIT_MODE_REPLACE;
        break;
    case NK_KEY_TEXT_RESET_MODE:
        if (state->mode == NK_TEXT_EDIT_MODE_INSERT ||
            state->mode == NK_TEXT_EDIT_MODE_REPLACE)
            state->mode = NK_TEXT_EDIT_MODE_VIEW;
        break;

    case NK_KEY_LEFT:
        if (shift_mod) {
            nk_textedit_clamp(state);
            nk_textedit_prep_selection_at_cursor(state);

            if (state->select_end > 0)
                --state->select_end;
            state->cursor = state->select_end;
            state->has_preferred_x = 0;
        } else {

            if (NK_TEXT_HAS_SELECTION(state))
                nk_textedit_move_to_first(state);
            else if (state->cursor > 0)
               --state->cursor;
            state->has_preferred_x = 0;
        } break;

    case NK_KEY_RIGHT:
        if (shift_mod) {
            nk_textedit_prep_selection_at_cursor(state);

            ++state->select_end;
            nk_textedit_clamp(state);
            state->cursor = state->select_end;
            state->has_preferred_x = 0;
        } else {

            if (NK_TEXT_HAS_SELECTION(state))
                nk_textedit_move_to_last(state);
            else ++state->cursor;
            nk_textedit_clamp(state);
            state->has_preferred_x = 0;
        } break;

    case NK_KEY_TEXT_WORD_LEFT:
        if (shift_mod) {
            if( !NK_TEXT_HAS_SELECTION( state ) )
            nk_textedit_prep_selection_at_cursor(state);
            state->cursor = nk_textedit_move_to_word_previous(state);
            state->select_end = state->cursor;
            nk_textedit_clamp(state );
        } else {
            if (NK_TEXT_HAS_SELECTION(state))
                nk_textedit_move_to_first(state);
            else {
                state->cursor = nk_textedit_move_to_word_previous(state);
                nk_textedit_clamp(state );
            }
        } break;

    case NK_KEY_TEXT_WORD_RIGHT:
        if (shift_mod) {
            if( !NK_TEXT_HAS_SELECTION( state ) )
                nk_textedit_prep_selection_at_cursor(state);
            state->cursor = nk_textedit_move_to_word_next(state);
            state->select_end = state->cursor;
            nk_textedit_clamp(state);
        } else {
            if (NK_TEXT_HAS_SELECTION(state))
                nk_textedit_move_to_last(state);
            else {
                state->cursor = nk_textedit_move_to_word_next(state);
                nk_textedit_clamp(state );
            }
        } break;

    case NK_KEY_DOWN: {
        struct nk_text_find find;
        struct nk_text_edit_row row;
        int i, sel = shift_mod;

        if (state->single_line) {

            key = NK_KEY_RIGHT;
            goto retry;
        }

        if (sel)
            nk_textedit_prep_selection_at_cursor(state);
        else if (NK_TEXT_HAS_SELECTION(state))
            nk_textedit_move_to_last(state);

        nk_textedit_clamp(state);
        nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
            font, row_height);

        if (find.length)
        {
            float x;
            float goal_x = state->has_preferred_x ? state->preferred_x : find.x;
            int start = find.first_char + find.length;

            state->cursor = start;
            nk_textedit_layout_row(&row, state, state->cursor, row_height, font);
            x = row.x0;

            for (i=0; i < row.num_chars && x < row.x1; ++i) {
                float dx = nk_textedit_get_width(state, start, i, font);
                x += dx;
                if (x > goal_x)
                    break;
                ++state->cursor;
            }
            nk_textedit_clamp(state);

            state->has_preferred_x = 1;
            state->preferred_x = goal_x;
            if (sel)
                state->select_end = state->cursor;
        }
    } break;

    case NK_KEY_UP: {
        struct nk_text_find find;
        struct nk_text_edit_row row;
        int i, sel = shift_mod;

        if (state->single_line) {

            key = NK_KEY_LEFT;
            goto retry;
        }

        if (sel)
            nk_textedit_prep_selection_at_cursor(state);
        else if (NK_TEXT_HAS_SELECTION(state))
            nk_textedit_move_to_first(state);

         nk_textedit_clamp(state);
         nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
                font, row_height);

         if (find.prev_first != find.first_char) {

            float x;
            float goal_x = state->has_preferred_x ? state->preferred_x : find.x;

            state->cursor = find.prev_first;
            nk_textedit_layout_row(&row, state, state->cursor, row_height, font);
            x = row.x0;

            for (i=0; i < row.num_chars && x < row.x1; ++i) {
                float dx = nk_textedit_get_width(state, find.prev_first, i, font);
                x += dx;
                if (x > goal_x)
                    break;
                ++state->cursor;
            }
            nk_textedit_clamp(state);

            state->has_preferred_x = 1;
            state->preferred_x = goal_x;
            if (sel) state->select_end = state->cursor;
         }
      } break;

    case NK_KEY_DEL:
        if (state->mode == NK_TEXT_EDIT_MODE_VIEW)
            break;
        if (NK_TEXT_HAS_SELECTION(state))
            nk_textedit_delete_selection(state);
        else {
            int n = state->string.len;
            if (state->cursor < n)
                nk_textedit_delete(state, state->cursor, 1);
         }
         state->has_preferred_x = 0;
         break;

    case NK_KEY_BACKSPACE:
        if (state->mode == NK_TEXT_EDIT_MODE_VIEW)
            break;
        if (NK_TEXT_HAS_SELECTION(state))
            nk_textedit_delete_selection(state);
        else {
            nk_textedit_clamp(state);
            if (state->cursor > 0) {
                nk_textedit_delete(state, state->cursor-1, 1);
                --state->cursor;
            }
         }
         state->has_preferred_x = 0;
         break;

    case NK_KEY_TEXT_START:
         if (shift_mod) {
            nk_textedit_prep_selection_at_cursor(state);
            state->cursor = state->select_end = 0;
            state->has_preferred_x = 0;
         } else {
            state->cursor = state->select_start = state->select_end = 0;
            state->has_preferred_x = 0;
         }
         break;

    case NK_KEY_TEXT_END:
         if (shift_mod) {
            nk_textedit_prep_selection_at_cursor(state);
            state->cursor = state->select_end = state->string.len;
            state->has_preferred_x = 0;
         } else {
            state->cursor = state->string.len;
            state->select_start = state->select_end = 0;
            state->has_preferred_x = 0;
         }
         break;

    case NK_KEY_TEXT_LINE_START: {
        if (shift_mod) {
            struct nk_text_find find;
           nk_textedit_clamp(state);
            nk_textedit_prep_selection_at_cursor(state);
            if (state->string.len && state->cursor == state->string.len)
                --state->cursor;
            nk_textedit_find_charpos(&find, state,state->cursor, state->single_line,
                font, row_height);
            state->cursor = state->select_end = find.first_char;
            state->has_preferred_x = 0;
        } else {
            struct nk_text_find find;
            if (state->string.len && state->cursor == state->string.len)
                --state->cursor;
            nk_textedit_clamp(state);
            nk_textedit_move_to_first(state);
            nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
                font, row_height);
            state->cursor = find.first_char;
            state->has_preferred_x = 0;
        }
      } break;

    case NK_KEY_TEXT_LINE_END: {
        if (shift_mod) {
            struct nk_text_find find;
            nk_textedit_clamp(state);
            nk_textedit_prep_selection_at_cursor(state);
            nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
                font, row_height);
            state->has_preferred_x = 0;
            state->cursor = find.first_char + find.length;
            if (find.length > 0 && nk_str_rune_at(&state->string, state->cursor-1) == '\n')
                --state->cursor;
            state->select_end = state->cursor;
        } else {
            struct nk_text_find find;
            nk_textedit_clamp(state);
            nk_textedit_move_to_first(state);
            nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
                font, row_height);

            state->has_preferred_x = 0;
            state->cursor = find.first_char + find.length;
            if (find.length > 0 && nk_str_rune_at(&state->string, state->cursor-1) == '\n')
                --state->cursor;
        }} break;
    }
}
NK_INTERN void
nk_textedit_flush_redo(struct nk_text_undo_state *state)
{
    state->redo_point = NK_TEXTEDIT_UNDOSTATECOUNT;
    state->redo_char_point = NK_TEXTEDIT_UNDOCHARCOUNT;
}
NK_INTERN void
nk_textedit_discard_undo(struct nk_text_undo_state *state)
{

    if (state->undo_point > 0) {

        if (state->undo_rec[0].char_storage >= 0) {
            int n = state->undo_rec[0].insert_length, i;

            state->undo_char_point = (short)(state->undo_char_point - n);
            NK_MEMCPY(state->undo_char, state->undo_char + n,
                (nk_size)state->undo_char_point*sizeof(nk_rune));
            for (i=0; i < state->undo_point; ++i) {
                if (state->undo_rec[i].char_storage >= 0)
                state->undo_rec[i].char_storage = (short)
                    (state->undo_rec[i].char_storage - n);
            }
        }
        --state->undo_point;
        NK_MEMCPY(state->undo_rec, state->undo_rec+1,
            (nk_size)((nk_size)state->undo_point * sizeof(state->undo_rec[0])));
    }
}
NK_INTERN void
nk_textedit_discard_redo(struct nk_text_undo_state *state)
{

    nk_size num;
    int k = NK_TEXTEDIT_UNDOSTATECOUNT-1;
    if (state->redo_point <= k) {

        if (state->undo_rec[k].char_storage >= 0) {
            int n = state->undo_rec[k].insert_length, i;

            state->redo_char_point = (short)(state->redo_char_point + n);
            num = (nk_size)(NK_TEXTEDIT_UNDOCHARCOUNT - state->redo_char_point);
            NK_MEMCPY(state->undo_char + state->redo_char_point,
                state->undo_char + state->redo_char_point-n, num * sizeof(char));
            for (i = state->redo_point; i < k; ++i) {
                if (state->undo_rec[i].char_storage >= 0) {
                    state->undo_rec[i].char_storage = (short)
                        (state->undo_rec[i].char_storage + n);
                }
            }
        }
        ++state->redo_point;
        num = (nk_size)(NK_TEXTEDIT_UNDOSTATECOUNT - state->redo_point);
        if (num) NK_MEMCPY(state->undo_rec + state->redo_point-1,
            state->undo_rec + state->redo_point, num * sizeof(state->undo_rec[0]));
    }
}
NK_INTERN struct nk_text_undo_record*
nk_textedit_create_undo_record(struct nk_text_undo_state *state, int numchars)
{

    nk_textedit_flush_redo(state);

    if (state->undo_point == NK_TEXTEDIT_UNDOSTATECOUNT)
        nk_textedit_discard_undo(state);

    if (numchars > NK_TEXTEDIT_UNDOCHARCOUNT) {
        state->undo_point = 0;
        state->undo_char_point = 0;
        return 0;
    }

    while (state->undo_char_point + numchars > NK_TEXTEDIT_UNDOCHARCOUNT)
        nk_textedit_discard_undo(state);
    return &state->undo_rec[state->undo_point++];
}
NK_INTERN nk_rune*
nk_textedit_createundo(struct nk_text_undo_state *state, int pos,
    int insert_len, int delete_len)
{
    struct nk_text_undo_record *r = nk_textedit_create_undo_record(state, insert_len);
    if (r == 0)
        return 0;

    r->where = pos;
    r->insert_length = (short) insert_len;
    r->delete_length = (short) delete_len;

    if (insert_len == 0) {
        r->char_storage = -1;
        return 0;
    } else {
        r->char_storage = state->undo_char_point;
        state->undo_char_point = (short)(state->undo_char_point +  insert_len);
        return &state->undo_char[r->char_storage];
    }
}
NK_API void
nk_textedit_undo(struct nk_text_edit *state)
{
    struct nk_text_undo_state *s = &state->undo;
    struct nk_text_undo_record u, *r;
    if (s->undo_point == 0)
        return;

    u = s->undo_rec[s->undo_point-1];
    r = &s->undo_rec[s->redo_point-1];
    r->char_storage = -1;

    r->insert_length = u.delete_length;
    r->delete_length = u.insert_length;
    r->where = u.where;

    if (u.delete_length)
    {

        if (s->undo_char_point + u.delete_length >= NK_TEXTEDIT_UNDOCHARCOUNT) {

            r->insert_length = 0;
        } else {
            int i;

            while (s->undo_char_point + u.delete_length > s->redo_char_point) {

                nk_textedit_discard_redo(s);

                if (s->redo_point == NK_TEXTEDIT_UNDOSTATECOUNT)
                    return;
            }

            r = &s->undo_rec[s->redo_point-1];
            r->char_storage = (short)(s->redo_char_point - u.delete_length);
            s->redo_char_point = (short)(s->redo_char_point -  u.delete_length);

            for (i=0; i < u.delete_length; ++i)
                s->undo_char[r->char_storage + i] =
                    nk_str_rune_at(&state->string, u.where + i);
        }

        nk_str_delete_runes(&state->string, u.where, u.delete_length);
    }

    if (u.insert_length) {

        nk_str_insert_text_runes(&state->string, u.where,
            &s->undo_char[u.char_storage], u.insert_length);
        s->undo_char_point = (short)(s->undo_char_point - u.insert_length);
    }
    state->cursor = (short)(u.where + u.insert_length);

    s->undo_point--;
    s->redo_point--;
}
NK_API void
nk_textedit_redo(struct nk_text_edit *state)
{
    struct nk_text_undo_state *s = &state->undo;
    struct nk_text_undo_record *u, r;
    if (s->redo_point == NK_TEXTEDIT_UNDOSTATECOUNT)
        return;

    u = &s->undo_rec[s->undo_point];
    r = s->undo_rec[s->redo_point];

    u->delete_length = r.insert_length;
    u->insert_length = r.delete_length;
    u->where = r.where;
    u->char_storage = -1;

    if (r.delete_length) {

        if (s->undo_char_point + u->insert_length > s->redo_char_point) {
            u->insert_length = 0;
            u->delete_length = 0;
        } else {
            int i;
            u->char_storage = s->undo_char_point;
            s->undo_char_point = (short)(s->undo_char_point + u->insert_length);

            for (i=0; i < u->insert_length; ++i) {
                s->undo_char[u->char_storage + i] =
                    nk_str_rune_at(&state->string, u->where + i);
            }
        }
        nk_str_delete_runes(&state->string, r.where, r.delete_length);
    }

    if (r.insert_length) {

        nk_str_insert_text_runes(&state->string, r.where,
            &s->undo_char[r.char_storage], r.insert_length);
    }
    state->cursor = r.where + r.insert_length;

    s->undo_point++;
    s->redo_point++;
}
NK_INTERN void
nk_textedit_makeundo_insert(struct nk_text_edit *state, int where, int length)
{
    nk_textedit_createundo(&state->undo, where, 0, length);
}
NK_INTERN void
nk_textedit_makeundo_delete(struct nk_text_edit *state, int where, int length)
{
    int i;
    nk_rune *p = nk_textedit_createundo(&state->undo, where, length, 0);
    if (p) {
        for (i=0; i < length; ++i)
            p[i] = nk_str_rune_at(&state->string, where+i);
    }
}
NK_INTERN void
nk_textedit_makeundo_replace(struct nk_text_edit *state, int where,
    int old_length, int new_length)
{
    int i;
    nk_rune *p = nk_textedit_createundo(&state->undo, where, old_length, new_length);
    if (p) {
        for (i=0; i < old_length; ++i)
            p[i] = nk_str_rune_at(&state->string, where+i);
    }
}
NK_LIB void
nk_textedit_clear_state(struct nk_text_edit *state, enum nk_text_edit_type type,
    nk_plugin_filter filter)
{

   state->undo.undo_point = 0;
   state->undo.undo_char_point = 0;
   state->undo.redo_point = NK_TEXTEDIT_UNDOSTATECOUNT;
   state->undo.redo_char_point = NK_TEXTEDIT_UNDOCHARCOUNT;
   state->select_end = state->select_start = 0;
   state->cursor = 0;
   state->has_preferred_x = 0;
   state->preferred_x = 0;
   state->cursor_at_end_of_line = 0;
   state->initialized = 1;
   state->single_line = (unsigned char)(type == NK_TEXT_EDIT_SINGLE_LINE);
   state->mode = NK_TEXT_EDIT_MODE_VIEW;
   state->filter = filter;
   state->scrollbar = nk_vec2(0,0);
}
NK_API void
nk_textedit_init_fixed(struct nk_text_edit *state, void *memory, nk_size size)
{
    NK_ASSERT(state);
    NK_ASSERT(memory);
    if (!state || !memory || !size) return;
    NK_MEMSET(state, 0, sizeof(struct nk_text_edit));
    nk_textedit_clear_state(state, NK_TEXT_EDIT_SINGLE_LINE, 0);
    nk_str_init_fixed(&state->string, memory, size);
}
NK_API void
nk_textedit_init(struct nk_text_edit *state, struct nk_allocator *alloc, nk_size size)
{
    NK_ASSERT(state);
    NK_ASSERT(alloc);
    if (!state || !alloc) return;
    NK_MEMSET(state, 0, sizeof(struct nk_text_edit));
    nk_textedit_clear_state(state, NK_TEXT_EDIT_SINGLE_LINE, 0);
    nk_str_init(&state->string, alloc, size);
}
#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void
nk_textedit_init_default(struct nk_text_edit *state)
{
    NK_ASSERT(state);
    if (!state) return;
    NK_MEMSET(state, 0, sizeof(struct nk_text_edit));
    nk_textedit_clear_state(state, NK_TEXT_EDIT_SINGLE_LINE, 0);
    nk_str_init_default(&state->string);
}
#endif
NK_API void
nk_textedit_select_all(struct nk_text_edit *state)
{
    NK_ASSERT(state);
    state->select_start = 0;
    state->select_end = state->string.len;
}
NK_API void
nk_textedit_free(struct nk_text_edit *state)
{
    NK_ASSERT(state);
    if (!state) return;
    nk_str_free(&state->string);
}

NK_API nk_bool
nk_filter_default(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(unicode);
    NK_UNUSED(box);
    return nk_true;
}
NK_API nk_bool
nk_filter_ascii(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if (unicode > 128) return nk_false;
    else return nk_true;
}
NK_API nk_bool
nk_filter_float(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if ((unicode < '0' || unicode > '9') && unicode != '.' && unicode != '-')
        return nk_false;
    else return nk_true;
}
NK_API nk_bool
nk_filter_decimal(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if ((unicode < '0' || unicode > '9') && unicode != '-')
        return nk_false;
    else return nk_true;
}
NK_API nk_bool
nk_filter_hex(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if ((unicode < '0' || unicode > '9') &&
        (unicode < 'a' || unicode > 'f') &&
        (unicode < 'A' || unicode > 'F'))
        return nk_false;
    else return nk_true;
}
NK_API nk_bool
nk_filter_oct(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if (unicode < '0' || unicode > '7')
        return nk_false;
    else return nk_true;
}
NK_API nk_bool
nk_filter_binary(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if (unicode != '0' && unicode != '1')
        return nk_false;
    else return nk_true;
}

NK_LIB void
nk_edit_draw_text(struct nk_command_buffer *out,
    const struct nk_style_edit *style, float pos_x, float pos_y,
    float x_offset, const char *text, int byte_len, float row_height,
    const struct nk_user_font *font, struct nk_color background,
    struct nk_color foreground, nk_bool is_selected)
{
    NK_ASSERT(out);
    NK_ASSERT(font);
    NK_ASSERT(style);
    if (!text || !byte_len || !out || !style) return;

    {int glyph_len = 0;
    nk_rune unicode = 0;
    int text_len = 0;
    float line_width = 0;
    float glyph_width;
    const char *line = text;
    float line_offset = 0;
    int line_count = 0;

    struct nk_text txt;
    txt.padding = nk_vec2(0,0);
    txt.background = background;
    txt.text = foreground;

    glyph_len = nk_utf_decode(text+text_len, &unicode, byte_len-text_len);
    if (!glyph_len) return;
    while ((text_len < byte_len) && glyph_len)
    {
        if (unicode == '\n') {

            struct nk_rect label;
            label.y = pos_y + line_offset;
            label.h = row_height;
            label.w = line_width;
            label.x = pos_x;
            if (!line_count)
                label.x += x_offset;

            if (is_selected)
                nk_fill_rect(out, label, 0, background);
            nk_widget_text(out, label, line, (int)((text + text_len) - line),
                &txt, NK_TEXT_CENTERED, font);

            text_len++;
            line_count++;
            line_width = 0;
            line = text + text_len;
            line_offset += row_height;
            glyph_len = nk_utf_decode(text + text_len, &unicode, (int)(byte_len-text_len));
            continue;
        }
        if (unicode == '\r') {
            text_len++;
            glyph_len = nk_utf_decode(text + text_len, &unicode, byte_len-text_len);
            continue;
        }
        glyph_width = font->width(font->userdata, font->height, text+text_len, glyph_len);
        line_width += (float)glyph_width;
        text_len += glyph_len;
        glyph_len = nk_utf_decode(text + text_len, &unicode, byte_len-text_len);
        continue;
    }
    if (line_width > 0) {

        struct nk_rect label;
        label.y = pos_y + line_offset;
        label.h = row_height;
        label.w = line_width;
        label.x = pos_x;
        if (!line_count)
            label.x += x_offset;

        if (is_selected)
            nk_fill_rect(out, label, 0, background);
        nk_widget_text(out, label, line, (int)((text + text_len) - line),
            &txt, NK_TEXT_LEFT, font);
    }}
}
NK_LIB nk_flags
nk_do_edit(nk_flags *state, struct nk_command_buffer *out,
    struct nk_rect bounds, nk_flags flags, nk_plugin_filter filter,
    struct nk_text_edit *edit, const struct nk_style_edit *style,
    struct nk_input *in, const struct nk_user_font *font)
{
    struct nk_rect area;
    nk_flags ret = 0;
    float row_height;
    char prev_state = 0;
    char is_hovered = 0;
    char select_all = 0;
    char cursor_follow = 0;
    struct nk_rect old_clip;
    struct nk_rect clip;

    NK_ASSERT(state);
    NK_ASSERT(out);
    NK_ASSERT(style);
    if (!state || !out || !style)
        return ret;

    area.x = bounds.x + style->padding.x + style->border;
    area.y = bounds.y + style->padding.y + style->border;
    area.w = bounds.w - (2.0f * style->padding.x + 2 * style->border);
    area.h = bounds.h - (2.0f * style->padding.y + 2 * style->border);
    if (flags & NK_EDIT_MULTILINE)
        area.w = NK_MAX(0, area.w - style->scrollbar_size.x);
    row_height = (flags & NK_EDIT_MULTILINE)? font->height + style->row_padding: area.h;

    old_clip = out->clip;
    nk_unify(&clip, &old_clip, area.x, area.y, area.x + area.w, area.y + area.h);

    prev_state = (char)edit->active;
    is_hovered = (char)nk_input_is_mouse_hovering_rect(in, bounds);
    if (in && in->mouse.buttons[NK_BUTTON_LEFT].clicked && in->mouse.buttons[NK_BUTTON_LEFT].down) {
        edit->active = NK_INBOX(in->mouse.pos.x, in->mouse.pos.y,
                                bounds.x, bounds.y, bounds.w, bounds.h);
    }

    if (!prev_state && edit->active) {
        const enum nk_text_edit_type type = (flags & NK_EDIT_MULTILINE) ?
            NK_TEXT_EDIT_MULTI_LINE: NK_TEXT_EDIT_SINGLE_LINE;

        struct nk_vec2 oldscrollbar = edit->scrollbar;
        nk_textedit_clear_state(edit, type, filter);
        edit->scrollbar = oldscrollbar;
        if (flags & NK_EDIT_AUTO_SELECT)
            select_all = nk_true;
        if (flags & NK_EDIT_GOTO_END_ON_ACTIVATE) {
            edit->cursor = edit->string.len;
            in = 0;
        }
    } else if (!edit->active) edit->mode = NK_TEXT_EDIT_MODE_VIEW;
    if (flags & NK_EDIT_READ_ONLY)
        edit->mode = NK_TEXT_EDIT_MODE_VIEW;
    else if (flags & NK_EDIT_ALWAYS_INSERT_MODE)
        edit->mode = NK_TEXT_EDIT_MODE_INSERT;

    ret = (edit->active) ? NK_EDIT_ACTIVE: NK_EDIT_INACTIVE;
    if (prev_state != edit->active)
        ret |= (edit->active) ? NK_EDIT_ACTIVATED: NK_EDIT_DEACTIVATED;

    if (edit->active && in)
    {
        int shift_mod = in->keyboard.keys[NK_KEY_SHIFT].down;
        const float mouse_x = (in->mouse.pos.x - area.x) + edit->scrollbar.x;
        const float mouse_y = (in->mouse.pos.y - area.y) + edit->scrollbar.y;

        is_hovered = (char)nk_input_is_mouse_hovering_rect(in, area);
        if (select_all) {
            nk_textedit_select_all(edit);
        } else if (is_hovered && in->mouse.buttons[NK_BUTTON_LEFT].down &&
            in->mouse.buttons[NK_BUTTON_LEFT].clicked) {
            nk_textedit_click(edit, mouse_x, mouse_y, font, row_height);
        } else if (is_hovered && in->mouse.buttons[NK_BUTTON_LEFT].down &&
            (in->mouse.delta.x != 0.0f || in->mouse.delta.y != 0.0f)) {
            nk_textedit_drag(edit, mouse_x, mouse_y, font, row_height);
            cursor_follow = nk_true;
        } else if (is_hovered && in->mouse.buttons[NK_BUTTON_RIGHT].clicked &&
            in->mouse.buttons[NK_BUTTON_RIGHT].down) {
            nk_textedit_key(edit, NK_KEY_TEXT_WORD_LEFT, nk_false, font, row_height);
            nk_textedit_key(edit, NK_KEY_TEXT_WORD_RIGHT, nk_true, font, row_height);
            cursor_follow = nk_true;
        }

        {int i;
        int old_mode = edit->mode;
        for (i = 0; i < NK_KEY_MAX; ++i) {
            if (i == NK_KEY_ENTER || i == NK_KEY_TAB) continue;
            if (nk_input_is_key_pressed(in, (enum nk_keys)i)) {
                nk_textedit_key(edit, (enum nk_keys)i, shift_mod, font, row_height);
                cursor_follow = nk_true;
            }
        }
        if (old_mode != edit->mode) {
            in->keyboard.text_len = 0;
        }}

        edit->filter = filter;
        if (in->keyboard.text_len) {
            nk_textedit_text(edit, in->keyboard.text, in->keyboard.text_len);
            cursor_follow = nk_true;
            in->keyboard.text_len = 0;
        }

        if (nk_input_is_key_pressed(in, NK_KEY_ENTER)) {
            cursor_follow = nk_true;
            if (flags & NK_EDIT_CTRL_ENTER_NEWLINE && shift_mod)
                nk_textedit_text(edit, "\n", 1);
            else if (flags & NK_EDIT_SIG_ENTER)
                ret |= NK_EDIT_COMMITED;
            else nk_textedit_text(edit, "\n", 1);
        }

        {int copy= nk_input_is_key_pressed(in, NK_KEY_COPY);
        int cut = nk_input_is_key_pressed(in, NK_KEY_CUT);
        if ((copy || cut) && (flags & NK_EDIT_CLIPBOARD))
        {
            int glyph_len;
            nk_rune unicode;
            const char *text;
            int b = edit->select_start;
            int e = edit->select_end;

            int begin = NK_MIN(b, e);
            int end = NK_MAX(b, e);
            text = nk_str_at_const(&edit->string, begin, &unicode, &glyph_len);
            if (edit->clip.copy)
                edit->clip.copy(edit->clip.userdata, text, end - begin);
            if (cut && !(flags & NK_EDIT_READ_ONLY)){
                nk_textedit_cut(edit);
                cursor_follow = nk_true;
            }
        }}

        {int paste = nk_input_is_key_pressed(in, NK_KEY_PASTE);
        if (paste && (flags & NK_EDIT_CLIPBOARD) && edit->clip.paste) {
            edit->clip.paste(edit->clip.userdata, edit);
            cursor_follow = nk_true;
        }}

        {int tab = nk_input_is_key_pressed(in, NK_KEY_TAB);
        if (tab && (flags & NK_EDIT_ALLOW_TAB)) {
            nk_textedit_text(edit, "    ", 4);
            cursor_follow = nk_true;
        }}
    }

    if (edit->active)
        *state = NK_WIDGET_STATE_ACTIVE;
    else nk_widget_state_reset(state);

    if (is_hovered)
        *state |= NK_WIDGET_STATE_HOVERED;

    {const char *text = nk_str_get_const(&edit->string);
    int len = nk_str_len_char(&edit->string);

    {
    const struct nk_style_item *background;
    if (*state & NK_WIDGET_STATE_ACTIVED)
        background = &style->active;
    else if (*state & NK_WIDGET_STATE_HOVER)
        background = &style->hover;
    else background = &style->normal;

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(out, bounds, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(out, bounds, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(out, bounds, style->rounding, background->data.color);
            nk_stroke_rect(out, bounds, style->rounding, style->border, style->border_color);
            break;
    }}

    area.w = NK_MAX(0, area.w - style->cursor_size);
    if (edit->active)
    {
        int total_lines = 1;
        struct nk_vec2 text_size = nk_vec2(0,0);

        const char *cursor_ptr = 0;
        const char *select_begin_ptr = 0;
        const char *select_end_ptr = 0;

        struct nk_vec2 cursor_pos = nk_vec2(0,0);
        struct nk_vec2 selection_offset_start = nk_vec2(0,0);
        struct nk_vec2 selection_offset_end = nk_vec2(0,0);

        int selection_begin = NK_MIN(edit->select_start, edit->select_end);
        int selection_end = NK_MAX(edit->select_start, edit->select_end);

        float line_width = 0.0f;
        if (text && len)
        {

            float glyph_width;
            int glyph_len = 0;
            nk_rune unicode = 0;
            int text_len = 0;
            int glyphs = 0;
            int row_begin = 0;

            glyph_len = nk_utf_decode(text, &unicode, len);
            glyph_width = font->width(font->userdata, font->height, text, glyph_len);
            line_width = 0;

            while ((text_len < len) && glyph_len)
            {

                if (!cursor_ptr && glyphs == edit->cursor)
                {
                    int glyph_offset;
                    struct nk_vec2 out_offset;
                    struct nk_vec2 row_size;
                    const char *remaining;

                    cursor_pos.y = (float)(total_lines-1) * row_height;
                    row_size = nk_text_calculate_text_bounds(font, text+row_begin,
                                text_len-row_begin, row_height, &remaining,
                                &out_offset, &glyph_offset, NK_STOP_ON_NEW_LINE);
                    cursor_pos.x = row_size.x;
                    cursor_ptr = text + text_len;
                }

                if (!select_begin_ptr && edit->select_start != edit->select_end &&
                    glyphs == selection_begin)
                {
                    int glyph_offset;
                    struct nk_vec2 out_offset;
                    struct nk_vec2 row_size;
                    const char *remaining;

                    selection_offset_start.y = (float)(NK_MAX(total_lines-1,0)) * row_height;
                    row_size = nk_text_calculate_text_bounds(font, text+row_begin,
                                text_len-row_begin, row_height, &remaining,
                                &out_offset, &glyph_offset, NK_STOP_ON_NEW_LINE);
                    selection_offset_start.x = row_size.x;
                    select_begin_ptr = text + text_len;
                }

                if (!select_end_ptr && edit->select_start != edit->select_end &&
                    glyphs == selection_end)
                {
                    int glyph_offset;
                    struct nk_vec2 out_offset;
                    struct nk_vec2 row_size;
                    const char *remaining;

                    selection_offset_end.y = (float)(total_lines-1) * row_height;
                    row_size = nk_text_calculate_text_bounds(font, text+row_begin,
                                text_len-row_begin, row_height, &remaining,
                                &out_offset, &glyph_offset, NK_STOP_ON_NEW_LINE);
                    selection_offset_end.x = row_size.x;
                    select_end_ptr = text + text_len;
                }
                if (unicode == '\n') {
                    text_size.x = NK_MAX(text_size.x, line_width);
                    total_lines++;
                    line_width = 0;
                    text_len++;
                    glyphs++;
                    row_begin = text_len;
                    glyph_len = nk_utf_decode(text + text_len, &unicode, len-text_len);
                    glyph_width = font->width(font->userdata, font->height, text+text_len, glyph_len);
                    continue;
                }

                glyphs++;
                text_len += glyph_len;
                line_width += (float)glyph_width;

                glyph_len = nk_utf_decode(text + text_len, &unicode, len-text_len);
                glyph_width = font->width(font->userdata, font->height,
                    text+text_len, glyph_len);
                continue;
            }
            text_size.y = (float)total_lines * row_height;

            if (!cursor_ptr && edit->cursor == edit->string.len) {
                cursor_pos.x = line_width;
                cursor_pos.y = text_size.y - row_height;
            }
        }
        {

            if (cursor_follow)
            {

                if (!(flags & NK_EDIT_NO_HORIZONTAL_SCROLL)) {

                    const float scroll_increment = area.w * 0.25f;
                    if (cursor_pos.x < edit->scrollbar.x)
                        edit->scrollbar.x = (float)(int)NK_MAX(0.0f, cursor_pos.x - scroll_increment);
                    if (cursor_pos.x >= edit->scrollbar.x + area.w)
                        edit->scrollbar.x = (float)(int)NK_MAX(0.0f, cursor_pos.x - area.w + scroll_increment);
                } else edit->scrollbar.x = 0;

                if (flags & NK_EDIT_MULTILINE) {

                    if (cursor_pos.y < edit->scrollbar.y)
                        edit->scrollbar.y = NK_MAX(0.0f, cursor_pos.y - row_height);
                    if (cursor_pos.y >= edit->scrollbar.y + row_height)
                        edit->scrollbar.y = edit->scrollbar.y + row_height;
                } else edit->scrollbar.y = 0;
            }

            if (flags & NK_EDIT_MULTILINE)
            {
                nk_flags ws;
                struct nk_rect scroll;
                float scroll_target;
                float scroll_offset;
                float scroll_step;
                float scroll_inc;

                scroll = area;
                scroll.x = (bounds.x + bounds.w - style->border) - style->scrollbar_size.x;
                scroll.w = style->scrollbar_size.x;

                scroll_offset = edit->scrollbar.y;
                scroll_step = scroll.h * 0.10f;
                scroll_inc = scroll.h * 0.01f;
                scroll_target = text_size.y;
                edit->scrollbar.y = nk_do_scrollbarv(&ws, out, scroll, 0,
                        scroll_offset, scroll_target, scroll_step, scroll_inc,
                        &style->scrollbar, in, font);
            }
        }

        {struct nk_color background_color;
        struct nk_color text_color;
        struct nk_color sel_background_color;
        struct nk_color sel_text_color;
        struct nk_color cursor_color;
        struct nk_color cursor_text_color;
        const struct nk_style_item *background;
        nk_push_scissor(out, clip);

        if (*state & NK_WIDGET_STATE_ACTIVED) {
            background = &style->active;
            text_color = style->text_active;
            sel_text_color = style->selected_text_hover;
            sel_background_color = style->selected_hover;
            cursor_color = style->cursor_hover;
            cursor_text_color = style->cursor_text_hover;
        } else if (*state & NK_WIDGET_STATE_HOVER) {
            background = &style->hover;
            text_color = style->text_hover;
            sel_text_color = style->selected_text_hover;
            sel_background_color = style->selected_hover;
            cursor_text_color = style->cursor_text_hover;
            cursor_color = style->cursor_hover;
        } else {
            background = &style->normal;
            text_color = style->text_normal;
            sel_text_color = style->selected_text_normal;
            sel_background_color = style->selected_normal;
            cursor_color = style->cursor_normal;
            cursor_text_color = style->cursor_text_normal;
        }
        if (background->type == NK_STYLE_ITEM_IMAGE)
            background_color = nk_rgba(0,0,0,0);
        else
            background_color = background->data.color;

        if (edit->select_start == edit->select_end) {

            const char *begin = nk_str_get_const(&edit->string);
            int l = nk_str_len_char(&edit->string);
            nk_edit_draw_text(out, style, area.x - edit->scrollbar.x,
                area.y - edit->scrollbar.y, 0, begin, l, row_height, font,
                background_color, text_color, nk_false);
        } else {

            if (edit->select_start != edit->select_end && selection_begin > 0){

                const char *begin = nk_str_get_const(&edit->string);
                NK_ASSERT(select_begin_ptr);
                nk_edit_draw_text(out, style, area.x - edit->scrollbar.x,
                    area.y - edit->scrollbar.y, 0, begin, (int)(select_begin_ptr - begin),
                    row_height, font, background_color, text_color, nk_false);
            }
            if (edit->select_start != edit->select_end) {

                NK_ASSERT(select_begin_ptr);
                if (!select_end_ptr) {
                    const char *begin = nk_str_get_const(&edit->string);
                    select_end_ptr = begin + nk_str_len_char(&edit->string);
                }
                nk_edit_draw_text(out, style,
                    area.x - edit->scrollbar.x,
                    area.y + selection_offset_start.y - edit->scrollbar.y,
                    selection_offset_start.x,
                    select_begin_ptr, (int)(select_end_ptr - select_begin_ptr),
                    row_height, font, sel_background_color, sel_text_color, nk_true);
            }
            if ((edit->select_start != edit->select_end &&
                selection_end < edit->string.len))
            {

                const char *begin = select_end_ptr;
                const char *end = nk_str_get_const(&edit->string) +
                                    nk_str_len_char(&edit->string);
                NK_ASSERT(select_end_ptr);
                nk_edit_draw_text(out, style,
                    area.x - edit->scrollbar.x,
                    area.y + selection_offset_end.y - edit->scrollbar.y,
                    selection_offset_end.x,
                    begin, (int)(end - begin), row_height, font,
                    background_color, text_color, nk_true);
            }
        }

        if (edit->select_start == edit->select_end)
        {
            if (edit->cursor >= nk_str_len(&edit->string) ||
                (cursor_ptr && *cursor_ptr == '\n')) {

                struct nk_rect cursor;
                cursor.w = style->cursor_size;
                cursor.h = font->height;
                cursor.x = area.x + cursor_pos.x - edit->scrollbar.x;
                cursor.y = area.y + cursor_pos.y + row_height/2.0f - cursor.h/2.0f;
                cursor.y -= edit->scrollbar.y;
                nk_fill_rect(out, cursor, 0, cursor_color);
            } else {

                int glyph_len;
                struct nk_rect label;
                struct nk_text txt;

                nk_rune unicode;
                NK_ASSERT(cursor_ptr);
                glyph_len = nk_utf_decode(cursor_ptr, &unicode, 4);

                label.x = area.x + cursor_pos.x - edit->scrollbar.x;
                label.y = area.y + cursor_pos.y - edit->scrollbar.y;
                label.w = font->width(font->userdata, font->height, cursor_ptr, glyph_len);
                label.h = row_height;

                txt.padding = nk_vec2(0,0);
                txt.background = cursor_color;;
                txt.text = cursor_text_color;
                nk_fill_rect(out, label, 0, cursor_color);
                nk_widget_text(out, label, cursor_ptr, glyph_len, &txt, NK_TEXT_LEFT, font);
            }
        }}
    } else {

        int l = nk_str_len_char(&edit->string);
        const char *begin = nk_str_get_const(&edit->string);

        const struct nk_style_item *background;
        struct nk_color background_color;
        struct nk_color text_color;
        nk_push_scissor(out, clip);
        if (*state & NK_WIDGET_STATE_ACTIVED) {
            background = &style->active;
            text_color = style->text_active;
        } else if (*state & NK_WIDGET_STATE_HOVER) {
            background = &style->hover;
            text_color = style->text_hover;
        } else {
            background = &style->normal;
            text_color = style->text_normal;
        }
        if (background->type == NK_STYLE_ITEM_IMAGE)
            background_color = nk_rgba(0,0,0,0);
        else
            background_color = background->data.color;
        nk_edit_draw_text(out, style, area.x - edit->scrollbar.x,
            area.y - edit->scrollbar.y, 0, begin, l, row_height, font,
            background_color, text_color, nk_false);
    }
    nk_push_scissor(out, old_clip);}
    return ret;
}
NK_API void
nk_edit_focus(struct nk_context *ctx, nk_flags flags)
{
    nk_hash hash;
    struct nk_window *win;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return;

    win = ctx->current;
    hash = win->edit.seq;
    win->edit.active = nk_true;
    win->edit.name = hash;
    if (flags & NK_EDIT_ALWAYS_INSERT_MODE)
        win->edit.mode = NK_TEXT_EDIT_MODE_INSERT;
}
NK_API void
nk_edit_unfocus(struct nk_context *ctx)
{
    struct nk_window *win;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return;

    win = ctx->current;
    win->edit.active = nk_false;
    win->edit.name = 0;
}
NK_API nk_flags
nk_edit_string(struct nk_context *ctx, nk_flags flags,
    char *memory, int *len, int max, nk_plugin_filter filter)
{
    nk_hash hash;
    nk_flags state;
    struct nk_text_edit *edit;
    struct nk_window *win;

    NK_ASSERT(ctx);
    NK_ASSERT(memory);
    NK_ASSERT(len);
    if (!ctx || !memory || !len)
        return 0;

    filter = (!filter) ? nk_filter_default: filter;
    win = ctx->current;
    hash = win->edit.seq;
    edit = &ctx->text_edit;
    nk_textedit_clear_state(&ctx->text_edit, (flags & NK_EDIT_MULTILINE)?
        NK_TEXT_EDIT_MULTI_LINE: NK_TEXT_EDIT_SINGLE_LINE, filter);

    if (win->edit.active && hash == win->edit.name) {
        if (flags & NK_EDIT_NO_CURSOR)
            edit->cursor = nk_utf_len(memory, *len);
        else edit->cursor = win->edit.cursor;
        if (!(flags & NK_EDIT_SELECTABLE)) {
            edit->select_start = win->edit.cursor;
            edit->select_end = win->edit.cursor;
        } else {
            edit->select_start = win->edit.sel_start;
            edit->select_end = win->edit.sel_end;
        }
        edit->mode = win->edit.mode;
        edit->scrollbar.x = (float)win->edit.scrollbar.x;
        edit->scrollbar.y = (float)win->edit.scrollbar.y;
        edit->active = nk_true;
    } else edit->active = nk_false;

    max = NK_MAX(1, max);
    *len = NK_MIN(*len, max-1);
    nk_str_init_fixed(&edit->string, memory, (nk_size)max);
    edit->string.buffer.allocated = (nk_size)*len;
    edit->string.len = nk_utf_len(memory, *len);
    state = nk_edit_buffer(ctx, flags, edit, filter);
    *len = (int)edit->string.buffer.allocated;

    if (edit->active) {
        win->edit.cursor = edit->cursor;
        win->edit.sel_start = edit->select_start;
        win->edit.sel_end = edit->select_end;
        win->edit.mode = edit->mode;
        win->edit.scrollbar.x = (nk_uint)edit->scrollbar.x;
        win->edit.scrollbar.y = (nk_uint)edit->scrollbar.y;
    } return state;
}
NK_API nk_flags
nk_edit_buffer(struct nk_context *ctx, nk_flags flags,
    struct nk_text_edit *edit, nk_plugin_filter filter)
{
    struct nk_window *win;
    struct nk_style *style;
    struct nk_input *in;

    enum nk_widget_layout_states state;
    struct nk_rect bounds;

    nk_flags ret_flags = 0;
    unsigned char prev_state;
    nk_hash hash;

    NK_ASSERT(ctx);
    NK_ASSERT(edit);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    state = nk_widget(&bounds, ctx);
    if (!state) return state;
    in = (win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;

    hash = win->edit.seq++;
    if (win->edit.active && hash == win->edit.name) {
        if (flags & NK_EDIT_NO_CURSOR)
            edit->cursor = edit->string.len;
        if (!(flags & NK_EDIT_SELECTABLE)) {
            edit->select_start = edit->cursor;
            edit->select_end = edit->cursor;
        }
        if (flags & NK_EDIT_CLIPBOARD)
            edit->clip = ctx->clip;
        edit->active = (unsigned char)win->edit.active;
    } else edit->active = nk_false;
    edit->mode = win->edit.mode;

    filter = (!filter) ? nk_filter_default: filter;
    prev_state = (unsigned char)edit->active;
    in = (flags & NK_EDIT_READ_ONLY) ? 0: in;
    ret_flags = nk_do_edit(&ctx->last_widget_state, &win->buffer, bounds, flags,
                    filter, edit, &style->edit, in, style->font);

    if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
        ctx->style.cursor_active = ctx->style.cursors[NK_CURSOR_TEXT];
    if (edit->active && prev_state != edit->active) {

        win->edit.active = nk_true;
        win->edit.name = hash;
    } else if (prev_state && !edit->active) {

        win->edit.active = nk_false;
    } return ret_flags;
}
NK_API nk_flags
nk_edit_string_zero_terminated(struct nk_context *ctx, nk_flags flags,
    char *buffer, int max, nk_plugin_filter filter)
{
    nk_flags result;
    int len = nk_strlen(buffer);
    result = nk_edit_string(ctx, flags, buffer, &len, max, filter);
    buffer[NK_MIN(NK_MAX(max-1,0), len)] = '\0';
    return result;
}

NK_LIB void
nk_drag_behavior(nk_flags *state, const struct nk_input *in,
    struct nk_rect drag, struct nk_property_variant *variant,
    float inc_per_pixel)
{
    int left_mouse_down = in && in->mouse.buttons[NK_BUTTON_LEFT].down;
    int left_mouse_click_in_cursor = in &&
        nk_input_has_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, drag, nk_true);

    nk_widget_state_reset(state);
    if (nk_input_is_mouse_hovering_rect(in, drag))
        *state = NK_WIDGET_STATE_HOVERED;

    if (left_mouse_down && left_mouse_click_in_cursor) {
        float delta, pixels;
        pixels = in->mouse.delta.x;
        delta = pixels * inc_per_pixel;
        switch (variant->kind) {
        default: break;
        case NK_PROPERTY_INT:
            variant->value.i = variant->value.i + (int)delta;
            variant->value.i = NK_CLAMP(variant->min_value.i, variant->value.i, variant->max_value.i);
            break;
        case NK_PROPERTY_FLOAT:
            variant->value.f = variant->value.f + (float)delta;
            variant->value.f = NK_CLAMP(variant->min_value.f, variant->value.f, variant->max_value.f);
            break;
        case NK_PROPERTY_DOUBLE:
            variant->value.d = variant->value.d + (double)delta;
            variant->value.d = NK_CLAMP(variant->min_value.d, variant->value.d, variant->max_value.d);
            break;
        }
        *state = NK_WIDGET_STATE_ACTIVE;
    }
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, drag))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, drag))
        *state |= NK_WIDGET_STATE_LEFT;
}
NK_LIB void
nk_property_behavior(nk_flags *ws, const struct nk_input *in,
    struct nk_rect property,  struct nk_rect label, struct nk_rect edit,
    struct nk_rect empty, int *state, struct nk_property_variant *variant,
    float inc_per_pixel)
{
    nk_widget_state_reset(ws);
    if (in && *state == NK_PROPERTY_DEFAULT) {
        if (nk_button_behavior(ws, edit, in, NK_BUTTON_DEFAULT))
            *state = NK_PROPERTY_EDIT;
        else if (nk_input_is_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, label, nk_true))
            *state = NK_PROPERTY_DRAG;
        else if (nk_input_is_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, empty, nk_true))
            *state = NK_PROPERTY_DRAG;
    }
    if (*state == NK_PROPERTY_DRAG) {
        nk_drag_behavior(ws, in, property, variant, inc_per_pixel);
        if (!(*ws & NK_WIDGET_STATE_ACTIVED)) *state = NK_PROPERTY_DEFAULT;
    }
}
NK_LIB void
nk_draw_property(struct nk_command_buffer *out, const struct nk_style_property *style,
    const struct nk_rect *bounds, const struct nk_rect *label, nk_flags state,
    const char *name, int len, const struct nk_user_font *font)
{
    struct nk_text text;
    const struct nk_style_item *background;

    if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->active;
        text.text = style->label_active;
    } else if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        text.text = style->label_hover;
    } else {
        background = &style->normal;
        text.text = style->label_normal;
    }

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_image(out, *bounds, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_nine_slice(out, *bounds, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            text.background = background->data.color;
            nk_fill_rect(out, *bounds, style->rounding, background->data.color);
            nk_stroke_rect(out, *bounds, style->rounding, style->border, background->data.color);
            break;
    }

    text.padding = nk_vec2(0,0);
    nk_widget_text(out, *label, name, len, &text, NK_TEXT_CENTERED, font);
}
NK_LIB void
nk_do_property(nk_flags *ws,
    struct nk_command_buffer *out, struct nk_rect property,
    const char *name, struct nk_property_variant *variant,
    float inc_per_pixel, char *buffer, int *len,
    int *state, int *cursor, int *select_begin, int *select_end,
    const struct nk_style_property *style,
    enum nk_property_filter filter, struct nk_input *in,
    const struct nk_user_font *font, struct nk_text_edit *text_edit,
    enum nk_button_behavior behavior)
{
    const nk_plugin_filter filters[] = {
        nk_filter_decimal,
        nk_filter_float
    };
    nk_bool active, old;
    int num_len = 0, name_len;
    char string[NK_MAX_NUMBER_BUFFER];
    float size;

    char *dst = 0;
    int *length;

    struct nk_rect left;
    struct nk_rect right;
    struct nk_rect label;
    struct nk_rect edit;
    struct nk_rect empty;

    left.h = font->height/2;
    left.w = left.h;
    left.x = property.x + style->border + style->padding.x;
    left.y = property.y + style->border + property.h/2.0f - left.h/2;

    name_len = nk_strlen(name);
    size = font->width(font->userdata, font->height, name, name_len);
    label.x = left.x + left.w + style->padding.x;
    label.w = (float)size + 2 * style->padding.x;
    label.y = property.y + style->border + style->padding.y;
    label.h = property.h - (2 * style->border + 2 * style->padding.y);

    right.y = left.y;
    right.w = left.w;
    right.h = left.h;
    right.x = property.x + property.w - (right.w + style->padding.x);

    if (*state == NK_PROPERTY_EDIT) {
        size = font->width(font->userdata, font->height, buffer, *len);
        size += style->edit.cursor_size;
        length = len;
        dst = buffer;
    } else {
        switch (variant->kind) {
        default: break;
        case NK_PROPERTY_INT:
            nk_itoa(string, variant->value.i);
            num_len = nk_strlen(string);
            break;
        case NK_PROPERTY_FLOAT:
            NK_DTOA(string, (double)variant->value.f);
            num_len = nk_string_float_limit(string, NK_MAX_FLOAT_PRECISION);
            break;
        case NK_PROPERTY_DOUBLE:
            NK_DTOA(string, variant->value.d);
            num_len = nk_string_float_limit(string, NK_MAX_FLOAT_PRECISION);
            break;
        }
        size = font->width(font->userdata, font->height, string, num_len);
        dst = string;
        length = &num_len;
    }

    edit.w =  (float)size + 2 * style->padding.x;
    edit.w = NK_MIN(edit.w, right.x - (label.x + label.w));
    edit.x = right.x - (edit.w + style->padding.x);
    edit.y = property.y + style->border;
    edit.h = property.h - (2 * style->border);

    empty.w = edit.x - (label.x + label.w);
    empty.x = label.x + label.w;
    empty.y = property.y;
    empty.h = property.h;

    old = (*state == NK_PROPERTY_EDIT);
    nk_property_behavior(ws, in, property, label, edit, empty, state, variant, inc_per_pixel);

    if (style->draw_begin) style->draw_begin(out, style->userdata);
    nk_draw_property(out, style, &property, &label, *ws, name, name_len, font);
    if (style->draw_end) style->draw_end(out, style->userdata);

    if (nk_do_button_symbol(ws, out, left, style->sym_left, behavior, &style->dec_button, in, font)) {
        switch (variant->kind) {
        default: break;
        case NK_PROPERTY_INT:
            variant->value.i = NK_CLAMP(variant->min_value.i, variant->value.i - variant->step.i, variant->max_value.i); break;
        case NK_PROPERTY_FLOAT:
            variant->value.f = NK_CLAMP(variant->min_value.f, variant->value.f - variant->step.f, variant->max_value.f); break;
        case NK_PROPERTY_DOUBLE:
            variant->value.d = NK_CLAMP(variant->min_value.d, variant->value.d - variant->step.d, variant->max_value.d); break;
        }
    }

    if (nk_do_button_symbol(ws, out, right, style->sym_right, behavior, &style->inc_button, in, font)) {
        switch (variant->kind) {
        default: break;
        case NK_PROPERTY_INT:
            variant->value.i = NK_CLAMP(variant->min_value.i, variant->value.i + variant->step.i, variant->max_value.i); break;
        case NK_PROPERTY_FLOAT:
            variant->value.f = NK_CLAMP(variant->min_value.f, variant->value.f + variant->step.f, variant->max_value.f); break;
        case NK_PROPERTY_DOUBLE:
            variant->value.d = NK_CLAMP(variant->min_value.d, variant->value.d + variant->step.d, variant->max_value.d); break;
        }
    }
    if (old != NK_PROPERTY_EDIT && (*state == NK_PROPERTY_EDIT)) {

        NK_MEMCPY(buffer, dst, (nk_size)*length);
        *cursor = nk_utf_len(buffer, *length);
        *len = *length;
        length = len;
        dst = buffer;
        active = 0;
    } else active = (*state == NK_PROPERTY_EDIT);

    nk_textedit_clear_state(text_edit, NK_TEXT_EDIT_SINGLE_LINE, filters[filter]);
    text_edit->active = (unsigned char)active;
    text_edit->string.len = *length;
    text_edit->cursor = NK_CLAMP(0, *cursor, *length);
    text_edit->select_start = NK_CLAMP(0,*select_begin, *length);
    text_edit->select_end = NK_CLAMP(0,*select_end, *length);
    text_edit->string.buffer.allocated = (nk_size)*length;
    text_edit->string.buffer.memory.size = NK_MAX_NUMBER_BUFFER;
    text_edit->string.buffer.memory.ptr = dst;
    text_edit->string.buffer.size = NK_MAX_NUMBER_BUFFER;
    text_edit->mode = NK_TEXT_EDIT_MODE_INSERT;
    nk_do_edit(ws, out, edit, NK_EDIT_FIELD|NK_EDIT_AUTO_SELECT,
        filters[filter], text_edit, &style->edit, (*state == NK_PROPERTY_EDIT) ? in: 0, font);

    *length = text_edit->string.len;
    *cursor = text_edit->cursor;
    *select_begin = text_edit->select_start;
    *select_end = text_edit->select_end;
    if (text_edit->active && nk_input_is_key_pressed(in, NK_KEY_ENTER))
        text_edit->active = nk_false;

    if (active && !text_edit->active) {

        *state = NK_PROPERTY_DEFAULT;
        buffer[*len] = '\0';
        switch (variant->kind) {
        default: break;
        case NK_PROPERTY_INT:
            variant->value.i = nk_strtoi(buffer, 0);
            variant->value.i = NK_CLAMP(variant->min_value.i, variant->value.i, variant->max_value.i);
            break;
        case NK_PROPERTY_FLOAT:
            nk_string_float_limit(buffer, NK_MAX_FLOAT_PRECISION);
            variant->value.f = nk_strtof(buffer, 0);
            variant->value.f = NK_CLAMP(variant->min_value.f, variant->value.f, variant->max_value.f);
            break;
        case NK_PROPERTY_DOUBLE:
            nk_string_float_limit(buffer, NK_MAX_FLOAT_PRECISION);
            variant->value.d = nk_strtod(buffer, 0);
            variant->value.d = NK_CLAMP(variant->min_value.d, variant->value.d, variant->max_value.d);
            break;
        }
    }
}
NK_LIB struct nk_property_variant
nk_property_variant_int(int value, int min_value, int max_value, int step)
{
    struct nk_property_variant result;
    result.kind = NK_PROPERTY_INT;
    result.value.i = value;
    result.min_value.i = min_value;
    result.max_value.i = max_value;
    result.step.i = step;
    return result;
}
NK_LIB struct nk_property_variant
nk_property_variant_float(float value, float min_value, float max_value, float step)
{
    struct nk_property_variant result;
    result.kind = NK_PROPERTY_FLOAT;
    result.value.f = value;
    result.min_value.f = min_value;
    result.max_value.f = max_value;
    result.step.f = step;
    return result;
}
NK_LIB struct nk_property_variant
nk_property_variant_double(double value, double min_value, double max_value,
    double step)
{
    struct nk_property_variant result;
    result.kind = NK_PROPERTY_DOUBLE;
    result.value.d = value;
    result.min_value.d = min_value;
    result.max_value.d = max_value;
    result.step.d = step;
    return result;
}
NK_LIB void
nk_property(struct nk_context *ctx, const char *name, struct nk_property_variant *variant,
    float inc_per_pixel, const enum nk_property_filter filter)
{
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states s;

    int *state = 0;
    nk_hash hash = 0;
    char *buffer = 0;
    int *len = 0;
    int *cursor = 0;
    int *select_begin = 0;
    int *select_end = 0;
    int old_state;

    char dummy_buffer[NK_MAX_NUMBER_BUFFER];
    int dummy_state = NK_PROPERTY_DEFAULT;
    int dummy_length = 0;
    int dummy_cursor = 0;
    int dummy_select_begin = 0;
    int dummy_select_end = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    style = &ctx->style;
    s = nk_widget(&bounds, ctx);
    if (!s) return;

    if (name[0] == '#') {
        hash = nk_murmur_hash(name, (int)nk_strlen(name), win->property.seq++);
        name++;
    } else hash = nk_murmur_hash(name, (int)nk_strlen(name), 42);

    if (win->property.active && hash == win->property.name) {
        buffer = win->property.buffer;
        len = &win->property.length;
        cursor = &win->property.cursor;
        state = &win->property.state;
        select_begin = &win->property.select_start;
        select_end = &win->property.select_end;
    } else {
        buffer = dummy_buffer;
        len = &dummy_length;
        cursor = &dummy_cursor;
        state = &dummy_state;
        select_begin =  &dummy_select_begin;
        select_end = &dummy_select_end;
    }

    old_state = *state;
    ctx->text_edit.clip = ctx->clip;
    in = ((s == NK_WIDGET_ROM && !win->property.active) ||
        layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    nk_do_property(&ctx->last_widget_state, &win->buffer, bounds, name,
        variant, inc_per_pixel, buffer, len, state, cursor, select_begin,
        select_end, &style->property, filter, in, style->font, &ctx->text_edit,
        ctx->button_behavior);

    if (in && *state != NK_PROPERTY_DEFAULT && !win->property.active) {

        win->property.active = 1;
        NK_MEMCPY(win->property.buffer, buffer, (nk_size)*len);
        win->property.length = *len;
        win->property.cursor = *cursor;
        win->property.state = *state;
        win->property.name = hash;
        win->property.select_start = *select_begin;
        win->property.select_end = *select_end;
        if (*state == NK_PROPERTY_DRAG) {
            ctx->input.mouse.grab = nk_true;
            ctx->input.mouse.grabbed = nk_true;
        }
    }

    if (*state == NK_PROPERTY_DEFAULT && old_state != NK_PROPERTY_DEFAULT) {
        if (old_state == NK_PROPERTY_DRAG) {
            ctx->input.mouse.grab = nk_false;
            ctx->input.mouse.grabbed = nk_false;
            ctx->input.mouse.ungrab = nk_true;
        }
        win->property.select_start = 0;
        win->property.select_end = 0;
        win->property.active = 0;
    }
}
NK_API void
nk_property_int(struct nk_context *ctx, const char *name,
    int min, int *val, int max, int step, float inc_per_pixel)
{
    struct nk_property_variant variant;
    NK_ASSERT(ctx);
    NK_ASSERT(name);
    NK_ASSERT(val);

    if (!ctx || !ctx->current || !name || !val) return;
    variant = nk_property_variant_int(*val, min, max, step);
    nk_property(ctx, name, &variant, inc_per_pixel, NK_FILTER_INT);
    *val = variant.value.i;
}
NK_API void
nk_property_float(struct nk_context *ctx, const char *name,
    float min, float *val, float max, float step, float inc_per_pixel)
{
    struct nk_property_variant variant;
    NK_ASSERT(ctx);
    NK_ASSERT(name);
    NK_ASSERT(val);

    if (!ctx || !ctx->current || !name || !val) return;
    variant = nk_property_variant_float(*val, min, max, step);
    nk_property(ctx, name, &variant, inc_per_pixel, NK_FILTER_FLOAT);
    *val = variant.value.f;
}
NK_API void
nk_property_double(struct nk_context *ctx, const char *name,
    double min, double *val, double max, double step, float inc_per_pixel)
{
    struct nk_property_variant variant;
    NK_ASSERT(ctx);
    NK_ASSERT(name);
    NK_ASSERT(val);

    if (!ctx || !ctx->current || !name || !val) return;
    variant = nk_property_variant_double(*val, min, max, step);
    nk_property(ctx, name, &variant, inc_per_pixel, NK_FILTER_FLOAT);
    *val = variant.value.d;
}
NK_API int
nk_propertyi(struct nk_context *ctx, const char *name, int min, int val,
    int max, int step, float inc_per_pixel)
{
    struct nk_property_variant variant;
    NK_ASSERT(ctx);
    NK_ASSERT(name);

    if (!ctx || !ctx->current || !name) return val;
    variant = nk_property_variant_int(val, min, max, step);
    nk_property(ctx, name, &variant, inc_per_pixel, NK_FILTER_INT);
    val = variant.value.i;
    return val;
}
NK_API float
nk_propertyf(struct nk_context *ctx, const char *name, float min,
    float val, float max, float step, float inc_per_pixel)
{
    struct nk_property_variant variant;
    NK_ASSERT(ctx);
    NK_ASSERT(name);

    if (!ctx || !ctx->current || !name) return val;
    variant = nk_property_variant_float(val, min, max, step);
    nk_property(ctx, name, &variant, inc_per_pixel, NK_FILTER_FLOAT);
    val = variant.value.f;
    return val;
}
NK_API double
nk_propertyd(struct nk_context *ctx, const char *name, double min,
    double val, double max, double step, float inc_per_pixel)
{
    struct nk_property_variant variant;
    NK_ASSERT(ctx);
    NK_ASSERT(name);

    if (!ctx || !ctx->current || !name) return val;
    variant = nk_property_variant_double(val, min, max, step);
    nk_property(ctx, name, &variant, inc_per_pixel, NK_FILTER_FLOAT);
    val = variant.value.d;
    return val;
}

NK_API nk_bool
nk_chart_begin_colored(struct nk_context *ctx, enum nk_chart_type type,
    struct nk_color color, struct nk_color highlight,
    int count, float min_value, float max_value)
{
    struct nk_window *win;
    struct nk_chart *chart;
    const struct nk_style *config;
    const struct nk_style_chart *style;

    const struct nk_style_item *background;
    struct nk_rect bounds = {0, 0, 0, 0};

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);

    if (!ctx || !ctx->current || !ctx->current->layout) return 0;
    if (!nk_widget(&bounds, ctx)) {
        chart = &ctx->current->layout->chart;
        nk_zero(chart, sizeof(*chart));
        return 0;
    }

    win = ctx->current;
    config = &ctx->style;
    chart = &win->layout->chart;
    style = &config->chart;

    nk_zero(chart, sizeof(*chart));
    chart->x = bounds.x + style->padding.x;
    chart->y = bounds.y + style->padding.y;
    chart->w = bounds.w - 2 * style->padding.x;
    chart->h = bounds.h - 2 * style->padding.y;
    chart->w = NK_MAX(chart->w, 2 * style->padding.x);
    chart->h = NK_MAX(chart->h, 2 * style->padding.y);

    {struct nk_chart_slot *slot = &chart->slots[chart->slot++];
    slot->type = type;
    slot->count = count;
    slot->color = color;
    slot->highlight = highlight;
    slot->min = NK_MIN(min_value, max_value);
    slot->max = NK_MAX(min_value, max_value);
    slot->range = slot->max - slot->min;}

    background = &style->background;

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(&win->buffer, bounds, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(&win->buffer, bounds, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(&win->buffer, bounds, style->rounding, style->border_color);
            nk_fill_rect(&win->buffer, nk_shrink_rect(bounds, style->border),
                style->rounding, style->background.data.color);
            break;
    }
    return 1;
}
NK_API nk_bool
nk_chart_begin(struct nk_context *ctx, const enum nk_chart_type type,
    int count, float min_value, float max_value)
{
    return nk_chart_begin_colored(ctx, type, ctx->style.chart.color,
                ctx->style.chart.selected_color, count, min_value, max_value);
}
NK_API void
nk_chart_add_slot_colored(struct nk_context *ctx, const enum nk_chart_type type,
    struct nk_color color, struct nk_color highlight,
    int count, float min_value, float max_value)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    NK_ASSERT(ctx->current->layout->chart.slot < NK_CHART_MAX_SLOT);
    if (!ctx || !ctx->current || !ctx->current->layout) return;
    if (ctx->current->layout->chart.slot >= NK_CHART_MAX_SLOT) return;

    {struct nk_chart *chart = &ctx->current->layout->chart;
    struct nk_chart_slot *slot = &chart->slots[chart->slot++];
    slot->type = type;
    slot->count = count;
    slot->color = color;
    slot->highlight = highlight;
    slot->min = NK_MIN(min_value, max_value);
    slot->max = NK_MAX(min_value, max_value);
    slot->range = slot->max - slot->min;}
}
NK_API void
nk_chart_add_slot(struct nk_context *ctx, const enum nk_chart_type type,
    int count, float min_value, float max_value)
{
    nk_chart_add_slot_colored(ctx, type, ctx->style.chart.color,
        ctx->style.chart.selected_color, count, min_value, max_value);
}
NK_INTERN nk_flags
nk_chart_push_line(struct nk_context *ctx, struct nk_window *win,
    struct nk_chart *g, float value, int slot)
{
    struct nk_panel *layout = win->layout;
    const struct nk_input *i = &ctx->input;
    struct nk_command_buffer *out = &win->buffer;

    nk_flags ret = 0;
    struct nk_vec2 cur;
    struct nk_rect bounds;
    struct nk_color color;
    float step;
    float range;
    float ratio;

    NK_ASSERT(slot >= 0 && slot < NK_CHART_MAX_SLOT);
    step = g->w / (float)g->slots[slot].count;
    range = g->slots[slot].max - g->slots[slot].min;
    ratio = (value - g->slots[slot].min) / range;

    if (g->slots[slot].index == 0) {

        g->slots[slot].last.x = g->x;
        g->slots[slot].last.y = (g->y + g->h) - ratio * (float)g->h;

        bounds.x = g->slots[slot].last.x - 2;
        bounds.y = g->slots[slot].last.y - 2;
        bounds.w = bounds.h = 4;

        color = g->slots[slot].color;
        if (!(layout->flags & NK_WINDOW_ROM) &&
            NK_INBOX(i->mouse.pos.x,i->mouse.pos.y, g->slots[slot].last.x-3, g->slots[slot].last.y-3, 6, 6)){
            ret = nk_input_is_mouse_hovering_rect(i, bounds) ? NK_CHART_HOVERING : 0;
            ret |= (i->mouse.buttons[NK_BUTTON_LEFT].down &&
                i->mouse.buttons[NK_BUTTON_LEFT].clicked) ? NK_CHART_CLICKED: 0;
            color = g->slots[slot].highlight;
        }
        nk_fill_rect(out, bounds, 0, color);
        g->slots[slot].index += 1;
        return ret;
    }

    color = g->slots[slot].color;
    cur.x = g->x + (float)(step * (float)g->slots[slot].index);
    cur.y = (g->y + g->h) - (ratio * (float)g->h);
    nk_stroke_line(out, g->slots[slot].last.x, g->slots[slot].last.y, cur.x, cur.y, 1.0f, color);

    bounds.x = cur.x - 3;
    bounds.y = cur.y - 3;
    bounds.w = bounds.h = 6;

    if (!(layout->flags & NK_WINDOW_ROM)) {
        if (nk_input_is_mouse_hovering_rect(i, bounds)) {
            ret = NK_CHART_HOVERING;
            ret |= (!i->mouse.buttons[NK_BUTTON_LEFT].down &&
                i->mouse.buttons[NK_BUTTON_LEFT].clicked) ? NK_CHART_CLICKED: 0;
            color = g->slots[slot].highlight;
        }
    }
    nk_fill_rect(out, nk_rect(cur.x - 2, cur.y - 2, 4, 4), 0, color);

    g->slots[slot].last.x = cur.x;
    g->slots[slot].last.y = cur.y;
    g->slots[slot].index  += 1;
    return ret;
}
NK_INTERN nk_flags
nk_chart_push_column(const struct nk_context *ctx, struct nk_window *win,
    struct nk_chart *chart, float value, int slot)
{
    struct nk_command_buffer *out = &win->buffer;
    const struct nk_input *in = &ctx->input;
    struct nk_panel *layout = win->layout;

    float ratio;
    nk_flags ret = 0;
    struct nk_color color;
    struct nk_rect item = {0,0,0,0};

    NK_ASSERT(slot >= 0 && slot < NK_CHART_MAX_SLOT);
    if (chart->slots[slot].index  >= chart->slots[slot].count)
        return nk_false;
    if (chart->slots[slot].count) {
        float padding = (float)(chart->slots[slot].count-1);
        item.w = (chart->w - padding) / (float)(chart->slots[slot].count);
    }

    color = chart->slots[slot].color;;
    item.h = chart->h * NK_ABS((value/chart->slots[slot].range));
    if (value >= 0) {
        ratio = (value + NK_ABS(chart->slots[slot].min)) / NK_ABS(chart->slots[slot].range);
        item.y = (chart->y + chart->h) - chart->h * ratio;
    } else {
        ratio = (value - chart->slots[slot].max) / chart->slots[slot].range;
        item.y = chart->y + (chart->h * NK_ABS(ratio)) - item.h;
    }
    item.x = chart->x + ((float)chart->slots[slot].index * item.w);
    item.x = item.x + ((float)chart->slots[slot].index);

    if (!(layout->flags & NK_WINDOW_ROM) &&
        NK_INBOX(in->mouse.pos.x,in->mouse.pos.y,item.x,item.y,item.w,item.h)) {
        ret = NK_CHART_HOVERING;
        ret |= (!in->mouse.buttons[NK_BUTTON_LEFT].down &&
                in->mouse.buttons[NK_BUTTON_LEFT].clicked) ? NK_CHART_CLICKED: 0;
        color = chart->slots[slot].highlight;
    }
    nk_fill_rect(out, item, 0, color);
    chart->slots[slot].index += 1;
    return ret;
}
NK_API nk_flags
nk_chart_push_slot(struct nk_context *ctx, float value, int slot)
{
    nk_flags flags;
    struct nk_window *win;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(slot >= 0 && slot < NK_CHART_MAX_SLOT);
    NK_ASSERT(slot < ctx->current->layout->chart.slot);
    if (!ctx || !ctx->current || slot >= NK_CHART_MAX_SLOT) return nk_false;
    if (slot >= ctx->current->layout->chart.slot) return nk_false;

    win = ctx->current;
    if (win->layout->chart.slot < slot) return nk_false;
    switch (win->layout->chart.slots[slot].type) {
    case NK_CHART_LINES:
        flags = nk_chart_push_line(ctx, win, &win->layout->chart, value, slot); break;
    case NK_CHART_COLUMN:
        flags = nk_chart_push_column(ctx, win, &win->layout->chart, value, slot); break;
    default:
    case NK_CHART_MAX:
        flags = 0;
    }
    return flags;
}
NK_API nk_flags
nk_chart_push(struct nk_context *ctx, float value)
{
    return nk_chart_push_slot(ctx, value, 0);
}
NK_API void
nk_chart_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_chart *chart;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return;

    win = ctx->current;
    chart = &win->layout->chart;
    NK_MEMSET(chart, 0, sizeof(*chart));
    return;
}
NK_API void
nk_plot(struct nk_context *ctx, enum nk_chart_type type, const float *values,
    int count, int offset)
{
    int i = 0;
    float min_value;
    float max_value;

    NK_ASSERT(ctx);
    NK_ASSERT(values);
    if (!ctx || !values || !count) return;

    min_value = values[offset];
    max_value = values[offset];
    for (i = 0; i < count; ++i) {
        min_value = NK_MIN(values[i + offset], min_value);
        max_value = NK_MAX(values[i + offset], max_value);
    }

    if (nk_chart_begin(ctx, type, count, min_value, max_value)) {
        for (i = 0; i < count; ++i)
            nk_chart_push(ctx, values[i + offset]);
        nk_chart_end(ctx);
    }
}
NK_API void
nk_plot_function(struct nk_context *ctx, enum nk_chart_type type, void *userdata,
    float(*value_getter)(void* user, int index), int count, int offset)
{
    int i = 0;
    float min_value;
    float max_value;

    NK_ASSERT(ctx);
    NK_ASSERT(value_getter);
    if (!ctx || !value_getter || !count) return;

    max_value = min_value = value_getter(userdata, offset);
    for (i = 0; i < count; ++i) {
        float value = value_getter(userdata, i + offset);
        min_value = NK_MIN(value, min_value);
        max_value = NK_MAX(value, max_value);
    }

    if (nk_chart_begin(ctx, type, count, min_value, max_value)) {
        for (i = 0; i < count; ++i)
            nk_chart_push(ctx, value_getter(userdata, i + offset));
        nk_chart_end(ctx);
    }
}

NK_LIB nk_bool
nk_color_picker_behavior(nk_flags *state,
    const struct nk_rect *bounds, const struct nk_rect *matrix,
    const struct nk_rect *hue_bar, const struct nk_rect *alpha_bar,
    struct nk_colorf *color, const struct nk_input *in)
{
    float hsva[4];
    nk_bool value_changed = 0;
    nk_bool hsv_changed = 0;

    NK_ASSERT(state);
    NK_ASSERT(matrix);
    NK_ASSERT(hue_bar);
    NK_ASSERT(color);

    nk_colorf_hsva_fv(hsva, *color);
    if (nk_button_behavior(state, *matrix, in, NK_BUTTON_REPEATER)) {
        hsva[1] = NK_SATURATE((in->mouse.pos.x - matrix->x) / (matrix->w-1));
        hsva[2] = 1.0f - NK_SATURATE((in->mouse.pos.y - matrix->y) / (matrix->h-1));
        value_changed = hsv_changed = 1;
    }

    if (nk_button_behavior(state, *hue_bar, in, NK_BUTTON_REPEATER)) {
        hsva[0] = NK_SATURATE((in->mouse.pos.y - hue_bar->y) / (hue_bar->h-1));
        value_changed = hsv_changed = 1;
    }

    if (alpha_bar) {
        if (nk_button_behavior(state, *alpha_bar, in, NK_BUTTON_REPEATER)) {
            hsva[3] = 1.0f - NK_SATURATE((in->mouse.pos.y - alpha_bar->y) / (alpha_bar->h-1));
            value_changed = 1;
        }
    }
    nk_widget_state_reset(state);
    if (hsv_changed) {
        *color = nk_hsva_colorfv(hsva);
        *state = NK_WIDGET_STATE_ACTIVE;
    }
    if (value_changed) {
        color->a = hsva[3];
        *state = NK_WIDGET_STATE_ACTIVE;
    }

    if (nk_input_is_mouse_hovering_rect(in, *bounds))
        *state = NK_WIDGET_STATE_HOVERED;
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, *bounds))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, *bounds))
        *state |= NK_WIDGET_STATE_LEFT;
    return value_changed;
}
NK_LIB void
nk_draw_color_picker(struct nk_command_buffer *o, const struct nk_rect *matrix,
    const struct nk_rect *hue_bar, const struct nk_rect *alpha_bar,
    struct nk_colorf col)
{
    NK_STORAGE const struct nk_color black = {0,0,0,255};
    NK_STORAGE const struct nk_color white = {255, 255, 255, 255};
    NK_STORAGE const struct nk_color black_trans = {0,0,0,0};

    const float crosshair_size = 7.0f;
    struct nk_color temp;
    float hsva[4];
    float line_y;
    int i;

    NK_ASSERT(o);
    NK_ASSERT(matrix);
    NK_ASSERT(hue_bar);

    nk_colorf_hsva_fv(hsva, col);
    for (i = 0; i < 6; ++i) {
        NK_GLOBAL const struct nk_color hue_colors[] = {
            {255, 0, 0, 255}, {255,255,0,255}, {0,255,0,255}, {0, 255,255,255},
            {0,0,255,255}, {255, 0, 255, 255}, {255, 0, 0, 255}
        };
        nk_fill_rect_multi_color(o,
            nk_rect(hue_bar->x, hue_bar->y + (float)i * (hue_bar->h/6.0f) + 0.5f,
                hue_bar->w, (hue_bar->h/6.0f) + 0.5f), hue_colors[i], hue_colors[i],
                hue_colors[i+1], hue_colors[i+1]);
    }
    line_y = (float)(int)(hue_bar->y + hsva[0] * matrix->h + 0.5f);
    nk_stroke_line(o, hue_bar->x-1, line_y, hue_bar->x + hue_bar->w + 2,
        line_y, 1, nk_rgb(255,255,255));

    if (alpha_bar) {
        float alpha = NK_SATURATE(col.a);
        line_y = (float)(int)(alpha_bar->y +  (1.0f - alpha) * matrix->h + 0.5f);

        nk_fill_rect_multi_color(o, *alpha_bar, white, white, black, black);
        nk_stroke_line(o, alpha_bar->x-1, line_y, alpha_bar->x + alpha_bar->w + 2,
            line_y, 1, nk_rgb(255,255,255));
    }

    temp = nk_hsv_f(hsva[0], 1.0f, 1.0f);
    nk_fill_rect_multi_color(o, *matrix, white, temp, temp, white);
    nk_fill_rect_multi_color(o, *matrix, black_trans, black_trans, black, black);

    {struct nk_vec2 p; float S = hsva[1]; float V = hsva[2];
    p.x = (float)(int)(matrix->x + S * matrix->w);
    p.y = (float)(int)(matrix->y + (1.0f - V) * matrix->h);
    nk_stroke_line(o, p.x - crosshair_size, p.y, p.x-2, p.y, 1.0f, white);
    nk_stroke_line(o, p.x + crosshair_size + 1, p.y, p.x+3, p.y, 1.0f, white);
    nk_stroke_line(o, p.x, p.y + crosshair_size + 1, p.x, p.y+3, 1.0f, white);
    nk_stroke_line(o, p.x, p.y - crosshair_size, p.x, p.y-2, 1.0f, white);}
}
NK_LIB nk_bool
nk_do_color_picker(nk_flags *state,
    struct nk_command_buffer *out, struct nk_colorf *col,
    enum nk_color_format fmt, struct nk_rect bounds,
    struct nk_vec2 padding, const struct nk_input *in,
    const struct nk_user_font *font)
{
    int ret = 0;
    struct nk_rect matrix;
    struct nk_rect hue_bar;
    struct nk_rect alpha_bar;
    float bar_w;

    NK_ASSERT(out);
    NK_ASSERT(col);
    NK_ASSERT(state);
    NK_ASSERT(font);
    if (!out || !col || !state || !font)
        return ret;

    bar_w = font->height;
    bounds.x += padding.x;
    bounds.y += padding.x;
    bounds.w -= 2 * padding.x;
    bounds.h -= 2 * padding.y;

    matrix.x = bounds.x;
    matrix.y = bounds.y;
    matrix.h = bounds.h;
    matrix.w = bounds.w - (3 * padding.x + 2 * bar_w);

    hue_bar.w = bar_w;
    hue_bar.y = bounds.y;
    hue_bar.h = matrix.h;
    hue_bar.x = matrix.x + matrix.w + padding.x;

    alpha_bar.x = hue_bar.x + hue_bar.w + padding.x;
    alpha_bar.y = bounds.y;
    alpha_bar.w = bar_w;
    alpha_bar.h = matrix.h;

    ret = nk_color_picker_behavior(state, &bounds, &matrix, &hue_bar,
        (fmt == NK_RGBA) ? &alpha_bar:0, col, in);
    nk_draw_color_picker(out, &matrix, &hue_bar, (fmt == NK_RGBA) ? &alpha_bar:0, *col);
    return ret;
}
NK_API nk_bool
nk_color_pick(struct nk_context * ctx, struct nk_colorf *color,
    enum nk_color_format fmt)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_style *config;
    const struct nk_input *in;

    enum nk_widget_layout_states state;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(color);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !color)
        return 0;

    win = ctx->current;
    config = &ctx->style;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_color_picker(&ctx->last_widget_state, &win->buffer, color, fmt, bounds,
                nk_vec2(0,0), in, config->font);
}
NK_API struct nk_colorf
nk_color_picker(struct nk_context *ctx, struct nk_colorf color,
    enum nk_color_format fmt)
{
    nk_color_pick(ctx, &color, fmt);
    return color;
}

NK_INTERN nk_bool
nk_combo_begin(struct nk_context *ctx, struct nk_window *win,
    struct nk_vec2 size, nk_bool is_clicked, struct nk_rect header)
{
    struct nk_window *popup;
    int is_open = 0;
    int is_active = 0;
    struct nk_rect body;
    nk_hash hash;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    popup = win->popup.win;
    body.x = header.x;
    body.w = size.x;
    body.y = header.y + header.h-ctx->style.window.combo_border;
    body.h = size.y;

    hash = win->popup.combo_count++;
    is_open = (popup) ? nk_true:nk_false;
    is_active = (popup && (win->popup.name == hash) && win->popup.type == NK_PANEL_COMBO);
    if ((is_clicked && is_open && !is_active) || (is_open && !is_active) ||
        (!is_open && !is_active && !is_clicked)) return 0;
    if (!nk_nonblock_begin(ctx, 0, body,
        (is_clicked && is_open)?nk_rect(0,0,0,0):header, NK_PANEL_COMBO)) return 0;

    win->popup.type = NK_PANEL_COMBO;
    win->popup.name = hash;
    return 1;
}
NK_API nk_bool
nk_combo_begin_text(struct nk_context *ctx, const char *selected, int len,
    struct nk_vec2 size)
{
    const struct nk_input *in;
    struct nk_window *win;
    struct nk_style *style;

    enum nk_widget_layout_states s;
    int is_clicked = nk_false;
    struct nk_rect header;
    const struct nk_style_item *background;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(selected);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !selected)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (s == NK_WIDGET_INVALID)
        return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->combo.active;
        text.text = style->combo.label_active;
    } else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER) {
        background = &style->combo.hover;
        text.text = style->combo.label_hover;
    } else {
        background = &style->combo.normal;
        text.text = style->combo.label_normal;
    }

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_image(&win->buffer, header, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_nine_slice(&win->buffer, header, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            text.background = background->data.color;
            nk_fill_rect(&win->buffer, header, style->combo.rounding, background->data.color);
            nk_stroke_rect(&win->buffer, header, style->combo.rounding, style->combo.border, style->combo.border_color);
            break;
    }
    {

        struct nk_rect label;
        struct nk_rect button;
        struct nk_rect content;
        int draw_button_symbol;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else
            sym = style->combo.sym_normal;

        draw_button_symbol = sym != NK_SYMBOL_NONE;

        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.x;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;

        text.padding = nk_vec2(0,0);
        label.x = header.x + style->combo.content_padding.x;
        label.y = header.y + style->combo.content_padding.y;
        label.h = header.h - 2 * style->combo.content_padding.y;
        if (draw_button_symbol)
            label.w = button.x - (style->combo.content_padding.x + style->combo.spacing.x) - label.x;
        else
            label.w = header.w - 2 * style->combo.content_padding.x;
        nk_widget_text(&win->buffer, label, selected, len, &text,
            NK_TEXT_LEFT, ctx->style.font);

        if (draw_button_symbol)
            nk_draw_button_symbol(&win->buffer, &button, &content, ctx->last_widget_state,
                &ctx->style.combo.button, sym, style->font);
    }
    return nk_combo_begin(ctx, win, size, is_clicked, header);
}
NK_API nk_bool
nk_combo_begin_label(struct nk_context *ctx, const char *selected, struct nk_vec2 size)
{
    return nk_combo_begin_text(ctx, selected, nk_strlen(selected), size);
}
NK_API nk_bool
nk_combo_begin_color(struct nk_context *ctx, struct nk_color color, struct nk_vec2 size)
{
    struct nk_window *win;
    struct nk_style *style;
    const struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (s == NK_WIDGET_INVALID)
        return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED)
        background = &style->combo.active;
    else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
        background = &style->combo.hover;
    else background = &style->combo.normal;

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(&win->buffer, header, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(&win->buffer, header, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(&win->buffer, header, style->combo.rounding, background->data.color);
            nk_stroke_rect(&win->buffer, header, style->combo.rounding, style->combo.border, style->combo.border_color);
            break;
    }
    {
        struct nk_rect content;
        struct nk_rect button;
        struct nk_rect bounds;
        int draw_button_symbol;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        draw_button_symbol = sym != NK_SYMBOL_NONE;

        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.x;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;

        bounds.h = header.h - 4 * style->combo.content_padding.y;
        bounds.y = header.y + 2 * style->combo.content_padding.y;
        bounds.x = header.x + 2 * style->combo.content_padding.x;
        if (draw_button_symbol)
            bounds.w = (button.x - (style->combo.content_padding.x + style->combo.spacing.x)) - bounds.x;
        else
            bounds.w = header.w - 4 * style->combo.content_padding.x;
        nk_fill_rect(&win->buffer, bounds, 0, color);

        if (draw_button_symbol)
            nk_draw_button_symbol(&win->buffer, &button, &content, ctx->last_widget_state,
                &ctx->style.combo.button, sym, style->font);
    }
    return nk_combo_begin(ctx, win, size, is_clicked, header);
}
NK_API nk_bool
nk_combo_begin_symbol(struct nk_context *ctx, enum nk_symbol_type symbol, struct nk_vec2 size)
{
    struct nk_window *win;
    struct nk_style *style;
    const struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;
    struct nk_color sym_background;
    struct nk_color symbol_color;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (s == NK_WIDGET_INVALID)
        return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->combo.active;
        symbol_color = style->combo.symbol_active;
    } else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER) {
        background = &style->combo.hover;
        symbol_color = style->combo.symbol_hover;
    } else {
        background = &style->combo.normal;
        symbol_color = style->combo.symbol_hover;
    }

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            sym_background = nk_rgba(0, 0, 0, 0);
            nk_draw_image(&win->buffer, header, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            sym_background = nk_rgba(0, 0, 0, 0);
            nk_draw_nine_slice(&win->buffer, header, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            sym_background = background->data.color;
            nk_fill_rect(&win->buffer, header, style->combo.rounding, background->data.color);
            nk_stroke_rect(&win->buffer, header, style->combo.rounding, style->combo.border, style->combo.border_color);
            break;
    }
    {
        struct nk_rect bounds = {0,0,0,0};
        struct nk_rect content;
        struct nk_rect button;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.y;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;

        bounds.h = header.h - 2 * style->combo.content_padding.y;
        bounds.y = header.y + style->combo.content_padding.y;
        bounds.x = header.x + style->combo.content_padding.x;
        bounds.w = (button.x - style->combo.content_padding.y) - bounds.x;
        nk_draw_symbol(&win->buffer, symbol, bounds, sym_background, symbol_color,
            1.0f, style->font);

        nk_draw_button_symbol(&win->buffer, &bounds, &content, ctx->last_widget_state,
            &ctx->style.combo.button, sym, style->font);
    }
    return nk_combo_begin(ctx, win, size, is_clicked, header);
}
NK_API nk_bool
nk_combo_begin_symbol_text(struct nk_context *ctx, const char *selected, int len,
    enum nk_symbol_type symbol, struct nk_vec2 size)
{
    struct nk_window *win;
    struct nk_style *style;
    struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;
    struct nk_color symbol_color;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (!s) return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->combo.active;
        symbol_color = style->combo.symbol_active;
        text.text = style->combo.label_active;
    } else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER) {
        background = &style->combo.hover;
        symbol_color = style->combo.symbol_hover;
        text.text = style->combo.label_hover;
    } else {
        background = &style->combo.normal;
        symbol_color = style->combo.symbol_normal;
        text.text = style->combo.label_normal;
    }

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_image(&win->buffer, header, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_nine_slice(&win->buffer, header, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            text.background = background->data.color;
            nk_fill_rect(&win->buffer, header, style->combo.rounding, background->data.color);
            nk_stroke_rect(&win->buffer, header, style->combo.rounding, style->combo.border, style->combo.border_color);
            break;
    }
    {
        struct nk_rect content;
        struct nk_rect button;
        struct nk_rect label;
        struct nk_rect image;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.x;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;
        nk_draw_button_symbol(&win->buffer, &button, &content, ctx->last_widget_state,
            &ctx->style.combo.button, sym, style->font);

        image.x = header.x + style->combo.content_padding.x;
        image.y = header.y + style->combo.content_padding.y;
        image.h = header.h - 2 * style->combo.content_padding.y;
        image.w = image.h;
        nk_draw_symbol(&win->buffer, symbol, image, text.background, symbol_color,
            1.0f, style->font);

        text.padding = nk_vec2(0,0);
        label.x = image.x + image.w + style->combo.spacing.x + style->combo.content_padding.x;
        label.y = header.y + style->combo.content_padding.y;
        label.w = (button.x - style->combo.content_padding.x) - label.x;
        label.h = header.h - 2 * style->combo.content_padding.y;
        nk_widget_text(&win->buffer, label, selected, len, &text, NK_TEXT_LEFT, style->font);
    }
    return nk_combo_begin(ctx, win, size, is_clicked, header);
}
NK_API nk_bool
nk_combo_begin_image(struct nk_context *ctx, struct nk_image img, struct nk_vec2 size)
{
    struct nk_window *win;
    struct nk_style *style;
    const struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (s == NK_WIDGET_INVALID)
        return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED)
        background = &style->combo.active;
    else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
        background = &style->combo.hover;
    else background = &style->combo.normal;

    switch (background->type) {
        case NK_STYLE_ITEM_IMAGE:
            nk_draw_image(&win->buffer, header, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            nk_draw_nine_slice(&win->buffer, header, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            nk_fill_rect(&win->buffer, header, style->combo.rounding, background->data.color);
            nk_stroke_rect(&win->buffer, header, style->combo.rounding, style->combo.border, style->combo.border_color);
            break;
    }
    {
        struct nk_rect bounds = {0,0,0,0};
        struct nk_rect content;
        struct nk_rect button;
        int draw_button_symbol;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        draw_button_symbol = sym != NK_SYMBOL_NONE;

        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.y;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;

        bounds.h = header.h - 2 * style->combo.content_padding.y;
        bounds.y = header.y + style->combo.content_padding.y;
        bounds.x = header.x + style->combo.content_padding.x;
        if (draw_button_symbol)
            bounds.w = (button.x - style->combo.content_padding.y) - bounds.x;
        else
            bounds.w = header.w - 2 * style->combo.content_padding.x;
        nk_draw_image(&win->buffer, bounds, &img, nk_white);

        if (draw_button_symbol)
            nk_draw_button_symbol(&win->buffer, &bounds, &content, ctx->last_widget_state,
                &ctx->style.combo.button, sym, style->font);
    }
    return nk_combo_begin(ctx, win, size, is_clicked, header);
}
NK_API nk_bool
nk_combo_begin_image_text(struct nk_context *ctx, const char *selected, int len,
    struct nk_image img, struct nk_vec2 size)
{
    struct nk_window *win;
    struct nk_style *style;
    struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (!s) return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->combo.active;
        text.text = style->combo.label_active;
    } else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER) {
        background = &style->combo.hover;
        text.text = style->combo.label_hover;
    } else {
        background = &style->combo.normal;
        text.text = style->combo.label_normal;
    }

    switch(background->type) {
        case NK_STYLE_ITEM_IMAGE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_image(&win->buffer, header, &background->data.image, nk_white);
            break;
        case NK_STYLE_ITEM_NINE_SLICE:
            text.background = nk_rgba(0, 0, 0, 0);
            nk_draw_nine_slice(&win->buffer, header, &background->data.slice, nk_white);
            break;
        case NK_STYLE_ITEM_COLOR:
            text.background = background->data.color;
            nk_fill_rect(&win->buffer, header, style->combo.rounding, background->data.color);
            nk_stroke_rect(&win->buffer, header, style->combo.rounding, style->combo.border, style->combo.border_color);
            break;
    }
    {
        struct nk_rect content;
        struct nk_rect button;
        struct nk_rect label;
        struct nk_rect image;
        int draw_button_symbol;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        draw_button_symbol = sym != NK_SYMBOL_NONE;

        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.x;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;
        if (draw_button_symbol)
            nk_draw_button_symbol(&win->buffer, &button, &content, ctx->last_widget_state,
                &ctx->style.combo.button, sym, style->font);

        image.x = header.x + style->combo.content_padding.x;
        image.y = header.y + style->combo.content_padding.y;
        image.h = header.h - 2 * style->combo.content_padding.y;
        image.w = image.h;
        nk_draw_image(&win->buffer, image, &img, nk_white);

        text.padding = nk_vec2(0,0);
        label.x = image.x + image.w + style->combo.spacing.x + style->combo.content_padding.x;
        label.y = header.y + style->combo.content_padding.y;
        label.h = header.h - 2 * style->combo.content_padding.y;
        if (draw_button_symbol)
            label.w = (button.x - style->combo.content_padding.x) - label.x;
        else
            label.w = (header.x + header.w - style->combo.content_padding.x) - label.x;
        nk_widget_text(&win->buffer, label, selected, len, &text, NK_TEXT_LEFT, style->font);
    }
    return nk_combo_begin(ctx, win, size, is_clicked, header);
}
NK_API nk_bool
nk_combo_begin_symbol_label(struct nk_context *ctx,
    const char *selected, enum nk_symbol_type type, struct nk_vec2 size)
{
    return nk_combo_begin_symbol_text(ctx, selected, nk_strlen(selected), type, size);
}
NK_API nk_bool
nk_combo_begin_image_label(struct nk_context *ctx,
    const char *selected, struct nk_image img, struct nk_vec2 size)
{
    return nk_combo_begin_image_text(ctx, selected, nk_strlen(selected), img, size);
}
NK_API nk_bool
nk_combo_item_text(struct nk_context *ctx, const char *text, int len,nk_flags align)
{
    return nk_contextual_item_text(ctx, text, len, align);
}
NK_API nk_bool
nk_combo_item_label(struct nk_context *ctx, const char *label, nk_flags align)
{
    return nk_contextual_item_label(ctx, label, align);
}
NK_API nk_bool
nk_combo_item_image_text(struct nk_context *ctx, struct nk_image img, const char *text,
    int len, nk_flags alignment)
{
    return nk_contextual_item_image_text(ctx, img, text, len, alignment);
}
NK_API nk_bool
nk_combo_item_image_label(struct nk_context *ctx, struct nk_image img,
    const char *text, nk_flags alignment)
{
    return nk_contextual_item_image_label(ctx, img, text, alignment);
}
NK_API nk_bool
nk_combo_item_symbol_text(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *text, int len, nk_flags alignment)
{
    return nk_contextual_item_symbol_text(ctx, sym, text, len, alignment);
}
NK_API nk_bool
nk_combo_item_symbol_label(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *label, nk_flags alignment)
{
    return nk_contextual_item_symbol_label(ctx, sym, label, alignment);
}
NK_API void nk_combo_end(struct nk_context *ctx)
{
    nk_contextual_end(ctx);
}
NK_API void nk_combo_close(struct nk_context *ctx)
{
    nk_contextual_close(ctx);
}
NK_API int
nk_combo(struct nk_context *ctx, const char **items, int count,
    int selected, int item_height, struct nk_vec2 size)
{
    int i = 0;
    int max_height;
    struct nk_vec2 item_spacing;
    struct nk_vec2 window_padding;

    NK_ASSERT(ctx);
    NK_ASSERT(items);
    NK_ASSERT(ctx->current);
    if (!ctx || !items ||!count)
        return selected;

    item_spacing = ctx->style.window.spacing;
    window_padding = nk_panel_get_padding(&ctx->style, ctx->current->layout->type);
    max_height = count * item_height + count * (int)item_spacing.y;
    max_height += (int)item_spacing.y * 2 + (int)window_padding.y * 2;
    size.y = NK_MIN(size.y, (float)max_height);
    if (nk_combo_begin_label(ctx, items[selected], size)) {
        nk_layout_row_dynamic(ctx, (float)item_height, 1);
        for (i = 0; i < count; ++i) {
            if (nk_combo_item_label(ctx, items[i], NK_TEXT_LEFT))
                selected = i;
        }
        nk_combo_end(ctx);
    }
    return selected;
}
NK_API int
nk_combo_separator(struct nk_context *ctx, const char *items_separated_by_separator,
    int separator, int selected, int count, int item_height, struct nk_vec2 size)
{
    int i;
    int max_height;
    struct nk_vec2 item_spacing;
    struct nk_vec2 window_padding;
    const char *current_item;
    const char *iter;
    int length = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(items_separated_by_separator);
    if (!ctx || !items_separated_by_separator)
        return selected;

    item_spacing = ctx->style.window.spacing;
    window_padding = nk_panel_get_padding(&ctx->style, ctx->current->layout->type);
    max_height = count * item_height + count * (int)item_spacing.y;
    max_height += (int)item_spacing.y * 2 + (int)window_padding.y * 2;
    size.y = NK_MIN(size.y, (float)max_height);

    current_item = items_separated_by_separator;
    for (i = 0; i < count; ++i) {
        iter = current_item;
        while (*iter && *iter != separator) iter++;
        length = (int)(iter - current_item);
        if (i == selected) break;
        current_item = iter + 1;
    }

    if (nk_combo_begin_text(ctx, current_item, length, size)) {
        current_item = items_separated_by_separator;
        nk_layout_row_dynamic(ctx, (float)item_height, 1);
        for (i = 0; i < count; ++i) {
            iter = current_item;
            while (*iter && *iter != separator) iter++;
            length = (int)(iter - current_item);
            if (nk_combo_item_text(ctx, current_item, length, NK_TEXT_LEFT))
                selected = i;
            current_item = current_item + length + 1;
        }
        nk_combo_end(ctx);
    }
    return selected;
}
NK_API int
nk_combo_string(struct nk_context *ctx, const char *items_separated_by_zeros,
    int selected, int count, int item_height, struct nk_vec2 size)
{
    return nk_combo_separator(ctx, items_separated_by_zeros, '\0', selected, count, item_height, size);
}
NK_API int
nk_combo_callback(struct nk_context *ctx, void(*item_getter)(void*, int, const char**),
    void *userdata, int selected, int count, int item_height, struct nk_vec2 size)
{
    int i;
    int max_height;
    struct nk_vec2 item_spacing;
    struct nk_vec2 window_padding;
    const char *item;

    NK_ASSERT(ctx);
    NK_ASSERT(item_getter);
    if (!ctx || !item_getter)
        return selected;

    item_spacing = ctx->style.window.spacing;
    window_padding = nk_panel_get_padding(&ctx->style, ctx->current->layout->type);
    max_height = count * item_height + count * (int)item_spacing.y;
    max_height += (int)item_spacing.y * 2 + (int)window_padding.y * 2;
    size.y = NK_MIN(size.y, (float)max_height);

    item_getter(userdata, selected, &item);
    if (nk_combo_begin_label(ctx, item, size)) {
        nk_layout_row_dynamic(ctx, (float)item_height, 1);
        for (i = 0; i < count; ++i) {
            item_getter(userdata, i, &item);
            if (nk_combo_item_label(ctx, item, NK_TEXT_LEFT))
                selected = i;
        }
        nk_combo_end(ctx);
    } return selected;
}
NK_API void
nk_combobox(struct nk_context *ctx, const char **items, int count,
    int *selected, int item_height, struct nk_vec2 size)
{
    *selected = nk_combo(ctx, items, count, *selected, item_height, size);
}
NK_API void
nk_combobox_string(struct nk_context *ctx, const char *items_separated_by_zeros,
    int *selected, int count, int item_height, struct nk_vec2 size)
{
    *selected = nk_combo_string(ctx, items_separated_by_zeros, *selected, count, item_height, size);
}
NK_API void
nk_combobox_separator(struct nk_context *ctx, const char *items_separated_by_separator,
    int separator, int *selected, int count, int item_height, struct nk_vec2 size)
{
    *selected = nk_combo_separator(ctx, items_separated_by_separator, separator,
                                    *selected, count, item_height, size);
}
NK_API void
nk_combobox_callback(struct nk_context *ctx,
    void(*item_getter)(void* data, int id, const char **out_text),
    void *userdata, int *selected, int count, int item_height, struct nk_vec2 size)
{
    *selected = nk_combo_callback(ctx, item_getter, userdata,  *selected, count, item_height, size);
}

NK_API nk_bool
nk_tooltip_begin(struct nk_context *ctx, float width)
{
    int x,y,w,h;
    struct nk_window *win;
    const struct nk_input *in;
    struct nk_rect bounds;
    int ret;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    in = &ctx->input;
    if (win->popup.win && (win->popup.type & NK_PANEL_SET_NONBLOCK))
        return 0;

    w = nk_iceilf(width);
    h = nk_iceilf(nk_null_rect.h);
    x = nk_ifloorf(in->mouse.pos.x + 1) - (int)win->layout->clip.x;
    y = nk_ifloorf(in->mouse.pos.y + 1) - (int)win->layout->clip.y;

    bounds.x = (float)x;
    bounds.y = (float)y;
    bounds.w = (float)w;
    bounds.h = (float)h;

    ret = nk_popup_begin(ctx, NK_POPUP_DYNAMIC,
        "__##Tooltip##__", NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_BORDER, bounds);
    if (ret) win->layout->flags &= ~(nk_flags)NK_WINDOW_ROM;
    win->popup.type = NK_PANEL_TOOLTIP;
    ctx->current->layout->type = NK_PANEL_TOOLTIP;
    return ret;
}

NK_API void
nk_tooltip_end(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return;
    ctx->current->seq--;
    nk_popup_close(ctx);
    nk_popup_end(ctx);
}
NK_API void
nk_tooltip(struct nk_context *ctx, const char *text)
{
    const struct nk_style *style;
    struct nk_vec2 padding;

    int text_len;
    float text_width;
    float text_height;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    NK_ASSERT(text);
    if (!ctx || !ctx->current || !ctx->current->layout || !text)
        return;

    style = &ctx->style;
    padding = style->window.padding;

    text_len = nk_strlen(text);
    text_width = style->font->width(style->font->userdata,
                    style->font->height, text, text_len);
    text_width += (4 * padding.x);
    text_height = (style->font->height + 2 * padding.y);

    if (nk_tooltip_begin(ctx, (float)text_width)) {
        nk_layout_row_dynamic(ctx, (float)text_height, 1);
        nk_text(ctx, text, text_len, NK_TEXT_LEFT);
        nk_tooltip_end(ctx);
    }
}
#ifdef NK_INCLUDE_STANDARD_VARARGS
NK_API void
nk_tooltipf(struct nk_context *ctx, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    nk_tooltipfv(ctx, fmt, args);
    va_end(args);
}
NK_API void
nk_tooltipfv(struct nk_context *ctx, const char *fmt, va_list args)
{
    char buf[256];
    nk_strfmt(buf, NK_LEN(buf), fmt, args);
    nk_tooltip(ctx, buf);
}
#endif

#endif

