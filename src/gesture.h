//
//  gesture.h
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//
// Gesture is a touch input recorder. It keeps a sequential, timestamped
// list of touch events. The positionAtTime method returns the position
// of the input gesture, interpolating between two points if needed.

#ifndef gesture_h
#define gesture_h

#include <list>

#include "ofMain.h"
#include "stepper.h"
#include "filter.h"

// A Blip on the radar. Timing and position of a point in the gesture.
// These will be added
struct Blip {
    ofVec2f pos;
    double time;
};


class Gesture {
private:
public:
    ofVec2f previousPos;
    double previousTime;

    Filter filter;
    Stepper stepper;
    std::list <Blip> blips;

    // Starts a new gesture. (does not change stepper size)
    void start( ofVec2f pos) {
        previousPos = pos;
        previousTime = 0;
        filter.fill(pos);
        blips.clear();
        stepper.restart();
    };

    void setStepSize(double stepSize) {
        stepper.setStepSize(stepSize);
    };


    void update(double frameDelta, ofVec2f pos) {
        double frameStart = previousTime;
        double frameEnd = previousTime + frameDelta;
        // how much time are we going to tick for in this frame
        double timeLeft = stepper.timeLeft(frameEnd);

        int x = ofGetMouseX();
        int y = ofGetMouseY();

        ofVec2f mi = previousPos;     // initial mouse position
        ofVec2f mf = pos;             // final mouse position
        ofVec2f dm = mf - mi;         // mouse delta
        ofVec2f vf = dm / frameDelta; // velocity final. NOTE: uses fame delta, not step delta

        ofSetColor(127. + 127. * sin(frameEnd), 255, 255);

        double startTime = stepper.time();
        while (stepper.stepToward(frameEnd)) {
            float timeLeft = stepper.timeLeft(frameEnd);
            float timeSince = stepper.timeSince(startTime);

            ofVec2f input = mi + vf * timeSince;
            filter.push(input);

            Blip b;
            b.pos = filter.average();
            b.time = stepper.time();

            blips.push_back(b);
            //t1.add(pos.x, pos.y, 30, timeLeft); // this is how it was done before abstracting Gesture
        }

        previousTime = frameEnd;
        previousPos = mf;
    };
};


#endif /* gesture_h */
