#include <iostream>
#include <limits> 
#include <cstdlib> // for rand() and srand()
#include <ctime>  
using namespace std;

int main() {
  int health = 100;
  int life = 3;
  int damage, dice;
  bool continueGame = true;
  char answer, diceChoice;

  
  srand(time(0));

  cout << "Bravest coding Warrior!! \nWe need you to slay the C++ Dragon."<< endl;
  cout << "Can you do it? (Y/N): ";
  cin >> answer;

  if(answer == 'n' || answer == 'N') {
    continueGame = false;
    cout << "That's too bad,\nYou must not want to be a coding warrior :(" << endl;
  }
  
  cout << "Brave Warrior you must roll the dice to attack!";
  cout << endl;
  cout << "Fate shall decide the damage to you or the dragon!";
  cout << endl;
  
  while (continueGame == true) {

    cout << "Press any key to roll: ";
    cin >> diceChoice;

// a codding syntax mistake that resulted in a cool
// press any button to do the only function hack.
  if(diceChoice == 'y' || 'Y'){
    dice = rand() % 10 + 1;
  } 

  if (dice >= 5) {
    damage = dice * 5;
    health -= damage;
    cout << endl;
    cout << "You inflicted " << damage << " damage.\n";
    cout << "The dragon is at " << health << " health." << endl;
    
  }
  else if (dice < 5) {
    life -= 1;
    cout << endl;
    cout << "You lost a life. Remaining: " << life << " life" << endl;
    cout << endl;
    cout << "Take a hit, code: 420" << endl;
  }
    if(health <= 0) {
      cout << "Congrats! You've deafeted the Coding Dragon!!" << endl;
      continueGame = false;
    }
    else if(life <= 0){
      cout << "Our brave coding warrior has fallen." << endl;
      cout << "Take a fat rip." << endl;
      continueGame = false;
    }
  }

// I didnt use ai once to fix this i used past assignments as reffrence!!

  return 0;

}