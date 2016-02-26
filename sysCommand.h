#ifndef __SYSTEMCOMMAND_H__
#define __SYSTEMCOMMAND_H__

vector<string> splitBy(char ch, char * path){
  vector<string> env;
  string p(path);
  string temp;
  size_t index;
  while((index = p.find(ch)) != string::npos){
    env.push_back(p.substr(0,index));
    p = p.substr(index+1);
  }
  return env;
}

// return full path!!! 
string findCommand(string command, vector<string> & env){
  DIR * pDIR;
  struct dirent * entry;
  string str;
  for(size_t i = 0; i < env.size(); i++){
    if((pDIR = opendir(env[i].c_str()))){ 
      while((entry = readdir(pDIR))){
	if(entry -> d_name == command){
	  str = env[i] + '/' +command;
	  closedir(pDIR);
	  return str;
	}
      }
    }
    closedir(pDIR);
  }
  // if can't find the command, return empty res
  return str;
}

int isCommand(vector<string> & vec){
  vector<string> env;
  char* pPath;
  pPath = getenv ("PATH");
  env = splitBy(':',pPath);
  string fullPath = findCommand(vec[0], env);
  if(!fullPath.empty()){ // if exists, it is full path
    vec[0] = fullPath; 
    return 1;
  }else{
    // command not found
    cout << "Command " << vec[0] << " not found" << endl;
    return 0;
  }
}

int sysCommand(vector<string> & vec){
  if(vec[0].find('/') == string::npos){
    // dosen't have '/', check whether command exist?         
    // it is a system command, assign full path to vec[0] and pass vec[0] into forkChild(); 
    if(!isCommand(vec)){
      // not a system command, return 1 to end execution
      return 1;
    }
  }else{
    // have '/'
    //check whether file exists?
    ifstream fs;
    fs.open(vec[0].c_str());
    // if exists, pass vec[0] into fokChild();
    if(!fs.good()){
      // doesn't exist, return 1 to continue next loop
      cout<< vec[0] <<": No such file or directory" << endl;    
      return 1;
    }
    fs.close();
  }
  return 2;
}
#endif
