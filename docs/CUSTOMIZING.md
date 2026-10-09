# Customizing the autograder

Change the setting in the file named here, then configure, build, and run CTest locally before pushing. The workflow grades the pushed branch on GitHub.

| File | Setting | What it controls | How to change |
| --- | --- | --- | --- |
| `.github/workflows/ci.yml` | `on: push` | Grades the commit after a push. | Remove this block to stop grading pushes. Leave `pull_request` in place if pull requests should still be graded. |
| `.github/workflows/ci.yml` | `on: pull_request` | Grades the head commit of a pull request. | Remove this block to stop grading pull requests. Do not replace it with `pull_request_target`. |
| `.github/workflows/ci.yml` | `env.BUILD_TYPE` | CMake configuration passed to the configure step. | Set `Release` or `Debug`. The configure step reads `${{ env.BUILD_TYPE }}`. |
| `.github/workflows/ci.yml` | `matrix.os` | Runner image for the grade job. | Keep `ubuntu-latest` as the primary runner. Add another image only after agreeing to expand the matrix. |
| `.github/workflows/ci.yml` | Checkout step | Which revision the job builds. | Keep `actions/checkout` pinned to a major version. The current major is v7. Read the actions/checkout README before bumping it. |
| `.github/workflows/ci.yml` | Configure step | Where CMake writes the build tree and which configuration it selects. | Edit the `cmake -S . -B build` command. Keep the build directory as `build/` so it stays gitignored. |
| `.github/workflows/ci.yml` | Build step | How the program and tests are compiled. | Edit the `cmake --build` command. `--parallel` uses the runner's available cores. |
| `.github/workflows/ci.yml` | Test step | Which tests form the grade, and that zero tests count as a failure. | Edit the `ctest` command. Keep `--no-tests=error` so a project with no `add_test()` calls fails the job. |
| `CMakeLists.txt` | `CMAKE_CXX_STANDARD` | Language standard for the program and the tests. | Set the standard the sources actually use. `CMAKE_CXX_STANDARD_REQUIRED` keeps CMake from silently falling back. |
| `CMakeLists.txt` | `add_compile_options` | Warning flags for every target. | Add a flag to tighten the rubric. Remove `-Werror` if a warning should not fail the grade. |
| `CMakeLists.txt` | `grade` library | Sources that implement the graded functions. | Add or remove files in the `add_library` list. Public headers stay on the `src` include path. |
| `CMakeLists.txt` | `grader` executable | Command-line program the CLI tests run. | Change `src/main.cpp` or the linked libraries. The test names expect the executable to stay named `grader`. |
| `CMakeLists.txt` | `grade_tests` executable | Program that runs the function rubric. | Add a source under `tests/` and list it here, then register it with `add_test()`. |
| `CMakeLists.txt` | `grade_unit` | CTest name for the function rubric. | Rename it in `add_test` and in `docs/CUSTOMIZING.md` together. `ctest -R grade_unit` selects it. |
| `CMakeLists.txt` | `grade_cli_pass` | Expected output for `grader 8 10`. | Change the arguments and the `PASS_REGULAR_EXPRESSION` list together. Each semicolon-separated pattern must match stdout. |
| `CMakeLists.txt` | `grade_cli_fail` | Expected output for `grader 5 10`. | Change the arguments and the `PASS_REGULAR_EXPRESSION` list together. |
| `CMakeLists.txt` | `grade_cli_usage` | Expects `grader` with no arguments to exit non-zero. | `WILL_FAIL TRUE` passes when the command fails. Remove the property if a usage error should fail the grade. |
| `README.md` | CI badge | Status image for the `ci` workflow. | Replace `OWNER/REPO` with the GitHub owner and repository name after the project is pushed. |
