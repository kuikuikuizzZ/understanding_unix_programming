








  }
}
}
}
  addstr(BLANK);
  addstr(MESSAGE);
  addstr(MESSAGE);
    c = getch();
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
  else if (dir == 1 && col + strlen(MESSAGE) >= COLS)
  endwin();
    if (c == ' ') dir = -dir;
    if (c == 'f' && delay > 2) ndelay = delay / 2;
    if (c == 'Q') break;
    if (c == 's') ndelay = delay * 2;
  if (dir == -1 && col <= 0)
    if (ndelay > 0)
#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
  initscr();
int col;
  int c;        // user input
  int delay;    // bigger => slower
int dir;
int main() {
  int ndelay;   // new delay
int row;
  int set_ticker(int);
int set_ticker(int n_msec)  {
    long n_sec = n_msec/1000;
    long n_usec = (n_msec%1000)*1000L;
  move(row, col);
  move(row, col);
  move(row, col);
    ndelay = 0;
    new_timeval.it_interval.tv_sec = n_sec;
    new_timeval.it_interval.tv_usec = n_usec;
    new_timeval.it_value.tv_sec = n_sec;
    new_timeval.it_value.tv_usec = n_usec;
  noecho();
  // now handle borders
  refresh();
  return 0;
    return setitimer(ITIMER_REAL,&new_timeval,NULL);
  row = 10;
  set_ticker(delay);
      set_ticker(delay = ndelay);
  signal(SIGALRM, move_msg);
  signal(SIGALRM, move_msg);
    struct itimerval new_timeval;
  void move_msg(int);
void move_msg(int signum) {
  while (1) {
