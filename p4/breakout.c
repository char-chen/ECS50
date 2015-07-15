/* 
 * File:   breakout.c
 * Author: davis
 *
 * Created on February 2, 2010, 9:25 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

const int TOP = 0;
const int BOTTOM = 13;
const int MAX_RIGHT = 37;
const int MIN_RIGHT = 1;
const int LEFT = 4;
const int RIGHT = 5;
const int MAX_PADDLE_X = 33;
const int  QUIT = 'x';
const int  START = ' ';
const int  NOKEY = 'n';
const int  VERTICLE_LINE = '|';
const int  HORIZONTAL_LINE = '-';
const int  BALL_CHR = 'O';
char crt[14][38];

bool advanceTime(int delay);
void clearCRT();
char getKey();
void  getNewballPosition(int *ballX, int *ballY, int *deltaX, int *deltaY);
void init();
void movePaddle(char key, int *x);
int play (int *score, int *ballX, int *ballY, int *deltaX, int *deltaY,
  int *lives);
void putChar(int x, int y, char c);
int random2(int max);
void showIntro();
void showPaddle(int x, char letter);
void showScore(int score, int lives);
void startGame(int *ballX, int *ballY, int *paddleX, int *deltaX,
  int *deltaY, int score);


bool advanceTime(int delay)
{
  static int timer = 0;
  int i;
  
  for(i = 0; i < 100000; i++)
      if(i * 1.75 == 17.5)
        i = 11;
  
 timer++;

  if(timer >= delay)
  {
    timer = 0;
    return false;
  }
  return true;
} // advanceTime()





void clearCRT()
{
  int i, j;
  erase();

  mvaddstr(0,0, "||____||____||____||____||____||____||");
  for(i = 1; i < 14; i++)
  {
    mvaddstr(i,0, "|                                    |");

    for(j = 0; j < 38; j++)
      crt[i][j] = ' ';

    crt[i][0] = crt[i][37] = '|';
  }

  strcpy(crt[0], "|111111222222333333444444555555666666");
  crt[0][37] = '|';
  mvaddstr(14,0,"--------------------------------------");
  mvaddstr(15,0,"Bottom border is not in CUSP");

}  // clearCRT()


char getKey()
{
  char key;

  if ((key = getch()) != ERR)
  {
    if ((key == LEFT) || (key == RIGHT) || (key == START) || (key == QUIT) )
       return key;
   } // { if key pressed }

  return NOKEY;
} // getKey()


void  getNewBallPosition(int *ballX, int *ballY, int *deltaX, int *deltaY)
 {
    int square;
   *ballY += *deltaY;
   *ballX += *deltaX;


   if(*ballY == BOTTOM  && crt[*ballY][*ballX] == '-')
   {
     *ballY = BOTTOM - 1;
     *deltaY = -1;
   }
   else
     if(*ballY < 0)
     {
       *ballY = 0;
       *deltaY = 1;
     }

   if(*ballX == 0)
   {
     *ballX = 2;
     *deltaX = 1;
   }
   else
     if(*ballX == MAX_RIGHT)
     {
       *ballX = MAX_RIGHT - 2;
       *deltaX = -1;
     }
}  // getNewballPosition()

void init()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  refresh();
} // init()

void movePaddle(char key, int *x)
  {
    showPaddle(*x, ' ');

    if ((key == LEFT) && (*x > 1))
      *x = *x - 1;
    else // { key is RIGHT }
      if  ((key == RIGHT) &&  (*x < MAX_PADDLE_X) )
        *x = *x + 1;

    showPaddle(*x, HORIZONTAL_LINE);
  } // movePaddle()



int play (int *score, int *ballX, int *ballY, int *deltaX, int *deltaY,
  int *lives)
{
  int square, i;
  putChar(*ballX, *ballY, ' ');
  getNewBallPosition(ballX, ballY, deltaX, deltaY);
  square = crt[*ballY][*ballX];

  if(square > '0' && square < '7') // hit brick
  {
    (*ballY)++;
    *deltaY = 1;
    (*score)++;
    if(*score % 6 == 0)
      return 1;

    for(i = 0; i < MAX_RIGHT; i++)
      if(crt[0][i] == square)
      {
        crt[0][i] = ' ';
        putChar(i, 0, ' ');
      }

  }

  if(*ballY > BOTTOM)
  {
    (*lives)--;
    return 1;
  }
  else
  {
    putChar(*ballX, *ballY, BALL_CHR);
    return 0;
  }
} // play()


void putChar(int x, int y, char c)
{
  crt[y][x] = c;
  mvaddch(y, x, c);
  move(200,200);
}  // putChar()


int random2(int max)
{
  static int seed = 1;
  seed = (seed * 2779 + 1997) % 2048;
  return seed % (max + 1);
}  // random2()


void showIntro()
{
  char key;
  
  mvaddstr(0, 5, "Breakout Introduction");
  mvaddstr(2, 0, "This is the minimal version of");
  mvaddstr(3, 0, "breakout.  The game starts when the");
  mvaddstr(4, 0, "space bar is pressed.  The game");
  mvaddstr(5, 0, "ends when either the user presses x,");
  mvaddstr(6, 0, "or their lives reaches zero.");
  mvaddstr(7, 0, "Instead of this introduction, students");
  mvaddstr(8, 0, "should place a description of their");
  mvaddstr(9, 0, "options here.");
  do
  {
    key = getKey();
  } while (key != START);
} // showIntro()


 void showPaddle(int x, char letter)
 {
    putChar(x, BOTTOM, letter);
    putChar(x + 1, BOTTOM, letter);
    putChar(x + 2, BOTTOM, letter);
    putChar(x + 3, BOTTOM, letter);
 } // showPaddle()


void showScore(int score, int lives)
{
  char s[11];
  sprintf(s, "Score: %d", score);
  mvaddstr(7, 3, s);
  mvaddstr(8, 3, "Lives: ");
  addch(lives + '0');
  if(lives == 0)
    mvaddstr(9,3, "Game Over");
  refresh();
  while(advanceTime(10000));
} // showScore }


void startGame(int *ballX, int *ballY, int *paddleX, int *deltaX,
  int *deltaY, int score)
{
  if(score % 6 == 0)
    clearCRT(score);
  else  // clear Lives and Score
  {
    mvaddstr(7,3, "          ");
    mvaddstr(8,3, "          ");
    mvaddstr(BOTTOM,0, "|                                    |");
  }  // else mid game

  *ballX = MAX_RIGHT / 2 - 4 + random2(8);
  *ballY = 1;
  *deltaX = 1 -  2 * random2(1);
  *deltaY = 1;
  *paddleX = MAX_RIGHT / 2 - 2;
  showPaddle(*paddleX, HORIZONTAL_LINE);
  refresh();
} // StartGame()


int main() {
  char key = 'n';
  int score, lives, paddleX, ballX, ballY, deltaX, deltaY;

  
  init();
  score = 0;
  lives = 3;

  showIntro();
  startGame(&ballX, &ballY, &paddleX, &deltaX, &deltaY, score);

  while (key != QUIT)
  {
      if(!play(&score, &ballX, &ballY, &deltaX, &deltaY, &lives))
      {
        do
        {
          key = getKey();

          if (key == RIGHT || key == LEFT)
            movePaddle(key, &paddleX);
        } while(advanceTime(500) && key != QUIT);
      } // { if no score }
      else  // live lost or last brick
      {
        showScore(score, lives);
        if(lives > 0)
          startGame(&ballX, &ballY, &paddleX, &deltaX, &deltaY, score);
        else
          key = QUIT;
      }
  } //; { while }
  return (EXIT_SUCCESS);
}

