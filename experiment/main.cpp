#include <cstdio>
#include <string>
#include <cstdlib>
/**
 * OPENCV RELATED 
 */
#include <opencv2/opencv.hpp>


#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>




using namespace cv;

Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

void DrawAQuad() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1., 1., -1., 1., 1., 20.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glBegin(GL_QUADS);
		glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
		glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
		glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
		glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
	glEnd();
} 

void screenshot(const std::string & fileName){
	cv::Mat img(gwa.width, gwa.height, CV_8UC3);
    glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
    glReadPixels(0, 0, img.cols, img.rows, GL_BGR_EXT, GL_UNSIGNED_BYTE, img.data);
    cv::Mat flipped(img);
    cv::flip(img, flipped, 0);
    cv::imwrite(fileName, img);
    printf("screen shot!\n" );
}

void keyboard_handle(){

	XNextEvent(dpy, &xev);
	if (xev.type == KeyPress)
    {
        printf( "KeyPress: %x\n", xev.xkey.keycode );


        /* exit on ESC key press */
        if(xev.xkey.keycode == 0x09){
        	glXMakeCurrent(dpy, None, NULL);
	        glXDestroyContext(dpy, glc);
	        XDestroyWindow(dpy, win);
	        XCloseDisplay(dpy);

            exit(EXIT_SUCCESS);
        	
        }
        else if (xev.xkey.keycode == 0x27) // press 's' for SCREEN SHOT
        {
        	screenshot("snapshot.png");
	        printf("screen shot!\n" );
        }
        	
        
    }
    else if (xev.type == KeyRelease)
    {
        printf( "KeyRelease: %x\n", xev.xkey.keycode );
    }

}



int main(int argc, char *argv[]) {

	dpy = XOpenDisplay(NULL);

	if(dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(0);
	}

	root = DefaultRootWindow(dpy);

	vi = glXChooseVisual(dpy, 0, att);

	if(vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
		exit(0);
	} 
	else {
		printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
	}


	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(dpy, win);
	XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

	glEnable(GL_DEPTH_TEST); 

	while(1) {
		XNextEvent(dpy, &xev);

		if(xev.type == Expose) {
	        XGetWindowAttributes(dpy, win, &gwa);
	        glViewport(0, 0, gwa.width, gwa.height);
	        DrawAQuad(); 
	        screenshot("snapshot.png");
	        glXSwapBuffers(dpy, win);
	        exit(EXIT_SUCCESS);
		}
		        
		else if(xev.type == KeyPress) {
	        keyboard_handle();
		}
	} /* this closes while(1) { */
} /* this is the } which closes int main(int argc, char *argv[]) { */

/*
int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}
*/