#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITEMS 50
#define MAX_USERS 10
typedef struct {
    char name[30];
    float price;
    int quantity;
} Item;

typedef struct {
    char customer[50];
    int itemCount;
    Item items[MAX_ITEMS];
    float total;
} Order;

typedef struct {
    char username[30];
    char password[20];
} User;

Item menu[MAX_ITEMS] = {
    {"Burger", 250.00, 10},
    {"Pizza", 450.00, 8},
    {"Pasta", 350.00, 12},
    {"Fries", 150.00, 15},
    {"Salad", 200.00, 10},
    {"Soda", 50.00, 20},
    {"Coffee", 80.00, 18},
    {"Ice Cream", 120.00, 10},
    {"Sandwich", 180.00, 12},
    {"Steak", 700.00, 5},
    {"Chicken Biryani", 300.00, 10},
    {"Beef Curry", 500.00, 6},
    {"Fish Fry", 400.00, 7},
    {"Dal Tadka", 150.00, 8},
    {"Butter Naan", 50.00, 15}
};
int menuCount = 15;
User users[MAX_USERS];
int userCount = 0;

void addMenuItem() {
    if (menuCount >= MAX_ITEMS) {
        printf("Menu is full!\n");
        return;
    }
    printf("Enter item name: ");
    scanf("%29s", menu[menuCount].name);  // Limit input to prevent overflow
    printf("Enter price: ");
    scanf("%f", &menu[menuCount].price);
    printf("Enter quantity: ");
    scanf("%d", &menu[menuCount].quantity);
    menuCount++;
    printf("Item added successfully!\n");
}

void displayMenu() {
    printf("\n--- MENU ---\n");
    for (int i = 0; i < menuCount; i++) {
        printf("%d. %s - %.2f Taka (%d available)\n", i + 1, menu[i].name, menu[i].price, menu[i].quantity);
    }
}

void takeOrder() {
    Order order;
    printf("Enter customer name: ");
    scanf("%49s", order.customer);  // Limit input to prevent overflow
    order.itemCount = 0;
    order.total = 0;

    int choice, qty;
    char cont = 'y';
    while (cont == 'y' || cont == 'Y') {
        displayMenu();
        printf("Select item number: ");
        scanf("%d", &choice);
        printf("Enter quantity: ");
        scanf("%d", &qty);
        if (choice > 0 && choice <= menuCount && menu[choice - 1].quantity >= qty) {
            order.items[order.itemCount] = menu[choice - 1];
            order.items[order.itemCount].quantity = qty;
            order.total += qty * menu[choice - 1].price;
            order.itemCount++;
            menu[choice - 1].quantity -= qty;
            printf("Item added to order!\n");
        } else {
            printf("Invalid choice or insufficient stock.\n");
        }
        printf("Add another item? (y/n): ");
        scanf(" %c", &cont);  // This is correct with space before %c to consume newline
    }
    printf("\n--- BILL ---\n");
    printf("Customer: %s\n", order.customer);
    for (int i = 0; i < order.itemCount; i++) {
        printf("%s x %d = %.2f Taka\n", order.items[i].name, order.items[i].quantity, order.items[i].quantity * order.items[i].price);
    }
    printf("Total: %.2f Taka\n", order.total);
}

void searchProduct() {
    char name[30];
    printf("Enter product name to search: ");
    scanf("%29s", name);  // Limit input to prevent overflow

    int found = 0;
    for (int i = 0; i < menuCount; i++) {
        if (strcmp(menu[i].name, name) == 0) {
            printf("Product found: %s - %.2f Taka (%d available)\n", menu[i].name, menu[i].price, menu[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found in the menu.\n");
    }
}

void removeProduct() {
    int productNumber;
    printf("Enter product number to remove (1 to %d): ", menuCount);
    scanf("%d", &productNumber);

    // Check if the product number is valid
    if (productNumber < 1 || productNumber > menuCount) {
        printf("Invalid product number!\n");
        return;
    }

    // Shift items to remove the selected product
    for (int i = productNumber - 1; i < menuCount - 1; i++) {
        menu[i] = menu[i + 1];
    }
    menuCount--;  // Decrease the menu count
    printf("Product removed successfully!\n");
}

void adminPanel() {
    int choice;
    do {
        printf("\n--- ADMIN PANEL ---\n");
        printf("1. Add Menu Item\n");
        printf("2. Display Menu\n");
        printf("3. Remove Menu Item\n");
        printf("4. Search Menu Item\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addMenuItem(); break;
            case 2: displayMenu(); break;
            case 3: removeProduct(); break;
            case 4: searchProduct(); break;
            case 5: printf("Logging out...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }
    printf("Enter username: ");
    scanf("%29s", users[userCount].username);  // Limit input to prevent overflow
    printf("Enter password: ");
    scanf("%19s", users[userCount].password);  // Limit input to prevent overflow
    userCount++;
    printf("Registration successful!\n");
}

int login() {
    char uname[30], pass[20];
    printf("Enter username: ");
    scanf("%29s", uname);  // Limit input to prevent overflow
    printf("Enter password: ");
    scanf("%19s", pass);  // Limit input to prevent overflow

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, uname) == 0 && strcmp(users[i].password, pass) == 0) {
            printf("Login successful!\n");
            return 1;
        }
    }
    printf("Invalid credentials!\n");
    return 0;
}
int main() {
    int choice;
    do {
        printf("\n--- RESTAURANT ORDER SYSTEM ---\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Take Order\n");
        printf("4. Admin Panel\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: registerUser(); break;
            case 2: if (login()) adminPanel(); break;
            case 3: takeOrder(); break;
            case 4: if (login()) adminPanel(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
    return 0;
}
