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
#ifndef INPUTPARSER
#define INPUTPARSER

/**
 * Adapted from @iain by @Shunxu Huang
 */

#include <vector>
#include <string>
enum class Flag{
    HEADLEASS,
    WINDOW_DIMENTSION,
    TEXTURE_DIRECTORY,
    SCENE_DIRECTORY,
    OUTPUT_DIRECTORY,
    CAMERA_DIRECTORY,
    RENDER_LIST,
    HELP,
    NOT_A_FLAG
};


class Cmd
{
public:
    static Flag string2flag(const std::string & str);
    Cmd(Flag _f);
    Cmd(char *s);
    inline int argc()const {return _args.size();}
    inline bool isFlag( const Flag & _f) const {return _f == _flag;}
    inline Flag getFlag() const {return _flag;}
    inline void addArg(const std::string & s){ _args.push_back(s);}
    inline std::vector<std::string> getArgs()const {return _args;};

    std::string operator [] (const size_t & index );
    bool operator==(const Cmd & rhs) const { return _flag == rhs._flag;}
    virtual ~Cmd(){};
private:
    Flag _flag;
    std::vector<std::string> _args;
};

class InputParser{
    public:
        InputParser (int &argc, char **argv);
        Cmd get(const Flag & flag) const;
        bool has(const Flag & f) const;
    private:
        std::vector <Cmd> cmds;

};

#endif
