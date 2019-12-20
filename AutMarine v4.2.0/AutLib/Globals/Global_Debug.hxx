#pragma once
#ifndef _Global_Debug_Header
#define _Global_Debug_Header

#include <Global_DefineException.hxx>

#ifdef _DEBUG
#define FULLDEBUG
#endif // _DEBUG
#define FULLDEBUG
#undef FULLDEBUG
#ifdef FULLDEBUG
#define Debug(theStatements)  \
    {theStatements}
#else
#define Debug(theStatements) ((void)0)
#endif // FULLDEBUG

#ifdef FULLDEBUG
#define Debug_Null_Pointer(Pointer) \
  Debug(if(!Pointer){Write_Error_Location_GetNewLine(cout); AutLib::CloseProgram(" Empty Pointer");})
#else
#define Debug_Null_Pointer(Pointer) ((void)0)
#endif // FULLDEBUG

#ifdef FULLDEBUG
#define Debug_If_Condition(theCondition)  \
  Debug(if(theCondition) {Write_Error_Location_GetNewLine(cout); AutLib::CloseProgram(" The Condition Is not Satisfied");})
#else
#define Debug_If_Condition(theCondition)  ((void)0)
#endif // FULLDEBUG

#ifdef FULLDEBUG
#define Debug_If_Condition_Message(theCondition, theMessage)  \
  Debug(if(theCondition) {Write_Error_Location_GetNewLine(cout); AutLib::CloseProgram(theMessage);})
#else
#define Debug_If_Condition_Message(theCondition, theMessage)  ((void)0)
#endif // FULLDEBUG

#ifdef FULLDEBUG
#define Debug_Bad_Index(INDEX, MinIndex, MaxIndex)  \
  Debug(IF_NOT_INSIDE(INDEX, MinIndex, MaxIndex){Write_Error_Location_GetNewLine(cout); AutLib::CloseProgram(" Bad Subscript");})
#else
#define Debug_Bad_Index(INDEX, MinIndex, MaxIndex)  ((void)0)
#endif // FULLDEBUG

#ifdef FULLDEBUG
#define Debug_Bad_Index_Array1(INDEX, Array1)  \
  Debug(IF_NOT_INSIDE(INDEX, 0, MaxIndexOf(Array1)){Write_Error_Location_GetNewLine(cout); AutLib::CloseProgram(" Bad Subscript");})
#else
#define Debug_Bad_Index_Array1(INDEX, Array1)  ((void)0)
#endif // FULLDEBUG

#ifdef FULLDEBUG
#define Debug_Bad_Index_Array2(INDEX1, INDEX2, Array2)  \
  Debug(IF_NOT_INSIDE2(INDEX1, INDEX2, 0, Array2.Size(0) - 1, 0, Array2.Size(1) - 1){Write_Error_Location_GetNewLine(cout); AutLib::CloseProgram(" Bad Subscript");}) 
#else
#define Debug_Bad_Index_Array2(INDEX1, INDEX2, Array2)  ((void)0)
#endif // FULLDEBUG

#endif // !_Global_Debug_Header
