#pragma once

#include <list>
#include "ofMain.h"
#include "ticker.h"

class Filter {
private:
    static const int SIZE = 30;
    ofVec2f values[SIZE];
    int position = 0;
public:
    void push(ofVec2f v) {
        values[position] = v;
        if (++position >= SIZE) {
            position = position % SIZE;
        }
    };
    void fill(ofVec2f v) {
        for (int i = 0; i < SIZE; i++) {
            values[i] = v;
        }
    }
    ofVec2f average(){
        ofVec2f result;
        for (int i = 0; i < SIZE; i++) {
            result += values[i];
        }
        return result / SIZE;
    }
};


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
private:
    // We want to make sure that our particles are drawn equally spaced. For
    // that reason, the list of particles ends before the particle that was
    // last appended. lastPos stores the last position that was appended to
    // the list of particles.
    ofVec2f lastPos;
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

    // Add a single particle, and update with deltaTime
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



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    uint64_t previousMicroseconds = 0;

    Stepper stepper;
    Trail t1;
    Filter filter;
    ofPolyline l1;

    ofVec2f previousMousePos;
};
