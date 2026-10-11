#include "taskbar.h"
#include "imgui.h"

#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <cstdint>

namespace
{
    const float kTaskbarHeight = 56.0f;
    const ImVec2 kIconSize(32.0f, 32.0f);

    // Loads a PNG and uploads it to the GPU
    GLuint loadIcon(const char* path)
    {
        int w, h, ch;
        unsigned char* px = stbi_load(path, &w, &h, &ch, 4);
        if (!px)
            return 0;

        GLuint tex = 0;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, px);
        stbi_image_free(px);
        return tex;
    }
    
    void iconButton(const char* id, GLuint tex, const char* fallbackLabel, bool* isOpen)
    {
        const bool wasOpen = *isOpen;

        // Colors for the button frame (the shape behind the icon)
        // CLOSED = base color, OPEN = lit up
        const ImVec4 baseColor  = ImVec4(0.12f, 0.14f, 0.22f, 1.0f);   // dark navy
        const ImVec4 baseHover  = ImVec4(0.22f, 0.25f, 0.38f, 1.0f);
        const ImVec4 litColor   = ImVec4(0.25f, 0.55f, 1.00f, 1.0f);   // bright blue
        const ImVec4 litHover   = ImVec4(0.35f, 0.65f, 1.00f, 1.0f);
        
        ImGui::PushStyleColor(ImGuiCol_Button,        wasOpen ? litColor : baseColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, wasOpen ? litHover : baseHover);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  wasOpen ? litColor : baseHover);

        bool clicked;
        if (tex != 0)
            clicked = ImGui::ImageButton(id, (ImTextureID)(intptr_t)tex, kIconSize);
        else
            clicked = ImGui::Button(fallbackLabel, ImVec2(80.0f, 64.0f));

        ImGui::PopStyleColor(3);

        if (clicked)
            *isOpen = !*isOpen;
    }
}

void renderTaskbar(bool* showTaskManager, bool* showApp1, bool* showApp2)
{
    static GLuint tasksIcon = loadIcon("assets/icon_tasks.jpg");
    static GLuint app1Icon  = loadIcon("assets/icon_app1.jpg");
    static GLuint app2Icon  = loadIcon("assets/icon_app2.jpg");

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(
        ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - kTaskbarHeight));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, kTaskbarHeight));

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.07f, 0.09f, 0.16f, 0.95f));

    ImGui::Begin("Taskbar", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar |
                 ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoSavedSettings);

    iconButton("##tasks", tasksIcon, "Tasks", showTaskManager);
    ImGui::SameLine();
    iconButton("##app1", app1Icon, "App 1", showApp1);
    ImGui::SameLine();
    iconButton("##app2", app2Icon, "App 2", showApp2);

    ImGui::End();
    ImGui::PopStyleColor();
}