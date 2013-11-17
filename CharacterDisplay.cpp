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

void CharacterDisplay::display(Display* dis, Window win, GC gc, Pixmap bitmap){
	printf("---------------\nKeys: ");
	for (std::vector<CustomCharacter>::iterator it = character_list.begin(); it != character_list.end(); ++it) {
		
		int key = it->getKey();
		printf("%c ", (char)key);

		//XDrawRectangle(dis, win, gc, key, key, key, key);

		XCopyPlane(dis, bitmap, win, gc,
          		0, 0, 32, 32,
          		key, key,1);

	}
	printf("\n");

	
}