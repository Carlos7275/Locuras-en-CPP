// Class for Creating Forms with Winapi Created by Carlos Sandoval 2024-05-03
#pragma once

#ifndef WindowsAPP
#define WindowsAPP
#include "IWindowsApp.cpp"
#include <CommCtrl.h>
#include <winuser.h>

class WindowsBase : public IWindowsApp
{

private:
    HWND hwnd;
    DWORD _style = WS_OVERLAPPEDWINDOW;
    LPCSTR _className;

    // Form Properties
    char *_titleApp = "Form";
    int _height = 0x80000000, _width = 0x80000000, _x = 0x80000000, _y = 0x80000000;
    bool _enableMaximize = true, _enableMinimize = true, _resizable = true;

protected:
    char *_font = "Microsoft Sans Serif";
    double _size = 8.25;
    bool _isNotEnd = true;

public:
    MSG msg = {};

    /**
     * @brief Set the Class Name object
     *
     * @param className
     */
    void SetClassName(LPCSTR className)
    {
        _className = className;
    }
    /**
     * @brief Set the Title App object
     *
     * @param titleApp
     */
    void SetTitleApp(char *titleApp)
    {
        _titleApp = titleApp;
    }
    /**
     * @brief Set the Font object
     *
     * @param font
     * @param size
     */
    void SetFont(char *font, double size)
    {
        _font = font;
        _size = size;
    }

    /**
     * @brief Set the Window Size object
     *
     * @param height
     * @param width
     */
    void SetWindowSize(int height, int width)
    {
        _height = height;
        _width = width;
    }

    /**
     * @brief Set the Windows Coords
     *
     * @param x
     * @param y
     */
    void SetCoords(int x, int y)
    {
        _x = x;
        _y = y;
    }
    /**
     * @brief Set the Maximize Status object
     *
     * @param status
     */
    void SetMaximizeStatus(bool status)
    {
        _enableMaximize = status;
    }

    /**
     * @brief Set the Minimize Status object
     *
     * @param status
     */
    void SetMinimizeStatus(bool status)
    {
        _enableMinimize = status;
    }
    /**
     * @brief Set the Resizable Status object
     *
     * @param status
     */
    void SetResizableStatus(bool status)
    {
        _resizable = status;
    }
    /**
     * @brief Get the Main Window Handle object
     *
     * @return HWND
     */
    HWND GetMainWindowHandle() const
    {
        return hwnd;
    }
    /**
     * @brief Set the Child Window Font object
     *
     * @param hwnd
     * @param hFont
     */
    void SetChildWindowFont(HWND hwnd, HFONT hFont)
    {
        // Set font for the current window
        SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Get the first child window
        HWND hwndChild = GetWindow(hwnd, GW_CHILD);
        // Iterate through all child windows
        while (hwndChild)
        {
            // Recursively set the font for each child window
            SetChildWindowFont(hwndChild, hFont);
            // Get the next child window
            hwndChild = GetWindow(hwndChild, GW_HWNDNEXT);
        }
    }
    /**
     * @brief Create a Windows Form
     *
     * @param hInstance
     * @param hPrevInstance
     * @param pCmdLine
     * @param nCmdShow
     * @return int
     */
    int Show(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
    {
        WNDCLASSA wc = {};

        wc.lpfnWndProc = StaticWindowProc<WindowsBase>;
        wc.hInstance = hInstance;
        wc.lpszClassName = _className; // Use the className parameter

        RegisterClassA(&wc);
        CheckStyles();

        hwnd = CreateWindowExA(
            0,
            _className,
            _titleApp,
            _style,
            _x,
            _y,
            _height,
            _width,
            NULL,
            NULL,
            hInstance,
            NULL);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        if (hwnd == NULL)
        {
            return 0;
        }

        ShowWindow(hwnd, nCmdShow);
        return 0;
    }

private:
    void CheckStyles()
    {
        if (!_enableMinimize)
            _style &= ~WS_MINIMIZEBOX;
        if (!_enableMaximize)
            _style &= ~WS_MAXIMIZEBOX;

        if (!_resizable)
            _style &= ~(WS_THICKFRAME | WS_SIZEBOX);
    }

protected:
    /**
     * @brief Convert WindowsHandler in Static Method
     *
     * @param hwnd
     * @param uMsg
     * @param wParam
     * @param lParam
     * @return LRESULT
     */
    template <class T>
    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        // Obtener el puntero al objeto WindowsApp almacenado en el GWLP_USERDATA
        T *pThis = reinterpret_cast<T *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        if (pThis)
            // Llamada al método no estático WindowProc
            return pThis->WindowProc(hwnd, uMsg, wParam, lParam);
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    /**
     * @brief
     *
     * @param hwnd
     * @param uMsg
     * @param wParam
     * @param lParam
     * @return LRESULT
     */
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            _isNotEnd = false;
            PostQuitMessage(0);
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1)); // Rellena con el color de fondo predeterminado de la ventana
            EndPaint(hwnd, &ps);
        }
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    /**
     * @brief Cycle Form
     *
     * @param type  1 is GetMessage default, 2 is for PeekMessage Cycle
     */
    void Cycle(int type = 1)
    {
        while (_isNotEnd)
        {
            if (type = 1)
                while (GetMessage(&msg, NULL, 0, 0))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            else if (type = 2)
                while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
        }
    }
};

#endif // WindowsAPP