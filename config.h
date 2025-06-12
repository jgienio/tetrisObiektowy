#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "./consts.h"
namespace game {
    class config {
    private:
        static sf::Texture tBGR, tBoard;
        class resolution {
        public:
            int w; int h;
            int isSet;
            float scale;
            void create(int x, int y, float sc) {
                w = x; h = y; scale = sc; isSet = 0;
            }
        };
        class theme {
        public:
            sf::Color text, button;
            std::string path;
            int isSet = 0;
            void create(int rt, int gt, int bt, int rb, int gb, int bb, std::string p) {
                text.r = rt; text.g = gt; text.b = bt;
                button.r = rb; button.g = gb; button.b = bb;
                path = p; isSet = 0;
            }
        };
        class savable {
        public:
            int res; int thm;
        };
    public:
        static int res_w, res_h;
        static int shiftX, shiftY;
        static int shiftHoldX, shiftHoldY;
        static float bloc_size;
        static float scale;
        static sf::Font font;
        static sf::Color txt_color, btn_color;
        static sf::Texture tetriminos[8];
        static sf::Sprite background, board;
        static resolution res[N_RES];
        static theme themes[N_THEMES];
        static std::string path;
        savable current;
        void doc() {
            res[0].create(800, 600, 1.f);
            res[1].create(1200, 720, 1.2);
            res[2].create(1600, 900, 1.5);
            res[3].create(1920, 1080, 1.5);
            res[4].create(2500, 1500, 2.f);
            res_set(current.res);

            themes[0].create(0, 0, 0, 255, 0, 0, "test");
            themes[1].create(0, 0, 0, 255, 0, 0, "mono");
            themes[2].create(15, 52, 15, 48, 95, 48, "retro");
            thm_set(current.thm);

            bloc_size = SIZE_T * scale;
            shiftX = (res_w - BOARD_W * scale) / 2 + BORDER * scale;
            shiftY = (res_h / 2) - bloc_size * 10;
            shiftHoldX = shiftX + bloc_size * 12;
            shiftHoldY = shiftY + bloc_size;

            font.loadFromFile("./rsc/PTMono.ttf");
            res_background();

            txt_color = sf::Color::Black;
            btn_color = sf::Color::Red;
        }
        config() {
            load();
            doc();
        }
        static config& get() {
            static config i;
            return i;
        }
        static void res_set(int n) {
            for (int i = 0; i < N_RES; i++) { res[i].isSet = 0; }
            res_w = res[n].w;
            res_h = res[n].h;
            scale = res[n].scale;
            res[n].isSet = 1;
        }
        static void thm_set(int n) {
            for (int i = 0; i < N_THEMES; i++) { themes[i].isSet = 0; }
            themes[n].isSet = 1;
            txt_color = themes[n].text;
            btn_color = themes[n].button;
            path = themes[n].path;
        }
        static void res_background() {
            bloc_size = SIZE_T * scale;
            shiftX = (res_w - BOARD_W * scale) / 2 + BORDER * scale;
            shiftY = (res_h / 2) - bloc_size * 10;
            shiftHoldX = shiftX + bloc_size * 12;
            shiftHoldY = shiftY + bloc_size;
            tBGR.loadFromFile("./themes/" + path + "/background.png");
            background.setTexture(tBGR);
            background.setScale(res_w / float(BACKGROUND_W), res_w / float(BACKGROUND_W));
            background.setPosition(0, -((((res_w / float(BACKGROUND_W)) * BACKGROUND_H) - res_h) / 2));
            tBoard.loadFromFile("./themes/" + path + "/board.png");
            tBoard.setSmooth(true);
            board.setTexture(tBoard);
            board.setPosition(shiftX - BORDER * scale, shiftY - BORDER * scale);
            board.setScale(scale, scale);
            for (int i = 0; i < 8; i++) {
                tetriminos[i].loadFromFile("./themes/" + path + "/tetriminos.png", sf::IntRect(i * SIZE_T, 0, SIZE_T, SIZE_T));
            }
        }
        void save() {
            for (int i = 0; i < N_RES;i++) { if (res[i].isSet) { current.res = i; } }
            for (int i = 0; i < N_THEMES;i++) { if (themes[i].isSet) { current.thm = i; } }
            std::fstream confile("./rsc/conf.bin", std::ios::binary | std::ios::out | std::ios::trunc);
            confile.write((char*)&current, sizeof(savable));
            confile.close();
        }
        void load() {
            std::fstream confile("./rsc/conf.bin", std::ios::binary | std::ios::in);
            confile.seekg(0);
            confile.read((char*)&current, sizeof(savable));
            confile.close();
        }
    };
    sf::Font config::font;
    sf::Color config::txt_color, config::btn_color;
    sf::Sprite config::background, config::board;
    int config::res_w, config::res_h;
    int config::shiftX, config::shiftY;
    int config::shiftHoldX, config::shiftHoldY;
    float config::scale, config::bloc_size;
    config::resolution config::res[];
    config::theme config::themes[];
    std::string config::path;
    sf::Texture config::tBGR, config::tBoard, config::tetriminos[8];
};