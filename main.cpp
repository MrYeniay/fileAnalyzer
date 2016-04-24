#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <vector>

#define FILE_NAME "file_types.dat"


int getLineCount();
void matchFound(int, std::string);
int main()
{
    unsigned char x;
    unsigned int c;
    bool match;
    int i, sign_len=0,pos,j;
    int file_len = getLineCount() / 2;
    int sign_counter;

    std::string sign_file, buffer;
    std::string dene = "0x50";

    std::ifstream input ("Tablo.docx", std::ios::binary);
    std::ifstream fileP (FILE_NAME);

for(sign_counter = 0; sign_counter < file_len; sign_counter++){
    i=1;
    getline(fileP, sign_file);
    std::istringstream iss(sign_file);
    iss >> sign_len;
    sign_file=sign_file.substr(sign_file.find_first_of(" ")+1);

    getline(fileP, buffer);
    std::istringstream buff(buffer, std::ios::binary);
    //std::cout<<"Signature length: "<<sign_len<<std::endl<<"Signature file type: "<<sign_file<<std::endl;


    std::istringstream hex_chars_stream(buffer);
    std::vector<unsigned char> bytes;


    while (hex_chars_stream >> std::hex >> c){
        bytes.push_back(c);
    }


    while(input >> x){

            if(x == bytes[0]){
                for(j=1;j<sign_len;j++){
                    input >> x;

                    if(x == bytes[j] )
                        match = true;
                    else {
                        match = false;
                        break;
                    }
                }
                if(match == true){
                    break;
                }
            }
            else
        i++;
    }

    if(match)
        matchFound(i, sign_file);
    else
      //  std::cout<<std::endl<<"NO MATCH";

    input.clear();
    input.seekg(0, std::ios::beg);
}
    return 1;
}

int getLineCount(){
    std::ifstream fileP (FILE_NAME, std::ios::binary);
    std::string buffer;
    int countLine=0;

    if(fileP.is_open()){
        while(getline(fileP, buffer)){
            countLine++;
        }
    }
    else
        return 0;

    fileP.close();
    return countLine;
}

void matchFound(int line, std::string type){

    std::cout<<"Possible match on: "<<line<<".th character for "<<type<<std::endl;

}
