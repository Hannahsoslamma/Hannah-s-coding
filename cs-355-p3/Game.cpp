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
    //cin.ignore();
    //Map* mapptr = new MapV2();
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
        
        if(player1->isGameOver() == 4) {
            cout << "Sanity points killed you." << endl;
            return;
        }
        //display area data
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
            player1->setCurrent(player1->getCurrent()->u);
        }
        else if(userInput == "d"){
            player1->setCurrent(player1->getCurrent()->d);
        }
        else if(userInput == "l"){
            player1->setCurrent(player1->getCurrent()->l);
        }
        else if(userInput == "r"){
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

