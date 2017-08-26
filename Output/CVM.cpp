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
#include "CVM.h"
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
#include "Line.h"

extern Config progConfig; 
extern Shader* shader;
extern std::vector<std::shared_ptr<Vector>> vertexBuffer;
extern std::shared_ptr<Curve> curveBuffer;
extern WindowManager* winMan;


CVM::CVM(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height)
:View(vt,mainContext, loc_x, loc_y, window_width, window_height)
{ 
	
	fromPoint = Vector(0, 0, 6);
	atPoint = Vector(0, 0, 5);
	UpVector = Vector(0, 1, 0);	
	mouse = new Mouse(this);
	float r = height/width;
	verticalViewAngle = M_PI / 3;
	horizontalViewAngle = 2*asin(sin(0.5*verticalViewAngle)/r);


}

CVM::~CVM(){

}




void CVM::drawLineDDA(Vector v1, Vector v2, const float *color){

	v1 = translateFromWorldToViewPort(v1);
	v2 = translateFromWorldToViewPort(v2);

	// v1.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	// v2.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	View::drawLineDDA(v1[X], v1[Y], v2[X], v2[Y], color );

}

Vector CVM::translateFromWorldToViewPort(Vector v)const{
	Matrix mt;
	mt.makeTranslationMatrix(-fromPoint[X], -fromPoint[Y], -fromPoint[Z]);
	v = mt*v;

	Matrix mr(4, 0);
	Vector c = atPoint - fromPoint;
	Vector a = c.cross(UpVector);
	
	c.normalize();
	a.normalize();

	// does not have to unify because it is the cross product of two unit vectors 
	// also because they are perpendicular to each other.
	Vector b = a.cross(c); 
	mr.concatenate(a);
	mr.concatenate(b);
	mr.concatenate(c);
	mr.concatenate(Vector(0, 0, 0));

	mr = mr.transpose();
	mr[3][0] = 0;
	mr[3][1] = 0;
	mr[3][2] = 0;
	mr[3][3] = 1;

	v = mr*v;

	int xCenter = 0.5*width;
	int yCenter = 0.5*height;
	Vector ret;
	ret[X] = xCenter + (v[X] / v[Z]*width) / (2*tan(horizontalViewAngle / 2) );
	ret[Y] = yCenter + (v[Y] / v[Z]*height) / (2*tan(verticalViewAngle / 2) );
	return ret;
}


Vector CVM::translateFromViewPortToWorld(Vector v)const{

	float viewPort_width = 2*tan(0.5*verticalViewAngle);
	float viewPort_height = 2*tan(0.5*horizontalViewAngle);
	float viewPort_i = (v[X] / width)*viewPort_width;
	float viewPort_j = (v[Y] / height)*viewPort_height;
	Vector a = ((atPoint - fromPoint).cross(UpVector)).makeUnitVector();
	Vector v_i = a * ( -(0.5*viewPort_width - viewPort_i) );
	Vector v_j = UpVector.makeUnitVector() * ( - (0.5*viewPort_height - viewPort_j));
	return (fromPoint + (atPoint - fromPoint).makeUnitVector() ) + (v_i + v_j);

	// Matrix mt;
	// mt.makeTranslationMatrix(-fromPoint[X], -fromPoint[Y], -fromPoint[Z]);
	// v = mt*v;

	// Matrix mr(4, 0);
	// Vector c = atPoint - fromPoint;
	// Vector a = c.cross(UpVector);
	
	// c.normalize();
	// a.normalize();

	// // does not have to unify because it is the cross product of two unit vectors 
	// // also because they are perpendicular to each other.
	// Vector b = a.cross(c); 
	// mr.concatenate(a);
	// mr.concatenate(b);
	// mr.concatenate(c);
	// mr.concatenate(Vector(0, 0, 0));
	// mr[3][3] = 1;

	// mr = mr.transpose();

	// v = mr*v;

	// int xCenter = 0.5*width;
	// int yCenter = 0.5*height;
	// Vector ret;
	// ret[X] = xCenter + (v[X] / v[Z]*width) / (2*tan(horizontalViewAngle / 2) );
	// ret[Y] = yCenter + (v[Y] / v[Z]*height) / (2*tan(verticalViewAngle / 2) );
	// return ret;


}

void CVM::translateCamera(Vector v){
	toCOORDS(v);

	Vector transY = UpVector;
	Vector transX = UpVector.cross(atPoint-fromPoint);
	Vector transZ = (atPoint - fromPoint).makeUnitVector();
	transX.makeUnitVector();
	transY.makeUnitVector();
	transX = transX * v[X];
	transY = transY * v[Y];
	transZ = transZ * v[Z];
	fromPoint = fromPoint + ( transX + transY + transZ );
	atPoint = atPoint + ( transX + transY + transZ);
	// std::cout << fromPoint << std::endl;
	// std::cout << atPoint << std::endl << std::endl;

}


void CVM::rotateCamera(Vector v){
	toCOORDS(v);
	v = v/10;
	Matrix m1;

	m1.makeTranslationMatrix(fromPoint[X],fromPoint[Y],fromPoint[Z]);


	Vector transY = UpVector;
	Vector transX = UpVector.cross(atPoint-fromPoint);
	Vector transZ = (atPoint - fromPoint).makeUnitVector();
	transX.makeUnitVector();
	transY.makeUnitVector();
	transX = transX * v[X];
	transY = transY * v[Y];
	transZ = transZ * v[Z];
	atPoint = atPoint + ( transX + transY + transZ);
	// std::cout << fromPoint << std::endl;
	// std::cout << atPoint << std::endl << std::endl;

}


void CVM::updateWindow(){

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	clear();

	// draw coordinate
	drawAxis();

	//drawLineDDA(*shader->rotationVector.getHead(), *shader->rotationVector.getTail(), progConfig.COLOR_rotVec);
	

	if(progConfig.fillMode == FILL)
		rayTrace();
	else	
		shader->drawAll();

	if( progConfig.opMode == CLIPPING )
		mouse->viewClipLine();
	else if ( progConfig.opMode == EDITING)
		mouse->drawSelectionBox();

	// draw buffers
	if (curveBuffer->size() > 0)
		curveBuffer->draw(progConfig.COLOR_regStroke);

	View::drawOutline();
	
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, PixelBuffer.get());
	
	glutPostRedisplay();
}

void CVM::reshapeWindow(const Vector& min, const Vector& max){
	// float minX = min[axis1], maxX = max[axis1], minY = min[axis2], maxY = max[axis2];

	// float dx = maxX - minX, 
	// 	  dy = maxY - minY;

	// pixelsPerUnit = (((height < width)? height:width) - 2*PADDING ) / ((dx > dy)? dx: dy); 
	// float shift = PADDING / pixelsPerUnit;

	// coordLoc[axis1] = min[axis1] - shift;
	// coordLoc[axis2] = min[axis2] - shift;	
}


void CVM::drawAxis(){
	// Vector origin(0, 0, 0);
	// origin.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	// drawVertical(origin[axis1], progConfig.COLOR_axis);
	// drawHorizontal(origin[axis2], progConfig.COLOR_axis);
}	

void CVM::drawOutline(const Face & face, const float * color){

	for (unsigned int i = 0; i < face.getVerticesCnt() ; i++)
		drawLineDDA(*face.getV(i), *face.getV((i+1) % face.getVerticesCnt() ), color);


}

void CVM::fillPolygon(Geometry &geo){

/*
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
*/
}

void CVM::halfToning(Geometry &geo){
/*

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
	*/
}




void CVM::fillPolygons(std::vector<std::shared_ptr<Geometry>> &geos){
	// sort(geos.begin(), geos.end(),  
	// 	[&, this](const std::shared_ptr<Geometry> & g1, const std::shared_ptr<Geometry> & g2 ) -> bool{
	// 		//return f1 > f2;
	// 		return g1->getCentroid()[getDeptAxis()] > 
	// 				g2->getCentroid()[getDeptAxis()];
	// 	});

	// for (auto geo: geos)
	// 	fillPolygon(*geo);
}

Vector oldV;


void CVM::rayTrace(){
	// Vector v = translateFromViewPortToWorld(Vector(width / 2 + 71, height / 2));
	// Vector curColor = shader->rayTrace(Line(fromPoint, v - fromPoint));
	
	
	float maxColor = -std::numeric_limits<float>::max();
	for (int x = 0; x < width; x++){
		for( int y = 0; y < height; y ++){
			Vector v = translateFromViewPortToWorld(Vector(x, y));
			Vector curColor = shader->rayTrace(Line(fromPoint, v - fromPoint));
			if (curColor[R] != -1 ){
				for(int i = 0; i < 3; i++){
					if (maxColor < curColor[i])
						maxColor = curColor[i];
				}

				setPix(x, y, static_cast<Matrix>(curColor)[0] );
			}
		}
			if(x % static_cast<int>(width / 20) == 0)
				std::cout << (x/width)*100 << "\% finished." << std::endl;  
	}

	// Vector dColor = maxColor - minColor;
	// for (int x = 0; x < width; x++){
	// 	for( int y = 0; y < height; y ++){
	// 		float* curPixel = &(PixelBuffer.get()[int((y*width + x)*3)]);
	// 		curPixel[R] = (curPixel[R] )/maxColor[R];
	// 		curPixel[G] = (curPixel[G] )/maxColor[G];
	// 		curPixel[B] = (curPixel[B] )/maxColor[B];
	// 	}
	// }

	for(int i = 0; i < width*height*3; i++){
		PixelBuffer.get()[i] = PixelBuffer.get()[i] / maxColor;
	}

}
