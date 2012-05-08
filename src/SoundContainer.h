#pragma once
#import <vector>
#import "Tone.h"
struct SoundEcho{
    int delay;
    float mix;
    float feedback;
};
class SoundContainer {
public:
    SoundContainer(){
        Tone::buildLUT();
        echo.delay = 200;
        echo.mix = 0.2;
        echo.feedback = 0.3;
        // calculate the length of the delay
        _delaySize = echo.delay*22.05;
        // setup the delay line, with a bunch of 0
        for(int i=0;i<_delaySize*2;i++) {
            _delayLine.push_back(0);
        }
        currentTone = 0;
        _delayIndex = 0;
        for (int i=0; i<50; i++) {
            _actives.push_back(new Tone());
        }
    };
    void processAudioAdd(float * output, int bufferSize, int nChannels);
    void addTone( float freq , int note , int octave , float pan , float duration , float volume );
private:
    SoundEcho echo;
    std::vector<float> _delayLine;
    int _delaySize, _delayIndex;
    std::vector<Tone *> _actives;
    int currentTone;
    void clearBuffer(float * output, int bufferSize, int nChannels);
};