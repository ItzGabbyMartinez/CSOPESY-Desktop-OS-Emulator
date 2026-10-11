#pragma once

// Placeholder apps. Each draws its window only while *isOpen is true;
// the window's X button sets *isOpen back to false.
void renderApp1(bool* isOpen);
void renderApp2(bool* isOpen);