#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

Display *dis;
Window win;

XEvent report;

GC green_gc;
XColor green_col;
Colormap colormap;
char green[] = "#00FF00";

int main(){
	dis = XOpenDisplay(NULL);
	win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 20, 20, 200, 
		200, 0, BlackPixel(dis, 0), BlackPixel(dis, 0));
	XMapWindow(dis, win);
	XFlush(dis);
	
	colormap = DefaultColormap(dis, 0);
	green_gc = XCreateGC(dis, win, 0, 0);
	XParseColor(dis, colormap, green, &green_col);
	XAllocColor(dis, colormap, &green_col);
	XSetForeground(dis, green_gc, green_col.pixel);

	XSelectInput (dis, win, KeyPressMask);
	
	while (1) {
		XNextEvent(dis, &report);
		switch (report.type) {
			case KeyPress:
				int key = XLookupKeysym(&report.xkey
					, 0);
				printf("You pressed key: %d.\n", key);
				
				if (key == (int)'a'){
					XDrawRectangle(dis, win, 
						green_gc, 1, 1, 20, 20);
				}
			break;	
			
		}
	}

	return 0;
} 
