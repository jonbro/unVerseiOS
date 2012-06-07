/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXUI_ROTARY_SLIDER
#define OFXUI_ROTARY_SLIDER

#include "ofxUIWidget.h"

class ofxUIRotarySlider : public ofxUIWidget
{
public:    
    ofxUIRotarySlider(float x, float y, float w, float _min, float _max, float _value, string _name)
    {
		rect = new ofxUIRectangle(x,y,w,w); 
        init(w, _min, _max, _value, _name); 
    }
    
    ofxUIRotarySlider(float w, float _min, float _max, float _value, string _name)
    {
		rect = new ofxUIRectangle(0,0,w,w); 
        init(w, _min, _max, _value, _name); 
    }
    
    void init(float w, float _min, float _max, float _value, string _name)
    {
		name = _name; 				
        kind = OFX_UI_WIDGET_ROTARYSLIDER;  			
		
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, w+padding);
		paddedRect->setParent(rect); 
        
        draw_fill = true; 
        
        value = _value;                                               //the widget's value
		max = _max; 
		min = _min; 
        
		if(value > max)
		{
			value = max; 
		}
		if(value < min)
		{
			value = min; 
		}
        
        outerRadius = rect->getWidth()*.5; 
        innerRadius = rect->getWidth()*.25;         
		
		value = ofMap(value, min, max, 0.0, 1.0, true); 
        
        label = new ofxUILabel(0,w+padding,(name+" LABEL"), (name + ": " + ofToString(getScaledValue(),2)), OFX_UI_FONT_SMALL); 		
		label->setParent(label); 
		label->setRectParent(rect); 		
        
		increment = 0.01;         
    }
    
    void draw()
    {
        ofPushStyle(); 
        
        ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
        if(draw_back)
        {
            ofFill(); 
            ofSetColor(color_back); 
            drawArcStrip(1.0); 
        }
        
        if(draw_fill)
        {			
            ofFill(); 
            ofSetColor(color_fill); 
            drawArcStrip(value); 
        }
        
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
            drawArcStrip(value); 
        }        
        
        if(draw_outline)
        {
            ofNoFill();
            ofSetColor(color_outline); 
            ofSetLineWidth(2.0);
            drawArcStrip(1.0); 
            ofSetLineWidth(1.0);            
        }
        
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofSetColor(color_outline_highlight); 
            ofSetLineWidth(2.0);
            drawArcStrip(1.0); 
            ofSetLineWidth(1.0);            
        }
		
		if(draw_padded_rect)
		{
            ofNoFill();
            ofSetColor(color_outline_highlight); 
			paddedRect->draw(); 
		}		
        ofPopStyle(); 
    }
    
    
    void mouseMoved(int x, int y ) 
    {
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_OVER;         
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();         
    }
    
    void mouseDragged(int x, int y, int button) 
    {
        if(hit)
        {
            state = OFX_UI_STATE_DOWN;     
			input(x, y); 
			triggerEvent(this); 			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();     
    }
    
    void mousePressed(int x, int y, int button) 
    {
        if(rect->inside(x, y))
        {
            hit = true; 
            state = OFX_UI_STATE_DOWN;     
			input(x, y); 
			triggerEvent(this); 
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();         
    }
    
    void mouseReleased(int x, int y, int button) 
    {
        if(hit)
        {
#ifdef TARGET_OPENGLES
            state = OFX_UI_STATE_NORMAL;        
#else            
            state = OFX_UI_STATE_OVER; 
#endif 
			input(x, y); 
			triggerEvent(this); 			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;         
        }
        stateChange();    
        hit = false; 
    }
	
    void keyPressed(int key) 
    {		
		if(state == OFX_UI_STATE_OVER)
		{
			switch (key) 
			{
				case OF_KEY_RIGHT:
					setValue(getScaledValue()+increment); 
					triggerEvent(this); 
					break;
                    
				case OF_KEY_UP:
					setValue(getScaledValue()+increment); 
					triggerEvent(this); 
					break;
					
				case OF_KEY_LEFT:
					setValue(getScaledValue()-increment); 					
					triggerEvent(this); 
					break;
                    
				case OF_KEY_DOWN:
					setValue(getScaledValue()-increment); 					
					triggerEvent(this); 
					break;					
                    
				default:
					break;
			}
		}
    }
    
    void drawArcStrip(float percent)
    {
        float theta = ofMap(percent, 0, 1, 0, 360.0, true); 
        
        ofPushMatrix(); 
        ofTranslate(rect->getX(),rect->getY()); 
        
        ofBeginShape(); 

        {
            float x = sin(-ofDegToRad(0)); 
            float y = cos(-ofDegToRad(0));         
            ofVertex(center.x+outerRadius*x,center.y+outerRadius*y); 
        }
        
        for(int i = 0; i <= theta; i+=10)
        {
            float x = sin(-ofDegToRad(i)); 
            float y = cos(-ofDegToRad(i)); 
            
            ofVertex(center.x+outerRadius*x,center.y+outerRadius*y); 
        }
        
        {
            float x = sin(-ofDegToRad(theta)); 
            float y = cos(-ofDegToRad(theta));         
            ofVertex(center.x+outerRadius*x,center.y+outerRadius*y); 
            ofVertex(center.x+innerRadius*x,center.y+innerRadius*y); 
        }
        
        for(int i = theta; i >= 0; i-=10)
        {
            float x = sin(-ofDegToRad(i)); 
            float y = cos(-ofDegToRad(i)); 
            
            ofVertex(center.x+innerRadius*x,center.y+innerRadius*y); 
        }
        
        {
            float x = sin(-ofDegToRad(0)); 
            float y = cos(-ofDegToRad(0));         
            ofVertex(center.x+innerRadius*x,center.y+innerRadius*y); 
        }
                
        ofEndShape(); 
        ofPopMatrix();         
    }
    
    void setIncrement(float _increment)
	{
		increment = _increment; 
	}
    
	void input(float x, float y)
	{
        hitPoint = ofPoint(x,y);         
        ofVec2f mappedHitPoint = hitPoint; 
        mappedHitPoint -= ofVec2f(rect->getX()+center.x, rect->getY()+center.y);         
        
        ofVec2f cVector = center-homePoint;                 
        value = ofMap(cVector.angle(mappedHitPoint), -180, 180, 0, 1.0, true); 
        
        if(value > 1.0)
        {
            value = 1.0;
        }
        else if(value < 0.0)
        {
            value = 0.0;
        }        
        
		updateLabel(); 
	}
    
	void updateLabel()
	{
        label->setLabel(name + ": " + ofToString(getScaledValue(),2)); 		
	}
	
    void stateChange()
    {
        if(value > 0) 
        {
            draw_fill = true; 
        }
        else 
        {
            draw_fill = false; 
        }
        
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_fill_highlight = false;             
                draw_outline_highlight = false;             
				label->unfocus(); 				
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = true;    
				label->unfocus(); 
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_fill_highlight = true;            
                draw_outline_highlight = true;             
				label->focus(); 				
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = false;
				label->unfocus(); 				
            }
                break;            
                
            default:
                break;
        }        
    }

	void setValue(float _value)
	{
		value = ofMap(_value, min, max, 0.0, 1.0, true);		
		updateLabel(); 		
	}
    
	float getValue()
	{
		return value; 
	}
	
	float getScaledValue()
	{
		return ofMap(value, 0.0, 1.0, min, max, true); 
	}
    
	ofxUILabel *getLabel()
	{
		return label; 
	}
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
		paddedRect->height += label->getPaddingRect()->height; 
        if(label->getPaddingRect()->width+padding*2.0 > paddedRect->width)
        {
            paddedRect->width = label->getPaddingRect()->width;         
        }
        center = ofPoint(rect->getWidth()*.5, rect->getHeight()*.5);   
        homePoint = ofPoint(rect->getWidth()*.5, rect->getHeight());   
	}	
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	float value, increment; 
	float max, min; 
	ofxUILabel *label; 
    ofPoint center; 
    ofPoint hitPoint; 
    ofPoint homePoint; 
    float outerRadius, innerRadius; 
    
}; 

#endif
