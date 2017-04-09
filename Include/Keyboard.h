#ifndef KEYBOARD_H
	#define KEYBOARD_H

#include <string>
#include <string>
#include <vector>
#include "Config.h"



/*
GLUT_BITMAP_8_BY_13

GLUT_BITMAP_9_BY_15

GLUT_BITMAP_TIMES_ROMAN_10

GLUT_BITMAP_TIMES_ROMAN_24

GLUT_BITMAP_HELVETICA_10

GLUT_BITMAP_HELVETICA_12

GLUT_BITMAP_HELVETICA_18
*/
/*


enum COLOR
{
	RED,
	GREEN,
	BLUE,
	ALPHA
};
*/

#include <deque>
#include "Color.h"

class OrthoView;
struct textConfig
{
	void* font;
	int fontSize;

	inline textConfig(): font(GLUT_BITMAP_HELVETICA_10), fontSize(10){
	};
};

class Keyboard
{
public:
	Keyboard(){};

	~Keyboard(){};

	void keyboardHandler(unsigned char key, int x, int y);
	void keyboardReleaseHandler(unsigned char key, int x, int y);
	void renderInput(void);

	void renderTips(void);
protected:


private:
	textConfig config;
	OpMode prevMode;
	std::string curStr;
	std::vector<std::string> history;

	void execute()const;
	std::vector<std::string> getTips();
	void drawBitmapText(const char*string,float x,float y);
	void changeRotAxis(std::deque<std::string>& tokens)const;
	void moveLight(std::deque<std::string>& tokens)const;
	void moveView(std::deque<std::string>& tokens)const;
	void setK(std::deque<std::string>& tokens)const;
	void setUVector(std::deque<std::string>& tokens)const;
	void setOneU(std::deque<std::string>& tokens)const;
	void setResolution(std::deque<std::string>& tokens)const;

	

};



	#endif