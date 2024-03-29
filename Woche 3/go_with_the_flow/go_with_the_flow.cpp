// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// helper macros for timings
#define TIMERSTART(label)                                                \
  std::chrono::time_point<std::chrono::system_clock> a##label, b##label; \
  a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                      \
  b##label = std::chrono::system_clock::now();                                \
  std::chrono::duration<double> delta##label = b##label - a##label;           \
  std::cout << #label << ": " << std::setprecision(4) << delta##label.count() \
            << " seconds" << std::endl;

using namespace std;

struct Input
{
  string text;               // only words and spaces
  vector<size_t> word_sizes; // contains for each word in the text the amount of characters
  size_t longest_word;       // amount of characters in the longest word
};

struct Result
{
  size_t line_width;   // line width that produces the longest river
  size_t river_length; //  length of the longest river

  // for testing equality of results (ignore this)
  bool operator==(const Result &rhs) const
  {
    return line_width == rhs.line_width && river_length == rhs.river_length;
  }
};

// one could easily tune the io speed, but io is not critical here,
// so we don't care about its speed
Input get_input(const string &path)
{
  ifstream ifs(path);
  if (ifs.fail())
  {
    throw runtime_error("cannot open file " + path + "\n");
  }
  size_t words;
  ifs >> words;              // read amount of words
  vector<size_t> word_sizes; // contains the size of each word
  string word;
  string text;
  size_t longest_word = 0;
  while (ifs >> word)
  {
    text += word + " ";
    word_sizes.push_back(word.size());
    longest_word = max(longest_word, word.size());
  }
  text.resize(text.size() - 1);
  return Input{move(text), move(word_sizes), longest_word};
}

Result get_result(const string &path)
{
  size_t line_width;
  size_t river_length;
  ifstream ifs(path);
  if (ifs.fail())
  {
    throw runtime_error("cannot open file " + path + "\n");
  }
  ifs >> line_width;
  ifs >> river_length;
  return Result{line_width, river_length};
}

/************** begin assignment **************/

// Read the detailed description of the problem in "exercise_go_with_the_flow.pdf.
// This is an actual problem from the "icpc world finals 2018".
// So some of the best programmers tried to solve this under time pressure.
// If you need some hints, read: hints_for_solution.pdf
//
// If you are interested in seeing more icpc problems that were used in the
// world finals, see here:
// https://icpc.baylor.edu/worldfinals/problems
//
// In a real competition you would also have to write the boilerplate code
// to parse the input.
// You don't have to write the boilerplate code here to parse the input.
// Here, you try to accomplish the actual task of finding the line width
// where the input text contains the longest possible river.
// If more than one line width yields this maximum,
// take the shortest line width.
// In the original task there is a time limit of 12 seconds.
// You don't have a time limit.
// But be aware that naive solutions will run "forever".

/*
The algorithm uses Dynamic Programming to find the optimal arrangement of words on different lines, minimizing the maximum number of words per line.
The algorithm iterates over all possible line widths and incrementally calculates the minimum number of lines needed to arrange the words on the current width.
The longest river in the text is returned as the maximum number of words per line on the width with the highest count.
*/

Result find_longest_river(Input &input)
{
  // You have the following information to design your algorithm.
  // You don't have to use everything, use only what you need.

  // the actual text, text is cleaned and contains only words and spaces
  const string &text = input.text;
  // amount of characters in the longest word in the text
  const size_t longest_word = input.longest_word;
  // contains for each word in the text the amount of characters (same order of words as in the text)
  const vector<size_t> &word_sizes = input.word_sizes;
  // the amount of all words in the text
  const size_t words_count = input.word_sizes.size();

  // When I solved the problem, the following thing was important,
  // which is not clearly mentioned in the task description:
  // --> a new line never starts with a space
  //     (if you would have a space after a line break, ignore the space and continue with the next word)

  // should contain in the end the "minimal" optimal line width
  size_t line_width = longest_word; // line width can't be shorter than the longest word
  // should contain in the end the longest possible river
  size_t river_length = 0;

  // Calculate the sum of the lengths of all words and the length of the longest word in the text
  const vector<size_t> &len = input.word_sizes;
  int n = len.size();
  int sum = 0, max_len = 0;
  for (int i = 0; i < n; i++)
  {
    sum += len[i];
    max_len = max(max_len, static_cast<int>(len[i]));
  }

  // Initialize variables to store the best line width
  int res = -1, resw = 0;

  // Iterate over all possible line widths
  for (int w = max_len; w <= sum + n - 1; w++)
  {
    // Vector to store the number of lines needed at the current line width
    vector<int> r(n);
    // Vector to store the length of the current word in the current line
    vector<int> c(n);
    int cR = 0, cC = -1;

    // Loop to place each word in each line and count the number of lines needed
    for (int i = 0; i < n; i++)
    {
      // cC is the position where the next word should be placed, so it is increased by the length of the previous word plus a space
      cC += (len[i] + 1);

      // If the current position is greater than the line width, a new line needs to be started
      if (cC > w)
      {
        // The number of lines is increased by 1
        r[i] = r[i - 1] + 1;
        // The position of the current word is set at the beginning of the next line
        c[i] = len[i];
        // The starting position of the next line is updated
        cR = r[i];
        cC = c[i];
      }
      else
      {
        // If the word can be placed in the current line, the line is not changed and the position is updated
        r[i] = cR;
        c[i] = cC;
      }
    }

    // Vector to store the optimal number of words per line using dynamic programming
    vector<int> dp(n);
    int i = 0, result = 0;
    while (i < n && r[i] == 0)
    {
      // If the first line has only one word, the second line can start with any word in the second line
      if (i + 1 < n && r[i + 1] == 0)
      {
        dp[i] = 1;
        result = 1;
      }
      i++;
    }

    int prev = 0;
    for (; i < n - 1; i++)
    {
      // If the next word cannot fit on the current line, a new line needs to be started
      if (r[i + 1] > r[i])
        continue;

      // Set the optimal number of words for the current line
      dp[i] = 1;

      // Calculate the position of the last word on the previous line
      int curI = w * r[i] + c[i];

      // Move backwards to find the last word in the previous line that can be continued onto the current line
      while (c[prev] == w || w * r[prev] + c[prev] < curI - w - 1)
        prev++;

      // Calculate the position of the last word on the previous line that can be continued onto the current line
      int prevI = w * r[prev] + c[prev];

      // If the previous word ends at the position where the current word should start
      if (prevI == curI - w - 1)
      {
        dp[i] = max(dp[i], dp[prev] + 1);
        prev++;
        prevI = w * r[prev] + c[prev];
      }
      else if (prevI == curI - w)
      {
        dp[i] = max(dp[i], dp[prev] + 1);
      }

      if (prevI == curI - w + 1)
        dp[i] = max(dp[i], dp[prev] + 1);

      result = max(result, dp[i]);
    }

    // Update the variables to store the best line width and the longest possible river
    if (result > res)
    {
      res = result;
      resw = w;
    }
  }

  // Return the best line width and the longest possible river
  return Result{static_cast<size_t>(resw), static_cast<size_t>(res)};
}

/*************** end assignment ***************/

int main()
{
  // set data_dir to folder with test data
  string data_dir = "./F-gowithflow/";
  // test texts in task description
  {
    string text = "The Yangtze is the third longest "
                  "river in Asia and the longest in "
                  "the world to flow "
                  "entirely in one country";
    vector<size_t> word_sizes{3, 7, 2, 3, 5, 7, 5, 2, 4, 3, 3,
                              7, 2, 3, 5, 2, 4, 8, 2, 3, 7};
    Input input{move(text), move(word_sizes), 8};
    Result result = find_longest_river(input);
    Result correct_result{15, 5};
    assert(result == correct_result);
  }
  {
    string text = "When two or more rivers meet at "
                  "a confluence other than the sea "
                  "the resulting merged river takes "
                  "the name of one of those rivers";
    vector<size_t> word_sizes{4, 3, 2, 4, 6, 4, 2, 1, 10, 5, 4, 3, 3,
                              3, 9, 6, 5, 5, 3, 4, 2, 3, 2, 5, 6};
    Input input{move(text), move(word_sizes), 10};
    Result result = find_longest_river(input);
    Result correct_result{21, 6};
    assert(result == correct_result);
  }

  TIMERSTART(total_time_on_test_data);
  // test now the texts provided by the organisers of the competition
  {
    string secret = "secret-";
    for (int i = 1000; i < 1030; ++i)
    {
      string in = secret + to_string(i).substr(1, 4) + ".in";
      string ans = secret + to_string(i).substr(1, 4) + ".ans";
      Input input = get_input(data_dir + in);
      Result correct_result = get_result(data_dir + ans);
      Result result = find_longest_river(input);
      assert(result == correct_result);
      cout << in.data() << " passed\n";
    }
  }
  {
    string secret = "secret-";
    for (int i = 1031; i <= 1047; ++i)
    {
      string in = secret + to_string(i).substr(1, 4) + "-per.in";
      string ans = secret + to_string(i).substr(1, 4) + "-per.ans";
      Input input = get_input(data_dir + in);
      Result correct_result = get_result(data_dir + ans);
      Result result = find_longest_river(input);
      assert(result == correct_result);
      cout << in.data() << " passed\n";
    }
  }
  {
    string secret = "secret-";
    for (int i = 1048; i <= 1062; ++i)
    {
      string in = secret + to_string(i).substr(1, 4) + "-dk.in";
      string ans = secret + to_string(i).substr(1, 4) + "-dk.ans";
      Input input = get_input(data_dir + in);
      Result correct_result = get_result(data_dir + ans);
      Result result = find_longest_river(input);
      assert(result == correct_result);
      cout << in.data() << " passed\n";
    }
  }
  {
    Input input = get_input(data_dir + "secret-099-small.in");
    Result correct_result = get_result(data_dir + "secret-099-small.ans");
    Result result = find_longest_river(input);
    assert(result == correct_result);
    cout << "secret-099-small.in passed\n";
  }
  TIMERSTOP(total_time_on_test_data);

  return 0;
}
