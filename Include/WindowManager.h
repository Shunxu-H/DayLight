#ifndef WINDOWMANAGER_H
	#define WINDOWMANAGER_H

#include <QMainWindow>
#include <vector>
#include <memory>
class View;
class Vector;
class Geometry;
class Face;

namespace Ui {
    class MainWindow;
}

class Keyboard;
class WindowManager: public QMainWindow
{
    Q_OBJECT

public:
    WindowManager();
    WindowManager(int argc, char** argv, QMainWindow * parent, const std::string& title, int window_width, int window_height);
	WindowManager(const WindowManager&);
	~WindowManager();

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
	int numOfWindows;
	int mainWindowWidth;
	int mainWindowHeight;
	View** views;
	Keyboard* keyboard;
	int mainWindowContex;

    void drawLineDDA(const Vector &v1, const Vector &v2, float const*);
    void drawLineBSH(const Vector &v1, const Vector &v2, float const*);
    Ui::MainWindow *ui;
};





	#endif
