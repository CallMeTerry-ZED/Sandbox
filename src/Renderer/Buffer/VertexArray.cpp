/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Renderer/Buffer/VertexArray.h"

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sandbox
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SANDBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		SANDBOX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}