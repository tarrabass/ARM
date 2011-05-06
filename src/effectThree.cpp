/*
 *  effectOne.cpp
 *  MappingDraw
 *
 *  Created by mchrbn on 27.03.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */

#include "effectThree.h"


void effectThree::apply(vector <mdLine> lns){
	lines = lns;
	noise = new Perlin(1,1.0,1.0, time(NULL));
}


void effectThree::draw(float sound,bool defromPerlin,float left[256] ){
	
	ofSetLineWidth(1);
	ofFill();
	ofSetColor(255, 255, 255);
	
	//Applique l'effet sur toutes les lignes
	
	glLineWidth(2.0f);
	
	
	glColor3ub((unsigned char)255,(unsigned char)255,(unsigned char)255);
	glPointSize(2);
	
	
	for(int i=0; i<lines.size(); i++){
		
		int div = 10;
		
		int posx1 = lines[i].x1;
		int posy1 = lines[i].y1;
		int posx2 = lines[i].x2;
		int posy2 = lines[i].y2;
	
		if(defromPerlin){
	
		float simplexNoiseX1 = (noise->noise3((512.0-(float)posx1)/div,(float)posy1/div,ofGetFrameNum()/3))*sound*15000;
		float simplexNoiseY1 = (noise->noise3((350-(float)posy1)/div,(float)posx1/div,ofGetFrameNum()/3))*sound*15000;
		float simplexNoiseX2 = (noise->noise3((512-(float)posx2)/div,(float)posy2/div,ofGetFrameNum()/3))*sound*15000;
		float simplexNoiseY2 = (noise->noise3((350-(float)posy2)/div,(float)posx2/div,ofGetFrameNum()/3))*sound*15000;
		
		posx1Voulu = posx1 + simplexNoiseX1;
		posy1Voulu = posy1 + simplexNoiseY1;
		posx2Voulu = posx2 + simplexNoiseX2;
		posy2Voulu = posy2 + simplexNoiseY2;
		
		float diffx1 =  posx1Voulu - posx1;
		float diffy1 =  posy1Voulu - posy1;
		float diffx2 =  posx2Voulu - posx2;
		float diffy2 =  posy2Voulu - posy2;
			
		posx1 += diffx1/150;
		posy1 += diffy1/150;
		posx2 += diffx2/150;
		posy2 += diffy2/150;
			
		}

		
		float angle = atan2(double(posy2-posy1) , double(posx2-posx1));
		float dist = sqrt(ofDistSquared(posx1, posy1, posx2, posy2 ));
		float mydegreangle = ofRadToDeg(angle);
		float rapport = 256/dist;
		ofPushMatrix();
		ofTranslate(posx1, posy1,0);
		ofRotateZ(mydegreangle); 
		

		glBegin(GL_LINE_STRIP);
		
		for (int i = 0; i < 256; i+=4){
			float coeff = (127-((float)abs(127-i)))/2;
			//ofLine(100+i,200,100+i,200+left[i]*coeff);
			
			glVertex3f(i/rapport,left[i]*coeff, 0);
			
		}
		glEnd();
		
		glPopMatrix();
	}
}