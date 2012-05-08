#pragma once
#include <vector>
#include "ofPoint.h"
#include "ofxShapeBatchRenderer.h"
class TitleScreen{
public:
    TitleScreen();
    void fixPoints();
    bool assignPoint(ofPoint *point);
    void draw(ofxShapeBatchRenderer *shapeBatch);
    vector< vector< ofPoint* > > letters;
    ofPoint offset, screenMult, screenDrawMult, offsetTap, screenMultTap;
};