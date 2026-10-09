#include "grade.hpp"

#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace {

bool parse_int(const char* text, int& value) {
    errno = 0;
    char* end = nullptr;
    const long parsed = std::strtol(text, &end, 10);
    if (text[0] == '\0' || end == text || *end != '\0' || errno == ERANGE) {
        return false;
    }
    if (parsed < std::numeric_limits<int>::min() || parsed > std::numeric_limits<int>::max()) {
        return false;
    }
    value = static_cast<int>(parsed);
    return true;
}

}  // namespace

// Prints three lines: the percentage, the letter, and pass or fail.
// Usage: grader <earned> <possible>
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: grader <earned> <possible>\n";
        return 1;
    }

    int earned = 0;
    int possible = 0;
    if (!parse_int(argv[1], earned) || !parse_int(argv[2], possible)) {
        std::cerr << "earned and possible must be integers\n";
        return 1;
    }

    const int percent = percentage(earned, possible);
    const char letter = letter_grade(percent);
    std::cout << percent << "%\n"
              << letter << '\n'
              << (is_passing(percent) ? "pass" : "fail") << '\n';
    return 0;
}
