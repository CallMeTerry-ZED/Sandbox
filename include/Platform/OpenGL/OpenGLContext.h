/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

 #ifndef OPENGL_CONTEXT_H
 #define OPENGL_CONTEXT_H

#include "Renderer/Context/GraphicsContext.h"

// Foward Declare GLFW window for now ig
struct GLFWwindow;

namespace Sandbox
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}

#endif