#include "GameStart.h"
#include "Variables.h"
#include "Pathfinding.h"
#include "Enemy.h"

#define LEN(arr) ((int) sizeof (arr) / sizeof (arr)[0])



t_player player;
t_player enemyF;

unsigned int frames;

int playerScore;
int mapRow;
int mapCol;

bool winFlag;
bool gameOverFlag;
bool up = false;
bool down = false;
bool right = false;
bool left = false;


char originalMap[15][33] = {
	"+#############################+\n",
	"#                             #\n",
	"#.                            #\n",
	"#.                            #\n",
	"#.     #  ###############     #\n",
	"#.     #  #       ##    #     #\n",
	"#.     #  # ###   ## #  #     #\n",
	"#.     #  # # #   ## #  #     #\n",
	"#.     #  # # #      #  #######\n",
	"#.     #  # # ########        #\n",
	"#.     #  # #  #     ######## #\n",
	"#.     #    #  #            # #\n",
	"#.     #####   #            # #\n",
	"#............. #..............#\n",
	"+#############################+\n"
};



char map[15][33];




void initGame() {

	frames = 0;

	mapRow = LEN(map);
	mapCol = LEN(map[0]);


	playerScore = 0;
	player.x = 1;
	player.y = 1;
	player.model = '@';

	enemyF.x = 20;
	enemyF.y = 10;
	enemyF.model = 'F';

	winFlag = false;
	gameOverFlag = false;

	up = false;
	down = false;
	left = false;
	right = false;

}



void PlayerLogic() {

	if (GetAsyncKeyState(VK_UP)) {
		up = true;
		down = false;
		left = false;
		right = false;
	} else

	if (GetAsyncKeyState(VK_DOWN)) {
		up = false;
		down = true;
		left = false;
		right = false;
	} else

	if (GetAsyncKeyState(VK_LEFT)) {
		up = false;
		down = false;
		left = true;
		right = false;
	}else

	if (GetAsyncKeyState(VK_RIGHT)) {
		up = false;
		down = false;
		left = false;
		right = true;
	}


	if (up) {
		if (map[player.y - 1][player.x] == '.') {
			map[player.y - 1][player.x] = ' ';
			player.y--; 
			playerScore++; 
			
		}
		else if (map[player.y - 1][player.x] == ' ') {player.y--;}
	}
	if (down) {
		if (map[player.y + 1][player.x] == '.') {
			map[player.y + 1][player.x] = ' ';
			player.y++;
			playerScore++; 
			
		}
		else if (map[player.y + 1][player.x] == ' ') { player.y++; }
	}
	if (left) {
		if (map[player.y][player.x - 1] == '.') {
			map[player.y][player.x - 1] = ' ';
			player.x--;
			playerScore++;
			
		}
		else if (map[player.y][player.x - 1] == ' ') { player.x--; }
	}
	if (right) {
		if (map[player.y][player.x + 1] == '.') { 
			map[player.y][player.x + 1] = ' ';
			player.x++; 
			playerScore++; 
		
		}
		else if (map[player.y][player.x + 1] == ' ') { player.x++; }
	}

	if (GetAsyncKeyState(VK_ESCAPE)) {
		gameOverFlag = true;
	}

}


void gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hStdout, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hStdout, &cursorInfo);
	SetConsoleCursorPosition(hStdout, position);
	
}

void displayHelp()
{
	gotoxy(55, 0); _cprintf("#####################");
	gotoxy(55, 1); _cprintf("#     Controls      #");
	gotoxy(55, 2); _cprintf("#<LEFT>   move left #");
	gotoxy(55, 3); _cprintf("#<RIGHT>  move right#");
	gotoxy(55, 4); _cprintf("#<UP>     move up   #");
	gotoxy(55, 5); _cprintf("#<DOWN>   move down #");
	gotoxy(55, 6); _cprintf("#<ESCAPE> EXIT      #");
	gotoxy(55, 7); _cprintf("#####################");

	gotoxy(9, 20); _cprintf("Score: %d", playerScore);


}

void displayDebug() {
	//gotoxy(9, 25); _cprintf("Frames: %d", frames);
	gotoxy(9, 26); _cprintf("Player X: %d  ", player.x);
	gotoxy(9, 27); _cprintf("Player Y: %d  ", player.y);
	gotoxy(9, 28); _cprintf("Enemy X: %d   ", enemyF.x);
	gotoxy(9, 29); _cprintf("Enemy Y: %d   ", enemyF.y);
	//gotoxy(9, 30); _cprintf("Minimal distance: %d", BFS(map));

	//gotoxy(9, 30); _cprintf("Map length: %d", strlen(*map));



}

void GameOver() {
	if (enemyF.x == player.x && enemyF.y == player.y) {
		system("@cls||clear");
		printf("You died. You have a score of %d", playerScore);
		Sleep(3000);
		gameOverFlag = true;
	}
}

void CheckForWin(char tmp_map[15][33]) {
	winFlag = true;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 33; j++) {
			if (tmp_map[i][j] == '.') {
				winFlag = false;
				break;
			}
		}
	}

	if (winFlag) {
		system("@cls||clear");
		printf("You Win! You have a score of %d", playerScore);
		Sleep(3000);
		gameOverFlag = true;
	}

}

void ShowMap() {
	
		for (int i = 0; i < 18; i++) {
			printf("%s", map[i]);
		}

		gotoxy(player.x, player.y);
		printf("%c", player.model);

		gotoxy(enemyF.x, enemyF.y);
		printf("%c", enemyF.model);
}

void RunGame() {
	

	memcpy(map, originalMap, sizeof(originalMap));
	initGame();
	while (1) {
		gotoxy(0, 0);
		ShowMap();
		displayHelp();
		displayDebug();
		PlayerLogic();

		if (frames % 2 == 0) {
			FindPath(enemyF.x, enemyF.y, player.x, player.y);
			EnemyMove();
		}
		
		GameOver();
		CheckForWin(map);

		frames++;

		if (gameOverFlag) {
			
			break;
		}

		Sleep(50);
	}
}