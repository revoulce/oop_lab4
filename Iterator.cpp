//
// Created by letih on 12/29/2020.
//

#include "Iterator.hpp"

Iterator::Iterator(std::unordered_set<const Employee*> employees_to_iterate) : employees_to_iterate_(std::move(
    employees_to_iterate)) {
    iterator_ = employees_to_iterate_.begin();
}

const Employee* Iterator::GetData() {
    if (employees_to_iterate_.empty() || (iterator_ == employees_to_iterate_.end())) {
        return nullptr;
    }

    return *iterator_;
}

const Employee* Iterator::StepForward() {
    if (iterator_ == employees_to_iterate_.end()) {
        return nullptr;
    }

    auto* current_employee = *iterator_;

    iterator_ = std::next(iterator_);

    return current_employee;
}
