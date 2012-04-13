#include "SoundContainer.h"
int readIndex;
float sourceLeft, sourceRight, delayLeft, delayRight;
void SoundContainer::processAudioAdd(float * output, int bufferSize, int nChannels) {
    clearBuffer(output, bufferSize, nChannels);
    int n = _actives.size();
    while( --n > -1 ) {
        if( _actives[n]->processAudioAdd(output, bufferSize, nChannels)){
            delete (_actives[n]);
            _actives.erase(_actives.begin()+n);
        }
    }
    for (int i=0; i<bufferSize; i++) {
        sourceLeft = output[i*2];
        sourceRight = output[i*2+1];
        // process the echo
        // calculate delay
        readIndex = _delayIndex - _delaySize + 1;
        if( readIndex < 0 )	readIndex += _delaySize;
        
        // get delay
        delayLeft	= _delayLine[readIndex*2];
        delayRight	= _delayLine[readIndex*2+1];
        
        
        // add delay
        _delayLine[_delayIndex*2]	= sourceLeft	+ delayRight	* echo.feedback;
        _delayLine[_delayIndex*2+1]	= sourceRight	+ delayLeft		* echo.feedback;
        
        
        // move delay pointer
        if( ++_delayIndex == _delaySize )
            _delayIndex = 0;
        
        
        // write sound
        output[i*2] =  sourceLeft	+ echo.mix * delayLeft;
        output[i*2+1] = sourceRight	+ echo.mix * delayRight;
    }

}
void SoundContainer::clearBuffer(float * output, int bufferSize, int nChannels) {
    for( int n = 0 ; n < bufferSize ; n++ )
    {
        for (int c = 0; c<nChannels; c++)
        {
            output[n*2]		= 0;
            output[n*2+1]	= 0;
        }
    }

}
void SoundContainer::addTone( float freq , int note , int octave , float pan , float duration , float volume )
{
    Tone *tone = new Tone(freq , note , octave , pan , duration , volume/(64*duration*duration));
    _actives.push_back(tone);
}