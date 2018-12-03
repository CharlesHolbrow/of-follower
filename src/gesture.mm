//
//  gesture.mm
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//

#include "gesture.h"

void Gesture::reset() {
    totalBlips = -1; // "un-terminate" the gesture
    recordingTime = 0;
    previousPos = ofVec2f(0, 0);
    filter.fill(previousPos);
    blipsVec.clear();
};

void Gesture::update(Stepper stepper, MouseEvent mouse) {
    if (!mouse.isDown) {
        recordingTime += stepper.stepsDuration();
        return;
    };
    if (mouse.press) {
        filter.fill(mouse.pos);
        previousPos = mouse.pos;
    }

    // Note that the step at "stepZeroTime" has already been processed.
    // For that reason, we start on stepIndex 1, and loop while "<="
    int stepIndex = 1; // start
    while (stepIndex <= stepper.steps) {
        // time since stepZero
        double sinceTime = stepIndex * stepper.stepSize;
        recordingTime += stepper.stepSize;

        ofVec2f input = previousPos + mouse.vel * sinceTime;
        filter.push(input);

        Blip b;
        b.pos = filter.average();
        b.gestureTime = recordingTime;

        blipsVec.push_back(b);
        stepIndex++;
    }
    previousPos = mouse.pos;
};

int Gesture::size() {
    return blipsVec.size();
};

void Gesture::terminate() {
    totalBlips = blipsVec.size();
};
