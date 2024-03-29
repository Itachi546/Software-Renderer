/*
  Main Window Class for making and rendering the window
  Managed by SDL
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iosfwd>
#include <stdint.h>

struct SDL_Renderer;
struct SDL_Window;

class vec2;
class vec3;
struct  Vertex3d;

class MainWindow{

 private:
  SDL_Renderer* renderer;
  SDL_Window* window;
  unsigned int width, height;
  bool running;
  float* z_buffer;


  vec3 barycentric(const vec2& v0, const vec2& v1, const vec2& v2, const vec2& px);
  void clear_depth();

 public:
  explicit MainWindow(int width, int height, const char* title);
  void destroy();
  void poll_events();
  bool is_open();
  void render();
  void clear(uint8_t r, uint8_t g, uint8_t b);
  void set_title(const char* title);
  void plot_pixel(int x, int y, vec3 color);
  void draw_line(vec2 v1, vec2 v2, vec3 color);

  void draw_triangle(Vertex3d v0, Vertex3d v1, Vertex3d v2);
  void draw_triangle(vec2 v0, vec2 v1, vec2 v2);

  void scan_triangle(Vertex3d v0, Vertex3d v1, Vertex3d v2);
  void triangle(Vertex3d v0, Vertex3d v1, Vertex3d v2);
  
};


#endif
