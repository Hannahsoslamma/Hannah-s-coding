#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

class IFDParser{
	public:
        IFDParser();
        void tokenIt();
        void eatToken();
        string getNext();
        void trim(string& s);
        void printTokens();
        //To load any game file
        void setGameFile(const string& filename);
	private:
		int pos;
		string gameFile;
        vector<string> tokenVec;
};
