#include <windows.h>
#include "ThemeManager.h"
#include "MainWindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    ThemeManager themeManager;
    MainWindow mainWindow(hInstance, &themeManager);

    if (!mainWindow.Create(L"Theme Application", WS_OVERLAPPEDWINDOW)) {
        return 0;
    }

    ShowWindow(mainWindow.Window(), nCmdShow);
    UpdateWindow(mainWindow.Window());

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}