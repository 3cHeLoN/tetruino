#pragma once
typedef unsigned char uint8_t;

class Color {
    private:
        uint8_t red;
        uint8_t green;
        uint8_t blue;

    public:
        // Constructor
        Color() : red(0), green(0), blue(0) {}
        Color(uint8_t r, uint8_t g, uint8_t b)
            : red(r), green(g), blue(b) {}

        // Getters for RGB values
        uint8_t getRed() const { return red; }
        uint8_t getGreen() const { return green; }
        uint8_t getBlue() const { return blue; }
};