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
        RGB rgb() const;
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
        RGBA rgba() const;
        float* ptr();
    };

    // HSV color values (h in rad, sv between 0 and 1).
    struct HSV { float h, s, v; } ;


    // -- Color Methods -- //
    
    float ColorGetHue(const RGBA& rgb);                                      // Returns the given RGB color's hue.
    RGBA  ColorLerp  (const float& val, const RGBA& start, const RGBA& end); // Linear interpolation between two given colors.
    HSV   BlendHSV   (const HSV& col0, const HSV& col1);                     // Blend between two HSV colors.
    HSV   RGBAtoHSV  (const RGBA& color);                                    // Convert an RGBA color (0 <= rgba <= 1) to HSV.
    RGBA  HSVtoRGBA  (const HSV& hsv, const float& alpha = 1);               // Convert an HSV color to RGBA.
    RGBA  ColorShift (const RGBA& color, const float& hue);                  // Shifts the hue of the given color.
}
