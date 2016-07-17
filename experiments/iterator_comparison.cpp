#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, char** argv) {
  // Get Test Vector Size from User
  if(argc != 2) {
    cout << "Usage: " << argv[0] << " <test vector size (a natural number)>\n";
    return 0;
  }
  int array_size = atoi(argv[1]);
  cout << "Testing std iterator on vector of size " << array_size << endl;
  vector<int>test_array;

  // Fill the vector
  for(int i=1; i<=array_size; i++)
    test_array.push_back(i);

  // Test a standard library iterator
  vector<int>::iterator it = test_array.begin();
  time_t start_time = clock();
  while(array_size != (*it))
    it++;
  time_t end_time = clock() - start_time;

  cout << "C++ Standard Iterator: " << end_time << endl;
  return 0;
}
