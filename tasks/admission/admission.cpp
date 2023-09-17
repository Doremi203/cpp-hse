#include "admission.h"

#include <map>

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> temp;
    AdmissionTable res;
    std::map<std::string, size_t> uni_map;

    for (auto& applicant : applicants) {
        temp.push_back(&applicant);
    }

    for (auto& uni : universities) {
        uni_map[uni.name] = uni.max_students;
    }

    std::sort(temp.begin(), temp.end(), [](auto& a, auto& b) {
        if (a->points == b->points) {
            if (a->student.birth_date.year == b->student.birth_date.year) {
                if (a->student.birth_date.month == b->student.birth_date.month) {
                    if (a->student.birth_date.day == b->student.birth_date.day) {
                        return a->student.name <= b->student.name;
                    }
                    return a->student.birth_date.day < b->student.birth_date.day;
                }
                return a->student.birth_date.month < b->student.birth_date.month;
            }
            return a->student.birth_date.year < b->student.birth_date.year;
        }
        return a->points > b->points;
    });

    for (auto& applicant : temp) {
        for (auto& item : applicant->wish_list) {
            if (uni_map[item] > 0) {
                res[item].push_back(&applicant->student);
                --uni_map[item];
                break;
            }
        }
    }

    return res;
}
