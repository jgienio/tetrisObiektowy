#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "./consts.h"
#include "./config.h"

namespace game {
    class scene {
    protected:
        friend class score_count;
        class text {
        protected:
            friend class score_count;
            sf::Text sfml_Text;
        public:
            text() {
                sfml_Text.setFont(config::get().font);
                sfml_Text.setFillColor(config::get().txt_color);
                sfml_Text.setCharacterSize(24);
                sfml_Text.setPosition(0, 0);
                sfml_Text.setString("content");
            }
            void make(int size, int x, int y, char alignment, std::string content) {
                sfml_Text.setFont(config::get().font);
                sfml_Text.setFillColor(config::get().txt_color);
                sfml_Text.setCharacterSize(size);
                float shift = 0;
                if (alignment == 'c') { shift = (size / FONT_CONST) * content.length() / 2; }
                sfml_Text.setPosition(x - shift, y);
                sfml_Text.setString(content);
            }
            sf::Text display() { return sfml_Text; }
            void visibility(int toggle) {
                if (toggle == 0) { sfml_Text.setFillColor(sf::Color::Transparent); }
                else { sfml_Text.setFillColor(config::txt_color); }
            }
            void update(int x = 0) {
                sfml_Text.setString(std::to_string(x));
                sfml_Text.setStyle(sf::Text::Bold);
            }
            void update(std::wstring x, int isBold = 1) {
                sfml_Text.setString(x);
                if (isBold) { sfml_Text.setStyle(sf::Text::Bold); }
                else { sfml_Text.setStyle(sf::Text::Regular); }
            }
            void update(std::string x) {
                sfml_Text.setString(x);
            }
        };
        class button : public text {
        public:
            int isHovered(sf::RenderWindow& win) {
                sf::Vector2f mouse(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y);
                if (sfml_Text.getGlobalBounds().contains(mouse)) {
                    sfml_Text.setFillColor(config::btn_color);
                    return 1;
                }
                sfml_Text.setFillColor(config::txt_color);
                return 0;
            }
            int isPressed(sf::RenderWindow& win) {
                if (isHovered(win) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) { return 1; }
                return 0;
            }
            void set() {
                sfml_Text.setStyle(sf::Text::Italic);
                if (sfml_Text.getString()[0] != '>') { sfml_Text.setString("> " + sfml_Text.getString()); }
            }
            void unset() {
                sfml_Text.setStyle(sf::Text::Regular);
                if (sfml_Text.getString()[0] == '>') { sfml_Text.setString(sfml_Text.getString().substring(2)); }
            }
        };
    public:
        char id;
        int noTXT; int noBTN;
        text* text_array;
        button* button_array;
        scene(char x = 'a') {
            id = x;
            text_array = button_array = NULL;
            noTXT = noBTN = 0;
        }
        void del() {
            if (noBTN != 0) { delete[] button_array; }
            if (noTXT != 0) { delete[] text_array; }
            noTXT = noBTN = 0;
        }
        ~scene() {
            if (noBTN != 0) { delete[] button_array; }
            if (noTXT != 0) { delete[] text_array; }
        }
        void make_txt(int size, float x, float y, std::string content, char alignment = 'l', char type = '%') {
            text* new_array = new text[noTXT + 1];
            if (noTXT != 0) {
                std::copy(text_array, text_array + noTXT, new_array);
                delete[] text_array;
            }
            text_array = new_array;
            if (type == '%') { text_array[noTXT].make(size * config::get().scale, x / 100 * config::get().res_w, y / 100 * config::get().res_h, alignment, content); }
            else { text_array[noTXT].make(size * config::get().scale, x, y, alignment, content); }
            noTXT++;
        }

        void make_btn(int size, float x, float y, std::string content, char alignment = 'l') {
            button* new_array = new button[noBTN + 1];
            if (noBTN != 0) {
                std::copy(button_array, button_array + noBTN, new_array);
                delete[] button_array;
            }
            button_array = new_array;
            button_array[noBTN].make(size * config::get().scale, x / 100 * config::get().res_w, y / 100 * config::get().res_h, alignment, content);
            noBTN++;
        }
    };
};