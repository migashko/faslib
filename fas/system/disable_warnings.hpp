
/*#ifndef FAS_SYSTEM_DISABLE_WARNINGS_HPP
#define FAS_SYSTEM_DISABLE_WARNINGS_HPP
*/


#ifdef _MSC_VER

#pragma warning( push )
#pragma warning( disable: 4503 )

#if _MSC_VER >= 1400
   // this is Visual C++ 2005
#elif _MSC_VER >= 1310
   // this is Visual c++ .NET 2003
#elif _MSC_VER > 1300
   // this is Visual C++ .NET 2002
#endif

#else


/*
#define DISABLE_WARNINGS
#define ENABLE_WARNINGS
*/

#endif

//#endif // FAS_SYSTEM_DISABLE_WARNINGS_HPP
