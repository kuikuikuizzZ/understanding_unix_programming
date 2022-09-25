#include <curses.h>
#include <signal.h>
#include "bounce.h"
#include "ticker_demo.c"

struct ppball the_ball;
struct bar the_bar;
int fail_times=0;

void move_bar(){

}

void set_up();
void wrap_up();
int bounce_or_lose(struct ppball *);
int main(int argc, char *argv[]) {
    int c;

    set_up();

    while ((c = getchar()) != 'Q') {
        if (c == 'f')    the_ball.x_ttm--;
        else if (c == 'g') the_ball.x_ttm++;
        else if (c == 'F') the_ball.y_ttm--;
        else if (c == 'G') the_ball.y_ttm++;
        else if (c == 'w') the_bar.dir--;
        else if (c == 's') the_bar.dir++;
    }
    wrap_up();
}

    // init structure and other stuff
void set_up() {
    void ball_move(int);

    the_ball.y_pos = Y_INIT;
    the_ball.x_pos = X_INIT;
    the_ball.y_ttg = the_ball.y_ttm = Y_TTM;
    the_ball.x_ttg = the_ball.x_ttm = X_TTM;
    the_ball.y_dir = the_ball.x_dir = 1;
    the_ball.symbol = DFL_SYMBOL;

    the_bar.x = BAR_X_INIT;
    the_bar.y = BAR_Y_INIT;
    the_bar.length = BAR_LENGTH;
    the_bar.symbol = DFL_BAR_SYMBOL;
    
    initscr();
    noecho();
    crmode();

    signal(SIGINT, SIG_IGN);
    mvvline(the_bar.y,the_bar.x,the_bar.symbol,the_bar.length);
    mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
    refresh();

    signal(SIGALRM, ball_move);
    set_ticker(1000 / TICKS_PER_SEC);
    // draw_boudary
    mvhline(TOP_ROW-1,LEFT_EDGE,'-',RIGHT_EDGE-LEFT_EDGE);
    mvhline(BOT_ROW+1,LEFT_EDGE,'-',RIGHT_EDGE-LEFT_EDGE);
    mvvline(TOP_ROW,LEFT_EDGE-1,'|',BOT_ROW-TOP_ROW+1);
//   mvvline(TOP_ROW,RIGHT_EDGE+1,'|',BOT_ROW-TOP_ROW);
}

void wrap_up() {
  set_ticker(0);
  endwin();
}

void ball_move(int signum) {
  int y_cur, x_cur, moved;

  signal(SIGALRM, SIG_IGN);
  y_cur = the_ball.y_pos;
  x_cur = the_ball.x_pos;
  moved = 0;

  if (the_ball.y_ttm > 0 & the_ball.y_ttg-- == 1) {
    the_ball.y_pos += the_ball.y_dir;
    the_ball.y_ttg = the_ball.y_ttm;
    moved = 1;
  }

  if (the_ball.x_ttm > 0 && the_ball.x_ttg-- == 1) {
    the_ball.x_pos += the_ball.x_dir;
    the_ball.x_ttg = the_ball.x_ttm;
    moved = 1;
  }

    if (moved) {
        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
        bounce_or_lose(&the_ball);
        move(LINES - 1, COLS - 1);
        refresh();
    }

    int bar_move = 0;
    int bar_y_cur = the_bar.y;
    if ((the_bar.y+the_bar.dir)>=TOP_ROW && (the_bar.y+the_bar.dir) <= (BOT_ROW-the_bar.length)){
        bar_move = 1;
        the_bar.y += the_bar.dir;
    } else if((the_bar.y+the_bar.dir)<TOP_ROW && the_bar.y != TOP_ROW){
        bar_move = 1;
        the_bar.y = TOP_ROW;
    }else if((the_bar.y+the_bar.dir)>(BOT_ROW-the_bar.length) && the_bar.y!= (BOT_ROW-the_bar.length)){
        bar_move = 1;
        the_bar.y = BOT_ROW-the_bar.length;
    }

    if (bar_move)
        mvvline(bar_y_cur, the_bar.x, ' ',the_bar.length);
        mvvline(the_bar.y,the_bar.x,the_bar.symbol,the_bar.length);
    the_bar.dir = 0;
    signal(SIGALRM, ball_move);
}

int bounce_or_lose(struct ppball *bp) {
  int return_val = 0;
  if (bp->y_pos == TOP_ROW) {
    bp->y_dir = 1;
    return_val = 1;
  } else if (bp->y_pos == BOT_ROW) {
    bp->y_dir = -1;
    return_val = 1;
  }

  if (bp->x_pos == LEFT_EDGE) {
    bp->x_dir = 1;
    return_val = 1;
  } else if (bp->x_pos == BAR_X_INIT &&
    bp->y_pos>= the_bar.y &&
    bp->y_pos<= (the_bar.y+the_bar.length)) {
    bp->x_dir = -1;
    return_val = 1;
  } else if (bp->x_pos >= BAR_X_INIT){
        char s[100];
        sprintf(s,"failed: %d",++fail_times);
        mvaddstr(0,0,s);
        set_up();
  }

  return return_val;
}