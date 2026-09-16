#include "Seat.h"

Seat::Seat(string id, bool vip, bool booked) 
    : seatId(id), isVIP(vip), isBooked(booked) {}

string Seat::getSeatId() const { return seatId; }
bool Seat::getIsVIP() const { return isVIP; }
bool Seat::getIsBooked() const { return isBooked; }

void Seat::setBooked(bool booked) { isBooked = booked; }