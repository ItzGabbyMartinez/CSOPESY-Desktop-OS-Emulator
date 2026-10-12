# NEKOS Desktop Mock-up
### CSOPESY MO4 — Desktop-Style OS Mock-up

A desktop-style operating system mock-up developed for **CSOPESY**. The application simulates a basic desktop environment featuring a top menu bar, taskbar, and dummy system applications.

Built using **C++17, GLFW, OpenGL 3, and Dear ImGui**.
---

## Group Members

- **BANCORO, Maria Fides**
- **DIMAUNAHAN, Chelsea Jei**
- **MANALANG, Kennese Ross**
- **MARTINEZ, Gabrielle**
---
## Entry File

src/main.cpp

The main() function is located in source/main.cpp.

---

## Features

- **Desktop Environment** — Displays a wallpaper, live date and clock, and a power button.
- **Shutdown Confirmation** — Prompts for confirmation before shutting down the mock-up.
- **Taskbar** — Opens and manages applications within the desktop environment.
- **Task Manager** — Displays a process table containing process names, CPU usage, and memory usage.
- **File Explorer** — Displays a directory table containing file names, types, and sizes.
- **System Settings** — Includes a dark/light theme toggle, an accent color picker, and an *About OS* tab.

> **Note:** The File Explorer and Task Manager use hardcoded data for demonstration purposes only. Their contents do not reflect actual files, processes, or system resource usage on the machine.
---

## Technologies Used

- C++17
- GLFW 3
- OpenGL 3
- Dear ImGui
- MinGW-w64 / G++
- GNU Make

## Requirements

Before building and running the project, ensure the following are installed and configured:

- **Windows**
- C++17
- GLFW 3
- GNU Make (`make` or `mingw32-make`)

The provided `Makefile` links against `glfw3`, `opengl32`, and `gdi32`.

---
## Build and Run

1. Open a terminal in the project root directory.
2. Build the project using one of the following commands:

   ```bash
   make
   ```

   Or, on Windows with MinGW:

   ```bash
   mingw32-make
   ```

3. Run the generated executable:

   ```bash
   ./csopesy.exe
   ```
---
