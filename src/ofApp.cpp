#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    uint64_t microseconds = ofGetElapsedTimeMicros();
    uint64_t deltaMicroseconds = microseconds - previousMicroseconds;

    // time differnece in seconds
    float dt = static_cast<float>(deltaMicroseconds * 0.000001);
    
    int x = ofGetMouseX();
    int y = ofGetMouseY();

    ofVec2f mi = ofVec2f(previousX, previousY);
    ofVec2f mf = ofVec2f(x, y);
    ofVec2f dm = mf - mi;

    ofVec2f vi = previousVelocity;
    ofVec2f vf = dm / dt;
    ofVec2f dv = vf - vi;

    ofVec2f a = dv / dt; // average acceleration = (change in V) / (change in T)

    ofSetColor(255, 0, 0);
    for (float time = 0; time < dt; time += 0.0015) {
        ofVec2f prevPos = t1.parts.back().pos;
        ofVec2f v = vi + (a * time);
        ofVec2f pos = mi + (v * time);
        t1.add(pos.x, pos.y, 30, dt - time); // not exact, but close enough
        ofSetColor(255, 255, 255);
        previousVelocity = (pos - prevPos) / 0.0015; // works as long as we have at least 2 steps
    }

    bool down = ofGetMousePressed(); // Is the mouse currently down?
    if (mouseDown) {
//        t1.append(mouseX, mouseY, 30);
    } else {
        t1.update(dt);
    }

    previousVelocity = vf; // Should we comment this out and do it in the for loop?
    previousAcceleration = a;
    previousX = x;
    previousY = y;
    previousMicroseconds = microseconds;
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
    if (button != 0) return;
    mouseDown = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (button != 0) return;
    mouseDown = false;
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
