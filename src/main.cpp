#include <windows.h>
#include <iostream>
#include <string>

// Function prototypes
LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::wstring get_last_error_message_as_string();

// WinMain is the user-provided entry point for a graphical Windows-based application
// The return value is NOT used by the operating system. You can use it to convey a status code for the application
// You're writing.
int CALLBACK WinMain(
    HINSTANCE hInstance, // Handle to the current instance of the application
    HINSTANCE hPrevInstance, // Deprecated. Always NULL.
    LPSTR lpCmdLine, // The command line for the application
    int nShowCmd // Flag stating if the main application window will be minimized, maximized, or shown normally.
)
{
    std::cout << "Hello from WinMain!" << std::endl;

    // In order to create a window we need to fill out the WNDCLASSEX structure.
    // This structure contains information that defines the behaviour visual look of any window using this class.
    // https://docs.microsoft.com/en-us/windows/win32/winmsg/about-window-classes
    wchar_t window_class_name[] = L"applicationwindow";

    // I use uniform initialization ( {} ) on this struct to set all members to zero and null per default.
    // This is so I don't manually have to set members of type pointer to NULL manually (as that is otherwise not done automatically).
    // Having non-null pointers initialized with incorrect values will make the "RegisterClassExW" function call fail.
    WNDCLASSEXW wcex {};
    wcex.cbSize = sizeof(WNDCLASSEXW); // Required to be set to "sizeof(WNDCLASSEX)"
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = window_proc; // The window procedure associated with this window class.
    wcex.hInstance = hInstance;
    wcex.lpszClassName = window_class_name;

    // After defining a windows class, we have to register it with Windows so that we can create windows based on it.
    if (!RegisterClassExW(&wcex))
    {
        auto errorMessage = get_last_error_message_as_string();
        std::cout << "Failed to register window class." << std::endl;
        return -1;
    }

    return 0;
}

// https://docs.microsoft.com/en-us/windows/win32/winmsg/window-procedures
// Every window has an associated window procedure.
// This is a function that processes messages sent or posted to all windows of a class.
LRESULT CALLBACK window_proc(
    HWND hwnd, // A handle to the window
    UINT uMsg, // The message being processed
    WPARAM wParam, // Additional message information. This depends on the type of message being processed.
    LPARAM lParam) { // Additional message information. This depends on the type of message being processed.
    // For any messages we do not handle, we can pass it on to the predefined "DefWindowProc", which is a 
    // Default window procedure function that contains fundamental behaviour shared by all windows.
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

std::wstring get_last_error_message_as_string()
{
    // Get the error message, if any
    DWORD errorMessageId = ::GetLastError();
    if (errorMessageId == 0)
        return std::wstring(); // No error message recorded

    LPWSTR messageBuffer = nullptr;
    size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                nullptr, errorMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, nullptr);

    std::wstring message(messageBuffer, size);

    // Free the buffer
    LocalFree(messageBuffer);

    return message;
}