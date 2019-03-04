enable_testing()

add_executable(SudokuSolver_unit_test main.cpp boardTest.cpp iteratorTest.cpp tSquareTest.cpp)
target_link_libraries(SudokuSolver_unit_test gtest libSudoku)

add_executable(SudokuSolver_integration_test main.cpp integrationTest.cpp )
target_link_libraries(SudokuSolver_integration_test gtest libSudoku)

add_test(NAME unit_test COMMAND SudokuSolver_unit_test)
add_test(NAME integration_test COMMAND SudokuSolver_integration_test)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS SudokuSolver_unit_test SudokuSolver_integration_test)