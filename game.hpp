#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <iostream>
#include <utility>

enum Disc{
    RED,
    BLUE,
    EMPTY
};
// Allow reading/writing discs to/from streams
std::ostream &operator<<(std::ostream &out, Disc slot);
std::istream &operator>>(std::istream &out, Disc &slot);



struct Game {
  int rows;
  int columns;
  int player;
  
  std::vector<std::vector<Disc>> cells;
};

////////////////////////////////////////////////////////////
// Declarations of "Public Interface" Game ADT Functions. //
////////////////////////////////////////////////////////////

// REQUIRES: rows > 3, width > 3
// EFFECTS: Initializes a Game with the given width and height. The specified
void Game_init(Game* game, int rows, int columns);

void Game_init(Game* game, std::istream &in);

void Game_save(const Game* game, std::ostream &out);

// EFFECTS: returns the rows in the game board
int Game_rows(const Game *game);

// EFFECTS: returns the columns in the game board
int Game_columns(const Game *game);


// EFFECTS: returns the player
int Game_player(const Game *game);

// REQUIRES: 0 <= x < Game_columns(game), 0 <= y < Game_rows(game)
// EFFECTS: Returns true if (x,y) is the position of a valid cell.
bool Game_in_bounds(const Game* game, int x, int y);

// REQUIRES: 0 <= col < Game_width(game)
// EFFECTS: Returns true if col has an empty cell available.
bool Game_col_available(const Game* game, int col);

// EFFECTS: Switches the player
void Game_Switch_player(Game *game);

// EFFECTS: Returns 1 if a player has connected 4.
//          Returns 0 if the game is not over.
//         Returns 2 if the game is a draw.
int Game_is_over(const Game* game, int move);

// EFFECTS: Returns 1 if all cells are full.
//          Returns 0 otherwise.
int Game_is_tie(const Game* game);

// REQUIRES: 0 <= col < Game_width(game)
// EFFECTS: Makes a move for the current player in the given column.
bool Game_make_move(Game *game, int col, Disc d);

// REQUIRES: Game_in_bounds(x,y)
// EFFECTS: Returns a pointer to the Disc at (x,y). The Disc may
//          not be modified through the pointer.
const Disc *Game_cell(const Game* game, int x, int y);



#endif


