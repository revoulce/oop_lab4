//
// Created by revoulce on 12/24/20.
//

#include "Employee.hpp"

Employee::Employee(const std::string& name,
                   const std::string& occupation,
                   const std::string& gender,
                   int32_t year_of_employment,
                   int32_t year_of_birth)
    : name_(name),
      occupation_(occupation),
      gender_(gender),
      year_of_employment_(year_of_employment),
      year_of_birth_(year_of_birth) {
    if (gender != "Male" && gender != "Female") {
        throw std::invalid_argument("Wrong gender.");
    }
}

const std::string& Employee::GetName() const {
    return name_;
}

const std::string& Employee::GetOccupation() const {
    return occupation_;
}

const std::string& Employee::GetGender() const {
    return gender_;
}

int32_t Employee::GetYearOfEmployment() const {
    return year_of_employment_;
}

int32_t Employee::GetYearOfBirth() const {
    return year_of_birth_;
}
