/*
 * Cogl
 *
 * An object oriented GL/GLES Abstraction/Utility Layer
 *
 * Copyright (C) 2011 Intel Corporation.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *
 *
 * Authors:
 *   Robert Bragg <robert@linux.intel.com>
 */

#ifndef __COGL_FRAMEBUFFER_H
#define __COGL_FRAMEBUFFER_H

#include <glib.h>

#ifdef COGL_HAS_WIN32_SUPPORT
#include <windows.h>
#endif /* COGL_HAS_WIN32_SUPPORT */

#if defined (COGL_HAS_EGL_PLATFORM_WAYLAND_SUPPORT)
#include <wayland-client.h>
#endif /* COGL_HAS_EGL_PLATFORM_WAYLAND_SUPPORT */

G_BEGIN_DECLS

/**
 * SECTION:cogl-framebuffer
 * @short_description: A common interface for manipulating framebuffers
 *
 * Framebuffers are a collection of buffers that can be rendered too.
 * A framebuffer may be comprised of one or more color buffers, an
 * optional depth buffer and an optional stencil buffer. Other
 * configuration parameters are associated with framebuffers too such
 * as whether the framebuffer supports multi-sampling (an anti-aliasing
 * technique) or dithering.
 *
 * There are two kinds of framebuffer in Cogl, #CoglOnscreen
 * framebuffers and #CoglOffscreen framebuffers. As the names imply
 * offscreen framebuffers are for rendering something offscreen
 * (perhaps to a texture which is bound as one of the color buffers).
 * The exact semantics of onscreen framebuffers depends on the window
 * system backend that you are using, but typically you can expect
 * rendering to a #CoglOnscreen framebuffer will be immediately
 * visible to the user.
 *
 * If you want to create a new framebuffer then you should start by
 * looking at the #CoglOnscreen and #CoglOffscreen constructor
 * functions, such as cogl_offscreen_new_to_texture() or
 * cogl_xlib_onscreen_new(). The #CoglFramebuffer interface deals with
 * all aspects that are common between those two types of framebuffer.
 *
 * Setup of a new CoglFramebuffer happens in two stages. There is a
 * configuration stage where you specify all the options and ancillary
 * buffers you want associated with your framebuffer and then when you
 * are happy with the configuration you can "allocate" the framebuffer
 * using cogl_framebuffer_allocate (). Technically explicitly calling
 * cogl_framebuffer_allocate () is optional for convenience and the
 * framebuffer will automatically be allocated when you first try to
 * draw to it, but if you do the allocation manually then you can
 * also catch any possible errors that may arise from your
 * configuration.
 */

#ifdef COGL_ENABLE_EXPERIMENTAL_API
#define COGL_FRAMEBUFFER(X) ((CoglFramebuffer *)(X))

#define cogl_framebuffer_allocate cogl_framebuffer_allocate_EXP
gboolean
cogl_framebuffer_allocate (CoglFramebuffer *framebuffer,
                           GError **error);

#define cogl_framebuffer_get_width cogl_framebuffer_get_width_EXP
int
cogl_framebuffer_get_width (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_get_height cogl_framebuffer_get_height_EXP
int
cogl_framebuffer_get_height (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_set_viewport cogl_framebuffer_set_viewport_EXP
void
cogl_framebuffer_set_viewport (CoglFramebuffer *framebuffer,
                               float x,
                               float y,
                               float width,
                               float height);

#define cogl_framebuffer_get_viewport_x cogl_framebuffer_get_viewport_x_EXP
float
cogl_framebuffer_get_viewport_x (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_get_viewport_y cogl_framebuffer_get_viewport_y_EXP
float
cogl_framebuffer_get_viewport_y (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_get_viewport_width cogl_framebuffer_get_viewport_width_EXP
float
cogl_framebuffer_get_viewport_width (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_get_viewport_height cogl_framebuffer_get_viewport_height_EXP
float
cogl_framebuffer_get_viewport_height (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_get_viewport4fv cogl_framebuffer_get_viewport4fv_EXP
void
cogl_framebuffer_get_viewport4fv (CoglFramebuffer *framebuffer,
                                  float *viewport);

/**
 * cogl_framebuffer_get_red_bits:
 * @framebuffer: a pointer to a #CoglFramebuffer
 *
 * Retrieves the number of red bits of @framebuffer
 *
 * Return value: the number of bits
 *
 * Since: 1.8
 * Stability: unstable
 */
#define cogl_framebuffer_get_red_bits cogl_framebuffer_get_red_bits_EXP
int
cogl_framebuffer_get_red_bits (CoglFramebuffer *framebuffer);

/**
 * cogl_framebuffer_get_green_bits:
 * @framebuffer: a pointer to a #CoglFramebuffer
 *
 * Retrieves the number of green bits of @framebuffer
 *
 * Return value: the number of bits
 *
 * Since: 1.8
 * Stability: unstable
 */
#define cogl_framebuffer_get_green_bits cogl_framebuffer_get_green_bits_EXP
int
cogl_framebuffer_get_green_bits (CoglFramebuffer *framebuffer);

/**
 * cogl_framebuffer_get_blue_bits:
 * @framebuffer: a pointer to a #CoglFramebuffer
 *
 * Retrieves the number of blue bits of @framebuffer
 *
 * Return value: the number of bits
 *
 * Since: 1.8
 * Stability: unstable
 */
#define cogl_framebuffer_get_blue_bits cogl_framebuffer_get_blue_bits_EXP
int
cogl_framebuffer_get_blue_bits (CoglFramebuffer *framebuffer);

/**
 * cogl_framebuffer_get_alpha_bits:
 * @framebuffer: a pointer to a #CoglFramebuffer
 *
 * Retrieves the number of alpha bits of @framebuffer
 *
 * Return value: the number of bits
 *
 * Since: 1.8
 * Stability: unstable
 */
#define cogl_framebuffer_get_alpha_bits cogl_framebuffer_get_alpha_bits_EXP
int
cogl_framebuffer_get_alpha_bits (CoglFramebuffer *framebuffer);

/**
 * cogl_framebuffer_get_dither_enabled:
 * @framebuffer: a pointer to a #CoglFramebuffer
 *
 * Returns whether dithering has been requested for the given @framebuffer.
 * See cogl_framebuffer_set_dither_enabled() for more details about dithering.
 *
 * <note>This may return %TRUE even when the underlying @framebuffer
 * display pipeline does not support dithering. This value only represents
 * the user's request for dithering.</note>
 *
 * Return value: %TRUE if dithering has been requested or %FALSE if not.
 */
gboolean
cogl_framebuffer_get_dither_enabled (CoglFramebuffer *framebuffer);

/**
 * cogl_framebuffer_set_dither_enabled:
 * @framebuffer: a pointer to a #CoglFramebuffer
 * @dither_enabled: %TRUE to enable dithering or %FALSE to disable
 *
 * Enables or disabled dithering if supported by the hardware.
 *
 * Dithering is a hardware dependent technique to increase the visible
 * color resolution beyond what the underlying hardware supports by playing
 * tricks with the colors placed into the framebuffer to give the illusion
 * of other colors. (For example this can be compared to half-toning used
 * by some news papers to show varying levels of grey even though their may
 * only be black and white are available).
 *
 * If the current display pipeline for @framebuffer does not support dithering
 * then this has no affect.
 *
 * Dithering is enabled by default.
 *
 * Since: 1.8
 * Stability: unstable
 */
void
cogl_framebuffer_set_dither_enabled (CoglFramebuffer *framebuffer,
                                     gboolean dither_enabled);

#define cogl_framebuffer_get_color_mask cogl_framebuffer_get_color_mask_EXP
/**
 * cogl_framebuffer_get_color_mask:
 * @framebuffer: a pointer to a #CoglFramebuffer
 *
 * Gets the current #CoglColorMask of which channels would be written to the
 * current framebuffer. Each bit set in the mask means that the
 * corresponding color would be written.
 *
 * Returns: A #CoglColorMask
 * Since: 1.8
 * Stability: unstable
 */
CoglColorMask
cogl_framebuffer_get_color_mask (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_set_color_mask cogl_framebuffer_set_color_mask_EXP
/**
 * cogl_framebuffer_set_color_mask:
 * @framebuffer: a pointer to a #CoglFramebuffer
 * @color_mask: A #CoglColorMask of which color channels to write to
 *              the current framebuffer.
 *
 * Defines a bit mask of which color channels should be written to the
 * given @framebuffer. If a bit is set in @color_mask that means that
 * color will be written.
 *
 * Since: 1.8
 * Stability: unstable
 */
void
cogl_framebuffer_set_color_mask (CoglFramebuffer *framebuffer,
                                 CoglColorMask color_mask);

#define cogl_framebuffer_get_context cogl_framebuffer_get_context_EXP
/**
 * @framebuffer: A #CoglFramebuffer
 *
 * Can be used to query the #CoglContext a given @framebuffer was
 * instantiated within. This is the #CoglContext that was passed to
 * cogl_onscreen_new() for example.
 *
 * Return value: The #CoglContext that the given @framebuffer was
 *               instantiated within.
 * Since: 1.8
 * Stability: unstable
 */
CoglContext *
cogl_framebuffer_get_context (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_clear cogl_framebuffer_clear_EXP
/**
 * cogl_framebuffer_clear:
 * @framebuffer: A #CoglFramebuffer
 * @buffers: A mask of #CoglBufferBit<!-- -->'s identifying which auxiliary
 *   buffers to clear
 * @color: The color to clear the color buffer too if specified in
 *         @buffers.
 *
 * Clears all the auxiliary buffers identified in the @buffers mask, and if
 * that includes the color buffer then the specified @color is used.
 *
 * Since: 1.8
 * Stability: unstable
 */
void
cogl_framebuffer_clear (CoglFramebuffer *framebuffer,
                        unsigned long buffers,
                        const CoglColor *color);

#define cogl_framebuffer_clear4f cogl_framebuffer_clear4f_EXP
/**
 * cogl_framebuffer_clear4f:
 * @framebuffer: A #CoglFramebuffer
 * @buffers: A mask of #CoglBufferBit<!-- -->'s identifying which auxiliary
 *   buffers to clear
 * @red: The red component of color to clear the color buffer too if
 *       specified in @buffers.
 * @green: The green component of color to clear the color buffer too if
 *         specified in @buffers.
 * @blue: The blue component of color to clear the color buffer too if
 *        specified in @buffers.
 * @alpha: The alpha component of color to clear the color buffer too if
 *         specified in @buffers.
 *
 * Clears all the auxiliary buffers identified in the @buffers mask, and if
 * that includes the color buffer then the specified @color is used.
 *
 * Since: 1.8
 * Stability: unstable
 */
void
cogl_framebuffer_clear4f (CoglFramebuffer *framebuffer,
                          unsigned long buffers,
                          float red,
                          float green,
                          float blue,
                          float alpha);

#define cogl_framebuffer_swap_buffers cogl_framebuffer_swap_buffers_EXP
void
cogl_framebuffer_swap_buffers (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_swap_region cogl_framebuffer_swap_region_EXP
void
cogl_framebuffer_swap_region (CoglFramebuffer *framebuffer,
                              const int *rectangles,
                              int n_rectangles);


typedef void (*CoglSwapBuffersNotify) (CoglFramebuffer *framebuffer,
                                       void *user_data);

#define cogl_framebuffer_add_swap_buffers_callback \
  cogl_framebuffer_add_swap_buffers_callback_EXP
unsigned int
cogl_framebuffer_add_swap_buffers_callback (CoglFramebuffer *framebuffer,
                                            CoglSwapBuffersNotify callback,
                                            void *user_data);

#define cogl_framebuffer_remove_swap_buffers_callback \
  cogl_framebuffer_remove_swap_buffers_callback_EXP
void
cogl_framebuffer_remove_swap_buffers_callback (CoglFramebuffer *framebuffer,
                                               unsigned int id);


typedef struct _CoglOnscreen CoglOnscreen;
#define COGL_ONSCREEN(X) ((CoglOnscreen *)(X))

void
cogl_onscreen_update_size (CoglOnscreen *framebuffer,
			   int width, int height);

#if defined (COGL_HAS_EGL_PLATFORM_POWERVR_NULL_SUPPORT) || \
  defined (COGL_HAS_EGL_PLATFORM_ANDROID_SUPPORT)        || \
  defined (COGL_HAS_EGL_PLATFORM_GDL_SUPPORT)
#define cogl_egl_onscreen_new cogl_egl_onscreen_new_EXP
CoglOnscreen *
cogl_egl_onscreen_new (CoglContext *context, int width, int height);
#endif

#ifdef COGL_HAS_X11
/**
 * cogl_xlib_onscreen_new:
 * @context: a #CoglContext
 * @xid: the XID of an existing X window
 *
 * Creates a new #CoglOnscreen, targeting @xid for drawing and reading.
 * The framebuffer is initially the size of the window. You need to
 * handle ConfigureNotify events and call cogl_onscreen_update_size() to
 * let Cogl know the window has changed size. You also need to pass
 * any extra event to cogl_xlib_onscreen_handle_event() (for example for
 * GLX swap events).
 */
#define cogl_xlib_onscreen_new cogl_xlib_onscreen_new_EXP
CoglOnscreen *
cogl_xlib_onscreen_new (CoglContext *context,
			Window       xwindow);

#define cogl_xlib_onscreen_get_window_xid cogl_xlib_onscreen_get_window_xid_EXP
guint32
cogl_xlib_onscreen_get_window_xid (CoglOnscreen *onscreen);

#define cogl_xlib_onscreen_get_visual_xid cogl_xlib_onscreen_get_visual_xid_EXP
guint32
cogl_xlib_onscreen_get_visual_xid (CoglOnscreen *onscreen);

/**
 * cogl_xlib_onscreen_handle_event:
 * @onscreen: a #CoglOnscreen targetting a X window
 * @event: a native event
 *
 * Asks Cogl if it is interested in handling this event, which is directed
 * to the window backing @onscreen. It is an error to pass an event directed
 * elsewhere.
 * Returns: %TRUE if Cogl has handled the event, %FALSE otherwise. Only GL
 *          related events (such as GLX_INTEL_swap_event) are handled,
 *          therefore they're not expected to be useful to embedding toolkits.
 */
#define cogl_xlib_onscreen_handle_event cogl_xlib_onscreen_handle_event_EXP
gboolean
cogl_xlib_onscreen_handle_event (CoglOnscreen *onscreen,
				 XEvent       *event);
#endif /* COGL_HAS_X11 */

#ifdef COGL_HAS_WIN32_SUPPORT
#define cogl_win32_onscreen_new cogl_win32_onscreen_foreign_new_EXP
CoglOnscreen *
cogl_win32_onscreen_new (CoglContext *context,
				 HWND         hwnd);

#define cogl_win32_onscreen_get_window cogl_win32_onscreen_get_window_EXP
HWND
cogl_win32_onscreen_get_window (CoglOnscreen *onscreen);
#endif /* COGL_HAS_WIN32_SUPPORT */

#if defined (COGL_HAS_EGL_PLATFORM_WAYLAND_SUPPORT)
#define cogl_wayland_onscreen_foreign_new cogl_wayland_onscreen_foreign_new_EXP
CoglOnscreen *
cogl_wayland_onscreen_new (CoglContext *context,
				   struct wl_surface *surface,
				   int width,
				   int height);

struct wl_surface *
cogl_wayland_onscreen_get_surface (CoglOnscreen *onscreen);
#endif /* COGL_HAS_EGL_PLATFORM_WAYLAND_SUPPORT */

#define cogl_onscreen_set_swap_throttled cogl_onscreen_set_swap_throttled_EXP
void
cogl_onscreen_set_swap_throttled (CoglOnscreen *onscreen,
                                  gboolean throttled);

/**
 * cogl_onscreen_show:
 * @onscreen: The onscreen framebuffer to make visible
 *
 * This requests to make @onscreen visible to the user.
 *
 * Actually the precise semantics of this function depend on the
 * window system currently in use, and if you don't have a
 * multi-windowining system this function may in-fact do nothing.
 *
 * This function will implicitly allocate the given @onscreen
 * framebuffer before showing it if it hasn't already been allocated.
 *
 * <note>Since Cogl doesn't explicitly track the visibility status of
 * onscreen framebuffers it wont try to avoid redundant window system
 * requests e.g. to show an already visible window. This also means
 * that it's acceptable to alternatively use native APIs to show and
 * hide windows without confusing Cogl.</note>
 *
 * Since: 2.0
 * Stability: Unstable
 */
#define cogl_onscreen_show cogl_onscreen_show_EXP
void
cogl_onscreen_show (CoglOnscreen *onscreen);

/**
 * cogl_onscreen_hide:
 * @onscreen: The onscreen framebuffer to make invisible
 *
 * This requests to make @onscreen invisible to the user.
 *
 * Actually the precise semantics of this function depend on the
 * window system currently in use, and if you don't have a
 * multi-windowining system this function may in-fact do nothing.
 *
 * This function does not implicitly allocate the given @onscreen
 * framebuffer before hiding it.
 *
 * <note>Since Cogl doesn't explicitly track the visibility status of
 * onscreen framebuffers it wont try to avoid redundant window system
 * requests e.g. to show an already visible window. This also means
 * that it's acceptable to alternatively use native APIs to show and
 * hide windows without confusing Cogl.</note>
 *
 * Since: 2.0
 * Stability: Unstable
 */
#define cogl_onscreen_hide cogl_onscreen_hide_EXP
void
cogl_onscreen_hide (CoglOnscreen *onscreen);

#define cogl_get_draw_framebuffer cogl_get_draw_framebuffer_EXP
CoglFramebuffer *
cogl_get_draw_framebuffer (void);

#endif /* COGL_ENABLE_EXPERIMENTAL_API */

G_END_DECLS

#endif /* __COGL_FRAMEBUFFER_H */

