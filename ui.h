#ifndef UI_U
#define UI_U

#include <iostream>
#include <string>

class Ui {
  public:
    Ui() {}

    int getPlayerInputInt(std::string promptString) {
        std::cout << promptString << '\n';
        // add type checking?
        int output;
        std::cin >> output;
        return output;
    }

    void continuePrompt() {
        std::cout << "Press Enter to Continue\n";
        std::cin.ignore();
    } 

    void choiceMessage(std::string choice) {
        std::cout << "\n" << "You chose: " << choice << '\n';
    }

    void showMessage(std::string messageText) {
        std::cout << messageText << '\n';
    }

    void playerPlayMenu() {
        std::cout << "\n----------Choose your play----------\n";
        std::cout << "[1] Hit\n";
        std::cout << "[2] Stand\n";
        std::cout << "[3] Double Down\n";
        std::cout << "[4] Split\n";
        std::cout << "[5] Insurance\n";
    }
};



#endif