#pragma once

#include "ofMain.h"
#include "ofxGui.h"
class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);

    //custom ripple function
    ofPixels mRipple(ofPixels pixIn, ofPixels pixOut, int sizeW, int sizeH, int channels, float xAlign, float noiseScale,float noiseMult, float noisePos,float vMult, float rAmount, float gAmount, float bAmount);

    //for loading an image file
    ofImage spider;

    //write the result of the process to an ofTexture object
    ofTexture myTexture;

    //instantiate some gui slider stuff to control the effect variables

    ofxFloatSlider s_xAlign;
    ofxFloatSlider s_noiseScale;
    ofxFloatSlider s_noiseMult;
    ofxFloatSlider s_noisePos;
    ofxFloatSlider s_vMult;
    ofxFloatSlider s_rAmount;
    ofxFloatSlider s_gAmount;
    ofxFloatSlider s_bAmount;

    ofxToggle reset;


    ofxPanel gui;

    //show/hide the GUI
    bool guiHide;




};
