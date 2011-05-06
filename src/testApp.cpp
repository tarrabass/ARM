/**
 
 Pour utiliser:
 
 - dessiner des traits
 - pour les éditer, appuye sur 'e' pour entrer dans le mode édition (rappuyer sur 'e' pour sortir du mode édition)
 - les flèches haut ou bas pour changer le trait à éditer
 - les flèches gauche ou droit pour changer le point du trait à éditer
 - pour supprimer un trait faut appuyer sur 'd' (dans le mode édition)
 
 
 Mapper les touches dans fonction keyPressed
 
 Utiliser effectSelection pour faire appel au draw des fonctions d'effet
 
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	useMSAA = false;
	fbo.setup(320, 240, GL_RGBA);
	noise = new Perlin(1,1.0,1.0, time(NULL));
	/*
	shader.setup("proj.vs", "proj.fs");
	shader.begin();
	shader.setUniform1i("tex0", 0);
	shader.setUniform1i("tex1", 1);
	shader.end();
	 */
	/*
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 */
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	editMode = false;
	curLineEdit = 0;
	curPointEdit = 0;
	curQuadEdit = 0;
	curEffect = 0;
	curEffectQuad = 0;
	quadMode = false;
	createMode = false;
	///// Sound Analyse /////
	numBands = 256;
	ofSoundStreamSetup(0,2,this, 44100, numBands, 4);	
	left = new float[numBands];
	myDiv = 10;
	////////////////////////	
}

//--------------------------------------------------------------
void testApp::update(){
	float totalFFT = 0;
	for(int i=0; i<numBands; i++){
		//		totalFFT += fftList[i]*50;
		totalFFT += left[i]*10;
	}
	averFFT = totalFFT / numBands;
	int soundVelocity =  abs((int)(averFFT*100));
	float soundVelocityVoulu = ((float)soundVelocity/100);
	float diff = soundVelocityVoulu - myDiv;
	myDiv += diff / 10;
	
	//update film
	for(int i=0; i<quads.size(); i++){
		quads[i].idleMovie();
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	
	int taille = 400;
	/*
	 for (int i=1; i<5; i++) {
	 ofRect(i*50,i*50,taille-(i*100),taille-i*100);
	 
	 }
	 */

	fbo.begin();
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	switch (curEffectQuad) {
		case 0:
			drawSimpleQuad();
			break;
			
		case 1:
				drawQuadSquareEffect();
			break;
		case 2:
			drawQuadVolumeEffect();
			break;
			
		default:
			break;
	}

	fbo.end();

	/*glVertex3f(i*10,i*10,0.0);	
	 glVertex3f(taillew-(i*20), i*10,0.0);
	 glVertex3f( taillew-(i*20),  tailleh-i*20,  0.0);	
	 glVertex3f(0.0, tailleh-i*20,  0.0);
	 */
	glEnd();
	if(!editMode && createMode){
		//Affiche l'effect choisi.
		curLine.draw();
		curQuad.draw(fbo,shader);
	}
	
	effectSelection();
}

//// test for FBO 

void testApp::drawQuadVolumeEffect() {
	float top = 240 - myDiv*60;
	ofFill();
	ofRect(0, top, 320, 240-top);
	
	
}

void testApp::drawSimpleQuad() {
ofDisableAlphaBlending();
ofSetColor(255, 255, 255);
ofNoFill();
ofBeginShape();
ofVertex(1,1);
ofVertex(320, 1);
ofVertex(320, 240);
ofVertex(1, 240);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(1,1,0);	
	glVertex3f(320,1,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(320,1,0);	
	glVertex3f(320,240,0);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(320,240,0);
	glVertex3f(1,240,0);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(1,240,0);
	glVertex3f(1,1,0);
	glEnd();
	
ofEndShape(true);
}


void testApp::drawQuadSquareEffect() {
	
	glEnable( GL_LINE_SMOOTH );
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	// Enable Blending
	glEnable(GL_BLEND);
	// Specifies pixel arithmetic
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glPushMatrix();
	int taillew = 320;
	int tailleh = 240;
	int nbIteration = 1+(int)myDiv*4;
	float simplexNoiseX1;
	float simplexNoiseY1;
	float simplexNoiseX2;
	float simplexNoiseY2;
	float div = 10.0;
	int posx1;
	int posy1;
	int posx2;
	int posy2;
	for (int i=0; i<nbIteration; i++) {		
	glLineWidth(2.0);
	glBegin(GL_LINES);
		 posx1 = i*10+1;
		 posy1 = i*10+1;
		 posx2 = taillew-(i*10);
		 posy2 = i*10+1;
		simplexNoiseX1 = (noise->noise3(((float)posx1)/div,(float)posy1/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseY1 = (noise->noise3(((float)posy1)/div,(float)posx1/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseX2 = (noise->noise3(((float)posx2)/div,(float)posy2/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseY2 = (noise->noise3(((float)posy2)/div,(float)posx2/div,ofGetFrameNum()/3))*myDiv*50;	
	glVertex3f(posx1 + simplexNoiseX1,posy1 + simplexNoiseY1,simplexNoiseX1);	
	glVertex3f(posx2 + simplexNoiseX2,posy2 + simplexNoiseY2,simplexNoiseX2);
	glEnd();
	glBegin(GL_LINES);
		
		posx1 = taillew-(i*10);
		posy1 = i*10+1;
		posx2 = taillew-(i*10);
		posy2 = tailleh-i*10;
		
		simplexNoiseX1 = (noise->noise3(((float)posx1)/div,(float)posy1/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseY1 = (noise->noise3(((float)posy1)/div,(float)posx1/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseX2 = (noise->noise3(((float)posx2)/div,(float)posy2/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseY2 = (noise->noise3(((float)posy2)/div,(float)posx2/div,ofGetFrameNum()/3))*myDiv*50;
		
		glVertex3f(posx1 + simplexNoiseX1,posy1 + simplexNoiseY1,simplexNoiseX1);	
		glVertex3f(posx2 + simplexNoiseX2,posy2 + simplexNoiseY2,simplexNoiseX2);
	glEnd();
	glBegin(GL_LINES);
		
		posx1 = taillew-(i*10);
		posy1 = tailleh-i*10;
		posx2 = i*10+1;
		posy2 = tailleh-i*10;
		
		simplexNoiseX1 = (noise->noise3(((float)posx1)/div,(float)posy1/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseY1 = (noise->noise3(((float)posy1)/div,(float)posx1/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseX2 = (noise->noise3(((float)posx2)/div,(float)posy2/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseY2 = (noise->noise3(((float)posy2)/div,(float)posx2/div,ofGetFrameNum()/3))*myDiv*50;
		
		glVertex3f(posx1 + simplexNoiseX1,posy1 + simplexNoiseY1,simplexNoiseX1);	
		glVertex3f(posx2 + simplexNoiseX2,posy2 + simplexNoiseY2,simplexNoiseX2);

	glEnd();
	glBegin(GL_LINES);
		
		posx1 = i*10+1;
		posy1 = tailleh-i*10;
		posx2 = i*10+1;
		posy2 = i*10+1;
		
		simplexNoiseX1 = (noise->noise3(((float)posx1)/div,(float)posy1/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseY1 = (noise->noise3(((float)posy1)/div,(float)posx1/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseX2 = (noise->noise3(((float)posx2)/div,(float)posy2/div,ofGetFrameNum()/3))*myDiv*50;
		simplexNoiseY2 = (noise->noise3(((float)posy2)/div,(float)posx2/div,ofGetFrameNum()/3))*myDiv*50;
		
		glVertex3f(posx1 + simplexNoiseX1,posy1 + simplexNoiseY1,0.0);	
		glVertex3f(posx2 + simplexNoiseX2,posy2 + simplexNoiseY2,0.0);
		

	glEnd();

	
	ofNoFill();

		//ofRect(i*10,i*10,taillew-(i*20),tailleh-i*20);
	
	}
	glPopMatrix();

}




//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == OF_KEY_UP && editMode){
		if(quadMode){
			curQuadEdit++;
			if(curQuadEdit == quads.size()){
				curQuadEdit = 0;
			}
		}
		else{
			curLineEdit++;
			if(curLineEdit == lines.size()){
				curLineEdit = 0;
			}
		}
	}
	else if(key == OF_KEY_DOWN && editMode){
		if(quadMode){
			curQuadEdit--;
			if(curQuadEdit == -1){
				curQuadEdit = quads.size()-1;
			}
		}
		else{
			curLineEdit--;
			if(curLineEdit == -1){
				curLineEdit = lines.size()-1;
			}
		}
	}
	else if(key == OF_KEY_RIGHT && editMode){
		if(quadMode){
			curPointEdit++;
			if(curPointEdit == 4){
				curPointEdit = 0;
			}
		}
		else{
			curPointEdit = 1;
		}
	}
	else if(key == OF_KEY_LEFT && editMode){
		if(quadMode){
			curPointEdit--;
			if(curPointEdit == -1){
				curPointEdit = 3;
			}
		}
		else{
			curPointEdit = 0;
		}
	}
	else if(key == 'e'){
		if (editMode){
			editMode = false;
			curLine.x1 = 0;
			curLine.x2 = 0;
			curLine.y1 = 0;
			curLine.y2 = 0;
		}
		else{
			editMode = true;
			curLineEdit = 0;
			curPointEdit = 0;
			curQuadEdit = 0;
			
			//Repasse en mode sans effets
			curEffect = 0;
		}
	}
	else if(key == 'd'){
		if(editMode){
			if(quadMode){
				if(curQuadEdit == quads.size()){
					curQuadEdit--;
				}
			}
			else{
				lines.erase(lines.begin() + curLineEdit);
				if(curLineEdit == lines.size()){
					curLineEdit--;
				}
			}
		}
	}
	else if(key == '0'){
		curEffect = 0;
	}
	else if(key == 'q'){
		if(quadMode){
			quadMode = false;
		}
		else{
			quadMode = true;
		}
	}
	else if(key == 'v'){
		std::stringstream ss;
		ss << curQuadEdit;
		string fileName = ss.str() + ".mov";
		
		ofVideoPlayer* tmp = new ofVideoPlayer();
		videos.push_back(tmp);
		videos.at(videos.size()-1)->loadMovie(fileName);
		videos.at(videos.size()-1)->play();
		
		quads[curQuadEdit].loadMovie(videos.at(videos.size()-1));
	}
	//Ajouter les autres effets ici en mappant d'autres touches
	switch (key) {
		case '1':
			//Variable pour dire quel effets est sélectionné
			curEffect = 1;
			//Applique l'effet sur la liste des vecteurs
			ef1.apply(lines);
			break;
		case '2':
			//Variable pour dire quel effets est sélectionné
			curEffect = 2;
			//Applique l'effet sur la liste des vecteurs
			ef2.apply(lines);
			break;
		case '3':
			curEffect = 3;
			ef3.apply(lines);
			break;
			
		case '4':
			curEffect = 4;
			ef4.apply(lines);
			break;
			
			
		case 'y':
			curEffectQuad = 0;
			break;
			
		case 'x':
			curEffectQuad = 1;
			break;
			
		case 'c':
			curEffectQuad = 2;
			break;
			

		case 'f':
			bFullscreen = !bFullscreen;
			
			if(!bFullscreen){
				ofSetWindowShape(1024,768);
				ofSetFullscreen(false);
				// figure out how to put the window in the center:
				
				ofSetWindowPosition(0, 0);
			} else if(bFullscreen == 1){
				
				ofSetFullscreen(true);
				//screenW-=200;
				ofSetWindowPosition(1024, 768);
				
			}
			break;
			
		case 'p':
			
			if(defromPerlin){
				
				defromPerlin = false;
				
			}else{
			
				defromPerlin = true;
			}
				break;
			}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(!editMode){
		if(quadMode){
			curQuad.updateP2(mouseX, curQuad.y1);
			curQuad.updateP3(mouseX, mouseY);
			curQuad.updateP4(curQuad.x1, mouseY);
		}
		else{
			curLine.updateP2(mouseX, mouseY);
		}
	}
	else{
		if(quadMode){
			if(curPointEdit == 0){
				quads[curQuadEdit].updateP1(mouseX, mouseY);
			}
			else if(curPointEdit == 1){
				quads[curQuadEdit].updateP2(mouseX, mouseY);
			}
			else if(curPointEdit == 2){
				quads[curQuadEdit].updateP3(mouseX, mouseY);
			}
			else{
				quads[curQuadEdit].updateP4(mouseX, mouseY);
			}
		}
		else{
			if(curPointEdit == 0){
				lines[curLineEdit].updateP1(mouseX, mouseY);
			}
			else{
				lines[curLineEdit].updateP2(mouseX, mouseY);
			}
		}
	}

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!editMode){
		createMode = true;
		if(quadMode){
			curQuad.create(mouseX, mouseY);
			curQuad.videoOn = false;
		}
		else{
			curLine.create(mouseX, mouseY);
		}
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(!editMode){
		createMode = false;
		if(quadMode){
			if((curQuad.x1 != curQuad.x2) || (curQuad.y1 != curQuad.y2)){
				quads.push_back(curQuad);
			}
		}
		else{
			if((curLine.x1 != curLine.x2) || (curLine.y1 != curLine.y2)){
				lines.push_back(curLine);
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

/*
	Effect: ajouter les autres effets ici avec le case
 */
void testApp::effectSelection(){
	switch (curEffect) {
		//Pas d'effets, affiche les lignes normales

		case 0:
			for(int i=0; i<lines.size(); i++){
				if(i == curLineEdit && editMode && !quadMode){
					lines[i].draw();
					lines[i].drawPoint(curPointEdit);
				}
				else {
					lines[i].draw();
				}
			}
			
			//Quad
			drawQuads();
			break;
		//Effet 1
		case 1:
			ef1.draw(myDiv,defromPerlin);
			drawQuads();
			break;
		case 2:
			ef2.draw(myDiv,defromPerlin);
			drawQuads();
			break;
		case 3:
			ef3.draw(myDiv,defromPerlin,left);
			drawQuads();
			break;
		case 4:
			ef4.draw(myDiv,defromPerlin,left);
			drawQuads();
			break;
		default:
			break;
	}
}


void testApp::drawQuads(){
	for(int i=0; i<quads.size(); i++){
		if(i == curQuadEdit && editMode && quadMode){
			quads[i].draw(fbo,shader);
			quads[i].drawPoint(curPointEdit);
		}
		else{
			quads[i].draw(fbo,shader);
		}
	}
}


void testApp::audioReceived(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
	}
}
