#ifndef HP_H
#define HP_H
#include "Player.h"

class HPSPlayer : public Player
{
public:

	HPSPlayer() {
		hitPoints = 100;
		sanity = 100;
	}

	void resetPlayerStats() {
		hitPoints = 100;
		sanity = 100;
	}

	void reportStats() {
		cout << "Player Stats:" << endl;
		cout << "\tHit Points: " << hitPoints << endl;
		cout << "\tSanity Points: " << sanity << endl;
	}

	int isGameOver()
	{
		if (currentLocation && currentLocation->info.getID()) {  
			return 2;
		}
		if (currentLocation && currentLocation->info.getGoal()) {  
			return 1;
		}

		if (hitPoints <= 0) {
		    cout << "You have died of your wounds." << endl;
			return 3; 
		}

		if (sanity <= 0) {
            cout << "You died because of your sanity." << endl;
			return 4;
		}
		return 0;
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
			bool found = false;
			while(temp != NULL && !found) {
				if(itemName == temp->info->getName()) {
					found = true;
				}
				else {
					temp = temp->link;
				}
			}
			if(!found) {
				cout << "No items by that name in your inventory." << endl;
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
			Effect* tempEffect;

			for(int i = 0; i < temp->info->getItemConsumeEffects().size(); i++) {
				tempEffect = (temp->info->getItemConsumeEffects())[i];
				if(tempEffect->effectID == 0) {
					hitPoints -= tempEffect->effectAmt;
				}
				else if(tempEffect->effectID == 1) {
					hitPoints += tempEffect->effectAmt;
				}
				else if(tempEffect->effectID == 2) {
					sanity -= tempEffect->effectAmt;
				}
				else {
					sanity += tempEffect->effectAmt;
				}
			}
			if (hitPoints > 100) {
				hitPoints = 100;
			}
			if(sanity > 100) {
				sanity = 100;
			}
			//items.deleteNode(temp->info);
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
            bool found = false;
            while (temp != NULL && !found){
                if(itemName == temp->info->getName()){
                    found = true;
                }
                else {
                    temp = temp->link;
                }
            }
            if(!found) {
                cout << "No items by that name in your inventory." << endl;
                return;
            }
        }
        if(temp->info->getType() != "use") {
            cout << "This item cannot be used." << endl;
            return;
        }
        else if(temp->info->getActiveArea() != mapptr->reverseLookUp(currentLocation)
                && temp->info->getActiveArea() != 0) {
                    cout << "This item cannot be used here." << endl;
                    return;
        }
        else {
            mapptr->updateMap(temp);
        }
	}
	
private:
	int hitPoints;
	int sanity;

};

#endif // HP_H