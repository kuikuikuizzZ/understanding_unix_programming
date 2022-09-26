








  
  }
  }
}
}
}
}
  addstr(BLANK);
  addstr(MESSAGE);
  addstr(MESSAGE);
  clear();
  col = 0;
  col += dir;
  crmode();
#define BLANK   "     "
#define MESSAGE "hello"
  delay = 200;  // 200ms
    dir = -1;
    dir = 1;
  dir = 1;
    dir=-dir;
  done = 0;
    done=1;
  } else if (c ==' '){
  else if (dir == 1 && col + strlen(MESSAGE) >= COLS)
  enable_fcntl();
  endwin();
  fcntl(0,F_SETFL,(fd_flags|O_ASYNC));
  fcntl(0,F_SETOWN,getpid());
  if (c == 'Q'){
  if (dir == -1 && col <= 0)
#include <curses.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "ticker_demo.c"
  initscr();
  int c = getch();
int col;
int dir,done,delay;
  int fd_flags = fcntl(0,F_GETFL);
int main(int argc, char *argv[]){
int row;
  move(row, col);
  move(row, col);
  move(row, col);
  noecho();
  // now handle borders
    pause();
  refresh();
  return 0;
  row = 10;
  set_ticker(200);
  signal(SIGALRM, move_msg);
  signal(SIGALRM, move_msg);
  signal(SIGIO, input);
  void enable_fcntl();
void enable_fcntl(){
  void input(int);
void input(int sig){
  void move_msg(int);
void move_msg(int signum) {
  while (!done) {
