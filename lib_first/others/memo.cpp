#include<bits/stdc++.h>
using namespace std;
    int lg(int _) {
        _ = _ & 0xffff0000? _ & 0xffff0000: _;
        _ = _ & 0xff00ff00? _ & 0xff00ff00: _;
        _ = _ & 0xf0f0f0f0? _ & 0xf0f0f0f0: _;
        _ = _ & 0xcccccccc? _ & 0xcccccccc: _;
        _ = _ & 0xaaaaaaaa? _ & 0xaaaaaaaa: _;
        return _ << 2;
    }

    /*
#ifdef E
#define _GLIBCXX_DEBUG
#else 
#define NDEBUG
#endif

g++ -DE -o a a.cpp

*/