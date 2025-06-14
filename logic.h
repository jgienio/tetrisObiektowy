#pragma once
#include <ctime>
#include <cstdlib>
#include "./window.h"
#include "./scene.h"
#include "./score.h"

namespace game {
	class score_count;
	class logic {
	private:
		struct tetromino {
			int shape[16];
			int size;
			int texture;
		};

		int check_down(struct tetromino bloc, int x, int y) {
			if (y > 20 - bloc.size - boundD()) { return 1; }
			for (int i = 0; i < bloc.size; i++) {
				for (int j = 0; j < bloc.size; j++) {
					if (bloc.shape[i + 4 * j]) {
						if (field[i + x][y + j + 1] > 0) { return 1; }
					}
				}
			}
			return 0;
		}

		void insert(struct tetromino n, int x, int y) {
			for (int i = 0; i < n.size; i++) {
				for (int j = 0; j < n.size; j++) {
					if (n.shape[i + 4 * j]) { field[i + x][y + j] = n.texture; }
				}
			}
		}

		void clear(struct tetromino n, int x, int y) {
			for (int i = 0; i < n.size; i++) {
				for (int j = 0; j < n.size; j++) {
					if (n.shape[i + 4 * j]) { field[i + x][y + j] = 0; }
				}
			}
		}

		struct tetromino rotate_r() {
			struct tetromino tout = tetr[0];
			tout.size = bloc.size;
			tout.texture = bloc.texture;
			for (int y = 0; y < bloc.size; y++) {
				for (int x = 0; x < bloc.size; x++) {
					tout.shape[x + y * 4] = bloc.shape[y + ((bloc.size - 1 - x) * 4)];
				}
			}
			return tout;
		}

		struct tetromino rotate_l() {
			struct tetromino tout = tetr[0];
			tout.size = bloc.size;
			tout.texture = bloc.texture;
			for (int y = 0; y < bloc.size; y++) {
				for (int x = 0; x < bloc.size; x++) {
					tout.shape[y + ((bloc.size - 1 - x) * 4)] = bloc.shape[x + y * 4];
				}
			}
			return tout;
		}
	public:
		logic() {
			srand(time(NULL));
		}
		int field[10][20] = { 0 };
		struct tetromino tetr[8] = {
			{
				{
					0,0,0,0,
					0,0,0,0,
					0,0,0,0,
					0,0,0,0,
				},
				4, 0
			},

			{
				{
					1,1,0,0,
					1,1,0,0,
					0,0,0,0,
					0,0,0,0
				},
				2, 1
			},

			{
				{
					0,2,0,0,
					0,2,0,0,
					0,2,0,0,
					0,2,0,0
				},
				4, 2
			},

			{
				{
					0,3,0,0,
					3,3,3,0,
					0,0,0,0,
					0,0,0,0
				},
				3, 3
			},

			{
				{
					4,4,0,0,
					0,4,4,0,
					0,0,0,0,
					0,0,0,0
				},
				3, 4
			},

			{
				{
					0,5,5,0,
					5,5,0,0,
					0,0,0,0,
					0,0,0,0
				},
				3, 5
			},

			{
				{
					0,6,0,0,
					0,6,0,0,
					6,6,0,0,
					0,0,0,0
				},
				3, 6
			},

			{
				{
					0,7,0,0,
					0,7,0,0,
					0,7,7,0,
					0,0,0,0
				},
				3, 7
			},
		};

		int x = 3, y = 0;
		struct tetromino bloc;
		int held = 0; int isHold = 0;
		int queue[4];
		int ghostY; int ghostX = 3;

		void insert_falling() { insert(bloc, x, y); }

		int insertable(struct tetromino bloc, int x, int y) {
			for (int i = 0; i < bloc.size; i++) {
				for (int j = 0; j < bloc.size; j++) {
					if (bloc.shape[i + 4 * j] != 0 && field[x + i][y + j] > 0 || y + j > 19) { return 0; }
				}
			}
			return 1;
		}

		void clear_falling() { clear(bloc, x, y); }
		void clear_ghost() { clear(bloc, ghostX, ghostY); }
		int check_down_falling() { return check_down(bloc, x, y); }

		int basic_check_lines() {
			int j; int mult = 0; int scored[4] = { -1, -1, -1, -1 };
			for (int i = 0; i < 20; i++) {
				for (j = 0; j < 10; j++) {
					if (field[j][i] <= 0) { break; }
				}
				if (j == 10) {
					scored[mult] = i;
					mult++;
				}
			}
			for (int m = 0; m < 4; m++) {
				for (int n = scored[m]; n > 0; n--) {
					for (int o = 0; o < 10; o++) {
						field[o][n] = field[o][n - 1];
					}
				}
			}
			return mult;
		}

		void ghost_update() {
			tetromino ghost = bloc;
			int i = y;
			ghost.texture *= -1;
			while (!check_down(ghost, x, i)) {
				i++;
			}
			insert(ghost, x, i);
			ghostX = x; ghostY = i;
		}

		int boundL() {
			for (int i = 0; i <= 12; i += 4) {
				if (bloc.shape[i] != 0) { return 1; }
			}
			if (bloc.size != 4) { return 0; }
			return bloc.shape[1] == 0 ? -1 : 0;
		}

		int boundR() {
			for (int i = bloc.size - 1; i <= 5 * (bloc.size - 1); i += 4) {
				if (bloc.shape[i] != 0) { return 1; }
			}
			if (bloc.size != 4) { return 0; }
			return bloc.shape[2] == 0 ? -1 : 0;
		}

		int boundD() {
			for (int i = 4 * (bloc.size - 1); i <= 5 * (bloc.size - 1); i++) {
				if (bloc.shape[i] != 0) { return 1; }
			}
			if (bloc.size != 4) { return 0; }
			return bloc.shape[10] == 0 ? -1 : 0;
		}

		void update_queue() {
			bloc = tetr[queue[0]];
			queue[0] = queue[1];
			queue[1] = queue[2];
			queue[2] = (rand() % 7) + 1;
		}

		void moveRight() {
			if ((x < 10 - bloc.size || x <= 10 - bloc.size - boundR()) && insertable(bloc, x + 1, y)) { x++; }
		}

		void moveLeft() {
			if ((x > 0 || boundL() <= x) && insertable(bloc, x - 1, y)) { x--; }
		}

		void rotateRight() {
			if (insertable(rotate_r(), x, y)) {
				if (x < 0) { x = 0; }
				if (x > 10 - bloc.size) { x = 10 - bloc.size; }
				bloc = rotate_r();
			}
		}

		void rotateLeft() {
			if (insertable(rotate_l(), x, y)) {
				if (x < 0) { x = 0; }
				if (x > 10 - bloc.size) { x = 10 - bloc.size; }
				bloc = rotate_l();
			}
		}

		void hold() {
			if (!isHold) {
				isHold = 1;
				clear_falling();
				if (held == 0) {
					held = bloc.texture;
					bloc = tetr[(rand() % 7) + 1];
				}
				else {
					int pom = held;
					held = bloc.texture;
					bloc = tetr[pom];
				}
				x = 3; y = 0;
				queue[3] = held;
			}
		}


		void drop(score_count* score, scene* s, int mult) {
			score->distance = mult * (20 - y);
			insert(bloc, x, ghostY);
			y = 0;
			x = 3;
			score->lines_cleared = basic_check_lines();
			score->update_score(s->text_array);
			update_queue();
			ghost_update();
			isHold = 0;
		}


		void new_game() {
			x = 3; y = 0;
			for (int i = 0; i < 3; i++) { queue[i] = (rand() % 7) + 1; }
			update_queue();
			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 20; y++) {
					field[x][y] = 0;
				}
			}
			held = 0;
			isHold = 0;
			ghost_update();
		}
	};
};