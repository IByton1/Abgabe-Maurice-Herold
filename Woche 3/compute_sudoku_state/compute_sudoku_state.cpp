// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <iostream>

using namespace std;

/************** begin assignment **************/
// Sudoku is a popular logic-based combinatorial number placement puzzle. The
// objective is to fill a 9 x 9 grid with digits subject to the constraint that
// each column, each row, and each of the nine 3 x 3 sub-grids that compose the
// grid contains unique integers.
// In case you need an introduction to Sudoku:
// https://www.learn-sudoku.com/sudoku-rules.html

// We define three different states in which a Sudoku board can be.
enum class state
{
  invalid,
  valid,
  solved
};
// invalid --> board violates the Sudoku rules
// valid --> board corresponds to the Sudoku rules
// solved --> the puzzle is solved

// Note that the only valid characters are "123456789" and the space ' ' meaning
// an empty field.
// Note that we do not care if a board can actually be solved, we only check if
// it violates the rules, or is valid, or is in a solved state.
// Of course a solved board is also valid, but we only return solved.

// TODO: implement a function that returns the state of a Sudoku board

/*
Check if the length of the board string is 81, otherwise the board is invalid.
Check if each character in the board is either a digit from 1 to 9 or a space, otherwise the board is invalid.
For each row, column, and grid, count the number of occurrences of each digit from 1 to 9. If any digit appears more than once, then the board is invalid.
If there are any empty cells, then the board is valid but not solved.
If there are no empty cells, then the board is solved.
*/

state compute_sudoku_state(const string &board)
{
  if (board.length() != 81)
  {
    return state::invalid;
  }

  // If the length of the board string is not 81, then it is invalid.
  for (int i = 0; i < 81; i++)
  {
    char cell = board[i];
    if (cell != ' ' && (cell < '1' || cell > '9'))
    {
      return state::invalid;
    }
  }

  // Check if each character in the board string is either a digit from 1 to 9 or a space.
  // If any other character is found, the board is invalid.
  for (int i = 0; i < 9; i++)
  {
    int row_count[10] = {0};
    int col_count[10] = {0};
    int grid_count[10] = {0};
    for (int j = 0; j < 9; j++)
    {
      char row_cell = board[i * 9 + j];
      char col_cell = board[j * 9 + i];
      char grid_cell = board[(i / 3 * 3 + j / 3) * 9 + (i % 3 * 3 + j % 3)];
      if (row_cell != ' ')
      {
        row_count[row_cell - '0']++;
      }
      if (col_cell != ' ')
      {
        col_count[col_cell - '0']++;
      }
      if (grid_cell != ' ')
      {
        grid_count[grid_cell - '0']++;
      }
    }
    // If any digit appears more than once in a row, column or grid, then the board is invalid.
    for (int j = 1; j <= 9; j++)
    {
      if (row_count[j] > 1 || col_count[j] > 1 || grid_count[j] > 1)
      {
        return state::invalid;
      }
    }
  }
  // If the board has no empty cells, then it is solved.
  for (int i = 0; i < 81; i++)
  {
    if (board[i] == ' ')
    {
      return state::valid;
    }
  }

  return state::solved;
}

/*************** end assignment ***************/

int main()
{
  {
    string board = "274935168"
                   "198726435"
                   "563814729"
                   "356187294"
                   "419562873"
                   "782493516"
                   "821349657"
                   "947651382"
                   "63527894"; // invalid size
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "274935168"
                   "198726435"
                   "563814729"
                   "356187294"
                   "419562873"
                   "782493516"
                   "821349657"
                   "947651382"
                   "6352789412"; // invalid size
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "   9  1 4"
                   " 2  5 7  "
                   "     25 6"
                   "    194 5"
                   " 6574391 "
                   "4 1 26  8"
                   " 18375 4 "
                   " : 4  631" // |:|
                   " 4  6    ";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "586937124"
                   "129654783"
                   "734182596"
                   "372819465"
                   "865743912"
                   "491526308" // |0|
                   "618375249"
                   "257498631"
                   "943261857";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "586937124"
                   "129654783"
                   "734182596"
                   "372819465"
                   "865743912"
                   "4915263a8" // |a|
                   "618375249"
                   "257498631"
                   "943261857";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "145673829"
                   "389215674"
                   "762948135"
                   "296157483"
                   "814369752"
                   "573824961"
                   "957436218"
                   "628591347"
                   "431782596";
    assert(compute_sudoku_state(board) == state::solved);
  }
  {
    string board = "495287163"
                   "821369547"
                   "367145298"
                   "179854632"
                   "634972815"
                   "582613974"
                   "216438759"
                   "953721486"
                   "748596321";
    assert(compute_sudoku_state(board) == state::solved);
  }
  {
    string board = "145673829"
                   "381215674" // 38|1|
                   "762948135"
                   "296157483"
                   "814369752"
                   "573824961"
                   "957436218"
                   "628591347"
                   "431782596";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "145673829"
                   "38 215674"
                   "762948135"
                   "296157483"
                   "814369752"
                   "573824961"
                   "957436 18"
                   "628591347"
                   "431782596";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = " 4    897"
                   " 379   52"
                   "8 27  3  "
                   "9  4 7  6"
                   " 8  9  3 "
                   "6 3 18 49"
                   "  83 192 "
                   "26   4  3"
                   " 142596  ";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = " 4    897"
                   " 379   52"
                   "8 27  3  "
                   "9  6 7  6" // 9  |6|
                   " 8  9  3 "
                   "6 3 18 49"
                   "  83 192 "
                   "26   4  3"
                   " 142596  ";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = " 4    897"
                   " 379   52"
                   "8 27  3  "
                   "9  4 7  6"
                   " 8  9  3 "
                   "6 3 18 49"
                   "  83 193 " //   83 19|3|
                   "26   4  3"
                   " 142596  ";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "   9  1 4"
                   " 2  5 7  "
                   "     25 6"
                   "    194 5"
                   " 6574391 "
                   "4 1 26  8"
                   " 18375 4 "
                   "   4  631"
                   " 4  6    ";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = "2  9  1 4" // |2|
                   " 2  5 7  "
                   "     25 6"
                   "    194 5"
                   " 6574391 "
                   "4 1 26  8"
                   " 18375 4 "
                   "   4  631"
                   " 4  6    ";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "         "
                   "         "
                   "         "
                   "         "
                   "         "
                   "         "
                   "         "
                   "         "
                   "         ";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   4     "
                   "    5    "
                   "     6   "
                   "      7  "
                   "       8 "
                   "        9";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1     "
                   "    2    "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1     "
                   "    2    "
                   "     3   "
                   "      1  "
                   "      32 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1    7"
                   "    2 7  "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1     "
                   "    2    "
                   "     3   "
                   "  4   1  "
                   " 4     2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2 1     "
                   "  3      "
                   "   1     "
                   "    2    "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1 6   "
                   "   62    "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   " 5 1     "
                   "5   2    "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  cout << "all tests passed" << endl;
}
