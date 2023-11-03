#ifndef ACCELERATOR_HPP_
#define ACCELERATOR_HPP_

#include <iostream>

static const int ACCELERATOR_MIN_RATIO = 0;
static const int ACCELERATOR_MAX_RATIO = 100;

/// @brief Accelerator class
class Accelerator {
    public:
        Accelerator() : is_state_(false), pedal_ratio_(0), is_fault_(false) {}
        ~Accelerator() {}

        /// @brief Operate the accelerator pedal
        /// @note Range: 0-100%
        void operate(int pedal_ratio) {
            if (pedal_ratio > ACCELERATOR_MAX_RATIO) {
                pedal_ratio = 0;
                is_fault_ = true;
                std::cout << "[error] Accelerator is broken!" << std::endl;
            } else if (pedal_ratio < ACCELERATOR_MIN_RATIO) {
                pedal_ratio = 0;
                is_fault_ = true;
                std::cout << "[error] Accelerator is broken!" << std::endl;
            }
            pedal_ratio_ = pedal_ratio;
            if (pedal_ratio_ > ACCELERATOR_MIN_RATIO) {
                is_state_ = true;
            } else {
                is_state_ = false;
            }
        }

        /// @brief Get the current accelerator state
        /// @return The current accelerator state
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
        /// @brief Accelerator state
        bool is_state_;

        /// @brief Accelerator pedal ratio
        /// @note Range: 0-100%
        int pedal_ratio_;

        /// @brief Fault status
        bool is_fault_;
};

#endif /* ACCELERATOR_HPP_ */
