#ifndef Form_CPP
#define Form_CPP

#include "WindowsApp.cpp"
#include "Calculator.cpp"
#include "../headers/Enums.h"
#include "windows.h"
#include <string>

class Form : public WindowsBase
{
public:
    /**
     * @brief  Overloading for Method Running With Structured Form
     *
     * @param hInstance
     * @param hPrevInstance
     * @param pCmdLine
     * @param nCmdShow
     * @return int
     */
    int Show(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
    {
        WindowsBase::Show(hInstance, hPrevInstance, pCmdLine, nCmdShow);
        HWND mainWindowHandle = WindowsBase::GetMainWindowHandle(); // Cambiado de "HWND m_hWnd = GetMainWindowHandle();" a "WindowsApp::GetMainWindowHandle();"

        SetWindowLongPtr(mainWindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        SetWindowLongPtr(mainWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&StaticWindowProc<Form>));

        HWND hwndLabel = CreateWindowEx(
            WS_EX_TRANSPARENT,
            "STATIC",               // Clase de control de edición
            "Ingrese un Numero",    // Texto inicial (vacío en este caso)
            WS_VISIBLE | WS_CHILD | // Estilos de ventana
                ES_AUTOHSCROLL,
            10, 10,                                                        // Posición (x, y)
            80, 25,                                                        // Tamaño (ancho, alto)
            mainWindowHandle,                                              // Ventana principal como padre
            (HMENU)-1,                                                     // Menú (NULL para ninguno)
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE), // Instancia del módulo
            NULL                                                           // Parámetro de creación (NULL en este caso)
        );

        HWND hwndLabel2 = CreateWindowEx(
            WS_EX_TRANSPARENT,
            "STATIC",               // Clase de control de edición
            "Ingrese otro Numero",  // Texto inicial (vacío en este caso)
            WS_VISIBLE | WS_CHILD | // Estilos de ventana
                ES_AUTOHSCROLL,
            10, 35,                                                        // Posición (x, y)
            80, 30,                                                        // Tamaño (ancho, alto)
            mainWindowHandle,                                              // Ventana principal como padre
            (HMENU)-1,                                                     // Menú (NULL para ninguno)
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE), // Instancia del módulo
            NULL                                                           // Parámetro de creación (NULL en este caso)
        );

        HWND hwndRes = CreateWindowEx(
            WS_EX_TRANSPARENT,
            "STATIC",               // Clase de control de edición
            "",                     // Texto inicial (vacío en este caso)
            WS_VISIBLE | WS_CHILD | // Estilos de ventana
                ES_AUTOHSCROLL,
            10, 150, // Posición (x, y)
            150,
            30,                                                            // Tamaño (ancho, alto)
            mainWindowHandle,                                              // Ventana principal como padre
            (HMENU)LBRES,                                                  // Menú (NULL para ninguno)
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE), // Instancia del módulo
            NULL                                                           // Parámetro de creación (NULL en este caso)
        );

        HWND hwndEdit = CreateWindow(
            "EDIT",                 // Clase de control de edición
            "",                     // Texto inicial (vacío en este caso)
            WS_VISIBLE | WS_CHILD | // Estilos de ventana
                WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
            100, 10,                                                       // Posición (x, y)
            200, 25,                                                       // Tamaño (ancho, alto)
            mainWindowHandle,                                              // Ventana principal como padre
            (HMENU)TNUM1,                                                  // Menú (NULL para ninguno)
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE), // Instancia del módulo
            NULL                                                           // Parámetro de creación (NULL en este caso)
        );
        HWND hwndEdit2 = CreateWindow(
            "EDIT",                 // Clase de control de edición
            "",                     // Texto inicial (vacío en este caso)
            WS_VISIBLE | WS_CHILD | // Estilos de ventana
                WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
            100, 35,                                                       // Posición (x, y)
            200, 25,                                                       // Tamaño (ancho, alto)
            mainWindowHandle,                                              // Ventana principal como padre
            (HMENU)TNUM2,                                                  // Menú (NULL para ninguno)
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE), // Instancia del módulo
            NULL                                                           // Parámetro de creación (NULL en este caso)
        );

        HWND buttonHandle = CreateWindow(
            "BUTTON",
            "+",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, // Estilo de botón de radio
            50, 70,
            30, 30,
            mainWindowHandle,
            (HMENU)RADD,
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE),
            NULL);

        HWND buttonHandle2 = CreateWindow(
            "BUTTON",
            "-",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, // Estilo de botón de radio y de grupo
            80, 70,
            30, 30,
            mainWindowHandle,
            (HMENU)RSUB,
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE),
            NULL);

        HWND buttonHandle3 = CreateWindow(
            "BUTTON",
            "*",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, // Estilo de botón de radio
            110, 70,
            30, 30,
            mainWindowHandle,
            (HMENU)RMUL,
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE),
            NULL);

        HWND buttonHandle4 = CreateWindowW(
            L"BUTTON",
            L"÷",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, // Estilo de botón de radio
            140, 70,
            30, 30,
            mainWindowHandle,
            (HMENU)RDIV,
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE),
            NULL);

        HWND hwndButton = CreateWindow(
            "BUTTON",                                              // Predefined class; Unicode assumed
            "Calcular",                                            // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
            100,                                                   // x position
            100,                                                   // y position
            60,                                                    // Button width
            20,                                                    // Button height
            mainWindowHandle,                                      // Parent window
            (HMENU)BTNCALC,                                        // No menu.
            (HINSTANCE)GetWindowLongPtr(mainWindowHandle, GWLP_HINSTANCE),
            NULL // Pointer not needed.
        );

        // Show the button
        ShowWindow(hwndButton, nCmdShow);
        UpdateWindow(hwndButton);
        _size = -MulDiv(_size, GetDeviceCaps(GetDC(mainWindowHandle), LOGPIXELSY), 72);

        HFONT hFont = CreateFont(
            _size,               // Height
            0,                   // Width
            0,                   // Escapement
            0,                   // Orientation
            FW_NORMAL,           // Weight
            FALSE,               // Italic
            FALSE,               // Underline
            FALSE,               // StrikeOut
            DEFAULT_CHARSET,     // CharSet
            OUT_DEFAULT_PRECIS,  // OutPrecision
            CLIP_DEFAULT_PRECIS, // ClipPrecision
            DEFAULT_QUALITY,     // Quality
            DEFAULT_PITCH,       // PitchAndFamily
            _font                // FaceName
        );
        SetChildWindowFont(mainWindowHandle, hFont);

        this->Cycle(2);
        return 0;
    }

    virtual LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        // Llamamos al WindProc Base que contiene el pintado de la app y el evento cerrar
        LRESULT result = WindowsBase::WindowProc(hWnd, message, wParam, lParam);

        switch (message)
        {
        case WM_COMMAND:

            if (LOWORD(wParam) == BTNCALC)
            {
                int operation = GetSelectedRadioButton(hWnd, 4, RADD);
                char strNum1[256], strNum2[256];
                char *endptr;

                HWND hwndNum1 = GetDlgItem(hWnd, TNUM1);
                HWND hwndNum2 = GetDlgItem(hWnd, TNUM2);
                HWND hwndLabel = GetDlgItem(hWnd, LBRES);

                GetWindowTextA(hwndNum1, strNum1, 256);
                GetWindowTextA(hwndNum2, strNum2, 256);

                double num1 = 0.0, num2 = 0.0, res = 0.0;
                num1= strtod(strNum1, &endptr), num2 = strtod(strNum2, &endptr);

                Calculator* objCalc = new Calculator(num1, num2);
                res = objCalc->Operate(operation);
                char buffer[20];
                snprintf(buffer, sizeof(buffer), "%f", res);

                SetWindowTextA(hwndLabel, buffer);
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
        }

        return 0;
    }

    int GetSelectedRadioButton(HWND hDlg, int numberRadioButtons, int radioButtonGroupID)
    {
        for (int id = radioButtonGroupID; id < radioButtonGroupID + numberRadioButtons; ++id)
        {
            if (IsDlgButtonChecked(hDlg, id) == BST_CHECKED)
                return id; // Return the ID of the checked RadioButton
        }
        return 0; // No RadioButton checked
    }
};
#endif // Form_CPP
