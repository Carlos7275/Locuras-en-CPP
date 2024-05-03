#include <windows.h>
#include <winuser.h>
#include "libs/Form1.cpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    Form app;
    LPCSTR className = "SampleWindowClass"; // Define el nombre de la clase de ventana deseado como cadena de caracteres ANSI   
    app.SetClassName(className);
    app.SetTitleApp("Hola Mundo en Winapi");
    
    return app.Run(
        hInstance,
        hPrevInstance,
        pCmdLine,
        nCmdShow);
}