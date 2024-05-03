#ifndef IWinAPP
#define IWinApp

interface IWindowsApp
{
public:
    void SetClassName(LPCSTR className);
    void SetTitleApp(char *titleApp);
    int Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow);

private:
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
#endif