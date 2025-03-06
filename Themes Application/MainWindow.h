#pragma once
#include <windows.h>
#include "ThemeManager.h"

class MainWindow {
public:
    MainWindow(HINSTANCE hInstance, ThemeManager* themeManager);
    BOOL Create(LPCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, HWND hWndParent = 0, HMENU hMenu = 0);
    HWND Window() const;

protected:
    void OnPaint();
    void OnCommand(WPARAM wParam);
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    HWND m_hWnd;
    HINSTANCE m_hInstance;
    ThemeManager* m_themeManager;
};
