# CSOPESY Desktop-Style OS Mock-up
#
# Purpose:
# Builds the application using g++, GLFW, OpenGL, and Dear ImGui.

CXX = g++

TARGET = csopesy.exe

IMGUI = lib/imgui

SOURCES = \
	src/main.cpp \
	src/task_manager.cpp \
	$(IMGUI)/imgui.cpp \
	$(IMGUI)/imgui_draw.cpp \
	$(IMGUI)/imgui_tables.cpp \
	$(IMGUI)/imgui_widgets.cpp \
	$(IMGUI)/backends/imgui_impl_glfw.cpp \
	$(IMGUI)/backends/imgui_impl_opengl3.cpp

INCLUDES = \
	-I$(IMGUI) \
	-I$(IMGUI)/backends

LIBS = -lglfw3 -lopengl32 -lgdi32

CXXFLAGS = -std=c++17 -Wall -Wextra

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)