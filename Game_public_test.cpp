/* Player_public_test.cpp
 *
 * Unit tests for the Simple and Human Euchre players
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2021-03-12
 */

#include "game.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
using namespace std;

// THESE TEST CASES WILL ONLY TELL YOU IF YOUR CODE COMPILES.
// YOU NEED TO WRITE YOUR OWN COMPREHENSIVE TEST CASES IN Player_tests.cpp

TEST(test_init_board) {
  Game game;
  Game_init(&game, 4, 4);
  ASSERT_EQUAL(4, Game_rows(&game));
  ASSERT_EQUAL(4, Game_columns(&game)); 
}
TEST(test_win_red) {
  Game game;
  Game_init(&game, 6, 7);
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(2, Game_is_over(&game, 0));
}
TEST(test_win_blue) {
  Game game;
  Game_init(&game, 6, 7);
  Game_make_move(&game, 0, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 0, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 0, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 0, BLUE);
  ASSERT_EQUAL(2, Game_is_over(&game, 0));
}
TEST(test_win_red_with_blue) {
  Game game;
  Game_init(&game, 6, 7);
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 1, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 1));
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 1, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 1));
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 1, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 1));
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(2, Game_is_over(&game, 0));
  
}
TEST(test_win_red_diagonal) {
  Game game;
  Game_init(&game, 6, 7);
  Game_make_move(&game, 0, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 0));
  Game_make_move(&game, 1, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 1));
  Game_make_move(&game, 1, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 1));
  Game_make_move(&game, 2, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 2));
  Game_make_move(&game, 2, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 2));
  Game_make_move(&game, 3, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 3));
  Game_make_move(&game, 2, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 2));
  Game_make_move(&game, 3, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 3));
  Game_make_move(&game, 4, RED);
  ASSERT_EQUAL(0, Game_is_over(&game, 4));
  Game_make_move(&game, 3, BLUE);
  ASSERT_EQUAL(0, Game_is_over(&game, 3));
  Game_make_move(&game, 3, RED);
  ASSERT_EQUAL(2, Game_is_over(&game, 3));
}


TEST_MAIN()
