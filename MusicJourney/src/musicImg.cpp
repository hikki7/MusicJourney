//
//  musicImg.cpp
//  MusicJourney
//
//  Created by 引田祐樹 on 2019/01/07.
//

#include "musicImg.hpp"

musicImg::musicImg(vec3 _start,ofImage _img,float *radius){
    
    //画像の処理系
    img=_img;
    imgW=img.getWidth();
    imgH=img.getHeight();
    pixels=img.getPixels();
    r=*radius;
    start=_start;
    start.x+=imgW;
    start.y+=imgH;
    
    //camPosとstartが全然違う問題治す
    
    //imgの場所と色の取得
    target.resize(imgH);
    fakeTarget.resize(imgH);
    imgColor.resize(imgH);
    location.resize(imgH);
    for(int y=0;y<imgH;y++){
        target[y].resize(imgW);
        fakeTarget[y].resize(imgW);
        imgColor[y].resize(imgW);
        location[y].resize(imgW);
        for(int x=0;x<imgW;x++){
            target[y][x]=vec3(x-imgW/2,imgH-y,0);
            imgColor[y][x]=pixels.getColor(x, y);
            location[y][x]=vec3(ofRandom(-ofGetWidth()*3,ofGetWidth()*3),ofRandom(-ofGetHeight()*3,ofGetHeight()*3),ofRandom(-ofGetHeight()*3,ofGetHeight()*3));
            fakeTarget[y][x]=location[y][x];
        }
    }
    
    camPos=target[int(imgH/2)][int(imgW/2)];
    
}

musicImg::~musicImg(){
    
    
}

void musicImg::update(){
    for (int y=0; y<imgH; y++) {
        for(int x=0;x<imgW;x++){
            location[y][x]+=(fakeTarget[y][x]-location[y][x])*0.15;
        }
    }
}

void musicImg::display(){
    for (int y=0; y<imgH; y++) {
        for(int x=0; x<imgW; x++){
            ofSetColor(imgColor[y][x]);
            ofDrawCircle(location[y][x].x, location[y][x].y, location[y][x].z,r);
        }
    }
}

void musicImg::scatterImg(){
    r=0.3;
    for(int y=0;y<imgH;y++){
        for(int x=0;x<imgW;x++){
            fakeTarget[y][x]=vec3(ofRandom(-ofGetWidth(),ofGetWidth()),ofRandom(-ofGetHeight(),ofGetHeight()),ofRandom(-ofGetHeight(),ofGetHeight()));
        }
    }
}

void musicImg::collectImg(vec3 camloc){
    
    //カメラに合わせて角度を取ってくる
    float angleX=atan2(camloc.z-start.z, camloc.y-start.y);
    float angleY=atan2(camloc.z-start.z,camloc.x-start.x);
    
    r=1;
    //カメラの向く方向に設定するため
    ofPushMatrix();
    ofTranslate(start.x, start.y,start.z);
    ofRotateXRad(angleX);
    ofRotateYRad(angleY);
    for(int y=0;y<imgH;y++){
        for(int x=0;x<imgW;x++){
            fakeTarget[y][x]=target[y][x];
        }
    }
    ofPushMatrix();
}

