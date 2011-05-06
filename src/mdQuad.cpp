/*
 *  mdQuad.cpp
 *  MappingDraw
 *
 *  Created by mchrbn on 06.04.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */

#include "mdQuad.h"


mdQuad::mdQuad(){

		///
	
	x1=0;
	x2=0;
	x3=0;
	x4=0;
	
	y1=0;
	y2=0;
	y3=0;
	y4=0;
	
	width = 1;
	
	videoOn = false;
}


void mdQuad::draw(ofFbo	fbo,ofShader shader){

	fbo.getTexture(0).bind();

    glBegin(GL_QUADS);
		
	glTexCoord2f(0.0,0.0);

	glVertex3f(x1, y1,  0.0);	// Bottom Left Of The Texture and Quad
  	glTexCoord2f(320,0);
	glVertex3f(x2, y2,  0.0);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(320,240);  
	glVertex3f( x3,  y3,  0.0);	// Top Right Of The Texture and Quad
	glTexCoord2f(0,240);  
	glVertex3f(x4, y4,  0.0);	// Top Left Of The Texture and Quad
	glEnd();
	
    //glActiveTexture(GL_TEXTURE0);
  fbo.getTexture().unbind();

	
	if(videoOn){
		videoTexture.setPoints(x1,y1,x2,y2,x3,y3,x4,y4);
		//videoTexture.loadData(vPlayer->getPixels(), vPlayer->getWidth(), vPlayer->getHeight(), GL_RGB);
		///videoTexture.loadData(fbo.getPixels(),fbo.getWidth(), fbo.getHeight(), GL_RGB);
		
		videoTexture.draw();
	}
}

void mdQuad::idleMovie(){
	if(videoOn){
		vPlayer->update();
	}
}

void mdQuad::drawPoint(int p){
	
	
	ofNoFill();
	ofSetColor(255, 0, 0);
	
	if(p == 0)
		ofCircle(x1, y1, 5);
	else if(p == 1)
		ofCircle(x2, y2, 5);
	else if(p == 2)
		ofCircle(x3, y3, 5);
	else if(p == 3)
		ofCircle(x4, y4, 5);
}

void mdQuad::loadMovie(ofVideoPlayer* vp){
	videoOn = true;
	vPlayer = vp;
	videoTexture.allocate(vPlayer->getWidth(), vPlayer->getHeight(), GL_RGB);
}

void mdQuad::create(int x, int y){
	x1=x;
	x2=x;
	x3=x;
	x4=x;
	
	y1=y;
	y2=y;
	y3=y;
	y4=y;
	
	videoOn = false;
}

void mdQuad::updateP1(int x, int y){
	x1 = x;
	y1 = y;
}

void mdQuad::updateP2(int x, int y){
	x2 = x;
	y2 = y;
}

void mdQuad::updateP3(int x, int y){
	x3 = x;
	y3 = y;
}

void mdQuad::updateP4(int x, int y){
	x4 = x;
	y4 = y;
}