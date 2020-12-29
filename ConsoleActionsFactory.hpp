//
// Created by letih on 12/29/2020.
//

#pragma once
#ifndef OOP_LAB4__CONSOLEACTIONSFACTORY_HPP_
#define OOP_LAB4__CONSOLEACTIONSFACTORY_HPP_

#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS_SUPPORT
#elif defined(linux) || defined(__linux) || defined(__linux__)
#define LINUX_SUPPORT
#endif

#if defined(WINDOWS_SUPPORT)

#include <Windows.h>

#elif defined(LINUX_SUPPORT)

#include <iostream>
#include <string>
#include <term.h>
#include <termios.h>
#include <unistd.h>

#endif //WINDOWS_SUPPORT || LINUX_SUPPORT

class ConsoleActionsFactory {
  public:
    static auto GetClearConsole() -> void (*)();

    static auto GetWaitForAnyKey() -> void (*)();
};

#endif //OOP_LAB4__CONSOLEACTIONSFACTORY_HPP_
