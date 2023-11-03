#ifndef CAR_HPP_
#define CAR_HPP_

#include "car_spec.hpp"
#include "accelerator/accelerator.hpp"
#include "brake/brake.hpp"
#include "shift/shift.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

/// @brief The car power state
/// @note ACC: very limited power--pretty much just the radio, MFD, Bluetooth. One push of the Power button without your foot on the brake.
/// @note POWER_ON: gives you power to the fans, windows, and most other stuff. 2 pushes of the Power button without your foot on the brake.
/// @note READY: closes the circuits to the HV battery and fires up all the ECUs to make the car drivable. Any single press of the Power button while your foot is on the brake from either ACC, POWER ON, or when the car is totally off.
enum class PowerState {
    OFF = 0,
    ACC,
    POWER_ON,
    READY
};

extern std::unordered_map<PowerState, std::string> powerStateMap;

class Car {
    public:
        /// @brief Constructor
        /// @note Initialize with power off, speed 0, driving mode STOP, and fully charged battery
        explicit Car(std::string name);
        ~Car();

        /// @brief Get the car name
        /// @return The car name
        std::string getCarName();

        void pushPowerSW();

        /// @brief Get power state
        /// @return The power state
        PowerState getPowerState();

        /// @brief Get accelerator object
        /// @return Accelerator object
        Accelerator& getAccelerator();

        /// @brief Get brake object
        /// @return Brake object
        Brake& getBrake();

        /// @brief Get the current speed
        /// @return The current speed
        int getSpeed();

        /// @brief Set the new shift position
        /// @param newPosition
        void operateShiftPosition(ShiftPosition newPosition);

        /// @brief Get the current shift position
        /// @return Shift object
        ShiftPosition getShiftPosition();

        /// @brief Update speed
        void updateSpeed();

        /// @brief Display car information
        void displayInfo() const;

        bool getFaultStatus() const;

    private:
        /// @brief Car name
        std::string name_;

        /// @brief Power state
        PowerState power_state_;

        /// @brief Speed [km/h]
        int speed_;

        /// @brief Accelerator pedal object
        Accelerator accelerator_;

        /// @brief Brake pedal object
        Brake brake_;

        /// @brief Shift object
        Shift shift_;

        /// @brief Fault status
        bool is_fault_;
};

#endif /* CAR_HPP_ */
