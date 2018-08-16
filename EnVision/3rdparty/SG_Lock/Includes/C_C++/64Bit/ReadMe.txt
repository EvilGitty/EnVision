
Using SGLW64.DLL in your Microsoft Visual C++ Project 
=====================================================

SglW64.lib: import library for Microsoft Visual C++

To use SG-Lock the DLL SglW32.dll has to be linked to your application. This can be done dynamically by using the Win32 functions "LoadLibrary" and "GetProcAddress" or, which is much more easy, statically by using the import library SglW64.lib . To do so, you have to add this file to "project/settings/link/project options".

If you are using another C-compiler a special import library has to be generated for it. If you need help for this please contact SG-Lock.
