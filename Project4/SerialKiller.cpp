//Serial killer.cpp

#include "SerialKiller.h"

// ---------------------------------------------------------------------------
// Constructor: Initializes hitPoints to 50 and attackPower to 15.
// ---------------------------------------------------------------------------
SerialKiller::SerialKiller()
{
    hitPoints = 50;
    attackPower = 15;
}

// ---------------------------------------------------------------------------
// getHitPoints() returns the enemy's current hit points.
// ---------------------------------------------------------------------------
int SerialKiller::getHitPoints()
{
    return hitPoints;
}

// ---------------------------------------------------------------------------
// takeDamage() subtracts the given damage value from hitPoints.
// If hitPoints fall below 0, they are set to 0.
// ---------------------------------------------------------------------------
void SerialKiller::takeDamage(int damage)
{
    hitPoints = hitPoints - damage;
    cout << "killer has: " << hitPoints << " health." << endl;
}

// ---------------------------------------------------------------------------
// getAttackPower() returns the enemy's attack power.
// ---------------------------------------------------------------------------
int SerialKiller::getAttackPower()
{
    return attackPower;
}

