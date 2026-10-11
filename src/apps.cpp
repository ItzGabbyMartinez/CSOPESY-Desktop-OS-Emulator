#include "apps.h"
#include "imgui.h"

void renderApp1(bool* isOpen)
{
    if (!*isOpen)
        return;

    ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(120, 120), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Application 1", isOpen))
    {
        ImGui::Text("Hello from Application 1!");
    }
    ImGui::End();
}

void renderApp2(bool* isOpen)
{
    if (!*isOpen)
        return;

    ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(200, 180), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Application 2", isOpen))
    {
        ImGui::Text("Hello from Application 2!");
    }
    ImGui::End();
}