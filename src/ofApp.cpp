#include <list>
#include <array>
#include "ofApp.h"
#include "stepper.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    stepper.setStepSize(1. / 2000.);
    ofLog() << "Ticks per frame @ 60fps: " << 1. / 60. / stepper.getStepSize();

    ofJson v;
    v["hi"] = 102;
    std::list <int> ints;
    ints.push_back(1);
    ints.push_back(4);
    v["ints"] = ints;
    Blip bbb;
    bbb.pos = ofVec2f(3.5, 4.5);
    bbb.gestureTime = 10.111;
    v["blip"] = bbb;

    ofLogNotice("setup - ") << v;
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
    for (auto t = trails.begin(); t != trails.end(); t++) {
        t->update(stepper.stepsDuration());
    }
    extraT.update(stepper.stepsDuration());

    // deal with the gesture
    if (down && down != previousMouseIsDown) {
        // start a new gesture
        gesture.record(pos);
        extraG.record(pos);
        // add a trail
        Trail t;
        t.speed = 0.5 + 0.25 * sin(frameStart * 0.5);
        trails.push_back(t);
        ofLog() << "add trail";
    }

    if (down) {
        gesture.update(stepper, pos);
        extraG.update(stepper, pos);
    }

    std::list<Blip> playBlips = gesture.play(stepper);
    for (auto b = playBlips.begin(); b != playBlips.end(); b++) {
        ofSetColor(127. + 127. * sin(b->gestureTime), 255, 255);
        trails.back().add(b->pos.x, b->pos.y, 30);
        trails.back().updateLast(b->updateTime);
    }

    // Hacky code for testing gesture playback;
    bool done = false;
    if (ofGetElapsedTimef() > 10) {
        playBlips = extraG.play(stepper);
        if (!done && playBlips.size()) {
            ofLog() << "playing... " << playBlips.size();
            ofJson j;
            j["points"] = playBlips;
            ofLogNotice("update - ") << j;
            done = true;
        }

        for (auto b = playBlips.begin(); b != playBlips.end(); b++) {
            ofSetColor(255, 127. + 127. * sin(b->gestureTime), 255);
            extraT.add(b->pos.x, b->pos.y, 30);
            extraT.updateLast(b->updateTime);
        }
    }

    previousMicroseconds = microseconds;
    previousMousePos = pos;
    previousMouseIsDown = down;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    for (auto t = trails.begin(); t != trails.end(); t++) {
        t->render();
    }
    extraT.render();
    while (!trails.empty() && trails.front().isDead()) {
        trails.pop_front();
        ofLog() << "removing trail";
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
