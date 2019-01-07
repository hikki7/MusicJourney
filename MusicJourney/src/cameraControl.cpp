//
//  cameraControl.cpp
//  MusicJourney
//
//  Created by 引田祐樹 on 2019/01/07.
//

#include "cameraControl.hpp"

using namespace glm;

cameraControl::cameraControl(){
    location=vec3(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(ofGetHeight()/2));
    velocity=vec3(0,0,0);
    acceleration=vec3(0,0,0);
    r=10;
    maxSpeed=4;
    maxForce=0.1;
    
    d=1000000;
    bd=1000000;
}

cameraControl::~cameraControl(){
    
}

void cameraControl::update(){
    
    velocity+=acceleration;
    
    if(length(velocity)>maxSpeed){
        velocity=normalize(velocity);
        velocity*=maxSpeed;
    }
    
    location+=velocity;
    acceleration*=0;
}

void cameraControl::display(){
    if(arrival){
     ofSetColor(255,0,0);
    }else if(near){
        ofSetColor(0,255,0);
    }else{
        ofSetColor(0,0,255);
    }
    ofDrawCircle(location.x,location.y,location.z,20);
}

void cameraControl::addForce(vec3 _force){
    acceleration+=_force;
}

void cameraControl::seek(vec3 _target){
    vec3 desired=_target-location;
    
    d=length(desired);
    desired=normalize(desired);
    
    if(d<=10&&bd>10){
        float m=ofMap(d, 0, 100, 0, maxSpeed);
        desired*=m;
        arrival=true;
        near=false;
    }else if(d<=100&&bd>100){
        float m=ofMap(d, 0, 100, 0, maxSpeed);
        desired*=m;
        near=true;
        arrival=false;
    }else{
        desired*=maxSpeed;
        near=false;
        arrival=false;
    }
    
    vec3 steer=desired-velocity;
    
    if(length(steer)>maxForce){
        steer=normalize(steer);
        steer*=maxForce;
    }
    
    addForce(steer);
    bd=d;
}

