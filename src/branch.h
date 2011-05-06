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
#include "cercle.h"
#include "perlin.h"
class branch{
	
public:
	branch();
	void create(int _x,Perlin *_noise);
	Perlin *noise;
	void draw();
	void clear();
	void addCercle(ofPoint p,int size);

	

private:
	int x;
	int index;
	ofPoint tempPoint; 
	vector<cercle> cercles;
	int nbCercle;
	
	
};

