//
//  ticker.h
//  Hike
//
//  Created by Charles Holbrow on 11/11/18.
//

#ifndef ticker_h
#define ticker_h

class Stepper {
private:
    double lastStepTime;
    double stepSize = 1;
public:
    // How many steps until time t?
    int stepsUntil(double t) { return floor((t - lastStepTime) / stepSize); };

    // Set our step duration. Noop if <= 0.
    void setStepSize(double t) { if (t > 0) stepSize = t; };

    // How long are our steps?
    double getStepSize() { return stepSize; };

    // When did the last step occur?
    double time() { return lastStepTime; };

    // Duration of all steps up until t.
    double timeLeft(double t) { return stepsUntil(t) * stepSize; };

    // Simple
    double timeSince(double t) { return lastStepTime - t; };

    // Restart the lastStepTime, but do not change the stepSize
    void restart() { lastStepTime = 0; };

    // returns true if step occured
    bool stepToward(double t) {
        if (t > lastStepTime) {
            double target = lastStepTime + stepSize;
            if (target < t) {
                lastStepTime += stepSize;
                return true;
            }
        }
        return false;
    };
};

#endif /* ticker_h */
