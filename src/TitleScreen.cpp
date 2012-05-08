#include "TitleScreen.h"

TitleScreen::TitleScreen()
{

    float wrapWidth = 320;
    float wrapHeight = 480;
    screenDrawMult.set(ofGetWidth()/(float)wrapWidth, ofGetHeight()/(float)wrapHeight);

    offset = ofPoint(82.65, 82.65);
    screenMult = ofPoint(154, 154);

    offsetTap = ofPoint(84.1, 366.9);
    screenMultTap = ofPoint(19.45, 19.45);
    
    // u
    vector<ofPoint*> a0;
    a0.push_back(new ofPoint(0,0));
    a0.push_back(new ofPoint(0,0.5092084006462035));
    a0.push_back(new ofPoint(0.1308562197092084,0.6449111470113086));
    a0.push_back(new ofPoint(0.2319870759289176,0.6449111470113086));
    a0.push_back(new ofPoint(0.3602584814216478,0.5092084006462035));
    a0.push_back(new ofPoint(0.3602584814216478,0));
    letters.push_back(a0);
    
    // n
    vector<ofPoint*> a1;
    a1.push_back(new ofPoint(0.48109854604200325,0.6449111470113086));
    a1.push_back(new ofPoint(0.48109854604200325,0));
    a1.push_back(new ofPoint(0.9951534733441034,0.6449111470113086));
    a1.push_back(new ofPoint(0.9951534733441034,0));
    letters.push_back(a1);
    
    // v
    vector<ofPoint*> a2;
    a2.push_back(new ofPoint(0.007431340872374797,0.7489499192245558));
    a2.push_back(new ofPoint(0.09693053311793215,1.0507269789983844));
    a2.push_back(new ofPoint(0.18675282714054928,0.7489499192245558));
    letters.push_back(a2);

    // e
    vector<ofPoint*> a3;
    a3.push_back(new ofPoint(0.2558966074313409,0.7489499192245558));
    a3.push_back(new ofPoint(0.39063004846526656,0.7489499192245558));
    a3.push_back(new ofPoint(0.2558966074313409,0.7489499192245558));
    a3.push_back(new ofPoint(0.2558966074313409,0.8833602584814215));
    a3.push_back(new ofPoint(0.39063004846526656,0.8833602584814215));
    a3.push_back(new ofPoint(0.2558966074313409,0.8833602584814215));
    a3.push_back(new ofPoint(0.2558966074313409,1.0507269789983844));
    a3.push_back(new ofPoint(0.39063004846526656,1.0507269789983844));
    letters.push_back(a3);
    
    // r
    vector<ofPoint*> a4;
    a4.push_back(new ofPoint(0.4484652665589661,1.0507269789983844));
    a4.push_back(new ofPoint(0.4484652665589661,0.7489499192245558));
    a4.push_back(new ofPoint(0.555735056542811,0.7489499192245558));
    a4.push_back(new ofPoint(0.5932148626817447,0.7867528271405493));
    a4.push_back(new ofPoint(0.5932148626817447,0.845557350565428));
    a4.push_back(new ofPoint(0.555735056542811,0.8833602584814215));
    a4.push_back(new ofPoint(0.4484652665589661,0.8833602584814215));
    a4.push_back(new ofPoint(0.49434571890145396,0.8833602584814215));
    a4.push_back(new ofPoint(0.5932148626817447,1.0507269789983844));
    letters.push_back(a4);
    
    // s
    vector<ofPoint*> a5;
    a5.push_back(new ofPoint(0.7964458804523424,0.7831987075928918));
    a5.push_back(new ofPoint(0.7625201938610663,0.7489499192245558));
    a5.push_back(new ofPoint(0.6882067851373183,0.7489499192245558));
    a5.push_back(new ofPoint(0.6516962843295637,0.7854604200323102));
    a5.push_back(new ofPoint(0.6516962843295637,0.8277867528271405));
    a5.push_back(new ofPoint(0.812924071082391,0.9515347334410339));
    a5.push_back(new ofPoint(0.812924071082391,1.0116316639741518));
    a5.push_back(new ofPoint(0.7738287560581584,1.0507269789983844));
    a5.push_back(new ofPoint(0.6768982229402262,1.0507269789983844));
    a5.push_back(new ofPoint(0.6374798061389338,1.0116316639741518));
    letters.push_back(a5);
    
    // e
    vector<ofPoint*> a6;
    a6.push_back(new ofPoint(0.863004846526656,0.7489499192245558));
    a6.push_back(new ofPoint(1,0.7489499192245558));
    a6.push_back(new ofPoint(0.863004846526656,0.7489499192245558));
    a6.push_back(new ofPoint(0.863004846526656,0.8833602584814215));
    a6.push_back(new ofPoint(1,0.8833602584814215));
    a6.push_back(new ofPoint(0.863004846526656,0.8833602584814215));
    a6.push_back(new ofPoint(0.863004846526656,1.0507269789983844));
    a6.push_back(new ofPoint(1,1.0507269789983844));
    letters.push_back(a6);
    
//    vector<ofPoint*> a8;
//    a8.push_back(new ofPoint(0.12082262210796917,0));
//    a8.push_back(new ofPoint(0,0.11825192802056554));
//    a8.push_back(new ofPoint(0,0.8766066838046274));
//    a8.push_back(new ofPoint(0.12082262210796917,0.9974293059125964));
//    a8.push_back(new ofPoint(0.5501285347043702,0.07969151670951158));
//    a8.push_back(new ofPoint(0.9511568123393317,0.07969151670951158));
//    a8.push_back(new ofPoint(0.7506426735218509,0.07969151670951158));
//    a8.push_back(new ofPoint(0.7506426735218509,0.8946015424164524));
//    a8.push_back(new ofPoint(0.9408740359897173,0.8946015424164524));
//    a8.push_back(new ofPoint(1.2596401028277635,0.07969151670951158));
//    a8.push_back(new ofPoint(1.5604113110539848,0.8946015424164524));
//    a8.push_back(new ofPoint(1.0437017994858613,0.6401028277634961));
//    a8.push_back(new ofPoint(1.4678663239074552,0.6401028277634961));
//    a8.push_back(new ofPoint(1.7017994858611827,0.8946015424164524));
//    a8.push_back(new ofPoint(1.7017994858611827,0.07969151670951158));
//    a8.push_back(new ofPoint(1.987146529562982,0.08226221079691518));
//    a8.push_back(new ofPoint(2.0925449871465296,0.18766066838046272));
//    a8.push_back(new ofPoint(2.0925449871465296,0.3419023136246787));
//    a8.push_back(new ofPoint(1.987146529562982,0.4498714652956298));
//    a8.push_back(new ofPoint(1.7017994858611827,0.4498714652956298));
//    a8.push_back(new ofPoint(2.5629820051413885,0.07969151670951158));
//    a8.push_back(new ofPoint(2.9640102827763495,0.07969151670951158));
//    a8.push_back(new ofPoint(2.7609254498714657,0.07969151670951158));
//    a8.push_back(new ofPoint(2.7609254498714657,0.8946015424164524));
//    a8.push_back(new ofPoint(3.190231362467866,0.07969151670951158));
//    a8.push_back(new ofPoint(3.5604113110539846,0.07969151670951158));
//    a8.push_back(new ofPoint(3.7969151670951153,0.31362467866323906));
//    a8.push_back(new ofPoint(3.7969151670951153,0.6478149100257069));
//    a8.push_back(new ofPoint(3.55012853470437,0.8946015424164524));
//    a8.push_back(new ofPoint(3.185089974293059,0.8946015424164524));
//    a8.push_back(new ofPoint(2.9640102827763495,0.6709511568123394));
//    a8.push_back(new ofPoint(2.9640102827763495,0.3059125964010283));
//    a8.push_back(new ofPoint(4.29305912596401,0.07969151670951158));
//    a8.push_back(new ofPoint(4.5681233933161955,0.07969151670951158));
//    a8.push_back(new ofPoint(4.676092544987147,0.18766066838046272));
//    a8.push_back(new ofPoint(4.676092544987147,0.4498714652956298));
//    a8.push_back(new ofPoint(4.29305912596401,0.4498714652956298));
//    a8.push_back(new ofPoint(4.29305912596401,0.8946015424164524));
//    a8.push_back(new ofPoint(4.663239074550129,0.8946015424164524));
//    a8.push_back(new ofPoint(4.789203084832906,0.7712082262210798));
//    a8.push_back(new ofPoint(4.789203084832906,0.5629820051413882));
//    a8.push_back(new ofPoint(4.969151670951157,0.07969151670951158));
//    a8.push_back(new ofPoint(5.341902313624679,0.07969151670951158));
//    a8.push_back(new ofPoint(4.969151670951157,0.4498714652956298));
//    a8.push_back(new ofPoint(5.341902313624679,0.4498714652956298));
//    a8.push_back(new ofPoint(4.969151670951157,0.8946015424164524));
//    a8.push_back(new ofPoint(5.341902313624679,0.8946015424164524));
//    a8.push_back(new ofPoint(6.223650385604113,0.21593830334190234));
//    a8.push_back(new ofPoint(6.087403598971723,0.07969151670951158));
//    a8.push_back(new ofPoint(5.714652956298201,0.07969151670951158));
//    a8.push_back(new ofPoint(5.488431876606684,0.3059125964010283));
//    a8.push_back(new ofPoint(5.488431876606684,0.6709511568123394));
//    a8.push_back(new ofPoint(5.712082262210797,0.8946015424164524));
//    a8.push_back(new ofPoint(6.074550128534705,0.8946015424164524));
//    a8.push_back(new ofPoint(6.32133676092545,0.6478149100257069));
//    a8.push_back(new ofPoint(6.32133676092545,0.5295629820051414));
//    a8.push_back(new ofPoint(6.020565552699229,0.5295629820051414));
//    a8.push_back(new ofPoint(6.4704370179948585,0.07969151670951158));
//    a8.push_back(new ofPoint(6.4704370179948585,0.8946015424164524));
//    a8.push_back(new ofPoint(6.624678663239075,0.8946015424164524));
//    a8.push_back(new ofPoint(6.624678663239075,0.07969151670951158));
//    a8.push_back(new ofPoint(7.277634961439589,0.8946015424164524));
//    a8.push_back(new ofPoint(7.277634961439589,0.07969151670951158));
//    a8.push_back(new ofPoint(7.763496143958869,0));
//    a8.push_back(new ofPoint(7.881748071979436,0.12082262210796917));
//    a8.push_back(new ofPoint(7.881748071979436,0.8817480719794344));
//    a8.push_back(new ofPoint(7.763496143958869,1));
//    letters.push_back(a8);

    
    fixPoints();
}
void TitleScreen::draw(ofxShapeBatchRenderer *shapeBatch)
{
    for (int i=0; i<letters.size(); i++) {
        for(int j=0; j<letters[i].size()-1; j++){
            shapeBatch->addLine(ofVec2f(*letters[i][j])*screenDrawMult, ofVec2f(*letters[i][j+1])*screenDrawMult);
        }
    }
}
bool TitleScreen::assignPoint(ofPoint *point)
{
    // first make sure that there is something to assign a point to
    if(letters.size() == 0 or letters[0].size() == 0){
        return false;
    }
    point->set(*letters[0][0]);
    letters[0].erase(letters[0].begin());
    // if there are no more points in the current letter, then erase it
    if(letters[0].size()==0){
        letters.erase(letters.begin());
    }
    return true;
}
void TitleScreen::fixPoints()
{
    for (int i=0; i<letters.size(); i++) {
        for (int j=0; j<letters[i].size(); j++) {
            letters[i][j]->set((*letters[i][j])*screenMult+offset);
        }
    }
//    for (int j=0; j<letters[letters.size()-1].size(); j++) {
//        letters[letters.size()-1][j]->set((*letters[letters.size()-1][j])*screenMultTap+offsetTap);
//    }
}