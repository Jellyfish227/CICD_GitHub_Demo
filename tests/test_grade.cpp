#include "grade.hpp"

#include <iostream>

namespace {

int failures = 0;

void expect(bool condition, const char* name) {
    if (condition) {
        std::cout << "PASS " << name << '\n';
        return;
    }
    std::cerr << "FAIL " << name << '\n';
    ++failures;
}

}  // namespace

// Rubric for the grading functions. A non-zero exit fails the CTest check.
int main() {
    expect(percentage(8, 10) == 80, "percentage 8/10");
    expect(percentage(10, 10) == 100, "percentage full marks");
    expect(percentage(0, 10) == 0, "percentage zero earned");
    expect(percentage(1, 3) == 33, "percentage integer division");
    expect(percentage(15, 10) == 100, "percentage capped at 100");
    expect(percentage(-1, 10) == 0, "percentage negative earned");
    expect(percentage(5, 0) == 0, "percentage zero possible");
    expect(percentage(5, -2) == 0, "percentage negative possible");

    expect(letter_grade(100) == 'A', "letter 100");
    expect(letter_grade(90) == 'A', "letter 90");
    expect(letter_grade(89) == 'B', "letter 89");
    expect(letter_grade(80) == 'B', "letter 80");
    expect(letter_grade(79) == 'C', "letter 79");
    expect(letter_grade(70) == 'C', "letter 70");
    expect(letter_grade(69) == 'D', "letter 69");
    expect(letter_grade(60) == 'D', "letter 60");
    expect(letter_grade(59) == 'F', "letter 59");
    expect(letter_grade(0) == 'F', "letter 0");

    expect(is_passing(60), "passing at 60");
    expect(is_passing(100), "passing at 100");
    expect(!is_passing(59), "failing at 59");
    expect(!is_passing(0), "failing at 0");

    if (failures != 0) {
        std::cerr << failures << " check(s) failed\n";
        return 1;
    }
    std::cout << "all checks passed\n";
    return 0;
}
