//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ArgumentParserTest.h>

// Your gtest code here...

TEST(AddTwoNumbersTest, PositiveNumbers) {
    int a = 5;
    int b = 5;
    int expected_result = 10;

    ASSERT_EQ(a+b, expected_result);
}