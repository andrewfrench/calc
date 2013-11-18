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

	//Pixmap Things

	/* this variable will contain the ID of the newly created pixmap.    */
	Pixmap bitmap;

	/* these variables will contain the dimensions of the loaded bitmap. */
	unsigned int bitmap_width, bitmap_height;

	/* these variables will contain the location of the hot-spot of the   */
	/* loaded bitmap.                                                    */
	int hotspot_x, hotspot_y;

	/* load the bitmap found in the file "icon.bmp", create a pixmap      */
	/* containing its data in the server, and put its ID in the 'bitmap'  */
	/* variable.                                                          */
	int rc = XReadBitmapFile(dis, win,
                         "icon.xbm",
                         &bitmap_width, &bitmap_height,
                         &bitmap,
                         &hotspot_x, &hotspot_y);

	switch (rc) {
    case BitmapOpenFailed:
        fprintf(stderr, "XReadBitmapFile - could not open file 'icon.bmp'.\n");
        break;
    case BitmapFileInvalid:
        fprintf(stderr,
                "XReadBitmapFile - file '%s' doesn't contain a valid bitmap.\n",
                "icon.bmp");
        break;
    case BitmapNoMemory:
        fprintf(stderr, "XReadBitmapFile - not enough memory.\n");
        break;
    case BitmapSuccess:
        /* bitmap loaded successfully - do something with it... */
   		printf("Loaded bitmap successfully.\n");
        break;
	}

	XSelectInput (dis, win, KeyPressMask);

	while (1) {
		XNextEvent(dis, &report);
		switch (report.type) {
			case KeyPress:
			int key = XLookupKeysym(&report.xkey, 0);
			printf("%d", key);
			if (key != DELETE_KEY) {
				input.addCharacter(key);
			} else {
				input.deleteCharacter();
			}
			
			input.display(dis, win, gc, bitmap);

			//XCopyPlane(dis, bitmap, win, gc,
          	//	0, 0, bitmap_width, bitmap_height,
          	//	100, 50,1);

			break;	
			
		}
	}

	return 0;
} 
