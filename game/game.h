#ifndef GAME_GAME_H
#define GAME_GAME_H

//Compulsory Game functions. 
void setup();
void loop();


//Game Functions
void DrawPlayer();

void PaintScreen();
void UpdateScreen();

void MoveLeft();
void MoveRight();
void MoveForward();
void MoveBackward();

void reset();
void DrawLives();
void repaint();

void LevelUp();

void MovedByWall();
void NextTick();


#endif
