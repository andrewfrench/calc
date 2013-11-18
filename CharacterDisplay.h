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
	CharacterDisplay(Display* dis, Window win);
	void addCharacter(int key);
	void deleteCharacter();
	void display(GC gc);
private:

	void loadConfig();

	std::vector<CustomCharacter> character_list;
	std::map<int, Pixmap> bitmap_list; 
	Display* dis;
	Window win;
	
};

#endif
