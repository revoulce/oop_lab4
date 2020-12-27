//
// Created by revoulce on 12/24/20.
//

#pragma once
#ifndef OOP_LAB4__EMPLOYEE_HPP_
#define OOP_LAB4__EMPLOYEE_HPP_

#include <string>

typedef struct EmployeeData {
  std::string name;
  std::string job_title;
  std::string gender;
  int year_of_employment;
  int year_of_birth;
} EmployeeData;

class Employee {
  public:
  private:
    std::string name_;
    std::string job_title_;
    std::string gender_;
    int year_of_employment_;
    int year_of_birth_;
};

#endif //OOP_LAB4__EMPLOYEE_HPP_
