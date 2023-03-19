// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>

using namespace std;

// helper macros for timings
#define TIMERSTART(label)                                                \
  std::chrono::time_point<std::chrono::system_clock> a##label, b##label; \
  a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                      \
  b##label = std::chrono::system_clock::now();                                \
  std::chrono::duration<double> delta##label = b##label - a##label;           \
  std::cout << #label << ": " << std::setprecision(4) << delta##label.count() \
            << " seconds" << std::endl;

// parse input file and create baskets vector
vector<set<string>> get_baskets(const string &file_name)
{
  ifstream ifs(file_name);
  if (ifs.fail())
  {
    cerr << "failed to open " << file_name << endl;
    exit(-1);
  }
  string line;
  string word;
  vector<set<string>> baskets;
  while (getline(ifs, line))
  {
    stringstream iss(line);
    set<string> basket;
    while (iss >> word)
      basket.insert(word);
    baskets.push_back(basket);
  }
  return baskets;
}

// count the common items between two sets of words
size_t intersection_count(const set<string> &b1, const set<string> &b2)
{
  vector<string> v;
  set_intersection(begin(b1), end(b1), begin(b2), end(b2),
                   std::back_inserter(v));
  return v.size();
}

/************** begin assignment **************/
// The "vector baskets" contains 5000 baskets of fruits, for example baskets[5]
// contains the following fruits {Coconut, Watermelon, Apricot}.
// The "vector preferences" contains preferences for fruits of 1000 people, for
// example the person in preferences[2] prefers {Strawberry, Melon, Avocado,
// Jackfruit}. Count the baskets for each person that have at least 3 fruits of
// a person's preferences. A basket can contain 3 to 7 different (unique)
// fruits. Also the preferences of the persons are between 3 to 7 different
// (unique) fruits. There are only 28 different fruits.

// A naive solution uses sets of strings to compute intersections between
// baskets and preferences.
// It also iterates over all baskets for each user.
vector<size_t> count_matches_naive(const vector<set<string>> &baskets,
                                   const vector<set<string>> &preferences)
{
  // matches_count contains the matches count for each person
  vector<size_t> matches_count(
      preferences.size()); // create vector of all zeros
  // iterate over all persons
  for (size_t i = 0; i < preferences.size(); ++i)
  {
    // iterate over all possible baskets
    for (const auto &basket : baskets)
    {
      // if a basket contains at least 3 fruits of a person's preferences, then
      // we have a match
      if (intersection_count(preferences[i], basket) >= 3)
      {
        matches_count[i]++;
      }
    }
  }
  return matches_count;
}

// TODO: implement a "fast matches counter" using bit operations
// Voluntary (not required): If you are really interested in speeding up the
// code, also develop a strategy to avoid iterating over all the baskets each
// time. (In a real speed competition this would be essential for winning!)
// helper function to create the mapping of fruits to integers
unordered_map<string, int> create_fruit_map()
{
  unordered_map<string, int> fruit_map;
  vector<string> fruits = {
      "Nectarine", "Mango", "Mandarin", "Lime", "Plum", "Watermelon", "Blueberry",
      "Pineapple", "Cherry", "Orange", "Strawberry", "Papaya", "Avocado", "Raspberry",
      "Banana", "Peach", "Lemon", "Apricot", "Pomegranate", "Grapefruit", "Pear",
      "Starfruit", "Jackfruit", "Coconut", "Melon", "Kiwi", "Apple", "Grape"};

  for (size_t i = 0; i < fruits.size(); i++)
  {
    fruit_map[fruits[i]] = i;
  }
  return fruit_map;
}

// function to convert the baskets and preferences to bitsets
vector<bitset<28>> convert_to_bitsets(const vector<set<string>> &data,
                                      const unordered_map<string, int> &fruit_map)
{
  vector<bitset<28>> bitsets;
  for (const auto &entry : data)
  {
    bitset<28> bits;
    // loop through each fruit in the basket
    for (const auto &fruit : entry)
    {
      // set the corresponding bit in the bitset to 1
      bits.set(fruit_map.at(fruit));
    }
    // add the completed bitset to the vector of bitsets
    bitsets.push_back(bits);
  }
  // return the vector of bitsets
  return bitsets;
}

vector<size_t> count_matches_fast(const vector<set<string>> &baskets,
                                  const vector<set<string>> &preferences)
{
  // create a map that maps each fruit string to an integer index
  unordered_map<string, int> fruit_map = create_fruit_map();
  // convert the baskets and preferences to bitsets
  vector<bitset<28>> bitset_baskets = convert_to_bitsets(baskets, fruit_map);
  vector<bitset<28>> bitset_preferences = convert_to_bitsets(preferences, fruit_map);

  // initialize a vector to keep track of the number of matches for each preference
  vector<size_t> matches_count(preferences.size());

  // loop through each preference bitset
  for (size_t i = 0; i < bitset_preferences.size(); ++i)
  {
    // loop through each basket bitset
    for (const auto &basket : bitset_baskets)
    {
      // count the number of overlapping bits between the preference bitset and the basket bitset
      if ((bitset_preferences[i] & basket).count() >= 3)
      {
        // if there are at least 3 overlapping bits, increment the corresponding element in matches_count
        matches_count[i]++;
      }
    }
  }
  // return the vector of match counts
  return matches_count;
}

/*************** end assignment ***************/

int main()
{
  vector<set<string>> baskets = get_baskets("baskets.txt");
  vector<set<string>> preferences = get_baskets("preferences.txt");

  TIMERSTART(naive)
  auto results_naive = count_matches_naive(baskets, preferences);
  TIMERSTOP(naive)

  TIMERSTART(fast)
  auto results_fast = count_matches_fast(baskets, preferences);
  TIMERSTOP(fast)

  assert(results_naive == results_fast);

  cout << "all tests passed" << endl;
}
