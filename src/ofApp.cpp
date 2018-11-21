#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    uint64_t microseconds = ofGetElapsedTimeMicros();
    uint64_t deltaMicroseconds = microseconds - previousMicroseconds;

    // time in seconds
    float t = static_cast<float>(microseconds * 0.000001);
    // delta time in seconds
    float dt = static_cast<float>(deltaMicroseconds * 0.000001);

    int x = ofGetMouseX();
    int y = ofGetMouseY();

    ofVec2f mi = previousMousePos; // initial mouse position
    ofVec2f mf = ofVec2f(x, y);    // final mouse position
    ofVec2f dm = mf - mi;          // mouse delta
    ofVec2f vf = dm / dt;          // velocity final

    float step = 0.001;

    ofSetColor(255, 255, 255);
    for (float time = 0; time < dt; time += step) {
        ofVec2f input = mi + vf * time;
        filter.push(input);
        ofVec2f pos = filter.average();
        t1.add(pos.x, pos.y, 30, dt - time); // not exact, but close enough
    }

    bool down = ofGetMousePressed(); // Is the mouse currently down?
    if (!down) t1.update(dt);

    previousMicroseconds = microseconds;
    previousMousePos = mf;
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
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    t1.clear();
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
