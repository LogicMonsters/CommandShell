#ifndef __READ_H__
#define __READ_H__

int read(string & line){
  if(getline(cin,line)){
    return 1;
  }
  return 0;
}

#endif
