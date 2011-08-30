/* -*- mode: C; c-basic-offset: 4; indent-tabs-mode: nil; -*- */

#include <cogl/cogl.h>
#include <glib.h>
#include <stdio.h>
#include <gdk/gdk.h>
#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#endif
#ifdef GDK_WINDOWING_WIN32
#include <gdk/gdkwin32.h>
#endif

CoglColor black;

typedef struct _DrawingData
{
    CoglPrimitive *primitive;
    CoglFramebuffer *fb;
} DrawingData;

static GdkFilterReturn
gdk_window_filter (GdkXEvent  *xevent,
		   GdkEvent   *event,
		   void       *user_data)
{
    CoglRenderer *renderer = user_data;

#if defined(GDK_WINDOWING_X11) && defined(COGL_HAS_XLIB_SUPPORT)
    if (GDK_IS_X11_WINDOW (event->any.window)) {
        if (cogl_xlib_renderer_handle_event (renderer, xevent) ==
            COGL_FILTER_REMOVE)
            return GDK_FILTER_REMOVE;

        return GDK_FILTER_CONTINUE;
    }
#endif

#if defined(GDK_WINDOWING_WIN32) && defined(COGL_HAS_WGL_SUPPORT)
    if (GDK_IS_WIN32_WINDOW (event->any.window)) {
        if (cogl_win32_renderer_handle_event (renderer, xevent) ==
            COGL_FILTER_REMOVE)
            return GDK_FILTER_REMOVE;

        return GDK_FILTER_CONTINUE;
    }
#endif

    return GDK_FILTER_CONTINUE;
}

#if defined(GDK_WINDOWING_X11) && defined(COGL_HAS_XLIB_SUPPORT)
static void
cogl_update_event_mask (CoglOnscreen *onscreen,
                        guint32       event_mask,
                        void         *user_data)
{
    /* Do nothing. Cogl only selects for StructureNotifyMask,
       and we already select GDK_STRUCTURE_MASK */
}
#endif

static CoglOnscreen *
gdk_create_onscreen (CoglRenderer *renderer,
                     CoglDisplay  *display,
                     CoglContext  *context,
                     int           width,
                     int           height,
                     GdkWindow   **windowp)
{
    GdkWindow *window;
    GdkWindowAttr attr;
    GdkWindowAttributesType attr_type;

    attr.title = "Hello, world";
    attr.event_mask = GDK_STRUCTURE_MASK;
    attr.width = width;
    attr.height = height;
    attr.wclass = GDK_INPUT_OUTPUT;
    attr.window_type = GDK_WINDOW_TOPLEVEL;

    attr_type = GDK_WA_TITLE;

#if defined(GDK_WINDOWING_X11) && defined(COGL_HAS_XLIB_SUPPORT)
    if (GDK_IS_X11_DISPLAY (gdk_display_get_default ())) {
        GdkDisplay *gdk_display = gdk_display_get_default ();
        GdkScreen *screen = gdk_display_get_default_screen (gdk_display);
        XVisualInfo *xvisinfo = cogl_xlib_display_get_visual_info (display);

        attr.visual = gdk_x11_screen_lookup_visual (screen,
                                                    xvisinfo->visualid);
        if (attr.visual)
            attr_type |= GDK_WA_VISUAL;
    }
#endif

    window = *windowp = gdk_window_new (NULL, &attr, attr_type);
    gdk_window_add_filter (window, gdk_window_filter, renderer);

#if defined(GDK_WINDOWING_X11) && defined(COGL_HAS_XLIB_SUPPORT)
    if (GDK_IS_X11_WINDOW (window))
        return cogl_xlib_onscreen_new (context,
                                       gdk_x11_window_get_xid (window),
                                       cogl_update_event_mask, NULL);
#endif

#if defined(GDK_WINDOWING_WIN32) && defined(COGL_HAS_WGL_SUPPORT)
    if (GDK_IS_WIN32_WINDOW (window))
        return cogl_win32_onscreen_new (context,
                                        gdk_win32_window_get_hwnd (window));
#endif

    g_error ("Cannot match Gdk backend to Cogl backend");
}

static void
gdk_event_handler (GdkEvent *event,
                   void     *user_data)
{
    GMainLoop *main_loop = user_data;

    if (event->any.type == GDK_DELETE)
        g_main_loop_quit (main_loop);
}

static gboolean
cogl_redraw (void *user_data)
{
    DrawingData *ddata = user_data;

    cogl_push_framebuffer (ddata->fb);

    cogl_clear (&black, COGL_BUFFER_BIT_COLOR);
    cogl_primitive_draw (ddata->primitive);
    cogl_framebuffer_swap_buffers (ddata->fb);

    return FALSE;
}

static void
cogl_swap_completed (CoglFramebuffer *buffer,
                     void            *user_data)
{
    g_idle_add (cogl_redraw, user_data);
}

int
main (int argc, char **argv)
{
    DrawingData ddata;
    CoglRenderer *renderer;
    CoglDisplay *display;
    CoglContext *ctx;
    CoglOnscreen *onscreen;
    GError *error = NULL;
    CoglVertexP2C4 triangle_vertices[] = {
        {0, 0.7, 0xff, 0x00, 0x00, 0x80},
        {-0.7, -0.7, 0x00, 0xff, 0x00, 0xff},
        {0.7, -0.7, 0x00, 0x00, 0xff, 0xff}
    };
    GdkWindow *window;
    GMainLoop *loop;

    gdk_init (&argc, &argv);

    loop = g_main_loop_new (NULL, FALSE);
    gdk_event_handler_set (gdk_event_handler, loop, NULL);

#if defined(GDK_WINDOWING_X11) && defined(COGL_HAS_XLIB_SUPPORT)
    if (GDK_IS_X11_DISPLAY (gdk_display_get_default ()))
        renderer = cogl_xlib_renderer_new (GDK_DISPLAY_XDISPLAY (gdk_display_get_default ()));
    else
#endif
        renderer = cogl_renderer_new ();

    if (!cogl_renderer_connect (renderer, &error)) {
        fprintf (stderr, "Failed to connect renderer: %s\n", error->message);
        return 1;
    }

    display = cogl_display_new (renderer, NULL);
    if (!cogl_display_setup (display, &error)) {
        fprintf (stderr, "Failed to setup display pipeline: %s\n", error->message);
        return 1;
    }

    ctx = cogl_context_new (display, &error);
    if (!ctx) {
        fprintf (stderr, "Failed to create context: %s\n", error->message);
        return 1;
    }

    onscreen = gdk_create_onscreen (renderer, display, ctx, 640, 480, &window);

    ddata.fb = COGL_FRAMEBUFFER (onscreen);
    /* Eventually there will be an implicit allocate on first use so this
     * will become optional... */
    if (!cogl_framebuffer_allocate (ddata.fb, &error)) {
        fprintf (stderr, "Failed to allocate framebuffer: %s\n", error->message);
        return 1;
    }

    ddata.primitive = cogl_primitive_new_p2c4 (COGL_VERTICES_MODE_TRIANGLES,
                                               3, triangle_vertices);

    cogl_framebuffer_add_swap_buffers_callback (ddata.fb, cogl_swap_completed, &ddata);

    cogl_redraw (&ddata);
    gdk_window_show (window);

    g_main_loop_run (loop);

    return 0;
}
