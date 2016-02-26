#include "myShell.h"
#include "RedirectInfo.h"
RedirectInfo rd;
#include "parse.h"

int main (void){
  vector<string> vec;
  string line;
  while(getline(cin,line)){
    vec = parse(line);
    vector<string>::iterator it = vec.begin(); 
    while(it != vec.end()){
      cout << *it <<endl;
      ++it;
    }
  }
  return EXIT_SUCCESS;
}
