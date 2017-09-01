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
class Geometry;
class Face;

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

        inline int getHeight()const{return mainWindowHeight;}
        inline int getwidth()const{return mainWindowWidth;}
        void updateWindow(const int & winID);

        void setPix(const Vector*, float const*);
        void setPix(const int&, const int&, float const*);

        void fillPolygon(Geometry &geometries, const float*);

        void fillPolygons(std::vector<std::shared_ptr<Geometry>> &geos);
        void halfToning(Geometry &geometries);

        void drawLine(const Vector &v1, const Vector &v2, float const*);
        void drawLine( const std::vector<Vector> &vertexBuffer, float*);

        View* operator[](const int& windowID)const;
        int getWindowID(View* d);

        void keyboardHandler(const unsigned char &key, const int &x, const int &y)const;
        void keyboardReleaseHandler(const unsigned char &key, const int &x, const int &y)const;

        //void reshapeWindows();

        void drawVertex(const Vector & v, float const *);
    protected:


    private:

        Ui::WindowManager *ui;

        int numOfWindows;
        int mainWindowWidth;
        int mainWindowHeight;
        View** views;
        Keyboard* keyboard;
        int mainWindowContex;

        Shader shader;
        Program *gProgram;

        void drawLineDDA(const Vector &v1, const Vector &v2, float const*);
        void drawLineBSH(const Vector &v1, const Vector &v2, float const*);

    };


}


	#endif
