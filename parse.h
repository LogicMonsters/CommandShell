#ifndef __PARSE_H__
#define __PARSE_H__

vector<string> parse(string line){
  size_t i = 0; 
  string str;
  vector<string> vec;
  while(i < line.size()){ 
    if(line[i] == ' '){
      if(!str.empty()){
	vec.push_back(str);
	str.clear(); 
      }
    }else if(line[i] == '>'){
      if(!str.empty()){
      	vec.push_back(str);
	str.clear();
      }
      vec.push_back(">");
    }else if(line[i] == '<'){
      if(!str.empty()){
      	vec.push_back(str);
	str.clear();
      }
      vec.push_back("<");
    }else if(line[i] == '2'){
      if(line[i+1] == '>'){
	if(!str.empty()){
	  vec.push_back(str);
	  str.clear();
	}
	vec.push_back("2>");
	i++;
      }else{
	str.push_back('2');
      }
    }else if(line[i] == '|'){
      if(!str.empty()){
	vec.push_back(str);
	str.clear();
      }
      vec.push_back("|");
      rd.incrementPipe();
    }else if(line[i] == '\\'){
      if(line[i+1] == ' '){
	str.push_back(line[i+1]);
	i++;
      }else{
	str.push_back('\\');
      }
    }else{ 
      str.push_back(line[i]);
    }
    i++;
  }
  if(!str.empty()){
    vec.push_back(str);
    str.clear();
  }
  /*  for test */ 
  /*
  for(size_t j = 0 ; j < vec.size(); j++){
    cout << "vec[" <<j << "] = " << vec[j] << endl;
  }
  */
  return vec; 
}

#endif
