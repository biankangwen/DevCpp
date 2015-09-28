#include <iostream>
#include <stdlib.h>
#include "mysql_escape.h"

using namespace std;

void test1() {
  string a = "\'xx\"";
  string b = EscapeString2(a);
  
  printf("a:%s\n", a.c_str());
  printf("b:%s\n", b.c_str());
  system("PAUSE");
}

void test2() {
  for(int i=0;i<10;i++) {
    printf("j:%d\n",i%3);
    time_t t = time(NULL);
    printf("time:%u\n",(unsigned int)t);
    printf("t:%sxx\n", ctime(&t));
  }  
  system("PAUSE");
}

int main(int argc, char *argv[])
{
  test1();
  test2();
  
  return 0;
}
