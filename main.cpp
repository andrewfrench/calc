#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include "CharacterDisplay.h"

//#include "icon.bmp"

const int DELETE_KEY = 65288;

Display *dis;
Window win;

XEvent report;

int main(){

	dis = XOpenDisplay(NULL);
	win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 0, 0, 400, 
		300, 0, BlackPixel(dis, 0), BlackPixel(dis, 0));
	XMapWindow(dis, win);
	XFlush(dis);
	
	// Color things
	GC gc;
	XColor color;
	Colormap colormap;
	char white[] = "#FFFFFF";

	std::string name = "Chris";
	printf("Hello %s.\n\n", name.c_str());  

	colormap = DefaultColormap(dis, 0);

	gc = XCreateGC(dis, win, 0, 0);

	XParseColor(dis, colormap, white, &color);
	XAllocColor(dis, colormap, &color);
	XSetForeground(dis, gc, color.pixel);

	CharacterDisplay input(dis, win);

	XSelectInput (dis, win, KeyPressMask);

	while (1) {
		XNextEvent(dis, &report);
		switch (report.type) {
			case KeyPress:
			XClearWindow(dis, win);

			int key = XLookupKeysym(&report.xkey, 0);
			printf("%d\n", key);

			if (key != DELETE_KEY) {
				input.addCharacter(key);
			} else {
				input.deleteCharacter();
			}
			
			input.display(gc);

			break;	
			
		}
	}

	return 0;
} 
