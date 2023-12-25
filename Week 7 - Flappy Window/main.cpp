#include <windows.h>

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);

// game properties
float velocity = 2.5;       // player fall speed
float gravity_scale = 0.5;  // player gravity scale
float jumpForce = -12;      // how high the player jumps when space is pressed
int update_time = 10;       // how often the game state updates in milliseconds
float pipe_velocity = -5;   // how fast the pipe is moving towards the player
float pipe_spawn_rate = 2000;  // spawn rate of the pipes

class PipeWindow {
   private:
    static const int WINDOW_LENGTH = 200;
    static const int WINDOW_HEIGHT = 800;

   public:
    HWND hwnd;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam,
                                       LPARAM lparam) {
        switch (msg) {
            case WM_CLOSE:
                DestroyWindow(hwnd);
                break;
            case WM_TIMER:
                // TODO: Refactor into a MovePipe function
                RECT pipePos;
                if (GetWindowRect(hwnd, &pipePos) == 0) {
                    return -1;
                    // TODO: handle error
                };

                if (pipePos.left + pipe_velocity < 0) DestroyWindow(hwnd);

                if (MoveWindow(hwnd, pipePos.left + pipe_velocity, pipePos.top,
                               WINDOW_LENGTH, WINDOW_HEIGHT, FALSE) == 0)
                    // TODO: handle error
                    return -1;

                break;
            default:
                return DefWindowProcW(hwnd, msg, wparam, lparam);
        };
        return 0;
    };

    PipeWindow() {
        WNDCLASSEXW wc = {0};
        wc.cbSize = sizeof(WNDCLASSEXW);
        // wc.cbWndExtra = DLGWINDOWEXTRA;
        wc.lpfnWndProc = &WindowProc;
        wc.lpszClassName = L"Pipe Window";
        wc.hInstance = GetModuleHandle(NULL);

        RegisterClassExW(&wc);
        hwnd = CreateWindowExW(WS_EX_NOACTIVATE, wc.lpszClassName, L"Pipe",
                               WS_VISIBLE | WS_DISABLED,
                               screenWidth - WINDOW_LENGTH, 0, WINDOW_LENGTH,
                               WINDOW_HEIGHT, 0, 0, GetModuleHandle(NULL), 0);

        // Set pipe velocity
        SetTimer(hwnd, 0, update_time, 0);
    };
};
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
                break;
            default:
                return DefWindowProcW(hwnd, msg, wparam, lparam);
        };
        return 0;
    };

    MainWindow(HINSTANCE hInstance) {
        WNDCLASSEXW wc = {0};
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.lpfnWndProc = &WindowProc;
        wc.lpszClassName = L"Main Window";

        RegisterClassExW(&wc);
        hwnd = CreateWindowExW(0, wc.lpszClassName, L"Main",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 800,
                               0, 0, hInstance, 0);
        // Set pipe spawn rate
        SetTimer(hwnd, 0, pipe_spawn_rate, 0);
    };
};

class PlayerWindow {
   private:
    static const int WINDOW_LENGTH = 200;
    static const int WINDOW_HEIGHT = 200;

   public:
    HWND hwnd;

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

                break;
            case WM_DESTROY:
                // Do nothing - quit message only sent from Main Window
            case WM_KEYDOWN:
                if (wparam == VK_SPACE) {
                    OutputDebugStringW(L"Space was pressed.\n");
                    velocity = jumpForce;
                };
                break;
            default:
                return DefWindowProcW(hwnd, msg, wparam, lparam);
        };
        return 0;
    };

    PlayerWindow() {
        WNDCLASSEXW wc = {0};
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.lpfnWndProc = &WindowProc;
        wc.lpszClassName = L"Player Window";
        wc.hInstance = GetModuleHandle(NULL);

        RegisterClassExW(&wc);
        hwnd = CreateWindowExW(
            0, wc.lpszClassName, L"Player", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0,
            0, WINDOW_LENGTH, WINDOW_HEIGHT, 0, 0, GetModuleHandle(NULL), 0);
    };
};

VOID CALLBACK PipeTimerProc(HWND hwnd, UINT msg, UINT_PTR idEvent,
                            DWORD dwTime) {
    HWND playerHWND = GetActiveWindow();
    PipeWindow pipeWindow = PipeWindow();
    SetActiveWindow(playerHWND);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
    MainWindow mainWindow = MainWindow(hInstance);
    // PipeWindow pipeWindow = PipeWindow();
    PlayerWindow playerWindow = PlayerWindow();

    SetTimer(0, 1, pipe_spawn_rate, PipeTimerProc);
    SetTimer(playerWindow.hwnd, 0, update_time, 0);
    // Run message loop
    MSG msg = {};
    while (GetMessageW(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };
    return 0;
};