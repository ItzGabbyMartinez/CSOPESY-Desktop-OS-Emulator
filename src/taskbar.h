#pragma once
 
// Draws the fixed taskbar at the bottom of the screen.
// Each bool is an app's open/close state
// and the app windows set it to false themselves when X is clicked.
// Call LAST each frame so the taskbar is drawn on top.
void renderTaskbar(bool* showTaskManager, bool* showApp1, bool* showApp2);
