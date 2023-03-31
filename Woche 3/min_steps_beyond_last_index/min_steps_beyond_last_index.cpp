// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

using namespace std;

/************** begin assignment **************/
// The input is an array of n unsigned integers, where A[i] denotes the maximum
// you can advance from index i.
// Write a function to compute the minimum number
// of steps needed to advance beyond the last index of an array. If it's
// impossible to go beyond the last index of an array, your function should
// return 0.
// Optimal: O(n) time, O(1) space

// EXAMPLES
// Input: < 4, 1, 2, 3, 0, 2, 0 >
// Output: 3

// Input: < 4, 1, 2, 3, 0, 1, 0 >
// Output: 0

size_t min_steps_beyond_last_index(const vector<size_t> &A)
{
  // size of the vector
  size_t n = A.size();
  // if size is 0 or the firt element is 0 its impossible
  if (n == 0 || A[0] == 0)
  {
    return 0;
  }
  // if size is 1 need is 1 step
  else if (n == 1)
  {
    return 1;
  }
  size_t max_reach = A[0];
  size_t steps = A[0];
  size_t jumps = 1;
  // Start traversing vector
  for (size_t i = 1; i < n; i++)
  {
    // Check if value at current index guarantees jump to end
    if (A[i] >= n - i)
    {
      return jumps + 1;
    }
    // update max_reach
    max_reach = max(max_reach, i + A[i]);
    // we needed 1 step to get to the current index
    steps--;
    // check if steps left
    if (steps == 0)
    {
      // need to jump
      jumps++;
      // Check if the current index/position or lesser index
      // is the maximum reach point from the previous indexes
      if (i >= max_reach)
      {
        return 0;
      }
      // re-initialize the steps to the amount
      // of steps to reach maxReach from position i.
      steps = max_reach - i;
    }
  }
  // cannot go beyond the last index, return 0
  return 0;
}

/*************** end assignment ***************/

int main()
{
  {
    vector<size_t> v;
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {1};
    assert(min_steps_beyond_last_index(v) == 1);
  }
  {
    vector<size_t> v = {0};
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {3, 3, 1, 0, 2, 0, 1};
    assert(min_steps_beyond_last_index(v) == 4);
  }
  {
    vector<size_t> v = {3, 3, 1, 0, 2, 0, 0};
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {3, 2, 0, 0, 2, 0, 1};
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {2, 4, 1, 1, 0, 2, 3};
    assert(min_steps_beyond_last_index(v) == 3);
  }
  {
    vector<size_t> v = {2, 1, 1, 3, 0, 2, 0};
    assert(min_steps_beyond_last_index(v) == 4);
  }
  {
    vector<size_t> v = {4, 1, 2, 3, 0, 1, 0};
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {4, 1, 2, 3, 0, 2, 0};
    assert(min_steps_beyond_last_index(v) == 3);
  }
  {
    vector<size_t> v = {1, 1, 5, 1, 1, 1, 1, 4, 1, 1, 1};
    assert(min_steps_beyond_last_index(v) == 4);
  }
  {
    vector<size_t> v = {3, 0, 0, 4, 1, 1, 1, 4, 1, 1, 1};
    assert(min_steps_beyond_last_index(v) == 3);
  }
  cout << "all tests passed" << endl;
}
