#include "testApp.h"
// chord 1
// 0, 3, 8
// 0, 3, 7

//--------------------------------------------------------------
void testApp::setup(){	
	// register touch events
	ofRegisterTouchEvents(this);
    shapeBatch = new ofxShapeBatchRenderer(SBR_LINE, 1000, 1);
    shapeBatch->setColor(255, 255, 255);
    title = new TitleScreen();
    int wrapWidth = 320;
    int wrapHeight = 480;
    screenMult.set(ofGetWidth()/(float)wrapWidth, ofGetHeight()/(float)wrapHeight);
    int swidth = ofGetWidth();
    ofFbo::Settings s;
    s.width				= 1024;
    s.height			= 1024;
    
    if(swidth == 320){
        titleImg.loadImage("UNVERSE_1.png");
    }else if(swidth == 640){
        titleImg.loadImage("UNVERSE_0.png");
    }else if(swidth == 768){
        titleImg.loadImage("UNVERSE_2.png");
    }else{
        titleImg.loadImage("UNVERSE_3.png");
        s.height = 2048;
        s.width = 2048;
    }
    
    state = ONTITLE;
    
    lastTime = 0;
    s.internalformat = GL_RGBA;
	nonFloatingPointFbo_GL_RGBA.allocate(s);
    nonFloatingPointFbo_GL_RGBA.begin();
	ofClear(255,255,255, 0);
    nonFloatingPointFbo_GL_RGBA.end();

    ofEnableAlphaBlending();
	ofSetFrameRate(60);
    for (int i=0; i<NUM_DOTS; i++) {
        dots[i] = new Dot(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        for (int j=i+1; j<NUM_DOTS; j++) {
            col[i*NUM_DOTS+j] = 0;
        }
    }
    setScale(0);
    lastDrag = 0;
    currentScale = 0;
    
    
    // set some constants
    collisionDistance = 33.16;
    mDist = 120.7;
    numDots = 46;
    // setup the ui
    int width = 304;
    int height = 40;
    if(retina)
    {
        width *= 2;
        height *= 2;
    }
    if(swidth > 768){
        width *= 2;
        height *= 2;
    }
    gui = new ofxUICanvas(0,0,ofGetWidth(),ofGetHeight());		//ofxUICanvas(float x, float y, float width, float height)		
    gui->addWidgetDown(new ofxUILabel("UNVERSE", OFX_UI_FONT_LARGE)); 
    gui->addWidgetDown(new ofxUISlider(width,height,0.0,60,collisionDistance,"COLLISION DISTANCE")); 
    gui->addWidgetDown(new ofxUISlider(width,height,50,200,mDist,"TOUCH DISTANCE")); 
    gui->addWidgetDown(new ofxUISlider(width,height,0.0,30,12,"DOT MAXSPEED")); 
    gui->addWidgetDown(new ofxUISlider(width,height,0.0,100,numDots,"NUM DOTS")); 
    //gui->addWidgetDown(new ofxUISlider(width,height,0.99,1.0,0.995,"FRICTION")); 
    gui->disable();
    
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent); 
    gui->loadSettings("GUI/guiSettings.xml"); 

    ofSoundStreamSetup(2, 0, this, 22050, 512, 4);
    ofSoundStreamStart();
    //ofSetFrameRate(60);
    addRate = 0.35;
}

void testApp::setScale(int _scale) {
    cout << "changing scales" << endl;
    // clear the scale
    while (!scale.empty())
    {
        scale.pop_back();
    }
    // load up the scale
    for (int o=0; o<3; o++) {
        scale.push_back(0+o*12);
        scale.push_back(3+o*12);
        if (_scale == 0) {
            scale.push_back(8+o*12);
        }else{
            scale.push_back(7+o*12);
        }
    }

}
//--------------------------------------------------------------
void testApp::update(){
    if(state == ADDINGDOTS){
        if(addRate > 0){
            addRate -= ofGetElapsedTimef();
        }else{
            // find the first unassigned dot, and assign it
            for (int i = 0; i<NUM_DOTS; i++) {
                if(!dots[i]->drawing){
                    Dot *v = dots[i];
                    if(!title->assignPoint(&(v->pos))){
                        state = MAINSTATE;
                    }
                    v->drawing = true;
                    v->vel.set(-ofRandom(v->maxSpeed)*0.25-v->maxSpeed*0.25, -ofRandom(v->maxSpeed)*0.25-v->maxSpeed*0.25);
                    float xd = v->pos.x;
                    float yd = v->pos.y;
                    int note = fmax(0, fmin(scale.size()*(1.0-yd/ofGetHeight()), scale.size()));

                    container.addTone(440, scale[note], -1, 2.0*xd/ofGetWidth()-1, 1, 0.5);
                    addRate = 0.35;
                    break;
                }
            }
        }
    }
}
void testApp::draw()
{
    currentTime = ofGetElapsedTimef();
    timeMultiplier = 60.0*(ofGetElapsedTimef()-lastTime);
    lastTime = currentTime;
    // clear the background    
    ofSetColor(0, 0, 0, 255);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    // BEGIN FBO
    nonFloatingPointFbo_GL_RGBA.begin();
    // clear out the fbo a bit
    ofSetColor(0, 0, 0, 10.0*timeMultiplier);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 255, 255);
    shapeBatch->clear();
    if(state == ONTITLE){
        titleImg.draw(0, 0);
    }
    if(state == ONTITLE || state == ADDINGDOTS){
        title->draw(shapeBatch);
    }
    drawDots(timeMultiplier);
    shapeBatch->draw();
    nonFloatingPointFbo_GL_RGBA.end();
	// END FBO
    ofSetColor(255, 255, 255);  // "color" for the fbo
    nonFloatingPointFbo_GL_RGBA.draw(0, 0); // 420px from the left, 10px from the top
    if(gui->isEnabled()){
        string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2);
        ofDrawBitmapString(fpsStr, 0,ofGetHeight()-10);
    }
}
//--------------------------------------------------------------
void testApp::drawDots(float timeMultiplier){
    // handle drawing the lines
    float a = 0.5;
    int lineCount = 0;
    bool played = false;
    // first update the positions
    for (int i=0; i<numDots; i++) {
        dots[i]->update(timeMultiplier);
    }
    // then handle the collisions
    for (int i=0; i<numDots; i++) {
        Dot *v1 = dots[i];
        for (int j=i+1; j<numDots; j++) {
            lineCount++;
            Dot *v2 = dots[j];
			float xd = v1->pos.x - v2->pos.x;
            float yd = v1->pos.y - v2->pos.y;
            float d = v1->pos.distance(v2->pos);
            if(v1->drawing && v2->drawing && d < collisionDistance && d != 0)
            {
                // draw a line between the dots, and push the dots away from one another
                v1->vel.x = v1->vel.x + a*xd/d;
                v1->vel.y = v1->vel.y + a*yd/d;
                v2->vel.x = v2->vel.x - a*xd/d;
                v2->vel.y = v2->vel.y - a*yd/d;   
                if(col[lineCount]==0){
                    if(!played){
                        xd = (v1->pos.x+v2->pos.x)*.5;
                        yd = (v1->pos.y+v2->pos.y)*.5;
                        int note = fmax(0, fmin(scale.size()*(1.0-yd/480.0), scale.size()));
                        container.addTone(440, scale[note], -1, 2.0*xd/320.0-1, 1, fmin(1.0, .2+.8*(d/50.0)));
                        played = true;
                    }
                    col[lineCount] = 10;
                    shapeBatch->addLine(v1->pos*screenMult, v2->pos*screenMult);
                }
            }else if(col[lineCount]!=0){
                col[lineCount] -= 1;
            }
        }
    }
    // then handle the slowdown
    for (int i=0; i<numDots; i++) {
        dots[i]->slowDown();
    }
    // then draw
    for (int i=0; i<numDots; i++) {
        dots[i]->draw(shapeBatch);
    }
    
}
//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
    container.processAudioAdd(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void testApp::exit(){
    gui->saveSettings("GUI/guiSettings.xml");     
    delete gui; 
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    if (state == ONTITLE) {
        state = ADDINGDOTS;
    }
    if(ofGetElapsedTimeMillis()-lastDrag > 2000){
        currentScale++;
        currentScale = currentScale%2;
        setScale(currentScale);
    }
    lastDrag = ofGetElapsedTimeMillis();
    lastPos[touch.id].set(touch.x, touch.y);
    lastPos[touch.id] /= screenMult;
    if(touch.id == 2){
        gui->toggleVisible();
    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    lastDrag = ofGetElapsedTimeMillis();

    ofVec2f dist = ofVec2f(touch.x, touch.y);
    dist /= screenMult;
    ofVec2f fpos = ofVec2f(dist);
    dist -= lastPos[touch.id];
    for (int i=0; i<numDots; i++) {
        Dot *v = dots[i];
		float d = dots[i]->pos.distance(fpos);
		if (d < mDist)
        {
			v->vel.x = v->vel.x+.001*(mDist-d)*dist.x;
            v->vel.y = v->vel.y+.001*(mDist-d)*dist.y;
        }
    }

    lastPos[touch.id].set(touch.x, touch.y);
    lastPos[touch.id] /= screenMult;
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::lostFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    
}


void testApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "COLLISION DISTANCE")	
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        collisionDistance = slider->getScaledValue();
    }  
    if(e.widget->getName() == "TOUCH DISTANCE")	
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        mDist = slider->getScaledValue();
    }
    if(e.widget->getName() == "NUM DOTS")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        numDots = slider->getScaledValue();
    }
    if(e.widget->getName() == "DOT MAXSPEED")	
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        float maxSpeed = slider->getScaledValue();
        for (int i=0; i<NUM_DOTS; i++) {
            dots[i]->maxSpeed = maxSpeed;
        }
    }
    if(e.widget->getName() == "FRICTION")	
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        float friction = slider->getScaledValue();
        for (int i=0; i<NUM_DOTS; i++) {
            dots[i]->friction = friction;
        }
    }
}