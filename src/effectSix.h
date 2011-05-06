

#include "ofMain.h"
#include "mdLine.h"
#include "perlin.h"
#include "MSAInterpolator.h"
#include "ofxVectorMath.h"


class effectSix{
	
	
public:
	
	MSA::Interpolator2D				spline2D;
	MSA::Interpolator3D				spline3D;
	
	MSA::InterpolationType			interpolationType;
	bool							useLength;
	
	float							currentRot;
	bool							rotateView;
	float						    spherePosPerc;
	float							sphereSpeed;
	void apply(vector <mdLine> lns);
	void builtNextBranch();
	void draw(float sound,bool defromPerlin,float left[256]);
	vector<MSA::Vec2f>trails;
	
private:
	int period;
	int offcetTime;
	int indexLine;
	int indexBranch;
	vector <mdLine> lines;
	Perlin *noise;
	float posx1Voulu;
	float posy1Voulu;
	float posx2Voulu;
	float posy2Voulu;
	
};