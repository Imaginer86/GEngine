#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <Windows.h>
#include    <GL/gl.h>
#include    <GL/glu.h>
#include    "glext.h"

void    initExtensions();

extern PFNGLGENBUFFERSPROC glGenBuffers;

typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
GLAPI void APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);