//
//  gesture.mm
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//

#include "ofMain.h"
#include "gesture.h"

void Gesture::clear() {
    points.clear();
}

/*
 Add a point to the gesture. The gloablTime must be greater than all
 previously added points. If it is not, the point will not be added.
*/
void Gesture::append(float x, float y, float globalTime) {
    GesturePoint gp;
    gp.pos.x = x;
    gp.pos.y = y;
    gp.globalTime = globalTime;

    if (points.size() != 0) {
        if (globalTime <= points.back().globalTime) return;
    }

    points.push_back(gp);
}

/*
 Get the length of the gesture. -1 if there are no points.
*/
float Gesture::duration() {
    if (points.size() == 0) return -1;
    if (points.size() == 1) return 0;
    return points.back().globalTime - points.front().globalTime;
}

/*
 Can provide a valid answer for the global time?
*/
bool Gesture::isValidAtTime(float globalTime) {
    if (points.size() == 0) return false;
    if (points.size() == 1){
        if (globalTime == points.back().globalTime) return true;
        else return false;
    }
    if (globalTime < points.front().globalTime) return false;
//    if (globalTime > points.back().globalTime) return false;
    return true;
}

/*
 WARNING: before calling this verify with isValidAtTime(time);
 Get the position in the gesture at the given time, interpolating between points;
*/
ofVec2f Gesture::positionAtTime(float globalTime) {
    ofVec2f result;
    result.x = 0;
    result.y = 0;

    if (points.size() == 0) return result;
    if (points.size() == 1) {
        if (points.back().globalTime == globalTime) return points.back().pos;
        else return result;
    }

    if (globalTime < points.front().globalTime) return result;
//    if (globalTime > points.back().globalTime) return result;

    // The two points that we are between
    GesturePoint before;
    GesturePoint after = points.back();

    for (auto gp = points.begin(); gp != points.end(); gp++) {
        // If we are exactly on the value, just return the position
        if (gp->globalTime == globalTime) return gp->pos;
        // If we run past the end, we're okay
        if (gp->globalTime >= globalTime) {
            after = *gp;
            break;
        }
        before = *gp;
    }

    // How long is the segment we are looking at?
    float duration = after.globalTime - before.globalTime;
    // What fraction of the segment is out point of interest at?
    float ratio = (globalTime - before.globalTime) / duration;
    // describe the segment as a vector;
    ofVec2f segmentVector = after.pos - before.pos;

    return (ratio * segmentVector) + before.pos;
}
