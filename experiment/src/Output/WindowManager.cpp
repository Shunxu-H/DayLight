#include <experimental/filesystem>
#include <iostream>
#include <ctime>
//#include "GL_include.h"
#include "WindowManager.h"
// #include "View.h"
// #include "View_bullet.h"
// #include "Shader.h"
// #include "Renderer.h"
// #include "View_renderer.h"
// #include "Utility.h"
// #include "Extern.h"


namespace fs = std::experimental::filesystem;



WindowManager::WindowManager()
{




}

WindowManager::~WindowManager()
{




}

void WindowManager::render(){
    /*
    double duration;
    int w = 1080, h = 720;
    clock_t start = std::clock();


    world->clearAll();
    shaper->clearAll();

    std::vector<std::experimental::filesystem::path> allobjpath;
    Utils::getAllDir(SCENE_FILE_DIR, allobjpath);

    for (const std::experimental::filesystem::path & p : allobjpath){
        qDebug() << "Rendering: " << std::string(p).c_str();
        std::string curScope = p.stem();
        shaper->loadFile(std::string(p) + "/" + curScope + ".obj");
        Patronus::Camera::loadCamerasFromDir(CAMERA_DIR + curScope);
        gProgram->preDrawSetUp();

        Utils::cleanAndMkdir("./" + shaper->getCurFileName());

        for( size_t camPtr = 0; camPtr < shaper->getNumOfCameras(); camPtr++){
            _render_hidden_view->setCamInUse(shaper->getnCamera(camPtr));
            _render_hidden_view->resize(w, h);
            _render_hidden_view->generateData();
        }

        world->clearAll();
        shaper->clearAll();
    }

    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    qDebug() << "Time passed: " << duration;

    */
}
/*

void WindowManager::updateAllViews(){
    for(View* & v : _views )
        v->update();
}


void WindowManager::positionAllViewsToFitAllInstances(){
    // compute bounding circle
    point3 position;
    float radius;
    Patronus::Shaper::getBoundingSphere(Patronus::Shaper::global_vertices, &position, &radius);

    for( View * v: _views )
        v->fitSphere(position, radius);

}


*/