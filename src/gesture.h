//
//  gesture.h
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//
// Gesture is a touch input recorder. It keeps a sequential, timestamped
// list of touch events.
//
// There are types of time that we are interested in.
// - Frames (frame rate). We cannot control this precisely, but we can request
//   with ofSetFrameRate(fps).
// - Steps a smaller increment that we controll precisely. Every frame, we step
//   multiple times. The step size is specified exactly.

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
    double updateStepsDuration; // duration of all steps in the most recent update
    ofVec2f previousPos;        // Mouse position at the end of last frame
    double previousTime;        // When did the last frame end?
public:
    Filter filter;
    Stepper stepper;
    std::list <Blip> blips;

    // Starts a new gesture. (does not change stepper size)
    void start( ofVec2f pos) {
        previousPos = pos;
        previousTime = 0;
        updateStepsDuration = 0;
        filter.fill(pos);
        blips.clear();
        stepper.restart();
    };

    void setStepSize(double stepSize) {
        stepper.setStepSize(stepSize);
    };

    // How long did the most recent update cover? Should be a multiple of step size.
    double getUpdateDuration() {
        return updateStepsDuration;
    }

    void update(double frameDelta, ofVec2f pos) {
        double frameEnd = previousTime + frameDelta;
        // how much time are we going to tick for in this frame
        updateStepsDuration = stepper.timeLeft(frameEnd);

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
        }

        previousTime = frameEnd;
        previousPos = mf;
    };
};


#endif /* gesture_h */
