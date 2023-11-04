#ifndef SHIFT_HPP_
#define SHIFT_HPP_

#include <string>
#include <unordered_map>

/// @brief Shift position
enum class ShiftPosition {
    P = 0,
    R,
    N,
    D
};

/// @brief Shift position map
extern std::unordered_map<ShiftPosition, std::string> shiftMap;

/// @brief Shift class
class Shift {
    public:
        /// @brief Constructor
        /// @note Initialize with P position
        Shift();

        /// @brief Destructor
        ~Shift();

        /// @brief Change shift position
        /// @param newPosition The new shift position
        void changePosition(ShiftPosition newPosition);

        /// @brief Get the current shift position
        /// @return The current shift position
        ShiftPosition getPosition() const;

        /// @brief Get the current shift position (string)
        /// @return Shift position
        std::string getShiftString() const;

        /// @brief Get fault status
        /// @return Fault status
        bool getFaultStatus() const;

    private:
        /// @brief Shift position
        ShiftPosition position_;

        /// @brief Fault status
        bool is_fault_;
};

#endif /* SHIFT_HPP_ */
