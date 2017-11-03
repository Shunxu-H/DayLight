#include <cstdio>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
/**
 * OPENCV RELATED 
 */
#include <opencv2/opencv.hpp>



#include <X11/X.h>
#include <X11/Xlib.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <GL/glu.h>


/**
 * HEADLESS RELATED
 */

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
typedef Bool (*glXMakeContextCurrentARBProc)(Display*, GLXDrawable, GLXDrawable, GLXContext);
static glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;
static glXMakeContextCurrentARBProc   glXMakeContextCurrentARB   = NULL;



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
int 					window_width;
int 					window_height;


GLuint FBO = 0;
GLuint _ColorTextureObject = 0;
GLuint _DepthTextureObject = 0;

void logOpenGLError(const std::string & sourceFile ){

        // check OpenGL error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::stringstream o;
        switch(err) {
            case GL_NO_ERROR:
                return;
                break;
            case GL_INVALID_ENUM:
                o <<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid enum!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_INVALID_VALUE:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid value!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_INVALID_OPERATION:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid operation!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_STACK_OVERFLOW:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Stack overflow!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_STACK_UNDERFLOW:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Stack underflow!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_OUT_OF_MEMORY:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Out Of memory!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_TABLE_TOO_LARGE:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Table too large!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            default:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Unknown error!"<< std::endl;
                throw std::runtime_error(o.str());
                break;
        }
    }
}

void DrawAQuad() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT );

	// logOpenGLError("here1");

	// glBegin(GL_TRIANGLES);

 //        glColor3f(0.1, 0.2, 0.3);
 //        glVertex3f(0, 0, 0);
 //        glVertex3f(1, 0, 0);
 //        glVertex3f(0, 1, 0);
 //    glEnd();
	// logOpenGLError("here2");

	// glLoadIdentity();
	// logOpenGLError("here");
	// glMatrixMode(GL_PROJECTION);

	// glOrtho(-1., 1., -1., 1., 1., 20.);

	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	// gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	// glBegin(GL_QUADS);
	// 	glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
	// 	glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
	// 	glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
	// 	glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
	// glEnd();

	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
logOpenGLError("here1");
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);


} 

void screenshot(const std::string & fileName){
	cv::Mat img(window_width, window_height, CV_8UC3);
    glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
    glBindTexture(GL_TEXTURE_2D, _ColorTextureObject);
    glGetTexImage ( GL_TEXTURE_2D,
                    0,
                    GL_BGR, // GL will convert to this format
                    GL_UNSIGNED_BYTE,   // Using this data type per-pixel
                    img.data );

    //glReadPixels(0, 0, img.cols, img.rows, GL_BGR_EXT, GL_UNSIGNED_BYTE, img.data);
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


void makeFrameBuffer(){

    GLint drawFboId = 0, readFboId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
    std::cout << "draw buffer in use: " << drawFboId << std::endl
    		  << "read buffer in use: " << readFboId << std::endl; 

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glEnable(GL_DEPTH_TEST);

    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    // create a RGBA color texture

    glGenTextures(1, &_ColorTextureObject);
    glBindTexture(GL_TEXTURE_2D, _ColorTextureObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        window_width, window_height,
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        NULL);

    // create a depth texture
    glGenTextures(1, &_DepthTextureObject);
    glBindTexture(GL_TEXTURE_2D, _DepthTextureObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
                        window_width, window_height,
                        0, GL_DEPTH_COMPONENT, GL_FLOAT,
                        NULL);



    // attach color
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ColorTextureObject, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _DepthTextureObject, 0);



    // check buffer status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error ( "Error! FrameBuffer is not complete" );



    glBindFramebuffer(GL_FRAMEBUFFER, FBO);


    GLint drawId = 0, readId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);


    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers



	/*
	glGenFramebuffers(1, &m_framebuffer1);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer1);

	glGenRenderbuffers(1, &m_colorRenderbuffer1);
	glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer1);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, window_width, window_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderbuffer1);

	glGenRenderbuffers(1, &m_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window_width, window_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Failed to make complete framebuffer object " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
	*/
}


int main(int argc, char *argv[]) {

	window_width = 500;
 	window_height = 500;
	// headless related 
	glXCreateContextAttribsARB = 
		(glXCreateContextAttribsARBProc) 
			glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
	glXMakeContextCurrentARB   = 
		(glXMakeContextCurrentARBProc)   
			glXGetProcAddressARB( (const GLubyte *) "glXMakeContextCurrent"      );

	dpy = XOpenDisplay(NULL);

	std::cout << dpy << std::endl;
	// headless related 
	static int visualAttribs[] = { None };
	int numberOfFramebufferConfigurations = 0;
	GLXFBConfig* fbConfigs = 
		glXChooseFBConfig( dpy, 
						   DefaultScreen(dpy), 
						   visualAttribs, 
						   &numberOfFramebufferConfigurations );

	// Request OpenGL context
	int context_attribs[] = {
	    GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
	    GLX_CONTEXT_MINOR_VERSION_ARB, 5,
	    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
	    GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
	    None
	};

	printf("here\n\n");
	GLXContext openGLContext = 
		glXCreateContextAttribsARB( dpy, 
									fbConfigs[0], 
									0, 
									True, 
									context_attribs);

	printf("here2\n\n");
	int pbufferAttribs[] = {
	    GLX_PBUFFER_WIDTH,  window_width,
	    GLX_PBUFFER_HEIGHT, window_height,
	    None
	};
	GLXPbuffer pbuffer = 
		glXCreatePbuffer( dpy, 
						  fbConfigs[0], 
						  pbufferAttribs );

	printf("here3\n\n");
	// clean up:
	XFree( fbConfigs );
	XSync( dpy, False );

	if ( !glXMakeContextCurrent( dpy, pbuffer, pbuffer, openGLContext ) )
	{
		throw std::runtime_error("Setting headless failed ");
	}

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

	//win = XCreateWindow(dpy, root, 0, 0, window_width, window_height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

	//XMapWindow(dpy, win);
	//XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

	// glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	// glXMakeCurrent(dpy, win, glc);

	// glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	// glXMakeCurrent(dpy, root, openGLContext);
	/*
	*/
	GLint drawFboId = 0, readFboId = 0;

	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
	glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
	std::cout << "Buffer in use: " << drawFboId << " " << readFboId << std::endl;



	// makeFrameBuffer();

	glEnable(GL_DEPTH_TEST); 
	// std::cout << FBO << " " << _ColorTextureObject 
	// 	<< " " << _DepthTextureObject << std::endl;

	// glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
	// glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
	// std::cout << "Buffer in use: " << drawFboId << " " << readFboId << std::endl;


	while(1) {
		//XNextEvent(dpy, &xev);
	//std::cout << "here" << std::endl;

		//if(xev.type == Expose) {
	        //XGetWindowAttributes(dpy, win, &gwa);
	        //std::cout << gwa.width << " " << gwa.height << std::endl;
	        glViewport(0, 0, window_width, window_height);
	        DrawAQuad(); 
	        screenshot("snapshotx11.png");
	        //glXSwapBuffers(dpy, win);
	        exit(EXIT_SUCCESS);
		//}
		        
		// else if(xev.type == KeyPress) {
	 //        keyboard_handle();
		// }
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