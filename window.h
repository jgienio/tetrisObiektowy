#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "./consts.h"
#include "./config.h"
#include "./scene.h"
#include "./logic.h"
#include "./score.h"
#include "./gtime.h"

namespace game {
    class win {
    private:
        int yconst(int i) {
            if (i % 2) { return config::shiftY + config::bloc_size * (4 + i) + 20 * config::scale; }
            return config::shiftY + config::bloc_size * (5 + i);
        }
    public:
        sf::RenderWindow window;
        char current_scene;
        scene menu, settings, game, defeat;
        logic tetris;
        score_count points;
        int restart = 0;
        float speedtemp = score_count::speed;
        int mode;
        void make(char start) {
            window.create(sf::VideoMode(config::get().res_w, config::get().res_h), "Tetris Obiektowy");
            window.setFramerateLimit(60);

            menu.id = 'm';
            menu.make_txt(80, 50, 10, "TETRIS++v2", 'c');
            menu.make_btn(35, 15, 75, "Zamknij");
            menu.make_btn(35, 66, 75, "Opcje");
            menu.make_btn(35, 15, 30, "Maraton");
            menu.make_btn(35, 15, 35, "40 linii");
            menu.make_btn(35, 15, 40, "2 minuty");

            settings.id = 's';
            settings.make_txt(80, 50, 10, "OPCJE", 'c');
            settings.make_btn(35, 20, 80, "Menu");
            settings.make_txt(35, 20, 25, "Rozdzielczosc");
            settings.make_btn(20, 20, 33, "800x600");
            settings.make_btn(20, 20, 36, "1280x720");
            settings.make_btn(20, 20, 39, "1600x900");
            settings.make_btn(20, 20, 42, "1920x1080");
            settings.make_btn(20, 20, 45, "2500x1500");
            settings.make_btn(35, 66, 80, "Zastosuj");
            settings.make_txt(35, 66, 25, "Motyw");
            settings.make_btn(20, 66, 33, "Test");
            settings.make_btn(20, 66, 36, "Mono");
            settings.make_btn(20, 66, 39, "Retro");
            settings.make_btn(35, 66, 85, "Zapisz");
            settings.make_txt(35, 20, 50, "Klawisze");
            settings.make_btn(20, 20, 58, "Strzalki");
            settings.make_btn(20, 20, 61, "DFJK");
            settings.make_txt(35, 66, 45, "Duszki?");
            settings.make_btn(20, 75, 53, "Nie");
            settings.make_btn(20, 66, 53, "Tak");
            for (int i = 0; i < N_RES; i++) {
                if (config::get().res[i].isSet) { settings.button_array[i + 1].set(); }
            }
            for (int i = 0; i < N_THEMES; i++) {
                if (config::get().themes[i].isSet) { settings.button_array[i + 7].set(); }
            }
            settings.button_array[13 + config::display_ghosts].set();
            settings.button_array[config::setbuttons + 11].set();
            settings.text_array[1].update(L"Rozdzielczoœæ", 0);

            game.id = 'g';
            const int xconst = config::get().shiftX + config::get().bloc_size * 15 + BORDER * config::get().scale * 2;
            game.make_txt(20, xconst, yconst(0), "Czas:", 'l', 'p');
            game.make_txt(30, xconst, yconst(1), "0", 'l', 'p');
            game.make_txt(20, xconst, yconst(2), "Wynik:", 'l', 'p');
            game.make_txt(30, xconst, yconst(3), "0", 'l', 'p');
            game.make_txt(20, xconst, yconst(4), "Poziom:", 'l', 'p');
            game.make_txt(30, xconst, yconst(5), "1", 'l', 'p');
            game.make_txt(20, xconst, yconst(6), "Linie:", 'l', 'p');
            game.make_txt(30, xconst, yconst(7), "0", 'l', 'p');
            game.make_txt(20, xconst, yconst(8), "", 'l', 'p');
            game.make_txt(30, xconst, yconst(9), "", 'l', 'p');
            game.make_txt(30, xconst, yconst(11), "", 'l', 'p');

            defeat.id = 'l';
            defeat.make_txt(80, 50, 10, "Przegrana :(", 'c');
            defeat.make_btn(35, 50, 70, "Menu", 'c');
            defeat.make_txt(25, 40, 33, "");
            defeat.make_txt(35, 50, 25, "Statystyki", 'c');

            current_scene = start;
        }
        win() {
            make('m');
        }

        void reload() {
            restart = 1;
            window.close();
            menu.del();
            settings.del();
            game.del();
            defeat.del();
            config::res_background();
            make('s');
            restart = 0;
        }

        void change_resolution(int n) {
            config::res_set(n);
            for (int i = 0; i < N_RES; i++) {
                if (config::get().res[i].isSet) { settings.button_array[i + 1].set(); }
                else { settings.button_array[i + 1].unset(); }
            }
        }

        void change_theme(int n) {
            config::thm_set(n);
            for (int i = 0; i < N_THEMES; i++) {
                if (config::get().themes[i].isSet) { settings.button_array[i + 7].set(); }
                else { settings.button_array[i + 7].unset(); }
            }
        }

        void change_button_map(int n) {
            config::but_set(n);
            for (int i = 0; i < N_BUTTONS; i++) {
                settings.button_array[i + 11].unset();
            }
            settings.button_array[config::setbuttons + 11].set();
        }

        void toggleGhost(int n) {
            config::display_ghosts = n;
            for (int i = 13; i <= 14;i++) { settings.button_array[i].unset(); }
            settings.button_array[13 + n].set();
        }

        void windowEvent() {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) { window.close(); }
                if (event.type == sf::Event::Resized) { window.setSize(sf::Vector2u(config::get().res_w, config::get().res_h)); }
                if (event.type == sf::Event::KeyPressed && current_scene == 'g') {
                    tetris.clear_ghost();
                    if (event.key.code == config::button_map[config::setbuttons].pause) { current_scene = 'm'; }
                    if (event.key.code == config::button_map[config::setbuttons].moveL) { tetris.moveLeft(); }
                    else if (event.key.code == config::button_map[config::setbuttons].moveR) { tetris.moveRight(); }
                    if (event.key.code == config::button_map[config::setbuttons].rotateR) { tetris.rotateRight(); }
                    else if (event.key.code == config::button_map[config::setbuttons].rotateL) { tetris.rotateLeft(); }
                    if (event.key.code == config::button_map[config::setbuttons].hold) { tetris.hold(); }
                    if (event.key.code == config::button_map[config::setbuttons].softDrop) { score_count::speed = speedtemp / 10; }
                    tetris.ghost_update();
                    if (event.key.code == config::button_map[config::setbuttons].hardDrop) { 
                        drop(2);
                    }
                }
                if (event.type == sf::Event::KeyReleased && current_scene == 'g') {
                    if (event.key.code == config::button_map[config::setbuttons].softDrop) { score_count::speed = speedtemp; }
                }
            }
        }

        void fall() {
            if (!tetris.check_down_falling()) { tetris.y++; }
            else { drop(1); }
        }

        void newgame() {
            game.text_array[1].update();
            game.text_array[3].update();
            game.text_array[5].update(1);
            game.text_array[7].update();
            points.score_reset();
            tetris.new_game();
        }

        void drop(int x) {
            if (!tetris.drop(&points, &game, x, mode)) { 
                defeat.text_array[0].update(L"Przegrana :(");
                defeat.text_array[1].update(points.get(), 0);
                current_scene = 'l'; 
            }
            if (mode == 1 && points.is40()) {
                defeat.text_array[0].update(L"Wygrana!! :D");
                defeat.text_array[1].update(points.get(), 0);
                current_scene = 'l';
            }
            if (mode == 2 && gtime::total <= 0) {
                defeat.text_array[0].update(L"Wygrana!! :D");
                defeat.text_array[1].update(points.get(), 0);
                current_scene = 'l';
            }
            speedtemp = score_count::speed;
        }

        void uptime(gtime t) {
            game.text_array[1].update(t.read());
        }

        void operator<<(const scene& disp) {
            window.clear();
            window.draw(config::get().background);
            if (disp.id == game.id) {
                window.draw(config::get().board);
                for (int x = 0; x < 10; x++) {
                    for (int y = 0; y < 20; y++) {
                        if (tetris.field[x][y] != 0) {
                            sf::Sprite bloc;
                            bloc.setPosition(float(x * config::bloc_size + config::shiftX), float(y * config::bloc_size + config::shiftY));
                            if (tetris.field[x][y] > 0) { bloc.setTexture(config::tetriminos[tetris.field[x][y]]); }
                            else {
                                bloc.setTexture(config::tetriminos[-tetris.field[x][y]]);
                                bloc.setColor(sf::Color(255, 255, 255, 128 * config::display_ghosts));
                            }
                            bloc.scale(config::scale, config::scale);
                            window.draw(bloc);
                        }
                    }
                }
                for (int q = 0; q < 4; q++) {
                    for (int i = 0; i < tetris.tetr[tetris.queue[q]].size; i++) {
                        for (int j = 0; j < tetris.tetr[tetris.queue[q]].size; j++) {
                            if (tetris.tetr[tetris.queue[q]].shape[i + 4 * j] != 0) {
                                sf::Sprite bloc;
                                bloc.setPosition(float(i * config::bloc_size + config::shiftHoldX + config::bloc_size * (4 - tetris.tetr[tetris.queue[q]].size) / 2),
                                    float(j * config::bloc_size + config::shiftHoldY + ((q + 1) % 4) * 5 * config::bloc_size) + config::bloc_size * (4 - tetris.tetr[tetris.queue[q]].size) / 2);
                                bloc.setTexture(config::tetriminos[tetris.queue[q]]);
                                bloc.scale(config::scale, config::scale);
                                window.draw(bloc);
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < disp.noTXT; i++) {
                window.draw(disp.text_array[i].display());
            }
            for (int i = 0; i < disp.noBTN; i++) {
                window.draw(disp.button_array[i].display());
            }
            window.display();
        }
    };
};