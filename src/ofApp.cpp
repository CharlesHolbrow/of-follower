#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    stepper.setStepSize(1. / 2000.);
    ofLog() << "Ticks per frame @ 60fps: " << 1. / 60. / stepper.getStepSize();

    ofJson v;
    Blip b;
    b.pos = ofVec2f(3.5, 4.5);
    b.gestureTime = 0.111;
    v["blip"] = b;
    Stepper s;
    s.frameStart = 0.1;
    s.frameEnd = 0.2;
    s.stepSize = 0.001;
    s.steps = 2;
    v["stepper"] = s;

    ofLogNotice("setup - ") << v << std::endl;

    Gesture g;
    GesturePlayhead head;
    head.playbackPoint = 0;
    head.gesture = &g;

    g.blipsVec.push_back(b);
    b.gestureTime += 1; g.blipsVec.push_back(b); // 1.1
    b.gestureTime += 1; g.blipsVec.push_back(b);
    b.gestureTime += 1; g.blipsVec.push_back(b);
    b.gestureTime += 1; g.blipsVec.push_back(b);
    b.gestureTime += 1; g.blipsVec.push_back(b); // 5.1
    ofLog() << "hi " <<  g.blipsVec.back().gestureTime;

    for (auto b : head.play(4)) {
        ofLog() << "gestureTime - first : " << b.gestureTime;
    }
    for (auto b : head.play(7)) {
        ofLog() << "gestureTime - second: " << b.gestureTime;
    }
    b.gestureTime += 1; g.blipsVec.push_back(b); // 6.1
    for (auto b : head.play(7)) {
        ofLog() << "gestureTime - third:  " << b.gestureTime;
    }
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

    bool down = ofGetMousePressed();
    MouseEvent mouse;
    mouse.press = down && !previousMouse.isDown;
    mouse.release = !down && previousMouse.isDown;
    mouse.isDown = down;
    mouse.pos = ofVec2f(ofGetMouseX(), ofGetMouseY());
    mouse.vel = (mouse.pos - previousMouse.pos) / stepper.stepsDuration();

    content.update(stepper, mouse);

    previousMicroseconds = microseconds;
    previousMouse = mouse;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);

    content.render();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofLog() << "keyPressed: " << key;
    // Tab toggles recording state
    if (key == OF_KEY_TAB) {
        if (state == PLAYING) {
            state = RECORDING;
            ofLog() << "Recording";
        }
        else {
            state = PLAYING;
            ofLog() << "Recording";
        }
        return;
    }
    if (state == RECORDING) {
        ofLog() << "Save last gesture to " << key;
    } else  if (state == PLAYING){
        ofLog() << "Play gesture: " << key;
    }
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
