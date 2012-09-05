/**
 * @author David Griffith
 * @date 2012-08-24
 * @note This is homework for CSE 274. 
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 *
 * @note The code for creating Textures and Surfaces comes from, https://github.com/brinkmwj/CatPicture/blob/master/src/CatPictureApp.cpp
 * @note The code for creating the rectangle and circle come from Allyson Yoder, https://github.com/allysonyoder/CatPicture/commits/master 
 *
 * @note This project satisfies goals A.1 (rectangle), A.2 (circle), A.3 (line). A.7 (triangle), C, D,
 * E.4 (red/blue colors)
 * 
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW01_3App : public AppBasic {
  public:
	void setup();
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	
  private:
	  
	Surface* mySurface_; //The Surface object whose pixel array we will modify
	
	//Width and height of the screen
	static const int appWidth = 800;
	static const int appHeight = 600;
	static const int surfaceSize = 1024;

	// Call the consturctors

	// Satisfies goal (A.1)
	void newRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
	
	// Satisfies goal (A.2)
	void newCircle(uint8_t* pixels, int x, int y, int r);

	// Satisfies goal (A.7)
	void newTriangle(uint8_t* pixels, int p1, int p2, int sideLength); 

	// Satisfies goal (A.3)
	void newLineSegment(uint8_t* pixels, int x1, int y1, int lenght);
};
	// Setting my default settings.
	void HW01_3App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

	/** 
	* Constructs a new rectangle 
	* @param pixels the pixels of the image
	* @param x1 a x coordinate
	* @param y1 a y coordinate
	* @param x2 a second x coordinate
	* @param y2 a second y coordinate
	*/
	void HW01_3App :: newRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2) {
	
	//Figure out the starting and ending coordinates of the rectangle to fill
	int startx = (x1 < x2) ? x1 : x2;
	int endx = (x1 < x2) ? x2 : x1;
	int starty = (y1 < y2) ? y1 : y2;
	int endy = (y1 < y2) ? y2 : y1;
	
	//Do some bounds checking
	if(starty >= appHeight) return;
	if(startx >= appWidth) return;
	if(endx >= appWidth) endx = appWidth-1;
	if(endy >= appHeight) endy = appHeight-1;

	for (int y = 300; y <= endy; y++) {
		for (int x = 600; x <= endx; x++) {
			pixels[3*(x+y*surfaceSize)] = 0;
			pixels[3*(x+y*surfaceSize)+1] = 0;
			pixels[3*(x+y*surfaceSize)+2] = 255;
		}
	}
	}
	
	/**
	* Constructs a new circle
	* @param pixels the pixels of the image
	* @param x a x coordinate
	* @param y a y coordinate
	* @param r a radius
	*/
	void HW01_3App :: newCircle(uint8_t* pixels, int x, int y, int r) {

		if (r <= 0) return;

		for (int newY = y-r; newY <= y+r; newY++) {
			for (int newX = x-r; newX <= x+r; newX++) {
				//Check bounds
				if (newY < 0 || newX < 0 || newY >= appHeight || newX >= appWidth) continue;

				int newR = (int)sqrt((double)((newX-x)*(newX-x) + (newY - y)*(newY - y)));
				if (newR <= r) {
					int offset = 3*(newX+newY*surfaceSize);
			pixels[offset] = 255;
			pixels[offset+1] = 0;
			pixels[offset+2] = 0;
				}
			}
		}
	}

	/** 
	* Constructs a new triangle
	* @param pixels the pixels of the image
	* @param p1 a point (x, y) 
	* @param p2 a second point (x, y) 
	* @param sideLength the length of the triangle's sides
	*/
	void HW01_3App :: newTriangle(uint8_t* pixels, int p1, int p2, int sideLength) {

		if ((p1 <= appWidth) && ((p1 + sideLength) <= appWidth)) {

			for (int i = 0; i <= sideLength; i++) {
				pixels[3*(p1+p2*surfaceSize)] = 255;
				pixels[3*(p1+p2*surfaceSize)+1] = 0;
				pixels[3*(p1+p2*surfaceSize)+2] = 0;

				p1 += 1;
				p2 += 1;
			}

			for (int i = 0; i <= sideLength*2; i++) {
				pixels[3*(p1+p2*surfaceSize)] = 255;
				pixels[3*(p1+p2*surfaceSize)+1] = 255;
				pixels[3*(p1+p2*surfaceSize)+2] = 255;

				p1 -= 1;
			}

			for (int i = 0; i <= sideLength; i++) {
				pixels[3*(p1+p2*surfaceSize)] = 0;
				pixels[3*(p1+p2*surfaceSize)+1] = 0;
				pixels[3*(p1+p2*surfaceSize)+2] = 255;

				p1 += 1;
				p2 -= 1;
			}
		}
	}

	/**
	* Constructs a new line segment 
	* @param pixels the pixels of the image
	* @param x1 the x coordinate of the line segment
	* @param y1 the y coordinate of the line segment
	* @param length the lenght of the line segment
	*/
	void HW01_3App :: newLineSegment(uint8_t* pixels, int x1, int y1, int length) {

		for (int i = 0; i <= length; i++) {
			pixels[3*(x1+y1*surfaceSize)] = 255;
			pixels[3*(x1+y1*surfaceSize)+1] = 0;
			pixels[3*(x1+y1*surfaceSize)+2] = 0;
		
			x1 += 1;
		}
	}

	// The default setup
	void HW01_3App :: setup() {
		mySurface_ = new Surface(surfaceSize, surfaceSize, false);
	}


void HW01_3App::update()
{
	//Get our array of pixel information
	uint8_t* dataArray = (*mySurface_).getData();

	// Creative bits go here
	Color8u fill1 = Color8u(128,128,192);
	Color8u border1 = Color8u(192,192,255);
	Color8u fill2 = Color8u(192,192,192);
	Color8u border2 = Color8u(255,255,255);

	// Update our constructors with the given information, Satisfies goal (C).
	newRectangle(dataArray, 400, 450, 700, 450);
	newCircle(dataArray, 125, 375, 75);
	newTriangle(dataArray, 400, 450, 100);
	newLineSegment(dataArray, 100, 450, 600);
}

// Draw the images to the screen
void HW01_3App::draw()
{
	
	//Draw our texture to the screen, using graphics library
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( HW01_3App, RendererGl )
