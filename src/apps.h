#pragma once

// Placeholder apps. Each draws its window only while *isOpen is true;
// the window's X button sets *isOpen back to false.
void renderFileExplorer(bool* isOpen);
void renderSystemSettings(bool* isOpen);