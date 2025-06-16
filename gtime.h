#pragma once
#include <SFML/Graphics.hpp>
#include "./score.h"

#include <string>

namespace game{
    class gtime {
    private:
        sf::Clock dClock;
        int sync = 0; int direction = 1;
        sf::Time delta;
    public:
        static long int total;
        void start() {
            delta = dClock.restart();
        }
        int fall() {
            if (sync > score_count::speed) {
                sync = 0;
                return 1;
            }
            return 0;
        }
        void end() {
            total += delta.asMilliseconds() * direction;
            sync += delta.asMilliseconds();
        }
        void reset() {
            total = 0;
            direction = 1;
        }
        void reverse() {
            total = 2 * 60 * 1000;
            direction = -1;
        }
        static std::wstring read(long int ms = total) {
            int help = ms % 1000;
            std::wstring out = std::to_wstring(help);
            if (help < 100) { out = L'0' + out; }
            if (help < 10) { out = L'0' + out; }
            out = L':' + out;
            ms /= 1000;
            help = ms % 60;
            out = std::to_wstring(help) + out;
            if (help < 10) { out = L'0' + out; }
            out = L':' + out;
            ms /= 60;
            out = std::to_wstring(ms) + out;
            return out;
        }
    };
    long int gtime::total;
};