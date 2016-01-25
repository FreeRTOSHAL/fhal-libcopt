#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <autocopt/autocopt.h>
#include <autocopt/emergency.h>
#include <ncurses.h>
//#define SYM

#define PITCH_STEPSIZE 0.01
#define ROLL_SETPSIZE 0.01
#define YAW_SETPSIZE 0.01
#define THURST_STEPSIZE 0.01

int startx;
int starty; 
int width;
int height;
WINDOW *win;
WINDOW *winBox;


struct autocopt_control ctl = {
	0,0,0,-1
};
struct autocopt_control ctlSave = {
	0,0,0,-1
};

static void updateWin() {
	mvwprintw(win, 1, 0, "roll:%f", ctl.roll);
	mvwprintw(win, 2, 0, "pitch:%f", ctl.pitch);
	mvwprintw(win, 3, 0, "yaw:%f", ctl.yaw);
	mvwprintw(win, 4, 0, "thrust:%f", ctl.thrust);
	box(winBox, 0 , 0);
	wnoutrefresh(winBox);
	wnoutrefresh(win);
	doupdate();
}

static int32_t initScreen() {
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	
	win = newwin(width - 2, height - 1, starty + 1 , startx + 2);
	winBox = newwin(width, height, starty, startx);
	updateWin();
	updateWin();
	return 0;
}

int main(int argc, char **argv) {
	int ch;
#ifndef SYM
	struct autocopt *copt;
	int32_t ret;
	copt = autocopt_init(AUTOCOPT_DEFAULT_DEV);
	if (copt == NULL) {
		return EXIT_FAILURE;
	}
	ret = autocopt_control(copt, &ctl);
	if (ret < 0) {
		mvwprintw(win, 0, 0, "can't send to copter");
	}
	ret = autocopt_select(copt, AUTOCOPT_MODE_LINUX);
	if (ret < 0) {
		fprintf(stderr, "Can't select mode\n");
		return EXIT_FAILURE;
	}
#endif
	initscr();
	height = 30;
	width = 30;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	initScreen();
	timeout(100);
	while((ch = getch()) != 'z') {
		switch(ch) {
			case 'w':
				ctl.pitch += PITCH_STEPSIZE;
				if (ctl.pitch > 1.) {
					ctl.pitch = 1;
				}
				break;
			case 's':
				ctl.pitch -= PITCH_STEPSIZE;
				if (ctl.pitch < -1.) {
					ctl.pitch = -1;
				}
				break;
			case 'd':
				ctl.roll += ROLL_SETPSIZE;
				if (ctl.roll > 1.) {
					ctl.roll = 1;
				}
				break;
			case 'a':
				ctl.roll -= ROLL_SETPSIZE;
				if (ctl.roll < -1.) {
					ctl.roll = -1;
				}
				break;
			case 'q':
				ctl.yaw -= YAW_SETPSIZE;
				if (ctl.yaw < -1.) {
					ctl.yaw = -1;
				}
				break;
			case 'e':
				ctl.yaw += YAW_SETPSIZE;
				if (ctl.yaw > 1.) {
					ctl.yaw = 1;
				}
				break;
			case 'f':
				ctl.thrust -= THURST_STEPSIZE;
				if (ctl.thrust < -1) {
					ctl.thrust = -1;
				}
				break;
			case 'r':
				ctl.thrust += THURST_STEPSIZE;
				if (ctl.thrust > 1.) {
					ctl.thrust = 1;
				}
				break;
			case 't':
				ctl.roll = ctlSave.roll;
				ctl.pitch = ctlSave.pitch;
				ctl.yaw = ctlSave.yaw;
				break;
			case 'g':
				ctlSave.roll = ctl.roll;
				ctlSave.pitch = ctl.pitch;
				ctlSave.yaw = ctl.yaw;
				break;
			case 'z':
				break;
			case ERR:
				ctl.roll = 0;
				ctl.pitch = 0;
				ctl.yaw = 0;
				break;
			case 'c':
				ctl.thrust = -0.2;
				break;
			case 'x':
				ctl.thrust =  -1;
				break;
			case '1':
#ifndef SYM
				ret = autocopt_select(copt, AUTOCOPT_MODE_SPECTRUM);
				if (ret < 0) {
					mvwprintw(win, 0, 0, "Can't select mode\n");
				}
#endif
				break;
			case '2':
#ifndef SYM
				ret = autocopt_select(copt, AUTOCOPT_MODE_LINUX);
				if (ret < 0) {
					mvwprintw(win, 0, 0, "Can't select mode\n");
				}
#endif
				break;
			case '3':
#ifndef SYM
				ret = autocopt_select(copt, AUTOCOPT_MODE_LINUX_THRUST_ONLY);
				if (ret < 0) {
					mvwprintw(win, 0, 0, "Can't select mode\n");
				}
#endif
				break;
			case '4':
#ifndef SYM
				ret = autocopt_select(copt, AUTOCOPT_MODE_LINUX_RPY_ONLY);
				if (ret < 0) {
					mvwprintw(win, 0, 0, "Can't select mode\n");
				}
#endif
				break;
			case 'y':
#ifndef SYM
				ret = autocopt_emergencyLanding(copt);
				if (ret < 0) {
					mvwprintw(win, 0, 0, "Can't send emergency Landing\n");
				}
#endif
				break;

			default:
				mvwprintw(win, 0, 0, "err: %c", ch);
				break;
		}
#ifndef SYM
		ret = autocopt_control(copt, &ctl);
		if (ret < 0) {
			mvwprintw(win, 0, 0, "can't send to copter");
		}
#endif
		updateWin();
	}
#ifndef SYM
	ret = autocopt_select(copt, AUTOCOPT_MODE_SPECTRUM);
	if (ret < 0) {
		fprintf(stderr, "Can't select mode\n");
		return EXIT_FAILURE;
	}
#endif
	endwin();

	return EXIT_SUCCESS;
}
