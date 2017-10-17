#define GL_GLEXT_PROTOTYPES

#include <GL/glu.h>
#include "visibility/visibility.hpp"


using namespace geometry;

const float def_segments[] = {
  0.0f, 0.0f,
  0.0f, 500.0f,
  0.0f, 500.0f,
  500.0f, 500.0f,
  500.0f, 500.0f,
  500.0f, 0.0f,
  500.0f, 0.0f,
  0.0f, 0.0f,

  300.0f, 300.0f,
  300.0f, 400.0f,
  300.0f, 400.0f,
  400.0f, 400.0f,
  400.0f, 400.0f,
  400.0f, 300.0f,
  400.0f, 300.0f,
  300.0f, 300.0f,

  60.0f, 20.0f,
  70.0f, 20.0f,
  70.0f, 20.0f,
  70.0f, 30.0f,
  70.0f, 30.0f,
  60.0f, 30.0f,
  60.0f, 30.0f,
  60.0f, 20.0f,

  100.0f, 20.0f,
  120.0f, 20.0f,
  120.0f, 20.0f,
  120.0f, 30.0f,
  120.0f, 30.0f,
  100.0f, 30.0f,
  100.0f, 30.0f,
  100.0f, 20.0f,
};


vec2 light = {
  30.0f, 50.0f
};


// The id of the VBO that will be used for rendering
unsigned int vbo;


extern "C" void
draw_visibility(
      float light_x,
      float light_y,
      const float *segments,
      unsigned int num_coords) {
    std::vector<line_segment> vsegments;

    for (unsigned int i = 0; i < num_coords; i += 4) {
      line_segment seg = line_segment {
	vec2 {segments[i], segments[i + 1]},
	vec2 {segments[i + 2], segments[i + 3]},
      };
      vsegments.push_back(seg);
    }
    std::vector<vec2> result = visibility_polygon(
      vec2 {light_x, light_y},
      vsegments
    );

    unsigned int vbo_size = 4 + (unsigned int) result.size() * 2;
    float *vs = new float[vbo_size];
    vs[0] = light_x;
    vs[1] = light_y;

    float *pos = vs + 2;

    for (auto&& v : result) {
      *(pos++) = v.x;
      *(pos++) = v.y;
    }

    *(pos++) = result.front().x;
    *(pos++) = result.front().y;

    //Make the new VBO active
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Upload vertex data to the video device
    glBufferData(GL_ARRAY_BUFFER, vbo_size * sizeof(float), vs, GL_DYNAMIC_DRAW);

    //Indicate that it's 2D vertices
    glVertexPointer(2, GL_FLOAT, 0, NULL);

    delete vs;

    //Establish array contains vertices (not normals, colours, texture coords etc)
    glEnableClientState(GL_VERTEX_ARRAY);

    //Actually draw the triangle, giving the number of vertices provided
    glDrawArrays(GL_TRIANGLE_FAN, 0, vbo_size / 2);
}


/*
void drawCenter(void) {
   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_LINE_LOOP);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(0.0f, 0.0f);    // x, y
      glVertex2f(0.0f, 500.0f);
      glVertex2f(500.0f,  500.0f);
      glVertex2f(500.0f,  0.0f);
   glEnd();
}


void
display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0f, -1.0f, 0.0f);
    glScalef(1.0f / 250.0f, 1.0f / 250.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glDisable(GL_CULL_FACE);
  draw_visibility(light.x, light.y, def_segments, sizeof def_segments / sizeof def_segments[0]);
  drawCenter();
  glutSwapBuffers();
}
*/


extern "C" void init(void) {
  glGenBuffers(1, &vbo);
}
