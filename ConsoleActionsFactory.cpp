//
// Created by letih on 12/29/2020.
//

#include "ConsoleActionsFactory.hpp"

#if defined(WINDOWS_SUPPORT)

void ClearConsole();

void WaitForAnyKey();

#elif defined(LINUX_SUPPORT)

void ClearConsole();

void Raw(bool b);

void WaitForAnyKey();

#endif //WINDOWS_SUPPORT || LINUX_SUPPORT

auto ConsoleActionsFactory::GetClearConsole() -> void (*)() {
#if defined(WINDOWS_SUPPORT) || defined(LINUX_SUPPORT)
    return &ClearConsole;
#endif
    return nullptr;
}

auto ConsoleActionsFactory::GetWaitForAnyKey() -> void (*)() {
#if defined(WINDOWS_SUPPORT) || defined(LINUX_SUPPORT)
    return &WaitForAnyKey;
#endif
    return nullptr;
}

#if defined(WINDOWS_SUPPORT)

void ClearConsole() {
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
    DWORD count;
    COORD home_coords = {0, 0};
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (handle == INVALID_HANDLE_VALUE) {
        return;
    }

    if (GetConsoleScreenBufferInfo(handle, &console_screen_buffer_info) == 0) {
        return;
    }

    DWORD cell_count = console_screen_buffer_info.dwSize.X * console_screen_buffer_info.dwSize.Y;

    if (FillConsoleOutputCharacter(handle, static_cast<TCHAR>(' '), cell_count, home_coords, &count) == 0) {
        return;
    }

    if (FillConsoleOutputAttribute(handle, console_screen_buffer_info.wAttributes, cell_count, home_coords, &count)
        == 0) {
        return;
    }

    SetConsoleCursorPosition(handle, home_coords);
}

void WaitForAnyKey() {
    TCHAR tchar;
    DWORD mode;
    DWORD count;
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    const TCHAR* prompt = TEXT("Press any key to continue...\n");

    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), prompt, lstrlen(prompt), &count, nullptr);

    GetConsoleMode(handle, &mode);
    SetConsoleMode(handle, 0);

    WaitForSingleObject(handle, INFINITE);

    ReadConsole(handle, &tchar, 1, &count, nullptr);

    SetConsoleMode(handle, mode);
}

#elif defined(LINUX_SUPPORT)

void ClearConsole() {
    if (!cur_term) {
        int success;

        setupterm(nullptr, STDOUT_FILENO, &success);

        if (success <= 0) {
            return;
        }
    }

    putp(tigetstr("clear"));
}

void Raw(bool b) {
    struct termios settings;
    static struct termios initial_settings;
    static bool is_unitialized = false;

    if (!is_unitialized) {
        is_unitialized = tcgetattr(STDIN_FILENO, &initial_settings) == 0;

        if (!is_unitialized) {
            return;
        }
    }

    if (b) {
        tcgetattr(STDIN_FILENO, &settings);

        settings.c_cc[VTIME] = 0;
        settings.c_cc[VMIN] = 1;
        settings.c_iflag &= ~(BRKINT | ICRNL | INLCR | ISTRIP | IXOFF);
        settings.c_iflag |= IGNBRK;
        settings.c_oflag &= ~(OPOST);
        settings.c_cflag &= ~(CSIZE | PARENB);
        settings.c_cflag |= CS8;
        settings.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    } else {
        settings = initial_settings;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void WaitForAnyKey() {
    const std::string prompt = std::string("Press any key to continue...");
    struct termios settings;

    tcgetattr(STDIN_FILENO, &settings);

    Raw(true);

    std::cout << prompt << std::endl;
    getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

#endif //WINDOWS_SUPPORT || LINUX_SUPPORT
