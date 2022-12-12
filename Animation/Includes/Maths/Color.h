#pragma once

namespace Maths
{
    class RGB;

    // RGBA color values between 0 and 1.
    class RGBA
    {
    public:
        float r, g, b, a = 1;

        RGBA();
        RGBA(const float& _r, const float& _g, const float& _b, const float& _a);
        RGBA(const RGB& rgb);
        RGB rgb();
        float* ptr();

        RGBA operator+ (const RGBA& c)  const { return { r + c.r,    g + c.g ,   b + c.b,    a + c.a }; }
        RGBA operator+ (const float& v) const { return { r + v  ,    g + v   ,   b + v  ,    a + v   }; }
        RGBA operator- (const RGBA& c)  const { return { r - c.r,    g - c.g ,   b - c.b,    a - c.a }; }
        RGBA operator- (const float& v) const { return { r - v  ,    g - v   ,   b - v  ,    a - v   }; }
        RGBA operator* (const RGBA& c)  const { return { r * c.r,    g * c.g ,   b * c.b,    a * c.a }; }
        RGBA operator* (const float& v) const { return { r * v  ,    g * v   ,   b * v  ,    a * v   }; }
        RGBA operator/ (const RGBA& c)  const { return { r / c.r,    g / c.g ,   b / c.b,    a / c.a }; }
        RGBA operator/ (const float& v) const { return { r / v  ,    g / v   ,   b / v  ,    a / v   }; }
        void operator+=(const RGBA& c)  { r += c.r;   g += c.g;   b += c.b;   a += c.a; }
        void operator+=(const float& v) { r += v;     g += v;     b += v;     a += v;   }
        void operator-=(const RGBA& c)  { r -= c.r;   g -= c.g;   b -= c.b;   a -= c.a; }
        void operator-=(const float& v) { r -= v;     g -= v;     b -= v;     a -= v;   }
        void operator*=(const RGBA& c)  { r *= c.r;   g *= c.g;   b *= c.b;   a *= c.a; }
        void operator*=(const float& v) { r *= v;     g *= v;     b *= v;     a *= v;   }
        void operator/=(const RGBA& c)  { r /= c.r;   g /= c.g;   b /= c.b;   a /= c.a; }
        void operator/=(const float& v) { r /= v;     g /= v;     b /= v;     a /= v;   }
        bool operator==(const RGBA& c) { return   r == c.r && g == c.g && b == c.b && a == c.a; }
        bool operator!=(const RGBA& c) { return   r != c.r || g != c.g || b != c.b || a != c.a; }
    };

    // RGB color values between 0 and 1.
    class RGB 
    { 
    public:
        float r, g, b; 

        RGB();
        RGB(const float& _r, const float& _g, const float& _b);
        RGB(const RGBA& rgba);
        RGBA rgba();
        float* ptr();
    };

    // HSV color values (h in rad, sv between 0 and 1).
    struct HSV { float h, s, v; } ;

    // Returns the given RGBA color's hue.
    float colorGetHue(const RGB& rgb);

    // Linear interpolation between two given colors.
    RGBA colorLerp(const float& val, const RGBA& start, const RGBA& end);

    // Blend between two HSV colors.
    HSV  blendHSV(const HSV& col0, const HSV& col1);

    // Convert an RGBA color (0 <= rgba <= 1) to HSV.
    HSV  RGBAtoHSV(const RGBA& color);

    // Convert an HSV color to RGBA.
    RGBA HSVtoRGBA(const HSV& hsv, const float& alpha = 1);

    // Shifts the hue of the given color.
    RGBA colorShift(const RGBA& color, const float& hue);
}
