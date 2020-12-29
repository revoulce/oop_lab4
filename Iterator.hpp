//
// Created by letih on 12/29/2020.
//

#pragma once
#ifndef OOP_LAB4__ITERATOR_HPP_
#define OOP_LAB4__ITERATOR_HPP_

#include <memory>
#include <unordered_set>
#include <utility>

#include "Employee.hpp"

class Iterator {
  public:
    explicit Iterator(std::unordered_set<const Employee*> employees_to_iterate);

    const Employee* GetData();

    const Employee* StepForward();

  private:
    std::unordered_set<const Employee*> employees_to_iterate_;
    std::unordered_set<const Employee*>::iterator iterator_;
};

#endif //OOP_LAB4__ITERATOR_HPP_
