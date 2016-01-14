#include "ofMain.h"
//#include "ofApp.h"
#include "testScene.h"

//========================================================================
int main( ){
ofSetupOpenGL(1440,986,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testScene());

    
    /*
     *256*4 64*4*4
     *256*3 64*4*3
     */
    
}
