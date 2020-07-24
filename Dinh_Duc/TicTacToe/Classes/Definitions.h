#pragma once

#define SPLASH_SCENE_TIME 1.5
#define SPLASH_SCENE_TRANSITION_TIME 0.5

#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1

#define PLAYER_PIECE X_PIECE
#define AI_PIECE O_PIECE



#define STATE_PLAYERS_TURN 98
#define STATE_PAUSED 97
#define STATE_WON 96
#define STATE_LOSE 95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING 93
#define STATE_DRAW 92


#define PIECE_FADE_IN_TIME 0.5

#define GAME_OVER_BACKGROUND_FADE_IN_TIME 0.5

#define PAUSE_BACKGROUND_FADE_TIME 0.5

#define MENU_MOVE_BOUNCE_DURATION 1.5

struct Move
{
    int x, y;
};