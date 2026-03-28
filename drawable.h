#pragma once

class ScreenManager;

class Drawable
{
private:
    bool m_visible = true;
    int x_coordinate, y_coordinate;

public:
    Drawable() {};
    virtual void draw(ScreenManager &manager) {};
    bool isVisible() { return m_visible; };
    void setVisible(bool visible)
    {
        m_visible = visible;
    };
    void toggleVisible()
    {
        m_visible = !m_visible;
    };
};