#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;
const int OPS=4;
string ops[OPS] = {"+","-","*","/"};

void tolower(string &in){
  for(unsigned i=0;i<in.length();i++){
    if(in[i]<='Z' && in[i]>='A')
        in[i]=in[i]-('Z'-'z');
  }
} 

string parse(string line,vector<string> &stack,vector<string> &buffer){
    string result="";

    if(line.find("make")!=string::npos){
        bool found=0;
        for(int i=0;i<OPS;i++)
            if(line.find(ops[i])!=string::npos){
                found=1;break;
            }
        if(found)
           result = line.substr(line.find("make")+4,line.length()-1)+";";
        else
          buffer.push_back("double " + line.substr(line.find("make")+4,line.length()-1)+";");
    }
    else if(line.find("repeat")!=string::npos){
        result = "do\n{";
        stack.push_back("do");
    }
    else if(line.find("if")!=string::npos){
        size_t then = line.find("then");
        size_t ifloc = line.find("if")+2;
        if (then == string::npos){
            cout<<"Error, then not found";exit(-1);
        }
        result = "if ("+line.substr(ifloc,then-ifloc)+")";
        result += "\n" + parse(line.substr(then+4,line.length()-1),stack,buffer);
    }
    else if(line.find("call")!=string::npos){
        result = line.substr(line.find("call")+4,line.length()-1)+"();";
    }
    else if(line.find("until")!=string::npos){
        result = "}\nwhile("+line.substr(line.find("until")+5,line.length()-1)+");";
    }
    else if(line.find("begin")!=string::npos){
        result = "{";
    }
    else if(line.find("end")!=string::npos || line.find("return")!=string::npos){
        result = "}";
    }
    else if(line.find("stop")!=string::npos){
        result = "}";
    }
    else if(line.find(":")!=string::npos){
        string func="void "+line.substr(line.find(":")+1,line.length()-1)+"()";
        result = func+"\n{";
        buffer.push_back(func+";");
    }
    else if(line.find("message")!=string::npos){
        string data=line.substr(line.find("message")+7,line.length()-1);
        result="cout<<";
        bool in=0,o=0;
        for(unsigned i=0;i<data.length();i++){
            if(data[i]=='"' || data[i]=='\''){
                in=1-in;
                result += data[i];
            }
            else if(!in && (data[i]==' ' || data[i]=='\t')){
                o=0;
            }
            else if(!in && (data[i]!=' ' && data[i]!='\t')){
                if(!o)
                    result+="<<";
                result += data[i];
                o=1;
            }
            else if(in){
                result += data[i];
            }
                
        }
        result +=";";
    }

    tolower(result);
    return result;
}

int main(int argc, char *argv[]){

if(argc<2){
    cout<<"\nError: Incorrect number of arguments\n";  
    return -1;
}

ifstream fin(argv[1],ios::in);
ofstream fout(argv[2],ios::out);

if(!fin){
    cout<<"\nError: Input file not found\n";  
    return -1;
}

if(!fout){
    cout<<"\nError: Output file not found\n";  
    return -1;
}

string line,output="int main()\n{\n";
vector<string> stack,buffer;

while(!fin.eof()){
    getline(fin,line);
    output += parse(line,stack,buffer)+"\n";
}

for(unsigned i=0;i<buffer.size();i++){
    tolower(buffer[i]);
    output = buffer[i] + "\n" + output;
}

output = "#include<iostream>\nusing namespace std;\n\n" + output;

fout<<output;

fin.close();
fout.close();
return 0;
}
