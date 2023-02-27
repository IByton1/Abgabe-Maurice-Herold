// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>

using namespace std;


int multiple_of_3_or_5(const int n) {
  int sum = 0;
  for(int i = 0; i < n; i++){
    if(i % 3 == 0 || i % 5 == 0){
        sum += i;
    }
  }
  return sum;
}

/*************** end assignment ***************/

int main() {
  cout << multiple_of_3_or_5(1000) << endl;
}
