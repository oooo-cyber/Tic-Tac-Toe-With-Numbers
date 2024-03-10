#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Define a function called NumberList that returns a vector of integers
vector<int> NumberList() {
  // Create a vector Numbers and initialize it with values 1 to 9
  vector<int> Numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // Return the vector Numbers
  return Numbers;
}

// Define a function called DisplayNumbers that takes in three vectors of
// integers: Numbers, PickedNumbersPlayer1, and PickedNumbersPlayer2
void DisplayNumbers(vector<int> &Numbers, vector<int> &PickedNumbersPlayer1,
                    vector<int> &PickedNumbersPlayer2) {
  // Create a vector called remainingNumbers to store the numbers that have not
  // been picked by either player
  vector<int> RemainingNumbers;
  // Iterate through each number in the Numbers vector
  for (int i : Numbers) {
    // Check if the current number i is not present in both PickedNumbersPlayer1
    // and PickedNumbersPlayer2
    if (find(PickedNumbersPlayer1.begin(), PickedNumbersPlayer1.end(), i) ==
            PickedNumbersPlayer1.end() &&
        find(PickedNumbersPlayer2.begin(), PickedNumbersPlayer2.end(), i) ==
            PickedNumbersPlayer2.end()) {
      // If the current number i has not been picked by either player, add it to
      // the remainingNumbers vector
      RemainingNumbers.push_back(i);
    }
  }
  // Print the remaining numbers
  cout << "Numbers: ";
  for (int Num : RemainingNumbers) {
    cout << Num << " ";
  }
  cout << endl;
}

// Define a function called CheckSumEqual15 that takes in a vector of integers
// called Numbers and returns a boolean value
bool CheckSumEqual15(vector<int> &Numbers) {
  // Iterate through each index i in the Numbers vector
  for (size_t i = 0; i < Numbers.size(); i++) {
    // Iterate through each index j starting from i+1 in the Numbers vector
    for (size_t j = i + 1; j < Numbers.size(); j++) {
      // Iterate through each index k starting from j+1 in the Numbers vector
      for (size_t k = j + 1; k < Numbers.size(); k++) {
        // Check if the sum of Numbers[i], Numbers[j], and Numbers[k] is equal
        // to 15
        if (Numbers[i] + Numbers[j] + Numbers[k] == 15) {
          // If the sum is equal to 15, return true
          return true;
        }
      }
    }
  }
  // If no combination of three numbers adds up to 15, return false
  return false;
}

// Define a function called PlayerVersusPlayer that takes in a vector of
// integers called Numbers and returns a string
string PlayerVersusPlayer(vector<int> &Numbers) {
  // Create vectors to store the numbers picked by each player and an integer to
  // keep track of the current player
  vector<int> Player1Numbers;
  vector<int> Player2Numbers;
  int CurrentPlayer = 1;

  // Iterate through each index i in the Numbers vector
  for (size_t i = 0; i < Numbers.size(); i++) {
    // Display the remaining numbers available for selection by both players
    DisplayNumbers(Numbers, Player1Numbers, Player2Numbers);

    // Check which player's turn it is and prompt the respective player to
    // select a number from the list
    if (CurrentPlayer == 1) {
      // Player 1's turn
      cout << "Player 1's turn" << endl;
      string Player1SelectedNumber;
      do {
        // Validate the input to ensure it is a number from the list
        cout << "Select a number from the list: ";
        cin >> Player1SelectedNumber;
        if (all_of(Player1SelectedNumber.begin(), Player1SelectedNumber.end(),
                   [](char c) { return isdigit(c); })) {
          break;
        }
        cout << "Invalid input, Please enter a number from the list." << endl;
      } while (true);

      // Check if the selected number is valid and has not been picked by the
      // other player
      if (find(Numbers.begin(), Numbers.end(), stoi(Player1SelectedNumber)) !=
              Numbers.end() &&
          find(Player1Numbers.begin(), Player1Numbers.end(),
               stoi(Player1SelectedNumber)) == Player1Numbers.end() &&
          find(Player2Numbers.begin(), Player2Numbers.end(),
               stoi(Player1SelectedNumber)) == Player2Numbers.end()) {
        // Add the selected number to Player1Numbers and check if Player 1 wins
        Player1Numbers.push_back(stoi(Player1SelectedNumber));
        if (Player1Numbers.size() >= 3 && CheckSumEqual15(Player1Numbers)) {
          return "Player 1 wins!";
        }
        // Switch to Player 2's turn
        CurrentPlayer = 2;
      } else {
        cout << "Invalid input, Please enter a number from the list." << endl;
      }
    } else {
      // Player 2's turn
      cout << "Player 2's turn" << endl;
      string Player2SelectedNumber;
      do {
        // Validate the input to ensure it is a number from the list
        cout << "Select a number from the list: ";
        cin >> Player2SelectedNumber;
        if (all_of(Player2SelectedNumber.begin(), Player2SelectedNumber.end(),
                   [](char c) { return isdigit(c); })) {
          break;
        }
        cout << "Invalid input, Please enter a number from the list." << endl;
      } while (true);

      // Check if the selected number is valid and has not been picked by the
      // other player
      if (find(Numbers.begin(), Numbers.end(), stoi(Player2SelectedNumber)) !=
              Numbers.end() &&
          find(Player1Numbers.begin(), Player1Numbers.end(),
               stoi(Player2SelectedNumber)) == Player1Numbers.end() &&
          find(Player2Numbers.begin(), Player2Numbers.end(),
               stoi(Player2SelectedNumber)) == Player2Numbers.end()) {
        // Add the selected number to Player2Numbers and check if Player 2 wins
        Player2Numbers.push_back(stoi(Player2SelectedNumber));
        if (Player2Numbers.size() >= 3 && CheckSumEqual15(Player2Numbers)) {
          return "Player 2 wins!";
        }
        // Switch to Player 1's turn
        CurrentPlayer = 1;
      } else {
        cout << "Invalid input. Please enter a number from the list." << endl;
      }
    }
  }

  // If no player wins after all numbers are picked, it's a draw
  return "It's a draw.";
}

/* Define a function called ReadUserChoice that takes no arguments and returns
void */
void ReadUserChoice() {
  // Declare a variable to store the user's choice
  short Choice;
  cout << "Enter your choice : ";
  // Loop to repeatedly prompt the user for input until a valid choice is made
  do {
    string Input;
    cin >> Input;

    // Check if the input consists of only digits
    if (all_of(Input.begin(), Input.end(), [](char c) { return isdigit(c); })) {
      // Convert the input to an integer
      Choice = stoi(Input);
      if (Choice == 1) {
        // If the choice is 1, start a player versus player game
        vector<int> Numbers = NumberList();
        cout << PlayerVersusPlayer(Numbers) << endl;
        break; // Exit the loop
      } else if (Choice == 2) {
        // If the choice is 2, exit the function
        break; // Exit the loop
      } else {
        // If the choice is neither 1 nor 2, prompt the user to choose a valid
        // option
        cout << "Invalid choice. Please choose a valid choice from the menu: ";
      }
    } else {
      // If the input contains non-digit characters, prompt the user to choose a
      // valid option
      cout << "Invalid choice, Please choose a valid choice from the menu: ";
    }
  } while (true); // Loop until a valid choice is made
}

/* Define a function called NumberScrabble that takes no arguments and returns
void */
void NumberScrabble() {
  // Loop to repeatedly display the game menu and prompt the user for choice
  while (true) {
    cout << "** Number scrabble **" << endl;
    cout << "1) start game" << endl;
    cout << "2) exit" << endl;
    ReadUserChoice(); // Call the function to read and process the user's choice
    break;            // Exit the loop after processing the user's choice
  }
}

int main() {
  NumberScrabble(); // Call the function to start the number scrabble game
  return 0;
}
