#include "scorer.h"

#include <unordered_map>

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable score_table;
    auto temp = events;
    std::sort(temp.begin(), temp.end(), [](auto& a, auto& b) { return a.time < b.time; });
    for (auto& event : temp) {
        if (event.time <= score_time) {
            switch (event.event_type) {
                case EventType::MergeRequestOpen:
                case EventType::CheckFailed:
                    score_table[event.student_name].erase(event.task_name);
                    if (score_table[event.student_name].empty()) {
                        score_table.erase(event.student_name);
                    }
                    break;
                case EventType::MergeRequestClosed:
                case EventType::CheckSuccess:
                    score_table[event.student_name].insert(event.task_name);
                    break;
            }
        }
    }

    return score_table;  // test
}
