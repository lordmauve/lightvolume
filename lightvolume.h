/* Initalise the library (allocate VBO). */
void init(void);


/* Draw a visibility volume. */
void draw_visibility(
      float light_x,
      float light_y,
      const float *segments,
      unsigned int num_coords);
