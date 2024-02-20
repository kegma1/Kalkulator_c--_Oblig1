#include <iostream>
#include <limits>
#include <functional>

// Med tanke på hvor simpel dette programet er så jeg ingen naturlinge plasser hvor bruk av klasser eller structs hadde gjort koden bedre

// Denne funksjonen tar seg av validering av bruker data. Funksjonen returnerer ikke med mindre brukeren skriver en valid integer
int get_number() {
    int user_input;
    while (!(std::cin >> user_input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Denne linjen er for å klargjøre cin for neste loop
        std::cout << "Please enter a valid number\n";
    }
    return user_input;
}

// Denne funksjonen finnes fordi det ble uryddig å ha den i main loopen.
void print_menu() {
    std::cout << "welcome to the best calculator, please enter a number form 1-5 to select an option" << std::endl;
    std::cout << "1. Addition" << std::endl;
    std::cout << "2. Subtraction" << std::endl;
    std::cout << "3. Multiplication" << std::endl;
    std::cout << "4. Division" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

// Denne funksjonen henter to tall fra brukeren som blir brukt i utregning. op er hvilken operator den skal skrive i mellom de to tallen.
// Denne funksjonen kunne vært integerert i "preform_calculation" funksjonen, men syntes det ble uryddig, som er hvorfor den er separert.
int* get_args(char op) {
    int* nums = new int[2];
    system("CLS");
    std::cout << "Enter your first number." << std::endl;
    nums[0] = get_number();
    system("CLS");
    std::cout << "Enter your second number." << std::endl;
    std::cout << nums[0] << ' ' << op << ' ';
    nums[1] = get_number();
    return nums;
}

// Grunnen for at jeg valgte å bruke en lambda funksjon er fordi det vil (med få endringer) være lett å støtte nye operatorer.
// Denne funksjonen er dermed ansvarlig for å vise resultatest på en bestemt måte, mens "func" har ansvaret for å gjøre utregningen.
void preform_calculation(char op, std::function<int(int, int)> func) {
    int* args = get_args(op);
    system("CLS");
    std::cout << "Your result is." << std::endl;
    std::cout << args[0] << " " << op << " " << args[1] << " = " << func(args[0], args[1]) << std::endl;
    delete[] args;
}

int main() {
    bool running = true;
    while(running) {
        print_menu();
        int choice = get_number();
        switch (choice) {
            case 1: // Addition
            {
                preform_calculation('+', [](int a, int b) {
                    return a + b;
                });
                break;
            }
            case 2: // Subtraction
            {
                preform_calculation('-', [](int a, int b) {
                    return a - b;
                });
                break;
            }
            case 3: // Multiplication
            {
                preform_calculation('*', [](int a, int b) {
                    return a * b;
                });
                break;
            }
            case 4: // Division
            {
                preform_calculation('/', [](int a, int b) {
                    return a / b;
                });
                break;
            }
            case 5: // Exit
                system("CLS");
                std::cout << "Goodbye :)\n";
                running = false;
                break;
            default:
                std::cout << "Unexpected input, please only enter a number between 1-5\n";
                break;
        }
        system("pause");
        system("CLS");
    }
    return 0;
}