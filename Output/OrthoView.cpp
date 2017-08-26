#include <cstring>
#include <GL/glut.h>
#include <utility>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include <queue>
#include <utility>
#include <memory>
#include "View.h"
#include "OrthoView.h"
#include "Vector.h"
#include "AEL.h"
#include "Geometry.h"
#include "Config.h"
#include "Shader.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Curve.h"
#include "Utility.h"
#include "WindowManager.h"

extern Config progConfig; 
extern Shader* shader;
extern std::vector<std::shared_ptr<Vector>> vertexBuffer;
extern std::shared_ptr<Curve> curveBuffer;
extern WindowManager* winMan;

void update();
void mouseClick(int button, int state, int x, int y);
void mouseHold(int x, int y);
void mouseHover(int x, int y);

void keyboardHandler(unsigned char key, int x, int y);
void keyboardReleaseHandler(unsigned char key, int x, int y);
void keyboardHandler(unsigned char key, int x, int y);
void keyboardReleaseHandler(unsigned char key, int x, int y);

int PADDING = 20;

OrthoView::OrthoView(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height)
:View(vt,mainContext, loc_x, loc_y, window_width, window_height)
{ //, int canvas_width, int canvas_height){
	//allocate new pixel buffer, need initialization!! 
	if (viewType == XY){
		axis1 = X;
		axis2 = Y;
	} 
	else if (viewType == ZY){
		axis1 = Z;
		axis2 = Y;
	}
	else if (viewType == XZ){
		axis1 = X;
		axis2 = Z;
	}

}

OrthoView::~OrthoView(){

}




void OrthoView::drawLineDDA(Vector v1, Vector v2, const float *color){
	v1.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	v2.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	

	View::drawLineDDA(v1[axis1], v1[axis2], v2[axis1], v2[axis2], color );

}


void OrthoView::updateWindow(){

	//glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	clear();

	// draw coordinate
	drawAxis();

	//drawLineDDA(*shader->rotationVector.getHead(), *shader->rotationVector.getTail(), progConfig.COLOR_rotVec);
	shader->drawAll();
	View::drawOutline();

	if( progConfig.opMode == CLIPPING )
		mouse->viewClipLine();
	else if ( progConfig.opMode == EDITING)
		mouse->drawSelectionBox();

	// draw buffers
	if (curveBuffer->size() > 0)
		curveBuffer->draw(progConfig.COLOR_regStroke);

	
	
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, PixelBuffer.get());
	
	glutPostRedisplay();
}

void OrthoView::reshapeWindow(const Vector& min, const Vector& max){
	float minX = min[axis1], maxX = max[axis1], minY = min[axis2], maxY = max[axis2];

	float dx = maxX - minX, 
		  dy = maxY - minY;

	pixelsPerUnit = (((height < width)? height:width) - 2*PADDING ) / ((dx > dy)? dx: dy); 
	float shift = PADDING / pixelsPerUnit;

	coordLoc[axis1] = min[axis1] - shift;
	coordLoc[axis2] = min[axis2] - shift;	
}


void OrthoView::drawAxis(){
	Vector origin(0, 0, 0);
	origin.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	drawVertical(origin[axis1], progConfig.COLOR_axis);
	drawHorizontal(origin[axis2], progConfig.COLOR_axis);
}	

void OrthoView::drawOutline(const Face & face, const float * color){

	for (unsigned int i = 0; i < face.getVerticesCnt() ; i++)
		drawLineDDA(*face.getV(i), *face.getV((i+1) % face.getVerticesCnt() ), color);


}

void OrthoView::fillPolygon(Geometry &geo){


	if (&geo == nullptr)
		return;

	// sort faces
	sort(geo.getFaces().begin(), geo.getFaces().end(),  
		[&, this](const std::shared_ptr<Face> &f1, const std::shared_ptr<Face> &f2 ) -> bool{
			//return f1 > f2;
			return f1->getNormalVector()[getDeptAxis()] > 
					f2->getNormalVector()[getDeptAxis()];
		});


	for (auto face: geo.getFaces()){
		if(face->getNormalVector()[getDeptAxis()] < 0)
			continue;

		std::vector<std::pair<int, Vector>> bucket;
		std::vector<int> prevBucket;
		std::vector<AEL*> AELs = face->getAELs(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z],axis1, axis2);
		

		// int looking = 1;
		// for (int lineCnt = AELs[looking]->getY(); lineCnt > 0; lineCnt--){
		// 	if (AELs[looking]->hasEnded(lineCnt))
		// 		break;
		// 	std::cout << interpolate(AELs[looking]->getY(), AELs[looking]->getLastY(), lineCnt, AELs[looking]->getC1(), AELs[looking]->getC2()) << std::endl;
					 
		// }
		// exit(0);

		if(AELs.size() <= 0)
			return;
		for (int lineCnt = AELs[0]->getY(); lineCnt > 0; lineCnt--){
			for (unsigned int i = 0; i < AELs.size(); i++){
				//std::cout << i << " " << std::endl;
				AEL* ael = AELs[i]; 
				if (lineCnt<=ael->getY())
				{
					bucket.push_back(
						std::pair<int, Vector>(static_cast<int>(ael->next()), 
										interpolate(AELs[i]->getY(), AELs[i]->getLastY(), lineCnt, AELs[i]->getC1(), AELs[i]->getC2())));
					 // if (i == 1){

					 // 	std::cout << interpolate(AELs[i]->getY(), AELs[i]->getLastY(), lineCnt, AELs[i]->getC1(), AELs[i]->getC2()) << std::endl;
					 // }
				}
				else if (AELs.size() <= 0)
					break;


				if (ael->hasEnded(lineCnt)){
					//bucket.push_back(static_cast<int>(ael->next()));
					remove(&AELs, i);
					lineCnt++;
					bucket.clear();
					break;
				}
			}
			// this is sorted in descending order so I can use pop_back in the next while loop 
			sort(bucket.begin(), bucket.end(), 
				[](std::pair<int, Vector> p1, std::pair<int, Vector> p2 ){ 
					return p1.first > p2.first;
				});
			
			// drawPics
			while(bucket.size() >= 2){
				const std::pair<int, Vector>  & startPair = bucket[bucket.size() - 1];
				const std::pair<int, Vector>  & endPair = bucket[bucket.size() - 2];

				//std::cout << startPair.second << std::endl;
				for ( int x_i = startPair.first; x_i <= endPair.first; x_i++ ){
					//Vector firstColor = interpolate(startPair.getY(), startPair.getLastY(), lineCnt, startPair.getC1(), startPair.getC2());
					//Vector secondColor = interpolate(endPair.getY(), endPair.getLastY(), lineCnt, endPair.getC1(), endPair.getC2());
					setPix(x_i, lineCnt, //

						static_cast<Matrix>(
						interpolate(startPair.first, endPair.first, x_i, startPair.second, endPair.second)

						)[0] );
				}
				bucket.pop_back();
				bucket.pop_back();
			}

			bucket.clear();
		}
		if (progConfig.showEdge == true)
			drawOutline(*face, Color().DGREY);
	}

}

void OrthoView::halfToning(Geometry &geo){


	if (&geo == nullptr)
		return;

	// sort faces
	sort(geo.getFaces().begin(), geo.getFaces().end(),  
		[&, this](const std::shared_ptr<Face> &f1, const std::shared_ptr<Face> &f2 ) -> bool{
			//return f1 > f2;
			return f1->getNormalVector()[getDeptAxis()] > 
					f2->getNormalVector()[getDeptAxis()];
		});


	for (auto face: geo.getFaces()){
		if(face->getNormalVector()[getDeptAxis()] < 0)
			continue;

		std::vector<std::pair<int, Vector>> bucket;
		std::vector<int> prevBucket;
		std::vector<AEL*> AELs = face->getAELs(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z],axis1, axis2);
		


		if(AELs.size() <= 0)
			return;
		for (int lineCnt = AELs[0]->getY(); lineCnt > 0; lineCnt -= 3){
			for (unsigned int i = 0; i < AELs.size(); i++){
				//std::cout << i << " " << std::endl;
				AEL* ael = AELs[i]; 
				if (lineCnt<=ael->getY())
				{

					ael->next();
					ael->next();
					bucket.push_back(
						std::pair<int, Vector>(static_cast<int>(ael->next()), 
										interpolate(AELs[i]->getY(), AELs[i]->getLastY(), lineCnt, AELs[i]->getC1(), AELs[i]->getC2())));
					 // if (i == 1){

					 // 	std::cout << interpolate(AELs[i]->getY(), AELs[i]->getLastY(), lineCnt, AELs[i]->getC1(), AELs[i]->getC2()) << std::endl;
					 // }
				}
				else if (AELs.size() <= 0)
					break;


				if (ael->hasEnded(lineCnt)){
					//bucket.push_back(static_cast<int>(ael->next()));
					remove(&AELs, i);
					lineCnt+=3;
					bucket.clear();
					break;
				}
			}
			// this is sorted in descending order so I can use pop_back in the next while loop 
			sort(bucket.begin(), bucket.end(), 
				[](std::pair<int, Vector> p1, std::pair<int, Vector> p2 ){ 
					return p1.first > p2.first;
				});
			
			// drawPics
			while(bucket.size() >= 2){
				const std::pair<int, Vector>  & startPair = bucket[bucket.size() - 1];
				const std::pair<int, Vector>  & endPair = bucket[bucket.size() - 2];

				//std::cout << startPair.second << std::endl;
				for ( int x_i = startPair.first; x_i <= endPair.first; x_i+=3 ){
					Vector c ( interpolate(startPair.first, endPair.first, x_i, startPair.second, endPair.second));
//std::cout << c << std::endl;
					setMagaPix(getMagePixel(c), x_i, lineCnt);

				}
				bucket.pop_back();
				bucket.pop_back();
			}

			bucket.clear();
		}
	}
}

std::shared_ptr<Vector> OrthoView::getMagePixel(const Vector& c){
	/* MAGIC NUMBERS */	
	int pixelWidth = 3;
	/* END: MAGIC NUMBERS */


	int n_pix = pow(pixelWidth, 2);
	int n_onPix = c.max()*n_pix;
	int n_offPix = n_pix - n_onPix;
	float sum = c[R] + c[G] + c[B];
	int n_r = (c[R]/sum)*n_onPix;
	int n_g = (c[G]/sum)*n_onPix;
	int n_b = (c[B]/sum)*n_onPix;

	std::shared_ptr<Vector> ret (new Vector[n_pix], [](Vector* vptr){ delete[] vptr; });
	std::shared_ptr<int> r_nums = generateUniqeInt(n_pix);

	for ( int i = 0; i < n_pix; i++){
		if (r_nums.get()[i] < n_offPix)
			ret.get()[r_nums.get()[i]] = Vector(0.0f, 0.0f, 0.0f); // black
		else if (r_nums.get()[i] < n_offPix + n_r) 	
			ret.get()[r_nums.get()[i]] = Vector(1.0f, 0.0f, 0.0f); // red
		else if (r_nums.get()[i] < n_offPix + n_r + n_g) 	
			ret.get()[r_nums.get()[i]] = Vector(0.0f, 1.0f, 0.0f); // green
		else 	
			ret.get()[r_nums.get()[i]] = Vector(0.0f, 0.0f, 1.0f); // blue
		
	}

	return ret;
}

void OrthoView::setMagaPix(std::shared_ptr<Vector> magaPix, const int& x, const int& y){
	/* MAGIC NUMBERS */	
	int pixelWidth = 3;
	/* END: MAGIC NUMBERS */

	for (int rowPtr = 0; rowPtr < pixelWidth; rowPtr++){
		for (int colPtr = 0; colPtr < pixelWidth; colPtr++){
			setPix(x+colPtr, y+rowPtr, static_cast<Matrix>(magaPix.get()[rowPtr*pixelWidth + colPtr])[0] );
		}
	}


}

INDEX OrthoView::getDeptAxis()const{
	int n = static_cast<int>(axis1) + static_cast<int>(axis2);
	if (n == 1)
		return Z; 
	else if (n == 2)
		return Y;
	else
		return X; 
}


void OrthoView::fillPolygons(std::vector<std::shared_ptr<Geometry>> &geos){
	sort(geos.begin(), geos.end(),  
		[&, this](const std::shared_ptr<Geometry> & g1, const std::shared_ptr<Geometry> & g2 ) -> bool{
			//return f1 > f2;
			return g1->getCentroid()[getDeptAxis()] > 
					g2->getCentroid()[getDeptAxis()];
		});

	for (auto geo: geos)
		fillPolygon(*geo);
}


Vector OrthoView::translateFromWorldToViewPort(Vector v)const{
	Vector position = v.inPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	return Vector(position[axis1], position[axis2]);
}