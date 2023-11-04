#include "shift/shift.hpp"
#include <gtest/gtest.h>

// Test fixture for Shift class
class ShiftTest : public ::testing::Test {
protected:
    Shift shift;
};

TEST_F(ShiftTest, InitialPositionP) {
    EXPECT_EQ(shift.getPosition(), ShiftPosition::P);
    EXPECT_EQ(shift.getShiftString(), "P");
    EXPECT_FALSE(shift.getFaultStatus());
}

TEST_F(ShiftTest, ChangePositionR) {
    shift.changePosition(ShiftPosition::R);
    EXPECT_EQ(shift.getPosition(), ShiftPosition::R);
    EXPECT_EQ(shift.getShiftString(), "R");
}

TEST_F(ShiftTest, ChangePositionN) {
    shift.changePosition(ShiftPosition::N);
    EXPECT_EQ(shift.getPosition(), ShiftPosition::N);
    EXPECT_EQ(shift.getShiftString(), "N");
}

TEST_F(ShiftTest, ChangePositionD) {
    shift.changePosition(ShiftPosition::D);
    EXPECT_EQ(shift.getPosition(), ShiftPosition::D);
    EXPECT_EQ(shift.getShiftString(), "D");
}
