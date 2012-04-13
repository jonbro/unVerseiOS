/*
 *  BrushedLine.h
 *  iPhoneEmptyExample
 *
 *  Created by Marek Bereza on 28/01/2011.
 *  Copyright 2011 Marek Bereza. All rights reserved.
 *	https://github.com/mazbox/ofxmarek/raw/master/mareklib/graphics/gl/BrushedLine.h
 */

/**
 * This class lets you draw a line with an image 
 * and it'll stretch it across the line to give 
 * you a nice smoothed stroke.
 *
 * see: http://answers.oreilly.com/topic/949-how-to-work-around-the-iphones-anti-aliasing-limitations/
 */

#pragma once

class BrushedLine {
public: 
	BrushedLine() {
		img = NULL;
		size = 10;
		
		// texcoords are always the same.
		texCoords[0] = ofVec2f(0, 1);
		texCoords[1] = ofVec2f(0, 0);
		texCoords[2] = ofVec2f(0.5, 1);
		texCoords[3] = ofVec2f(0.5, 0);
		texCoords[4] = ofVec2f(0.5, 1);
		texCoords[5] = ofVec2f(0.5, 0);
		texCoords[6] = ofVec2f(1, 1);
		texCoords[7] = ofVec2f(1, 0);
		imageBound = false;
		
	}
	void setup(ofImage *img, float size) {
		this->img = img;
		this->size = size;
	}
	
	void drawLine(ofVec2f &a, ofVec2f &b) {
		bool mustUnbind = false;
		if(!imageBound) {
			bindImage();
			mustUnbind = true;
		}
		ofVec2f E = (b - a).getNormalized() * size;
		ofVec2f N = ofVec2f(-E.y, E.x);
		ofVec2f S = -N;
		ofVec2f NE = N + E;
		ofVec2f NW = N - E;
		ofVec2f SW = -NE;
		ofVec2f SE = -NW;
		coords[0] = (a + SW);
		coords[1] = (a + NW);
		coords[2] = (a + S);
		coords[3] = (a + N);
		coords[4] = (b + S);
		coords[5] = (b + N);
		coords[6] = (b + SE);
		coords[7] = (b + NE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glVertexPointer(2, GL_FLOAT, 0, &coords[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		if(mustUnbind) unbindImage();
		
	}
	void drawLines(ofVec2f *points, int numPoints, bool close = false) {
		
		bindImage();
		for(int i = 0; i+1 < numPoints; i++) {
			ofVec2f a = points[i];
			ofVec2f b = points[i+1];
			drawLine(points[i], points[i+1]);
		}
		
		// close the loop if necessary.
		if(close) {
			drawLine(points[0], points[numPoints-1]);
		}
		unbindImage();
	}
	float size;
private:
	
	void bindImage() {
		if(!imageBound) {
			imageBound = true;
			img->getTextureReference().bind();
		}
	}
	
	void unbindImage() {
		if(imageBound) {
			img->getTextureReference().unbind();
			imageBound = false;
		}
	}
	
	bool imageBound;
	ofImage *img;
	
	ofVec2f texCoords[8];
	ofVec2f coords[8];
};

class bludLine {
public:
	static const char className[];
	static Lunar<bludLine>::RegType methods[];
	BrushedLine _line;
	bludImage *_image;
	ofVec2f a, b;
	bludLine(lua_State *L) {
		_image = Lunar<bludImage>::check(L, 1);
		int width = 4;
		if (lua_isnumber(L, 2)) {
			width = luaL_checknumber(L, 2);
		}
		_line.setup(&_image->_image,width);
	}
	int drawLine(lua_State *L) {
		a.x = luaL_checknumber(L, 1);
		a.y = luaL_checknumber(L, 2);
		b.x = luaL_checknumber(L, 3);
		b.y = luaL_checknumber(L, 4);
		_line.drawLine(a, b); return 0;
	}
	~bludLine() { printf("deleted line (%p)\n", this); }
};

const char bludLine::className[] = "bludLine";

Lunar<bludLine>::RegType bludLine::methods[] = {
	method(bludLine, drawLine),
	{0,0}
};