#pragma once

// Draws the full-screen background, clock, and PWR button.
// Call FIRST each frame so everything else renders on top.
// running: set to false when the user confirms shutdown.
void renderDesktop(bool* running);

void renderFileExplorer(bool* open);
void renderSystemSettings(bool* open);