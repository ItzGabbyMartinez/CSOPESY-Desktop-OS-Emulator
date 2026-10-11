#include <iostream>

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

//To connect our separate files
#include "desktop.h"
#include "task_manager.h"

// Set to false while developing if you want a normal 1280x720 window
static const bool kFullscreen = true;

int main()
{
    // Initialize GLFW (Starting point)
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW.\n";
        return 1;
    }

    // Configure OpenGL (Change niyo to if need for the GUI)
    const char* glslVersion = "#version 130";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create the main application window (1280 x 720, change this if you guys need)
    // Fullscreen uses the primary monitor's current resolution
    GLFWwindow* window = nullptr;

    if (kFullscreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        window = glfwCreateWindow(
            mode->width,
            mode->height,
            "CSOPESY Desktop OS Emulator",
            monitor,
            nullptr
        );
    }
    else
    {
        window = glfwCreateWindow(
            1280,
            720,
            "CSOPESY Desktop OS Emulator",
            nullptr,
            nullptr
        );
    }

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize Dear ImGui 
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    // System state: set to false by the PWR button on the desktop
    bool running = true;

    // Temporary state for testing the Task Manager (Tanngalin niyo na lang)
    bool showTaskManager = true;

    // Main application loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render system components (desktop first = at the back)
        renderDesktop(&running);
        renderTaskManager(&showTaskManager);

        // PWR button confirmed shutdown
        if (!running)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        // Render ImGui
        ImGui::Render();

        int displayWidth;
        int displayHeight;

        glfwGetFramebufferSize(
            window,
            &displayWidth,
            &displayHeight
        );

        glViewport(0, 0, displayWidth, displayHeight);
        glClearColor(0.10f, 0.10f, 0.10f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Clean up resources (For Shutdown)
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}