#include <GL/glut.h>
#include "structures.h"

struct PlayerControls{
    bool up;
    bool down;
};

class Player{
    private:
        int width;
        int height;
        int speed;
        Vertex defaultPosition;
    public:
        Player(Vertex initialPosition);

        PlayerControls controls;
        Vertex position;

        void move();
        void draw();
        void reset();
};