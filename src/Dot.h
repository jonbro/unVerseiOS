#pragma once
#include "ofMain.h"
#include "ofxShapeBatchRenderer.h"
class Dot{
public:
    Dot(int x, int y){
        maxSpeed = 10;
        friction = 0.992;
        pos.set(x, y);
        vel.set((ofRandom(maxSpeed)-maxSpeed)*0.5, (ofRandom(maxSpeed)-maxSpeed)*0.5);
        wrapWidth = 320;
        wrapHeight = 480;
        screenMult.set(ofGetWidth()/(float)wrapWidth, ofGetHeight()/(float)wrapHeight);
        cout << "screen width: " << ofGetWidth() << endl;
    };
    void update(float timeMultiplier);
    void draw(ofxShapeBatchRenderer *shapes);
    void slowDown();
    void wrapToScreen();
    ofVec2f pos, last_pos, vel, timeVel, screenMult;
    int wrapWidth, wrapHeight;
    float maxSpeed, friction;
};