#include <bits/stdc++.h>

using namespace std;

enum VehicleType
{
    BIKE,
    CAR,
    TRUCK
};

enum SlotStatus
{
    OCCUPIED,
    EMPTY
};

vector<int> parseTicket(string ticket)
{

    int n = ticket.size();
    string slotId = "";
    string floorId = "";
    int i;
    for (i = n - 1; i >= 0; i--)
    {
        if (ticket[i] == '_')
        {
            reverse(slotId.begin(), slotId.end());
            i--;
            break;
        }
        slotId += ticket[i];
    }

    for (; i >= 0; i--)
    {
        if (ticket[i] == '_')
        {
            reverse(floorId.begin(), floorId.end());
            i--;
            break;
        }
        floorId += ticket[i];
    }

    return {stoi(floorId), stoi(slotId)};
}

class Slot
{
    int slotId;
    VehicleType slotType;
    SlotStatus slotStatus;

public:
    Slot(int slotId, VehicleType slotType, SlotStatus slotStatus) : slotId(slotId), slotType(slotType), slotStatus(slotStatus) {}
    int getSlotId() const;
    VehicleType getSlotType() const;
    SlotStatus getSlotStatus() const;
    void setSlotStatus(SlotStatus);
};

int Slot::getSlotId() const
{
    return slotId;
}

VehicleType Slot::getSlotType() const
{
    return slotType;
}

SlotStatus Slot::getSlotStatus() const
{
    return slotStatus;
}

void Slot::setSlotStatus(SlotStatus slotStatus)
{
    this->slotStatus = slotStatus;
}

class Floor
{
    int floorId;
    int slotsCount;
    vector<Slot> slots;

public:
    Floor(int floorId, int slotsCount);
    int getFloorId() const;
    vector<Slot> &getSlots();
    void getFreeCount(VehicleType) const;
    void getFreeSlots(VehicleType) const;
    void getOccupiedSlots(VehicleType) const;
};

Floor::Floor(int floorId, int slotsCount)
{
    this->floorId = floorId;
    this->slotsCount = slotsCount;

    for (int slotId = 1; slotId <= slotsCount; slotId++)
    {
        if (slotId == 1)
        {
            Slot slot(slotId, VehicleType::TRUCK, SlotStatus::EMPTY);
            this->slots.push_back(slot);
        }
        else if (slotId <= 3)
        {
            Slot slot(slotId, VehicleType::BIKE, SlotStatus::EMPTY);
            this->slots.push_back(slot);
        }
        else
        {
            Slot slot(slotId, VehicleType::CAR, SlotStatus::EMPTY);
            this->slots.push_back(slot);
        }
    }
}
int Floor::getFloorId() const
{
    return floorId;
}

vector<Slot> &Floor::getSlots()
{
    return slots;
}

void Floor::getFreeCount(VehicleType vehicleType) const
{
    int freeCount = 0;
    for (auto slot : slots)
    {
        if (slot.getSlotType() == vehicleType && slot.getSlotStatus() == SlotStatus::EMPTY)
        {
            freeCount++;
        }
    }
    cout << "No. of free slots for " << vehicleType << " on Floor " << floorId << " : " << freeCount << endl;
}

void Floor::getFreeSlots(VehicleType vehicleType) const
{
    cout << "No. of free slots for " << vehicleType << " on Floor " << floorId << " : ";
    for (auto slot : slots)
    {

        if (slot.getSlotType() == vehicleType && slot.getSlotStatus() == SlotStatus::EMPTY)
        {
            cout << slot.getSlotId() << ", ";
        }
    }
    cout << endl;
}

void Floor::getOccupiedSlots(VehicleType vehicleType) const
{
    cout << "No. of ocuupied slots for " << vehicleType << " on Floor " << floorId << " : ";
    for (auto slot : slots)
    {

        if (slot.getSlotType() == vehicleType && slot.getSlotStatus() == SlotStatus::OCCUPIED)
        {
            cout << slot.getSlotId() << ", ";
        }
    }
    cout << endl;
}

class Vehicle
{
    VehicleType vehicleType;
    string registrationNumber;
    string color;

public:
    Vehicle(VehicleType vehicleType, string registrationNumber, string color) : vehicleType(vehicleType), registrationNumber(registrationNumber), color(color) {}
    VehicleType getVehicleType() const;
    string getRegistrationNumber() const;
    string getColor() const;
};

VehicleType Vehicle::getVehicleType() const
{
    return vehicleType;
}

string Vehicle::getRegistrationNumber() const
{
    return registrationNumber;
}

string Vehicle::getColor() const
{
    return color;
}

class ParkingLot
{
    string parkingId;
    int floorCount;
    int slotsPerFloorCount;
    vector<Floor> floors;

public:
    ParkingLot(string, int, int);
    string getParkingId() const;
    int getFloorCount() const;
    int getSlotsPerFloorCount() const;
    void setParkingId(string);
    void setFloorCount(int);
    void setSlotsPerFloorCount(int);
    void setFloors(int, int);
    vector<Floor> getFloors() const;
    void bookSlot(Vehicle);
    void unpark(string);
    void getFreeCount(VehicleType) const;
    void getFreeSlots(VehicleType) const;
    void getOccupiedSlots(VehicleType) const;
};

ParkingLot::ParkingLot(string parkingId, int floorCount, int slotsPerFloorCount)
{
    this->parkingId = parkingId;
    this->floorCount = floorCount;
    this->slotsPerFloorCount = slotsPerFloorCount;

    for (int floorId = 1; floorId <= floorCount; floorId++)
    {
        Floor floor(floorId, slotsPerFloorCount);
        this->floors.push_back(floor);
    }
}

string ParkingLot::getParkingId() const
{
    return this->parkingId;
}

int ParkingLot::getFloorCount() const
{
    return this->floorCount;
}

int ParkingLot::getSlotsPerFloorCount() const
{
    return this->slotsPerFloorCount;
}

void ParkingLot::setParkingId(string parkingId)
{
    this->parkingId = parkingId;
}

void ParkingLot::setFloorCount(int floorCount)
{
    this->floorCount = floorCount;
}

void ParkingLot::setSlotsPerFloorCount(int slotsPerFloorCount)
{
    this->slotsPerFloorCount = slotsPerFloorCount;
}

void ParkingLot::setFloors(int floorCount, int slotsPerFloorCount)
{
    for (int floorId = 1; floorId <= floorCount; floorId++)
    {
        Floor floor(floorId, slotsPerFloorCount);
        this->floors.push_back(floor);
    }
}

vector<Floor> ParkingLot::getFloors() const
{
    return this->floors;
}

void ParkingLot::bookSlot(Vehicle vehicle)
{
    for (auto &floor : this->floors)
    {
        auto *slots = &floor.getSlots();
        for (auto &slot : *slots)
        {
            if (slot.getSlotType() == vehicle.getVehicleType() && slot.getSlotStatus() == SlotStatus::EMPTY)
            {
                slot.setSlotStatus(SlotStatus::OCCUPIED);
                cout << "Parked vehicle. Ticket ID: " << parkingId << "-" << floor.getFloorId() << "-" << slot.getSlotId() << endl;
                return;
            }
        }
    }
    cout << "Parking Lot full" << endl;
}

void ParkingLot::unpark(string ticket)
{

    auto ticketInfo = parseTicket(ticket);
    if (ticketInfo[0] <= floors.size())
    {
        Floor *floor = &floors[ticketInfo[0] - 1];
        Slot *slot = &floor->getSlots()[ticketInfo[1] - 1];
        if (slot->getSlotStatus() == SlotStatus::OCCUPIED)
        {
            slot->setSlotStatus(SlotStatus::EMPTY);
            cout << "Unparked vehicle floor: " << floor->getFloorId() << " and slot no.: " << slot->getSlotId() << endl;
        }
        else
        {
            cout << "Invalid ticket" << endl;
        }
    }
    else
    {
        cout << "Invalid ticket" << endl;
    }
}

void ParkingLot::getFreeCount(VehicleType vehicleType) const
{
    for (auto floor : floors)
    {
        floor.getFreeCount(vehicleType);
    }
}

void ParkingLot::getFreeSlots(VehicleType vehicleType) const
{
    for (auto floor : floors)
    {
        floor.getFreeSlots(vehicleType);
    }
}

void ParkingLot::getOccupiedSlots(VehicleType vehicleType) const
{
    for (auto floor : floors)
    {
        floor.getOccupiedSlots(vehicleType);
    }
}
int main()
{

    cout << "================Welcome to Parking Lot System==========================\n";
    ParkingLot parkingLot("null", 0, 0);

    while (1)
    {
        string commandOne;
        cin >> commandOne;

        if (commandOne == "create_parking_lot")
        {
            string parkingId;
            int floorCount;
            int slotsPerFloor;
            cin >> parkingId >> floorCount >> slotsPerFloor;
            parkingLot.setParkingId(parkingId);
            parkingLot.setFloorCount(floorCount);
            parkingLot.setSlotsPerFloorCount(slotsPerFloor);
            parkingLot.setFloors(floorCount, slotsPerFloor);
            cout << "Parking Lot with " << floorCount << " and" << slotsPerFloor << " slots per floor created." << endl;
        }
        else if (commandOne == "display")
        {
            string commandTwo;
            cin >> commandTwo;
            if (commandTwo == "free_count")
            {
                string vehicleType;
                cin >> vehicleType;
                if (vehicleType == "BIKE")
                {
                    parkingLot.getFreeCount(VehicleType::BIKE);
                }
                else if (vehicleType == "TRUCK")
                {
                    parkingLot.getFreeCount(VehicleType::TRUCK);
                }
                else if (vehicleType == "CAR")
                {
                    parkingLot.getFreeCount(VehicleType::CAR);
                }
                else
                {
                    cout << "Invalid vehicle type" << endl;
                }
            }
            else if (commandTwo == "free_slots")
            {

                string vehicleType;
                cin >> vehicleType;
                if (vehicleType == "BIKE")
                {
                    parkingLot.getFreeSlots(VehicleType::BIKE);
                }
                else if (vehicleType == "TRUCK")
                {
                    parkingLot.getFreeSlots(VehicleType::TRUCK);
                }
                else if (vehicleType == "CAR")
                {
                    parkingLot.getFreeSlots(VehicleType::CAR);
                }
                else
                {
                    cout << "Invalid vehicle type" << endl;
                }
            }
            else if (commandTwo == "occupied_slots")
            {
                string vehicleType;
                cin >> vehicleType;
                if (vehicleType == "BIKE")
                {
                    parkingLot.getOccupiedSlots(VehicleType::BIKE);
                }
                else if (vehicleType == "TRUCK")
                {
                    parkingLot.getOccupiedSlots(VehicleType::TRUCK);
                }
                else if (vehicleType == "CAR")
                {
                    parkingLot.getOccupiedSlots(VehicleType::CAR);
                }
                else
                {
                    cout << "Invalid vehicle type" << endl;
                }
            }
        }
        else if (commandOne == "park_vehicle")
        {
            string vehicleType;
            string registrationNumber;
            string color;
            cin >> vehicleType >> registrationNumber >> color;
            if (vehicleType == "BIKE")
            {
                Vehicle vehicle(VehicleType::BIKE, registrationNumber, color);
                parkingLot.bookSlot(vehicle);
            }
            else if (vehicleType == "TRUCK")
            {
                Vehicle vehicle(VehicleType::TRUCK, registrationNumber, color);
                parkingLot.bookSlot(vehicle);
            }
            else if (vehicleType == "CAR")
            {
                Vehicle vehicle(VehicleType::CAR, registrationNumber, color);
                parkingLot.bookSlot(vehicle);
            }
            else
            {
                cout << "Invalid vehicle type" << endl;
            }
        }
        else if (commandOne == "unpark_vehicle")
        {
            string ticket;
            cin >> ticket;
            parkingLot.unpark(ticket);
        }
        else if (commandOne == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
    return 0;
}