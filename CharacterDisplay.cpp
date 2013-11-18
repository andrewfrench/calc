#include "CharacterDisplay.h"
#include <stdio.h>
#include <vector>
#include <X11/Xlib.h>

CharacterDisplay::CharacterDisplay(){
	printf("I got made!\n");
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

void CharacterDisplay::display(Display* dis, Window win, GC gc, Pixmap bitmap){
	printf("---------------\nKeys: ");
	int column = -1;
	int row = 0;
	for (std::vector<CustomCharacter>::iterator it = character_list.begin(); it != character_list.end(); ++it) {
		int key = it->getKey();
		printf("%c ", (char)key);

		if (column >= (400 / 17)) {
			++row;
			column = -1;
		}

		++column;


		XCopyPlane(dis, bitmap, win, gc,
          		0, 0, 16, 16,
          		column * 16, row * 16,1);

	}
	printf("\n");

	
}