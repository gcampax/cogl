/*
 * Cogl
 *
 * An object oriented GL/GLES Abstraction/Utility Layer
 *
 * Copyright (C) 2010 Intel Corporation.
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

#ifndef __COGL_TEXTURE_PIXMAP_X11_H
#define __COGL_TEXTURE_PIXMAP_X11_H

#include <cogl/cogl.h>

#ifdef COGL_ENABLE_EXPERIMENTAL_API

/* All of the cogl-texture-pixmap-x11 API is currently experimental so
 * we suffix the actual symbols with _EXP so if somone is monitoring
 * for ABI changes it will hopefully be clearer to them what's going
 * on if any of the symbols dissapear at a later date.
 */
#define cogl_texture_pixmap_x11_new cogl_texture_pixmap_x11_new_EXP
#define cogl_texture_pixmap_x11_update_area \
  cogl_texture_pixmap_x11_update_area_EXP
#define cogl_texture_pixmap_x11_is_using_tfp_extension \
  cogl_texture_pixmap_x11_is_using_tfp_extension_EXP
#define cogl_texture_pixmap_x11_set_damage_object \
  cogl_texture_pixmap_x11_set_damage_object_EXP
#define cogl_is_texture_pixmap_x11 cogl_is_texture_pixmap_x11_EXP

/**
 * cogl_texture_pixmap_x11_new:
 * @pixmap: A X11 pixmap ID
 *
 * Creates a texture that contains the contents of @pixmap. You
 * need to manually handle Damage events on the pixmap and call
 * cogl_texture_pixamp_x11_update_area() if you want the texture
 * reflect changes in the underlying pixmap.
 *
 * Return value: a CoglHandle to a texture
 *
 * Since: 1.4
 * Stability: Unstable
 */
CoglHandle
cogl_texture_pixmap_x11_new (guint32 pixmap);

/**
 * cogl_texture_pixmap_x11_update_area:
 * @handle: A CoglHandle to a CoglTexturePixmapX11 instance
 * @x: x coordinate of the area to update
 * @y: y coordinate of the area to update
 * @width: width of the area to update
 * @height: height of the area to update
 *
 * Forces an update of the texture pointed to by @handle so that it is
 * refreshed with the contents of the pixmap that was given to
 * cogl_texture_pixmap_x11_new().
 *
 * Since: 1.4
 * Stability: Unstable
 */
void
cogl_texture_pixmap_x11_update_area (CoglHandle handle,
                                     int x,
                                     int y,
                                     int width,
                                     int height);

/**
 * cogl_texture_pixmap_x11_is_using_tfp_extension:
 * @handle: A CoglHandle to a CoglTexturePixmapX11 instance
 *
 * Checks whether the texture is using the GLX_EXT_texture_from_pixmap
 * or similar extension to copy the contents of the pixmap to the texture.
 * This extension is usually implemented as zero-copy operation so it
 * implies the updates are working efficiently.
 *
 * Return value: %TRUE if the texture is using an efficient extension
 *   and %FALSE otherwise
 *
 * Since: 1.4
 * Stability: Unstable
 */
gboolean
cogl_texture_pixmap_x11_is_using_tfp_extension (CoglHandle handle);

/**
 * cogl_is_texture_pixmap_x11:
 * @handle: A CoglHandle
 *
 * Checks whether @handle points to a CoglTexturePixmapX11 instance.
 *
 * Return value: %TRUE if the handle is a CoglTexturePixmapX11, and
 *   %FALSE otherwise
 *
 * Since: 1.4
 * Stability: Unstable
 */
gboolean
cogl_is_texture_pixmap_x11 (CoglHandle handle);

#endif /* COGL_ENABLE_EXPERIMENTAL_API */

#endif /* __COGL_TEXTURE_PIXMAP_X11_H */
