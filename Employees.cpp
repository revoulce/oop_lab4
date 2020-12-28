//
// Created by revoulce on 12/28/20.
//

#include "Employees.hpp"

void Employees::AddEmployee(Employee* new_employee) {
    int32_t new_employee_id = employees_id_.cend()->first;

    employees_id_.emplace_hint(employees_id_.cend(), new_employee_id, new_employee);

}

EmployeesIterator* Employees::GetEmployees() {
    if (employees_id_.empty()) {
        return nullptr;
    }

    return new EmployeesIterator(employees_id_.begin());
}

EmployeesIterator* Employees::GetEmployeeById(int32_t id) {
    auto this_iterator = employees_id_.find(id);

    if (this_iterator == employees_id_.end()) {
        return nullptr;
    }

    return new EmployeesIterator(this_iterator);
}
