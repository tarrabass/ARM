/*
 *  branch.h
 *  MappingDraw
 *
 *  Created by Francois tarrabass on 29.03.11.
 *  Copyright 2011 cenc. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"
#include "perlin.h"

class cercle{
	
public:
	cercle();
	void create(ofPoint _p,int _size);
	void draw(Perlin *_noise);
	Perlin *noise;

	
private:
	ofPoint p;
	int size;
	
};

