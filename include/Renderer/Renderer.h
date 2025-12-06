/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef RENDERER_H
#define RENDERER_H

namespace FPS
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}

#endif