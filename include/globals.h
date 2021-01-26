#pragma once

/**
 * a value used for the general render scale of the game
 */ 
extern const float GAMESCALE_X, GAMESCALE_Y, TEXTSCALE_X, TEXTSCALE_Y;

/**
 * a value used for the general render scale of the game
 */ 
extern const int SCREEN_WIDTH, SCREEN_HEIGHT, GAME_WIDTH, GAME_HEIGHT;

/**
 * a value which tracks the number of game logic updates that have elapsed since engine start
 */ 
extern const unsigned long long ENGINE_TICK;

/**
 * enables or disables developer mode functions such as rendering hitboxes
 */ 
extern bool ENGINE_DEV_MODE;