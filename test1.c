#include <stdio.h>
#include <string.h>

// Function prototypes
int adminmenu();
int studentmenu();
int add_hostel();
int view_hostel_room();
int add_hostel_room();
int login();

int main() {
    login();
    return 0;
}

int add_hostel() {
    char newhostel[100];
    FILE *hostels;
    hostels = fopen("hostelsandrooms/hostels.txt", "r+"); // Open hostels file

    if (hostels == NULL) {
        printf("Error opening hostels file!\n");
        return 1;
    }
    printf("    |=====================================|\n");
    printf("    |           ADMINISTRATOR             |\n");
    printf("    |=====================================|\n");
    printf("    | Enter the name of new hostel : ");
    scanf("%s", newhostel);
    // Checking if hostel exists already
    char fileline[1000]; // Adjust buffer size as needed
    char buffer; // No need for an array, just a single char
    int z = 0;
    while ((buffer = fgetc(hostels)) != EOF) {
        if (buffer != '\n') {
            fileline[z++] = buffer;
        } else {
            fileline[z] = '\0'; // Null-terminate the string
            if (strcmp(fileline, newhostel) != 0) {
                /*char data[1000];
                sprintf(data, "%s \n", fileline);
                // Write data to the file
                fputs(data, hostels);*/
                break;
            } else {
                printf("Hostel already exists try another name");
                printf("    | Enter the name of new hostel : ");
                scanf("%s", newhostel);
            }
            z = 0; // Reset index for the next line
        }
    }
    fclose(hostels);

    FILE *new_hostel_file;

    // Construct file path for hostel files
    char file_path[1000];
    sprintf(file_path, "hostelsandrooms/%s.txt", newhostel);

    // Open the file in read and write mode ("r+")
    new_hostel_file = fopen(file_path, "r+");

    // Check if the file was opened successfully
    if (new_hostel_file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write to the file # to avoid living it empty
    fprintf(new_hostel_file, "#\n");

    // Close the file
    fclose(new_hostel_file);
    while (1) {
        printf("    |      hostel added succesfully       |\n");
        printf("    |  do you want to add another hostel? |\n");
        printf("    |  [1] Yes                            |\n");
        printf("    |  [2] No                             |\n");
        printf("    |  [3] Add room to new hostel         |\n");
        printf("    |  Select option :");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            add_hostel();
            break;
        } else if (choice == 2) {
            adminmenu();
            break;
        } else if (choice == 3) {
            //add_room();
            break;
        } else {
            printf("    |      Invalid input try again    |\n");
            continue;
        }
    }
    return 0;
}

int view_hostel_room() {
    printf("    |=====================================|\n");
    printf("    |           ADMINISTRATOR             |\n");
    printf("    |=====================================|\n");
    printf("    | hostels |       rooms               |\n");
    printf("    |=====================================|\n");

    FILE *hostels;
    hostels = fopen("hostelsandrooms/hostels.txt", "r"); // Open hostels file

    if (hostels == NULL) {
        printf("Error opening hostels file!\n");
        return 1;
    }

    char line[1000]; // Adjust buffer size as needed
    char buffer; // No need for an array, just a single char
    int i = 0;

    while ((buffer = fgetc(hostels)) != EOF) {
        if (buffer != '\n') {
            //printf("pass1\n");
            line[i++] = buffer;
            //printf("pass1.0\n");
        } else {
            //printf("pass2");
            line[i] = '\0'; // Null-terminate the string
            printf("    | Hostel: %s\n", line); // Output the hostel name

            // Construct file path for rooms file
            char file_path[1000];
            sprintf(file_path, "hostelsandrooms/%s.txt", line);

            // Open rooms file
            FILE *rooms;
            rooms = fopen(file_path, "r");
            if (rooms == NULL) {
                printf("Error opening rooms file for %s\n", line);
                return 1;
            }

            // Read and output rooms data
            char roomline[1000]; // Adjust buffer size as needed
            char roombuffer; // No need for an array, just a single char
            int z = 0;
            while ((roombuffer = fgetc(rooms)) != EOF) {
                if (roombuffer != '\n') {
                    roomline[z++] = roombuffer;
                } else {
                    roomline[z] = '\0'; // Null-terminate the string
                    printf("    |     Room: %s\n", roomline); // Output the room data
                    z = 0; // Reset index for the next line
                }
            }

            fclose(rooms); // Close rooms file

            i = 0; // Reset index for the next line
        }
    }

    fclose(hostels); // Close hostels file

    return 0;
}

int add_hostel_room() {
    //printf("inside add_hostel_room");

    int choice;
    printf("    |=====================================|\n");
    printf("    |           ADMINISTRATOR             |\n");
    printf("    |=====================================|\n");
    printf("    | Please select an option:            |\n");
    printf("    | [1]View Available Hostel and Rooms  |\n");
    printf("    | [2]Add Hostel                       |\n");
    printf("    | [3]Add room                         |\n");
    printf("    | [0]Menu                             |\n");
    printf("    | Type choice: ");

    scanf("%d", &choice);
    if (choice == 1) {
        view_hostel_room();
    } else if (choice == 2) {
        add_hostel();
    } else if (choice == 3) {
        //add_room();
    } else if (choice == 0) {
        adminmenu();
    } else {
        return 0;
    }
    return 0;
}

int login() {
    char userid[50];
    char password[50];

    printf("    |=====================================|\n");
    printf("    |           ADMINISTRATOR             |\n");
    printf("    |=====================================|\n");
    printf("    |                                     |\n");
    printf("    |       Authentication Required       |\n");
    printf("     Please provide userID: ");
    //admin should provide username
    scanf("%s", userid);

    // Check if userid is of the right size.
    int userid_length = 0;
    for (userid_length = 0; userid_length < 50; userid_length++) {
        if (userid[userid_length] == '\0') {
            break;
        }
    }
    if (userid_length < 6 || userid_length > 8) {
        printf("    |UserID should strictly be a number of 6-8 digits|\n");
        login();
        return 1; // Exit the function after recursive call
    }

    // Admin should provide password
    printf("     Please provide password: ");
    scanf("%s", password);

    // Clearing line
    printf("\r                                            \r");
    printf("    |                                     |\n");
    printf("    |Verifying Credentials Hold on...     |\n");

    FILE *adminsfile;
    FILE *studentsfile;
    adminsfile = fopen("credentials/administrators.txt", "r"); // Open file for reading
    studentsfile = fopen("credentials/students.txt", "r"); //Open file

    printf("Files are read\n");

    char buffer[10];
    //combining userID with password
    strcat(userid, password); // Concatenate str2 to str1
    //char combined_userid_password[50] = userid;
    printf("about to enter while loop\n");

    while (fgets(buffer, 40, adminsfile) != NULL) {
        printf("Inside while loop\n");
        printf("%s \n", buffer); // Print the line to the console

        if (strcmp(userid, buffer) != 0) {
            printf("    |Verification Failed, access denied   |\n");
            printf("    |=====================================|\n");
        } else {
            printf("    |Credentials verified Successfully.   |\n");
            printf("    |Administrative, access granted       |\n");
            printf("    |=====================================|\n");
            fclose(adminsfile);
            adminmenu();
            return 0;
        }
    }

    while (fgets(buffer, 40, studentsfile) != NULL) {
        printf("%s", buffer); // Print the line to the console

        if (strcmp(userid, buffer) != 0) {
            printf("    |Verification Failed, access denied   |\n");
            printf("    |=====================================|\n");
        } else {
            printf("    |Credentials verified Successfully.   |\n");
            printf("    |Student, access granted              |\n");
            printf("    |=====================================|\n");
            fclose(studentsfile);
            studentmenu();
            return 0;
        }
    }
    login();
    return 1;
}

int adminmenu() {
    int choice;
    printf("    |=====================================|\n");
    printf("    |           ADMINISTRATOR             |\n");
    printf("    |=====================================|\n");
    printf("    | Please select an option:            |\n");
    printf("    | [1]Add Hostel and Rooms             |\n");
    printf("    | [2]Allocate room                    |\n");
    printf("    | [3]Clear Student                    |\n");
    printf("    | [4]Reports                          |\n");
    printf("    | [0]Log out                          |\n");
    printf("    | Type choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        //printf("about to enter 1");
        add_hostel_room();
    } else if (choice == 2) {
        //allocate_room();
    } else if (choice == 3) {
        //clear_hostel();
    } else if (choice == 4) {
        //reports();
    } else if (choice == 0) {
        login();
    } else {
        return 0;
    }
    return 0;
}

int studentmenu() {
    int choice;
    printf("    |=====================================|\n");
    printf("    |               STUDENT               |\n");
    printf("    |=====================================|\n");
    printf("    | Please select an option:            |\n");
    printf("    | [1]Book Hostel                      |\n");
    printf("    | [0]Log out                          |\n");
    printf("    | Type choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        //book_hostel();
    } else if (choice == 0) {
        login();
    }
    return 0;
}

    char fileline[1000]; // Adjust buffer size as needed
    char buffer; // No need for an array, just a single char
    int z = 0;
    while ((buffer = fgetc(hostels)) != EOF) {
        if (buffer != '\n') {
            fileline[z++] = buffer;
        } else {
            fileline[z] = '\0'; // Null-terminate the string
            if (strcmp(fileline, newhostel) == 0) {
                printf("Hostel already exists try another name");
                printf("    | Enter the name of new hostel : ");
                scanf("%s", newhostel);
            } else {
                continue;
            }
            z = 0; // Reset index for the next line
        }
    }