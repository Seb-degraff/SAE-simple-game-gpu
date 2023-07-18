#pragma once // so that this header is included a maximum of one time per compilation unit. That way we don't get double declarations.

#define EXPORT __declspec(dllexport)    

struct Color
{
    float r, g, b, a;

    Color(float r, float g, float b, float a)
    {
        this->a = a;
        this->r = r;
        this->g = g;
        this->b = b;
    }
};
