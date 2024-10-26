#ifndef GAME_H
#define GAME_H

enum GameState {
    STATE_HOME,
    STATE_MENU,
    STATE_SAVELIST,
    STATE_GAME,
    STATE_BATTLE
};

void run_game();

#endif
