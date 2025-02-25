#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // For sleep()

#define MAX_TRANSACTIONS 100

float balance = 0.0;
char atmPassword[7];  // 6-digit password + null terminator

typedef struct {
    char type[10];     // Deposit or Withdraw
    float amount;
    char time[25];     // Transaction time
    float balance;
} Transaction;

Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

// Function to get current time in DD-MM-YYYY HH:MM:SS format
void getCurrentTime(char *timeStr) {
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    strftime(timeStr, 25, "%d-%m-%Y %H:%M:%S", tm_info);
}

// Function to display colorful menu
void displayMenu() {
    printf("\n\033[1;36m========== 🏦 \033[1;35mATM INTERFACE \033[1;36m==========\033[0m\n");
    printf("\033[1;34m1. Check Balance\n");
    printf("2. Deposit Money 💰\n");
    printf("3. Withdraw Money 🏦\n");
    printf("4. View Transaction History 📜\n");
    printf("5. Exit 🚪\033[0m\n");
    printf("=======================================\n");
    printf("\033[1;33mEnter your choice (1-5): \033[0m");
}

// Function to display balance
void checkBalance() {
    printf("\n💰 \033[1;32mYour Current Balance: ₹%.2f\033[0m\n", balance);
}

// Function to simulate money deposit
void simulateMoneyFlow(const char *action) {
    printf("\033[1;33mProcessing %s", action);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf(" ✅\033[0m\n");
}

// Function to record transaction
void recordTransaction(const char *type, float amount) {
    if (transactionCount < MAX_TRANSACTIONS) {
        strcpy(transactions[transactionCount].type, type);
        transactions[transactionCount].amount = amount;
        getCurrentTime(transactions[transactionCount].time);
        transactions[transactionCount].balance = balance;
        transactionCount++;
    }
}

// Function to deposit money
void depositMoney() {
    float amount;
    printf("\n💵 Enter the amount to deposit: ₹");
    scanf("%f", &amount);
    if (amount > 0) {
        simulateMoneyFlow("deposit");
        balance += amount;
        printf("✅ \033[1;32mSuccessfully deposited ₹%.2f!\033[0m\n", amount);
        recordTransaction("Deposit", amount);
        checkBalance();
    } else {
        printf("❌ \033[1;31mInvalid amount. Please enter a positive value.\033[0m\n");
    }
}

// Function to withdraw money
void withdrawMoney() {
    float amount;
    printf("\n🏧 Enter the amount to withdraw: ₹");
    scanf("%f", &amount);
    if (amount > 0 && amount <= balance) {
        simulateMoneyFlow("withdrawal");
        balance -= amount;
        printf("✅ \033[1;32mSuccessfully withdrawn ₹%.2f!\033[0m\n", amount);
        recordTransaction("Withdraw", amount);
        checkBalance();
    } else if (amount > balance) {
        printf("❌ \033[1;31mInsufficient balance. You only have ₹%.2f.\033[0m\n", balance);
    } else {
        printf("❌ \033[1;31mInvalid amount. Please enter a positive value.\033[0m\n");
    }
}

// Function to view transaction history
void viewTransactionHistory() {
    printf("\n📜 \033[1;33mTransaction History:\033[0m\n");
    if (transactionCount == 0) {
        printf("No transactions yet.\n");
    } else {
        for (int i = 0; i < transactionCount; i++) {
            printf("%d. 📅 %s | \033[1;34m%s\033[0m: ₹%.2f | Balance: ₹%.2f\n",
                   i + 1, transactions[i].time, transactions[i].type,
                   transactions[i].amount, transactions[i].balance);
        }
    }
}

// Function to set 6-digit ATM password
void setATMPassword() {
    printf("\n🔒 \033[1;36mSet a 6-digit ATM Password: \033[0m");
    scanf("%6s", atmPassword);
    atmPassword[6] = '\0';  // Ensure null termination
    printf("\033[1;32m✅ Password set successfully!\033[0m\n");
}

// Function to verify ATM password
int verifyPassword() {
    char inputPassword[7];
    printf("\n🔑 \033[1;35mEnter your 6-digit ATM Password: \033[0m");
    scanf("%6s", inputPassword);
    inputPassword[6] = '\0';  // Ensure null termination

    if (strcmp(inputPassword, atmPassword) == 0) {
        return 1;
    } else {
        printf("❌ \033[1;31mIncorrect password. Access denied!\033[0m\n");
        return 0;
    }
}

int main() {
    int choice;

    printf("\n🚀 \033[1;36mWelcome to the Advanced ATM Interface!\033[0m\n");

    // Set ATM password
    setATMPassword();

    // Verify password before proceeding
    if (!verifyPassword()) {
        exit(1);
    }

    // Initial deposit
    float initialDeposit;
    printf("\n💰 \033[1;33mEnter initial deposit amount: ₹\033[0m");
    scanf("%f", &initialDeposit);

    if (initialDeposit > 0) {
        balance = initialDeposit;
        printf("✅ \033[1;32mInitial deposit successful! Your balance is ₹%.2f.\033[0m\n", balance);
    } else {
        printf("❌ \033[1;31mInvalid initial deposit amount. Starting with ₹0.00 balance.\033[0m\n");
    }

    // Main menu loop
    while (1) {
        if (!verifyPassword()) {
            continue;  // Re-prompt if password is wrong
        }

        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                viewTransactionHistory();
                break;
            case 5:
                printf("\n🚪 \033[1;35mThank you for using the ATM. Goodbye!\033[0m\n");
                exit(0);
            default:
                printf("❌ \033[1;31mInvalid choice. Please select a valid option.\033[0m\n");
        }
    }

    return 0;
}
