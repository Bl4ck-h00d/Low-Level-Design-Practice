#include <bits/stdc++.h>

using namespace std;

class Meeting;
// typedef vector<Meeting> Calendar; //meetings for only 1 day
typedef unordered_map<int, vector<Meeting>> Calendar; // meetings for multiple days

class Room
{
    string name;       // room name;
    Calendar calendar; // scheduled meetings

public:
    Room(string name) : name(name) {}
    string getName() const;
    bool book(int, int, int);
};

string Room::getName() const
{
    return name;
}

//----------------------------------------------------------------------------------------------------

class Meeting
{
    int start;
    int end;
    Room room;

public:
    Meeting(int start, int end, Room &room) : start(start), end(end), room(room) {}

    int getStart() const;
    int getEnd() const;
};

int Meeting::getStart() const
{
    return start;
}

int Meeting::getEnd() const
{
    return end;
}

/**
 * book meeting
 * @param day day of the meeting (int)
 * @param start starting time of the meeting (int)
 * @param end ending time of the meeting (int)
 * @return true if booked else false (bool)
 *
 */
bool Room::book(int day, int start, int end)
{

    for (auto meet : calendar[day])
    {
        // check for clashes
        if (meet.getStart() < end && start < meet.getEnd())
            return false;
    }

    /**
     * Create meeting object
     *
     * @param start starting time of the meeting (int)
     * @param end ending time of the meeting (int)
     * @param room reference to the room
     */
    Meeting meeting(start, end, *this);
    calendar[day].push_back(meeting); // book the meeting

    return true;
}

//----------------------------------------------------------------------------------------------------

class Scheduler
{
    vector<Room> rooms;

public:
    Scheduler(vector<Room> rooms) : rooms(rooms) {}
    string book(int, int, int);
    void addRooms(Room room);
    void getRooms() const;
};

/**
 *
 * Check all the rooms for the given time slot
 *
 * @param day day of the meeting (int)
 * @param start starting time of the meeting (int)
 * @param end ending time of the meeting (int)
 * @return roomName name of the booked room
 */
string Scheduler::book(int day, int start, int end)
{

    // iterate through all the rooms and check for availability
    for (auto &room : rooms)
    {
        bool isRoomAvailable = room.book(day, start, end);

        if (isRoomAvailable)
        {
            return room.getName();
        }
    }

    return "No rooms available";
}

void Scheduler::addRooms(Room room)
{
    rooms.push_back(room);
    cout << room.getName() << " room added" << endl;
    return;
}

void Scheduler::getRooms() const
{
    for (Room room : rooms)
    {
        cout << room.getName() << endl;
    }
}

int main()
{
    // Room room1("Atlas");
    // Room room2("Nexus");
    // Room room3("HolyCow");

    vector<Room> rooms;
    // rooms.push_back(room1);
    // rooms.push_back(room2);
    // rooms.push_back(room3);

    Scheduler scheduler(rooms);

    // cout << scheduler.book(15, 2, 5) << '\n';
    // cout << scheduler.book(15, 5, 8) << '\n';
    // cout << scheduler.book(15, 4, 8) << '\n';
    // cout << scheduler.book(15, 3, 6) << '\n';
    // cout << scheduler.book(15, 7, 8) << '\n';
    // cout << scheduler.book(16, 6, 9) << '\n';

    string commandArg1, commandArg2;

    cout << "********************** Meeting Schedular**********************" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    while (1)
    {
        cin >> commandArg1 >> commandArg2;
        cout << endl;

        if (commandArg1 == "ADD" && commandArg2 == "ROOM")
        {
            string roomName;
            cin >> roomName;
            scheduler.addRooms(Room(roomName));
        }
        else if (commandArg1 == "SHOW" && commandArg2 == "ROOMS")
        {
            scheduler.getRooms();
        }
        else if (commandArg1 == "BOOK" && commandArg2 == "SLOT")
        {
            int day, start, end;
            cin >> day >> start >> end;

            cout << scheduler.book(day, start, end) << '\n';
        }
        else
        {
            cout << "Invalid Commands. Try Again!" << endl;
        }
    }

    cout << "Bye! Have a productive day" << endl;
    

    return 0;
}