#pragma once

class Color {
    private:
        unsigned char red;
        unsigned char green;
        unsigned char blue;

    public:
        // Constructor
        Color() : red(0), green(0), blue(0) {}
        Color(unsigned char r, unsigned char g, unsigned char b)
            : red(r), green(g), blue(b) {}

        // Getters for RGB values
        unsigned char getRed() const { return red; }
        unsigned char getGreen() const { return green; }
        unsigned char getBlue() const { return blue; }
};