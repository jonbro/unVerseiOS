#include "Tone.h"
#include "ofMath.h"
float one = 1.0;
float Tone::SinLUT[] = {0};
float Tone::FLUTSIZE = LUTSIZE;
bool Tone::processAudioAdd(float *output, int bufferSize, int nChannels) {
    
    float amplitude;
    float env;
    float tmp;
    if(!playing){
        return false;
    }
    for( int n = 0 ; n < bufferSize ; ++n )
    {
        if(declick < 1.0){
            declick += 0.05;
        }
            env = _played / 22050.0;
            
            amplitude	= SinLUT[(int)(_phase*Tone::FLUTSIZE)] * env * env * .5;
            
            
            output[n*2]		+= amplitude * _gainL * declick;
            output[n*2+1]	+= amplitude * _gainR * declick;
            _phase += _dPhase;
            _phase = modff(_phase, &tmp);
        if( --_played == 0 ){
            playing = false;
            return true;
        }
    }
    
    return false;
    
}

void Tone::buildLUT(){
    for (int i=0; i<LUTSIZE; i++) {
        SinLUT[i] = sinf((float)i/((float)Tone::FLUTSIZE)*TWO_PI);
    }
}