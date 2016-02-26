#ifndef __REDIRECTINFO_H__
#define __REDIRECTINFO_H__
class RedirectInfo{
  bool in; 
  bool out;
  bool err;
  string inputFile;
  string outputFile;
  string errName;
  int pipeAmount;
  int pipe_fd[2];
public:
  RedirectInfo():in(false),out(false),err(false),pipeAmount(0){}
  void resetRdInfo(){
    in = false;
    out = false;
    err = false;
    inputFile = "";
    outputFile = "";
    errName = "";
    pipeAmount = 0;
  }
  void incrementPipe(){
    pipeAmount++;
  }
  void decrementPipe(){
    if(pipeAmount>0){
      pipeAmount--;
    }
  }
  int getPipeAmount(){
    return pipeAmount;
  }
  void setPipe_fd(int _pipe_fd[2]){
    pipe_fd[0] = _pipe_fd[0];
    pipe_fd[1] = _pipe_fd[1];
  }
   int* getPipe_fd(){
     return pipe_fd;
   }
  void dealWithIn(){
    int in_fd = open(inputFile.c_str(),O_CREAT|O_RDONLY,0666);
    close(fileno(stdin));
    dup2(in_fd,fileno(stdin));
    close(in_fd);
  }
  void dealWithOut(){
    int out_fd = open(outputFile.c_str(),O_WRONLY|O_CREAT|O_TRUNC,0666);
    close(fileno(stdout));
    dup2(out_fd,fileno(stdout));
    close(out_fd);
  }
  void dealWithErr(){
    int err_fd = open(errName.c_str(),O_WRONLY|O_CREAT|O_TRUNC,0666);
    close(fileno(stderr));
    dup2(err_fd,fileno(stderr));
    close(err_fd);
  }
  void setIn(bool _in){
    in = _in;
  }
  bool getIn(){
    return in;
  }
  void setOut(bool _out){
    out = _out;
  }
  bool getOut(){
    return out;
  }
  void setErr(bool _err){
    err = _err;
  }
  bool getErr(){
    return err;
  }
  void setInputFile(string _inputFile){
    inputFile = _inputFile;
  }
  void setOutputFile(string _outputFile){
    outputFile = _outputFile;
  }
  void setErrName(string _errName){
    errName = _errName;
  }  
  
};


#endif
