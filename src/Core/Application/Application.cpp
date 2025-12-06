/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired By The Cherno
 * Referenced https://github.com/TheCherno/Hazel/blob/f9fbbd2bf3d870a6586c5c4f70a867d78e27b113/Hazel/src/Hazel/Application.cpp
 *
 */

#include "Core/Application/Application.h"
#include "Core/Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Core/Logger/Logger.h"

#include <glad.h>

namespace FPS
{
    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case FPS::ShaderDataType::Float:    return GL_FLOAT;
			case FPS::ShaderDataType::Float2:   return GL_FLOAT;
			case FPS::ShaderDataType::Float3:   return GL_FLOAT;
			case FPS::ShaderDataType::Float4:   return GL_FLOAT;
			case FPS::ShaderDataType::Mat3:     return GL_FLOAT;
			case FPS::ShaderDataType::Mat4:     return GL_FLOAT;
			case FPS::ShaderDataType::Int:      return GL_INT;
			case FPS::ShaderDataType::Int2:     return GL_INT;
			case FPS::ShaderDataType::Int3:     return GL_INT;
			case FPS::ShaderDataType::Int4:     return GL_INT;
			case FPS::ShaderDataType::Bool:     return GL_BOOL;
		}
		
		FPS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

    Application::Application()
    {
        if (s_Instance)
        {
            LOG_ERROR("Application already exists!");
            return;
        }
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetQueueEventCallback([this](std::unique_ptr<Event> e) {
            this->QueueEvent(std::move(e));
        });

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
		}

        uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

        uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
            out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
            in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        IsRunning = true;
    }

    Application::~Application()
    {
        IsRunning = false;
    }

    void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

    void Application::OnEvent(Event& event)
    {
        // Dispatch to layers (overlays first, then regular layers)
        // Overlays are at the end, so iterates in reverse
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(event);
            if (event.IsHandled())
            {
                break;
            }
        }

        // EventDispatcher for type-safe event handling
        EventDispatcher dispatcher(event);

        // Handle WindowCloseEvent
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {
            LOG_INFO("Window close event");
            IsRunning = false;
            return true;
        });

        // Handle WindowResizeEvent
        dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& e) {
            LOG_INFO("Window resized: {}x{}", e.GetWidth(), e.GetHeight());
            return false;
        });

        // Handle KeyPressedEvent
        dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e) {
            LOG_DEBUG("Key pressed: {}", e.GetKeyCode());
            return false;
        });
    }

    void Application::QueueEvent(std::unique_ptr<Event> event)
    {
        m_EventQueue.push_back(std::move(event));
    }

    void Application::ProcessEvents()
    {
        // Process all queued events
        for (auto& event : m_EventQueue)
        {
            OnEvent(*event);
        }
        m_EventQueue.clear();
    }

    void Application::Run()
    {
        while (IsRunning)
        {
            // Process deferred events always first
            ProcessEvents();

            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            // Update all layers
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }
}
