#include "Sokoban.h"

int main()
{
	Sokoban* sokoban = new Sokoban();

	sokoban->PlayGame();

	delete sokoban;
	return 0;
}