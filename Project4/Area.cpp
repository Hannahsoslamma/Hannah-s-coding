// ---------------------------------------------------------------------------
// Name: Elizabeth Lanier
// Course-Section: CS355-section #1
// Assignment: Project 2
// Date due: 2/7/2025
// Description: Area.cpp file
// ---------------------------------------------------------------------------
#include <iostream>
#include "Area.h"

// setters
void Area::setDescription (string desc) {
	description = desc;
}
void Area::setGoal(bool g) {
	goal = g;
}
void Area::setID(bool id) {
	instadeath = id;
}

// getters
string Area::getDescription() {
	return description;
}
bool Area::getID() {
	return instadeath;
}
bool Area::getGoal() {
	return goal;
}
// provides description of area
void Area::displayArea() {
	cout<<description<<endl;
}
//----------------------------------------------------------------------------
/* search()  Displays all items present in the current area.
* Traverses the linked list of items and prints their names.
* INCOMING DATA: None
* OUTGOING DATA: Prints output to the console
*/
void Area::search()
{
	nodeType<Item*>* current = items.getFirst();
	cout << "The following items are in this area:" << endl;
	// Traverse the list using nodeType's link member
	while (current != nullptr) {
		// Access the Item* through the node's info member
		Item* item = current->info;
        
		// Use -> operator to access Item members
		cout << "\t " << item->getName() << endl;
  
		// Move to next node using nodeType's link pointer
		current = current->link;
	}

	if (items.isEmptyList()) {
		cout << "No items are in this area." << endl;
	}
}
