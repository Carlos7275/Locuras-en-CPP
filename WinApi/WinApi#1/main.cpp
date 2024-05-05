#include <windows.h>
#include "libs/Form1.cpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    Form *app = new Form();
    LPCSTR className = "SampleWindowClass"; // Define el nombre de la clase de ventana deseado como cadena de caracteres ANSI
    app->SetClassName(className);
    app->SetTitleApp("Calculadora");
    app->SetWindowSize(320, 240);
    app->SetMaximizeStatus(false);
    app->SetResizableStatus(false);

    return app->Show(
        hInstance,
        hPrevInstance,
        pCmdLine,
        nCmdShow);
}