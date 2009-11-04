/*
 * Cogl
 *
 * An object oriented GL/GLES Abstraction/Utility Layer
 *
 * Copyright (C) 2007,2008,2009 Intel Corporation.
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

#ifndef __COGL_CONTEXT_DRIVER_H
#define __COGL_CONTEXT_DRIVER_H

#include "cogl.h"
#include "cogl-gles2-wrapper.h"

typedef struct _CoglContextDriver

{
  COGL_PFNGLGENRENDERBUFFERSPROC                pf_glGenRenderbuffers;
  COGL_PFNGLDELETERENDERBUFFERSPROC             pf_glDeleteRenderbuffers;
  COGL_PFNGLBINDRENDERBUFFERPROC                pf_glBindRenderbuffer;
  COGL_PFNGLRENDERBUFFERSTORAGEPROC             pf_glRenderbufferStorage;
  COGL_PFNGLGENFRAMEBUFFERSPROC                 pf_glGenFramebuffers;
  COGL_PFNGLBINDFRAMEBUFFERPROC                 pf_glBindFramebuffer;
  COGL_PFNGLFRAMEBUFFERTEXTURE2DPROC            pf_glFramebufferTexture2D;
  COGL_PFNGLFRAMEBUFFERRENDERBUFFERPROC         pf_glFramebufferRenderbuffer;
  COGL_PFNGLCHECKFRAMEBUFFERSTATUSPROC          pf_glCheckFramebufferStatus;
  COGL_PFNGLDELETEFRAMEBUFFERSPROC              pf_glDeleteFramebuffers;
  COGL_PFNGLGENERATEMIPMAPPROC                  pf_glGenerateMipmap;

#ifdef HAVE_COGL_GLES2
  CoglGles2Wrapper  gles2;
#endif
} CoglContextDriver;

#endif /* __COGL_CONTEXT_DRIVER_H */

