/*

PS- Design a ride sharing application where drivers can offer rides(origin, destination, no.of seats), any rider can request rides (origin, destination, no. of seats).

There is an algo to calculate Ride amount charged for a given ride based on distance and no. of seats.

1. When the ride closes, show the amount charged to the rider.
2. Ride amount if No. of seats >=2 => no. of kilometers x no. of seats x 0.75*amount charged per km
3. Ride amount if no. of seats =1 => no. of kilometers x amount charged per km

The program should take as input 2 or more drivers and a set of riders requesting rides. Multiple rides can happen simultaneously

Assumptions-
1. Assume amount charged per km = 20
2. No. of km = destination-origin

Test cases-

A requesting for ride R1

Input- A request 50,60,2
Output- Ride amount 10*2*0.75*20=300


Functionalities-
1. Add Driver(name)
2. Add Rider(name)￼

3. Create Ride(id,origin, destination, no. of seats)
4. Create/Update Ride (id, origin, destination, no. of seats)
5. Withdraw(id)
6. Close ride and return amount

*/

#include <iostream>
#include <vector>

using namespace std;

enum RideStatus
{
	IDLE,
	CREATED,
	WITHDRAWN,
	COMPLETED
};

class Ride
{
	int id;
	int origin, dest;
	int seats;

	RideStatus rideStatus;

public:
	static const int AMT_PER_KM = 20;

	Ride(int id = 0, int origin = 0, int dest = 0, int seats = 0, RideStatus rideStatus = RideStatus::IDLE) : id(id), origin(origin), dest(dest), seats(seats), rideStatus(rideStatus){};

	int calculateFare(bool);
	void setId(int id);
	void setDest(int dest);
	int getId() const;
	void setOrigin(int origin);
	RideStatus getRideStatus() const;
	void setRideStatus(RideStatus rideStatus);
	void setSeats(int seats);
};

int Ride::calculateFare(bool isPriviledgedRider)
{
	int distance = dest - origin;
	if (seats < 2)
	{
		return distance * AMT_PER_KM * (isPriviledgedRider ? 0.75 : 0.5);
	}

	return seats * distance * AMT_PER_KM * (isPriviledgedRider ? 0.75 : 0.5);
}

void Ride::setId(int id)
{
	this->id = id;
}

void Ride::setOrigin(int origin)
{
	this->origin = origin;
}

void Ride::setDest(int dest)
{
	this->dest = dest;
}

void Ride::setSeats(int seats) 
{
	this->seats = seats;
}

void Ride::setRideStatus(RideStatus rideStatus)
{
	this->rideStatus = rideStatus;
}

int Ride::getId() const
{
	return id;
}

RideStatus Ride::getRideStatus() const
{
	return rideStatus;
}

// since Rider and Driver class have commor property of "name". We can create a
// Person class and inherit it.

class Person
{

public:
	string name;
	Person(string name):name(name){}
};

class Driver : private Person
{
public:
	Driver(string name) : Person(name){};
};


class Rider : private Person
{
	vector<Ride> completedRides;
	Ride currentRide;

public:
	Rider(string name) : Person(name){};

	void createRide(int, int, int, int);
	void updateRide(int, int, int, int);
	void withdrawRide(int);
	int closeRide();
};

void Rider::createRide(int id, int origin, int dest, int seats)
{

	if (origin >= dest)
	{
		cout << "Wrong values of origin and destination provided. Cant create Ride";
		return;
	}

	currentRide.setId(id);
	currentRide.setOrigin(origin);
	currentRide.setDest(dest);
	currentRide.setSeats(seats);
	currentRide.setRideStatus(RideStatus::CREATED);
}

void Rider::updateRide(int id, int origin, int dest, int seats)
{

	if (currentRide.getRideStatus() == RideStatus::WITHDRAWN)
	{
		cout << "Cant update the ride. Ride was withdrawn" << endl;
		return;
	}
	if (currentRide.getRideStatus() == RideStatus::COMPLETED)
	{
		cout << "Cant update the ride. Ride was withdrawn" << endl;
		return;
	}

	createRide(id, origin, dest, seats);
}

void Rider::withdrawRide(int id)
{
	if (currentRide.getId() != id)
	{
		cout << "Wrong id as input. Cant withdraw ride" << endl;
		return;
	}
	if (currentRide.getRideStatus() != RideStatus::CREATED)
	{
		cout << "Ride not in progress. Cant witdraw" << endl;
		return;
	}

	currentRide.setRideStatus(RideStatus::WITHDRAWN);
}

int Rider::closeRide()
{
	if (currentRide.getRideStatus() != RideStatus::CREATED)
	{
		cout << "Ride was not in progress. Cant close the ride \n";
		return 0;
	}

	currentRide.setRideStatus(RideStatus::COMPLETED);
	completedRides.push_back(currentRide);
	return currentRide.calculateFare(completedRides.size() >= 10);
}

int main()
{
	Rider rider("Lucifer");
	Driver driver("Amanadiel");

	rider.createRide(1, 50, 60, 1);
	cout << rider.closeRide() << endl;
	rider.updateRide(1, 50, 60, 2);
	cout << rider.closeRide() << endl;

	return 0;
}
