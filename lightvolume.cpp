#define GL_GLEXT_PROTOTYPES

#ifdef _MSC_VER
// windows.h is needed for OpenGL on Windows
#include <windows.h>
#endif

#ifdef USE_GLEW
#include <GL/glew.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "visibility/visibility.hpp"


using namespace geometry;


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

    // Disable state change
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


extern "C" void init(void) {
#ifdef USE_GLEW
  GLenum err = glewInit();
  if (GLEW_OK != err) {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }
#endif

  glGenBuffers(1, &vbo);
}
