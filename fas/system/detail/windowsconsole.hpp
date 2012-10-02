#ifndef FAS_SYSTEM_DETAIL_WINDOWS_CONSOLE_HPP
#define FAS_SYSTEM_DETAIL_WINDOWS_CONSOLE_HPP

#include <fas/system/colors.hpp>
#include <fas/system/unp.hpp>

namespace fas { namespace console{ namespace detail{

#if defined(HAVE_WINDOWS_H)

class CWindowsConsole
{
  HANDLE m_hConsoleOutput;
  WORD m_wAttributes;
  BOOL m_bGetConsoleScreenBufferInfoResult;

  ~CWindowsConsole()
  {
    if ( m_bGetConsoleScreenBufferInfoResult )
      ::SetConsoleTextAttribute(m_hConsoleOutput, m_wAttributes);
  }

  CWindowsConsole()
    : m_hConsoleOutput(INVALID_HANDLE_VALUE)
    , m_bGetConsoleScreenBufferInfoResult(FALSE)
  {
    m_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if ( m_hConsoleOutput != INVALID_HANDLE_VALUE )
    {
      m_wAttributes = GetConsoleTextAttribute();
    }
  }

public:
  
  WORD GetConsoleTextAttribute()
  {
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    
    m_bGetConsoleScreenBufferInfoResult = 
        ::GetConsoleScreenBufferInfo(
            m_hConsoleOutput,
            &consoleScreenBufferInfo
        );

    if ( m_bGetConsoleScreenBufferInfoResult )
      return consoleScreenBufferInfo.wAttributes;
    
    return 0;
  }

  void SetAttributes(int member)
  {
    if ( !m_bGetConsoleScreenBufferInfoResult )
      return;

    if ( member == -1)
      return;

    if ( member == colors::restore)
    {
      this->Restore();
      return;
    }

    WORD foregroundMask = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    WORD backgroundMask = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    WORD mask = GetConsoleTextAttribute() ;

    if ( member >= colors::foreground::black && member <= colors::foreground::gray)
    {
      mask &=~foregroundMask;
      switch ( member )
      {
        case colors::foreground::black : break;
        case colors::foreground::red : mask |= FOREGROUND_RED; break;
        case colors::foreground::green : mask |= FOREGROUND_GREEN; break;
        case colors::foreground::brown : mask |= FOREGROUND_RED | FOREGROUND_GREEN; break;
        case colors::foreground::blue : mask |= FOREGROUND_BLUE; break;
        case colors::foreground::magenta : mask |= FOREGROUND_RED | FOREGROUND_BLUE; break;
        case colors::foreground::cyan : mask |= FOREGROUND_GREEN | FOREGROUND_BLUE; break;
        case colors::foreground::gray : mask |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
      }
    }
    else if ( member >= colors::foreground::dark_gray && member <= colors::foreground::white)
    {
      mask &=~foregroundMask;
      switch ( member )
      {
        case colors::foreground::dark_gray : mask |= FOREGROUND_INTENSITY; break;
        case colors::foreground::light_red : mask |= FOREGROUND_RED | FOREGROUND_INTENSITY; break;
        case colors::foreground::light_green : mask |= FOREGROUND_GREEN| FOREGROUND_INTENSITY; break;
        case colors::foreground::yellow : mask |= FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_INTENSITY; break;
        case colors::foreground::light_blue : mask |= FOREGROUND_BLUE| FOREGROUND_INTENSITY; break;
        case colors::foreground::light_magenta : mask |= FOREGROUND_RED | FOREGROUND_BLUE| FOREGROUND_INTENSITY; break;
        case colors::foreground::light_cyan : mask |= FOREGROUND_GREEN | FOREGROUND_BLUE| FOREGROUND_INTENSITY; break;
        case colors::foreground::white : mask |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE| FOREGROUND_INTENSITY; break;
      }
    } 
    else if ( member >= colors::background::black && member <= colors::background::gray)
    {
      mask &=~backgroundMask;
      switch ( member )
      {
      case colors::background::black : break;
      case colors::background::red : mask |= BACKGROUND_RED; break;
      case colors::background::green : mask |= BACKGROUND_GREEN; break;
      case colors::background::brown : mask |= BACKGROUND_RED | BACKGROUND_GREEN; break;
      case colors::background::blue : mask |= BACKGROUND_BLUE; break;
      case colors::background::magenta : mask |= BACKGROUND_RED | BACKGROUND_BLUE; break;
      case colors::background::cyan : mask |= BACKGROUND_GREEN | BACKGROUND_BLUE; break;
      case colors::background::gray : mask |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;
      }
    }
    else if ( member >= colors::background::dark_gray && member <= colors::background::white)
    {
      mask &=~backgroundMask;
      switch ( member )
      {
      case colors::background::dark_gray : mask |= BACKGROUND_INTENSITY; break;
      case colors::background::light_red : mask |= BACKGROUND_RED | BACKGROUND_INTENSITY; break;
      case colors::background::light_green : mask |= BACKGROUND_GREEN| BACKGROUND_INTENSITY; break;
      case colors::background::yellow : mask |= BACKGROUND_RED | BACKGROUND_GREEN| BACKGROUND_INTENSITY; break;
      case colors::background::light_blue : mask |= BACKGROUND_BLUE| BACKGROUND_INTENSITY; break;
      case colors::background::light_magenta : mask |= BACKGROUND_RED | BACKGROUND_BLUE| BACKGROUND_INTENSITY; break;
      case colors::background::light_cyan : mask |= BACKGROUND_GREEN | BACKGROUND_BLUE| BACKGROUND_INTENSITY; break;
      case colors::background::white : mask |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE| BACKGROUND_INTENSITY; break;
      }
    }
    else if ( member == colors::underline)
    {
      // mask |=COMMON_LVB_UNDERSCORE;
    }
    else if ( member == colors::nounderline)
    {
      // mask &=~COMMON_LVB_UNDERSCORE;
    }
    else if ( member == colors::reverse)
    {
      // mask |= COMMON_LVB_REVERSE_VIDEO;
    }
    else if ( member == colors::noreverse)
    {
      // mask &=~ COMMON_LVB_REVERSE_VIDEO;
    }
    else
      return;

    ::SetConsoleTextAttribute(m_hConsoleOutput, mask );
  }

  void Restore()
  {
    if ( !m_bGetConsoleScreenBufferInfoResult )
      return;

    ::SetConsoleTextAttribute(m_hConsoleOutput, m_wAttributes);
  }

  static CWindowsConsole& Instance()
  {
    static CWindowsConsole instance;
    return instance;
  }

public:
};

#endif // HAVE_WINDOWS_H

}}}

#endif
