//
//  ticker.h
//  Hike
//
//  Created by Charles Holbrow on 11/11/18.
//

#ifndef stepper_h
#define stepper_h

class Stepper {
public:
    double frameStart;
    double frameEnd;
    double stepZeroTime; // time of last step of previous frame
    int steps;
    double stepSize = 0.1;

    // Set our step duration. Noop if <= 0.
    void setStepSize(double t) { if (t > 0) stepSize = t; };

    // How long are our steps?
    double getStepSize() { return stepSize; };

    // How long was the last frame?
    double frameDuration() { return frameEnd - frameStart; };

    // How long were all the steps in the last frame;
    double stepsDuration() { return steps * stepSize; };

    // What time is the
    double lastStepTime() { return stepZeroTime + steps * stepSize; };

    // Restart the lastStepTime, but do not change the stepSize
    void restart() {
        frameStart = 0;
        frameEnd = 0;
        stepZeroTime = 0;
        steps = 0;
    };

    void advanceFrame(double frameDelta) {
        // update the stepZeroTime to the last step in the previous frame.
        // note that this should be done before other mutations.
        stepZeroTime += stepsDuration();

        // update the frame times
        frameStart = frameEnd;
        frameEnd = frameStart + frameDelta;

        // how many steps to take in this frame?
        steps = floor((frameEnd - stepZeroTime) / stepSize);
    };
};

#endif /* stepper_h */
