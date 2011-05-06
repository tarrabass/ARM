/*
 *  effectOne.cpp
 *  MappingDraw
 *
 *  Created by mchrbn on 27.03.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */

#include "effectSix.h"
void effectSix::apply(vector <mdLine> lns){
	lines = lns;
	noise = new Perlin(10,10.0,10.0, time(NULL));
	ofSetVerticalSync(true);
	rotateView = true;
	currentRot = 0;
	// create a 2D spline with MSA::Vec2f's
	useLength = true;
	interpolationType	= MSA::kInterpolationCubic;
	//interpolationType = MSA::kInterpolationLinear;
	int numItems = 10;
	int padding = 100;
	float len = (ofGetWidth() - padding*2.0f) / numItems;
	spherePosPerc	= 0;
	sphereSpeed = 	0.005f;
	spline2D.clear();
	spline2D.reserve(lines.size());		// not essential, but good habit if you know how big its gonna be
	for(int i=0; i<lines.size(); i++) {
		
		int posx1 = lines[i].x1;
		int posy1 = lines[i].y1;
		int posx2 = lines[i].x2;
		int posy2 = lines[i].y2;
		
		MSA::Vec2f v = MSA::Vec2f(posx1, posy1);
		MSA::Vec2f v2 = MSA::Vec2f(posx2, posy2);
		spline2D.push_back(v);
		
		//spline2D.push_back(v2);
		
		//MSA::Vec2f v = MSA::Vec2f(i * len + padding - ofGetWidth()/2, ofGetHeight()/2 + ofGetHeight()*0.2f * cos(i*0.9));
		//spline2D.push_back(v);
	}	
	int posx1 = lines[0].x1;
	int posy1 = lines[0].y1;
	int posx2 = lines[0].x2;
	int posy2 = lines[0].y2;
	
	MSA::Vec2f v = MSA::Vec2f(posx1, posy1);
	MSA::Vec2f v2 = MSA::Vec2f(posx2, posy2);
	spline2D.push_back(v);

	
	spline3D.verbose = true;
	
	glEnable(GL_DEPTH_TEST);

	

}



void effectSix::draw(float sound,bool defromPerlin,float left[256] ){
	
	glPushMatrix();
	//glTranslatef(ofGetWidth()/2, 0, 0);		// move to center of screen horizontally (so we can rotate)
/*
	if(rotateView) {
		currentRot += 0.2;
		glRotatef(currentRot, 0, 1, 0);		// rotate view
	} else {
		currentRot = 0;
	}
*/
	
	
	int numSteps = floor(200/ (float)ofGetWidth() * 1000);
	if(numSteps<10) numSteps = 10;
	float spacing = 1.0/numSteps;	
	
	// draw spline2D
	glColor3f(1, 1, 1);
	//drawInterpolatorRaw(spline2D);
	
	// draw interpolated spline2D
	glColor3f(0, 0, 1);
	//drawInterpolatorSmooth(spline2D, numSteps);
	
	// draw raw spline3D
	glColor3f(1, 1, 1);
	//drawInterpolatorRaw(spline3D);
	
	// draw interpolated spline3D
	glColor3f(0.2f, 0.2f, 0.2f);
	//drawInterpolatorSmooth(spline3D, numSteps);
	
	
	
	// draw sphere moving along 3D path

	MSA::Vec2f spherePos = spline2D.sampleAt(spherePosPerc);
	
	
	trails.push_back(spherePos);
	for (int i=trails.size(); i>1; i--) {
	glPushMatrix();
	float alpha = (i*(0.02));
	glColor4f(1, 1, 1,alpha);
	glTranslatef(trails[i].x, trails[i].y,0);
	//glutSolidSphere(20, 5, 5);
	//glBegin(GL_LINES);

	
	ofCircle(0, 0, 2);
	glPopMatrix();
		glEnd();
		}
	
	if(trails.size() > 50){
	trails.erase(trails.begin());
	}

	
	// move sphere
	// if it reaches the edges, bounce back
	printf("spherePosPerc>>%f",spherePosPerc);


	spherePosPerc += sphereSpeed;
	
	
	if(spherePosPerc > 1) {
		spherePosPerc = 1;
		sphereSpeed *= -1;
	} else if(spherePosPerc < 0) {
		spherePosPerc = 0;
		sphereSpeed *= -1;
	}

	
	
	glPopMatrix();
	
	ofSetColor(0);
	string uiLin = interpolationType == MSA::kInterpolationLinear ? "* " : "  ";
	string uiCub = interpolationType == MSA::kInterpolationCubic ? "* " : "  ";
	string uiDist = spline3D.getUseLength() ? "* " : "  ";
	ofDrawBitmapString( ofToString(ofGetFrameRate(), 2) + "\n"
					   + "numSteps (resampling resolution - mouseX to change): " + ofToString(numSteps) + "\n"
					   + "mouse click around the area to draw a 3D spline\n"
					   + "\n"
					   + uiLin + "'1' to use linear interpolation\n"
					   + uiCub + "'2' to use cubic (catmull rom) interpolation\n"
					   + "\n"
					   + uiDist + "'d' to toggle 'using Length in interpolation'\n"
					   + "\n"
					   + "'c' to clear 3D spline\n"
					   , 20, 20);

}