//
// Created by revoulce on 12/24/20.
//

#pragma once
#ifndef OOP_LAB4__EMPLOYEE_HPP_
#define OOP_LAB4__EMPLOYEE_HPP_

#include <stdexcept>
#include <string>
#include <utility>

class Employee {
  public:
    Employee(const std::string& name,
             const std::string& occupation,
             const std::string& gender,
             int32_t year_of_employment,
             int32_t year_of_birth);

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] const std::string& GetOccupation() const;

    [[nodiscard]] const std::string& GetGender() const;

    [[nodiscard]] int32_t GetYearOfEmployment() const;

    [[nodiscard]] int32_t GetYearOfBirth() const;

  private:
    std::string name_;
    std::string occupation_;
    std::string gender_;
    int32_t year_of_employment_;
    int32_t year_of_birth_;
};

#endif //OOP_LAB4__EMPLOYEE_HPP_
