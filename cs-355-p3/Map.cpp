#include <iostream>

#ifndef H_MAP
#define H_MAP
#include "Map.h"
#endif //H_MAP

Map::Map() {
	areacnt = 0;
	ifderr = false;
	nextToken = "";
}
void Map::buildMap() {
	ifderr = false;
	parser.tokenIt();

	nextToken = parser.getNext();

	if(nextToken == "<game>") {
		parser.eatToken();
		nextToken = parser.getNext();
		while(nextToken != "</game>") { //consider what happens when run out of tokens && not error state
			if(nextToken == "<area>") {
				parser.eatToken();
				nextToken = parser.getNext();
				makeArea();
			}
			else if(nextToken == "<links>") {
				parser.eatToken();
				nextToken = parser.getNext();
				makeLinks();
			}
			else {
				cout<<"Parse Error Location 1"<<endl;
				ifderr = true;
				break;
			}
			parser.eatToken();
			nextToken = parser.getNext();
		}// while !</game>

		if(ifderr) {
			cout<<" :: ERROR :: IF Document Formatting Error"<<endl;
			cout<<"Game Loading Failed"<<endl;
			cout<<"General Area of Parsing Failure:"<<endl;
			cout<<"-------------------------------------"<<endl;
			cout<<nextToken<<endl;
			parser.eatToken();
			nextToken = parser.getNext();
			cout<<nextToken<<endl;
			parser.eatToken();
			nextToken = parser.getNext();
			cout<<nextToken<<endl;
			parser.eatToken();
			nextToken = parser.getNext();
			cout<<nextToken<<endl;
			cout<<"-------------------------------------"<<endl;
			return;
		}
	}
	else {
		cout<<" :: ERROR :: No \"<game>\" tag found."<<endl;
		cout<<"Game Loading Failed"<<endl;
	}

	//link up areas
	linkLinks();
}
void Map::makeArea() {
	string xstr;
	areaNode* tempNodePtr = new areaNode;

	while(nextToken != "</area>") {
		if(nextToken == "<desc>") {
			parser.eatToken();
			nextToken = parser.getNext();
			tempNodePtr->info.setDescription(nextToken);
		}
		else if(nextToken == "<feats>") {
			parser.eatToken();
			nextToken = parser.getNext();

			istringstream ss(nextToken);
			getline(ss, xstr, ',');
			tempNodePtr->info.setID(atoi(xstr.c_str()));

			getline(ss, xstr, ',');
			tempNodePtr->info.setGoal(atoi(xstr.c_str()));
		}
		else if(nextToken == "</desc>" || nextToken == "</feats>") {
			//do nothing
		}
		else {
			cout<<"Parse Error Location 2"<<endl;
			ifderr = true;
			break;
		}

		parser.eatToken();
		nextToken = parser.getNext();
	}//while !</area>

	//add area to vector
	areacnt++;
	areasVec.push_back(tempNodePtr);
} //end makeArea()

void Map::makeLinks() {
	string xstr;
	int u, d, l, r;
	while(nextToken != "</links>") {
		if(nextToken == "<linkset>") {
			parser.eatToken();
			nextToken = parser.getNext();

			LinkData* tempLDPtr = new LinkData;
			istringstream ss(nextToken);
			getline(ss, xstr, ',');
			u = atoi(xstr.c_str());
			getline(ss, xstr, ',');
			d = atoi(xstr.c_str());
			getline(ss, xstr, ',');
			l = atoi(xstr.c_str());
			getline(ss, xstr, ',');
			r = atoi(xstr.c_str());

			tempLDPtr->setDigits(u, d, l, r);
			linkVec.push_back(tempLDPtr);
		}
		else if(nextToken == "</linkset>") {
			//do nothing
		}
		else {
			cout<<"Parse Error Location 3"<<endl;
			ifderr = true;
			break;
		}
		parser.eatToken();
		nextToken = parser.getNext();
	}//while !</links>
}//makeLinks()

void Map::linkLinks() {
	for(int i=0; i<linkVec.size(); i++) {
		areasVec[i]->u = areasVec[(linkVec[i]->getDigit(0))-1];
		areasVec[i]->d = areasVec[(linkVec[i]->getDigit(1))-1];
		areasVec[i]->l = areasVec[(linkVec[i]->getDigit(2))-1];
		areasVec[i]->r = areasVec[(linkVec[i]->getDigit(3))-1];
	}
}


areaNode* Map::getStart() {
	return areasVec[0];  //returns a pointer to the first area listed
}

int Map::reverseLookUp(areaNode* addy) {
	for(int i=0; i<areasVec.size(); i++) {

		if(areasVec[i] == addy) {

			return i+1;

		}
	}
	//this should not happen
	cout << areasVec.size();
	return -1;
}

ostream& operator<<(ostream& osObject, Map& map)
{
	osObject<<"******************************************************************"<<endl;
	osObject<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
	osObject<<"******************************************************************"<<endl;
	for(int i=0; i<map.areasVec.size(); i++) {
		cout<<"This is area: "<<i+1<<endl;
		cout<<map.areasVec[i]->info.getDescription()<<endl;
		if(map.areasVec[i]->info.getID() == 1) {
			cout<<"Area is INSTADEATH."<<endl;
		}
		if(map.areasVec[i]->info.getGoal() == 1) {
			cout<<"Area is GOAL."<<endl;
		}
		cout<<"Connections:"<<endl;
		cout<<"\t u: Area #"<<map.reverseLookUp(map.areasVec[i]->u)<<endl;
		cout<<"\t d: Area #"<<map.reverseLookUp(map.areasVec[i]->d)<<endl;
		cout<<"\t l: Area #"<<map.reverseLookUp(map.areasVec[i]->l)<<endl;
		cout<<"\t r: Area #"<<map.reverseLookUp(map.areasVec[i]->r)<<endl;
	}
	return osObject;
}
