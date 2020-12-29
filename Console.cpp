//
// Created by letih on 12/28/2020.
//

#include "Console.hpp"

void Console::Run() {
    int32_t user_answer;

    ClearConsole = ConsoleActionsFactory::GetClearConsole();
    WaitForAnyKey = ConsoleActionsFactory::GetWaitForAnyKey();

    ReadFile();

    while (true) {
        ClearConsole();
        ShowMainMenu();

        user_answer = GetNumber("Please enter your choice: ");

        switch (user_answer) {
            case 0:
                return;
            case 1:
                PrintEmployees(std::move(employees_.GetEmployees()));
                WaitForAnyKey();
                break;
            case 2:
                DeleteEmployee();
                break;
            case 3:
                PrintRetirees();
                WaitForAnyKey();
                break;
            case 4:
                PrintEmployeesByAttributes();
                break;
            default:
                std::cerr << "Wrong choice." << std::endl;
                WaitForAnyKey();
        }
    }
}

void Console::ReadFile() {
    try {
        std::string employees_filename("employees.txt");

        std::ifstream employees_file(employees_filename);
        employees_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        std::string line, token;
        std::string parameters[5];
        char delimiter = ',';

        std::getline(employees_file, line);
        int employees_count = std::stoi(Trim(line));

        for (int32_t i = 0; i < employees_count; ++i) {
            std::getline(employees_file, line);
            std::stringstream ss(line);

            for (auto& parameter : parameters) {
                std::getline(ss, token, delimiter);
                parameter = Trim(token);
            }

            employees_.AddEmployee(std::make_unique<Employee>(parameters[0],
                                                              parameters[1],
                                                              parameters[2],
                                                              std::stoi(parameters[3]),
                                                              std::stoi(parameters[4])));
        }

        employees_file.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Exception opening/reading/closing file" << std::endl;
        std::cerr << "Error message: " << e.what() << std::endl;
        WaitForAnyKey();
    } catch (std::invalid_argument& e) {
        std::cerr << "No number of employees at the beginning of the file." << std::endl;
        std::cerr << "Error message: " << e.what() << std::endl;
        WaitForAnyKey();
    }
}

void Console::ShowMainMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "0. Exit." << std::endl;
    std::cout << "1. Print all employees." << std::endl;
    std::cout << "2. Delete employee." << std::endl;
    std::cout << "3. Show retirees by year of retirement." << std::endl;
    std::cout << "4. Print employees by attribute." << std::endl;
}

void Console::ShowAttributesMenu() {
    std::cout << "What do you want to enter?" << std::endl;
    std::cout << "0. Exit to main menu." << std::endl;
    std::cout << "1. ID." << std::endl;
    std::cout << "2. Full name." << std::endl;
    std::cout << "3. Occupation." << std::endl;
    std::cout << "4. Gender." << std::endl;
    std::cout << "5. Year of employment." << std::endl;
    std::cout << "6. Year of birth." << std::endl;
}

void Console::PrintEmployees(std::unique_ptr<Iterator> iterator) {
    if (iterator == nullptr) {
        std::cout << "No matching employees." << std::endl;
        return;
    }
    auto employee = iterator->StepForward();

    while (employee != nullptr) {
        PrintEmployee(employee);

        employee = iterator->StepForward();
    }
}

void Console::PrintEmployee(const Employee* employee) {
    if (employee == nullptr) {
        std::cout << "Such employee doesn't exist." << std::endl;
        return;
    }

    std::cout << "Full name: " << employee->GetName() << std::endl;
    std::cout << "Occupation: " << employee->GetOccupation() << std::endl;
    std::cout << "Gender: " << employee->GetGender() << std::endl;
    std::cout << "Year of employment: " << employee->GetYearOfEmployment() << std::endl;
    std::cout << "Year of birth: " << employee->GetYearOfBirth() << std::endl << std::endl;
}

void Console::DeleteEmployee() {
    int32_t id = GetNumber("Enter id to delete: ");

    employees_.DeleteEmployee(id);
}

void Console::PrintRetirees() {
    int32_t retirement_year;

    retirement_year = GetNumber("Enter retirement year: ");

    PrintEmployees(std::move(employees_.GetRetirees(retirement_year)));
}

void Console::PrintEmployeesByAttributes() {
    int32_t user_answer;

    while (true) {
        ClearConsole();
        ShowAttributesMenu();

        user_answer = GetNumber("Please enter your choice: ");

        switch (user_answer) {
            case 0:
                return;
            case 1:
                PrintEmployee(employees_.GetEmployeeById(GetNumber("Enter id to find: ")));
                WaitForAnyKey();
                break;
            case 2:
                PrintEmployees(std::move(employees_.GetEmployeesByName(Trim(GetString("Enter full name: ")))));
                WaitForAnyKey();
                break;
            case 3:
                PrintEmployees(std::move(employees_.GetEmployeesByOccupation(Trim(GetString("Enter occupation: ")))));
                WaitForAnyKey();
                break;
            case 4:
                PrintEmployees(std::move(employees_.GetEmployeesByGender(Trim(GetString("Enter gender: ")))));
                WaitForAnyKey();
                break;
            case 5:
                PrintEmployees(std::move(employees_.GetEmployeesByYearOfEmployment(GetNumber(
                    "Enter year of employment: "))));
                WaitForAnyKey();
                break;
            case 6:
                PrintEmployees(std::move(employees_.GetEmployeesByYearOfBirth(GetNumber("Enter year of birth: "))));
                WaitForAnyKey();
                break;
            default:
                std::cerr << "Wrong choice." << std::endl;
                WaitForAnyKey();
        }
    }
}

int32_t Console::GetNumber(const std::string& message) {
    int32_t number;
    std::string str_number;

    std::cout << message;
    std::getline(std::cin, str_number);

    try {
        if (!str_number.empty() && CheckIsNumeric(str_number)) {
            number = std::stoi(str_number);
        } else {
            std::cerr << "The value entered is empty or does not contain only digits." << std::endl;
            WaitForAnyKey();
            return -1;
        }
    } catch (std::out_of_range& e) {
        std::cerr << "Value entered too high." << std::endl;
        std::cerr << "Error message: " << e.what() << std::endl;
        WaitForAnyKey();
        return -1;
    }

    return number;
}

std::string Console::GetString(const std::string& message) {
    std::string user_input;

    std::cout << message;
    std::getline(std::cin, user_input);

    return user_input;
}

std::string Console::Trim(const std::string& string, const std::string& whitespace) {
    const auto string_begin = string.find_first_not_of(whitespace);

    if (string_begin == std::string::npos) {
        return std::string();
    }

    const auto string_end = string.find_last_not_of(whitespace);

    const auto string_range = string_end - string_begin + 1;

    return string.substr(string_begin, string_range);
}

bool Console::CheckIsNumeric(const std::string& string_to_check) {
    return std::ranges::all_of(string_to_check, [](char ch) { return std::isdigit(ch) != 0; });
}
