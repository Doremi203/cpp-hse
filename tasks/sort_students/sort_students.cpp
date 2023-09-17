#include "sort_students.h"

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    switch (sort_kind) {
        case SortKind::Name:
            std::sort(students.begin(), students.end(), [](Student& student_left, Student& student_right) {
                bool is_last_name_equal{student_left.last_name == student_right.last_name};
                bool is_name_equal{student_left.name == student_right.name};
                bool is_year_equal{student_left.birth_date.year == student_right.birth_date.year};
                bool is_month_equal{student_left.birth_date.month == student_right.birth_date.month};
                bool is_day_equal{student_left.birth_date.day == student_right.birth_date.day};
                if (is_last_name_equal) {
                    if (is_name_equal) {
                        if (is_year_equal) {
                            if (is_month_equal) {
                                if (!is_day_equal) {
                                    return student_left.birth_date.day < student_right.birth_date.day;
                                }
                            } else {
                                return student_left.birth_date.month < student_right.birth_date.month;
                            }
                        }
                        return student_left.birth_date.year < student_right.birth_date.year;
                    } else {
                        return student_left.name < student_right.name;
                    }
                } else {
                    return student_left.last_name < student_right.last_name;
                }
            });
            break;
        case SortKind::Date:
            std::sort(students.begin(), students.end(), [](Student& student_left, Student& student_right) {
                bool is_year_equal{student_left.birth_date.year == student_right.birth_date.year};
                bool is_month_equal{student_left.birth_date.month == student_right.birth_date.month};
                bool is_day_equal{student_left.birth_date.day == student_right.birth_date.day};
                if (is_year_equal) {
                    if (is_month_equal) {
                        if (is_day_equal) {
                            bool is_lastname_less{student_left.last_name < student_right.last_name};
                            if (!is_lastname_less) {
                                return student_left.name < student_right.name;
                            }
                            return is_lastname_less;
                        } else {
                            return student_left.birth_date.day < student_right.birth_date.day;
                        }
                    } else {
                        return student_left.birth_date.month < student_right.birth_date.month;
                    }
                }
                return student_left.birth_date.year < student_right.birth_date.year;
            });
            break;
    }
}
