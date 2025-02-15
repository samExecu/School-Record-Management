// Project Title:- School's Record Management
/*
Data File : SCHOOL.DAT
Menu
1. Add Records (Name, Class and Roll number of students)
2. View Records (All the records)
3. Search Records (Ask Name to search and display)
4. Delete Records (by Roll Number)
5. Update Records (if class is 10 then update as 11)
*/

//!The max size for writing student information are 50
//! system("cls") is being used to clear the previous screen
//! system("color 4") & ("color 0") are used to change color of text inside terminal

#include <stdio.h>    // Standard Input/Output functions
#include <conio.h>    // Console Input/Output functions (includes _getch())
#include <stdlib.h>   // Standard Library functions (e.g., system())
#include <string.h>   // String manipulation functions (e.g., strcpy(), strcmp())
#include <ctype.h>    // Character handling functions (e.g., toupper())

void main(); // Prototype of the main() function to prevent errors when calling it from other functions

struct school { // Definition of a structure for better data storage and access
   char name[50];
   int class;
   int rollNo;
};

// _getch() function is used to receive an input from the user without displaying the output

// This function is called when there is an error in menu selection
void errorOption() {
   char temp;
   system("cls"); // Clearing the screen
   system("color 4"); // Changing the font color in the terminal to red
   printf("Error!\n");
   printf("Invalid Option! Please re-enter the correct option.\n");
   printf("Press Any Key to Continue...\n");
   _getch(); // Waiting for user input to continue
   system("cls"); // Clearing the screen
   system("color 0"); // Changing the font color back to default
   main(); // Returning to the main menu
}

//Function to add student records
void addRecords() {
   system("cls"); // Clearing previous menu screen

   FILE *fptr;
   fptr = fopen("Student.dat", "a"); // Open for append

   if (fptr == NULL) { // Handling file opening error
      system("cls");
      printf("Error Opening File!!\n");
      printf("Returning to selection screen\n");
      printf("Press Any Key to Continue...\n");
      _getch();
      system("cls");
      main();
   }

   struct school student[50]; // Max amount of data input per launch

   int index = 0;
   char ch;
   do {
      printf("No.%i Input : \n", index + 1);
      printf("Enter Student Name : ");
      scanf(" %[^\n]s", &student[index].name);
      printf("Enter Class : ");
      scanf("%i", &student[index].class);
      printf("Enter Roll No : ");
      scanf("%i", &student[index].rollNo);

      printf("\nDo you want to enter another record?\n");
      printf("If yes press [Y] else [N] : ");
      scanf(" %c", &ch);
      printf("\n");
      index++;
   } while (toupper(ch) == 'Y');

   system("cls"); // Clearing all the details entered by the user only on screen

   int idx;
   for (idx = 0; idx < index; idx++) { // Writing the details entered by the user into the file "Student.dat"
      fprintf(fptr, "Student Name : %s\n", student[idx].name);
      fprintf(fptr, "Class : %i\n", student[idx].class);
      fprintf(fptr, "Roll No : %i\n", student[idx].rollNo);
   }

   printf("Task Successful!!\n");
   printf("The details have been entered into the file!\n");
   printf("Press any key to continue...");
   _getch();
   system("cls");

   fclose(fptr); // Closing the file "Student.dat"

printf("Exit [E] / Menu [M]: ");
   scanf(" %c", &ch);
   if (toupper(ch) == 'E') {
      system("cls"); // Clearing screen before exiting the program
      exit(0);
   } else if (toupper(ch) == 'M') {
      system("cls"); // Clearing screen before going back to main menu
      main();
   } else {
      system("cls"); // Clearing screen before exiting the program
      printf("Invalid Option!!\n");
      printf("Exiting the program!!");
      exit(0);
   }

   system("cls"); // Clearing the screen and exiting the function
   exit(0);
}

//Function to view student records
void viewRecords() {
   system("cls"); // Clearing previous menu screen

   FILE *fptr;
   fptr = fopen("Student.dat", "r"); // Open for read

   if (fptr == NULL) { // Handling file opening error
      system("cls");
      system("color 4"); // Changes font color to red
      printf("Error Opening File!!\n");
      printf("Returning to selection screen\n");
      printf("Press Any Key to Continue...\n");
      _getch();
      system("cls");
      system("color 0"); // Resets font color to default
      main();
   }

   char temp;
   if (fscanf(fptr, "%c", &temp) == EOF) { // Checking if file is empty
      system("color 4");
      printf("The file is empty.\n");
      printf("Press any key to continue...");
      _getch();
      system("cls");
      system("color 0");
      fclose(fptr);
      main();
   } else {
      fseek(fptr, 0, SEEK_SET); // Setting cursor position to beginning of file
      struct school student[50];
      int idx = 0;

      // Reading info from file and writing into structure
      while (fscanf(fptr, "Student Name : %[^\n]\nClass : %d\nRoll No : %d\n",
            &student[idx].name, &student[idx].class, &student[idx].rollNo) == 3 && idx < 50) {
         idx++;
      }

      fclose(fptr); // Closing the file
    /*
    %5d ensures that the first column "Class" is left-aligned within a width of 5 characters.
    %9d ensures that the second column "Roll No." is left-aligned within a width of 9 characters.
    %12s ensures that the third column "Name" is left-aligned within a width of 12 characters.
    */
    printf("+------+----------+--------------------+\n");
    printf("| Class| Roll No. |        Name        |\n");
    printf("+------+----------+--------------------+\n");
    int index;
    for (index = 0; index < idx; index++) {
        printf("| %-5d| %-9d| %-19s|\n", student[index].class, student[index].rollNo, student[index].name);
    }
    printf("+------+----------+--------------------+\n");

   }

   printf("All records have been displayed.\n");
   printf("Press Any Key to Continue...\n");
   _getch();
   system("cls");

   char ch;
  printf("Exit [E] / Menu [M]: ");
   scanf(" %c", &ch);
   if (toupper(ch) == 'E') {
      system("cls");
      exit(0);
   } else if (toupper(ch) == 'M') {
      system("cls");
      main();
   } else {
      system("cls");
      printf("Invalid Option!!\n");
      printf("Exiting the program!!");
      exit(0);
   }
   system("cls");
   exit(0);
}

// Function to search student records
void searchRecords() {
   system("cls"); // Clearing previous menu screen

   FILE *fptr;
   fptr = fopen("Student.dat", "r+"); // Open for read & write mode
   struct school student[50];

   if (fptr == NULL) { // Handling file opening error
      system("cls");
      system("color 4"); // Changes font color to red
      printf("Error Opening File!!\n");
      printf("Returning to selection screen\n");
      printf("Press Any Key to Continue...\n");
      _getch();
      system("cls");
      system("color 0"); // Resets font color to default
      fclose(fptr);
      main();
   }

   char search[100];
   int found = 0;

   printf("Enter the name of the student that you want to search: ");
   scanf(" %[^\n]s", &search);
   printf("Records Found\n");
   printf("Class\t\tRoll No.\tName\n");
   int i;
   for (i = 0; i < 50; i++) {
      fscanf(fptr, "Student Name : %[^\n]\nClass : %d\nRoll No : %d\n", &student[i].name, &student[i].class, &student[i].rollNo);

      if (strcmpi(student[i].name, search) == 0) {
         printf("%d\t\t%d\t\t%s\n", student[i].class, student[i].rollNo, student[i].name);
         found = 1;
      }
   }

   if (found == 0) { // Handling no records found
      system("cls");
      system("color 4");
      printf("Record not found!\n");
      printf("Press any key to continue...");
      _getch();
      system("color 0");
      system("cls");
   }

   fclose(fptr);

   char ch;
   printf("\n");
   printf("Exit [E] / Menu [M]: ");
   scanf(" %c", &ch);
   if (toupper(ch) == 'E') {
      system("cls");
      exit(0);
   } else if (toupper(ch) == 'M') {
      system("cls");
      main();
   } else {
      system("cls");
      printf("Invalid Option!!\n");
      printf("Exiting the program!!");
      exit(0);
   }
}

// Function to update student records
void updateRecords() {
   system("cls"); // Clearing previous menu screen

   // Declaring file pointer
   FILE *fptr;
   int idx, i;
   char ch, temp;
   struct school student[50];

   // Opening file for reading
   fptr = fopen("Student.dat", "r");

   // Handling file opening errors
   if (fptr == NULL) {
      system("cls");
      system("color 4"); // Changing font color to red
      printf("Error Opening File!!\n");
      printf("Returning to selection screen\n");
      printf("Press Any Key to Continue...\n");
      _getch();
      system("cls");
      system("color 0"); // Restoring font color to default
      fclose(fptr);
      main();
   }

   // Checking if file is empty
   if (fscanf(fptr, "%c", &temp) == EOF) {
      system("color 4"); // Changing font color to red
      printf("The file is empty.\n");
      printf("Press any key to continue...");
      _getch();
      system("cls");
      system("color 0"); // Restoring font color to default
      fclose(fptr);
      main();
   } else {
      // Setting cursor position to the beginning of the file
      fseek(fptr, 0, SEEK_SET);

      idx = 0;
      // Reading info from the file and storing in the structure
      while (fscanf(fptr, "Student Name : %[^\n]\nClass : %d\nRoll No : %d\n",
            &student[idx].name, &student[idx].class, &student[idx].rollNo) == 3 && idx < 50) {
         idx++;
      }

      fclose(fptr); // Closing the file
   }

   int counter = 0;
   // Updating student records
   for (i = 0; i < idx; i++) {
      if (student[i].class == 10) {
         student[i].class = 11;
         counter++;
      }
   }

   // Overwriting records
   fptr = fopen("Student.dat", "w");
   if (fptr == NULL) {
      system("cls");
      printf("Error Opening File!!\n");
      printf("Returning to selection screen\n");
      printf("Press Any Key to Continue...\n");
      _getch();
      system("cls");
      main();
   }

   // Writing updated details to file
   for (i = 0; i < idx; i++) {
      fprintf(fptr, "Student Name : %s\n", student[i].name);
      fprintf(fptr, "Class : %i\n", student[i].class);
      fprintf(fptr, "Roll No : %i\n", student[i].rollNo);
   }

   // Displaying update status
   if (counter > 0) {
      printf("Record Updated Successfully\n");
   } else {
      printf("No Class 10 Student Found\n");
   }

   printf("Press any key to continue...");
   _getch();
   system("cls");

   fclose(fptr); // Closing the file

   // Prompting user to exit or go back to menu
   printf("Exit [E] / Menu [M]: ");
   scanf(" %c", &ch);
   if (toupper(ch) == 'E') {
      system("cls");
      exit(0);
   } else if (toupper(ch) == 'M') {
      system("cls");
      main();
   } else {
      system("cls");
      printf("Invalid Option!!\n");
      printf("Exiting the program!!");
      exit(0);
   }

   system("cls");
   exit(0);
}

// Function to delete student records
void deleteRecords() {
   system("cls"); // Clearing previous menu screen

   // Declaring file pointer and variables
   FILE *fptr;
   int idx, i, tempRoll, tempClass;
   char ch, temp;
   struct school student[50];
   struct school tempS;

   // Opening file for reading
   fptr = fopen("Student.dat", "r");

   // Handling file opening errors
   if (fptr == NULL) {
      system("cls");
      system("color 4"); // Changing font color to red
      printf("Error Opening File!!\n");
      printf("Returning to selection screen\n");
      printf("Press Any Key to Continue...\n");
      _getch();
      system("cls");
      system("color 0"); // Restoring font color to default
      fclose(fptr);
      main();
   }

   // Checking if file is empty
   if (fscanf(fptr, "%c", &temp) == EOF) {
      system("color 4"); // Changing font color to red
      printf("The file is empty.\n");
      printf("Press any key to continue...");
      _getch();
      system("cls");
      system("color 0"); // Restoring font color to default
      fclose(fptr);
      main();
   } else {
      // Setting cursor position to the beginning of the file
      fseek(fptr, 0, SEEK_SET);

      idx = 0;
      // Reading info from the file and storing in the structure
      while (fscanf(fptr, "Student Name : %[^\n]\nClass : %d\nRoll No : %d\n",
            &student[idx].name, &student[idx].class, &student[idx].rollNo) == 3 && idx < 50) {
         idx++;
      }

      fclose(fptr); // Closing the file
   }

   // Requesting roll no and class for deletion
   system("cls");
   printf("Delete Record:\n");
   printf("Enter Roll No : ");
   scanf("%i", &tempRoll);
   printf("Enter Class : ");
   scanf("%i", &tempClass);
   int x;
   FILE *delRecords;
   delRecords = fopen("Recycle Bin.dat", "a");
   for (i = 0; i < idx; i++) {
      if (student[i].class == tempClass && student[i].rollNo == tempRoll) {
         // Writing deleted records to recycle bin
         fprintf(delRecords, "Student Name : %s\n", student[i].name);
         fprintf(delRecords, "Class : %i\n", student[i].class);
         fprintf(delRecords, "Roll No : %i\n", student[i].rollNo);
         for (x = i; x < idx; x++) {
            student[x] = student[x + 1];
         }
         // Decrement index to reflect the removal
      idx--;

      // Decrement i to stay at the same index in the next iteration
      i--;
      }
   }
   fclose(delRecords);

   // Overwriting records
   fptr = fopen("Student.dat", "w");
   if (fptr == NULL) {
      system("cls");
      printf("Error Opening File!!\n");
      printf("Returning to selection screen\n");
      printf("Press Any Key to Continue...\n");
      _getch();
      system("cls");
      main();
   }

   // Writing updated details to file
   for (i = 0; i < idx; i++) {
      fprintf(fptr, "Student Name : %s\n", student[i].name);
      fprintf(fptr, "Class : %i\n", student[i].class);
      fprintf(fptr, "Roll No : %i\n", student[i].rollNo);
   }

   // Displaying deletion status
   printf("Successfully Deleted.\n");
   printf("Press Any Key to Continue...\n");
   _getch();
   system("cls");

   fclose(fptr); // Closing the file

   // Prompting user to exit or go back to menu
   printf("Exit [E] / Menu [M]: ");
   scanf(" %c", &ch);
   if (toupper(ch) == 'E') {
      system("cls"); // Clearing screen before exiting the program
      exit(0);
   } else if (toupper(ch) == 'M') {
      system("cls"); // Clearing screen before going back to main
      main();
   } else {
      system("cls"); // Clearing screen before exiting the program
      printf("Invalid Option!!\n");
      printf("Exiting the program!!");
      exit(0);
   }
   system("cls");
   exit(0);
}

// Function to view records in the recycle bin
void viewRecycleBin() {
   system("cls"); // Clearing previous menu screen

   // Declaring a file pointer
   FILE * fptr;

   // Opening recycle bin file for reading
   fptr = fopen("Recycle Bin.dat", "r");

   // Handling file opening errors
   if (fptr == NULL) {
      system("cls");
      system("color 4"); // Changing font color to red
      printf("Error Opening File!!\n");
      printf("Returning to selection screen\n");
      printf("Press Any Key to Continue...\n");
      _getch(); // Waiting for user input
      system("cls");
      system("color 0"); // Restoring font color to default
      fclose(fptr);
      main();
   }

   char temp;
   // Checking if file is empty
   if (fscanf(fptr, "%c", &temp) == EOF) {
      system("color 4"); // Changing font color to red
      printf("The file is empty.\n");
      printf("Press any key to continue...");
      _getch(); // Waiting for user input
      system("cls");
      system("color 0"); // Restoring font color to default
      fclose(fptr);
      main();
   } else {
      // Setting cursor position to the beginning of the file
      fseek(fptr, 0, SEEK_SET);
      struct school student[50];

      int idx = 0;
      // Reading info from the file and storing in the structure
      while (fscanf(fptr, "Student Name : %[^\n]\nClass : %d\nRoll No : %d\n",
            &student[idx].name, &student[idx].class, &student[idx].rollNo) == 3 && idx < 50) {
         idx++;
      }

      fclose(fptr); // Closing the file
      int index;
      // Displaying records from the recycle bin
        printf("+------+----------+-------------+\n");
        printf("| Class| Roll No. |    Name     |\n");
        printf("+------+----------+-------------+\n");
          for (index= 0; index < idx; index++) {
        printf("| %-5d| %-9d| %-12s|\n", student[index].class, student[index].rollNo, student[index].name);
          }
        printf("+------+----------+-------------+\n");

   }

   printf("All records have been displayed.\n");
   printf("Press Any Key to Continue...\n");
   _getch(); // Waiting for user input
   system("cls"); // Clearing the screen

   char ch;
   // Prompting user to exit or go back to menu
  printf("Exit [E] / Menu [M]: ");
   scanf(" %c", &ch);
   if (toupper(ch) == 'E') {
      system("cls"); // Clearing screen before exiting the program
      exit(0);
   } else if (toupper(ch) == 'M') {
      system("cls"); // Clearing screen before going back to main
      main();
   } else {
      system("cls"); // Clearing screen before exiting the program
      printf("Invalid Option!!\n");
      printf("Exiting the program!!");
      exit(0);
   }
   system("cls");
   exit(0);
}

// Main function which handles the task selection
void main() {
   int selection; // Stores the option selected by the user

printf("\n");
printf(" ***************************\n");
printf(" *          Menu           *\n");
printf(" ***************************\n");
printf(" * 1. Add Records          *\n"); // Option to add Name, Class, and Roll No. of Student
printf(" * 2. View Records         *\n"); // Option to view all the records
printf(" * 3. Search Records       *\n"); // Option to search and display records by name
printf(" * 4. Delete Records       *\n"); // Option to delete records by Roll No
printf(" * 5. Update Records       *\n"); // Option to update records, changing class from 10 to 11
printf(" *                         *\n");
printf(" *                         *\n");
printf(" * 9. View Recycle Bin     *\n");
printf(" * 0. Exit                 *\n");
printf(" ***************************\n");
printf("\n");

printf("Select an option (1/2/3/4/5/9/0): "); // Getting input from user to perform selected task

scanf("%i", &selection);

   // Calling functions according to the user selection
   switch (selection) {
      case 1: // Option 1: Add Records
         addRecords(); // Calls the addRecord function 
         break;
      case 2: // Option 2: View Records
         viewRecords();
         break;
      case 3: // Option 3: Search Records
         searchRecords();
         break;
      case 4: // Option 4: Delete Records
         deleteRecords();
         break;
      case 5: // Option 5: Update Records
         updateRecords();
         break;
      case 9: // Option 9: View Recycle Bin
         viewRecycleBin();
         break;
      case 0: // Option 0: Exit
         exit(1);
         break;
      default: // In case user inputs an invalid option
         errorOption();
         break;
   }
}
