#ifndef IL_COLOR_H
#define IL_COLOR_H

typedef struct {
    float r; // 0 <= . <= 1
    float g; // 0 <= . <= 1
    float b; // 0 <= . <= 1
} rgbf;

typedef struct {
    float h; // 0 <= . <= 360
    float s; // 0 <= . <= 1
    float v; // 0 <= . <= 1
} hsvf;

rgbf rgbf_from_hsvf(hsvf in);
hsvf hsvf_from_rgbf(rgbf in);

#endif //IL_COLOR_H