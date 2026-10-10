// GUYS TRY NOT TO EDIT THIS, MESSAGE ME FIRST (GABBY)

#include "task_manager.h"
#include "imgui.h"

void renderTaskManager(bool* isOpen)
{
    if (!*isOpen)
        return;

    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Task Manager", isOpen))
    {
        ImGui::Text("Processes");
        ImGui::Separator();

        if (ImGui::BeginTable(
                "ProcessTable",
                3,
                ImGuiTableFlags_Borders |
                ImGuiTableFlags_RowBg |
                ImGuiTableFlags_Resizable))
        {
            // Table headings
            ImGui::TableSetupColumn("Process");
            ImGui::TableSetupColumn("CPU");
            ImGui::TableSetupColumn("Memory");
            ImGui::TableHeadersRow();

            // Placeholder process data
            const char* processes[] = {
                "System",
                "Desktop",
                "Task Manager",
                "Application 1",
                "Application 2"
            };

            const char* cpuUsage[] = {
                "2.1%",
                "1.4%",
                "0.8%",
                "3.2%",
                "1.7%"
            };

            const char* memoryUsage[] = {
                "120 MB",
                "85 MB",
                "42 MB",
                "96 MB",
                "73 MB"
            };

            const int processCount =
                sizeof(processes) / sizeof(processes[0]);

            for (int i = 0; i < processCount; i++)
            {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", processes[i]);

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", cpuUsage[i]);

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", memoryUsage[i]);
            }

            ImGui::EndTable();
        }
    }

    ImGui::End();
}