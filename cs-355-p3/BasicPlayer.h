#ifndef BP_H
#define BP_H
#include "Player.h"

#include "Item.h"
#include "UseItem.h"
#include "ConsumeItem.h"
#include "MapV2.h"
#include <vector>

class BasicPlayer : public Player
{
public:
	BasicPlayer() {
		lastLocation = NULL;
		currentLocation = NULL;
	}

	int isGameOver()
	{
		if (currentLocation && currentLocation->info.getID()) {  // Check if instadeath area
			return 2;
		}
		if (currentLocation && currentLocation->info.getGoal()) {  // Check if goal area
			return 1;
		}
		return 0;
	}

	void resetPlayerStats()
	{
		//does nothing
	}

	void reportStats()
	{
		cout << "No player statistics to report." << endl;
	}

	void consume(Map* mapptr) {
		cout<<"Consume what item?"<<endl;
		string itemName;
		getline(cin, itemName);

		nodeType<Item*>* temp = NULL;
		temp = items.getFirst();

		if(temp == NULL) {
			cout<<"You have no items in your inventory to use"<<endl;
			return;
		}
		else {
			bool itemFound = false;
			while(temp != NULL && !itemFound) {
				if (temp->info == nullptr) {  // Prevent accessing null pointer
					cerr << "Error: temp->info is null!" << endl;
					return;
				}


				if(itemName== temp->info->getName()) {
					itemFound = true;
				
				}
				else {
					temp = temp->link;
				}
			}
			if(!itemFound) {
				cout << "No item by that name in your inventory." << endl;
				return;
			}
		}

		if(temp->info->getType() != "consume") {
		    cout << temp->info->getType() << endl;
		    
			cout << "This item cannot be consumed" << endl;
			return;
		}
		else if (temp->info->getActiveArea() != mapptr->reverseLookUp(currentLocation)
		         && temp->info->getActiveArea() != 0) {
			cout << "This item cannot be consumed here." << endl;
			
			return;
		}
		else {
			cout << temp->info->getActiveMessage() << endl;
			items.deleteNode(temp->info);
		}
	}


	void use(Map* mapptr)  {
		cout<<"Use what item?"<<endl;
		string itemName;
		getline(cin, itemName);

		nodeType<Item*>* temp = NULL;
		temp = items.getFirst();

		if(temp == NULL) {
			cout<<"You have no items in your inventory to use"<<endl;
			return;
		}
		else {
			bool itemFound = false;
			while(temp != NULL && !itemFound) {
				if (temp->info == nullptr) {  // Prevent accessing null pointer
					cerr << "Error: temp->info is null!" << endl;
					return;
				}


				if(itemName== temp->info->getName()) {
					itemFound = true;
				
				}
				else {
					temp = temp->link;
				}
			}
			if(!itemFound) {
				cout << "No item by that name in your inventory." << endl;
				return;
			}

			// now my bug is here
			else if (temp->info->getActiveArea() != mapptr->reverseLookUp(currentLocation)
			         && temp->info->getActiveArea() != 0) {
				cout << "This item cannot be used here." << endl;
				//cout << "Item's Active Area: " << temp->info->getActiveArea() << endl;
				//cout << "Current Area: " << mapptr->reverseLookUp(currentLocation) << endl;
				//cout << "CHECKPOINT" << endl << endl << endl << endl;
				return;
			}
			else {
				mapptr->updateMap(temp);
			}
		}
	}
};


#endif // BP_H
