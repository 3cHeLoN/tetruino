#pragma once

class ScreenManager;

class Drawable
{
    private:
        int x_coordinate, y_coordinate;
    public:
        Drawable() {};
        virtual void draw(ScreenManager &manager) = 0;
};