#include <iostream>
#include "BinaryList.h"
using namespace std;

/*void printTree(const char &data) {
    cout << data << ends;
}*/

int main() {
  BinaryList<char> test('a');
  //BinaryNode<char> t0('b');
  //BinaryNode<char> t1('c');
  //test.preOrder(printTree);
  unsigned int a = test.getDepth();
  BinaryList.clear();
	char b = *test.getRoot();
  return 0;
}
