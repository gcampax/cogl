/*
 * Cogl
 *
 * An object oriented GL/GLES Abstraction/Utility Layer
 *
 * Copyright (C) 2007,2008,2009,2012 Intel Corporation.
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
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#if !defined(__COGL_H_INSIDE__) && !defined(COGL_COMPILATION)
#error "Only <cogl/cogl.h> can be included directly."
#endif

#ifndef __COGL_OFFSCREEN_H__
#define __COGL_OFFSCREEN_H__

#include <cogl/cogl-types.h>
#include <cogl/cogl-texture.h>

COGL_BEGIN_DECLS

/**
 * SECTION:cogl-offscreen
 * @short_description: Functions for creating and manipulating offscreen
 *                     framebuffers.
 *
 * Cogl allows creating and operating on offscreen framebuffers.
 */

typedef struct _CoglOffscreen CoglOffscreen;

#define COGL_OFFSCREEN(X) ((CoglOffscreen *)X)

/* Offscreen api */

/**
 * cogl_offscreen_new_to_texture:
 * @texture: A #CoglTexture pointer
 *
 * This creates an offscreen buffer object using the given @texture as the
 * primary color buffer. It doesn't just initialize the contents of the
 * offscreen buffer with the @texture; they are tightly bound so that
 * drawing to the offscreen buffer effectivly updates the contents of the
 * given texture. You don't need to destroy the offscreen buffer before
 * you can use the @texture again.
 *
 * <note>This only works with low-level #CoglTexture types such as
 * #CoglTexture2D, #CoglTexture3D and #CoglTextureRectangle, and not
 * with meta-texture types such as #CoglTexture2DSliced.</note>
 *
 * Return value: (transfer full): a newly instantiated #CoglOffscreen
 *   framebuffer or %NULL if it wasn't possible to create the
 *   buffer.
 */
CoglOffscreen *
cogl_offscreen_new_to_texture (CoglTexture *texture);

/**
 * cogl_is_offscreen:
 * @object: A pointer to a #CoglObject
 *
 * Determines whether the given #CoglObject references an offscreen
 * framebuffer object.
 *
 * Returns: %TRUE if @object is a #CoglOffscreen framebuffer,
 *          %FALSE otherwise
 */
CoglBool
cogl_is_offscreen (void *object);

COGL_END_DECLS

#endif /* __COGL_OFFSCREEN_H__ */
