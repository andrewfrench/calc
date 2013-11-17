#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include <CharacterDisplay.h>

Display *dis;
Window win;

XEvent report;

int main(){
	dis = XOpenDisplay(NULL);
	win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 20, 20, 200, 
		200, 0, BlackPixel(dis, 0), BlackPixel(dis, 0));
	XMapWindow(dis, win);
	XFlush(dis);
	
	/* this variable will contain the handle to the returned graphics context. */
	GC gc;

	/* these variables are used to specify various attributes for the GC. */
	/* initial values for the GC. */
	XGCValues values = CapButt | JoinBevel;
	/* which values in 'values' to check when creating the GC. */
	unsigned long valuemask = GCCapStyle | GCJoinStyle;

	/* create a new graphical context. */
	gc = XCreateGC(display, win, valuemask, &values);	

	XSelectInput (dis, win, KeyPressMask);
	
	while (1) {
		XNextEvent(dis, &report);
		switch (report.type) {
			case KeyPress:
			int key = XLookupKeysym(&report.xkey
				, 0);
			printf("You pressed key: %d.\n", key);
			
			break;	
			
		}
	}

	return 0;
} 
