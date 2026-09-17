#include "Seat.h"

using namespace std;

Seat::Seat(const string& id, bool isVip, bool isMaintenanceValue)
    : seatId(id), vip(isVip), maintenance(isMaintenanceValue) {}

string Seat::getSeatId() const { return seatId; }
bool Seat::isVIP() const { return vip; }
bool Seat::isMaintenance() const { return maintenance; }

void Seat::setVIP(bool value) { vip = value; }
void Seat::setMaintenance(bool value) { maintenance = value; }


bool Seat::operator==(const Seat& other) const
{
    return seatId == other.seatId;
}
