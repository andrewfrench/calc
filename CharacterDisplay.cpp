#include "CharacterDisplay.h"
#include <stdio.h>
#include <vector>
#include <X11/Xlib.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

CharacterDisplay::CharacterDisplay(){
	printf("I got made!\n");
	bitmap_list[48] = "0.xbm";
	bitmap_list[49] = "1.xbm";
}

void CharacterDisplay::addCharacter(int key){
	CustomCharacter character(key, bitmap_list[key]);
	character_list.push_back(character);
}

void CharacterDisplay::deleteCharacter(){
	if (!character_list.empty()){
		character_list.pop_back();
	}
}

void CharacterDisplay::display(Display* dis, Window win, GC gc, Pixmap bitmap){
	printf("---------------\n");
	
	printf("Keys: ");

	int column = -1;
	int row = 0;
	for (std::vector<CustomCharacter>::iterator it = character_list.begin(); it != character_list.end(); ++it) {
		int key = it->getKey();
		printf("%c (%s) ", (char)key, it->getFilename().c_str());

		if (column >= (400 / 12)) {
			++row;
			column = -1;
		}

		++column;


		/* this variable will contain the ID of the newly created pixmap.    */
		Pixmap bitmap2;

		/* these variables will contain the dimensions of the loaded bitmap. */
		unsigned int bitmap_width, bitmap_height;

		/* these variables will contain the location of the hot-spot of the   */
		/* loaded bitmap.                                                    */
		int hotspot_x, hotspot_y;

		/* load the bitmap found in the file "icon.bmp", create a pixmap      */
		/* containing its data in the server, and put its ID in the 'bitmap'  */
		/* variable.                                                          */
		int rc = XReadBitmapFile(dis, win, it->getFilename().c_str(), &bitmap_width, &bitmap_height,
			&bitmap2, &hotspot_x, &hotspot_y);

		switch (rc) {
			case BitmapOpenFailed:
				fprintf(stderr, "XReadBitmapFile - could not open file %s.\n", it->getFilename().c_str());
			break;
			case BitmapFileInvalid:
				fprintf(stderr,
					"XReadBitmapFile - file '%s' doesn't contain a valid bitmap.\n",
					it->getFilename().c_str());
			break;
			case BitmapNoMemory:
				fprintf(stderr, "XReadBitmapFile - not enough memory.\n");
			break;
			case BitmapSuccess:
        		/* bitmap loaded successfully - do something with it... */
				printf("Loaded bitmap successfully.\n");
				XCopyPlane(dis, bitmap2, win, gc,
					0, 0, 8, 12,
					column * 10, row * 14,1);
			break;
		}

		

	}
	printf("\n");

	
}