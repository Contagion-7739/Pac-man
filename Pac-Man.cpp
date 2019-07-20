#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <queue>
using namespace std;

const int N = 10, M = 43;
char mp[10][50] = 
{
	"############################################",
	"#............         .....................#",
	"#............         .....................#",
	"#.....#    ..#  #  #   #.. ###  ###..### ..#",
	"#....# #   ..# #   ##  #..#   #  # ..#  #..#",
	"#...#####  ..##1234# # #..#   #  # ..####..#",
	"#..#     # ..# #   #  ##..#   #  # ..#   ..#",
	"#.#.......#..#  ####   #.. ###  ###..#.....#",
	"#.........................................H#",
	"############################################"
};
char noghost[10][50] = 
{
	"############################################",
	"#............         .....................#",
	"#............         .....................#",
	"#.....#    ..#  #  #   #.. ###  ###..### ..#",
	"#....# #   ..# #   ##  #..#   #  # ..#  #..#",
	"#...#####  ..##    # # #..#   #  # ..####..#",
	"#..#     # ..# #   #  ##..#   #  # ..#   ..#",
	"#.#.......#..#  ####   #.. ###  ###..#.....#",
	"#.........................................H#",
	"############################################"
};
const int Next[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int dir = 1;//0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT
int px = 2, py = 17, kcnt;
int dist[15][55], ghostp[4][2] = {{5, 7}, {5, 8}, {5, 9}, {5, 10}}, initg[4][2];

void Prefix() {
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			kcnt += mp[i][j] == '.';
			if (mp[i][j] == 'H') {
				px = i;
				py = j;
			}
			if (mp[i][j] >= '0' && mp[i][j] <= '9') {
				ghostp[mp[i][j] - '1'][0] = i;
				ghostp[mp[i][j] - '1'][1] = j;
				initg[mp[i][j] - '1'][0] = i;
				initg[mp[i][j] - '1'][1] = j;
			}
		}
	}
}

void Display() {
	for (int i = 0;i < N;i++) {
		puts(mp[i]);
	}
}

void MovePlayer() {
	switch (mp[px + Next[dir][0]][py + Next[dir][1]]) {
		case '#':
			break;
		case '1':
			system("cls");
			puts("GAME OVER");
			while (1);
		case '2':
			system("cls");
			puts("GAME OVER");
			while (1);
		case '3':
			system("cls");
			puts("GAME OVER");
			while (1);
		case '4':
			system("cls");
			puts("GAME OVER");
			while (1);
		case '.':
			kcnt--;
			mp[px][py] = ' ';
			noghost[px][py] = ' ';
			px += Next[dir][0]; py += Next[dir][1];
			mp[px][py] = 'H';
			noghost[px][py] = 'H';
			break;
		case ' ':
			mp[px][py] = ' ';
			noghost[px][py] = ' ';
			px += Next[dir][0]; py += Next[dir][1];
			mp[px][py] = 'H';
			noghost[px][py] = 'H';
			break;
	}
}

void Bfs() {
	queue <pair <int, int> > que;
	que.push(make_pair(px, py));
	memset(dist, 0x3f, sizeof(dist));
	dist[px][py] = 0;
	while (!que.empty()) {
		int ux = que.front().first, uy = que.front().second;
		que.pop();
		for (int i = 0;i < 4;i++) {
			int tx = ux + Next[i][0], ty = uy + Next[i][1];
			if (tx < 0 || tx >= N || ty < 0 || ty >= M) {
				continue;
			}
			if (mp[tx][ty] != '#' && (mp[tx][ty] < '0' || mp[tx][ty] > '9') && dist[tx][ty] == 0x3f3f3f3f) {
				dist[tx][ty] = dist[ux][uy] + 1;
				que.push(make_pair(tx, ty));
			}
		}
	}
}

void MoveEnemy() {
	Bfs();
	for (int i = 0;i < 4;i++) {
		int mind = -1, minv = 0x3f3f3f3f;
		for (int j = 0;j < 4;j++) {
			if (dist[ghostp[i][0] + Next[j][0]][ghostp[i][1] + Next[j][1]] < minv) {
				minv = dist[ghostp[i][0] + Next[j][0]][ghostp[i][1] + Next[j][1]];
				mind = j;
			}
		}
		if (mind != -1) {
			mp[ghostp[i][0]][ghostp[i][1]] = noghost[ghostp[i][0]][ghostp[i][1]];
			ghostp[i][0] += Next[mind][0]; ghostp[i][1] += Next[mind][1];
			if (mp[ghostp[i][0]][ghostp[i][1]] == 'H') {
				system("cls");
				puts("GAME OVER");
				while (1);
			}
			mp[ghostp[i][0]][ghostp[i][1]] = i + 49;
		}
	}
}

void Game() {
	int round = 0;
	while (1) {
		system("cls");
		Display();
		Sleep(500);
		if (_kbhit()) {
			char c = getch();
			switch (c) {
				case 'w':
					dir = 0;
					break;
				case 's':
					dir = 1;
					break;
				case 'a':
					dir = 2;
					break;
				case 'd':
					dir = 3;
					break;
			}
		}
		MovePlayer();
		MoveEnemy();
		round++;
		if (round % 20 == 0) {
			for (int i = 0;i < 4;i++) {
				mp[ghostp[i][0]][ghostp[i][1]] = noghost[ghostp[i][0]][ghostp[i][1]];
				mp[initg[i][0]][initg[i][1]] = i + 49;
				ghostp[i][0] = initg[i][0]; ghostp[i][1] = initg[i][1];
			}
		}
		if (kcnt == 0) {
			system("cls");
			Display();
			Sleep(1000);
			printf("YOU WIN!");
			while (1);
		}
	}
}

int main() {
	Prefix();
	printf("PAC-MAN\n");
	printf("Press W,S,A,D to move the Pac-man(H) around\n");
	printf("Once Pac-man touch one of the ghost(1,2,3,4), the game ends and the player lose\n");
	printf("Once Pac-man eats all of the dots, the game ends and the player win\n");
	printf("Every 20 rounds the ghosts will move to their home\n");
	printf("Preview the map:\n");
	Display();
	getch();
	system("cls");
	Game();
	return 0;
}

