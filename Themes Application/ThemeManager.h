#pragma once
#include <string>
#include <windows.h>

class ThemeManager {
public:
    ThemeManager();
    void SetWallpaper(const std::wstring& wallpaperPath);
    void SetBackgroundColor(COLORREF color);
    void SetIconSize(int size);

private:
    std::wstring m_wallpaperPath;
    COLORREF m_backgroundColor;
    int m_iconSize;
};

