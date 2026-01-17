#include <iostream>
#ifndef H_GAME
#define H_GAME
  #include "Game.h"
#endif // H_GAME

#include "BasicPlayer.h"
#include "HPSPPlayer.h"
#include "MapV2.h"
#include "Player.h"


Game::Game(){
    map.buildMap();

    if(map.getPT() == 0) {
        player1 = new BasicPlayer;
        cout << "Creating Basic Player ... READY!" << endl;

    }else{

        player1 = new HPSPlayer;
        cout << "Creating HPSP Player ... READY!" << endl;
    }
    player1->setCurrent(map.getStart());
}

Game::~Game() {
    if (player1) {
        delete player1; // Free the allocated memory for player1
        player1 = nullptr; // Avoid dangling pointer
    }
}
void Game::play(){
    string userInput;
    while(true){

        //check game status
        if(player1->isGameOver() != 0){
            player1->getCurrent()->info.displayArea();
            return;
        }

        //My way for now
        if(player1->isGameOver() == 3) {
            cout << "Hit points killed you." << endl;
            return;
        }

        if(player1->isGameOver() == 1) {
            //cout << "Sanity points killed you." << endl;
            return;
        }


        if(player1->getCurrent()->info.getID() == true)
        {
            cout << "You have entered a dangerous area!" << endl;

            combatDeathRoom();  // Call combat system (to be implemented)
            return;
        }

        if(player1->playerMoved()){
                player1->getCurrent()->info.displayArea();
        }
        else{
            if(userInput != "reset"){
                cout<<"There appears to be no way to go that direction."<<endl;
            }
        }

        //get movement selection
        cout<<"Which way would you like to go?  Enter u, d, l, or r"<<endl;
        getline(cin, userInput);

        //update area
        if(userInput == "u"){
            if (player1->getCurrent() != player1->getCurrent()->u)
            {
                player1->takeHP(10);
                map.updateDeathRoom();
            }
            player1->setCurrent(player1->getCurrent()->u);
        }
        else if(userInput == "d"){
            if (player1->getCurrent() != player1->getCurrent()->d)
            {
                player1->takeHP(10);
                map.updateDeathRoom();
            }
            player1->setCurrent(player1->getCurrent()->d);
        }
        else if(userInput == "l"){
            if (player1->getCurrent() != player1->getCurrent()->l)
            {
                player1->takeHP(10);
                map.updateDeathRoom();
            }
            player1->setCurrent(player1->getCurrent()->l);
        }
        else if(userInput == "r"){
            if (player1->getCurrent() != player1->getCurrent()->r)
            {
                player1->takeHP(10);
                map.updateDeathRoom();
            }
            player1->setCurrent(player1->getCurrent()->r);
        }
        else if(userInput == "iseedeadpeople"){ //issdeadpeople cheat code to reveal map
            //map.print();
            cout<<map;
        }
        else if(userInput == "reset"){
            resetGame();
            player1->resetPlayerStats();
        }
        else if(userInput == "exit"){
            cout<<"Good bye!"<<endl;
            return;
        }
        else if(userInput == "search"){
            player1->getCurrent()->info.search();
        }
        else if(userInput == "inventory"){
            player1->inventory();
        }
        else if(userInput == "take"){
            player1->take();
        }
        else if(userInput == "leave"){
            player1->leave();
        }
        else if(userInput == "examine"){
            player1->examine();
        }
        else if(userInput == "stats") {
            player1->reportStats();
        }
        else if(userInput == "use") {
            player1->use(&map);
        }
        else if(userInput == "consume") {
            player1->consume(&map);
        }

        else if(userInput == "help"){
            cout<<"You may type: "<<endl;
            cout<<"\t u, d, l, or r: to move up, down, left or right on the map,"<<endl;
            cout<<"\t search: to search for items in current area,"<<endl;
            cout<<"\t take: to attempt to take an item,"<<endl;
            cout<<"\t leave: to attempt to leave an item,"<<endl;
            cout<<"\t examine: to examine an item in your inventory,"<<endl;
            cout<<"\t stats: to see the player's status." << endl;
            cout<<"\t use: to use an item." << endl;
            cout<<"\t consume: to eat an item." << endl;
            cout<<"\t reset: to reset the game,"<<endl;
            cout<<"\t exit: to exit the game."<<endl;
            cout<<endl;
        }
        else{
            cout<<"I do not understand: "<<userInput<<endl<<endl;
        }
    }//end while
    //delete mapptr;
}//end play()



void Game::resetGame(){
    player1->setCurrent(map.getStart());
    //remove item from player list
    player1->items.destroyList();
    //remove item from each area in turn
    map.resetItems();
    player1->resetPlayerStats();

}

void Game::combatDeathRoom()
{
    // Check if the player has a "use" item (sword) in the inventory.
    bool hasWeapon = false;
    nodeType<Item*>* currentNode = player1->items.getFirst();
    Item* weapon = nullptr;  // Pointer to store the sword item.

    // Loop through the inventory.
    while (currentNode != nullptr)
    {
        // If an item is of type "use", treat it as a sword.
        if (currentNode->info->getType() == "use")
        {
            hasWeapon = true;
            weapon = currentNode->info;
            break;
        }
        currentNode = currentNode->link;
    }

    // If no weapon is found, the player loses.
    if (!hasWeapon)
    {
        cout << "You have no weapon to fight the Serial Killer! You lose." << endl;
        return;
    }

    // Create the Serial Killer enemy.
    SerialKiller enemy;

    // Variables to hold damage values.
    int playerDamage = 0;
    int enemyDamage = 0;

    // Get the player's current health.
    int playerHealth = player1->getHP();
    // Get the enemy's starting health.
    int enemyHealth = enemy.getHitPoints();

    // This flag will be true if the player wins.
    bool playerWon = false;

    // Seed the random number generator.
    // (Ideally, this should be done once in main(), not repeatedly here.)
    //srand((unsigned int)time(NULL));

    // Combat loop: continue until either the player or enemy is defeated.
    while (playerHealth >= 0 && enemyHealth >= 0)
    {
        // At the beginning of each round, ask the player for a sword attack type.
        cout << "\nChoose your attack (slash, stab, or swing): ";
        string attackChoice;
        getline(cin, attackChoice);
        // The chosen attack type is only cosmetic and does not affect damage.

        // Generate a random outcome: 0 means enemy attacks, 1 means player attacks.
        int outcome = rand() % 2;

        if (outcome == 0)
        {
            // Outcome 0: The enemy attacks the player.
            enemyDamage = enemy.getAttackPower();  // Get enemy damage.
            cout << "The Serial Killer hits you for " << enemyDamage << " damage." << endl;
            player1->takeHP(enemyDamage);           // Subtract damage from player's health.
            playerHealth = player1->getHP();          // Update player's health.
        }
        else
        {
            // Outcome 1: The player attacks the enemy.
            // Calculate random sword damage between 15 and 25.
            playerDamage = (rand() % 11) + 15;
            cout << "You " << attackChoice << " the Serial Killer for "
                 << playerDamage << " damage." << endl;
            enemy.takeDamage(playerDamage);           // Subtract damage from enemy's health.
            enemyHealth = enemy.getHitPoints();       // Update enemy's health.
        }
    }

    // Set the outcome flag based on final health values.
    if (enemyHealth <= 0 && playerHealth > 0)
    {
        playerWon = true;
    }
    else
    {
        playerWon = false;
    }

    // Print the combat result.
    if (playerWon)
    {
        cout << "You have defeated the Serial Killer!" << endl;
    }
    else
    {
        cout << "You were defeated by the Serial Killer." << endl;
    }
}



