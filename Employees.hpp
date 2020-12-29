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
#include "Iterator.hpp"

class Employees {
  public:
    Employees();

    void AddEmployee(std::unique_ptr<Employee> new_employee);

    [[nodiscard]] std::unique_ptr<Iterator> GetEmployees() const;

    [[nodiscard]] const Employee* GetEmployeeById(int32_t id) const;

    [[nodiscard]] std::unique_ptr<Iterator> GetEmployeesByName(const std::string& name) const;

    [[nodiscard]] std::unique_ptr<Iterator> GetEmployeesByOccupation(const std::string& occupation) const;

    [[nodiscard]] std::unique_ptr<Iterator> GetEmployeesByGender(const std::string& gender) const;

    [[nodiscard]] std::unique_ptr<Iterator> GetEmployeesByYearOfEmployment(int32_t year_of_employment) const;

    [[nodiscard]] std::unique_ptr<Iterator> GetEmployeesByYearOfBirth(int32_t year_of_birth) const;

    void DeleteEmployee(int32_t id);

    [[nodiscard]] std::unique_ptr<Iterator> GetRetirees(int32_t retirement_year) const;

  private:
    int32_t current_id_;
    int32_t males_count_;
    int32_t females_count_;
    const int32_t retirement_year_for_men_ = 65;
    const int32_t retirement_year_for_women_ = 60;

    std::unordered_map<int32_t, std::unique_ptr<Employee>> employees_by_id_;
    std::unordered_map<std::string, std::unordered_set<int32_t>> employees_by_name_;
    std::unordered_map<std::string, std::unordered_set<int32_t>> employees_by_occupation_;
    std::unordered_map<std::string, std::unordered_set<int32_t>> employees_by_gender_;
    std::unordered_map<int32_t, std::unordered_set<int32_t>> employees_by_year_of_employment_;
    std::unordered_map<int32_t, std::unordered_set<int32_t>> employees_by_year_of_birth_;
    std::unordered_map<std::string, std::unordered_set<int32_t>> employees_by_gender_and_year_of_birth_;

    [[nodiscard]] std::unordered_set<const Employee*> MakeFilteredSet(const std::unordered_set<int32_t>&& filtered_employee_ids) const;
};

#endif //OOP_LAB4__EMPLOYEES_HPP_
