#include <cogl/cogl.h>
#include <glib.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define X11_FOREIGN_EVENT_MASK \
  (KeyPressMask | \
   KeyReleaseMask | \
   ButtonPressMask | \
   ButtonReleaseMask | \
   PointerMotionMask | \
   StructureNotifyMask)

CoglColor black;

int
main (int argc, char **argv)
{
  Display *xdpy;
  CoglRenderer *renderer;
  CoglSwapChain *chain;
  CoglOnscreenTemplate *onscreen_template;
  CoglDisplay *display;
  CoglContext *ctx;
  CoglOnscreen *onscreen;
  CoglFramebuffer *fb;
  GError *error = NULL;
  XVisualInfo *xvisinfo;
  XSetWindowAttributes xattr;
  unsigned long mask;
  Window xwin;
  CoglVertexP2C4 triangle_vertices[] = {
      {0, 0.7, 0xff, 0x00, 0x00, 0x80},
      {-0.7, -0.7, 0x00, 0xff, 0x00, 0xff},
      {0.7, -0.7, 0x00, 0x00, 0xff, 0xff}
  };
  CoglPrimitive *triangle;


  /* Since we want to test external ownership of the X display,
   * connect to X manually... */
  xdpy = XOpenDisplay (NULL);
  if (!xdpy)
    {
      fprintf (stderr, "Failed to open X Display\n");
      return 1;
    }

  /* Conceptually choose a GPU... */
  renderer = cogl_xlib_renderer_new (xdpy);
  if (!cogl_renderer_connect (renderer, &error))
    {
      fprintf (stderr, "Failed to connect to a renderer: %s\n",
               error->message);
    }

  chain = cogl_swap_chain_new ();
  cogl_swap_chain_set_has_alpha (chain, TRUE);

  /* Conceptually declare upfront the kinds of windows we anticipate
   * creating so that when we configure the display pipeline we can avoid
   * having an impedance miss-match between the format of windows and the
   * format the display pipeline expects. */
  onscreen_template = cogl_onscreen_template_new (chain);
  cogl_object_unref (chain);

  /* Conceptually setup a display pipeline */
  display = cogl_display_new (renderer, onscreen_template);
  cogl_object_unref (renderer);
  if (!cogl_display_setup (display, &error))
    {
      fprintf (stderr, "Failed to setup a display pipeline: %s\n",
               error->message);
      return 1;
    }

  ctx = cogl_context_new (display, &error);
  if (!ctx)
    {
      fprintf (stderr, "Failed to create context: %s\n", error->message);
      return 1;
    }

  /* We want to test that Cogl can handle foreign X windows... */

  xvisinfo = cogl_xlib_display_get_visual_info (display);
  if (!xvisinfo)
    {
      fprintf (stderr, "Failed to query an X visual suitable for the "
               "configured CoglDisplay\n");
      return 1;
    }

  /* window attributes */
  xattr.background_pixel = WhitePixel (xdpy, DefaultScreen (xdpy));
  xattr.border_pixel = 0;
  xattr.colormap = XCreateColormap (xdpy,
                                    DefaultRootWindow (xdpy),
                                    xvisinfo->visual,
                                    AllocNone);
  xattr.event_mask = X11_FOREIGN_EVENT_MASK;
  mask = CWBorderPixel | CWColormap | CWEventMask;

  xwin = XCreateWindow (xdpy,
                        DefaultRootWindow (xdpy),
                        0, 0,
                        800, 600,
                        0,
                        xvisinfo->depth,
                        InputOutput,
                        xvisinfo->visual,
                        mask, &xattr);

  XFree (xvisinfo);

  onscreen = cogl_xlib_onscreen_new (ctx, xwin);

  fb = COGL_FRAMEBUFFER (onscreen);
  /* Eventually there will be an implicit allocate on first use so this
   * will become optional... */
  if (!cogl_framebuffer_allocate (fb, &error))
    {
      fprintf (stderr, "Failed to allocate framebuffer: %s\n", error->message);
      return 1;
    }

  XMapWindow (xdpy, xwin);

  cogl_push_framebuffer (fb);

  triangle = cogl_primitive_new_p2c4 (COGL_VERTICES_MODE_TRIANGLES,
                                      3, triangle_vertices);
  for (;;)
    {
      while (XPending (xdpy))
        {
          XEvent event;
          XNextEvent (xdpy, &event);

	  if (event.xany.window != xwin)
	    continue;

          if (cogl_xlib_onscreen_handle_event (onscreen, &event))
	    continue;

          switch (event.type)
            {
            case KeyRelease:
            case ButtonRelease:
              return 0;
	    case ConfigureNotify:
	      cogl_onscreen_update_size (onscreen,
					 event.xconfigure.width,
					 event.xconfigure.height);
	      break;
            }
        }
      cogl_clear (&black, COGL_BUFFER_BIT_COLOR);
      cogl_primitive_draw (triangle);
      cogl_framebuffer_swap_buffers (fb);
    }

  return 0;
}
