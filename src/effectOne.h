/*
 *  effectOne.h
 *  MappingDraw
 *
 *  Created by mchrbn on 27.03.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */

#include "ofMain.h"
#include "mdLine.h"
#include "perlin.h"

class effectOne{

	
	public:
		void apply(vector <mdLine> lns);
		void draw(float sound,bool defromPerlin);
		
	private:
		vector <mdLine> lines;
		Perlin *noise;
	float posx1Voulu;
	float posy1Voulu;
	float posx2Voulu;
	float posy2Voulu;

};