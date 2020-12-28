//
// Created by revoulce on 12/28/20.
//

#include "EmployeesIterator.hpp"

EmployeesIterator::EmployeesIterator(std::unordered_map<int, Employee*>::iterator iterator) : iterator_(iterator) {}

Employee* EmployeesIterator::GetData() {
    return iterator_->second;
}

Employee* EmployeesIterator::StepForward() {
    iterator_ = std::next(iterator_);
    return iterator_->second;
}

Employee* EmployeesIterator::StepBack() {
    iterator_ = std::prev(iterator_);
    return iterator_->second;
}
