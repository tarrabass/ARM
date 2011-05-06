/*
 *  branch.cpp
 *  MappingDraw
 *
 *  Created by Francois tarrabass on 29.03.11.
 *  Copyright 2011 cenc. All rights reserved.
 *
 */

#include "branch.h"
branch::branch()
{

}

void branch::create(int _x,Perlin *_noise){	
	noise = _noise;
	x = _x;

	tempPoint.x = x;
	tempPoint.y = 0;
	index = 0;
	

	
	
	
}
void branch::clear(){
	cercles.clear();	
}

void branch::draw(){
	
	for(int i=0;i<cercles.size();i++){
		cercles[i].draw(noise);
	}
	int div = 30;
	if(cercles.size()<10){
		tempPoint.x = tempPoint.x+(noise->noise3(tempPoint.x/div,tempPoint.y/div,ofGetFrameNum()/div))*30;
		tempPoint.y = tempPoint.y+(noise->noise3(tempPoint.y/div,tempPoint.x/div,ofGetFrameNum()/div))*30;
		int size = 10  - cercles.size() ;
		addCercle(tempPoint,size);
		index++;

	}
}

void branch::addCercle(ofPoint p,int size){
	
	
	cercle tempCercle;
	tempCercle.create(p,size);
	cercles.push_back(tempCercle);
	
}



	