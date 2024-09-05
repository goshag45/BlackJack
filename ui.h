#ifndef UI_U
#define UI_U

#include <iostream>
#include <string>

class Ui {
  public:
    Ui() {}

    void showMessage(std::string messageText) {
        std::cout << messageText << '\n';
    }

    int getPlayerInputInt(std::string promptString) {
        std::cout << promptString << '\n';
        // add type checking?
        int output;
        std::cin >> output;
        return output;
    }

  private:

};

inline void continuePrompt() {
    std::cout << "Press Enter to Continue\n";
    std::cin.ignore();
} 

inline void choiceMessage(std::string choice) {
    std::cout << "\n" << "You chose: " << choice << '\n';
}

#endif