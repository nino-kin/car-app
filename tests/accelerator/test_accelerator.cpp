#include <gtest/gtest.h>

#include "accelerator/accelerator.hpp"

// Test fixture for Accelerator class
class AcceleratorTest : public ::testing::Test {
 protected:
  Accelerator accelerator;
};

TEST_F(AcceleratorTest, InitialState) {
  // Initial state should be off
  EXPECT_FALSE(accelerator.getState());
  // Initial pedal ratio should be 0
  EXPECT_EQ(0, accelerator.getRatio());
}

TEST_F(AcceleratorTest, OperateWithValidRatio) {
  // Operate accelerator with 50% ratio
  accelerator.operate(50);
  EXPECT_TRUE(accelerator.getState());    // Accelerator should be on
  EXPECT_EQ(50, accelerator.getRatio());  // Pedal ratio should be 50
}

TEST_F(AcceleratorTest, OperateWithMaxRatio) {
  // Operate accelerator with 100% ratio
  accelerator.operate(100);
  EXPECT_TRUE(accelerator.getState());     // Accelerator should be on
  EXPECT_EQ(100, accelerator.getRatio());  // Pedal ratio should be 100
}

TEST_F(AcceleratorTest, OperateWithLessThanMinRatio) {
  // Operate accelerator with an invalid ratio (-10)
  accelerator.operate(-10);
  EXPECT_FALSE(accelerator.getState());  // Accelerator should be off
  EXPECT_EQ(0, accelerator.getRatio());  // Pedal ratio should be 0

  // Check if an error message is printed
  // Note: This assumes that you have a mechanism in place to print error
  // messages. If not, you might need to modify the Accelerator class or the
  // test accordingly. For the sake of this example, we assume that an error
  // message is printed to std::cout. You can adapt this part based on your
  // actual implementation.
  testing::internal::CaptureStdout();
  accelerator.operate(-10);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(output.find("[error] Accelerator is broken!") !=
              std::string::npos);
}

TEST_F(AcceleratorTest, OperateWithGreaterThanMaxRatio) {
  // Operate accelerator with an invalid ratio (150)
  accelerator.operate(150);
  EXPECT_FALSE(accelerator.getState());  // Accelerator should be off
  EXPECT_EQ(0, accelerator.getRatio());  // Pedal ratio should be 0

  // Check if an error message is printed
  // Note: This assumes that you have a mechanism in place to print error
  // messages. If not, you might need to modify the Accelerator class or the
  // test accordingly. For the sake of this example, we assume that an error
  // message is printed to std::cout. You can adapt this part based on your
  // actual implementation.
  testing::internal::CaptureStdout();
  accelerator.operate(150);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(output.find("[error] Accelerator is broken!") !=
              std::string::npos);
}
