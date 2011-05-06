/*
 *  branch.cpp
 *  MappingDraw
 *
 *  Created by Francois tarrabass on 29.03.11.
 *  Copyright 2011 cenc. All rights reserved.
 *
 */

#include "cercle.h"
cercle::cercle()
{

}

void cercle::create(ofPoint _p,int _size){
	p = _p;
	size = _size;

}

void cercle::draw(Perlin *_noise){
	int div = 80;
	noise = _noise;
	ofPoint newPos;
	newPos.x = p.x + ofRandom(2);
	newPos.y = p.y + ofRandom(2);
	ofSetLineWidth(2);
	ofCircle(newPos.x,newPos.y,size);
}



	