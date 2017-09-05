#ifndef WINDOWMANAGER_H
	#define WINDOWMANAGER_H

//#include "View.h"


#include <QMainWindow>
#include <QMainWindow>
#include <vector>
#include <memory>
#include "Program.h"
#include "Shader.h"
#include "Config.h"

class View;
class Vector;
class Mesh;

QT_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui {
    class WindowManager;
}
QT_END_NAMESPACE

namespace Lumos {
    class Keyboard;
    class WindowManager: public QMainWindow
    {
        Q_OBJECT
    public:
        // Disable copy constructor
        WindowManager( const WindowManager& ) = delete;
        // Disable assignment operator
        WindowManager& operator = ( const WindowManager& ) = delete;

        WindowManager(QWidget *parent = nullptr);
        virtual ~WindowManager();

        void setUpProgram( const std::string & shaderDir );
        void setUpProgram( const std::vector<Shader> & shader );

    protected:


    private:

        Ui::WindowManager *ui;

        Shader shader;


    };


}


	#endif
