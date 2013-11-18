#ifndef CustomCharacter_h
#define CustomCharacter_h

#include <string>

class CustomCharacter {
public:
	CustomCharacter(int key);
	char getKey() { return key; }
private:
	char key;
};

#endif