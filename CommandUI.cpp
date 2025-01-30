#include "CommandUI.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>

const std::string RESET_COLOR = "\033[0m";


void print_cell(const Disc &cell) {
  if (cell == RED) {
    std::cout << "\u001b[48;5;7m" << "🔴 ";
  }
  else if (cell == BLUE) {
    std::cout << "\u001b[48;5;7m" << "🔵 ";
  }
  else {
    // print gray circle
    std::cout << "\u001b[48;5;7m" << "⚪ ";
  }
  // reset output color
  std::cout << RESET_COLOR;
}

void CommandUI_init(CommandUI *ui, Game *game) {
  ui->game = game;
}

void CommandUI_print_board(const CommandUI* ui) {
  Game *game = ui->game;
  for(int r = 0; r < Game_rows(game); ++r) {
    for(int c = 0; c < Game_columns(game); c++) {
      const Disc *cell = Game_cell(game, r, c);
      print_cell(*cell);
    }
    std::cout << std::endl;
  }
}


int handle_move_input(CommandUI *ui) {

  std::string col;
  std::cin >> col;
  int c = stoi(col);
  if (c < 0 || c >= Game_columns(ui->game)) {
    std::cout << "Invalid column!" << std::endl;
    return -1;
  }
  if (Game_col_available(ui->game, c)) {
      Disc d = RED;
      if (Game_player(ui->game) == 1){
        d = BLUE;
      }
      Game_make_move(ui->game, c, d);
        return c;
 }
  else {
    std::cout << "Out of bounds!" << std::endl;
    return -1;
  }
}

void handle_save_input(CommandUI *ui) {
  std::string filename;
  std::cin >> filename;
  std::ofstream out(filename);
  Game_save(ui->game, out);
}

void CommandUI_print_menu(const CommandUI *ui) {
  std::cout << "M column | Save = S <filename> | Quit = Q" << std::endl;
}

int CommandUI_input(CommandUI *ui) {
  std::cout << "Enter move: ";
  std::string move;
  std::cin >> move;
  // Make commands case insensitive by automatically converting to uppercase.
  std::transform(move.begin(), move.end(), move.begin(), ::toupper);
  
  if (move == "Q") {
    return -2;
  }
  else if (move == "S") {
    handle_save_input(ui);
  }
  else if (move == "M") {
    return handle_move_input(ui);
  }
  else {
    std::cout << "Invalid move!" << std::endl;
    return -1;
  }

  // If there was an input error, print a message, reset cin errors, and clear buffer.
  if (!std::cin) {
    std::cout << "Invalid input!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1;
  }
  return -1; // we should never get here
}

/*void CommandUI_play(CommandUI *ui) {
  int input = -1;
  int result = 0;
  CommandUI_print_board(ui);
  do {
    if (input != -1)
        Game_Switch_player(ui->game);
    CommandUI_print_menu(ui);
    input = CommandUI_input(ui);
    CommandUI_print_board(ui);
    if(input == -1)
        result = -1;
    else
      result = Game_is_over(ui->game, input);
  }
  while (result == 0);
  if (result == 1 ) {
    std::cout << "You Win!" << std::endl;
  }
  else if (result == 2) {
    std::cout << "Game over - Tie!" << std::endl;
  }
}*/
void CommandUI_play(CommandUI *ui) {
    int playerInput, gameState = 0;

    CommandUI_print_board(ui);

    while (true) {
        CommandUI_print_menu(ui);
        playerInput = CommandUI_input(ui);

        if (playerInput == -2) {  // Handle quit command
            std::cout << "Game exited by player." << std::endl;
            return;
        }

        if (playerInput == -1) {  // Invalid input, ask again
            continue;
        }

        CommandUI_print_board(ui);

        gameState = Game_is_over(ui->game, playerInput);
        if (gameState != 0) break;

        Game_Switch_player(ui->game);
    }

    if (gameState == 2) {
        std::cout << "You Win!" << std::endl;
    } else if (gameState == 1) {
        std::cout << "Game over - Tie!" << std::endl;
    }
}

