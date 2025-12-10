/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

extern Sandbox::Application* Sandbox::CreateApplication();

int main()
{
    Sandbox::Logger logger;

    auto app = Sandbox::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif
