//
// Created by revoulce on 12/28/20.
//

#include "Employees.hpp"

Employees::Employees() : current_id_(0), males_count_(0), females_count_(0) {}

void Employees::AddEmployee(std::unique_ptr<Employee> new_employee) {
    employees_by_id_[current_id_] = std::move(new_employee);
    const auto current_employee = employees_by_id_.at(current_id_).get();

    employees_by_name_[current_employee->GetName()].insert(current_id_);
    employees_by_occupation_[current_employee->GetOccupation()].insert(current_id_);
    employees_by_gender_[current_employee->GetGender()].insert(current_id_);
    employees_by_year_of_employment_[current_employee->GetYearOfEmployment()].insert(current_id_);
    employees_by_year_of_birth_[current_employee->GetYearOfBirth()].insert(current_id_);
    employees_by_gender_and_year_of_birth_[current_employee->GetGender()].insert(current_employee->GetYearOfBirth());

    ++current_id_;

    if (current_employee->GetGender() == "Male") {
        ++males_count_;
    } else if (current_employee->GetGender() == "Female") {
        ++females_count_;
    }
}

std::unique_ptr<Iterator> Employees::GetEmployees() const {
    if (employees_by_id_.empty()) {
        return nullptr;
    }

    std::unordered_set<const Employee*> employees_ptr;

    for (const auto& employee : employees_by_id_) {
        employees_ptr.insert(employee.second.get());
    }

    return std::make_unique<Iterator>(std::move(employees_ptr));
}

const Employee* Employees::GetEmployeeById(int32_t id) const {
    if (!employees_by_id_.contains(id)) {
        return nullptr;
    }

    return employees_by_id_.at(id).get();
}

std::unique_ptr<Iterator> Employees::GetEmployeesByName(const std::string& name) const {
    if (!employees_by_name_.contains(name)) {
        return nullptr;
    }

    return std::make_unique<Iterator>(std::move(MakeFilteredSet(employees_by_name_.at(name))));
}

std::unique_ptr<Iterator> Employees::GetEmployeesByOccupation(const std::string& occupation) const {
    if (!employees_by_occupation_.contains(occupation)) {
        return nullptr;
    }

    return std::make_unique<Iterator>(std::move(MakeFilteredSet(employees_by_occupation_.at(occupation))));
}

std::unique_ptr<Iterator> Employees::GetEmployeesByGender(const std::string& gender) const {
    if (!employees_by_gender_.contains(gender)) {
        return nullptr;
    }

    return std::make_unique<Iterator>(std::move(MakeFilteredSet(employees_by_gender_.at(gender))));
}

std::unique_ptr<Iterator> Employees::GetEmployeesByYearOfEmployment(const int32_t year_of_employment) const {
    if (!employees_by_year_of_employment_.contains(year_of_employment)) {
        return nullptr;
    }

    return std::make_unique<Iterator>(std::move(MakeFilteredSet(employees_by_year_of_employment_.at(year_of_employment))));
}

std::unique_ptr<Iterator> Employees::GetEmployeesByYearOfBirth(const int32_t year_of_birth) const {
    if (!employees_by_year_of_birth_.contains(year_of_birth)) {
        return nullptr;
    }

    return std::make_unique<Iterator>(std::move(MakeFilteredSet(employees_by_year_of_birth_.at(year_of_birth))));
}

void Employees::DeleteEmployee(int32_t id) {
    if (!employees_by_id_.contains(id)) {
        return;
    }

    auto employee_to_delete = std::move(employees_by_id_.at(id));
    const auto name_to_delete = employee_to_delete->GetName();
    const auto occupation_to_delete = employee_to_delete->GetOccupation();
    const auto gender_to_delete = employee_to_delete->GetGender();
    const auto year_of_employment_to_delete = employee_to_delete->GetYearOfEmployment();
    const auto year_of_birth_to_delete = employee_to_delete->GetYearOfBirth();

    if (gender_to_delete == "Male") {
        --males_count_;
    } else {
        --females_count_;
    }

    const auto iterator_at_employee_to_delete = employees_by_id_.find(id);
    employees_by_id_.erase(iterator_at_employee_to_delete);

    employees_by_name_.at(name_to_delete).erase(id);
    employees_by_occupation_.at(occupation_to_delete).erase(id);
    employees_by_gender_.at(gender_to_delete).erase(id);
    employees_by_year_of_employment_.at(year_of_employment_to_delete).erase(id);
    employees_by_year_of_birth_.at(year_of_birth_to_delete).erase(id);

    if (gender_to_delete == "Male" && males_count_ == 0) {
        employees_by_gender_and_year_of_birth_.erase(gender_to_delete);
    }

    if (gender_to_delete == "Female" && females_count_ == 0) {
        employees_by_gender_and_year_of_birth_.erase(gender_to_delete);
    }

    if (employees_by_name_.at(name_to_delete).empty()) {
        employees_by_name_.erase(name_to_delete);
    }

    if (employees_by_occupation_.at(occupation_to_delete).empty()) {
        employees_by_occupation_.erase(occupation_to_delete);
    }

    if (employees_by_gender_.at(gender_to_delete).empty()) {
        employees_by_gender_.erase(gender_to_delete);
    }

    if (employees_by_year_of_employment_.at(year_of_employment_to_delete).empty()) {
        employees_by_year_of_employment_.erase(year_of_employment_to_delete);
    }

    if (employees_by_year_of_birth_.at(year_of_birth_to_delete).empty()) {
        employees_by_year_of_birth_.erase(year_of_birth_to_delete);
    }

    if (employees_by_gender_and_year_of_birth_.contains(gender_to_delete)) {
        if (employees_by_gender_and_year_of_birth_.at(gender_to_delete).empty()) {
            employees_by_gender_and_year_of_birth_.erase(gender_to_delete);
        }
    }
}

std::unique_ptr<Iterator> Employees::GetRetirees(const int32_t retirement_year) const {
    std::unordered_set<int32_t> retirees_by_id;
    int32_t current_birth_year = retirement_year - retirement_year_for_men_;

    if (employees_by_gender_and_year_of_birth_.at("Male").contains(current_birth_year)) {
        for (const auto id : employees_by_year_of_birth_.at(current_birth_year)) {
            if (employees_by_id_.at(id)->GetGender() == "Male") {
                retirees_by_id.insert(id);
            }
        }
    }

    current_birth_year = retirement_year - retirement_year_for_women_;

    if (employees_by_gender_and_year_of_birth_.at("Female").contains(current_birth_year)) {
        for (const auto id : employees_by_year_of_birth_.at(current_birth_year)) {
            if (employees_by_id_.at(id)->GetGender() == "Female") {
                retirees_by_id.insert(id);
            }
        }
    }

    return std::make_unique<Iterator>(MakeFilteredSet(retirees_by_id));
}

std::unordered_set<const Employee*> Employees::MakeFilteredSet(const std::unordered_set<int32_t>& filtered_employee_id) const {
    std::unordered_set<const Employee*> employees_ptr;

    for (const auto& employee_id : filtered_employee_id) {
        employees_ptr.insert(employees_by_id_.at(employee_id).get());
    }

    return employees_ptr;
}
