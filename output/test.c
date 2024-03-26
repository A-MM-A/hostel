#include <stdio.h>
#include <string.h>

// Function prototypes
int adminmenu();
int studentmenu();
int add_hostel();
int view_hostel_room();
int add_hostel_room();
int login();

/*
The main function is the starting point.
It begins by executing login(). Go to where login() is...
*/
int main() {
    login();
    return 0;
}

int add_room() {
    //enter hostel first before checking its rooms
    char hostel[100];
    printf("    |  Enter name of hostel : ");
    scanf("%s", hostel);
    char file_path[1000];
    sprintf(file_path, "hostelsandrooms/%s.txt", hostel);
    //printf("file path : %s \n",file_path);

    FILE *hostel_file;

    // Open the file in write mode ("r")
    hostel_file = fopen(file_path, "r");

    // Check if the file was opened successfully
    if (hostel_file == NULL) {
        printf("\n");
        printf("    |  hostel not found                   |\n");
        printf("    |  do you want to add the hostel?     |\n");
        printf("    |  [1] Yes                            |\n");
        printf("    |  [2] No, enter hostel again         |\n");
        printf("    |  Enter Choice : ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            add_hostel();
        } else if (choice == 2) {
            add_room();
        } else {
            printf("Invalid input, terminating...");
            return 0;
        }
    }
    // Open the file in write mode ("w")
    hostel_file = fopen(file_path, "a");
    //adding new rooms
    char new_room[100];
    while (1)
    {   
        printf("    |  Enter room name : ");
        scanf("%s", new_room);
        printf("    |  Room %s created \n", new_room);
        strcat(new_room, "\n");
        /*
        write a code that shall check if the room actually exists
        if the room exists the loop should "continue;" i.e name of rooms should be unique
        */
        fputs(new_room, hostel_file);
        printf("    |  do you want to add another room?   |\n");
        printf("    |  [1] Yes                            |\n");
        printf("    |  [2] No,                            |\n");
        printf("    |  Enter option : ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            continue;
        } else if (choice == 2) {
            break;
        } else {
            printf("Invalid input, terminating...");
            break;
            return 0;
        }
    }
    
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

    // Check if the hostel already exists in the file
    char fileline[1000];
    //int hostel_exists = 0; // Flag to track whether the hostel exists
    while (fscanf(hostels, "%s", fileline) != EOF) {
        if (strcmp(fileline, newhostel) == 0) {
            printf("Hostel already exists. Please enter another name: ");
            scanf("%s", newhostel);
            //hostel_exists = 1;
            rewind(hostels); // Reset file pointer to the beginning for re-reading
        }
    }

    // Construct file path for hostel files before adding '\n' to newhostel
    char file_path[1000];
    sprintf(file_path, "hostelsandrooms/%s.txt", newhostel);
    printf("file path : %s",file_path);

    //After reading till the bottom of the file.
    // Append a newline character to fileline
    strcat(newhostel, "\n");

    // Append newhostel to the hostels file
    hostels = fopen("hostelsandrooms/hostels.txt", "a");
    fputs(newhostel, hostels);

    fclose(hostels);

    FILE *new_hostel_file;

    // Open the file in write mode ("w")
    new_hostel_file = fopen(file_path, "w");

    // Check if the file was opened successfully
    if (new_hostel_file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write to the file # to avoid living it empty
    //fprintf(new_hostel_file, "\n");

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

    while (1) {
        int choice;
        printf("    |=====================================|\n");
        printf("    |           ADMINISTRATOR             |\n");
        printf("    |=====================================|\n");
        printf("    | Please select an option:            |\n");
        printf("    | [0]Menu                             |\n");
        printf("    | [1]Add new hostel                   |\n");
        printf("    | Enter option : ");
        scanf("%d", &choice);
        if (choice == 0) {
            adminmenu();
        } else if (choice == 1) {
            add_hostel();
        } else {
            continue;
        }
    }

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
        add_room();
    } else if (choice == 0) {
        adminmenu();
    } else {
        return 0;
    }
    return 0;
}

/*
here the user is asked to provide userID and password.
This function then takes the userID and password and combines them.
It takes the combined... and checks it up in the administrators.txt.
administrators.txt is a file that stores credentials for admins and as you guessed it students.txt for students.
Incase the the credentials provided by the user are found in the administrators.txt the user is given administrative access,
else if they are found in the students.txt the user is given student access.
Administrative access means the ability to access the adminsmenu()
while student access means the ability to access studentmenu()
I know the security on this is quite simple unless we find a way to encrypt the files before storing them using the credentials provided by the user,
but that is not the most important task.
For now let us focus on the following.
One person should deal with allocate_room()
the other clear_hostel()
and reports()
NB : Add Hostel and Rooms I'm on it.
*/
int login() {
    char userid[200];
    char password[200];

    while (1) {
        printf("    |=====================================|\n");
        printf("    |                LOGIN                |\n");
        printf("    |=====================================|\n");
        printf("    |                                     |\n");
        printf("    |       Authentication Required       |\n");
        printf("     Please provide userID: ");
        //user should provide username
        scanf("%s", userid);

        // Check if userid is of the right size.
        //getting length of userid
        int userid_length = 0;
        for (userid_length = 0; userid_length < 50; userid_length++) {
            if (userid[userid_length] == '\0') {
                break;
            }
        }
        //checking if 6 < userid_length < 8
        if (userid_length < 6 || userid_length > 8) {
            printf("    |UserID should strictly be a number of 6-8 digits|\n");
            continue;
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

        char buffer[400];
        char byte_buffer;
        int buffer_index = 0;

        //combining userID with password
        strcat(userid, password); // Concatenate str2 to str
        //char combined_userid_password[50] = userid;
        printf("about to enter while loop\n");

        while ((byte_buffer = fgetc(adminsfile)) != EOF) {
            if (byte_buffer != '\n') {
                // Store character in buffer until newline is encountered
                buffer[buffer_index++] = byte_buffer;
            } else {
                // Null-terminate the buffer
                buffer[buffer_index] = '\0';
                
                // Compare combined user ID and password with buffer
                if (strcmp(userid, buffer) == 0) {
                    printf("    |Credentials verified Successfully.   |\n");
                    printf("    |Administrative, access granted       |\n");
                    printf("    |=====================================|\n");
                    fclose(adminsfile);
                    adminmenu(); // Assuming adminmenu() is defined elsewhere
                    return 0;
                }

                // Reset buffer index for next line
                buffer_index = 0;
            }
        }

        while ((byte_buffer = fgetc(adminsfile)) != EOF) {
            if (byte_buffer != '\n') {
                // Store character in buffer until newline is encountered
                buffer[buffer_index++] = byte_buffer;
            } else {
                // Null-terminate the buffer
                buffer[buffer_index] = '\0';
                
                // Compare combined user ID and password with buffer
                if (strcmp(userid, buffer) == 0) {
                    printf("    |Credentials verified Successfully.   |\n");
                    printf("    |Administrative, access granted       |\n");
                    printf("    |=====================================|\n");
                    fclose(adminsfile);
                    adminmenu(); // Assuming adminmenu() is defined elsewhere
                    return 0;
                }

                // Reset buffer index for next line
                buffer_index = 0;
            }
        }
        while (fgets(buffer, 400, studentsfile) != NULL) {
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

