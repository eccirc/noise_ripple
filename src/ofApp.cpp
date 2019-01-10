/*Image manipulation program written by David Williams 27/11/2018
 * for Lab Assignment in 'Advanced Audio Visual Processing' week 8.
 * Credit to Mick Grierson - the ripple effect created here is based on
 * his horizonal re-sizing example code. This was adapted to include a parameterised noise function which creates the ripple effect
 * in both the horizonal and vertical axis. GUI setup help thanks to the OF examples.
 *
 *David Williams January 2019
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //show/hide the GUI panel

    guiHide = true;

    //load an image

    spider.load("PATH/TO/YOUR/IMAGE"); //image to be loaded

    //
    spider.resize(ofGetWidth(), ofGetHeight()); //resize the image for faster performance

    //setup the sliders
    gui.setup();
    gui.add(s_xAlign.setup("horizontal align", 1, 5, 0));
    gui.add(s_noiseScale.setup("noise scale", 0.1, 0, 5));
    gui.add(s_noiseMult.setup("noise freq multiplier", 0.00001, 0, 0.0001));
    gui.add(s_noisePos.setup("noise wave position",1,0,5));
    gui.add(s_vMult.setup("vertical ripple amount", 0, 0,0.5));
    gui.add(s_rAmount.setup("red channel",1,2,0));
    gui.add(s_gAmount.setup("green channel",1,2,0));
    gui.add(s_bAmount.setup("blue channel",1,2,0));

    //reset button
    gui.add(reset.setup("reset all", true));


}

//--------------------------------------------------------------
void ofApp::update(){
    //use these for image processing based on the image above
    ofPixels pPixIn;
    ofPixels pPixOut;

    //allocate the dimensions of the loaded image to pixels out with three channels (RGB)
    pPixOut.allocate(spider.getWidth(), spider.getHeight(), 3);
    //load image pixel data into the pixels In object
    pPixIn = spider.getPixels();

    //set the function params to match the sliders
    pPixOut = mRipple(pPixIn, pPixOut, spider.getWidth(), spider.getHeight(),3, s_xAlign, s_noiseScale,s_noiseMult, s_noisePos, s_vMult, s_rAmount,s_gAmount,s_bAmount);

    if(reset){
        s_noiseMult = 0;
        s_rAmount = 1;
        s_gAmount = 1;
        s_bAmount = 1;
        s_xAlign = 1;
        s_noiseScale = 0.1;
        s_noisePos = 1;
        s_vMult = 0;

        reset = !reset;
    }

    myTexture.allocate(pPixOut);
}

//--------------------------------------------------------------
void ofApp::draw(){

    //draw the image with the effect
    myTexture.draw(0,0, ofGetWidth(), ofGetHeight());

    if(guiHide){
    gui.draw();
    }

}

//--------------------------------------------------------------
//Ripple function using openFrameworks built-in noise function
ofPixels ofApp::mRipple(ofPixels pixIn, ofPixels pixOut, int sizeW, int sizeH, int channels, float xAlign, float noiseScale,float noiseMult, float noisePos,float vMult, float rAmount, float gAmount, float bAmount){

    //calculate the total size of the pixel array
    int totalSize = sizeH*sizeW*channels;


    for (int i =0;i<totalSize;i+=sizeW*channels) { //loop through the total pixel array

                for (int j = 0;j<sizeW;j++) { //loop through the x-axis

                    float noise = ofNoise(noisePos + i * noiseMult, j * vMult) * noiseScale; // increasing the noiseScale effectively up the 'distortion' - smooth or noisy wave. Second noise dimension controls vertical ripples
                    float noiseEffect = noise + xAlign; //increase xAlign to move on the x; numbers over 1 shows the image multiplied over the canvas


                    //adding the 'noiseEffect' to each channel seperately allows shifting of the RGB channels
                    pixOut[i+(j*3)]=pixIn[i+(floor(j * (noiseEffect * rAmount))*3)];
                    pixOut[i+(j*3)+1]=pixIn[i+(floor(j* (noiseEffect * gAmount))*3)+1];
                    pixOut[i+(j*3)+2]=pixIn[i+(floor(j* (noiseEffect* bAmount))*3)+2];

                   //cout << noise << endl;
                }

            }

            return pixOut;
}




//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    if(key == 'h'){
        guiHide = !guiHide;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
