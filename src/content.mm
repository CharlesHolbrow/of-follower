//
//  content.m
//  Follower
//
//  Created by Charles Holbrow on 11/30/18.
//
#include "content.h"

string randomString(int size) {
    string result;
    result.reserve(size);
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < size; ++i) {
        result.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
    }
    return result;
};


void Content::update(Stepper stepper, MouseEvent mouse){
    // If there is no current target, create one
    if (mouse.press && mainGesture == NULL) {
        Gesture g;
        std::string id = randomString(16);
        gestures[id] = g;
        mainGesture = &gestures[id];
        Trail t;
        t.playhead.init(mainGesture);
        trails.push_back(t);
        ofLog() << "Creating player with ID: " << id  << " size: " << gestures.size();
    }

    if (mainGesture != NULL) {
        mainGesture->update(stepper, mouse);
    }

    // update all existing trails
    for (auto trail = trails.begin(); trail != trails.end(); trail++) {
        trail->update(stepper.stepsDuration());
    }

    // TODO: remove unused players? This will be important once we start
    // creating new players
};

void Content::render() {
    for (auto trail = trails.begin(); trail != trails.end(); trail++) {
        trail->render();
    }
};
