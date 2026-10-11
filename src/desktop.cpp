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
    // Chosen Date format: Day | mm/dd/yyyy  
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
            // Backup if the PNG can't be loaded: plain dark blue
            drawList->AddRectFilled(pos, bottomRight, IM_COL32(24, 40, 84, 255));
        }
    }
}

void renderDesktop(bool* running)
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    if (!wallpaperTried)
        loadWallpaper();

    // Wallpaper: drawn on ImGui's background layer, so it is always behind every window 
    drawWallpaper(ImGui::GetBackgroundDrawList(), viewport->Pos, viewport->Size);

    // ---- Top bar: title on the left; date, time and PWR on the right ----
    char dateText[48];
    char timeText[32];
    getClockStrings(dateText, sizeof(dateText), timeText, sizeof(timeText));

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.0f, 10.0f));  // makes the bar taller
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.07f, 0.09f, 0.16f, 0.95f));

    if (ImGui::BeginMainMenuBar())
    {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("CSOPESY Desktop OS");

        // Push the date, time and PWR button to the right edge of the bar
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

        // PWR button (red)
            ImGui::SameLine(0.0f, spacing);
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.75f, 0.15f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.90f, 0.25f, 0.25f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.60f, 0.10f, 0.10f, 1.0f));
        if (ImGui::Button("PWR", ImVec2(buttonWidth, 0.0f)))
            ImGui::OpenPopup("Shut Down?");
        ImGui::PopStyleColor(3);

        ImGui::PopStyleVar();   // back to normal padding for the popup below

        // Shutdown confirmation popup after pressing PWR button
        ImGui::SetNextWindowPos(
            ImVec2(viewport->Pos.x + viewport->Size.x * 0.5f,
                   viewport->Pos.y + viewport->Size.y * 0.5f),
            ImGuiCond_Appearing,
            ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("Shut Down?", nullptr,
                                   ImGuiWindowFlags_AlwaysAutoResize))
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
    else
    {
        ImGui::PopStyleVar();
    }

    ImGui::PopStyleColor();   // menu bar color
}