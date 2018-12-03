//
//  trail.h
//  Follower
//
//  Created by Charles Holbrow on 11/26/18.
//

#ifndef trail_h
#define trail_h

#include "gesturePlayhead.h"

class Particle {
public:
    ofVec2f pos;
    ofVec2f velocity;
    double size;

    ofColor ofc = ofColor::white;

    void update(double deltaTime) {
        pos += velocity * deltaTime;
        size -= 30.f * deltaTime;
        size = (size < 0) ? 0 : size;
    };

    ofColor color() {
        float scale = ofMap(size, 0, 28, 0.1, 1, true);
        return scale * ofc;
    };

    bool isDead() {
        return (size < 1) ;
    };

    void render() {
        ofSetColor(color());
        ofDrawCircle(pos.x, pos.y, size);
    };
};

class Trail {
public:
    GesturePlayhead playhead;
    float speed = 1;
    std::list <Particle> parts;
    void clear() {
        parts.clear();
    };

    // Update each particle
    void update(float deltaTime) {
        for (auto p = parts.begin(); p != parts.end(); p++) {
            p->update(deltaTime * speed);
        }
        // remove small particles from the "front"
        while (parts.size() > 0 && parts.front().isDead()) {
            parts.pop_front();
        }

        // see if there are new blips from the gesture
        double updateTime = 0;
        for (auto b : playhead.update(deltaTime)) {
            ofSetColor(127. + 127. * sin(b.gestureTime), 255, 255);
            add(b.pos.x, b.pos.y, 30);
            updateLast(playhead.playbackTime - b.gestureTime);
        }
    };
    
    void updateLast(double deltaTime) {
        if (!parts.size()) return;
        parts.back().update(deltaTime * speed);
    };

    // Add a single particle, and update with deltaTime. Calls ofGetStyle for color.
    void add(float x, float y, float size) {
        Particle p;
        p.size = size;
        p.pos.x = x;
        p.pos.y = y;
//        p.velocity.x = 100;
//        p.velocity.y = 80;
        p.ofc = ofGetStyle().color;
        parts.push_back(p);
    }

    // Draw the trail
    void render() {
        for (auto p = parts.begin(); p != parts.end(); p++) {
            p->render();
        }
    };
    
    bool isDead() {
        return parts.empty();
    }
};


#endif /* trail_h */
