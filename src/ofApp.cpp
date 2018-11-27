#include "ofApp.h"
#include "stepper.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    stepper.setStepSize(1. / 2000.);
    ofLog() << "Tickst per frame @ 60fps: " << 1. / 60. / stepper.getStepSize();
    t1.speed =  0.5;
}

//--------------------------------------------------------------
void ofApp::update(){
    uint64_t microseconds = ofGetElapsedTimeMicros();
    uint64_t deltaMicroseconds = microseconds - previousMicroseconds;

    // What time did the frame start?
    double frameStart = static_cast<double>(previousMicroseconds * 0.000001);
    // time in seconds
    double frameEnd = static_cast<double>(microseconds * 0.000001);
    // delta time in seconds
    double frameDelta = static_cast<double>(deltaMicroseconds * 0.000001);

    // Setup the Stepper for this frame
    stepper.advanceFrame(frameDelta);

    // Get mouse information;
    bool down = ofGetMousePressed(); // Is the mouse currently down?
    ofVec2f pos = ofVec2f(ofGetMouseX(), ofGetMouseY()); // mouse position

    // update all existing particles
    t1.update(stepper.stepsDuration());

    // deal with the
    if (down && down != previousMouseIsDown) {
        gesture.start(pos);
    }

    if (down) {
        gesture.update(stepper, pos);
    }

    while (gesture.canPop()) {
        Blip b = gesture.pop();
        ofSetColor(127. + 127. * sin(b.gestureTime), 255, 255);
        t1.add(b.pos.x, b.pos.y, 30);
        t1.updateLast(b.updateTime);
    }

    previousMicroseconds = microseconds;
    previousMousePos = pos;
    previousMouseIsDown = down;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    t1.render();
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
