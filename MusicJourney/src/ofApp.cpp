#include "ofApp.h"

using namespace glm;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFullscreen(true);
    ofEnableDepthTest();
    ofBackground(10, 20, 30);
    ofHideCursor();
    cam.setDistance(1000);
    count=0;
    time = 0;
    
    //----------------------------setup music system
    //初期位置の設定
    img[0].load("blueGrass.jpg");
    img[1].load("country.jpeg");
    img[2].load("RockRoll.jpg");
    img[3].load("RarageRock.jpeg");
    img[4].load("IndieRock.jpg");
    img[5].load("NuGaze.jpeg");
    
    r=100;
    
    
    for(int i=0;i<num;i++){
        theta1[i]=ofRandom(-PI,PI);
        theta2[i]=ofRandom(PI);
        
        
        x[i]=r*sin(theta1[i])*cos(theta2[i]);
        y[i]=r*sin(theta1[i])*sin(theta2[i]);
        z[i]=r*cos(theta1[i]);
        
        /*
        x[i]=r*cos(ofDegToRad(theta1[i]));
        y[i]=r*sin(ofDegToRad(theta1[i]));
        z[i]=5*r*(i+1);
         */
        
        start[i]=vec3(x[i],y[i],z[i]);
        radius[i]=0.3;
        auto m=make_unique<musicImg>(start[i], img[i], &radius[i]);
        mis.push_back(move(m));
        col[i].setHsb(i*255/num, 80*255/100, 60*255/100);
    }
    

    
    //----------------- setup cemera control
    cc=new cameraControl();
    
    //----------------- setup color
}

//--------------------------------------------------------------
void ofApp::update(){
    for(auto& m:mis){
        m->update();
    }
    
    //unityでいうinvolve関数を作っておきたかったから笑
    auto& m=mis[count];
    if(cc->arrival){
        count++;
        if(count>num-1){
            count=num-1;
        }
        time=1;
     //ある程度近づいたら集合
    }else if(cc->near){
        m->collectImg(cc->location);
        if(count>0){
            auto& bm=mis[count-1];
            bm->scatterImg();
        }
    }
    
    //cameraの位置のcontrol
    cam.setPosition(cc->location);
    
    cc->seek(start[count]);
    cc->update();
    
    //involveの片割れ
    if(time!=0){
        time++;
        if(time>60){
            time=0;
            auto& bm=mis[count-1];
            bm->scatterImg();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    for(auto& m:mis){
        m->display();
    }
    
    /*
    ofSetLineWidth(3);
    for(int i=0;i<mis.size()-1;i++){
        ofSetColor(col[i],100);
        ofDrawLine(mis[i]->start.x, mis[i]->start.y, mis[i]->start.z, mis[i+1]->start.x,mis[i+1]->start.y,mis[i+1]->start.z);
    }
     */
    
    //カメラを向ける方向
    auto& m=mis[count];
    cam.setTarget(m->camPos);
    //cam.setTarget(m->start);
    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
