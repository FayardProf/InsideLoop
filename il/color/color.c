#include "color.h"

#include "math.h"

hsvf hsvf_from_rgbf(rgbf in) {
    hsvf out;
    float min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;
    float max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;
    out.v = max;
    float delta = max - min;
    if (delta < 0.00001f) {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if (max > 0.0f) {
        // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN; // its now undefined
        return out;
    }
    if (in.r >= max) // > is bogus, just keeps compilor happy
        out.h = (in.g - in.b) / delta; // between yellow & magenta
    else
    if (in.g >= max)
        out.h = 2.0f + (in.b - in.r) / delta; // between cyan & yellow
    else
        out.h = 4.0f + (in.r - in.g) / delta; // between magenta & cyan

    out.h *= 60.0; // degrees
    if (out.h < 0.0)
        out.h += 360.0;

    return out;
}

rgbf rgbf_from_hsvf(hsvf in) {
    float hh, p, q, t, ff;
    long i;
    rgbf out;
    if (in.s <= 0.0f) { // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if (hh >= 360.0f) hh = 0.0f;
    hh /= 60.0f;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0f - in.s);
    q = in.v * (1.0f - (in.s * ff));
    t = in.v * (1.0f - (in.s * (1.0 - ff)));
    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;
    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}