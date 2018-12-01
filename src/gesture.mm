//
//  gesture.mm
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//

#include "gesture.h"

void Gesture::record(ofVec2f pos) {
    recordingTime = 0;
    previousPos = pos;
    filter.fill(pos);
    blips.clear();
};

void Gesture::update(Stepper stepper, ofVec2f pos) {
    ofVec2f mi = previousPos;     // initial mouse position
    ofVec2f mf = pos;             // final mouse position
    ofVec2f dm = mf - mi;         // mouse delta

    // Velocity final. The unfiltered gesture looks prettier with stepsDuration
    // than with frameDuration.
    ofVec2f vf = dm / stepper.stepsDuration();

    // Note that the step at "stepZeroTime" has already been processed.
    // For that reason, we start on stepIndex 1, and loop while "<="
    int stepIndex = 1; // start
    while (stepIndex <= stepper.steps) {
        // time since stepZero
        double sinceTime = stepIndex * stepper.stepSize;
        recordingTime += stepper.stepSize;

        ofVec2f input = mi + vf * sinceTime;
        filter.push(input);

        Blip b;
        b.pos = filter.average();
        b.gestureTime = recordingTime;

        blips.push_back(b);
        stepIndex++;
    }

    previousPos = mf;
};

int Gesture::size() {
    return blips.size();
};

std::list <Blip> Gesture::play(Stepper stepper) {
    std:list <Blip> result;
    double timeSince = 0;
    double timeLeft = stepper.stepsDuration();
    int stepIndex = 1;
    playbackTime += timeLeft;

    while (!blips.empty() && stepIndex <= stepper.steps) {
        timeSince += stepper.stepSize;
        timeLeft -= stepper.stepSize;
        Blip b = blips.front();
        // time since stepZero
        b.sinceTime = timeSince;
        // time to next stepZero
        b.updateTime = timeLeft;
        result.push_back(b);
        blips.pop_front();
    }
    return result;
}
