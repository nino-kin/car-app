#include <gtest/gtest.h>

#include "car/car.hpp"
#include "driver/driver.hpp"
#include "shift/shift.hpp"

// Test case for pushPowerSW
TEST(DriverTest, PushPowerSW) {
  // Create a car
  Car car("Test");
  Driver driver;

  // Power state is OFF, so pushing the switch should change it to ACC
  driver.pushPowerSW(car);
  EXPECT_EQ(car.getPowerState(), PowerState::ACC);

  // Power state is ACC, so pushing the switch should change it to READY
  driver.pushPowerSW(car);
  EXPECT_EQ(car.getPowerState(), PowerState::ON);

  // Power state is POWER ON, so pushing the switch should change it to READY
  driver.operateBrake(car, 50);
  driver.pushPowerSW(car);
  EXPECT_EQ(car.getPowerState(), PowerState::READY);

  // Power state is READY, so pushing the switch should turn the car OFF
  driver.pushPowerSW(car);
  EXPECT_EQ(car.getPowerState(), PowerState::OFF);
}

// Test case for operateShiftPosition
TEST(DriverTest, OperateShiftPosition) {
  // Create a car
  Car car("Test");
  Driver driver;

  // Power state is OFF, shifting should not work
  driver.operateShift(car, ShiftPosition::D);
  EXPECT_NE(car.getShiftPosition(), ShiftPosition::D);

  // Power state is READY, shifting should work
  driver.operateBrake(car, 50);
  driver.pushPowerSW(car);
  driver.operateShift(car, ShiftPosition::D);
  EXPECT_EQ(car.getShiftPosition(), ShiftPosition::D);
}

// Test case for operateAccelerator
TEST(DriverTest, OperateAccelerator) {
  // Create a car
  Car car("Test");
  Driver driver;

  // Accelerator is operated with 50% ratio
  driver.operateAccelerator(car, 50);
  EXPECT_EQ(car.getAccelerator().getRatio(), 50);

  // Accelerator is operated with 100% ratio
  driver.operateAccelerator(car, 100);
  EXPECT_EQ(car.getAccelerator().getRatio(), 100);

  // Accelerator is operated with 0% ratio
  driver.operateAccelerator(car, 0);
  EXPECT_EQ(car.getAccelerator().getRatio(), 0);
}

// Test case for operateBrake
TEST(DriverTest, OperateBrake) {
  // Create a car
  Car car("Test");
  Driver driver;

  // Brake is operated with 50% ratio
  driver.operateBrake(car, 50);
  EXPECT_EQ(car.getBrake().getRatio(), 50);

  // Brake is operated with 100% ratio
  driver.operateBrake(car, 100);
  EXPECT_EQ(car.getBrake().getRatio(), 100);

  // Brake is operated with 0% ratio
  driver.operateBrake(car, 0);
  EXPECT_EQ(car.getBrake().getRatio(), 0);
}
