#pragma once
#include <string>

#include "./scene.h"
#include "./logic.h"

namespace game {
	class score_count {
	protected:
		friend class logic;
		int x;
		int lines_cleared; int cleared_total;
		int mult; int distance; int lvl;
			std::string narrow_read(long int ms) {
				int help = ms % 1000;
				std::string out = std::to_string(help);
				if (help < 100) { out = '0' + out; }
				if (help < 10) { out = '0' + out; }
				out = ':' + out;
				ms /= 1000;
				help = ms % 60;
				out = std::to_string(help) + out;
				if (help < 10) { out = '0' + out; }
				out = ':' + out;
				ms /= 60;
				out = std::to_string(ms) + out;
				return out;
			}
	public:
		static float speed;

		void Lsave(std::string name, long int t, int mode) {
			std::string lineOut = name + "\t";
			std::string lineIn;
			lineOut += std::to_string(x);

			if (mode == 1) {
				lineOut += '\t' + std::to_string(t);
				std::fstream scores;
				scores.open("./rsc/scores/lines.txt");
				int linesN = 0;
				while (std::getline(scores, lineIn)) {
					linesN++;
				}
				scores.close();
				linesN++;
				std::string* all_scores = new std::string[linesN];
				scores.open("./rsc/scores/lines.txt");
				int put = 0;
				for (int i = 0; i < linesN; i++) {
					std::string stime = "";
					std::getline(scores, lineIn);
					int j = lineIn.length();
					if (i == linesN - 1 && !put) {
						all_scores[i] = lineOut;
						break;
					}
					while (lineIn[j] != '\t') {
						stime = lineIn[j] + stime;
						j--;
					}
					if (stoi(stime) > t && !put) {
						all_scores[i] = lineOut;
						i++;
						put = 1;
					}
					all_scores[i] = lineIn;
				}
				std::string out;
				int k;
				for (k = 0; k < linesN - 1; k++) {
					out += all_scores[k] + "\n";
				}
				out += all_scores[k];
				//std::cout << out;
				scores.close();
				std::ofstream outfile;
				outfile.open("./rsc/scores/lines.txt", std::ios::trunc);
				outfile << out;
				outfile.close();
				delete[] all_scores;
			}

			if (mode == 2) {
				std::fstream scores;
				scores.open("./rsc/scores/fast.txt");
				int linesN = 0, put = 0;
				while (std::getline(scores, lineIn)) {
					linesN++;
				}
				scores.close();

				scores.open("./rsc/scores/fast.txt");
				linesN++;
				std::string* all_scores = new std::string[linesN];
				int iscore;
				for (int i = 0; i < linesN; i++) {
					std::string sscore = "";
					std::getline(scores, lineIn);
					int j = lineIn.length();
					if (i == linesN - 1 && !put) {
						all_scores[i] = lineOut;
						break;
					}
					while (lineIn[j] != '\t') {
						sscore = lineIn[j] + sscore;
						j--;
					}
					if (stoi(sscore) < x && !put) {
						all_scores[i] = lineOut;
						i++;
						put = 1;
					}
					all_scores[i] = lineIn;
				}
				scores.close();
				std::string out;
				int k;
				for (k = 0; k < linesN - 1; k++) {
					out += all_scores[k] + "\n";
				}
				out += all_scores[k];
				//std::cout << out;
				scores.close();
				std::ofstream outfile;
				outfile.open("./rsc/scores/fast.txt", std::ios::trunc);
				outfile << out;
				outfile.close();
				delete[] all_scores;
			}

			if (mode == 0) {
				lineOut += '\t' + std::to_string(t);
				std::fstream scores;
				scores.open("./rsc/scores/endless.txt");
				int linesN = 0, put = 0;
				while (std::getline(scores, lineIn)) {
					linesN++;
				}
				scores.close();

				scores.open("./rsc/scores/endless.txt");
				linesN++;
				std::string* all_scores = new std::string[linesN];
				int iscore;
				for (int i = 0; i < linesN; i++) {
					std::string sscore = "";
					std::getline(scores, lineIn);
					int j = lineIn.length();
					if (i == linesN - 1 && !put) {
						all_scores[i] = lineOut;
						break;
					}
					while (lineIn[j] != '\t') {
						j--;
					}
					j--;
					while (lineIn[j] != '\t') {
						sscore = lineIn[j] + sscore;
						j--;
					}
					if (stoi(sscore) < x && !put) {
						all_scores[i] = lineOut;
						i++;
						put = 1;
					}
					all_scores[i] = lineIn;
				}
				scores.close();
				std::string out;
				int k;
				for (k = 0; k < linesN - 1; k++) {
					out += all_scores[k] + "\n";
				}
				out += all_scores[k];
				//std::cout << out;
				scores.close();
				std::ofstream outfile;
				outfile.open("./rsc/scores/endless.txt", std::ios::trunc);
				outfile << out;
				outfile.close();
				delete[] all_scores;
			}
		}

		std::string Lget(int mode) {
			std::string out = "", in, stime;
			std::fstream file;
			if (mode == 2) {
				file.open("./rsc/scores/fast.txt");
				int k = 1;
				while (std::getline(file, in) && k <= 10) {
					out += std::to_string(k++) + ". " + in + "\n";
				}
			}
			else {
				if (mode == 1) { file.open("./rsc/scores/lines.txt"); }
				if (mode == 0) { file.open("./rsc/scores/endless.txt"); }
				int k = 1, itime;
				while (std::getline(file, in) && k <= 10) {
					int i;
					for (i = in.length(); in[i] != '\t'; i--) {
						stime = in[i] + stime;
					}
					in.erase(i + 1, in.length());
					in += narrow_read(std::stoi(stime));
					out += std::to_string(k++) + ".";
					if (k <= 10) { out += " "; }
					out += in + "\n";
				}
			}
			file.close();
			return out;
		}

		score_count() {
			score_reset();
		}

		void score_reset() {
			x = 0;
			lines_cleared = 0;
			cleared_total = 0;
			mult = 0;
			distance = 0;
			lvl = 1;
			speed = 1000.f;
		}

		std::wstring get() {
			return L"Punkty: " + std::to_wstring(x) + L"\nZbite linie: " + std::to_wstring(cleared_total) + L"\nPoziom: " + std::to_wstring(lvl);
		}

		int is40() {
			if (cleared_total >= 40) { return 1; }
			return 0;
		}

		void update_score(scene::text* sidebar, char mode = 'e') {
			int add_score = 0;
			cleared_total += lines_cleared;
			add_score += distance;
			int l = lvl;
			if (mode == 0) { lvl = cleared_total / 10 + 1; }
			if (l != lvl) { speed *= 2.f / 3.f; }
			std::wstring cleared_display = L"";
			if (lines_cleared == 1) { add_score += 100; cleared_display = L"SINGLE"; }
			if (lines_cleared == 2) { add_score += 300; cleared_display = L"DOUBLE!"; }
			if (lines_cleared == 3) { add_score += 500; cleared_display = L"TRIPLE!!"; }
			if (lines_cleared == 4) { add_score += 800; cleared_display = L"TETRIS!!!"; }
			if (lines_cleared != 0) { mult++; }
			else { mult = 0; }
			add_score += 50 * mult;
			x += add_score * lvl;
			sidebar[3].update(x);
			sidebar[5].update(lvl);
			sidebar[7].update(cleared_total);
			if (mult > 1) {
				sidebar[8].update(L"Mno¿nik:", 0);
				sidebar[9].update(std::to_wstring(mult) + L'x');
			}
			else {
				sidebar[8].update(L"");
				sidebar[9].update(L"");
			}
			sidebar[10].update(cleared_display);
		}
	};
	float score_count::speed;
};