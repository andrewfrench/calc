#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include "CharacterDisplay.h"

Display *dis;
Window win;

XEvent report;

int main(){

	CharacterDisplay input;

	dis = XOpenDisplay(NULL);
	win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 0, 0, 400, 
		300, 0, BlackPixel(dis, 0), BlackPixel(dis, 0));
	XMapWindow(dis, win);
	XFlush(dis);
	
	// Color things
	GC gc;
	XColor green_col;
	Colormap colormap;
	char green[] = "#00FF00";


	colormap = DefaultColormap(dis, 0);

	gc = XCreateGC(dis, win, 0, 0);

	XParseColor(dis, colormap, green, &green_col);
	XAllocColor(dis, colormap, &green_col);
	XSetForeground(dis, gc, green_col.pixel);

	XSelectInput (dis, win, KeyPressMask);

	while (1) {
		XNextEvent(dis, &report);
		switch (report.type) {
			case KeyPress:
			int key = XLookupKeysym(&report.xkey
				, 0);
				//printf("You pressed key: %d.\n", key);
			input.addCharacter(key);
			input.display(dis, win, gc);
			break;	
			
		}
	}

	return 0;
} 
