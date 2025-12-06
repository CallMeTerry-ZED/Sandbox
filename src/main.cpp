/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */


#include "Core/Engine.h"

class ExampleLayer : public FPS::Layer
{
public:
    ExampleLayer() : Layer("Example")
    {
    }

    void OnUpdate() override
    {
         //LOG_TRACE("ExampleLayer::Update");
    }

    void OnEvent(FPS::Event& event) override
    {
        //LOG_TRACE("{}", event.ToString());
    }

};

class TestApp : public FPS::Application
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

FPS::Application* FPS::CreateApplication()
{
    return new TestApp();
}
