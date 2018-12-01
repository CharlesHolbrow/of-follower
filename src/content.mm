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
    // update all existing trails
    for (auto it = storage.begin(); it != storage.end(); it++) {
        it->second.trail.update(stepper.stepsDuration());
    }

    // If there is no current target, create one
    if (mouse.press && mainPlayer == NULL) {
        Player p;
        p.id = randomString(16);
        storage[p.id] = p;
        mainPlayer = &storage[p.id];
        ofLog() << "Creating player with ID: " << p.id  << " size: " << storage.size();
    }

    if (mainPlayer != NULL) {
        mainPlayer->gesture.update(stepper, mouse);
    }

    // for every player, check if the gesture had new blips
    for (auto it = storage.begin(); it != storage.end(); it++) {
        list<Blip> newBlips = it->second.gesture.play(stepper);
        for (auto b = newBlips.begin(); b != newBlips.end(); b++) {
            ofSetColor(127. + 127. * sin(b->gestureTime), 255, 255);
            it->second.trail.add(b->pos.x, b->pos.y, 30);
            it->second.trail.updateLast(b->updateTime);
        }
    }

    // TODO: remove unused players? This will be important once we start
    // creating new players
};

void Content::render() {
    for (auto p = storage.begin(); p != storage.end(); p++) {
        p->second.trail.render();
    }
};
