//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ArgumentParserTest.h>

// Your gtest code here...

TEST_F(ArgumentParserTest, ParseArguments) {
    // Arrange
    const int argc = 6;
    char* argv[argc] = {"./program", "-input", "file.txt", "-output", "output.txt", "-verbose"};
    const std::vector<std::pair<std::string, std::string>> expectedPairs = {
        {"input", "file.txt"},
        {"output", "output.txt"},
        {"verbose", ""}
    };
    const std::string expectedString = "-input file.txt -output output.txt -verbose ";

    // Act
    const bool result = parser->ParseArguments(argc, argv);

    // Assert
    EXPECT_TRUE(result);
    EXPECT_EQ(parser->GetArgumentString(), expectedString);
    EXPECT_EQ(parser->GetArgumentPairs(), expectedPairs);
}
