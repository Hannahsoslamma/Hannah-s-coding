// ---------------------------------------------------------------------------
// Name: Elizabeth Lanier
// Course-Section: CS355-section #1
// Assignment: Project 2
// Date due: 2/7/2025
// Description: MapV2.cpp file
// ---------------------------------------------------------------------------
#include "MapV2.h"
#include "UseItem.h"
#include "ConsumeItem.h"
#include <sstream>
#include <iostream>

//----------------------------------------------------------------------------
/* MapV2() Constructor, this sets ifderr to false. initializes a filename to
* be read.
* INCOMING DATA: ifstream inFile
* OUTGOING DATA: Prints output to the console
*/
MapV2::MapV2() : Map() {

	ifderr = false;
	string fileName;
	ifstream inFile;

	while (true)
	{
		cout << "Enter the name of the IFD file: ";
		getline(cin,fileName);
		inFile.open(fileName);
		if (inFile.is_open())
		{
			break;
		} else {
			cout << "Failed to open file: " << fileName << endl;
		}
	}

	parser.setGameFile(fileName);
}
//----------------------------------------------------------------------------
/* buildMap() reads all game tags and builds the map based off their area
* location, area link and items.
* INCOMING DATA: None
* OUTGOING DATA: Prints output to the console
*/
void MapV2::buildMap()
{
	ifderr = false;
	parser.tokenIt();

	nextToken = parser.getNext();

	if (nextToken == "<game>")
	{
		parser.eatToken();
		nextToken = parser.getNext();

		while (nextToken != "</game>")
		{
			if (nextToken == "<ptype>") {
				// cout << "Before eat: " << nextToken << endl;
				parser.eatToken();
				nextToken = parser.getNext();

				ptype = playerType();
				// cout << "After eat: "<< nextToken << endl;
				parser.eatToken();
				nextToken = parser.getNext();

			}
			else if (nextToken == "<area>")
			{
				parser.eatToken();
				nextToken = parser.getNext();
				makeArea();
				//cout << "Made it to area tag" << endl;
			}
			else if (nextToken == "<links>")
			{
				parser.eatToken();
				nextToken = parser.getNext();
				makeLinks();
				//cout << "Made it to links" << endl;
			}
			else if (nextToken == "<item>")
			{
				parser.eatToken();
				nextToken = parser.getNext();
				makePtype();

			}
			else
			{
				cout << "Parse Error Location (Items)" << endl;
				ifderr = true;
				break;
			}

			parser.eatToken();
			nextToken = parser.getNext();
		}

		if (ifderr)
		{
			cout << " :: ERROR :: IF Document Formatting Error (Items)" << endl;
			return;
		}
	}
	else
	{
		cout << " :: ERROR :: No \"<game>\" tag found." << endl;
	}

	linkLinks();
	insertItems(); //cout << "Passed insert items. " << endl;
}

void MapV2::makePtype() {
	Item* tempItem;

	if(nextToken == "<basic>") {
		tempItem = new Item;
		//cout << nextToken << endl;
	}
	else if (nextToken == "<use>") {
		tempItem = new UseItem;
		//cout << nextToken << endl;
	}
	else if (nextToken == "<consume>") {
		tempItem = new ConsumeItem;
		//cout << nextToken << endl;
	}
	else {
		return;
	}
	parser.eatToken();
	nextToken = parser.getNext();
	string xstr;
	//cout << "After part 1: "<<nextToken << endl;

	while (nextToken != "</item>") {
		if (nextToken == "<name>") {
			parser.eatToken();
			nextToken = parser.getNext();
			tempItem->setName(nextToken);
			//cout << nextToken << endl;
		}
		else if (nextToken == "<desc>") {
			parser.eatToken();
			nextToken = parser.getNext();
			tempItem->setDesc(nextToken);
			//cout << nextToken << endl;
		}
		else if (nextToken == "<star>") {
			parser.eatToken();
			nextToken = parser.getNext();
			istringstream ss(nextToken);
			getline(ss, xstr, ',');
			tempItem->setSR(atoi(xstr.c_str()));
		//	cout << nextToken << endl;
		}
		else if (nextToken == "<actmess>") {
			parser.eatToken();
			nextToken = parser.getNext();
			tempItem->setActiveMessage(nextToken);
			//cout << tempItem->getActiveMessage() << endl;
		}
		else if (nextToken == "<actar>") {
			parser.eatToken();
			nextToken = parser.getNext();
			istringstream ss(nextToken);
			getline(ss, xstr, ',');
			tempItem->setActiveArea(atoi(xstr.c_str()));
		//	cout << tempItem->getActiveArea() << endl;
		}
		else if (nextToken == "<rule>") {
			parser.eatToken();
			nextToken = parser.getNext();
			istringstream ss(nextToken);
			getline(ss, xstr, ',');
			Rule* temp = new Rule;
			temp->beginRm = atoi(xstr.c_str());

			getline(ss, xstr, ',');
			temp->direction = xstr[0];

			getline(ss, xstr, ',');
			temp->destRm = atoi(xstr.c_str());

			tempItem->addRule(temp);
			//cout << "Rule: "<<nextToken << endl;

		}
		else if (nextToken == "<effect>") {
			parser.eatToken();
			nextToken = parser.getNext();
			//cout << "Effect: "<<nextToken << endl;
			istringstream ss(nextToken);
			getline(ss, xstr, ',');
			Effect* temp = new Effect;
			temp->effectID = atoi(xstr.c_str());

			getline(ss, xstr, ',');
			temp->effectAmt = atoi(xstr.c_str());
			tempItem->addEffect(temp);
			
			//cout << "Effect: "<<nextToken << endl;
		}
		else if (nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"||
		         nextToken == "</basic>" || nextToken == "</use>" || nextToken == "</actmess>"||
		         nextToken == "</actar>" || nextToken == "</effect>" || nextToken == "</rule>" ||
		         nextToken == "</feats>" || nextToken == "</consume>") {
			// Ignore closing tags
		}
		else {
			cout << "Parser Error: In makePtype" << endl;
			ifderr = true;
			break;
		}
		parser.eatToken();
		nextToken = parser.getNext();
	}
	items.insertLast(tempItem);
}

//----------------------------------------------------------------------------
/* insertItem() inserts items at the proper location in the map
* INCOMING DATA: Item* newItem.
* OUTGOING DATA: Item* newItem.
*/
void MapV2::insertItems()
{
	nodeType<Item*>* current = items.getFirst(); // Get first item in the list

	while (current != nullptr)
	{
		areaNode* areaLoc = areasVec[(current->info->getSR()) - 1];
		areaLoc->info.items.insertLast(current->info);
		current = current->link;
	}
}
//----------------------------------------------------------------------------
/* resetItem() resets items to the proper location in the map
* INCOMING DATA: Item* newItem.
* OUTGOING DATA: Item* newItem.
*/
void MapV2::resetItems()
{
	for(int i = 0; i <areacnt; i++ ) //area count
	{
		areasVec[i]->info.items.initializeList();//destroys nodes
	}
	insertItems();
}

int MapV2::playerType() {
	if(nextToken == "basic") {
		return 0;
	} else if (nextToken == "hpsp") {
		return 1;
	} else {
		return -1;
	}
	//nextToken = getNextToken();
}

//----------------------------------------------------------------------------
/* ostream& operator() This outputs all the items, areas, and their links as
* a cheat code for the player.
* INCOMING DATA: MapV2& map
* OUTGOING DATA: ostream& os
*/
ostream& operator<<(ostream& os, MapV2& map)
{
	os<<"******************************************************************"<<endl;
	os<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
	os<<"******************************************************************"<<endl;
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
	os<<"******************************************************************"<<endl;
	os<<"CHEATING!!!! ITEM LOCATIONS FOR ALL NON-INVENTORY ITEMS." << endl;
	os<<"******************************************************************"<<endl;
	for (int i = 0; i < map.areasVec.size(); i++)
	{
		os << "Items for area " << i << ": " << map.areasVec[i]->info.getDescription() << endl;
		if (map.areasVec[i]->info.items.length() > 0)
		{
			nodeType<Item*>* current = map.areasVec[i]->info.items.getFirst();
			while (current != nullptr)
			{
				os << "\t";
				os << current->info->getName() << endl;
				current = current->link;
			}
		}
		else
		{
			os << "No items in list" << endl;
		}
	}
	return os;
}
