
#include "ThemeManager.h"
#include <windows.h>

ThemeManager::ThemeManager() : m_backgroundColor(RGB(255, 255, 255)), m_iconSize(32) {}

void ThemeManager::SetWallpaper(const std::wstring& wallpaperPath) {
    m_wallpaperPath = wallpaperPath;
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)m_wallpaperPath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}

void ThemeManager::SetBackgroundColor(COLORREF color) {
    m_backgroundColor = color;
    // Here you need to implement the logic to change the background color of the application window
    // For example, you can send a message to the main window to repaint with the new color
    HWND hwnd = FindWindow(nullptr, L"Theme Application");
    if (hwnd) {
        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
    }
}

void ThemeManager::SetIconSize(int size) {
    m_iconSize = size;
    // Here you need to implement the logic to change the icon size of the application
    // This involves updating the system metrics for the icon size
    SystemParametersInfo(SPI_SETICONS, 0, (PVOID)(INT_PTR)m_iconSize, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}