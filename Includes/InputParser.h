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