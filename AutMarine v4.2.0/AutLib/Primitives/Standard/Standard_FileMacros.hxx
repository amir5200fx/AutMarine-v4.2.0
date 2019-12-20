#pragma once
#ifndef _FileMarcros_Header
#define _FileMarcros_Header

#include <fstream>

#define Open_OutputFile_txt(Stream, FileName)   \
   std::fstream Stream;                         \
   Stream.open(FileName##".txt", std::ios::out)

#define Open_OutputFile_txt_App(Stream, FileName)                 \
   std::fstream Stream;                                           \
   Stream.open(FileName##".txt", std::ios::trunc | std::ios::app)

#define Open_OutputFile_txt_read(Stream, FileName)           \
   std::fstream Stream;                                      \
   Stream.open(FileName##".txt", std::ios::in);              \
   if(Stream.fail()){CloseProgram(" Failed to open File");}

#define Open_OutputFile_igs_read(Stream, FileName)           \
   std::fstream Stream;                                      \
   Stream.open(FileName##".igs", std::ios::in);              \
   if(Stream.fail()){CloseProgram(" Failed to open File");}

#define Open_OutputFile_TecPlot(Stream, FileName)   \
   std::fstream Stream;                             \
   Stream.open(FileName##".plt", std::ios::out)

#define Open_OutputFile_TecPlot_App(Stream, FileName)              \
   std::fstream Stream;                                            \
   Stream.open(FileName##".plt", std::ios::trunc | std::ios::app)

#endif // !_FileMarcros_H