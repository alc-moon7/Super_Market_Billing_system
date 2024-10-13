#include <bits/stdc++.h>
using namespace std;

void typeMessage(const string& message) {
    for (char c : message) {
        cout << c << flush;
        for (volatile long delay = 0; delay < 19100000; ++delay);
    }
}
void coutWithTypeEffect(const string& message) {
    typeMessage(message);
}

class Product {
private:
    int code;
    string name;
    float price;
    float discount;

public:
    Product(int code, string name, float price, float discount) : code(code), name(name), price(price), discount(discount) {}

    int getCode() const {
        return code;
    }

    string getName() const {
        return name;
    }

    float getPrice() const {
        return price;
    }

    float getDiscount() const {
        return discount;
    }
};


class Supermarket {
private:
    string adminUsername;
    string adminPassword;
    vector<Product> products;
    void saveToFile(const string& data, const string& filename) const {
        ofstream file;
        file.open(filename, ios_base::app);
        if (file.is_open()) {
            file << data << "\n";
            file.close();
        } else {
            coutWithTypeEffect("\n\nUnable to open file!\n");
        }
    }

    void saveAdminCredentials(const string& username, const string& password) const {
        string data = "Admin Username: " + username + "\nAdmin Password: " + password;
        saveToFile(data, "admin_credentials.txt");
    }

    void saveProductDetails(const Product& product) const {
        string data = "Product Code: " + to_string(product.getCode()) +
                      "\nProduct Name: " + product.getName() +
                      "\nPrice: " + to_string(product.getPrice()) +
                      "\nDiscount: " + to_string(product.getDiscount()) + "%";

        saveToFile(data, "product_details.txt");
    }

    void saveReceiptDetails(const Product& product, int quantity, float totalAmount) const {
    string data = "\nReceipt:\n"
                  "Product Name: " + product.getName() + "\n" +
                  "Quantity: " + to_string(quantity) + "\n" +
                  "Price per item: " + to_string(product.getPrice()) + "\n" +
                  "Total Amount: " + to_string(totalAmount);

    saveToFile(data, "receipt.txt");
}

    void listProducts() const {
        if (products.empty()) {
            coutWithTypeEffect("\n\nSorry No products available.\n");
            return;
        }

      coutWithTypeEffect("Product List:\n");
       cout << left << setw(10) << "Code" << setw(20) << "Name" << setw(10) << "Price" << "Discount\n\n";
    for (const auto& product : products) {
        cout << setw(10) << product.getCode() << setw(20) << product.getName() << setw(10) << product.getPrice() << setw(10) << product.getDiscount() << "%\n";
    }
}

    void editProduct() {
        int code;
        cout << "\n\nEnter the product code to edit: ";
        cin >> code;

        bool found = false;
        for (auto& product : products) {
            if (product.getCode() == code) {
                string name;
                float price, discount;

                cout << "\nEnter new details for the product:\n";
                cout << "\nProduct Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Price: ";
                cin >> price;

                cout << "Discount(%): ";
                cin >> discount;

                product = Product(code, name, price, discount);
                coutWithTypeEffect("\n\nProduct details updated successfully.\n");
                found = true;
                break;
            }
        }

        if (!found) {
          coutWithTypeEffect("\nProduct not found.\n");
        }
    }

    void deleteProduct() {
        int code;
        cout << "\n\nEnter the product code to delete: ";
        cin >> code;

        auto it = products.begin();
        while (it != products.end()) {
            if (it->getCode() == code) {
                it = products.erase(it);
              coutWithTypeEffect("\n\nProduct deleted successfully.\n");
                return;
            } else {
                ++it;
            }
        }
        coutWithTypeEffect("\n\nProduct not found.\n");
    }

public:
     Supermarket() : adminUsername(""), adminPassword("") {}

 void adminLogin() {
        if (adminUsername.empty() || adminPassword.empty()) {
            coutWithTypeEffect("\n\t\t\t\t   Oops ! \n");
            coutWithTypeEffect("\n\tYou have not signed up before. So please sign up first !\n ");
            coutWithTypeEffect("\n\t\t\t       SignUp Menu\n");
            coutWithTypeEffect("\n\t\t------------------------------------\n\n");
        cout << "1. Admin SignUp\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
        cout << "\n\n\nEnter choice: ";

        int loginChoice;
        cin >> loginChoice;

        switch (loginChoice) {
            case 1:
                adminSignup();
                break;
            case 2:
                adminSignIn();
                break;
            case 3:
               coutWithTypeEffect("Exiting program.\n");
                break;
            default:
                coutWithTypeEffect("Invalid choice.\n");
                break;
        }
    } else {
        adminSignIn();
    }
}

void adminSignup() {
    string newUsername, newPassword;
    cout << "\nEnter new username: ";
    cin >> newUsername;

    cout << "\nEnter new password: ";
    cin >> newPassword;

    adminUsername = newUsername;
    adminPassword = newPassword;

    saveAdminCredentials(adminUsername, adminPassword);
   coutWithTypeEffect( "\n\nAdmin account created successfully.\n");
    return;
}


    void adminSignIn() {
        string username, password;
        cout << "\nEnter username: ";
        cin >> username;

        cout << "\nEnter password: ";
        cin >> password;

        if (username == adminUsername && password == adminPassword) {
            cout << "\n\nLogged in as administration.\n";
            saveAdminCredentials(username, password);
            int choice;
            do {
                coutWithTypeEffect("\n\t\t  Admin Menu:\n");
                coutWithTypeEffect("\n\t\t---------------\n\n");
                cout << "1. Add Product\n";
                cout << "2. Edit Product\n";
                cout << "3. Delete Product\n";
                cout << "4. List Products\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        addProduct();
                        break;
                    case 2:
                        editProduct();
                        break;
                    case 3:
                        deleteProduct();
                        break;
                    case 4:
                        listProducts();
                        break;
                    case 5:
                        coutWithTypeEffect("\nReturning to Main Menu.\n");
                        break;
                    default:
                        coutWithTypeEffect("\n\nInvalid choice.\n");
                        break;
                }
            } while (choice != 5);
        } else {
            coutWithTypeEffect("\n\nInvalid credentials.\n");
        }
    }
    void addProduct() {
    int code;
    string name;
    float price, discount;

    coutWithTypeEffect("\nEnter product details:\n\n");
    cout << "Product Code: ";
    cin >> code;

    cout << "Product Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Price: ";
    while (!(cin >> price) || price < 0) {
        cout << "\n\nInvalid input. Enter a valid price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Discount(%): ";
    while (!(cin >> discount) || discount < 0 || discount > 100) {
        cout << "Invalid input. Enter a valid discount percentage: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    products.emplace_back(code, name, price, discount);
    saveProductDetails(products.back());
    coutWithTypeEffect("Product added successfully.\n");
}

    void buyerMenu() {
        int choice;
        do {
            coutWithTypeEffect("\n\t\t  Buyer Menu:\n");
            coutWithTypeEffect("\n\t\t---------------\n");
            cout << "1. View Products\n";
            cout << "2. Buy Products\n";
            cout << "3. Back to Main Menu\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    listProducts();
                    break;
                case 2:
                    buyProducts();
                    break;
                case 3:
                    coutWithTypeEffect("\n\nReturning to Main Menu.\n");
                    break;
                default:
                    coutWithTypeEffect("\n\nInvalid choice.\n");
                    break;
            }
        } while (choice != 3);
    }

void buyProducts() {
    int productCode, quantity;
    float totalAmount = 0;

    if (products.empty()) {
        coutWithTypeEffect("\n\nNo products available for purchase.\n");
        return;
    }

    listProducts();
    cout << "\nEnter the product code you want to buy: ";
    cin >> productCode;

    bool productFound = false;
    for (const auto& product : products) {
        if (product.getCode() == productCode) {
            productFound = true;
            cout << "\nEnter the quantity you want to buy: ";
            cin >> quantity;

            float amount = (product.getPrice() - (product.getDiscount() / 100) * product.getPrice()) * quantity;
            totalAmount += amount;

            generateReceipt(product, quantity, amount);
            saveReceiptDetails(product, quantity, amount); // Save receipt details
            cout << "\n\nProduct(s) added to cart.\n";
            break;
        }
    }

    if (!productFound) {
        cout << "\nProduct not found.\n";
    }

    cout << "\n\nTotal Amount to be paid: " << fixed << setprecision(2) << totalAmount << endl;
}

void generateReceipt(const Product& product, int quantity, float totalAmount) {
     coutWithTypeEffect("\n\t\t  Receipt:\n");
     coutWithTypeEffect("\n\t\t-------------\n");
    cout << "\n\n  Product Name: " << product.getName() << endl << endl;
    cout << "      Quantity: " << quantity << endl << endl;
    cout << "Price per item: " << product.getPrice() << endl << endl;
    cout << "  Total Amount: " << totalAmount << endl << endl;
    coutWithTypeEffect("\n\nThank you for shopping with us!\n");
}

void saveReceiptDetails(const Product& product, int quantity, float totalAmount) {
    ofstream file;
    file.open("receipt.txt", ios_base::app);
    if (file.is_open()) {
        file << "\n\t\t  Receipt:\n";
        file << "\n\t\t--------------\n";
        file << "  Product Name: " << product.getName() << endl << endl;
        file << "      Quantity: " << quantity << endl << endl;
        file << "Price per item: " << product.getPrice() << endl << endl;
        file << "  Total Amount: " << totalAmount << endl << endl;
        file << "\n\nThank you for shopping with us!\n\n";
        file.close();
    } else {
        cout << "\n\nUnable to open file for saving receipt details!\n";
    }
}
};
int main() {
    Supermarket supermarket;
    int choice;

    do {
        coutWithTypeEffect("\n\t\t\tWelcome to SuperMarket ");
        coutWithTypeEffect("\n\t\t\t     Main Menu\n");
        coutWithTypeEffect("\n\t\t------------------------------------\n");
        coutWithTypeEffect("1. Admin Login\n");
        coutWithTypeEffect("2. Buyer Menu\n");
        coutWithTypeEffect("3. Exit\n");
        coutWithTypeEffect("\n\nEnter choice: ");
        cin >> choice;

        switch (choice) {
            case 1:
                supermarket.adminLogin();
                break;
            case 2:
                supermarket.buyerMenu();
                break;
            case 3:
                 coutWithTypeEffect( "Exiting program.\n");
                break;
            default:
             coutWithTypeEffect( "Invalid choice.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}