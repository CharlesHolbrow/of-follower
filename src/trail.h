//
//  trail.h
//  Follower
//
//  Created by Charles Holbrow on 11/26/18.
//

#ifndef trail_h
#define trail_h

class Particle {
public:
    ofVec2f pos;
    float size;
    void update(float deltaTime) {
        size -= 30.f * deltaTime;
        size = (size < 0) ? 0 : size;
    };
    ofColor ofc = ofColor::white;
    ofColor color() {
        float scale = ofMap(size, 0, 28, 0.1, 1, true);
        return scale * ofc;
    };
};

class Trail {
public:
    std::list <Particle> parts;
    void clear() {
        parts.clear();
    };

    // Update each particle
    void update(float deltaTime) {
        for (auto p = parts.begin(); p != parts.end(); p++) {
            p->update(deltaTime);
        }
        // remove small particles from the
        while (parts.size() > 0 && parts.front().size < 1) {
            parts.pop_front();
        }
    };

    // Add a single particle, and update with deltaTime. Calls ofGetStyle for color.
    void add(float x, float y, float size, float deltaTime) {
        Particle p;
        p.size = size;
        p.pos.x = x;
        p.pos.y = y;
        p.update(deltaTime);
        p.ofc = ofGetStyle().color;
        parts.push_back(p);
    }

    // Draw the trail
    void render() {
        for (auto p = parts.begin(); p != parts.end(); p++) {
            ofSetColor(p->color());
            ofDrawCircle(p->pos.x, p->pos.y, p->size);
        }
    };
};


#endif /* trail_h */
