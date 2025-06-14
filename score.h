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
    public:
        static float speed;

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

        void update_score(scene::text* sidebar, char mode = 'e') {
            int add_score = 0;
            cleared_total += lines_cleared;
            add_score += distance;
            int l = lvl;
            if (mode == 'e') { lvl = cleared_total / 10 + 1; }
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
}