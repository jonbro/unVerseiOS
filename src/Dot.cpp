#include "Dot.h"

void Dot::update(){
    last_pos.set(pos);
    pos += vel;
}
void Dot::draw(ofxShapeBatchRenderer *shapes){
    ofSetColor(255, 255, 255);
    shapes->addLine(last_pos, pos);
    wrapToScreen();
}
void Dot::wrapToScreen(){
    if(pos.x>ofGetWidth()){
        pos.x = 0;
    }else if(pos.x<0){
        pos.x = ofGetWidth();
    }
    if(pos.y>ofGetHeight()){
        pos.y = 0;
    }else if(pos.y<0){
        pos.y = ofGetHeight();
    }
}
void Dot::slowDown()
{
    float s = maxSpeed;
	float d = vel.length();
	if(d > s)
    {
		vel.x = s*vel.x/d;
        vel.y = s*vel.y/d;        
    }
	vel *= friction;
}