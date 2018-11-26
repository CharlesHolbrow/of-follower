//
//  gesture.h
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//
// Gesture is a touch input recorder. It keeps a sequential, timestamped
// list of touch events.

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
    // Age and birth are both mulitples of the step size.
    double birth; // How long after the gesture started was the blip born.
    double age;   // At the time that the Blip was poped, how old is it?
};


// There are two types of time represented in a Gesture.
// - Frames (frame rate). We cannot control this precisely, but we can request
//   with ofSetFrameRate(fps). Frame time is passed to the update function.
// - Steps a smaller increment that we controll precisely. Every frame, we step
//   multiple times. The step size is specified exactly.
class Gesture {
private:
    double updateStepsDuration; // duration of all steps in the most recent update
    ofVec2f previousPos;        // Mouse position at the end of last frame
    double previousTime;        // When did the last frame end?
    std::list <Blip> blips;
    Filter filter;

public:
    Stepper stepper;

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
            b.birth = stepper.time();

            blips.push_back(b);
        }

        previousTime = frameEnd;
        previousPos = mf;
    };

    bool canPop() {
        return !blips.empty();
    };

    Blip pop() {
        Blip b;
        if (!canPop()) return b;

        b = blips.front();
        b.age = stepper.time() - b.birth;
        blips.pop_front();
        return b;
    }
};


#endif /* gesture_h */
