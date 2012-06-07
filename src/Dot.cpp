#include "Dot.h"

void Dot::update(float timeMultiplier){
    last_pos.set(pos);
    timeVel.set(vel);
    timeVel *= timeMultiplier;
    pos += timeVel;
}
void Dot::draw(ofxShapeBatchRenderer *shapes){
    if(drawing){
        ofSetColor(255, 255, 255);
        shapes->addLine(last_pos*screenMult, pos*screenMult);
        wrapToScreen();
    }
}
void Dot::wrapToScreen(){
    if(pos.x>wrapWidth){
        pos.x = 0;
    }else if(pos.x<0){
        pos.x = wrapWidth;
    }
    if(pos.y>wrapHeight){
        pos.y = 0;
    }else if(pos.y<0){
        pos.y = wrapHeight;
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