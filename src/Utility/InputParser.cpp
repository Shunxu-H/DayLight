#include <stdexcept>
#include <algorithm>
#include "InputParser.h"


 Flag Cmd::string2flag(const std::string & str){
    if (str.compare("-hl") == 0 or str.compare("--headless") == 0){
        return Flag::HEADLEASS;
    }
    else if (str.compare("-wd") == 0 or str.compare("--window_dimension") == 0){
        return Flag::WINDOW_DIMENTSION;
    }
    else if (str.compare("-td") == 0 or str.compare("--texture_directory") == 0){
        return Flag::TEXTURE_DIRECTORY;
    }
    else if (str.compare("-sd") == 0 or str.compare("--scene_directory") == 0){
        return Flag::SCENE_DIRECTORY;
    }
    else if (str.compare("-od") == 0 or str.compare("--output_directory") == 0){
        return Flag::OUTPUT_DIRECTORY;
    }
    else if (str.compare("-cd") == 0 or str.compare("--cameara_directory") == 0){
        return Flag::CAMERA_DIRECTORY;
    }
    else if (str.compare("-rl") == 0 or str.compare("--render_list") == 0){
        return Flag::RENDER_LIST;
    }
    else if (str.compare("-loop") == 0 ){
        return Flag::LOOP;
    }
    else if (str.compare("-lf") == 0 or str.compare("--load_file") == 0){
        return Flag::LOAD_FILE;
    }
    else if (str.compare("-h") == 0 or str.compare("--help") == 0){
        return Flag::HELP;
    }

    else
        return Flag::NOT_A_FLAG;
}

Cmd::Cmd(char* s):Cmd(string2flag(s)){};
Cmd::Cmd(Flag _f){
    if(_f == Flag::NOT_A_FLAG)
        throw std::runtime_error("Not a valid flag");
    _flag = _f;
};

std::string Cmd::operator [] (const size_t & index ){
    if (index >= _args.size())
        throw std::runtime_error( std::string("Overload at " + __LINE__).c_str() );
    return _args[index];
}



InputParser::InputParser (int &argc, char **argv){
    if (argc < 2)
        return;
    else if(Cmd::string2flag(argv[1]) == Flag::NOT_A_FLAG )
        throw std::runtime_error("Arguments invalid");
    Cmd curCmd(argv[1]);
    for (int i=2; i < argc; ++i){
        Flag curFlag(Cmd::string2flag( argv[i] ));
        if (curFlag == Flag::NOT_A_FLAG)
            curCmd.addArg(argv[i]);
        else{
            cmds.push_back(curCmd);
            curCmd = Cmd(curFlag);
        }
        // this->tokens.push_back(std::string(argv[i]));
    }
    cmds.push_back(curCmd);
}

Cmd InputParser::get(const Flag & flag) const{
    if (!has(flag))
        throw std::runtime_error("Make sure to check existance before getting the option.");
    return *std::find(this->cmds.begin(), this->cmds.end(), Cmd(flag));
}

bool InputParser::has(const Flag & f) const{

    return std::find(this->cmds.begin(), this->cmds.end(), Cmd(f))
           != this->cmds.end();

}
