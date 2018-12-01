#pragma once

#include <string>
#include <map>
#include "gesture.h"
#include "trail.h"
#include "stepper.h"
#include "ofMain.h"

using namespace std;

string randomString(int size);

struct Player {
    Gesture gesture;
    Trail trail;
    string id;
};

class Content {
public:
    Player* mainPlayer;
    map<string, Player> storage;

    void update(Stepper stepper, ofVec2f pos, bool isDown);
    void render();
};
