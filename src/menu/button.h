#pragma once

class Button {
    private:
        int x;
        int y;
        int width;
        int height;
    public:
        Button(int x, int y, int width, int height);
        render();
};