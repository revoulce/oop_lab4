//
// Created by revoulce on 12/28/20.
//

#pragma once
#ifndef OOP_LAB4__EMPLOYEESITERATOR_HPP_
#define OOP_LAB4__EMPLOYEESITERATOR_HPP_

#include <algorithm>

#include "Employees.hpp"

class EmployeesIterator {
  public:
    explicit EmployeesIterator(std::unordered_map<int, Employee*>::iterator iterator);

    Employee* GetData();

    Employee* StepForward();

    Employee* StepBack();

  private:
    std::unordered_map<int, Employee*>::iterator iterator_;
};

#endif //OOP_LAB4__EMPLOYEESITERATOR_HPP_
