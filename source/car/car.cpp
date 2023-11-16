#include "car.hpp"

std::unordered_map<PowerState, std::string> powerStateMap = {
    {PowerState::OFF, "OFF"},
    {PowerState::ACC, "ACC"},
    {PowerState::ON, "POWER ON"},
    {PowerState::READY, "READY"}};

Car::Car(std::string name)
    : name_(name), power_state_(PowerState::OFF), speed_(0), is_fault_(true) {}

Car::~Car() {}

std::string Car::getCarName() { return name_; }

void Car::pushPowerSW() {
  switch (power_state_) {
    case PowerState::OFF:
      power_state_ = PowerState::ACC;
      if (brake_.getState()) {
        systemCheck();
        power_state_ = PowerState::READY;
      }
      break;
    case PowerState::ACC:
      power_state_ = PowerState::ON;
      systemCheck();
      if (brake_.getState()) {
        power_state_ = PowerState::READY;
      }
      break;
    case PowerState::ON:
      power_state_ = PowerState::OFF;
      if (brake_.getState()) {
        systemCheck();
        power_state_ = PowerState::READY;
      }
      break;
    case PowerState::READY:
      power_state_ = PowerState::OFF;
      break;
    default:
      is_fault_ = true;
      std::cout << "[error] Unknown power state." << std::endl;
      break;
  }
}

PowerState Car::getPowerState() { return power_state_; }

Accelerator& Car::getAccelerator() { return accelerator_; }

Brake& Car::getBrake() { return brake_; }

int Car::getSpeed() { return speed_; }

void Car::operateShiftPosition(ShiftPosition newPosition) {
  if (brake_.getState()) {
    shift_.changePosition(newPosition);
  }
}

ShiftPosition Car::getShiftPosition() { return shift_.getPosition(); }

void Car::updateSpeed() {
  bool is_accelerator = accelerator_.getState();
  bool is_brake = brake_.getState();
  int speed = speed_;

  if (is_brake) {
    speed -= 10 * DECELERATION_RATE * brake_.getRatio();
  } else if (is_accelerator && power_state_ == PowerState::READY) {
    speed += 10 * ACCELERATION_RATE * accelerator_.getRatio();
  }
  if (speed > TOP_SPEED) {
    speed = TOP_SPEED;
  }
  if (speed <= 0) {
    speed = 0;
  }
  speed_ = speed;
}

void Car::displayInfo() const {
  std::cout << "[info] "
            << "Power: " << powerStateMap[power_state_] << ", "
            << "Shift: " << shift_.getShiftString() << ", "
            << "Accelerator: " << accelerator_.getRatio() << "%, "
            << "Brake: " << brake_.getRatio() << "%, "
            << "Speed: " << speed_ << "km/h" << std::endl;
}

bool Car::getFaultStatus() const { return is_fault_; }

void Car::systemCheck() {
  // TODO: We need to check every car parts in this process.
  is_fault_ = false;
}
