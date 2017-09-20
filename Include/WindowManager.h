#ifndef WINDOWMANAGER_H
	#define WINDOWMANAGER_H

#include <QMainWindow>
#include "Renderer.h"
class QAction;
class QActionGroup;
class QLabel;
class QMenu;


QT_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui {
    class WindowManager;
}
QT_END_NAMESPACE

class View;
namespace Lumos {
    class Shader;
}

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

    void updateAllViews();

    void setUpProgram( const std::string & shaderDir );
    void setUpProgram( const std::vector<Lumos::Shader> & shader );

    void createMenus();

    void positionAllViewsToFitAllInstances();

protected:

#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void newFile();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();
    void aboutQt();
    void exit();

    // for views
    void showCameraOuliner();

private:

    Ui::WindowManager *_ui;

    std::vector< View* > _views;
    View * _render_hidden_view;

    void _createActions();
    void _createMenus();

    QMenuBar *topMenuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;

    QAction *showCameraOulinerAct;



};




	#endif
