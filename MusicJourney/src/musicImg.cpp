//
//  musicImg.cpp
//  MusicJourney
//
//  Created by 引田祐樹 on 2019/01/07.
//

#include "musicImg.hpp"

musicImg::musicImg(vec3 start,ofImage _img,float *radius){
        
    //画像の処理系
    img=_img;
    imgW=img.getWidth();
    imgH=img.getHeight();
    pixels=img.getPixels();
    
    r=*radius;
    
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
            target[y][x]=vec3(x,y,0);
            target[y][x]+=start;
            imgColor[y][x]=pixels.getColor(x, y);
            location[y][x]=vec3(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(ofGetHeight()));
            fakeTarget[y][x]=location[y][x];
        }
    }
    
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
    r=0.1;
    for(int y=0;y<imgH;y++){
        for(int x=0;x<imgW;x++){
            fakeTarget[y][x]=vec3(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(ofGetHeight()));
        }
    }
}

void musicImg::collectImg(){
    r=1;
    for(int y=0;y<imgH;y++){
        for(int x=0;x<imgW;x++){
            fakeTarget[y][x]=target[y][x];
        }
    }
}

