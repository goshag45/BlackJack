#ifndef UI_U
#define UI_U

#include <iostream>
#include <string>
#include <ios>
#include <limits>
#include <chrono>
#include <thread>

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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } 

    void choiceMessage(std::string choice) {
        std::cout << "\n" << "You chose: " << choice << '\n';
    }

    void showMessage(std::string messageText) {
        std::cout << messageText << '\n';
    }

    // this use of auto MAY be sus - might be better way to do this? im not sure
    // void showMessage(std::string messageText, auto inputVariable) {
    //     std::cout << messageText << inputVariable << '\n';
    // }

    void playerPlayMenu() {
        std::cout << "\n----------Choose your play----------\n";
        std::cout << "[1] Hit\n";
        std::cout << "[2] Stand\n";
        std::cout << "[3] Double Down\n";
        std::cout << "[4] Split\n";
        std::cout << "[5] Insurance\n";
    }
};

// after game logic is done, use this to add some flair to dealing/drawing methods
inline void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif