#include <stdio.h>

#define MAX_ROOMS 100

// Structure to represent a hostel room
typedef struct {
    int room_number;
    int is_allocated;
    int student_id;
} Room;

// Global array to store hostel rooms
Room hostel[MAX_ROOMS];

// Function to add hostel rooms
void add_hostel_rooms(int num_rooms) {
    // Initialize hostel rooms
    for (int i = 0; i < num_rooms; i++) {
        hostel[i].room_number = i + 1;
        hostel[i].is_allocated = 0;
        hostel[i].student_id = -1;
    }
    printf("%d hostel rooms added successfully.\n", num_rooms);
}

// Function to allow a student to book a hostel room
void book_room(int room_number, int student_id) {
    if (room_number <= 0 || room_number > MAX_ROOMS) {
        printf("Invalid room number.\n");
        return;
    }
    if (hostel[room_number - 1].is_allocated) {
        printf("Room %d is already allocated.\n", room_number);
}

// Function to allocate a room
void allocate_room(int room_number, int student_id) {
    
}

// Function to clear hostel
void clear_hostel() {
    
}

// Function to output report
void output_report() {
    //
}

void login() {
    char userid[50];
    printf("    |=====================================|\n");
    printf("    |           ADMINISTRATOR             |\n");
    printf("    |=====================================|\n");
    printf("    |                                     |\n");
    printf("    |       Authentication Required       |\n");
    printf("    |Please provide userID: 41851765");
    //admin should provide username
    scanf("%s", userid);
    //check if userid is of right size.
    if (userid < 100000000 && userid > 99999) {
        printf("      |\n");
    } else {
        printf("    userID should strictly be a number of 6-8 digits");
        login();
    }

    //admin should provide password
    scanf("%s", password)
    //clearing line
    printf("\r                            \r");
    printf("    |Please provide password: ********    |\n");
    printf("    |                                     |\n");
    printf("    |Verifying Credentials Hold on...     |\n");
    printf("    |Credentials verified Successfully.   |\n");
    printf("    |=====================================|\n");
    return 0;
}

login();

void log_out() {
    //
}

