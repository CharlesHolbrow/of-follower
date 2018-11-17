#pragma once

#include <list>
#include "ofMain.h"
#include "gesture.h"

class Particle {
public:
    ofVec2f pos;
    float size;
    void update(float deltaTime) {
        size *= 1 - (0.9 * deltaTime);
    };
    float color() {
        return ofMap(size, 0, 28, 12, 255, true);
    } const;
};

class Trail {
private:
    // We want to make sure that our particles are drawn equally spaced. For
    // that reason, the list of particles ends before the particle that was
    // last appended. lastPos stores the last position that was appended to
    // the list of particles.
    ofVec2f lastPos;

    // The most recently appended value should always be draw, even if it is
    // not far enough from the last point that was succesfully added. This
    // this ensures that the most recently added value does not appear
    // jittery when the trail extends slowly.
    Particle tip;

    ofPolyline line;
public:
    std::list <Particle> parts;
    void clear() {
        parts.clear();
        line.clear();
    };
    void update(float deltaTime) {
        // draw the tip first, then iterate toward the back. This means we
        // start at the "back" of the list, and work toward the front (new
        // particles are pushed to the back).
        tip.update(deltaTime);
        for (auto p = parts.begin(); p != parts.end(); p++) {
            p->update(deltaTime);
        }
        
        // remove small particles from the
        while (parts.size() > 0 && parts.front().size < 1) {
            parts.pop_front();
        }
    };

    // Append adds new particles. The new particles extend in a line from the
    // previous particles. Particles will be equally spaced. If the
    void append(float x, float y, float size) {
        Particle p;
        p.size = size;
        p.pos.x = x;
        p.pos.y = y;
        if (parts.size() == 0) {
            parts.push_back(p);
            lastPos = p.pos;
            return;
        }

        tip = p;

        ofVec2f target = ofVec2f{x, y};
        ofVec2f vector = target - lastPos;
        float stepSize = 1; // size of each step in pixels
        float numSteps = static_cast<int>(vector.length() / stepSize);
        ofVec2f step = vector.normalize() * stepSize;
        if (numSteps == 0) return; // we don't want
        ofVec2f pos = lastPos;
        for (float i = 0; i < numSteps; i++) {
            pos += step;
            p.pos = pos;
            parts.push_back(p);
        }
        lastPos = pos;
    };

    void curveTo(float x, float y, float size) {

        line.addVertex(x, y);

        // We need at least 4 points to make a curve. If we do not have four
        // points, just draw our points regularly
        if (line.getVertices().size() < 4) {
            append(x, y, size);
            return;
        }

        // create a curve from the last four points
        ofPolyline curve;
        auto verts = line.getVertices();
        for (int i = verts.size() - 4; i < verts.size(); i++) {
            curve.curveTo(verts[i], 10);
        }

        // Append along the curve. Remember that append only permanently adds a
        // particle iff it is far enough from the previously added particle.
        float step = 1./60./curve.size();
        float frameTime = 0;
        for (auto p = curve.getVertices().cbegin(); p != curve.getVertices().cend(); p++) {
            append(p->x, p->y, size);
            frameTime += step;
        }
    }

    // Draw the trail
    void render() {
        ofSetColor(tip.color());
        ofDrawCircle(tip.pos.x, tip.pos.y, tip.size);
        
        for (auto p = parts.rbegin(); p != parts.rend(); p++) {
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
    
    float previousTime = 0;
    float mouseX;
    float mouseY;
    Trail t1;
    Gesture gesture;
    ofPolyline l1;
    ofPath p1;
    bool mouseDown;
};
