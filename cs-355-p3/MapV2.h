// ---------------------------------------------------------------------------
// Name: Elizabeth Lanier
// Course-Section: CS355-section #1
// Assignment: Project 2
// Date due: 2/7/2025
// Description: MapV2.h file
// ---------------------------------------------------------------------------
#ifndef MAPV2_H
#define MAPV2_H

#include "Map.h"
#include "Item.h"
#include "UseItem.h"
#include "ConsumeItem.h"
#include <vector>

using namespace std;

class MapV2 : public Map
{
private:
	uLList<Item*> items; //storing pntrs to item obj.
	int ptype;

public:
	MapV2();
	void buildMap();       
	void insertItems();
	void resetItems();
	int playerType();

	//int getPlayer();
	int getPT() 
	{
		return ptype;
	}
	void makePtype();
	//void updateMap(nodeType<Item*>* temp);
	void updateMap(nodeType<Item*>* temp) {
		cout << temp->info->getActiveMessage() << endl;
		Rule* tempRule;

		for (int i = 0; i < temp->info->getItemUseRules().size(); i++){
		    
		    tempRule = (temp->info->getItemUseRules())[i];
		    if(tempRule->direction == 'u') {
		        //areaNode* nodeTemp = getStart();
		        areasVec[(tempRule->beginRm-1)]->u = areasVec[tempRule->destRm-1];
		        //cout << areasVec[tempRule->destRm-1];
		    }
		    else if(tempRule->direction == 'd') {
		        //areaNode* nodeTemp = getStart();
		        areasVec[(tempRule->beginRm-1)]->d = areasVec[tempRule->destRm-1];
		        //cout << areasVec[tempRule->destRm-1];
		    }
		    else if(tempRule->direction == 'l') {
		        //areaNode* nodeTemp = getStart();
		        areasVec[(tempRule->beginRm-1)]->l = areasVec[tempRule->destRm-1];
		        //cout << areasVec[tempRule->destRm-1];
		    }
		    else {
		        //areaNode* nodeTemp = getStart();
		        areasVec[(tempRule->beginRm-1)]->r = areasVec[tempRule->destRm-1];
		        //cout << areasVec[tempRule->destRm-1];
		    }
		}
	}

	friend ostream& operator<<(ostream& os, MapV2& map);
};

#endif // MapV2.h