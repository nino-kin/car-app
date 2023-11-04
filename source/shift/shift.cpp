#include "shift/shift.hpp"

std::unordered_map<ShiftPosition, std::string> shiftMap = {
    {ShiftPosition::P, "P"},
    {ShiftPosition::R, "R"},
    {ShiftPosition::N, "N"},
    {ShiftPosition::D, "D"}
};

Shift::Shift() : position_(ShiftPosition::P), is_fault_(false) {}
Shift::~Shift() {}

void Shift::changePosition(ShiftPosition newPosition) {
    position_ = newPosition;
}

ShiftPosition Shift::getPosition() const {
    return position_;
}

std::string Shift::getShiftString() const {
    return shiftMap[position_];
}

bool Shift::getFaultStatus() const {
    return is_fault_;
}
