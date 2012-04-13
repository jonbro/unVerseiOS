#pragma once
#include <math.h>

#define LUTSIZE 3600

class Tone {
private:
    float _phase;			// tone phase
    float _dPhase;		// tone phase increment
    
    int _duration;		// sound duration in samples
    int _played;		// sound samples played
    
    float _gainL;			// left gain
    float _gainR;			// right gain
    
public:
    Tone(float frec , int note, int octave , float pan , float duration, float volume) {
        _duration	= duration*22050;
        _played		= duration*22050;
        _phase		= 0.0;
        _dPhase		= frec * pow(2.0, octave + note / 12.0) / 22050.0;
        
        _gainL		= ( 1 - pan ) * volume;
        _gainR		= ( pan + 1 ) * volume;
    }
    static void buildLUT();
    bool processAudioAdd(float * output, int bufferSize, int nChannels);
    static float SinLUT[LUTSIZE];
    static float FLUTSIZE;
};