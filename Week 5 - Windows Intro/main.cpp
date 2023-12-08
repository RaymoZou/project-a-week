#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wparam, lparam);
            break;
    };
    return 0;
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PWSTR pCmdLine,
                    int nCmdShow) {
    WNDCLASSW wc = {};
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Testing";

    // RegisterClassW(&wc);
    if (!RegisterClassW(&wc)) {
        MessageBoxW(NULL, L"Window Registration Failed!", L"ERROR",
                    MB_ICONEXCLAMATION | MB_OK);
        return 0;
    };

    // Create Window (CreateWindowW)
    HWND hwnd = CreateWindowW(wc.lpszClassName, L"Testing",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 800,
                              0, 0, hInstance, 0);

    // if (hwnd == NULL) {
    //     MessageBoxW(NULL, L"Window Creation Failed", L"ERROR",
    //                 MB_ICONEXCLAMATION | MB_OK);
    //     return -1;
    // };

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessageW(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };

    return 0;
};
