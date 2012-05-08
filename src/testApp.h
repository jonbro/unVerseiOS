#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "Dot.h"
#include "SoundContainer.h"
#include <vector>
#include "ofxUI.h"
#include "ofxShapeBatchRenderer.h"
#include "TitleScreen.h"

#define NUM_DOTS 100
enum appState{
    ONTITLE,
    ADDINGDOTS,
    MAINSTATE
};
class testApp : public ofxiPhoneApp{
    
    public:
        void setScale(int scale);
        void setup();
        void update();
        void draw();
        void drawDots(float timeMultiplier);
        void audioOut(float * output, int bufferSize, int nChannels);

        void exit();
    
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);
	
        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
        
        void guiEvent(ofxUIEventArgs &e);
        TitleScreen *title;
    
        ofFbo nonFloatingPointFbo_GL_RGBA;
        Dot *dots[NUM_DOTS];
        int col[NUM_DOTS*NUM_DOTS];
        ofVec2f lastPos[15];
        ofPoint screenMult;
        bool retina;
        SoundContainer container;
        vector<int> scale;
        int lastDrag;
        int currentScale, numDots;
        float collisionDistance, mDist;
        float lastTime, currentTime, timeMultiplier;
        ofImage titleImg;
        appState state;
        ofxUICanvas *gui;
        ofxShapeBatchRenderer *shapeBatch;
        float addRate;
};


