#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
using namespace std;

int globalScore = 0;

class Question {
private:
    string question;
    char answer;
public:
    Question(string q, char a) {
        question = q;
        answer = a;
    }
    bool checkAnswer(char userAnswer) {
        return toupper(userAnswer) == answer || tolower(userAnswer) == answer;
    }
};

void readQuestions() {
    ifstream file("questions.txt");
    string line;
    char answer;

    while (getline(file, line)) {
        cout << "+------------------------------+" << endl;
        cout << "|                              |" << endl;
        cout << "| " << line << endl;
        getline(file, line);
        cout << "| A) " << line << endl;
        getline(file, line);
        cout << "| B) " << line << endl;
        getline(file, line);
        cout << "| C) " << line << endl;
        getline(file, line);
        cout << "| D) " << line << endl;
        cout << "|                              |" << endl;
        cout << "+------------------------------+" << endl;
        file >> answer;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        // Ask for user's answer and wait for enter key
        // Ask for user's answer and wait for enter key
char userAnswer;
do {
    cout << "Enter your answer (A/B/C/D): ";
    cin >> userAnswer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    userAnswer = toupper(userAnswer);

    if (userAnswer != 'A' && userAnswer != 'B' && userAnswer != 'C' && userAnswer != 'D') {
        cout << "Invalid input. Please enter A, B, C, or D." << endl;
    }
} while (userAnswer != 'A' && userAnswer != 'B' && userAnswer != 'C' && userAnswer != 'D');

// Check if user's answer is correct
Question question(line, answer);
if (question.checkAnswer(userAnswer)) {
    cout << "Correct!" << endl;
    globalScore++;
} else {
    cout << "Wrong answer." << endl;
    cout << "The correct answer was " << answer << "." << endl;
}


        // Wait for user to press enter before moving on to next question
        cout << "Press enter to continue..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    file.close();
}

void storeScore(string name, int playerScore) {
    ofstream file("scores.txt", ios::app);
    if (file.is_open()) {
        file << name << ": " << playerScore << endl;
        file.close();
    } else {
        cout << "Error opening file." << endl;
    }
}

void displayScores() {
    ifstream file("scores.txt");
    if (file.is_open()) {
        string line;
        cout << "+------------------------------+" << endl;
        cout << "|      Final Scores            |" << endl;
        cout << "+------------------------------+" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Error opening file." << endl;
    }
}

int main() {
    vector<string> names;
    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        string name;
        cout << "Enter your name: ";
        getline(cin, name);
        names.push_back(name);

        globalScore = 0;
        readQuestions();
        storeScore(name, globalScore);

        cout << "+------------------------------+" << endl;
        cout << "|                              |" << endl;
        cout << "| Your score is: " << globalScore << " out of 5" << endl;
        cout << "|                              |" << endl;
        cout << "+------------------------------+" << endl;

        // Display all names and scores
        cout << "+------------------------------+" << endl;
        cout << "| Final Scores |" << endl;
        cout << "+------------------------------+" << endl;
        for (int i = 0; i < names.size(); i++) {
            ifstream file("scores.txt");
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    if (line.find(names[i]) != string::npos) {
                        cout << line << endl;
                        break;
                    }
                }
                file.close();
            } else {
                cout << "Error opening file." << endl;
            }
        }
        cout << "+------------------------------+" << endl;

        // Prompt user to play again
        cout << "Play again? (y/n): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}

