#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

#include "./consts.h"
#include "./config.h"
#include "./scene.h"
#include "./window.h"


int main()
{
    game::win mwindow; game::gtime time; game::config conf;

    while (mwindow.window.isOpen() && !mwindow.restart)
    {
        time.start();
        switch (mwindow.current_scene) {
        case 'm':
            mwindow.windowEvent();
            if (mwindow.menu.button_array[0].isPressed(mwindow.window)) { return 0; }
            if (mwindow.menu.button_array[1].isPressed(mwindow.window)) { mwindow.current_scene = 's'; }
            if (mwindow.menu.button_array[2].isPressed(mwindow.window)) {
                mwindow.tetris.new_game();
                mwindow.current_scene = 'g';
            }
            mwindow << mwindow.menu;
            break;
        case 's':
            mwindow.windowEvent();
            if (mwindow.settings.button_array[0].isPressed(mwindow.window)) { mwindow.current_scene = 'm'; }
            for (int i = 0; i < N_RES; i++) { if (mwindow.settings.button_array[i + 1].isPressed(mwindow.window)) { mwindow.change_resolution(i); } }
            if (mwindow.settings.button_array[6].isPressed(mwindow.window)) { mwindow.reload(); }
            for (int i = 0; i < N_THEMES; i++) { if (mwindow.settings.button_array[i + 7].isPressed(mwindow.window)) { mwindow.change_theme(i); } }
            if (mwindow.settings.button_array[10].isPressed(mwindow.window)) { conf.save(); }
            mwindow << mwindow.settings;
            break;
        case 'g':
            mwindow.tetris.clear_falling();
            mwindow.windowEvent();
            if (time.fall()) { mwindow.fall(); }
            mwindow.tetris.insert_falling();
            mwindow << mwindow.game;
            break;

        }
        time.end();
    }

    return 0;
}