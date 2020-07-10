#pragma once
#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>

struct walk {
	short walk_count;
	short x;
	short y;
	short back;
};

struct target {
	short x;
	short y;
};


extern std::vector<target> walk_queue;

void FindPath(int sx, int sy, int x, int y);
void EnemyMove();
#endif // !PATHFINDING_H


