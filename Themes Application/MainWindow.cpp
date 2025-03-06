#include "MainWindow.h"
#include "resource.h"  // Ensure this header file includes definitions for ID_CHANGE_WALLPAPER, ID_CHANGE_COLOR, and ID_CHANGE_ICON_SIZE
#include <iostream>

MainWindow::MainWindow(HINSTANCE hInstance, ThemeManager* themeManager) : m_hInstance(hInstance), m_themeManager(themeManager), m_hWnd(nullptr) {}

BOOL MainWindow::Create(LPCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu) {
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = MainWindow::WindowProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = L"MainWindowClass";

    if (!RegisterClass(&wc)) {
        MessageBox(nullptr, L"Failed to register window class", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    m_hWnd = CreateWindowEx(dwExStyle, L"MainWindowClass", lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, m_hInstance, this);

    if (!m_hWnd) {
        MessageBox(nullptr, L"Failed to create window", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    return TRUE;
}

HWND MainWindow::Window() const {
    return m_hWnd;
}

void MainWindow::OnPaint() {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(m_hWnd, &ps);
    // Add painting code here
    EndPaint(m_hWnd, &ps);
}

void MainWindow::OnCommand(WPARAM wParam) {
    switch (LOWORD(wParam)) {
    case ID_CHANGE_WALLPAPER:
        m_themeManager->SetWallpaper(L"path/to/wallpaper.jpg");
        break;
    case ID_CHANGE_COLOR:
        m_themeManager->SetBackgroundColor(RGB(0, 128, 255));
        break;
    case ID_CHANGE_ICON_SIZE:
        m_themeManager->SetIconSize(48);
        break;
    default:
        break;
    }
}

LRESULT CALLBACK MainWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    MainWindow* pThis = nullptr;

    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (MainWindow*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->m_hWnd = hWnd;
    }
    else {
        pThis = (MainWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (pThis) {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    else {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT:
        OnPaint();
        return 0;
    case WM_COMMAND:
        OnCommand(wParam);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
    }
}