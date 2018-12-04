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
        g.id = randomString(16);
        gestures[g.id] = g;
        mainGesture = &gestures[g.id];
        Trail t;
        t.playhead.init(mainGesture);
        trails.push_back(t);
        ofLog() << "Creating player with ID: " << g.id  << " size: " << gestures.size();
    }

    if (mainGesture != NULL) {
        mainGesture->update(stepper, mouse);
    }

    // update all existing trails
    for (auto trail = trails.begin(); trail != trails.end(); trail++) {
        trail->update(stepper.stepsDuration());
    }

    while (!trails.empty() && trails.front().isDead()) {
        ofLog() << "removing trail!";
        trails.pop_front();
    }
};

void Content::render() {
    for (auto trail = trails.begin(); trail != trails.end(); trail++) {
        trail->render();
    }
};

void Content::replayMainGesture() {
    if (mainGesture == NULL) return;
    Trail t;
    t.playhead.init(mainGesture);
    trails.push_back(t);
};

void Content::terminateMainGesture() {
    if (mainGesture == NULL) return;
    ofLogNotice("Content") << "Main Gesture terminated. Size: " << mainGesture->size();
    mainGesture->terminate();
    mainGesture = NULL;
};

void Content::mapMainGestureToKey(int key) {
    if (mainGesture == NULL) return;
    keymap[key].push_back(mainGesture->id);
};

void Content::playSavedGesture(int key) {
    if (!keymap.count(key)) return;
    std::string id = keymap[key].back();
    if (!gestures.count(id)) {
        ofLog() << "Content::playSavedGesture failed to find id: " << id;
        return;
    }
    Trail t;
    t.playhead.init(&gestures[id]);
    trails.push_back(t);
};
