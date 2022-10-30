#include "color.hh"

namespace Delta {

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }

Color::Color(uint32_t colour) { 
  int rr = (colour >> 24) & 0xff;
  int gg = (colour >> 16) & 0xff;
  int bb = (colour >> 8 ) & 0xff;
  int aa =  colour        & 0xff;

  r = rr / 255.0f;
  g = gg / 255.0f;
  b = bb / 255.0f;
  a = aa / 255.0f;
};

uint32_t Color::UintRgba() const {
  unsigned char rr = (unsigned char)(0xff * r);
  unsigned char gg = (unsigned char)(0xff * g);
  unsigned char bb = (unsigned char)(0xff * b);
  unsigned char aa = (unsigned char)(0xff * a);
  return  (rr << 24) | (gg << 16) | (bb << 8) | aa;
};

uint32_t Color::UintAbgr() const {
  unsigned char rr = (unsigned char)(0xff * r);
  unsigned char gg = (unsigned char)(0xff * g);
  unsigned char bb = (unsigned char)(0xff * b);
  unsigned char aa = (unsigned char)(0xff * a);
  return  (aa << 24) | (bb << 16) | (gg << 8) | rr;
};

}
