#ifndef _TEST_APP
#define _TEST_APP
#define kFBOWidth			400
#define kFBOHeight			400


// used for screen layout
#define kPreviewWidth		400
#define kPreviewHeight		400


// auto calculated
#define kPreviewX(i)	((kPreviewWidth + 10) * i)
#define kPreviewY(i)	((kPreviewHeight + 60) * i)

#define kLabelX(i)		(kPreviewX(i) + 15)
#define kLabelY(i)		(kPreviewY(i) + kPreviewHeight + 15)

#include "ofMain.h"
#include "perlin.h"
#include "mdLine.h"
#include "mdQuad.h"
#include "effectOne.h"
#include "effectTwo.h"
#include "effectThree.h"
#include "effectFour.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		Perlin *noise;
	////fbo quad ///
	bool			useMSAA;
	ofFbo			fbo;
		ofShader shader;

	///////////////
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		bool  	bFullscreen;
	private:
		vector <mdLine> lines;
		mdLine curLine;
		bool editMode;
		bool createMode;
	
		int curLineEdit;
		int curPointEdit;
	
		bool quadMode;
		vector <mdQuad> quads;
		mdQuad curQuad;
		int curQuadEdit;
		void drawQuadSquareEffect();
	void drawQuadVolumeEffect();
	void drawSimpleQuad();
		void	drawQuads();
		vector<ofVideoPlayer*> videos;
		
		int curEffect;
	int curEffectQuad;
		effectOne ef1;
		effectTwo ef2;
		effectThree ef3;
		effectFour ef4;
		void effectSelection();
	
	
		float * left;
		float myDiv;
		int numBands;
		float averFFT;
		void audioReceived(float * input, int bufferSize, int nChannels);
		bool defromPerlin;
};

#endif
