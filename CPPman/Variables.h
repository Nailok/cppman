#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H

 struct t_player {
	int x, y;
	char model; 
};

/*extern char map[50][50] = {
	"+#############################+\n",
	"|      ..........   .      |  |\n",
	"|                  .  .    #  |\n",
	"|## #######  .    .    .   # #|\n",
	"|   |                         |\n",
	"|  |###         ..            |\n",
	"|              .              |\n",
	"|          .   .       ##     |\n",
	"|           .     #  |     |  |\n",
	"|        ##|    .    ##       |\n",
	"|             . .             |\n",
	"|   #|   ##|   ..             |\n",
	"|    |          . # #####     |\n",
	"|##  |          .             |\n",
	"|      |         ..   ####### |\n",
	"|  ########     .             |\n",
	"|                             |\n",
	"+#############################+\n"
};*/

 extern char map[15][33];


extern int temp;
extern int playerScore;
extern int mapRow;
extern int mapCol;

extern t_player player;
extern t_player enemyF;

extern struct queueNode;
extern struct Point;

extern bool gameOverFlag;
extern bool up;
extern bool down;
extern bool left;
extern bool right;
extern bool winFlag;





#endif