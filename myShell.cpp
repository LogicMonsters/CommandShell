#include "myShell.h"
#include "RedirectInfo.h"
RedirectInfo rd;
#include "prompt.h"
#include "read.h"
#include "parse.h"
#include "specialCommand.h"
#include "sysCommand.h"
#include "rdCommand.h"

void executePipe(vector<string> vec, int pipeAmount, int pipe_fd[2]){
  vector<string> vec_pipe;
  pid_t pid;
  int state;
  int pipe_fd_new[2];
  for(size_t i = 0; i < vec.size(); i++){
    if(vec[i] != "|"){
      vec_pipe.push_back(vec[i]);
      vec.erase(vec.begin()+i);
      --i;
    }else{
      vec.erase(vec.begin()+i);
      break;
    }
  }
  const char * fileName = vec_pipe[0].c_str();
  char ** args = new char*[vec_pipe.size()+1];
  size_t k = 0;
  for(; k < vec_pipe.size(); k++){
    char * temp = new char[vec_pipe[k].length()+1];
    strcpy(temp,vec_pipe[k].c_str());
    args[k] = temp;
  }
  args[k] = NULL;
  if(pipeAmount > 0){
    if(pipe(pipe_fd_new)<0){
      cout<<"error : pipe failed"<<endl;
      return;
    }
  }
  pid = fork();
  if(pid == 0){
    if(pipeAmount == 0){    
      if(rd.getOut()){
	rd.dealWithOut();
      }
      close(pipe_fd[1]);
      close(fileno(stdin));
      dup2(pipe_fd[0],fileno(stdin));
      close(pipe_fd[0]);
    }else{
      close(pipe_fd[1]);
      close(fileno(stdin));
      dup2(pipe_fd[0],fileno(stdin));
      close(pipe_fd[0]);
      close(pipe_fd_new[0]);
      close(fileno(stdout));
      dup2(pipe_fd_new[1],fileno(stdout));
      close(pipe_fd_new[1]); 
    }
    execve(fileName,args,NULL);      
  }

  if(pid > 0){	
    if(pipeAmount > 0){
      executePipe(vec,pipeAmount-1,pipe_fd_new);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid, &state, WUNTRACED | WCONTINUED);
    for(size_t i = 0; i < vec_pipe.size()+1; i++){
      delete[] args[i];
    }
    delete[] args;
  }     
}
int forkChild(vector<string> vec){
  pid_t cpid,w;
  int status;
  vector<string> vec_pipe;
  for(size_t i = 0; i < vec.size(); i++){
    if(vec[i] != "|"){
      vec_pipe.push_back(vec[i]);
      vec.erase(vec.begin()+i);
      --i;
    }else{
      vec.erase(vec.begin()+i);
      break;
    }
  }
  const char * fileName = vec_pipe[0].c_str();
  char ** args = new char*[vec_pipe.size()+1];
  size_t k = 0;
  for(; k < vec_pipe.size(); k++){
    char * temp = new char[vec_pipe[k].length()+1];
    strcpy(temp,vec_pipe[k].c_str());
    args[k] = temp;
  }
  args[k] = NULL;
  int pipe_fd[2];
  int pipeAmount = rd.getPipeAmount(); 
  if(pipeAmount > 0){
    if(pipe(pipe_fd) < 0){
      cout<<"pipe command failed!"<<endl;
      return 1;
    }
  }
  cpid = fork();
  if(cpid > 0){
    if(pipeAmount>0){   
      executePipe(vec,pipeAmount-1,pipe_fd);
    }
    w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
    for(size_t i = 0; i < vec_pipe.size()+1; i++){
      delete[] args[i];
    }
    delete[] args;   
    if (w == -1) {
      cerr << "waitpid" << endl;
      exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)){
      cout << "Program exited with status " << WEXITSTATUS(status) << endl;
    }
    if (WIFSIGNALED(status)){
      cout << "Program was killed by signal " << WTERMSIG(status) << endl;
    }
  }else if(cpid == 0){   
    if(pipeAmount > 0){
      if(rd.getIn()){
	close(pipe_fd[0]);
	close(fileno(stdout));
	dup2(pipe_fd[1],fileno(stdout));
	close(pipe_fd[1]);
	rd.dealWithIn();
      }else{   
	close(pipe_fd[0]);
	close(fileno(stdout));
	dup2(pipe_fd[1], fileno(stdout));
	close(pipe_fd[1]);
      }    
    }else{
      if(rd.getIn()){
	rd.dealWithIn();
      }
      if(rd.getOut()){
	rd.dealWithOut();
      }
      if(rd.getErr()){
	rd.dealWithErr();
      }
    }
    execve(fileName,args,NULL);   
  }else{
    cerr << "creation of a child process was unsuccessful!!!" << endl;
    exit(EXIT_FAILURE);
  }
  return 1;
}
/*
void rdCommand(vector<string> &vec){
 for(size_t i = 0; i < vec.size(); i++){
    if(vec[i] == ">"){
      rd.setOut(true);
      rd.setOutputFile(vec[i+1]);
      vec.erase(vec.begin()+i);
      vec.erase(vec.begin()+i);
      --i;
    }
    if(vec[i] == "<"){
      rd.setIn(true);
      rd.setInputFile(vec[i+1]);
      vec.erase(vec.begin()+i);
      vec.erase(vec.begin()+i);
      --i;
    }
    if(vec[i] == "2>"){
      rd.setErr(true);
      rd.setErrName(vec[i+1]);
      vec.erase(vec.begin()+i);
      vec.erase(vec.begin()+i);
      --i;
    }
  }
}
*/
int execute(vector<string> vec, vector<string> & pathStack){
  rdCommand(vec);
  int res = specialCommand(vec, pathStack);
  if(res == 0){
    return 0;
  }
  if(res == 1){
    return 1;
  }
 
  int res2 = sysCommand(vec);
  if(res2 == 1){
    // command doesn't exist, end execution
    return 1;
  }
 
  return forkChild(vec);
}

void myShell(){
  int status = 1;
  vector<string> vec;
  string line;
  vector<string> pathStack;
 
  while(status){
    prompt();
    vec.clear();
    if(!read(line)){
      break;
    }
    rd.resetRdInfo();    
    vec = parse(line);
    status = execute(vec, pathStack);
  }
}

int main(void){
  myShell();
  return EXIT_SUCCESS;
}
