#pragma once

#include <list>
#include "ofMain.h"
#include "stepper.h"
#include "gesture.h"
#include "trail.h"
#include "customJson.h"

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

    // Caching the previous frame make it easy to get the delta
    uint64_t previousMicroseconds = 0;
    bool previousMouseIsDown;
    ofVec2f previousMousePos;

    Stepper stepper;
    Gesture gesture;
		Gesture extraG;
		Trail extraT;
    std::list <Trail> trails;
};
