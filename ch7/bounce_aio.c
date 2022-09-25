#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include "ticker_demo.c"
#include <aio.h>


#define MESSAGE "hello"
#define BLANK   "     "

int row;
int col;
int dir,done,delay;
struct aiocb kbcbuf;

int main(int argc, char *argv[]){
  void move_msg(int);
  void on_input(int);
  void setup_aio_buffer();
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
  signal(SIGIO, on_input);
  setup_aio_buffer();
  aio_read(&kbcbuf);
  while (!done) {
    pause();
  }
  endwin();
  return 0;
}

void on_input(int sig){
  int c ;
  char *cp = (char*)kbcbuf.aio_buf;
  if(aio_error(&kbcbuf)!=0){
    perror("reading fail");
  }else{
    if (aio_return(&kbcbuf)==1){
      c = *cp;
      if (c == 'Q'){
        done=1;
      } else if (c ==' '){
        dir=-dir;
      }
    }
  }
  aio_read(&kbcbuf);
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

void setup_aio_buffer(){
  static char input[1] ;
  kbcbuf.aio_buf=input;
  kbcbuf.aio_fildes=0;
  kbcbuf.aio_nbytes =1;
  kbcbuf.aio_offset=0;
  kbcbuf.aio_sigevent.sigev_notify=SIGEV_SIGNAL;
  kbcbuf.aio_sigevent.sigev_signo = SIGIO;

}