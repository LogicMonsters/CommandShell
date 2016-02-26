#ifndef __SPECIALCOMMAND_H__
#define __SPECIALCOMMAND_H__
void cd(string path){
  if(chdir(path.c_str()) != 0){
    prompt();
    cerr << strerror(errno) << endl;
  }
}

int pushd(vector<string> vec,vector<string> & pathStack){
  if(vec.size() == 2){
    cd(vec[1]);
  }
  char pathName[max_path_len];
  getcwd(pathName,max_path_len);
  pathStack.push_back(pathName);
  return 1;
}

int popd(vector<string> & pathStack){
  if(pathStack.empty()){
    prompt();
    cerr << "path stack is empty!"<<endl;
  }else{
    string topOfPathStack = pathStack.back();
    cd(topOfPathStack);
    pathStack.pop_back();
  }
  return 1;
}

int dirstack(vector<string> & pathStack){
  for(size_t j = 0 ; j < pathStack.size(); j++){
    prompt();
    cout << pathStack[j] << endl;
  }
  return 1;
}



int about(){
  prompt();
  cout <<"This is a simulation of shell - Qing Guo" <<endl;
  return 1;
}

int specialCommand(vector<string> & vec,  vector<string> & pathStack){
  if(vec.empty()){
    return 1;
  }
  if(vec[0] == "exit"){
    return 0;
  }
  if(vec[0]== "about"){
    return about();
  }
  if(vec[0] == "cd"){
    if(vec.size() == 2){
      cd(vec[1]);
    }
    return 1;
  }
  if(vec[0] == "pushd"){
    return pushd(vec,pathStack); // return 1
  }
  if(vec[0] == "popd"){
    return popd(pathStack);
  }

  if(vec[0] == "dirstack"){
    return dirstack(pathStack);
  }
  return 2;
}

#endif
