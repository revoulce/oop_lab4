//
// Created by revoulce on 12/28/20.
//

#pragma once
#ifndef OOP_LAB4__EMPLOYEES_HPP_
#define OOP_LAB4__EMPLOYEES_HPP_

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Employee.hpp"
#include "EmployeesIterator.hpp"

class Employees {
  public:
    void AddEmployee(Employee* new_employee);

    EmployeesIterator* GetEmployees();

    EmployeesIterator* GetEmployeeById(int32_t id);

  private:
    int32_t retirement_year_for_men_ = 65;
    int32_t retirement_year_for_women = 60;

    std::unordered_map<int, Employee*> employees_id_;
    std::unordered_map<int, std::unordered_set<int>> employees_year_of_birth_;
    std::unordered_map<int, std::unordered_set<int>> employees_year_of_employment_;
    std::unordered_map<std::string, std::unordered_set<int>> employees_name_;
    std::unordered_map<std::string, std::unordered_set<int>> employees_job_title_;
};

#endif //OOP_LAB4__EMPLOYEES_HPP_
