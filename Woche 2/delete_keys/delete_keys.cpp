// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <cstddef>
#include <vector>
#include <iostream>

using namespace std;

/************** begin assignment **************/
// Implement a function which takes as input an sorted array and a key, and
// updates the array so that all occurrences of the input key have been removed
// and the remaining elements have been shifted left to fill the emptied
// indices. Return the number of remaining elements. Values beyond the last
// valid element are the same as in the original array.
// (Requirements: O(1) space, O(n) time)

inline size_t delete_keys(vector<int> &v, const int key)
{
  size_t i = 0;
  size_t j = 0;
  // Loop through the vector.
  while (i < v.size())
  {
    // If the current element is not equal to the key, update the vector by copying the current element to position j.
    if (v[i] != key)
    {
      v[j] = v[i];
      // Increment j to move to the next position in the updated vector.
      ++j;
    }
    // Increment i to move to the next element in the original vector.
    ++i;
  }
  // Return the number of elements in the updated vector.
  return j;
}

/*************** end assignment ***************/

int main()
{
  {
    vector<int> v;
    vector<int> vresult;
    int key = 1;
    auto valid_entries = delete_keys(v, key);
    assert(v == vresult);
    assert(valid_entries == 0);
  }
  {
    vector<int> v{1};
    vector<int> vresult{1};
    int key = 2;
    auto valid_entries = delete_keys(v, key);
    assert(v == vresult);
    assert(valid_entries == 1);
  }
  {
    vector<int> v{1};
    vector<int> vresult{1};
    int key = 1;
    auto valid_entries = delete_keys(v, key);
    assert(v == vresult);
    assert(valid_entries == 0);
  }
  {
    vector<int> v{1, 2, 3};
    vector<int> vresult{2, 3, 3};
    int key = 1;
    auto valid_entries = delete_keys(v, key);
    assert(v == vresult);
    assert(valid_entries == 2);
  }
  {
    vector<int> v{1, 2, 2, 3};
    vector<int> vresult{1, 3, 2, 3};
    int key = 2;
    auto valid_entries = delete_keys(v, key);
    assert(v == vresult);
    assert(valid_entries == 2);
  }
  {
    vector<int> v{1, 2, 2, 3, 3};
    vector<int> vresult{1, 3, 3, 3, 3};
    int key = 2;
    auto valid_entries = delete_keys(v, key);
    assert(v == vresult);
    assert(valid_entries == 3);
  }
  {
    vector<int> v{2, 3, 5, 5, 7, 11, 11, 11, 13};
    vector<int> vresult{2, 3, 5, 5, 11, 11, 11, 13, 13};
    int key = 7;
    auto valid_entries = delete_keys(v, key);
    assert(v == vresult);
    assert(valid_entries == 8);
  }
  cout << "all tests passed" << endl;
}
