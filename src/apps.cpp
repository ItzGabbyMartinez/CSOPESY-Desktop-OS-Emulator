#include "apps.h"
#include "imgui.h"

// Application 1: File Explorer
void renderFileExplorer(bool* isOpen)
{
    if (!*isOpen)
        return;

    ImGui::SetNextWindowSize(ImVec2(580, 360), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(120, 120), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("File Explorer - CSOPESY OS", isOpen, ImGuiWindowFlags_MenuBar))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Folder")) {}
                if (ImGui::MenuItem("Close")) { *isOpen = false; }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Refresh")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Text("Path:");
        ImGui::SameLine();
        static char currentPath[128] = "C:/CSOPESY/Documents";
        ImGui::InputText("##pathbuf", currentPath, IM_ARRAYSIZE(currentPath));
        ImGui::Separator();

        ImGui::Columns(2, "ExplorerSplit", true);
        ImGui::SetColumnWidth(0, 150.0f);

        // Left Navigation Pane
        ImGui::TextDisabled("DIRECTORIES");
        if (ImGui::TreeNode("Local Disk (C:)"))
        {
            if (ImGui::TreeNode("System"))
            {
                ImGui::Selectable("Drivers");
                ImGui::Selectable("Logs");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Documents"))
            {
                ImGui::Selectable("Projects");
                ImGui::Selectable("Assignments");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        ImGui::NextColumn();

        // Right File Contents Pane
        ImGui::TextDisabled("FILES");
        if (ImGui::BeginTable("FileTable", 3, ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 80.0f);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 70.0f);
            ImGui::TableHeadersRow();

            const char* names[] = { "csopesy.exe", "kernel32.dll", "config.sys", "readme.txt" };
            const char* types[] = { "Application", "System DLL", "System", "Text Doc" };
            const char* sizes[] = { "1,240 KB", "512 KB", "2 KB", "14 KB" };

            for (int i = 0; i < 4; i++)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Selectable(names[i]);
                ImGui::TableSetColumnIndex(1);
                ImGui::TextUnformatted(types[i]);
                ImGui::TableSetColumnIndex(2);
                ImGui::TextUnformatted(sizes[i]);
            }
            ImGui::EndTable();
        }

        ImGui::Columns(1);
    }
    ImGui::End();
}

// Application 2: System Settings
void renderSystemSettings(bool* isOpen)
{
    if (!*isOpen)
        return;

    ImGui::SetNextWindowSize(ImVec2(480, 340), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(200, 180), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("System Settings - CSOPESY OS", isOpen))
    {
        if (ImGui::BeginTabBar("SettingsTabs"))
        {
            if (ImGui::BeginTabItem("Display"))
            {
                ImGui::Spacing();
                ImGui::Text("Appearance Preferences");
                ImGui::Separator();

                static int themeMode = 1;
                if (ImGui::RadioButton("Dark Theme", &themeMode, 1))
                    ImGui::StyleColorsDark();
                ImGui::SameLine();
                if (ImGui::RadioButton("Light Theme", &themeMode, 0))
                    ImGui::StyleColorsLight();

                static float accentColor[3] = { 0.2f, 0.4f, 0.8f };
                ImGui::ColorEdit3("Accent Color", accentColor);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("About OS"))
            {
                ImGui::Spacing();
                ImGui::Text("CSOPESY Desktop OS Emulator");
                ImGui::Text("Version 1.0 (Build 2026)");
                ImGui::Separator();
                ImGui::TextWrapped("Developed by CSOPESY Group 1: Bancoro, Dimaunahan, Manalang, and Martinez.");
                ImGui::TextWrapped("Built using GLFW, OpenGL3, and Dear ImGui.");
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
    ImGui::End();
}