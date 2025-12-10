/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Core/Engine.h"

class ExampleLayer : public Sandbox::Layer
{
public:
    ExampleLayer() : Layer("Example")
    {
        // BOY IF YOU DONT STOP
    }

    void OnUpdate() override
    {
        //LOG_TRACE("ExampleLayer::Update");

        if (Sandbox::Input::IsKeyPressed(SANDBOX_KEY_TAB))
		LOG_TRACE("Tab key is pressed (poll)!");
    }

    virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();

        ImGui::Begin("Sandbox ENGINE");
        ImGui::Text("WELCOME TO Sandbox ENGINE!");
        ImGui::End();
	}

    void OnEvent(Sandbox::Event& event) override
    {
        //LOG_TRACE("{}", event.ToString());

        if (event.GetEventType() == Sandbox::EventType::KeyPressed)
		{
			Sandbox::KeyPressedEvent& e = (Sandbox::KeyPressedEvent&)event;
			if (e.GetKeyCode() == SANDBOX_KEY_TAB)
            {
                LOG_TRACE("Tab key is pressed (event)!");
            }
			LOG_TRACE("{} - Key code: {}", event.ToString(), e.GetKeyCode());
		}
    }
};

class TestApp : public Sandbox::Application
{
public:
    TestApp()
    {
        PushLayer(new ExampleLayer());
    }

    ~TestApp()
    {

    }
};

Sandbox::Application* Sandbox::CreateApplication()
{
    return new TestApp();
}
