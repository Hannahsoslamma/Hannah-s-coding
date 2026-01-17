
#ifndef H_MAPV2
#define H_MAPV2
    #include "MapV2.h"
#endif // H_MAPV2

#ifndef H_PLAYER
#define H_PLAYER
    #include "Player.h"
#endif // H_PLAYER

#ifndef H_SERIALKILLER
#define H_SERIALKILLER
    #include "SerialKiller.h"
#endif // H_SERIALKILLER
#include <ctime>

class Game{
	private:
		Player* player1;
		MapV2 map;
		//int deathRoom;

  	public:
		Game();
		~Game();

  		void play();
  		void resetGame();

  		void combatDeathRoom();
};
