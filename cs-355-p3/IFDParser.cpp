#include <iostream>
#include "IFDParser.h"


IFDParser::IFDParser()
{
    pos = 0;
    gameFile = "";
}

void IFDParser::setGameFile(const string& filename)
{
    gameFile = filename;
    pos = 0;
    tokenVec.clear();
    tokenIt();
}

void IFDParser::tokenIt()
{
    string token ="";
    string nextLine;
    char c;

    ifstream inFile(gameFile);

    while(!inFile.eof()){
        getline(inFile, nextLine);
        trim(nextLine); // removes whitespace from the front and end of tocken
        c=nextLine[0]; // reads first character to determine action

        //dump any comment or blank line (all comments exist alone on their lines)
        if(c=='%' || nextLine == ""){
            //do nothing
        }
        else{
            //tokenize the entire line
            //cout<<nextLine<<endl;
            for(int i=0; i<nextLine.length(); i++){
                if(nextLine[i] == '>'){
                    token = token + nextLine[i];
                    if(token !="\n" && token !="" && token !=" " && token !="\t"){
                        tokenVec.push_back(token);
                    }
                    token = "";
                }
                else if(nextLine[i]=='<'){
                    if(token !="\n" && token !="" && token !=" " && token !="\t"){
                        tokenVec.push_back(token); // add to the end of a vector
                    }
                    token = "";
                    token = token + nextLine[i];
                }
                else{
                    token = token + nextLine[i];
                }
            }
        }
    }//while !eof
    inFile.close();
    return;
}// end of tokenIt()

void IFDParser::eatToken()
{
    pos++;
}

string IFDParser::getNext(){
    return tokenVec[pos];
}

//helper function for trimming a string's white space
void IFDParser::trim(string& s)
{
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);
    p = s.find_last_not_of(" \t");
    if (string::npos != p)
    {
        s.erase(p+1);
    }
}

void IFDParser::printTokens()
{
    cout<<":::Printing the Tokens in Order:::"<<endl;
    for(int i=0; i<tokenVec.size(); i++){
        cout<<i<<": "<<tokenVec[i]<<endl;
    }
}
