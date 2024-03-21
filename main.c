#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STUDENTS 1
#define MAX_ROOMS 10
// Student
struct Student {
    char name[50];
    int age;
    char gender;
};

struct Room {
    int roomNumber;
    bool booked;
    struct Student students[MAX_STUDENTS];
};

struct Hostel {
    char name[50];
    int numberOfRooms;
    struct Room rooms[MAX_ROOMS];
};

// Function to add a room to the hostel
void addRoom(struct Hostel *hostel, int roomNumber) {
    if (hostel->numberOfRooms < MAX_ROOMS) {
        struct Room newRoom = {roomNumber, false};
        hostel->rooms[hostel->numberOfRooms++] = newRoom;
        printf("Room %d has been added to the hoste", roomNumber);
    } else {
        printf("Cannot add more rooms. Maximum capacity reached");
    }
}

// Function to assign a room to a student 
void assignRoom(struct Hostel *hostel, int roomNumber, struct Student student) {
    for (int i = 0; i < hostel->numberOfRooms; i++) {
        if (hostel->rooms[i].roomNumber == roomNumber) {
            if (!hostel->rooms[i].booked) {
                hostel->rooms[i].booked = true;
                hostel->rooms[i].students[0] = student;
                printf("Room %d has been booked for %s", roomNumber, student.name);
                return;
            } else {
                printf("Room %d is already booked", roomNumber);
                return;
            }
        }
    }
    printf("Room %d does not exist in the hostel", roomNumber);
}

// Function to print available rooms
void printAvailableRooms(struct Hostel hostel) {
    printf("Available Rooms:\n");
    for (int i = 0; i < hostel.numberOfRooms; i++) {
        if (!hostel.rooms[i].booked) {
            printf("Room %d\n", hostel.rooms[i].roomNumber);
        }
    }
}

// Function to print booked roomsand students whove booked

void printBookedRooms(struct Hostel hostel) {
    printf("Booked Rooms:\n");
    for (int i = 0; i < hostel.numberOfRooms; i++) {
        if (hostel.rooms[i].booked) {
            printf("Room %d - Student(s): ", hostel.rooms[i].roomNumber);
            for (int j = 0; j < MAX_STUDENTS; j++) {
                if (strlen(hostel.rooms[i].students[j].name) > 0) {
                    printf("%s ", hostel.rooms[i].students[j].name);
                }
            }
            printf("\n");
        }
    }
}

int main() {
    struct Hostel myHostel;
    strcpy(myHostel.name, "My Hostel");
    myHostel.numberOfRooms = 0;

    // Adding rooms
    addRoom(&myHostel, 101);
    addRoom(&myHostel, 102);
    addRoom(&myHostel, 103);

    // Assigning rooms to students
    struct Student student1 = {"Alice", 20, 'F'};
    struct Student student2 = {"Bob", 21, 'M'};
    struct Student student3 = {"Charlie", 19, 'M'};

    assignRoom(&myHostel, 101, student1);
    assignRoom(&myHostel, 102, student2);
    assignRoom(&myHostel, 103, student3);

    // Printing available and booked rooms
    printAvailableRooms(myHostel);
    printBookedRooms(myHostel);

    return 0;
}

