//
//  filter.h
//  Follower
//
//  Created by Charles Holbrow on 11/24/18.
//

#ifndef filter_h
#define filter_h

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

#endif /* filter_h */
