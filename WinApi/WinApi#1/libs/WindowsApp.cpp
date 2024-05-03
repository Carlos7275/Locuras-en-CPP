#pragma once
#ifndef WindowsAPP
#define WindowsAPP
#include "IWindowsApp.cpp"

class WindowsApp : public IWindowsApp
{

private:
    HWND hwnd;
    LPCSTR _className;
    char *_titleApp = "HelloWorld";

public:
    void SetClassName(LPCSTR className)
    {
        _className = className;
    }

    void SetTitleApp(char *titleApp)
    {
        _titleApp = titleApp;
    }
    HWND GetMainWindowHandle() const
    {
        return hwnd;
    }
    int Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
    {
        // Register the window class.
        WNDCLASSA wc = {};

        wc.lpfnWndProc = StaticWindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = _className; // Use the className parameter

        RegisterClassA(&wc);

        // Create the window.
        hwnd = CreateWindowExA(
            0,                   // Optional window styles.
            _className,          // Use the className parameter
            _titleApp,           // Window text (using ANSI string)
            WS_OVERLAPPEDWINDOW, // Window style
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL, NULL, hInstance, NULL);

        if (hwnd == NULL)
        {
            return 0;
        }

        ShowWindow(hwnd, nCmdShow);

        // Run the message loop.
        MSG msg = {};
        while (GetMessage(&msg, NULL, 0, 0) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 0;
    }

private:
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        // Obtener el puntero al objeto WindowsApp almacenado en el GWLP_USERDATA
        WindowsApp *pThis = reinterpret_cast<WindowsApp *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        if (pThis)
        {
            // Llamada al método no estático WindowProc
            return pThis->WindowProc(hwnd, uMsg, wParam, lParam);
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
};

#endif // WindowsAPP