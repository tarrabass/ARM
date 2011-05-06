

#include "ofMain.h"
#include "mdLine.h"
#include "perlin.h"
#include "branch.h"

class effectFive{
	
	
public:
	void apply(vector <mdLine> lns);
	void builtNextBranch();
	void draw(float sound,bool defromPerlin,float left[256]);
	
private:
	int period;
	int offcetTime;
	int indexLine;
	int indexBranch;
	vector <branch> branches;
	vector <mdLine> lines;
	Perlin *noise;
	float posx1Voulu;
	float posy1Voulu;
	float posx2Voulu;
	float posy2Voulu;
	
};