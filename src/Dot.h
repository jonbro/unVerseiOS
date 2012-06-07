#pragma once
#include "ofMain.h"
#include "ofxShapeBatchRenderer.h"
class Dot{
public:
    Dot(int x, int y){
        maxSpeed = 10;
        friction = 0.985;
        pos.set(x, y);
        vel.set(0,0);
        wrapWidth = 320;
        wrapHeight = 480;
        screenMult.set(ofGetWidth()/(float)wrapWidth, ofGetHeight()/(float)wrapHeight);
        drawing = false;
    };
    void update(float timeMultiplier);
    void draw(ofxShapeBatchRenderer *shapes);
    void slowDown();
    void wrapToScreen();
    ofPoint pos, last_pos, vel, timeVel, screenMult;
    int wrapWidth, wrapHeight;
    bool drawing;
    float maxSpeed, friction;
};