#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> deque;
    std::vector<std::string> res;
    for (auto& action : student_actions) {
        switch (action.side) {
            case Side::Top:
                deque.push_front(action.name);
                break;
            case Side::Bottom:
                deque.push_back(action.name);
                break;
        }
    }
    for (auto& item : queries) {
        res.push_back(deque[item - 1]);
    }
    return res;
}
