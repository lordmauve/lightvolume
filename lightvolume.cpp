#define GL_GLEXT_PROTOTYPES

#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include "visibility/visibility.hpp"


using namespace geometry;

const float segments[] = {
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


void draw_visibility() {
    std::vector<line_segment> vsegments;
    for (int i = 0; i < sizeof segments / sizeof(float); i += 4) {
      line_segment seg = line_segment {
	vec2 {segments[i], segments[i + 1]},
	vec2 {segments[i + 2], segments[i + 3]},
      };
      vsegments.push_back(seg);
    }
    std::vector<vec2> result = visibility_polygon(light, vsegments);

    unsigned int vbo_size = 4 + (unsigned int) result.size() * 2;
    float *vs = new float[vbo_size];
    vs[0] = light.x;
    vs[1] = light.y;

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
  draw_visibility();
  drawCenter();
  glutSwapBuffers();
}


void
init(void) {

  glGenBuffers(1, &vbo);

  //Force display to be drawn now
  glFlush();
}


void
mouseMove(int x, int y) {
  light.x = (float) x;
  light.y = (float) (500 - y);
  glutPostRedisplay();
}

int
main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Lighting demo");
  glutDisplayFunc(display);
  glutMotionFunc(mouseMove);
  init();
  glutMainLoop();
  return 0;
}
