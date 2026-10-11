#include "desktop.h"
#include "imgui.h"

#include <GLFW/glfw3.h>   // used to upload the wallpaper

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"    // loads the PNG file

#include <cstdint>
#include <ctime>

namespace
{
    // Wallpaper file. Run the .exe from the project root folder.
    const char* wallpaperpath = "assets/wallpaper.png";

    GLuint wallpaperTexture = 0;
    int wallpaperWidth = 0;
    int wallpaperHeight = 0;
    bool wallpaperTried = false;

    // Window visibility state flags for Apps 1 and 2
    bool showApp1 = false;
    bool showApp2 = false;

    // Loads the PNG once and turns it into an OpenGL texture.
    void loadWallpaper()
    {
        wallpaperTried = true; 
        int channels = 0;
        unsigned char* pixels = stbi_load(
            wallpaperpath, &wallpaperWidth, &wallpaperHeight, &channels, 4);

        if (pixels == nullptr)
            return;
        
        // Create an OpenGL texture from the loaded image
        glGenTextures(1, &wallpaperTexture);
        glBindTexture(GL_TEXTURE_2D, wallpaperTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     wallpaperWidth, wallpaperHeight, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        stbi_image_free(pixels);
    }

    // Fills the buffers with the current local date and time.
    void getClockStrings(char* dateBuf, size_t dateLen, char* timeBuf, size_t timeLen)
    {
        std::time_t now = std::time(nullptr);
        std::tm* local = std::localtime(&now);
        std::strftime(dateBuf, dateLen, "%A | %m/%d/%Y", local);
        std::strftime(timeBuf, timeLen, "%I:%M:%S %p", local);
    }

    // Draws the wallpaper over the whole screen.
    void drawWallpaper(ImDrawList* drawList, ImVec2 pos, ImVec2 size)
    {
        ImVec2 bottomRight(pos.x + size.x, pos.y + size.y);

        if (wallpaperTexture != 0)
        {
            drawList->AddImage((ImTextureID)(intptr_t)wallpaperTexture, pos, bottomRight);
        }
        else
        {
            drawList->AddRectFilled(pos, bottomRight, IM_COL32(24, 40, 84, 255));
        }
    }

    // Application 1: File Explorer
    void renderFileExplorerWindow(bool* open)
    {
        if (!*open) return;

        ImGui::SetNextWindowSize(ImVec2(580, 360), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("File Explorer", open, ImGuiWindowFlags_MenuBar))
        {
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("New Folder")) {}
                    if (ImGui::MenuItem("Close")) { *open = false; }
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
    void renderSystemSettingsWindow(bool* open)
    {
        if (!*open) return;

        ImGui::SetNextWindowSize(ImVec2(480, 340), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("System Settings", open))
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
                    ImGui::TextWrapped("Made by CSOPESY Group 1: Bancoro, Dimaunahan, Manalang, and Martinez");
                    ImGui::TextWrapped("Built using GLFW, OpenGL3, and Dear ImGui.");
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
}

void renderDesktop(bool* running)
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    if (!wallpaperTried)
        loadWallpaper();

    // Wallpaper background layer
    drawWallpaper(ImGui::GetBackgroundDrawList(), viewport->Pos, viewport->Size);

    // ---- Top Main Menu Bar ----
    char dateText[48];
    char timeText[32];
    getClockStrings(dateText, sizeof(dateText), timeText, sizeof(timeText));

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.0f, 10.0f));
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.07f, 0.09f, 0.16f, 0.95f));

    if (ImGui::BeginMainMenuBar())
    {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("CSOPESY Desktop OS");

        const float spacing = 24.0f;
        const float buttonWidth = 64.0f;
        float dateWidth = ImGui::CalcTextSize(dateText).x;
        float timeWidth = ImGui::CalcTextSize(timeText).x;
        float totalWidth = dateWidth + spacing + timeWidth + spacing + buttonWidth;

        ImGui::SameLine(ImGui::GetWindowWidth() - totalWidth - 16.0f);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", dateText);

        ImGui::SameLine(0.0f, spacing);
        ImGui::Text("%s", timeText);

        // Shutdown Button
        ImGui::SameLine(0.0f, spacing);
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.75f, 0.15f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.90f, 0.25f, 0.25f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.60f, 0.10f, 0.10f, 1.0f));
        if (ImGui::Button("PWR", ImVec2(buttonWidth, 0.0f)))
            ImGui::OpenPopup("Shut Down?");
        ImGui::PopStyleColor(3);

        // Modal Shutdown Confirmation
        ImGui::SetNextWindowPos(
            ImVec2(viewport->Pos.x + viewport->Size.x * 0.5f,
                   viewport->Pos.y + viewport->Size.y * 0.5f),
            ImGuiCond_Appearing,
            ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("Shut Down?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Are you sure you want to shut down?");
            ImGui::Separator();

            if (ImGui::Button("Shut Down", ImVec2(120, 0)))
            {
                *running = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("Cancel", ImVec2(120, 0)))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }

        ImGui::EndMainMenuBar();
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    // taskbar
    float taskbarHeight = 48.0f;
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - taskbarHeight));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, taskbarHeight));
    
    ImGuiWindowFlags taskbarFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
                                    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | 
                                    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 8.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.07f, 0.09f, 0.16f, 0.95f));

    if (ImGui::Begin("Taskbar", nullptr, taskbarFlags))
    {
        if (ImGui::Button("File Explorer", ImVec2(120, 0))) showApp1 = !showApp1;
        ImGui::SameLine();
        if (ImGui::Button("Settings", ImVec2(100, 0)))      showApp2 = !showApp2;
    }
    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

    // rendering the apps
    renderFileExplorerWindow(&showApp1);
    renderSystemSettingsWindow(&showApp2);
}