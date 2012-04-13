#pragma once
#include "ofMain.h"
#include "ofxShapeBatchRenderer.h"
class Dot{
public:
    Dot(int x, int y){
        maxSpeed = 10;
        friction = 0.995;
        pos.set(x, y);
        vel.set((ofRandom(maxSpeed)-maxSpeed)*0.5, (ofRandom(maxSpeed)-maxSpeed)*0.5);
    };
    void update();
    void draw(ofxShapeBatchRenderer *shapes);
    void slowDown();
    void wrapToScreen();
    ofVec2f pos, last_pos, vel;
    float maxSpeed, friction;
};