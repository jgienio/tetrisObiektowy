#pragma once
#include <SFML/Graphics.hpp>
#include "./score.h"

#include <string>

namespace game{
    class gtime {
    private:
        sf::Clock dClock;
        long int total = 0;
        int sync = 0; int direction = 1;
        sf::Time delta;
    public:
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
        void reset(int d = 1) {
            total = 0;
            direction = d;
        }
        std::string read() {
            long int ms = total;
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
    };
};