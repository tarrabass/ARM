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
#include "ofxTween.h"

class effectFour{

	
	public:
		void apply(vector <mdLine> lns);
	void draw(float sound,bool defromPerlin,float left[256]);
	void initTween();
		
	private:
		vector <mdLine> lines;
		Perlin *noise;
	
	float posx1Voulu;
	float posy1Voulu;
	float posx2Voulu;
	float posy2Voulu;

	
	     float length_float;
	ofxTween tweenback;
	ofxTween tweenbounce;
	ofxTween tweencirc;
	ofxTween tweencubic;
	ofxTween tweenelastic;
	ofxTween tweenexpo;
	ofxTween tweenlinear;
	ofxTween tweenquad;
	ofxTween tweenquart;
	ofxTween tweenquint;
	ofxTween tweensine;
	
	ofxTween multitween;
	
	ofxEasingBack 	easingback;
	ofxEasingBounce 	easingbounce;
	ofxEasingCirc 	easingcirc;
	ofxEasingCubic 	easingcubic;
	ofxEasingElastic easingelastic;
	ofxEasingExpo 	easingexpo;
	ofxEasingLinear 	easinglinear;
	ofxEasingQuad 	easingquad;
	ofxEasingQuart 	easingquart;
	ofxEasingQuint 	easingquint;
	ofxEasingSine	easingsine;

};