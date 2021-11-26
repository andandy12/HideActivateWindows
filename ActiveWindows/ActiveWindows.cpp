// ActiveWindows.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <windows.h>
#include <iostream>
#define toggle
void moveWindow(bool Relative, int NewX, int NewY, HWND WindowToMove) {
    RECT Result;
    if (GetWindowRect(WindowToMove, &Result)) {
        printf("Window Currently At: %ld, %ld\n", Result.left, Result.top);
        LONG Height = Result.bottom - Result.top;
        LONG Width =  Result.right - Result.left;
        if (Relative) {
            NewX += Result.left;
            NewY += Result.top;
        }
        printf("Height/Width: %ld/%ld\n", Height, Width);
        if (MoveWindow(WindowToMove, NewX, NewY, Width, Height, TRUE)) {
            if (GetWindowRect(WindowToMove, &Result)) {
                printf("Moved Window To: %ld, %ld\n", Result.left, Result.top);
            }
        }
    }
}
// Toggle Active Windows Watermark

int main() {
    HWND windowActivateWindows = FindWindowA("Worker Window", NULL);
    std::printf("Found Worker Window: %llx \n", windowActivateWindows);
    if (windowActivateWindows != NULL) {
        if (IsWindowVisible(windowActivateWindows)) {
            ShowWindow(windowActivateWindows, SW_HIDE);
            std::printf("Toggling to hide: %llx\n", windowActivateWindows);
            moveWindow(FALSE, -49, -243, windowActivateWindows);
        } else {
#ifdef toggle
            ShowWindow(windowActivateWindows, SW_SHOW);
            std::printf("Toggling to show: %llx\n", windowActivateWindows);
            moveWindow(FALSE, 0, 0, windowActivateWindows); // we could move it to original spot but there is never really a need to turn it back on
#else
            printf("Window is already hidden");
#endif
        }
    }
}
