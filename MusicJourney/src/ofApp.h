#pragma once

#include "ofMain.h"
#include "musicImg.hpp"
#include "cameraControl.hpp"

using namespace glm;

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
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    ofEasyCam cam;
		
    vector<unique_ptr<musicImg>> mis;
    cameraControl* cc;
    
    float r;
    static const int num=2;
    float theta1[num];
    float theta2[num];
    float x[num];
    float y[num];
    float z[num];
    
    vec3 start[num];
    ofImage img[num];
    float radius[num];
    int count;
    float time;
};
