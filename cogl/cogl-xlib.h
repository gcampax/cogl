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
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#if !defined(__COGL_H_INSIDE__) && !defined(CLUTTER_COMPILATION)
#error "Only <cogl/cogl.h> can be included directly."
#endif

#ifndef __COGL_XLIB_H__
#define __COGL_XLIB_H__

#include <cogl/cogl-types.h>

#include <X11/Xlib.h>

G_BEGIN_DECLS

/*
 * cogl_xlib_get_display:
 *
 * Return value: the Xlib display that will be used by the Xlib winsys
 * backend. The display needs to be set with _cogl_xlib_set_display()
 * before this function is called.
 *
 * Stability: Unstable
 */
#define cogl_xlib_get_display cogl_xlib_get_display_EXP
Display *
cogl_xlib_get_display (void);

/*
 * cogl_xlib_set_display:
 *
 * Sets the Xlib display that Cogl will use for the Xlib winsys
 * backend. This function should eventually go away when Cogl gains a
 * more complete winsys abstraction.
 *
 * Stability: Unstable
 */
#define cogl_xlib_set_display cogl_xlib_set_display_EXP
void
cogl_xlib_set_display (Display *display);

#endif /* __COGL_XLIB_H__ */
