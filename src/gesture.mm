//
//  gesture.mm
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//

#include "ofMain.h"
#include "gesture.h"


using nlohmann::json;
void to_json(json& j, const Blip& b) {
    j = json{{"x", b.pos.x}, {"y", b.pos.y}, {"t", b.gestureTime}};
}

void from_json(const json& j, Blip& b) {
    b.pos.x = j.at("x").get<double>();
    b.pos.y = j.at("y").get<double>();
}


void Gesture::record(ofVec2f pos) {
    previousPos = pos;
    filter.fill(pos);
    blips.clear();
};

void Gesture::update(Stepper stepper, ofVec2f pos) {
    ofVec2f mi = previousPos;     // initial mouse position
    ofVec2f mf = pos;             // final mouse position
    ofVec2f dm = mf - mi;         // mouse delta

    // Velocity final. The unfiltered gesture looks prettier with stepsDuration
    // than with frameDuration
    ofVec2f vf = dm / stepper.stepsDuration();

    // Note that the step at "stepZeroTime" has already been processed.
    // For that reason, we start on stepIndex 1, and loop while "<="
    int stepIndex = 1; // start
    while (stepIndex <= stepper.steps) {
        // time since stepZero
        double sinceTime = stepIndex * stepper.stepSize;
        // time to next step zero
        double updateTime = stepper.stepsDuration() - sinceTime;

        ofVec2f input = mi + vf * sinceTime;
        filter.push(input);

        Blip b;
        b.pos = filter.average();
        b.updateTime = updateTime;
        b.sinceTime = sinceTime;
        b.gestureTime = stepper.stepZeroTime + sinceTime;

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
    double innerFrameEnd = playbackTime + stepper.frameDuration();
    // the difference in time between the stepper and the gesture;
    // How far ahead is global transport from inner?
    double diff = stepper.frameEnd - innerFrameEnd;
    double innerStepZero = stepper.stepZeroTime - diff;
    double innerLastStep = stepper.lastStepTime() - diff;

    while (!blips.empty() && blips.front().gestureTime <= innerFrameEnd) {
        Blip b = blips.front();
        b.sinceTime = b.gestureTime - innerStepZero;
        b.updateTime = innerLastStep - b.gestureTime;
        result.push_back(b);

        blips.pop_front();
    }
    playbackTime = innerFrameEnd;
    return result;
}