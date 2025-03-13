#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_CATEGORY_LENGTH 20

typedef struct {
    char category[MAX_CATEGORY_LENGTH];
    double amount;
} Expense;

typedef struct {
    Expense expenses[MAX_EXPENSES];
    int numExpenses;
} ExpenseTracker;

void initExpenseTracker(ExpenseTracker* tracker) {
    tracker->numExpenses = 0;
}

void addExpense(ExpenseTracker* tracker) {
    if (tracker->numExpenses >= MAX_EXPENSES) {
        printf("Maximum number of expenses reached.\n");
        return;
    }

    char category[MAX_CATEGORY_LENGTH];
    printf("Enter category (e.g., Food, Travel, Bills): ");
    fgets(category, MAX_CATEGORY_LENGTH, stdin);
    category[strcspn(category, "\n")] = 0; // Remove newline character

    double amount;
    printf("Enter amount: ");
    scanf("%lf", &amount);
    getchar(); // Consume newline left-over

    // Check if category already exists
    for (int i = 0; i < tracker->numExpenses; i++) {
        if (strcmp(tracker->expenses[i].category, category) == 0) {
            tracker->expenses[i].amount += amount;
            printf("Expense added successfully!\n");
            return;
        }
    }

    // Category does not exist, add new expense
    Expense newExpense;
    strcpy(newExpense.category, category);
    newExpense.amount = amount;
    tracker->expenses[tracker->numExpenses] = newExpense;
    tracker->numExpenses++;
    printf("Expense added successfully!\n");
}

void removeExpense(ExpenseTracker* tracker) {
    if (tracker->numExpenses == 0) {
        printf("No expenses to remove.\n");
        return;
    }

    char category[MAX_CATEGORY_LENGTH];
    printf("Enter category to remove(e.g., Food, Travel, Bills): ");
    fgets(category, MAX_CATEGORY_LENGTH, stdin);
    category[strcspn(category, "\n")] = 0; // Remove newline character

    for (int i = 0; i < tracker->numExpenses; i++) {
        if (strcmp(tracker->expenses[i].category, category) == 0) {
            for (int j = i; j < tracker->numExpenses - 1; j++) {
                tracker->expenses[j] = tracker->expenses[j + 1];
            }
            tracker->numExpenses--;
            printf("Expense removed successfully!\n");
            return;
        }
    }

    printf("Category not found.\n");
}

void editExpense(ExpenseTracker* tracker) {
    if (tracker->numExpenses == 0) {
        printf("No expenses to edit.\n");
        return;
    }

    char category[MAX_CATEGORY_LENGTH];
    printf("Enter category to edit (e.g., Food, Travel, Bills): ");
    fgets(category, MAX_CATEGORY_LENGTH, stdin);
    category[strcspn(category, "\n")] = 0; // Remove newline character

    for (int i = 0; i < tracker->numExpenses; i++) {
        if (strcmp(tracker->expenses[i].category, category) == 0) {
            printf("Enter new amount: ");
            scanf("%lf", &tracker->expenses[i].amount);
            getchar(); // Consume newline left-over
            printf("Expense edited successfully!\n");
            return;
        }
    }

    printf("Category not found.\n");
}

void deleteExpense(ExpenseTracker* tracker) {
    removeExpense(tracker);
}

void displayTotalExpenses(ExpenseTracker* tracker) {
    if (tracker->numExpenses == 0) {
        printf("No expenses to display.\n");
        return;
    }

    double totalExpenses = 0;
    printf("Total Expenses:\n");
    for (int i = 0; i < tracker->numExpenses; i++) {
        printf("%s: %.2lf\n", tracker->expenses[i].category, tracker->expenses[i].amount);
        totalExpenses += tracker->expenses[i].amount;
    }
    printf("Total: %.2lf\n", totalExpenses);
}

int main() {
    ExpenseTracker tracker;
    initExpenseTracker(&tracker);

    while (1) {
        printf("Expense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. Remove Expense\n");
        printf("3. Edit Expense\n");
        printf("4. Delete Expense\n");
        printf("5. Display Total Expenses\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        getchar(); // Consume newline left-over

        switch (choice) {
            case 1:
             addExpense(&tracker);
                break;
            case 2:
                removeExpense(&tracker);
                break;
            case 3:
                editExpense(&tracker);
                break;
            case 4:
                deleteExpense(&tracker);
                break;
            case 5:
                displayTotalExpenses(&tracker);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}