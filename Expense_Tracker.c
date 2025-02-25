#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100

typedef struct {
    char category[20];
    float amount;
    char date[11];
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// Function to display the chart
void displayChart() {
    float foodTotal = 0, travelTotal = 0, shoppingTotal = 0;

    for (int i = 0; i < expenseCount; i++) {
        if (strcmp(expenses[i].category, "Food") == 0)
            foodTotal += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Travel") == 0)
            travelTotal += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Shopping") == 0)
            shoppingTotal += expenses[i].amount;
    }

    printf("\n📊 Expense Chart by Category:\n");
    printf("------------------------------\n");
    printf("🍔 Food    : ₹%.2f | ", foodTotal);
    for (int i = 0; i < foodTotal / 100; i++) printf("█");
    printf("\n");

    printf("🚗 Travel  : ₹%.2f | ", travelTotal);
    for (int i = 0; i < travelTotal / 100; i++) printf("█");
    printf("\n");

    printf("🛍️ Shopping: ₹%.2f | ", shoppingTotal);
    for (int i = 0; i < shoppingTotal / 100; i++) printf("█");
    printf("\n------------------------------\n");
}

// Function to add an expense
void addExpense() {
    if (expenseCount < MAX_EXPENSES) {
        printf("\n💰 Enter Expense Details:\n--------------------------\n");
        printf("Category (Food, Travel, Shopping): ");
        scanf("%s", expenses[expenseCount].category);
        printf("Amount (₹): ");
        scanf("%f", &expenses[expenseCount].amount);
        printf("Date (DD-MM-YYYY): ");
        scanf("%s", expenses[expenseCount].date);
        printf("✅ Expense added successfully!\n");
        expenseCount++;
        displayChart();
    } else {
        printf("❌ Expense limit reached!\n");
    }
}

// Function to view all expenses
void viewExpenses() {
    float totalExpense = 0;
    printf("\n📊 Expense Log:\n------------------------------\n");
    for (int i = 0; i < expenseCount; i++) {
        printf("%d. 📂 Category: %s\n", i + 1, expenses[i].category);
        printf("   💸 Amount: ₹%.2f\n", expenses[i].amount);
        printf("   📅 Date: %s\n", expenses[i].date);
        printf("------------------------------\n");
        totalExpense += expenses[i].amount;
    }
    printf("💰 Total Expense: ₹%.2f\n", totalExpense);
}

// Function to search by category
void searchExpenseByCategory() {
    char searchCategory[20];
    printf("\n🔍 Enter category to search (Food, Travel, Shopping): ");
    scanf("%s", searchCategory);

    printf("\n📖 Search Results for '%s':\n", searchCategory);
    printf("------------------------------\n");
    int found = 0;

    for (int i = 0; i < expenseCount; i++) {
        if (strcmp(expenses[i].category, searchCategory) == 0) {
            printf("📂 Category: %s\n💸 Amount: ₹%.2f\n📅 Date: %s\n",
                   expenses[i].category, expenses[i].amount, expenses[i].date);
            printf("------------------------------\n");
            found = 1;
        }
    }

    if (!found) printf("❌ No expenses found for '%s'.\n", searchCategory);
}

// Function to delete an expense
void deleteExpense() {
    int index;
    viewExpenses();
    printf("\n🗑️ Enter expense number to delete: ");
    scanf("%d", &index);

    if (index > 0 && index <= expenseCount) {
        for (int i = index - 1; i < expenseCount - 1; i++) {
            expenses[i] = expenses[i + 1];
        }
        expenseCount--;
        printf("✅ Expense deleted successfully!\n");
        displayChart();
    } else {
        printf("❌ Invalid expense number!\n");
    }
}

// Function to calculate total expense
void calculateTotalExpense() {
    float total = 0;
    for (int i = 0; i < expenseCount; i++) {
        total += expenses[i].amount;
    }
    printf("\n💰 Total Expense: ₹%.2f\n", total);
    displayChart();
}

int main() {
    int choice;
    while (1) {
        printf("\n🌟 Welcome to Expense Tracker 🌟\n");
        printf("================================\n");
        printf("1. 📝 Add Expense\n");
        printf("2. 📊 View All Expenses\n");
        printf("3. 🔍 Search Expense by Category\n");
        printf("4. 🗑️ Delete Expense\n");
        printf("5. 🟢 Calculate Total Expense\n");
        printf("6. ❌ Exit\n");
        printf("================================\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: searchExpenseByCategory(); break;
            case 4: deleteExpense(); break;
            case 5: calculateTotalExpense(); break;
            case 6: printf("👋 Thank you for using Expense Tracker! Goodbye!\n"); exit(0);
            default: printf("❌ Invalid choice! Please select a valid option.\n");
        }
    }
    return 0;
}
