/*
The MIT License (MIT)

Copyright (c) 2016-2017 Shunxu Huang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef KEYBOARD_H
	#define KEYBOARD_H

#include <string>
#include <string>
#include <vector>
#include "Config.h"



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
