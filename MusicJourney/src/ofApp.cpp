#include "ofApp.h"

using namespace glm;

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetFullscreen(true);
    ofBackground(10, 20, 30);
    ofHideCursor();
    cam.setDistance(1000);
    count=0;
    time=NULL;
    
    //----------------------------setup music system
    //初期位置の設定
    img[0].load("blueGrass.jpg");
    img[1].load("country.jpeg");
    
    r=10;
    
    for(int i=0;i<num;i++){
        theta1[i]=ofRandom(-PI,PI);
        theta2[i]=ofRandom(PI);
        radius[i]=0.1;
        x[i]=r*sin(theta1[i])*cos(theta2[i])+ofGetWidth()/2;
        y[i]=r*sin(theta1[i])*sin(theta2[i])+ofGetHeight()/2;
        z[i]=r*cos(theta1[i]);
        start[i]=vec3(x[i],y[i],z[i]);
        auto m=make_unique<musicImg>(start[i], img[i],&radius[i]);
        mis.push_back(move(m));
    }
    
    //----------------- setup cemera control
    cc=new cameraControl();
}

//--------------------------------------------------------------
void ofApp::update(){
    for(auto& m:mis){
        m->update();
    }
    
    auto& m=mis[count];
    if(cc->arrival){
        m->scatterImg();
        count++;
        if(count>num){
            count=num;
        }
    }else if(cc->near){
        m->collectImg();
    }
    
    
    cc->seek(start[count]);
    cc->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    for(auto& m:mis){
        m->display();
    }
    
    
    cc->display();
    cam.end();
    
    string thresholdMsg = "threshold:" + ofToString( count );
    ofDrawBitmapString( thresholdMsg, 20, 600);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key==' '){
        auto& m=mis[1];
        m->collectImg();
    }else{
        auto& m=mis[1];
        m->scatterImg();
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
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
