#pragma once

#include <string>
#include <map>
#include "gesture.h"
#include "trail.h"
#include "stepper.h"
#include "ofMain.h"

using namespace std;

string randomString(int size);

class Content {
public:
    Gesture* mainGesture;
    map<string, Gesture> gestures;
    list<Trail> trails;

    void update(Stepper stepper, MouseEvent mouse);
    void render();
    void replayMainGesture();
};
