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

void CharacterDisplay::display(Display* dis, Window win, GC gc){
	printf("---------------\nKeys: ");
	for (std::vector<CustomCharacter>::iterator it = character_list.begin(); it != character_list.end(); ++it) {
		
		int key = it->getKey();
		printf("%c ", (char)key);

		XDrawRectangle(dis, win, gc, key, key, key, key);

	}
	printf("\n");

	
}