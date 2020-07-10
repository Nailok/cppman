#include "Variables.h"
#include "Enemy.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <iostream>


class Enemy {
	public:
		char name;
		t_player enemy;

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

		char temp_map[15][33];

		std::vector<target> walk_queue;

		std::vector<walk> BFSArray;

		void AddArray(int x, int y, int wc, int back) {
			if (temp_map[y][x] == ' ' || temp_map[y][x] == '.') {
				temp_map[y][x] = '#';
				walk tmp;
				tmp.x = x;
				tmp.y = y;
				tmp.walk_count = wc;
				tmp.back = back;
				BFSArray.push_back(tmp);
			}
		}

		void FindPath(int sx, int sy, int x, int y) {
			memcpy(temp_map, map, sizeof(map));
			BFSArray.clear();
			walk tmp;
			tmp.x = sx;
			tmp.y = sy;
			tmp.walk_count = 0;
			tmp.back = -1;
			BFSArray.push_back(tmp);

			int i = 0;
			while (i < BFSArray.size()) {
				if (BFSArray[i].x == x && BFSArray[i].y == y) {
					walk_queue.clear();
					target tmp2;
					while (BFSArray[i].walk_count != 0) {
						tmp2.x = BFSArray[i].x;
						tmp2.y = BFSArray[i].y;
						walk_queue.push_back(tmp2);

						i = BFSArray[i].back;
					}

					break;
				}

				AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
				AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
				AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i);
				AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i);

				i++;
			}

			BFSArray.clear();
		}

		void EnemyMove() {
			if (walk_queue.size() != 0) {
				enemy.x = walk_queue.back().x;
				enemy.y = walk_queue.back().y;
				walk_queue.pop_back();
			}
		}
};

