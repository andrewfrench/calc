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

CharacterDisplay::CharacterDisplay(Display* dis, Window win){
	this->dis = dis;
	this->win = win;

	loadConfig();
}

void CharacterDisplay::addCharacter(int key){
	CustomCharacter character(key);
	character_list.push_back(character);
}

void CharacterDisplay::deleteCharacter(){
	if (!character_list.empty()){
		character_list.pop_back();
	}
}

void CharacterDisplay::display(GC gc){

	int column = -1;
	int row = 0;
	for (std::vector<CustomCharacter>::iterator it = character_list.begin(); it != character_list.end(); ++it) {
		int key = it->getKey();

		// Fix the following to include actual window and character dimensions.
		if (column >= (400 / 12)) {
			++row;
			column = -1;
		}

		++column;
		
		if (bitmap_list[key] != NULL){
			// Should use variables instead of raw numbers.
			XCopyPlane(dis, bitmap_list[key], win, gc,
				0, 0, 8, 12,
				column * 10, row * 14,1);
		}

	}
}

void CharacterDisplay::loadConfig(){
	FILE* data_file = fopen("data.calc", "r");
	if (data_file == NULL){
		printf("error opening file.");
	}

	int key;
	char* filename;

	//Trying to use strings for filepath but segfaults?

	while (fscanf(data_file, "%d, %s", &key, filename) != EOF){

		Pixmap bitmap;
		unsigned int bitmap_width, bitmap_height;
		int hotspot_x, hotspot_y;
		int rc = XReadBitmapFile(dis, win, filename, &bitmap_width, &bitmap_height,
			&bitmap, &hotspot_x, &hotspot_y);

		switch (rc) {
			case BitmapOpenFailed:
				fprintf(stderr, "XReadBitmapFile - could not open file '%s'.\n", filename);
			break;
			case BitmapFileInvalid:
				fprintf(stderr,
					"XReadBitmapFile - file '%s' doesn't contain a valid bitmap.\n", filename);
			break;
			case BitmapNoMemory:
				fprintf(stderr, "XReadBitmapFile - not enough memory.\n");
			break;
			case BitmapSuccess:
				printf("Loaded bitmap '%s' successfully.\n", filename);
				bitmap_list[key] = bitmap;
			break;
		}
	}

}