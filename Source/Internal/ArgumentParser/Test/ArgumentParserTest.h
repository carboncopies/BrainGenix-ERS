//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

#include <gtest/gtest.h>

class ArgumentParserTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;
};

TEST_F(ArgumentParserTest, ParseArguments);
