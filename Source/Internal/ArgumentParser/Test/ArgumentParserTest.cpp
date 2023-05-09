#include <gtest/gtest.h>
#include <ArgumentParser.h>

using namespace BrainGenix::ERS::Module;

class ArgumentParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a new ArgumentParser instance
        parser = new ArgumentParser(&logger);
    }

    void TearDown() override {
        // Delete the ArgumentParser instance
        delete parser;
    }

    // Declare variables
    ArgumentParser* parser;
    ERS_LoggingSystem logger;
};

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
