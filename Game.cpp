#include "Game.hpp"
#include <cassert>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>


//////////////////////////////////////////////////////////////////////////
// Declarations for "private" Game ADT functions. Only used as helpers  //
// internally and not available as part of the "public" Game interface, //
// because they are not declared in the .hpp header file.               //
//////////////////////////////////////////////////////////////////////////
// A private overload of the Game_cell() function that may be used when the
// Game is not const-qualified and allows modification of cells via the returned
// (non-const-qualified) pointer.
Disc *Game_cell(Game *game, int x, int y);

/////////////////////////////////////////////////////////
// Definitions (implementations) of Game ADT Functions //
/////////////////////////////////////////////////////////


void Game_init(Game* game, int rows, int columns) {
    game->rows = rows;
    game->columns = columns;
    game->player = 0;
    game->cells = std::vector<std::vector<Disc>>(
        rows, std::vector<Disc>(columns, Disc{})
    );
    for(int r = 0; r<rows; r++) {
        for(int c = 0; c<columns; c++) {
            game->cells[r][c] = {EMPTY};
        }
    }
  }

void Game_init(Game *game, std::istream &is) {
  is >> game->rows;
  is >> game->columns;
  is >> game->player;
  game->cells = std::vector<std::vector<Disc>>(
        game->rows, std::vector<Disc>(game->columns, Disc{})
    );
  for(int x = 0; x < game->rows; ++x) {
    for(int y = 0; y < game->columns; ++y) {
      is >> *Game_cell(game, x, y);
    }
  }
}

void Game_save(const Game *game, std::ostream &out) {
  out << game->rows << " " << game->columns << " " << game->player<< std::endl;
  for(int x = 0; x < game->rows; ++x) {
    for(int y = 0; y < game->columns; ++y) {
      out << game->cells[x][y] << " ";
    }
    out << std::endl;
  }
}

void Game_Switch_player(Game* game)
{
    if (game->player == 0){
       game->player = 1;
    }
    else{
        game->player= 0;
    }
}

// EFFECTS: returns the player
int Game_player(const Game *game){
  return game->player;
}

int Game_rows(const Game *game) {
  return game->rows;
}

int Game_columns(const Game *game) {
  return game->columns;
}

bool Game_in_bounds(const Game* game, int x, int y) {
  return 0 <= x && x < game->rows && 0 <= y && y < game->columns;
}


int count_sequence(const Game *game, Disc d,  int x, int y, int dx, int dy) {
  int count = 0;
  while (Game_in_bounds(game, x, y) && *Game_cell(game, x, y) == d) {
    count++;
    x += dx;
    y += dy;
  }
  return count;
}

int Game_is_tie(const Game *game) {
  for (int i = 0; i < game->columns; i++) {
    if (Game_col_available(game, i)) {
      return 0;
    }
  }
  return 1;
}
// 1 is a Win
// 2 is a Tie
// 0 is no result yet
int  Game_is_over(const Game *game, int move) {
  // we made a move at col move, check if we won
  // check the col and figure out the row
  int row = 0;
  for (int i = 0; i < game->rows; i++) {
    if (game->cells[i][move] != EMPTY) {
      row = i;
      break;
    }
  }

  // check row
  int count = count_sequence(game, game->cells[row][move], row, move, 1, 0);
  count += count_sequence(game, game->cells[row][move], row, move, -1, 0) - 1;
  if (count >= 4) {
    return 2;
  }

  // check col

  count = count_sequence(game, game->cells[row][move], row, move, 0, 1);
  count += count_sequence(game, game->cells[row][move], row, move, 0, -1) - 1;
  if (count >= 4) {
    return 2;
  }
  // check diagonal
  count = count_sequence(game, game->cells[row][move], row, move, -1, 1);
  count += count_sequence(game, game->cells[row][move], row, move, 1, -1) - 1;
  if (count >= 4) {
    return 2;
  }
  // check other diagonal
  count = count_sequence(game, game->cells[row][move], row, move, 1, 1);
  count += count_sequence(game, game->cells[row][move], row, move, -1, -1) - 1;
  if (count >= 4) {
    return 2;
  }
  // check if all fields are full
  return Game_is_tie(game);
  
}


const Disc * Game_cell(const Game* game, int x, int y) {
  assert(Game_in_bounds(game, x, y));
  return &game->cells[x][y];
}

Disc * Game_cell(Game* game, int x, int y) {
  //assert(Game_in_bounds(game, x, y));
  //std::cout << "x: " << x << " y: " << y << std::endl;
  return &game->cells[x][y];
}


bool Game_col_available(const Game *game, int col) {
  // check if any of the rows in this column are available
  // start at the top since that would be faster - not 
  // tha it really matters since the board is so small
    for(int r = 0; r < game->rows; ++r) {
        const Disc *cell = Game_cell(game, r, col);
        if (*cell == EMPTY) {
            return true;
        }
    }
    return false;
}



bool Game_make_move(Game *game, int col, Disc d) {
  // check if any of the rows in this column are available
  // if available, then make the move at the last available row
  for(int r = game->rows-1; r >= 0 ; --r) {
    Disc *cell = Game_cell(game, r, col);
    if (*cell == EMPTY) {
      *cell = d;
      return true;
    }
  }
  return false;
}
///////////////////////////////////////////
// Definitions of Cell stream operations //
///////////////////////////////////////////

std::ostream &operator<<(std::ostream &out, Disc cell) {
  out << static_cast<int>(cell) << " ";
  return out;
}

std::istream &operator>>(std::istream &in, Disc &cell) {
  int item; in >> item; cell = static_cast<Disc>(item);
  return in;
}



