
Using SGLW32.DLL in your Microsoft Visual C++ or Borland C++ Builder Project 
============================================================================

SglW32.lvc: import library for Microsoft Visual C++
SglW32.lbc: import library for Borland C++ Builder

To use SG-Lock the DLL SglW32.dll has to be linked to your application. This can be done dynamically by using the Win32 functions "LoadLibrary" and "GetProcAddress" or, which is much more easy, statically by using the import library SglW32.lvc . To do so, you have to add this file to "project/settings/link/project options".

Normally the suffix is "lib" but "lvc" shall indicate that it is for Visual C++ ("lbc" for C++ Builder), as the format of theese import libraries is different for other compilers. Please change the suffix to "lib" if you like.

If you are using another C-compiler a special import library has to be generated for it. If you need help for this please contact SG-Lock.
