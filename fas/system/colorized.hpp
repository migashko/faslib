#ifndef FAS_SYSTEM_COLORIZED_HPP
#define FAS_SYSTEM_COLORIZED_HPP

#include <fas/integral/int2type.hpp>
#include <fas/system/colors.hpp>
#include <fas/system/system.hpp>
#include <fas/system/detail/windowsconsole.hpp>

#include <ostream>
#include <iostream>

namespace fas { namespace console{

  template<int C1=0, int C2=-1, int C3=-1, int C4=-1, int C5=-1>
  struct color_list {};

  template<int C1=-1, int C2=-1, int C3=-1, int C4=-1, int C5=-1>
  struct make_color
  {
    typedef void (*type)( color_list<C1, C2, C3, C4, C5> );
  };

  template<int C1, int C2, int C3, int C4, int C5>
  inline typename make_color<C1, C2, C3, C4, C5>::type color() { return 0; }

  template<int C1, int C2, int C3, int C4>
  inline typename make_color<C1, C2, C3, C4, -1>::type color() { return 0; }

  template<int C1, int C2, int C3>
  inline typename make_color<C1, C2, C3, -1, -1>::type color() { return 0; }

  template<int C1, int C2>
  inline typename make_color<C1, C2, -1, -1, -1>::type color() { return 0; }

  template<int C1>
  inline typename make_color<C1, -1, -1, -1, -1>::type color() { return 0; }

  inline make_color<-1, -1, -1, -1, -1>::type color() { return 0; }

  inline void restore_colors(color_list<colors::restore>){}
  inline void black( color_list<colors::foreground::black>){}
  inline void red( color_list<colors::foreground::red>){}
  inline void green( color_list<colors::foreground::green>){}
  inline void brown( color_list<colors::foreground::brown>){}
  inline void blue( color_list<colors::foreground::blue>){}
  inline void magenta( color_list<colors::foreground::magenta>){}
  inline void cyan( color_list<colors::foreground::cyan>){}
  inline void gray( color_list<colors::foreground::gray>){}

  inline void dark_gray( color_list<colors::foreground::dark_gray>){}
  inline void light_red( color_list<colors::foreground::light_red>){}
  inline void light_green( color_list<colors::foreground::light_green>){}
  inline void yellow( color_list<colors::foreground::yellow>){}
  inline void light_blue( color_list<colors::foreground::light_blue>){}
  inline void light_magenta( color_list<colors::foreground::light_magenta>){}
  inline void light_cyan   ( color_list<colors::foreground::light_cyan>){}
  inline void white( color_list<colors::foreground::white>){}

  inline void bg_black( color_list<colors::background::black>){}
  inline void bg_red( color_list<colors::background::red>){}
  inline void bg_green( color_list<colors::background::green>){}
  inline void bg_brown( color_list<colors::background::brown>){}
  inline void bg_blue( color_list<colors::background::blue>){}
  inline void bg_magenta( color_list<colors::background::magenta>){}
  inline void bg_cyan( color_list<colors::background::cyan>){}
  inline void bg_gray( color_list<colors::background::gray>){}

  inline void bg_dark_gray( color_list<colors::background::dark_gray>){}
  inline void bg_light_red( color_list<colors::background::light_red>){}
  inline void bg_light_green( color_list<colors::background::light_green>){}
  inline void bg_yellow( color_list<colors::background::yellow>){}
  inline void bg_light_blue( color_list<colors::background::light_blue>){}
  inline void bg_light_magenta( color_list<colors::background::light_magenta>){}
  inline void bg_light_cyan   ( color_list<colors::background::light_cyan>){}
  inline void bg_white( color_list<colors::background::white>){}

  inline void bold(color_list<colors::bold>){}
  inline void underline(color_list<colors::underline>){}
  inline void underline2(color_list<colors::underline2>){}
  inline void blink(color_list<colors::blink>){}
  inline void blink2(color_list<colors::blink2>){}
  inline void reverse_color(color_list<colors::reverse>){}
  inline void nobold(color_list<colors::nobold>){}
  inline void nounderline(color_list<colors::nounderline>){}
  inline void noblink(color_list<colors::noblink>){}
  inline void noreverse_color(color_list<colors::noreverse>){}

}} // namespace fas

namespace std {
  template<int C1, int C2, int C3, int C4, int C5>
  ostream& operator << (
    ostream& os,
    void (*)( ::fas::console::color_list<C1, C2, C3, C4, C5> )
  )
  {
    // если переопределить rdbuf в cout, clog, или cerr, то все равно будет пытаться установить цвета
    if ( (::fas::system::is_atty_stdout() && ( cout.rdbuf() == os.rdbuf() || clog.rdbuf() == os.rdbuf() ) )
         || ( ::fas::system::is_atty_stderr() && cerr.rdbuf() == os.rdbuf() )
       )
    {

#if defined(CWINDOWSCONSOLE)
      ::fas::detail::CWindowsConsole::Instance().SetAttributes(C1);
      ::fas::detail::CWindowsConsole::Instance().SetAttributes(C2);
      ::fas::detail::CWindowsConsole::Instance().SetAttributes(C3);
      ::fas::detail::CWindowsConsole::Instance().SetAttributes(C4);
      ::fas::detail::CWindowsConsole::Instance().SetAttributes(C5);
      return os
#elif defined(_POSIX_VERSION)
      os << "\033["<<C1;
      //os << "\e["<<C1;
      if (C2!=-1) os << ";" << C2;
      if (C3!=-1) os << ";" << C3;
      if (C4!=-1) os << ";" << C4;
      if (C5!=-1) os << ";" << C5;
      os << "m";
      return os;
#endif
    }
    return os;
  }
}

#endif
