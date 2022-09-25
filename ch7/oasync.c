#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include "ticker_demo.c"

#define MESSAGE "hello"
#define BLANK   "     "

int row;
int col;
int dir,done,delay;

int main(int argc, char *argv[]){
  void move_msg(int);
  void input(int);
  void enable_fcntl();
  initscr();
  crmode();
  noecho();
  clear();

  row = 10;
  col = 0;
  dir = 1;
  delay = 200;  // 200ms
  done = 0;
  set_ticker(200);

  move(row, col);
  addstr(MESSAGE);
  signal(SIGALRM, move_msg);
  signal(SIGIO, input);
  enable_fcntl();
  
  while (!done) {
    pause();
  }
  endwin();
  return 0;
}

void input(int sig){
  int c = getch();
  if (c == 'Q'){
    done=1;
  } else if (c ==' '){
    dir=-dir;
  }
}

void move_msg(int signum) {
  signal(SIGALRM, move_msg);
  move(row, col);
  addstr(BLANK);
  col += dir;
  move(row, col);
  addstr(MESSAGE);
  refresh();

  // now handle borders
  if (dir == -1 && col <= 0)
    dir = 1;
  else if (dir == 1 && col + strlen(MESSAGE) >= COLS)
    dir = -1;
}

void enable_fcntl(){
  fcntl(0,F_SETOWN,getpid());
  int fd_flags = fcntl(0,F_GETFL);
  fcntl(0,F_SETFL,(fd_flags|O_ASYNC));
}