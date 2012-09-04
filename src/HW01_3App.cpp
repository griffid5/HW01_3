/**
 * @author David Griffith
 * @date 2012-08-24
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 *
 * @note The code fore creating Textures and Surfaces comes from, https://github.com/brinkmwj/CatPicture/blob/master/src/CatPictureApp.cpp
 *
 * @note This project satisfies goals A.1 (rectangle), A.2 (circle), B.1 (blur), E.2 (transparency),
 * E.5 (animation) and E.6 (mouse interaction)
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
	static const int appWidth=800;
	static const int appHeight=600;
	static const int surfaceSize = 1024;

	void newRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
	void newCircle(uint8_t* pixels, int x, int y, int r);
};
void HW01_3App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}


	void HW01_3App :: newRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2) {
	//Figure out the starting and ending coordinates of the rectangle to fill
	int startx = (x1 < x2) ? x1 : x2;
	int endx = (x1 < x2) ? x2 : x1;
	int starty = (y1 < y2) ? y1 : y2;
	int endy = (y1 < y2) ? y2 : y1;
	
	//Do some bounds checking
	if(endx >= appWidth) endx = appWidth-1;
	if(endy >= appHeight) endy = appHeight-1;

	for (int y = 50; y <= endy; y++) {
		for (int x = 50; x <= endx; x++) {
			pixels[3*(x+y*surfaceSize)] = 50;
			pixels[3*(x+y*surfaceSize)+1] = 150;
			pixels[3*(x+y*surfaceSize)+2] = 200;
		}
	}
	}
	

	void HW01_3App :: newCircle(uint8_t* pixels, int x, int y, int r) {

		if (r <= 0) return;

		for (int newY = y-r; newY <= y+r; newY++) {
			for (int newX = x-r; newX <= x+r; newX++) {
				//Check bounds
				if (newY < 0 || newX < 0 || newY >= appHeight || newX >= appWidth) continue;

				int newR = (int)sqrt((double)((newX-x)*(newX-x) + (newY - y)*(newY - y)));
				if (newR <= r) {
					int offset = 3*(newX+newY*surfaceSize);
			pixels[offset] = 100;
			pixels[offset+1] = 100;
			pixels[offset+2] = 100;
				}
			}
		}
	}

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

	newRectangle(dataArray, 800, 600, 800, 600);
	newCircle(dataArray, 300, 350, 100);
}
	// End creative bits
	//

void HW01_3App::draw()
{
	
	//Draw our texture to the screen, using graphics library
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( HW01_3App, RendererGl )
