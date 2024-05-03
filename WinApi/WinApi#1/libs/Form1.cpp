#ifndef Form_CPP
#define Form_CPP

#include "WindowsApp.cpp"
#include "stdio.h"

class Form : public WindowsApp
{
public:
    int Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
    {
        WindowsApp::Run(hInstance, hPrevInstance, pCmdLine, nCmdShow);
        HWND m_hWnd = GetMainWindowHandle();
        // Create a button
        HWND hwndButton = CreateWindow(
            L"BUTTON",                                             // Predefined class; Unicode assumed
            L"Click Me",                                           // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
            10,                                                    // x position
            10,                                                    // y position
            100,                                                   // Button width
            50,                                                    // Button height
            m_hWnd,
            NULL, // No menu.
            (HINSTANCE)GetWindowLongPtr(m_hWnd, GWLP_HINSTANCE),
            NULL // Pointer not needed.
        );

        // Show the button
        ShowWindow(hwndButton, SW_SHOWNORMAL);
        UpdateWindow(hwndButton);

        printf("here");

        return 0;
    }
};
#endif // Form_CPP
