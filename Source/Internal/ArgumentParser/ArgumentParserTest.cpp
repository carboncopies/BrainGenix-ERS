#include "ArgumentParser.h"
#include "ERS_LoggingSystem.h"
#include "gtest/gtest.h"

namespace BrainGenix {
namespace ERS {
namespace Module {

class ArgumentParserTest : public ::testing::Test {
protected:
    ERS_LoggingSystem* Logger;
    ArgumentParser* parser;

    void SetUp() override {
        Logger = new ERS_LoggingSystem();
        parser = new ArgumentParser(Logger);
    }

    void TearDown() override {
        delete parser;
        delete Logger;
    }
};

TEST_F(ArgumentParserTest, TestGetArgumentString) {
    const int argc = 3;
    char* argv[argc] = {"program", "-arg1", "value1"};
    parser->ParseArguments(argc, argv);
    ASSERT_EQ(parser->GetArgumentString(), "program -arg1 value1 ");
}

TEST_F(ArgumentParserTest, TestGetArgumentPairs) {
    const int argc = 3;
    char* argv[argc] = {"program", "-arg1", "value1"};
    parser->ParseArguments(argc, argv);

    std::vector<std::pair<std::string, std::string>> argPairs = parser->GetArgumentPairs();
    ASSERT_EQ(argPairs.size(), 1);
    ASSERT_EQ(argPairs[0].first, "arg1");
    ASSERT_EQ(argPairs[0].second, "value1");
}

TEST_F(ArgumentParserTest, TestParseArgumentsWithoutLeadingDash) {
    const int argc = 3;
    char* argv[argc] = {"program", "arg1", "value1"};
    bool result = parser->ParseArguments(argc, argv);
    ASSERT_FALSE(result);
}

TEST_F(ArgumentParserTest, TestParseArgumentsWithUnevenArgs) {
    const int argc = 4;
    char* argv[argc] = {"program", "-arg1", "value1", "-arg2"};
    bool result = parser->ParseArguments(argc, argv);
    ASSERT_FALSE(result);
}

} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix

