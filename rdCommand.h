#ifndef __RDCOMMAND_H__
#define __RDCOMMAND_H__
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
#endif
