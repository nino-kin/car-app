#include <gtest/gtest.h>

#include "car/car.hpp"
#include "car_spec.hpp"

// Test fixture for Vehicle class
class CarTest : public ::testing::Test {
 protected:
  Car car{"Test"};
};

TEST_F(CarTest, InitialState) {
  EXPECT_EQ(PowerState::OFF, car.getPowerState());
  EXPECT_EQ(0, car.getSpeed());
  EXPECT_EQ(0, car.getAccelerator().getRatio());
  EXPECT_EQ(0, car.getBrake().getRatio());
  EXPECT_EQ(ShiftPosition::P, car.getShiftPosition());
  EXPECT_EQ("Test", car.getCarName());
  EXPECT_TRUE(car.getFaultStatus());
}

TEST_F(CarTest, StartAndStop) {
  // ACC ON
  car.pushPowerSW();
  EXPECT_EQ(PowerState::ACC, car.getPowerState());
  EXPECT_EQ(ShiftPosition::P, car.getShiftPosition());

  // POWER ON
  car.pushPowerSW();
  EXPECT_EQ(PowerState::ON, car.getPowerState());
  EXPECT_EQ(ShiftPosition::P, car.getShiftPosition());
  EXPECT_FALSE(car.getFaultStatus());

  // READY ON
  car.getBrake().operate(10);
  car.pushPowerSW();
  testing::internal::CaptureStdout();
  car.displayInfo();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(output.find("[info] Power: READY, Shift: P, Accelerator: 0%, "
                          "Brake: 10%, Speed: 0km/h") != std::string::npos);
  EXPECT_EQ(PowerState::READY, car.getPowerState());
  EXPECT_EQ(ShiftPosition::P, car.getShiftPosition());
  EXPECT_FALSE(car.getFaultStatus());
  car.getBrake().operate(0);

  // Change the shift position
  car.getBrake().operate(10);
  car.operateShiftPosition(ShiftPosition::R);
  EXPECT_EQ(ShiftPosition::R, car.getShiftPosition());
  car.operateShiftPosition(ShiftPosition::N);
  EXPECT_EQ(ShiftPosition::N, car.getShiftPosition());
  car.operateShiftPosition(ShiftPosition::D);
  EXPECT_EQ(ShiftPosition::D, car.getShiftPosition());
  car.getBrake().operate(0);

  // Running
  car.getAccelerator().operate(30);
  car.updateSpeed();
  EXPECT_LT(0, car.getSpeed());
  EXPECT_EQ(ShiftPosition::D, car.getShiftPosition());

  // Accelerate to the top speed
  while (car.getSpeed() < TOP_SPEED) {
    car.getAccelerator().operate(100);
    car.updateSpeed();
  }
  EXPECT_EQ(TOP_SPEED, car.getSpeed());

  // Power OFF while driving
  car.pushPowerSW();
  EXPECT_EQ(PowerState::OFF, car.getPowerState());
  EXPECT_EQ(ShiftPosition::D, car.getShiftPosition());

  // Continue stepping on the brake until the car comes to a stop
  while (car.getSpeed() > 0) {
    car.getBrake().operate(10);
    car.updateSpeed();
    std::cout << "Speed: " << car.getSpeed() << std::endl;
  }
  car.operateShiftPosition(ShiftPosition::P);
  car.getBrake().operate(0);
  EXPECT_EQ(0, car.getSpeed());
  EXPECT_EQ(PowerState::OFF, car.getPowerState());
  EXPECT_EQ(ShiftPosition::P, car.getShiftPosition());

  // Power ON again
  car.getBrake().operate(10);
  car.pushPowerSW();
  car.getBrake().operate(0);
  EXPECT_EQ(PowerState::READY, car.getPowerState());

  // Power OFF
  car.pushPowerSW();
  EXPECT_EQ(PowerState::OFF, car.getPowerState());
}

TEST_F(CarTest, OperatePowerStateFromACCToREADY) {
  // ACC ON
  car.pushPowerSW();
  EXPECT_EQ(PowerState::ACC, car.getPowerState());
  EXPECT_EQ(ShiftPosition::P, car.getShiftPosition());

  // READY ON
  car.getBrake().operate(10);
  car.pushPowerSW();
  car.getBrake().operate(0);
  EXPECT_EQ(PowerState::READY, car.getPowerState());
  EXPECT_EQ(ShiftPosition::P, car.getShiftPosition());

  // Power OFF
  car.pushPowerSW();
  EXPECT_EQ(PowerState::OFF, car.getPowerState());
  EXPECT_EQ(ShiftPosition::P, car.getShiftPosition());
}
