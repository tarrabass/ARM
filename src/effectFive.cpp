/*
 *  effectOne.cpp
 *  MappingDraw
 *
 *  Created by mchrbn on 27.03.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */

#include "effectFive.h"


void effectFive::apply(vector <mdLine> lns){
	offcetTime = 0;
	period = 1;
	indexLine = 0;
	indexBranch = 0;
	for(int z=0; z<branches.size(); z++){
		branches[z].clear();
		
	}
	branches.clear();
	lines = lns;
	noise = new Perlin(10,10.0,10.0, time(NULL));

	

}

void effectFive::builtNextBranch(){
printf("on built next branche!!!%i",indexLine);
	if(indexLine<lines.size()){
	
		int posx1 = lines[indexLine].x1;
		int posy1 = lines[indexLine].y1;
		int posx2 = lines[indexLine].x2;
		int posy2 = lines[indexLine].y2;
		float dist = sqrt(ofDistSquared(posx1, posy1, posx2, posy2 ));
		//branches.clear();
		int nbBranch = int(dist/20);
		if (indexBranch<nbBranch) {
			branch tempBranch;
			tempBranch.create((dist/20)*indexBranch,noise);
			branches.push_back(tempBranch);
			indexBranch++;
		}else {
			indexBranch = 0;
			indexLine++;
		}

		

		
	}
	


}

void effectFive::draw(float sound,bool defromPerlin,float left[256]){
	offcetTime++;
	if(offcetTime > period){
	
		builtNextBranch();
			offcetTime = 0;
	}
	
	
	
	//ofSetLineWidth(1);
	ofNoFill();
	ofSetColor(255, 255, 255);
	int index = 0;
	
	//Applique l'effet sur toutes les lignes
	
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
		
		float dist = sqrt(ofDistSquared(posx1, posy1, posx2, posy2 ));
		float coeff = 256.0 / dist;
		float hight = 200.0 / coeff;
		float angle = atan2(double(posy2-posy1) , double(posx2-posx1));
		float mydegreangle = ofRadToDeg(angle);			
		
		glPushMatrix();
		ofTranslate(posx1, posy1,0);
		ofRotateZ(mydegreangle);
	//	glBegin(GL_LINES);

		for(int x = 1; x < dist; x +=20) {
			if(branches.size()>index){
			branches[index].draw();
			index++;
			}
			//ofCircle(x,0, 10);
		
		}
		
		glPopMatrix();
	}
}