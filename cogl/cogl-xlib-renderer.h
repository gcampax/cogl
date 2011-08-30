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

#ifndef __COGL_XLIB_RENDERER_H__
#define __COGL_XLIB_RENDERER_H__

#include <cogl/cogl-types.h>
#include <cogl/cogl-renderer.h>

#include <X11/Xlib.h>

G_BEGIN_DECLS

#define cogl_xlib_renderer_get_display cogl_xlib_renderer_get_display_EXP
Display *
cogl_xlib_renderer_get_display (CoglRenderer *renderer);

#define cogl_xlib_renderer_new cogl_xlib_renderer_new_EXP
CoglRenderer *
cogl_xlib_renderer_new (Display *display);

G_END_DECLS

#endif /* __COGL_XLIB_RENDERER_H__ */
