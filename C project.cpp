#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student details
struct Student {
    char name[50];
    char email[50];
    char roll[20];
    char college[50];
    char phone[15];
    char address[100];
};

// Function to add a student
void addStudent() {
    FILE *fp = fopen("students.dat", "ab"); // binary append mode
    struct Student s;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Email: ");
    scanf(" %[^\n]", s.email);

    printf("Enter Roll Number: ");
    scanf(" %[^\n]", s.roll);

    printf("Enter College Name: ");
    scanf(" %[^\n]", s.college);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", s.phone);

    printf("Enter Address: ");
    scanf(" %[^\n]", s.address);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\n? Student added successfully!\n");
}

// Function to display all students
void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n=========== STUDENT RECORDS ===========\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nName     : %s", s.name);
        printf("\nEmail    : %s", s.email);
        printf("\nRoll No  : %s", s.roll);
        printf("\nCollege  : %s", s.college);
        printf("\nPhone    : %s", s.phone);
        printf("\nAddress  : %s\n", s.address);
        printf("--------------------------------------\n");
    }

    fclose(fp);
}

// Function to search student
void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    char roll[20];
    int found = 0;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf(" %[^\n]", roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (strcmp(s.roll, roll) == 0) {
            printf("\n? Student Found!\n");
            printf("Name: %s\nEmail: %s\nCollege: %s\nPhone: %s\nAddress: %s\n",
                   s.name, s.email, s.college, s.phone, s.address);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\n? Student not found!\n");

    fclose(fp);
}

// Function to delete student
void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    struct Student s;
    char roll[20];
    int found = 0;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to delete: ");
    scanf(" %[^\n]", roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (strcmp(s.roll, roll) != 0) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\n? Student deleted successfully!\n");
    else
        printf("\n? Student not found!\n");
}

// Function to update student details
void updateStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    struct Student s;
    char roll[20];
    int found = 0;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to update: ");
    scanf(" %[^\n]", roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (strcmp(s.roll, roll) == 0) {
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Email: ");
            scanf(" %[^\n]", s.email);

            printf("Enter New College: ");
            scanf(" %[^\n]", s.college);

            printf("Enter New Phone: ");
            scanf(" %[^\n]", s.phone);

            printf("Enter New Address: ");
            scanf(" %[^\n]", s.address);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("\n? Student updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\n? Student not found!\n");

    fclose(fp);
}

// Function to count total students
void countStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int count = 0;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        count++;
    }

    printf("\n?? Total Students: %d\n", count);

    fclose(fp);
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n====================================\n");
        printf("   STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Count Students\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: countStudents(); break;
            case 7: exit(0);
            default: printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
