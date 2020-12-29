//
// Created by letih on 12/28/2020.
//

#pragma once
#ifndef OOP_LAB4__CONSOLE_HPP_
#define OOP_LAB4__CONSOLE_HPP_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "ConsoleActionsFactory.hpp"
#include "Employee.hpp"
#include "Employees.hpp"

class Console {
  public:
    void Run();

  private:
    Employees employees_;

    void (* ClearConsole)();

    void (* WaitForAnyKey)();

    void ReadFile();

    void ShowMainMenu();

    void ShowAttributesMenu();

    void PrintEmployees(std::unique_ptr<Iterator> iterator);

    void PrintEmployee(const Employee* employee);

    void DeleteEmployee();

    void PrintRetirees();

    void PrintEmployeesByAttributes();

    int32_t GetNumber(const std::string& message);

    std::string GetString(const std::string& message);

    std::string Trim(const std::string& string, const std::string& whitespace = " /t");

    bool CheckIsNumeric(const std::string& string_to_check);

};

#endif //OOP_LAB4__CONSOLE_HPP_
