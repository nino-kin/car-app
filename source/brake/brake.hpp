#ifndef BRAKE_HPP_
#define BRAKE_HPP_

#include <iostream>

static const int BRAKE_PEDAL_MIN_RATIO = 0;
static const int BRAKE_PEDAL_MAX_RATIO = 100;

/// @brief Brake class
class Brake {
    public:
        /// @brief Constructor
        Brake() : is_state_(false), pedal_ratio_(0), is_fault_(false) {}

        /// @brief Destructor
        ~Brake() {}

        /// @brief Operate the brake pedal
        /// @note Range: 0-100%
        void operate(int pedal_ratio) {
            if (pedal_ratio > BRAKE_PEDAL_MAX_RATIO) {
                pedal_ratio = 0;
                is_fault_ = true;
                std::cout << "[error] Brake is broken!" << std::endl;
            } else if (pedal_ratio < BRAKE_PEDAL_MIN_RATIO) {
                pedal_ratio = 0;
                is_fault_ = true;
                std::cout << "[error] Brake is broken!" << std::endl;
            }
            pedal_ratio_ = pedal_ratio;
            if (pedal_ratio_ > BRAKE_PEDAL_MIN_RATIO) {
                is_state_ = true;
            } else {
                is_state_ = false;
            }
        }

        /// @brief Get the current brake state
        /// @return The current brake state
        bool getState() const {
            return is_state_;
        }

        /// @brief Get the current pedal ratio
        /// @return The current pedal ratio
        int getRatio() const {
            return pedal_ratio_;
        }

        /// @brief Get fault status
        /// @return Fault status
        bool getFaultStatus() const {
            return is_fault_;
        }

    private:
        /// @brief Brake state
        bool is_state_;

        /// @brief Brake pedal ratio
        /// @note Range: 0-100%
        int pedal_ratio_;

        /// @brief Fault status
        bool is_fault_;
};

#endif /* BRAKE_HPP_ */
