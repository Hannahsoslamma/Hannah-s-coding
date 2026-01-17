// ---------------------------------------------------------------------------
// Name: Group 2
// Course-Section: CS355-Section #
// Assignment: Project #4 - Combat Feature
// Date due: 03/14/2025
// Description: This class represents an enemy (Serial Killer) that tracks its
//              health and attack value. It provides functions to get the attack
//              power and to reduce its health when it takes damage.
// ---------------------------------------------------------------------------
#ifndef SERIAL_KILLER_H
#define SERIAL_KILLER_H

#include <iostream>
using namespace std;

class SerialKiller
{
public:
    // Constructor: Sets hitPoints to 50 and attackPower to 20.
    SerialKiller();

    // Returns the current hit points of the enemy.
    int getHitPoints();

    // Subtracts the damage value from hitPoints.
    void takeDamage(int damage);

    // Returns the enemy's attack power.
    int getAttackPower();

private:
    int hitPoints;     // Enemy's health
    int attackPower;   // Enemy's attack strength
};

#endif


