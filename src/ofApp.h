#pragma once

#include <list>
#include "ofMain.h"
#include "stepper.h"
#include "gesture.h"
#include "trail.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    uint64_t previousMicroseconds = 0;

    bool previousMouseIsDown;

    Stepper stepper;
    Trail t1;
    Filter filter;
    ofPolyline l1;
    Gesture gesture;

    ofVec2f previousMousePos;
};
