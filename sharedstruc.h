#pragma once
/*
by Tyler and Ibrahim
*/

struct linkedNode {
    int year;
    int mCount;
    int fCount;
    linkedNode(int _year, int _m = 0, int _f = 0) {
        year = _year;
        mCount = _m;
        fCount = _f;
    }
};
