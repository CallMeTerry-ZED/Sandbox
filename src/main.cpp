/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */


#include "Core/Application/Application.h"
#include "Core/Logger/Logger.h"
#include "Core/EntryPoint.h"

class TestApp : public FPS::Application
{
public:
    TestApp()
    {

    }

    ~TestApp()
    {

    }
};

FPS::Application* FPS::CreateApplication()
{
    return new TestApp();
}
