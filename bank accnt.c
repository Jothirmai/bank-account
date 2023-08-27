
#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct BankAccount {
    int number;
    char holder[50];
    double balance;
    char pin[6];
};

int num_accounts = 0;
struct BankAccount accounts[MAX_ACCOUNTS];

void createAccount() {
    if (num_accounts < MAX_ACCOUNTS) {
        struct BankAccount account;
        printf("Enter account holder name: ");
        scanf("%s", account.holder);
        printf("Enter initial balance: ");
        scanf("%lf", &account.balance);
        printf("Enter PIN (5 digits): ");
        scanf("%s", account.pin);
        account.account_number = num_accounts + 1;
        accounts[num_accounts++] = account;
        printf("Account created successfully!\n");
    } else {
        printf("Maximum number of accounts reached.\n");
    }
}

struct BankAccount* login() {
    int number;
    char pin[6];
    printf("Enter account number: ");
    scanf("%d", &number);
    printf("Enter PIN: ");
    scanf("%s", &pin);

    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].number == number && strcmp(accounts[i].pin, pin) == 0) {
            return &accounts[i];
        }
    }

    printf("Invalid account number or PIN.\n");
    return NULL;
}

void mainMenu(struct BankAccount* loggedAccount) {
    while (loggedAccount != NULL) {
        printf("\nLogged in as: %s\n", loggedAccount->holder);
        printf("1. Deposit\n2. Withdraw\n3. Check Balance\n4. Transfer\n5. Logout\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                double amount;
                printf("Enter deposit amount: ");
                scanf("%lf", &amount);
                loggedAccount->balance += amount;
                printf("Amount deposited successfully!\n");
                break;
            }
            case 2: {
                double amount;
                printf("Enter withdrawal amount: ");
                scanf("%lf", &amount);
                if (loggedAccount->balance >= amount) {
                    loggedAccount->balance -= amount;
                    printf("Amount withdrawn successfully!\n");
                } else {
                    printf("Insufficient balance.\n");
                }
                break;
            }
            case 3: {
                printf("Current balance: %.2lf\n", loggedAccount->balance);
                break;
            }
            case 4: {
                int recipient_account_number;
                double transfer_amount;
                printf("Enter recipient's account number: ");
                scanf("%d", &recipient_account_number);
                printf("Enter transfer amount: ");
                scanf("%lf", &transfer_amount);
                for (int i = 0; i < num_accounts; i++) {
                    if (accounts[i].account_number == recipient_account_number) {
                        if (loggedAccount->balance >= transfer_amount) {
                            loggedAccount->balance -= transfer_amount;
                            accounts[i].balance += transfer_amount;
                            printf("Transfer successful!\n");
                        } else {
                            printf("Insufficient balance for transfer.\n");
                        }
                        break;
                    }
                }
                break;
            }
            case 5: {
                printf("Logged out.\n");
                loggedAccount = NULL;
                break;
            }
            default:
                printf("Invalid choice.\n");
        }
    }
}

int main() {
    while (1) {
        printf("\nWelcome to the Banking System!\n");
        printf("1. Create Account\n2. Login\n3. Exit\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2: {
                struct BankAccount* loggedAccount = login();
                if (loggedAccount != NULL) {
                    mainMenu(loggedAccount);
                }
                break;
            }
            case 3:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}