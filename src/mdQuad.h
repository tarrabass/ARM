/*
 *  mdQuad.h
 *  MappingDraw
 *
 *  Created by mchrbn on 06.04.11.
 *  Copyright 2011 HEAD. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "ofTextureAdv.h"


class mdQuad{

	public:
		mdQuad();
		void draw(ofFbo	fbo,ofShader shader);
		void drawPoint(int p);
		void create(int x, int y);
		void loadMovie(ofVideoPlayer* vp);
		void idleMovie();
		void updateP1(int x, int y);
		void updateP2(int x, int y);
		void updateP3(int x, int y);
		void updateP4(int x, int y);
	
	//// fbo stufff ///
	ofShader shader;
	
	////////////////////
		int x1,x2,x3,x4,y1,y2,y3,y4;
		int width;
		ofVideoPlayer* vPlayer;
		ofTextureAdv videoTexture;
		bool videoOn;
		
	private:
	
};