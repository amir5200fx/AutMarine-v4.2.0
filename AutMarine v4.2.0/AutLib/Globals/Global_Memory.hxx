#pragma once
#ifndef _Global_Memory_Header
#define _Global_Memory_Header

#define Global_Handle(_Pointer) _Pointer*

#define Global_NullHandle(_Type) Global_Handle(_Type) _Pointer(0)

#define Global_DownCast(Class, Object) \
   dynamic_cast<Class*>(Object)

#define FreePointer(_Pointer)  \
   if(_Pointer)  {delete _Pointer; _Pointer = NULL;}

#define FreeMemory(_Array)  \
  forThose(Index, 0, MaxIndexOf(_Array))  \
   {FreePointer((_Array)[Index]);}

#endif // !_Global_Memory_Header
