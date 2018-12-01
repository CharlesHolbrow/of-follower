//
//  gesture.h
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//
// Gesture is a touch input recorder. It keeps a sequential, timestamped
// list of touch events.

#ifndef gesture_h
#define gesture_h

#include <list>

#include "ofMain.h"
#include "stepper.h"
#include "filter.h"

// A Blip on the radar. Timing and position of a point in the gesture.
struct Blip {
    // The x,y position of this blip
    ofVec2f pos;

    // How long into the gesture was this created?
    double gestureTime;

    // sinceTime and updateTime are only meaningful in the context of a frame.
    // The provide timing information within a frame, and help the renderer
    // know how much to update each blip.
    double sinceTime;   // how long after step0 was this created?
    double updateTime;  // At the last step in the frame, how old is the blip?
};

struct MouseEvent {
    ofVec2f pos;
    ofVec2f vel;
    bool isDown;
    bool down;
};


class Gesture {
private:
    // Mouse position at the end of last frame
    ofVec2f previousPos;
    // Playhead position, so consecutive play() calls know where to pick up from
    double playbackTime;
    // The last added blip
    double recordingTime;
    // Smooth out input values
    Filter <60> filter;
    std::list <Blip> blips;

public:
    // input
    ofVec2f velocity;

    // Start recording a new gesture. (does not change stepper size)
    void record(ofVec2f pos);

    // Construct the gesture by adding a new blips
    void update(Stepper stepper, ofVec2f pos);

    // How many unplayed blips are in the gesture?
    int size();

    // Get all the blips for a frame. This advances the gesture's playhead by
    // the frameDuration. The absolute position of the stepper is ignored.
    std::list <Blip> play(Stepper stepper);
};

#endif /* gesture_h */
