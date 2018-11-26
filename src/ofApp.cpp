#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    stepper.setStepSize(1. / 1000.);
    gesture.stepper.setStepSize(1. / 1000.);
    ofLog() << "Tickst per frame @ 60fps: " << 1. / 60. / stepper.getStepSize();
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

    // Get mouse information;
    bool down = ofGetMousePressed(); // Is the mouse currently down?
    int x = ofGetMouseX();
    int y = ofGetMouseY();

    // What did the mouse do during the last frame?
    ofVec2f mi = previousMousePos; // initial mouse position
    ofVec2f mf = ofVec2f(x, y);    // final mouse position
    ofVec2f dm = mf - mi;          // mouse delta
    ofVec2f vf = dm / frameDelta;  // velocity final. NOTE: use fame delta, not step delta

    // update all existing particles
    t1.update(frameDelta);

    // deal with the gesture
    if (down && down != previousMouseIsDown) {
        gesture.start(mf);
    }
    if (down) {
        gesture.update(frameDelta, mf);
    }
    for (auto b = gesture.blips.begin(); b != gesture.blips.end(); b++) {
        // How long has the blip been alive for?
        double lifeTime = gesture.stepper.time() - b->time;
        t1.add(b->pos.x, b->pos.y, 30, lifeTime);
    }
    gesture.blips.clear();

    previousMicroseconds = microseconds;
    previousMousePos = mf;
    previousMouseIsDown = down;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    t1.render();
    ofSetColor(200, 10, 10);
    l1.draw();

    ofSetColor(128, 0, 0);
    for (auto blip = gesture.blips.begin(); blip != gesture.blips.end(); blip++) {
        ofDrawCircle(blip->pos.x, blip->pos.y, 4);
    }
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
