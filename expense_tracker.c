#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define USER_FILE "users.txt"
#define KEY 7 

struct Expense 
{
    char date[15];     
    char category[20]; 
    float amount;
};

char currentUser[50]; 

void encryptDecrypt(char *data)
 {
    while (*data) 
    {
        *data = *data ^ KEY;
        data++;
    }
}

void registerUser() 
{
    FILE *fp = fopen(USER_FILE, "a");
    char username[50], password[50];

    printf("Choose Username: ");
    scanf(" %[^\n]", username);
    printf("Choose Password: ");
    scanf(" %[^\n]", password);

    encryptDecrypt(username);
    encryptDecrypt(password);

    fprintf(fp, "%s,%s\n", username, password);
    fclose(fp);

    printf("Registered successfully!\n");

    encryptDecrypt(username); // Decrypt for reuse
    strcpy(currentUser, username);
}

int checkCredentials(char *username, char *password) 
{
    FILE *fp = fopen(USER_FILE, "r");
    char fileUser[50], filePass[50];

    if (!fp) return 0;

    while (fscanf(fp, "%[^,],%[^\n]\n", fileUser, filePass) != EOF)
    {
        encryptDecrypt(fileUser);
        encryptDecrypt(filePass);
        if (strcmp(fileUser, username) == 0 && strcmp(filePass, password) == 0) 
        {
            fclose(fp);
            strcpy(currentUser, username);
            return 1;
        }
        encryptDecrypt(fileUser);  
        encryptDecrypt(filePass);
    }
    fclose(fp);
    return 0;
}

int login() 
{
    int choice;
    char username[50], password[50];

    printf("\n1. Login\n2. Register\nChoose: ");
    scanf("%d", &choice);

    if (choice == 2) 
    {
        registerUser();
        return 1;
    }

    printf("Username: ");
    scanf(" %[^\n]", username);
    printf("Password: ");
    scanf(" %[^\n]", password);

    if (checkCredentials(username, password)) 
    {
        printf("Login successful!\n");
        return 1;
    }
    else 
    {
        printf("Invalid credentials!\n");
        return 0;
    }
}

void getExpenseFile(char *filename) 
{
    sprintf(filename, "%s_expenses.dat", currentUser);
}

void addExpense() 
{
    char filename[100];
    getExpenseFile(filename);

    FILE *fp = fopen(filename, "a");
    struct Expense e;

    printf("Enter Date (DD-MM-YYYY): ");
    scanf(" %[^\n]", e.date);
    printf("Enter Category: ");
    scanf(" %[^\n]", e.category);
    printf("Enter Amount: ");
    scanf("%f", &e.amount);

    encryptDecrypt(e.date);
    encryptDecrypt(e.category);

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("Expense added successfully!\n");
}

void viewExpenses()
{
    char filename[100];
    getExpenseFile(filename);

    FILE *fp = fopen(filename, "r");
    struct Expense e;

    if (!fp) 
    {
        printf("No expenses found.\n");
        return;
    }

    printf("\n%-15s %-15s %-10s\n", "Date", "Category", "Amount");
    printf("--------------------------------------------\n");

    while (fread(&e, sizeof(e), 1, fp)) 
    {
        encryptDecrypt(e.date);
        encryptDecrypt(e.category);

        printf("%-15s %-15s ₹%.2f\n", e.date, e.category, e.amount);

        encryptDecrypt(e.date); 
        encryptDecrypt(e.category);
    }

    fclose(fp);
}

void monthlyReport() 
{
    char filename[100], targetMonth[10];
    getExpenseFile(filename);

    FILE *fp = fopen(filename, "r");
    struct Expense e;
    float total = 0;

    if (!fp) 
    {
        printf("No expenses found.\n");
        return;
    }

    printf("Enter Month-Year (MM-YYYY): ");
    scanf(" %[^\n]", targetMonth);

    printf("\nReport for %s:\n", targetMonth);
    printf("--------------------------------------------\n");

    while (fread(&e, sizeof(e), 1, fp)) 
    {
        encryptDecrypt(e.date);
        encryptDecrypt(e.category);

        if (strstr(e.date + 3, targetMonth))
        {
            printf("%-15s %-15s ₹%.2f\n", e.date, e.category, e.amount);
            total += e.amount;
        }

        encryptDecrypt(e.date);
        encryptDecrypt(e.category);
    }

    fclose(fp);
    printf("--------------------------------------------\n");
    printf("Total: ₹%.2f\n", total);
}

void showCategoryChart()
{
    char filename[100];
    getExpenseFile(filename);

    FILE *fp = fopen(filename, "r");
    struct Expense e;
    float food = 0, travel = 0, other = 0;

    if (!fp) 
    {
        printf("No expenses found.\n");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp)) 
    {
        encryptDecrypt(e.date);
        encryptDecrypt(e.category);

        if (strcasecmp(e.category, "food") == 0)
            food += e.amount;
        else if (strcasecmp(e.category, "travel") == 0)
            travel += e.amount;
        else
            other += e.amount;

        encryptDecrypt(e.date);
        encryptDecrypt(e.category);
    }

    fclose(fp);

    printf("\nCategory-wise Expense Chart:\n");
    printf("Food   : ");
    for (int i = 0; i < food / 100; i++) printf("█");
    printf(" ₹%.2f\n", food);

    printf("Travel : ");
    for (int i = 0; i < travel / 100; i++) printf("█");
    printf(" ₹%.2f\n", travel);

    printf("Other  : ");
    for (int i = 0; i < other / 100; i++) printf("█");
    printf(" ₹%.2f\n", other);
}

int main() 
{
    int choice;

    printf("====== Welcome to Personal Expense Tracker ======\n");
    if (!login()) return 0;

    while (1) 
    {
        printf("\n============ Menu ============\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Monthly Report\n");
        printf("4. Show Category-wise Chart\n");
        printf("5. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: monthlyReport(); break;
            case 4: showCategoryChart(); break;
            case 5: printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}