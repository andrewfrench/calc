#ifndef CharacterDisplay_h
#define CharacterDisplay_h

#include <stdio.h>
#include <vector>
#include <X11/Xlib.h>
#include "CustomCharacter.h"

class CharacterDisplay {
public:
	CharacterDisplay();
	void addCharacter(int key);
	void display(Display* dis, Window w, GC gc);
private:
	std::vector<CustomCharacter> character_list;
};

#endif
