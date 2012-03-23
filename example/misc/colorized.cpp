#include <iostream>
#include <fas/system/colorized.hpp>

using namespace fas;

/*
std::ostream& test(std::ostream& out, int x)
{
  return out;
}*/

inline void my_color2( color_list< colors::bold, colors::fg::red, colors::background::yellow, colors::underline> ) {};

int main()
{
  //std::cout << test( std::cout, 10) << std::endl;
  // std::cout << red << "Red" << restore << std::endl;
  std::cout << black << bg_white<< "black" << restore << " foreground"<<std::endl;
  std::cout << red << "red" << restore << " foreground"<<std::endl;
  std::cout << green << "green" << restore << " foreground"<<std::endl;
  std::cout << brown << "brown" << restore << " foreground"<<std::endl;
  std::cout << blue << "blue" << restore << " foreground"<<std::endl;
  std::cout << magenta << "magenta" << restore << " (purple) foreground"<<std::endl;
  std::cout << cyan << "cyan" << restore << " (light blue) foreground"<<std::endl;
  std::cout << gray << "gray" << restore << " foreground"<<std::endl;

  
  std::cout << dark_gray << "dark_gray" << restore << " foreground"<<std::endl;
  std::cout << light_red << "light_red" << restore << " foreground"<<std::endl;
  std::cout << light_green << "light_green" << restore << " foreground"<<std::endl;
  std::cout << yellow << "yellow" << restore << " foreground"<<std::endl;
  std::cout << light_blue << "light_blue" << restore << " foreground"<<std::endl;
  std::cout << light_magenta << "light_magenta" << restore << " foreground"<<std::endl;
  std::cout << light_cyan << "light_cyan" << restore << " foreground"<<std::endl;
  std::cout << white << "white" << restore << " foreground"<<std::endl;

  std::cout << std::endl;
  std::cout << bg_black << "black" << restore << " background"<<std::endl;
  std::cout << bg_red << "red" << restore << " background"<<std::endl;
  std::cout << bg_green << "green" << restore << " background"<<std::endl;
  std::cout << bg_brown << "brown" << restore << " background"<<std::endl;
  std::cout << bg_blue << "blue" << restore << " background"<<std::endl;
  std::cout << bg_magenta << "magenta" << restore << " background"<<std::endl;
  std::cout << bg_cyan << "cyan" << restore << " background"<<std::endl;
  std::cout << bg_gray << black << "gray" << restore << " background"<<std::endl;

  std::cout << bg_dark_gray << "dark_gray" << restore << " background"<<std::endl;
  std::cout << bg_light_red << black << "light_red" << restore << " background"<<std::endl;
  std::cout << bg_light_green << black << "light_green" << restore << " background"<<std::endl;
  std::cout << bg_yellow << "yellow" << restore << " background"<<std::endl;
  std::cout << bg_light_blue << black << "light_blue" << restore << " background"<<std::endl;
  std::cout << bg_light_magenta << black << "light_magenta" << restore << " background"<<std::endl;
  std::cout << bg_light_cyan << black << "light_cyan" << restore << " background"<<std::endl;
  std::cout << bg_white << black << "white" << restore << " background"<<std::endl;
  
  std::cout << std::endl;
  std::cout << bold << "bold" << nobold << " && nobold" << std::endl;
  std::cout << underline << "underline" << nounderline << " && nounderline" << std::endl;
  std::cout << underline2 << "underline2" << nounderline << " && nounderline" << std::endl;
  std::cout << blink << "blink" << noblink << " && noblink" << std::endl;
  std::cout << blink2 << "blink2" << noblink << " && noblink" << std::endl;
  std::cout << reverse_color << "reverse" << noreverse_color << " && noreverse" << std::endl;
  
  std::cout << std::endl;
  
  std::cout << bold << red << bg_yellow << underline 
            << "bold, foreground red, background yellow, underline " 
            << restore << std::endl;


  // typedef color< colors::bold, colors::fg::red, colors::background::yellow, colors::underline> xxx;
  std::cout << make_color< colors::bold, colors::fg::red, colors::background::yellow, colors::underline>::type()
            << "bold, foreground red, background yellow, underline " 
            << restore << std::endl;
// #warning почему на работает на рабочем компе?

  std::cout << ::fas::color< colors::bold, colors::fg::red, colors::background::yellow, colors::underline>()
            << "bold, foreground red, background yellow, underline " 
            << restore << std::endl;

  void (*my_color)( color_list< colors::bold, colors::fg::red, colors::background::yellow, colors::underline> ) = 0;
  
  std::cout << my_color
            << "bold, foreground red, background yellow, underline " 
            << restore << std::endl;

  std::cout << my_color2
            << "bold, foreground red, background yellow, underline " 
            << restore << std::endl;

  // std::cout << "\e[0m" <<std::endl;
  
  /*
  for (int i = 0 ; i < 128; ++i)
    std::cout<<i<<"\t\e["<<i<<"mTesting Escepe\e[0m" << std::endl;
  */

  return 0;
}