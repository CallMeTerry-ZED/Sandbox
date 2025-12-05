/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

extern FPS::Application* FPS::CreateApplication();

int main(int argc, char** argv)
{
    FPS::Logger logger;

    auto app = FPS::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif
