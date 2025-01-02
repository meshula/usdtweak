#pragma once

#define GL_SILENCE_DEPRECATION 1

/// ImGui includes
#include "imgui.h"

#ifdef HAVE_GLFW3
#include "imgui_impl_glfw.h"
#endif
#ifdef HAVE_OPENGL3
#include "imgui_impl_opengl3.h"
#endif
#include "imgui_internal.h"
#include "imgui_stdlib.h"

/// glfw
#ifdef HAVE_GLFW3
#include <GLFW/glfw3.h>
#endif

/// Icons font
#include "IconsFontAwesome5.h"
