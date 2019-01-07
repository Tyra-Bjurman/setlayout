/**
 * Ultralightweight NetWM desktop pager setlayout by Tyra Bjurman
 * Derivative work of Mikachu's setlayout.c from Openbox official website.
 *
 * To compile this program: gcc -o setlayout setlayout.c -lX11
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

void print_help() {
	printf("Usage: setlayout ORIENTATION COLUMNS ROWS START\n\n"
		
		"ORIENTATION:\n"
		" The orientation of the desktop layout\n"
		"  0 - horizontal\n"
		"  1 - vertical\n\n"
		
		"COLUMNS and ROWS:\n"
		" Number of columns and rows\n\n"
		
		"START:\n"
		" Starting corner\n"
		"  0 - Top-left\n"
		"  1 - Top-right\n"
		"  2 - Bottom-right\n"
		"  3 - Bottom-left\n");
}

int main(int argc, char **argv) {
	unsigned long data[4];
	Display *display;
	int screen;
	Window root;
	
	//Argument validation
	if(argc == 2 && (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"-?") == 0 || strcmp(argv[1],"--help") == 0)) {
		print_help();
		return 1;
	} else if(argc < 5 || argc > 5) {
		printf("setlayout: invalid number of arguments\n");
		print_help();
		return 1;
	}
	
	//Assign the _NET_DESKTOP_LAYOUT variables
	data[0] = atoi(argv[1]); //Orientation
	data[1] = atoi(argv[2]); //Columns
	data[2] = atoi(argv[3]); //Rows
	data[3] = atoi(argv[4]); //Starting corner
	
	//Get desktop objects
	display = XOpenDisplay(NULL);
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
	
	//Set desktop layout
	XChangeProperty(display, root, XInternAtom(display, "_NET_DESKTOP_LAYOUT", False), XA_CARDINAL, 32, PropModeReplace, (unsigned char *)&data, 4);
	
	//Clean up
	XFlush(display);
	XCloseDisplay(display);
	return 0;
}

