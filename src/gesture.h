//
//  gesture.h
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//
// Gesture is a touch input recorder. It keeps a sequential, timestamped
// list of touch events. The positionAtTime method returns the position
// of the input gesture, interpolating between two points if needed.

#ifndef gesture_h
#define gesture_h

#include "ofMain.h"

struct GesturePoint {
    ofVec2f pos;
    float globalTime;
};

class Gesture {
private:
    GesturePoint* lastPoint;
public:
    std::list <GesturePoint> points;
    void clear();
    void append(float x, float y, float globalTime);
    float duration(); // how long does the gesture last for?
    bool isValidAtTime(float globalTime);
    ofVec2f positionAtTime(float globalTime);
};


#endif /* gesture_h */
