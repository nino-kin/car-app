#ifndef DRIVER_HPP_
#define DRIVER_HPP_

#include "car/car.hpp"

/// @brief Driver class
class Driver {
    public:
        /// @brief Push the switch to turn on/off the car
        /// @param car Car object
        void pushPowerSW(Car& car) {
            car.pushPowerSW();
        }

        /// @brief Operate the shift position
        /// @param car Car object
        /// @param newPosition Shift position
        void operateShift(Car& car, ShiftPosition newPosition) {
            car.operateShiftPosition(newPosition);
        }

        /// @brief Operate the accelerator pedal
        /// @param car Car object
        void operateAccelerator(Car& car, int pedal_ratio) {
            car.getAccelerator().operate(pedal_ratio);
        }

        /// @brief Operate the brake pedal
        /// @param car Car object
        void operateBrake(Car& car, int pedal_ratio) {
            car.getBrake().operate(pedal_ratio);
        }
};

#endif /* DRIVER_HPP_ */
