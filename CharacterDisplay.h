#ifndef CharacterDisplay_h
#define CharacterDisplay_h

#include <stdio.h>
#include <vector>
#include <X11/Xlib.h>
#include <map>
#include <string>
#include "CustomCharacter.h"

class CharacterDisplay {
public:
	CharacterDisplay();
	void addCharacter(int key);
	void deleteCharacter();
	void display(Display* dis, Window w, GC gc, Pixmap bitmap);
private:
	std::vector<CustomCharacter> character_list;
	std::map<int, std::string> bitmap_list; 
};

#endif
