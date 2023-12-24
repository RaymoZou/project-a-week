#include <windows.h>

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);

// game properties
float velocity = 2.5;      // player fall speed
float gravity_scale = 0.5; // player gravity scale
int update_time = 10;    // how often the game state updates in milliseconds

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
   private:
    static const int WINDOW_LENGTH = 200;
    static const int WINDOW_HEIGHT = 200;

   public:
    HWND hwnd;

    // int MovePlayer() {
    //     // get current window position
    //     RECT playerPos;
    //     if (GetWindowRect(hwnd, &playerPos) == 0) {
    //         return -1;
    //         // TODO: handle error
    //     };

    //     velocity = velocity + gravity_scale;
    //     if (MoveWindow(hwnd, playerPos.left, playerPos.top + velocity,
    //                    WINDOW_LENGTH, WINDOW_HEIGHT, FALSE) == 0)
    //         // TODO: handle error
    //         return -1;

    //     return 0;
    // };

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam,
                                       LPARAM lparam) {
        switch (msg) {
            case WM_CLOSE:
                DestroyWindow(hwnd);
                break;
            case WM_TIMER:
                // TODO: Refactor into a MovePlayer function
                // get current window position
                RECT playerPos;
                if (GetWindowRect(hwnd, &playerPos) == 0) {
                    return -1;
                    // TODO: handle error
                };

                velocity = velocity + gravity_scale;
                if (MoveWindow(hwnd, playerPos.left, playerPos.top + velocity,
                               WINDOW_LENGTH, WINDOW_HEIGHT, FALSE) == 0)
                    // TODO: handle error
                    return -1;

                return 0;
                break;
            case WM_DESTROY:
                // Do nothing - quit message only sent from Main Window
            default:
                return DefWindowProcW(hwnd, msg, wparam, lparam);
        };
        return 0;
    };

    PlayerWindow() {
        WNDCLASSW wc = {0};
        wc.lpfnWndProc = &WindowProc;
        wc.lpszClassName = L"Player Window";
        wc.hInstance = GetModuleHandle(NULL);

        RegisterClassW(&wc);
        hwnd = CreateWindowW(
            wc.lpszClassName, L"Player", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0,
            WINDOW_LENGTH, WINDOW_HEIGHT, 0, 0, GetModuleHandle(NULL), 0);
    };
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
    MainWindow mainWindow = MainWindow(hInstance);
    PlayerWindow playerWindow = PlayerWindow();

    // SetTimer(mainWindow.hwnd, 0, update_time, 0);
    SetTimer(playerWindow.hwnd, 0, update_time, 0);

    // Run message loop
    MSG msg = {};
    while (GetMessageW(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };
    return 0;
};