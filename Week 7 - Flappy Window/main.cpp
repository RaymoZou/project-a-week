#include <windows.h>

class MainWindow {
   public:
    HWND hwnd;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam,
                                       LPARAM lparam) {
        switch (msg) {
            case WM_CLOSE:
                DestroyWindow(hwnd);
                break;
            case WM_TIMER:
                OutputDebugStringW(L"WM_TIMER from Main\n");
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
            default:
                return DefWindowProcW(hwnd, msg, wparam, lparam);
        };
        return 0;
    };

    MainWindow(HINSTANCE hInstance) {
        WNDCLASSW wc = {0};
        wc.lpfnWndProc = &WindowProc;
        wc.lpszClassName = L"Main Window";

        RegisterClassW(&wc);
        hwnd = CreateWindowW(wc.lpszClassName, L"Main",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 800,
                             0, 0, hInstance, 0);
    };
};

class PlayerWindow {
   public:
    HWND hwnd;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam,
                                       LPARAM lparam) {
        switch (msg) {
            case WM_CLOSE:
                DestroyWindow(hwnd);
                break;
            case WM_TIMER:
                OutputDebugStringW(L"WM_TIMER from Player\n");
                break;
            case WM_DESTROY:
                // Do nothing - quit message only sent from Main Window
            default:
                return DefWindowProcW(hwnd, msg, wparam, lparam);
        };
        return 0;
    };

    PlayerWindow(HINSTANCE hInstance) {
        WNDCLASSW wc = {0};
        wc.lpfnWndProc = &WindowProc;
        wc.lpszClassName = L"Player Window";

        RegisterClassW(&wc);
        hwnd = CreateWindowW(wc.lpszClassName, L"Player",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 800,
                             0, 0, hInstance, 0);
    };
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
    MainWindow mainWindow = MainWindow(hInstance);
    PlayerWindow playerWindow = PlayerWindow(hInstance);

    SetTimer(mainWindow.hwnd, 0, 1000, 0);
    SetTimer(playerWindow.hwnd, 0, 1000, 0);

    // Run message loop
    MSG msg = {};
    while (GetMessageW(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };
    return 0;
};