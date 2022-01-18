#include <iostream>
#include <vector>
using namespace std;


#include "shaders/shaders.h"
#include "shaders/fragment_shader.h"
#include "shaders/shaders_program.h"

#include "viewing/vectors.h"


void tests() {
    FragmentShader frag;
    ShadersList vect(1, &frag);

    Vec3f v3f(1, 2, 3);
    Vec3d v3d;
    v3d << 11, 12, 13;
    cout << v3f << endl << v3d << endl;
    cout << v3d.x() << ", " << v3d.x(5) << endl;

}
