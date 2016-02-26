#ifndef __PROMPT_H__
#define __PROMPT_H__
const int max_path_len = 1024;
void prompt(){
  char pathName[max_path_len];
  getcwd(pathName,max_path_len);
  cout << "myShell:" << pathName << " $ ";
}

#endif
