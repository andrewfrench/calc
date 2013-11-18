#ifndef CustomCharacter_h
#define CustomCharacter_h

#include <string>

class CustomCharacter {
public:
	CustomCharacter(int key, std::string filename);
	char getKey() { return key; }
	std::string getFilename() { return filename; }
private:
	char key;
	std::string filename;
};

#endif