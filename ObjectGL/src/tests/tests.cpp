#include <vector>
using namespace std;


#include "shaders/shaders.h"
#include "shaders/fragment_shader.h"
#include "shaders/shaders_program.h"

class C {

public:
    C() { val = 0; }

    C(const C&) = delete;

    int val;
};



void tests() {
    FragmentShader frag;
    ShadersList vect(1, &frag);

}