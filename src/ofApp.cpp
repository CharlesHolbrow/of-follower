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

    // how much time are we going to tick for in this frame
    double timeLeft = stepper.timeLeft(frameEnd);

    bool down = ofGetMousePressed(); // Is the mouse currently down?

    int x = ofGetMouseX();
    int y = ofGetMouseY();

    ofVec2f mi = previousMousePos; // initial mouse position
    ofVec2f mf = ofVec2f(x, y);    // final mouse position
    ofVec2f dm = mf - mi;          // mouse delta
    ofVec2f vf = dm / frameDelta;  // velocity final. NOTE: use fame delta, not step delta

    // update all existing particles
    t1.update(timeLeft);

    ofSetColor(127. + 127. * sin(frameEnd), 255, 255);

    double startTime = stepper.time();
    while (stepper.stepToward(frameEnd)) {
        float timeLeft = stepper.timeLeft(frameEnd);
        float timeSince = stepper.timeSince(startTime);

        ofVec2f input = mi + vf * timeSince;
        filter.push(input);
        ofVec2f pos = filter.average();
        t1.add(pos.x, pos.y, 30, timeLeft);
    }

    // deal with the gesture
    if (down != previousMouseIsDown) {
        if (down) {
            // mouse pressed
            gesture.start(mf);
        } else {
            // mouse released
        }
    }

    if (down) {
        gesture.update(frameDelta, mf);
    }

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
