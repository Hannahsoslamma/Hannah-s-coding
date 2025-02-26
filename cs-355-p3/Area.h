// ---------------------------------------------------------------------------
// Name: Elizabeth Lanier
// Course-Section: CS355-section #1
// Assignment: Project 2
// Date due: 2/7/2025
// Description: Area.h file
// ---------------------------------------------------------------------------
#ifndef AREA_H  
#define AREA_H
#include <string>
#include "Item.h"
#include "ull.h"

using namespace std;

class Area{
  public:
    void setDescription (string);
    void setGoal(bool);
    void setID(bool);
    string getDescription();
    bool getID();
    bool getGoal();
    void displayArea();
    //new added
    uLList<Item*>items;
    void search();

  private:
     string description;
     bool instadeath;
     bool goal;
  
};

#endif // H_area