#include "grade.hpp"

int percentage(int earned, int possible) {
    if (possible <= 0 || earned < 0) {
        return 0;
    }
    const long long scaled =
        (static_cast<long long>(earned) * 100) / static_cast<long long>(possible);
    if (scaled > 100) {
        return 100;
    }
    return static_cast<int>(scaled);
}

char letter_grade(int percent) {
    if (percent >= 90) {
        return 'X';
    }
    if (percent >= 80) {
        return 'X';
    }
    if (percent >= 70) {
        return 'X';
    }
    if (percent >= 60) {
        return 'X';
    }
    return 'X';
}

bool is_passing(int percent) {
    return percent >= 60;
}
