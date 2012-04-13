#include "Tone.h"
#include "ofMath.h"
float one = 1.0;
float Tone::SinLUT[] = {0};
float Tone::FLUTSIZE = LUTSIZE;
bool Tone::processAudioAdd(float *output, int bufferSize, int nChannels) {
    
    float amplitude;
    float env;
    float tmp;
    
    for( int n = 0 ; n < bufferSize ; ++n )
    {
            env = _played / 10000.0;
            
            //tmp 		= ( _phase * 4.0 - 1.0 );
            _phase += _dPhase;
            _phase = modff(_phase, &tmp);
            amplitude	= SinLUT[(int)(_phase*Tone::FLUTSIZE)] * env * env * .5;
            
            
            output[n*2]		+= amplitude * _gainL;
            output[n*2+1]	+= amplitude * _gainR;
        if( --_played == 0 )
            return true;
    }
    
    return false;
    
}

void Tone::buildLUT(){
    for (int i=0; i<LUTSIZE; i++) {
        SinLUT[i] = sinf((float)i/Tone::FLUTSIZE*TWO_PI);
    }
}