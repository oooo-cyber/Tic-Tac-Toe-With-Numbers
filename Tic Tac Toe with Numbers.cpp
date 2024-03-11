#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Define a function called DisplayBoard that takes a reference to a 2D vector
// of integers (Board) and returns void
void DisplayBoard(const vector<vector<int>> &Board) {
  // Display the column indices
  cout << "   0   1   2" << endl;
  // Loop through the rows of the board
  for (int i = 0; i < 3; ++i) {
    cout << i << " "; // Display the row index

    // Loop through the columns of the board
    for (int j = 0; j < 3; ++j) {
      // Check if the cell is empty (-1) or contains a number
      if (Board[i][j] == -1) {
        cout << "   "; // Display an empty space
      } else {
        cout << " " << Board[i][j] << " "; // Display the number in the cell
      }

      // Display vertical separator between columns
      if (j < 2) {
        cout << "|";
      }
    }

    cout << endl; // Move to the next line after displaying a row

    // Display horizontal separator between rows
    if (i < 2) {
      cout << "  -----------" << endl;
    }
  }
}

// Define a lambda function called isValidNumber that takes a reference to a
// string (Input) and returns a boolean value to validate the entered numbers
auto isValidNumber = [](const string &Input) {
  // Check if all characters in the input are digits
  return all_of(Input.begin(), Input.end(), [](char c) { return isdigit(c); });
};

// Define a lambda function called isValidRowColumn that takes an integer input
// and returns a boolean value
auto isValidRowColumn = [](int Input) {
  // Check if the input is within the range [0, 2]
  return Input >= 0 && Input <= 2;
};

// Define a function called isWinner that takes a reference to a 2D vector of
// integers (Board), an integer (Player), and a reference to a set of integers
// (PlayerNumbers), and returns a boolean value
bool isWinner(const vector<vector<int>> &Board, int Player,
              const set<int> &PlayerNumbers) {
  // Check for winning combinations in rows and columns
  for (int i = 0; i < 3; ++i) {
    int RowSum = 0;
    int ColumnSum = 0;
    for (int j = 0; j < 3; ++j) {
      RowSum += Board[i][j]; // Calculate the sum of numbers in the current row
      ColumnSum +=
          Board[j][i]; // Calculate the sum of numbers in the current column
    }
    if (RowSum == 15 || ColumnSum == 15) {
      return true; // If the sum of numbers in a row or column is 15, the player
                   // wins
    }
  }

  // Check for winning combinations in diagonals
  int Diagonal1 =
      Board[0][0] + Board[1][1] +
      Board[2][2]; // Calculate the sum of numbers in the main diagonal
  int Diagonal2 =
      Board[0][2] + Board[1][1] +
      Board[2][0]; // Calculate the sum of numbers in the other diagonal
  if (Diagonal1 == 15 || Diagonal2 == 15) {
    return true; // If the sum of numbers in any diagonal is 15, the player wins
  }

  return false; // If no winning combination is found, the player does not win
}

// Define a function called PlayerTurn that takes a reference to an integer
// (Player), a reference to a set of integers (PlayerNumbers), and a reference
// to a 2D vector of integers (Board) and returns void
void PlayerTurn(int &Player, set<int> &PlayerNumbers,
                vector<vector<int>> &Board) {
  string Input;
  int Number;
  int Row, Column;

  // Prompt the player to choose a number to place on the board
  cout << "Player " << Player << ", choose a number to place on the board: ";

  // Validate and process the chosen number
  do {
    cin >> Input;
    if (isValidNumber(Input)) {
      Number = stoi(Input);
      if (PlayerNumbers.count(Number) == 0) {
        cout << "Invalid input, Please enter a number from the list: ";
      } else {
        break;
      }
    } else {
      cout << "Invalid input, Please enter a valid number: ";
    }
  } while (true);

  PlayerNumbers.erase(
      Number); // Remove the chosen number from the available numbers

  // Prompt the player to enter the row to place the number
  do {
    cout << "Enter the row to place your number: ";
    cin >> Input;
    if (isValidNumber(Input)) {
      Row = stoi(Input);
      if (!isValidRowColumn(Row)) {
        cout << "Invalid input, Please enter a valid row (0-2)" << endl;
      } else {
        break;
      }
    } else {
      cout << "Invalid input, Please enter a valid row (0-2)" << endl;
    }
  } while (true);

  // Prompt the player to enter the column to place the number
  do {
    cout << "Enter the column to place your number: ";
    cin >> Input;
    if (isValidNumber(Input)) {
      Column = stoi(Input);
      if (!isValidRowColumn(Column)) {
        cout << "Invalid input, Please enter a valid column (0-2)" << endl;
      } else {
        break;
      }
    } else {
      cout << "Invalid input, Please enter a valid column (0-2)" << endl;
    }
  } while (true);

  // Check if the selected cell is already occupied
  if (Board[Row][Column] != -1) {
    cout << "Cell already occupied. Try again." << endl;
    PlayerTurn(Player, PlayerNumbers,
               Board); // Recursively call PlayerTurn to prompt the player for
                       // input again
  } else {
    Board[Row][Column] = Number; // Place the chosen number in the selected cell
  }
}

// Define a function called TicTacToe that simulates the Tic Tac Toe game and
// returns void
void TicTacToe() {
  // Initialize the game board with empty cells
  vector<vector<int>> Board(3, vector<int>(3, -1));

  // Initialize the available numbers for each player
  set<int> Player1Numbers = {1, 3, 5, 7, 9};
  set<int> Player2Numbers = {0, 2, 4, 6, 8};

  int Turn = 0;   // Initialize the turn counter
  int Player = 1; // Initialize the starting player

  // Start the game loop
  while (true) {
    DisplayBoard(Board); // Display the current state of the game board

    // Prompt the current player to take their turn
    if (Player == 1) {
      PlayerTurn(Player, Player1Numbers, Board);
    } else {
      PlayerTurn(Player, Player2Numbers, Board);
    }

    // Check if the current player has won the game
    if (isWinner(Board, Player,
                 Player == 1 ? Player1Numbers : Player2Numbers)) {
      DisplayBoard(Board); // Display the final state of the game board
      cout << "Player " << Player << " wins!" << endl; // Announce the winner
      break;                                           // End the game loop
    }

    Turn++;                // Increment the turn counter
    if (Turn == 9) {       // Check if the game has ended in a draw
      DisplayBoard(Board); // Display the final state of the game board
      cout << "It's a draw!" << endl; // Announce the draw
      break;                          // End the game loop
    }

    Player = 3 - Player; // Switch to the next player for the next turn
  }
}

int main() {
  TicTacToe(); // Call the TicTacToe function to start the game
  return 0;
}
