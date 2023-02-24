// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_map>

using namespace std;

// helper macros for timing
#define TIMERSTART(label)                                                      \
  std::chrono::time_point<std::chrono::system_clock> a##label, b##label;       \
  a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                       \
  b##label = std::chrono::system_clock::now();                                 \
  std::chrono::duration<double> delta##label = b##label - a##label;            \
  std::cout << #label << ": " << delta##label.count() << " seconds"            \
            << std::endl;

/************** begin assignment **************/
// compute the amount of all positive integer solutions to the equation
// a^3 + b^3 = c^3 + d^3 where a, b, c, and d are integers between 1 and n
// (1 <= n <= 500)

// an obvious brute force solution will just have four nested for loops
// this algorithm iterates through all possible values of a, b, c, and d
// and checks if that combination happens to work --> runtime is O(n^4)
int compute_amount_brute_force(const int n) {
  int amount = 0;
  for (int a = 1; a <= n; ++a) {
    for (int b = 1; b <= n; ++b) {
      for (int c = 1; c <= n; ++c) {
        for (int d = 1; d <= n; ++d) {
          if (a * a * a + b * b * b == c * c * c + d * d * d) {
            ++amount;
          }
        }
      }
    }
  }
  return amount;
}

// try to improve the time complexity
// (if you can't, try at least to improve the execution time)
int compute_amount(const int n) {
  int amount = 0;

  // create a map to store the count of each possible sum
  // this allows us to quickly check if a sum has already been seen
  unordered_map<int, int> sums;

  // iterate through all possible values of a and b
  for (int a = 1; a <= n; ++a) {
    for (int b = 1; b <= n; ++b) {
      int sum = a * a * a + b * b * b;

      // check if this sum has already been seen
      if (sums.count(sum) > 0) {
        // if it has, increment the count for this sum
        sums[sum]++;
      } else {
        // if it hasn't, add it to the map with a count of 1
        sums[sum] = 1;
      }
    }
  }

  // iterate through all possible values of c and d
  for (int c = 1; c <= n; ++c) {
    for (int d = 1; d <= n; ++d) {
      int sum = c * c * c + d * d * d;

      // check if this sum has already been seen
      if (sums.count(sum) > 0) {
        // if it has, add the count of this sum to the final amount
        amount += sums[sum];
      }
    }
  }

  return amount;
}

/*************** end assignment ***************/

int main() {
  // test correctness of implementation
  for (int n = 1; n < 100; ++n) {
    assert(compute_amount_brute_force(n) == compute_amount(n));
  }

  // compare execution times for n = 500
  int n = 500;
  cout << "n = " << n << endl;
  TIMERSTART(brute_force)
  int result_bf = compute_amount_brute_force(n);
  TIMERSTOP(brute_force)

  TIMERSTART(improved)
  int result = compute_amount(n);
  TIMERSTOP(improved)

  assert(result_bf == result);
}
