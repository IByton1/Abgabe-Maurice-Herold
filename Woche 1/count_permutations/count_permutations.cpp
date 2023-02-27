// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

/************** begin assignment **************/
// given a smaller string s and a bigger string b, design an algorithm to count
// all permutation appearances of the shorter string within the longer string
// assumption: only the 26 characters from a to z are allowed in both strings
//
// example:
// s = abbc
// b = cbabadcbbabbcba
//     cbab
//           cbba
//              abbc
//                bcba
// answer: permutations of the shorter string s
//         appear 4 times in the longer string b

// An obvious brute force solution is to generate all permutations of s and then
// look for each in b. Since there are S! permutations, this will take O(S! * B)
// time, where S is the length of s and B is the length of b. This works, but
// it's an extraordinarily slow algorithm. It's actually worse than an
// exponential algorithm. If s has 14 characters, that's over 87 billion
// permutations. Add one more character into s and we have 15 times more
// permutations. -->  implement an algorithm that needs at most O(B * S^2) time
//
// Before you start coding: Try to find the places where the permutations appear
// on your own. Observe how you do this. This will help you to develop a decent
// algorithm quite easily.

int count_permutations(const string &s, const string &b) {
  int count = 0;
  int product_b = 1;
  int product_s = 1;

  // If b is shorter than s or s has length less than 1, return 0
  if(b.length() < s.length() || s.length() < 1){
      return count;
  }

  // Calculate the product of characters in s
  for(int i = 0; i < s.length(); i++){
    product_s *= s[i];
    }
  // Loop over all possible substrings of b of length s.length()
  for (int i = 0; i <= b.length() - s.length(); i++) {
    // Calculate the product of characters in the current substring of b
    for(int j = 0; j < s.length(); j++){
      product_b *= b[i+j];
    }
    // If the product of characters in the substring of b matches the product of characters in s, increment count
    if(product_b == product_s){
      count++;
    }
    // Reset the product_b variable for the next substring of b
    product_b = 1;
  }
  return count;
}

/*************** end assignment ***************/

int main() {
  // longer string is not a permutation of shorter string
  assert(count_permutations("cbabadcbbabbcba", "abbc") == 0);

  assert(count_permutations("xyz", "xyz") == 1);
  assert(count_permutations("xyz", "xzy") == 1);

  // no common permutations
  assert(count_permutations("abzc", "cbabadcbbabbcba") == 0);
  assert(count_permutations("", "cbabadcbbabbcba") == 0);
  assert(count_permutations("cbabadcbbabbcba", "") == 0);

  assert(count_permutations("abbc", "cbabadcbbabbcba") == 4);
  assert(count_permutations("abbc", "cbabadcbbabbcbabaabccbabc") == 7);

  string s = "cat";
  string b =
      "ydwztctaaaatxocabnpgcircgysctattacqtklzypxzqtvmwejcbvqhgljulsopnldoifefp"
      "kjnvipxkfnamdsacaxosactbrnioabfxixseyetzackxhmuqnpjwfzesjwktacatfqlxxmqb"
      "jnaceobxyvqahrjdofrdhhciatcgaoueybnqsklwhfkzvltcaiacty";
  assert(count_permutations(s, b) == 9);

  // some longer word
  s = "Psychotomimetic";
  b = "PsychoxtomimetiPsycotomimehticcunyaschPoetcomyimtixkjnvipxkfnamdsacaxosa"
      "ctbrnioabfxixseyetzackxhmuqunyaschePocomtyimti";
  assert(count_permutations(s, b) == 3);

  cout << "all tests passed" << endl;
}

