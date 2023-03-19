// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

/************** begin assignment **************/
// Find k (= 8) brightest stars in a stream. To measure the brightness we use
// the visual magnitude (Vmag). The smaller Vmag the brighter the star appears
// to us. If you want to know more about Vmag read this:
// https://de.wikipedia.org/wiki/Scheinbare_Helligkeit
// We work with the file stars.txt. Look at the structure of the file, because
// you will parse it line by line to extract information about the stars.

struct Star
{
  string name; // name of the star
  double vmag; // stars brightness (the smaller vmag the brighter the star)
};

// You get the input file stream "ifs" to the "stars.txt" file and a parameter
// "k". "k" is the amount of the brightest stars we wan't to extract from the
// stream. Try to extract the "k" brightest stars in O(n * log(k)) time with
// O(log n) extra space.
vector<Star> find_k_brightest_stars(ifstream &ifs, const size_t k)
{
  vector<Star> result;

  auto comparator = [](const Star &a, const Star &b)
  {
    return a.vmag < b.vmag;
  };
  priority_queue<Star, vector<Star>, decltype(comparator)> min_heap(comparator);

  string line;
  while (getline(ifs, line))
  {
    if (line.empty() || line[0] == '#')
    {
      continue;
    }

    Star star;
    star.name = line.substr(0, 18);

    // remove trailing spaces from star name
    size_t endpos = star.name.find_last_not_of(" ");
    if (endpos != string::npos)
    {
      star.name = star.name.substr(0, endpos + 1);
    }

    star.vmag = stod(line.substr(64, 6));

    if (min_heap.size() < k)
    {
      min_heap.push(star);
    }
    else if (star.vmag < min_heap.top().vmag)
    {
      min_heap.pop();
      min_heap.push(star);
    }
  }

  while (!min_heap.empty())
  {
    result.push_back(min_heap.top());
    min_heap.pop();
  }

  reverse(result.begin(), result.end());

  return result;
}

/*************** end assignment ***************/

int main()
{
  string path = "stars.txt";
  ifstream ifs{path}; // open file as a stream
  if (ifs.fail())
  {
    cerr << "cannot find: " << path << endl;
    return 1;
  }
  size_t k = 8; // k brightest stars
  vector<Star> brightest_stars = find_k_brightest_stars(ifs, k);

  vector<Star> correct_stars{{"Sirius", -1.45}, {"Canopus", -0.62}, {"Arcturus", -0.05}, {"Rigil Kentaurus", -0.01}, {"Vega", 0.03}, {"Capella", 0.08}, {"Rigel", 0.18}, {"Procyon", 0.4}};

  // test correctness of solution
  assert(brightest_stars.size() == correct_stars.size());
  const double epsilon = 1.0e-12; // almost 0
  for (size_t i = 0; i < brightest_stars.size(); ++i)
  {
    assert(abs(brightest_stars[i].vmag - correct_stars[i].vmag) < epsilon);
    assert(brightest_stars[i].name == correct_stars[i].name);
  }

  // output brightest stars
  for (const auto &star : brightest_stars)
  {
    cout << star.name << endl;
    cout << star.vmag << endl;
    cout << endl;
  }
}
