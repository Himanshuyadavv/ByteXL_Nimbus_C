#include <stdio.h>
#include <stdlib.h>

void displayMenu() {
    printf("\n===== 🖩 Interactive Calculator =====\n");
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("5. Modulus (%%)\n");
    printf("6. Reset Result\n");
    printf("7. Exit\n");
    printf("====================================\n");
}

int main() {
    int choice;
    double num1, num2, result = 0.0;
    int usePrevious = 0;  // Flag to use the previous result

    while (1) {
        displayMenu();

        // Display current result if available
        printf("\n⭐ Current Result: %.2lf\n", result);
        printf("Choose an option (1-7): ");
        scanf("%d", &choice);

        if (choice == 7) {
            printf("\n🚀 Exiting the calculator. Thank you!\n");
            break;
        }

        // Reset result if chosen
        if (choice == 6) {
            result = 0.0;
            usePrevious = 0;
            printf("\n🔄 Result has been reset to 0.\n");
            continue;
        }

        // Determine first number (previous result or new input)
        if (usePrevious) {
            num1 = result;
            printf("\n💡 Using previous result as the first number: %.2lf\n", num1);
        } else {
            printf("Enter first number: ");
            scanf("%lf", &num1);
        }

        // Second number input
        printf("Enter second number: ");
        scanf("%lf", &num2);

        // Perform the selected operation
        switch (choice) {
            case 1:
                result = num1 + num2;
                printf("\n✅ Result: %.2lf + %.2lf = %.2lf\n", num1, num2, result);
                break;
            case 2:
                result = num1 - num2;
                printf("\n✅ Result: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
                break;
            case 3:
                result = num1 * num2;
                printf("\n✅ Result: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
                break;
            case 4:
                if (num2 != 0) {
                    result = num1 / num2;
                    printf("\n✅ Result: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
                } else {
                    printf("\n❌ Error: Division by zero is not allowed!\n");
                }
                break;
            case 5:
                if ((int)num1 == num1 && (int)num2 == num2) {
                    result = (int)num1 % (int)num2;
                    printf("\n✅ Result: %d %% %d = %d\n", (int)num1, (int)num2, (int)result);
                } else {
                    printf("\n❌ Error: Modulus is only for integers!\n");
                }
                break;
            default:
                printf("\n⚠️ Invalid choice! Please select a valid option.\n");
                continue;
        }

        // Set flag to use previous result
        usePrevious = 1;

        // Pause before the next iteration
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        system("clear || cls");  // Clear console for better visibility
    }

    return 0;
}
