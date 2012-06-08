#ifndef FAS_SYSTEM_COLORS_HPP
#define FAS_SYSTEM_COLORS_HPP

namespace fas { namespace console{
  
struct colors
{
  enum
  {
    restore = 0,
    bold = 1,
    underline = 4,
    blink = 5,
    blink2 = 6,
    reverse = 7,
    underline2 = 21,
    nobold = 22,
    nounderline = 24,
    noblink = 25,
    noreverse = 27
  };

  struct foreground
  {
    enum
    {
      black = 30,
      red = 31,
      green = 32,
      brown = 33,
      blue = 34,
      magenta = 35,
      cyan = 36,
      gray = 37,

      dark_gray = 90,
      light_red = 91,
      light_green = 92,
      yellow = 93,
      light_blue = 94,
      light_magenta = 95,
      light_cyan = 96,
      white = 97
    };
  };

  typedef foreground fg;

  struct background
  {
    enum
    {
      black = 40,
      red = 41,
      green = 42,
      brown = 43,
      blue = 44,
      magenta = 45,
      cyan = 46,
      gray = 47,

      dark_gray = 100,
      light_red = 101,
      light_green = 102,
      yellow = 103,
      light_blue = 104,
      light_magenta = 105,
      light_cyan = 106,
      white = 107
    };

    typedef background bg;
  };
};
  
}}

#endif
