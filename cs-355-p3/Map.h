#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#ifndef H_AREANODE
#define H_AREANODE
  #include "areaNode.h"
#endif // H_AREANODE

#ifndef H_AREA
#define H_AREA
  #include "Area.h"
#endif // H_AREA

#ifndef H_IFDPARSER
#define H_IFDPARSER
  #include "IFDParser.h"
#endif // H_IFDPARSER

#ifndef H_LINKDATA
#define H_LINKDATA
  #include "LinkData.h"
#endif // H_LINKDATA

using namespace std;

class Map{
	protected:
		vector<areaNode*> areasVec;
		int areacnt;

		//Here is the instance of IFDParser
	  	IFDParser parser;

		//Some additional class attributes here
        vector<LinkData*> linkVec;
		string nextToken;

		bool ifderr;

	public:
	    Map();
	    void buildMap();
		void makeArea();
		void makeLinks();
		void linkLinks();
		areaNode* getStart();
		//void print();
		int reverseLookUp(areaNode*);
        virtual void updateMap(nodeType<Item*>* temp) =0;

		friend ostream& operator<<(ostream&, Map&);
};
