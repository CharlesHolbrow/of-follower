#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    float currentTime = ofGetElapsedTimef();
    float deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    
    if (mouseDown) {
        t1.append(mouseX, mouseY, 30);
    }
    
    t1.update(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    
    ofSetColor(12, 127, 127);
    t1.render();
    ofSetColor(200, 10, 10);
    l1.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (button != 0) return;
    mouseDown = true;
    
    t1.clear();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (button != 0) return;
    mouseDown = false;
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
