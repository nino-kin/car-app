#include "car_spec.hpp"
#include "car/car.hpp"
#include "driver/driver.hpp"

#include <iostream>
#include <thread>
#include <chrono>

int main() {
    Car car(CAR_NAME);
    Driver driver;

    // Initial state
    car.displayInfo();

    std::thread driverThread([&]() {
        // Power on
        std::cout << "[info] Power on..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        driver.operateBrake(car, 50);
        car.displayInfo();
        driver.pushPowerSW(car);
        car.displayInfo();

        // Operate shift position
        std::cout << "[info] Change shift position to D range..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        driver.operateShift(car, ShiftPosition::D);
        car.displayInfo();

        /// Release brake pedal
        driver.operateBrake(car, 0);
        car.displayInfo();

        // Acceleration
        std::cout << "[info] Speed up..." << std::endl;
        for (int i = 0; i < 20; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            driver.operateAccelerator(car, 30);
            car.displayInfo();
        }
        driver.operateAccelerator(car, 0);

        // Deceleration
        std::cout << "[info] Speed down until the car stops..." << std::endl;
        while (car.getSpeed() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            driver.operateBrake(car, 50);
            car.displayInfo();
        }

        // Operate shift position
        std::cout << "[info] Change shift position to P range..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        driver.operateShift(car, ShiftPosition::P);
        car.displayInfo();

        // Power off
        std::cout << "[info] Power off..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        driver.pushPowerSW(car);
        driver.operateBrake(car, 0);
        car.displayInfo();
    });

    while (car.getPowerState() == PowerState::OFF) {
        std::cout << "[info] Waiting for car to wake up..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::thread ecuThread([&]() {
        while (car.getPowerState() != PowerState::OFF) {
            // TODO: Need to add new functions to update car status
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    std::thread carThread([&]() {
        while (car.getPowerState() != PowerState::OFF) {
            car.updateSpeed();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    driverThread.join();
    ecuThread.join();
    carThread.join();

    return 0;
}
