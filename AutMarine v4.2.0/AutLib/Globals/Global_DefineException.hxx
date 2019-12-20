#pragma once
#ifndef _Global_DefineException_Header
#define _Global_DefineException_Header

#include <Standard_OStream.hxx>
#include <Standard_String.hxx>
#include <Global_Configs.hxx>
#include <Global_Failure.hxx>
#include <Global_Macros.hxx>
#include <Standard_FileMacros.hxx>

#define DEFINE_AUT_EXCEPTION(ExceptionName) \
class ExceptionName : public AutLib::Global_Failure \
{ \
public: \
Standard_String message_; \
Standard_String location_; \
ExceptionName(std::string theMessage) : message_(theMessage) {} \
virtual void What(Standard_OStream& _ostream = cout) const \
{\
Global_Failure::What(_ostream);\
\
_ostream << message_ << "\n";\
_ostream << location_;\
}\
};

#define DEFINE_BAD_BOUNDARY_EXCEPTION(ExceptionName) \
class ExceptionName : public AutLib::Bad_Boundary_Failure \
{ \
public: \
Standard_String message_; \
Standard_String location_; \
Standard_String name_; \
Standard_String date_; \
ExceptionName(std::string theMessage) : message_(theMessage) {} \
virtual void What(Standard_OStream& _ostream = cout) const \
{\
Bad_Boundary_Failure::What(_ostream);\
\
_ostream << "Surface name : "<<name_<<"\n"; \
_ostream << " Date : "<<date_<<"\n"; \
_ostream << message_ << "\n";\
_ostream << location_;\
}\
};

#define DEFINE_BAD_SURFACE_EXCEPTION(ExceptionName) \
class ExceptionName : public AutLib::Bad_Surface_Failure \
{ \
public: \
Standard_String message_; \
Standard_String location_; \
Standard_String name_; \
Standard_String date_; \
ExceptionName(std::string theMessage) : message_(theMessage) {} \
virtual void What(Standard_OStream& _ostream = cout) const \
{\
Bad_Surface_Failure::What(_ostream);\
\
_ostream << "Surface name : "<<name_<<"\n"; \
_ostream << " Date : "<<date_<<"\n"; \
_ostream << message_ << "\n";\
_ostream << location_;\
}\
};

#define DEFINE_NONCONVERGENCY_ITERATION_EXCEPTION(ExceptionName) \
class ExceptionName : public AutLib::NonConvergency_Iteration_Failure \
{ \
public: \
Standard_String message_; \
Standard_String location_; \
Standard_String name_; \
Standard_String date_; \
ExceptionName(std::string theMessage) : message_(theMessage) {} \
virtual void What(Standard_OStream& _ostream = cout) const \
{\
NonConvergency_Iteration_Failure::What(_ostream);\
\
_ostream << "Surface name : "<<name_<<"\n"; \
_ostream << " Date : "<<date_<<"\n"; \
_ostream << message_ << "\n";\
_ostream << location_;\
}\
};

#ifdef USE_EXCEPTION
#define THROW_STANDARD_EXCEPTION(theMassage) \
{ \
DEFINE_AUT_EXCEPTION(ExceptionName) \
ExceptionName StandardException(theMassage); \
StandardException.location_ = AutLib::getSource(__FILE__, __FUNCSIG__, __LINE__);\
throw StandardException; \
}

#define THROW_BAD_BOUNDARY_EXCEPTION(theMassage) \
{ \
DEFINE_BAD_BOUNDARY_EXCEPTION(ExceptionName) \
ExceptionName BADBOUNDARY_EXCEPTION(theMassage); \
BADBOUNDARY_EXCEPTION.location_ = AutLib::getSource(__FILE__, __FUNCSIG__, __LINE__);\
BADBOUNDARY_EXCEPTION.name_ = GET_DOMAIN_NAME; \
BADBOUNDARY_EXCEPTION.date_ = AutLib::CurrentDateTime(); \
throw BADBOUNDARY_EXCEPTION; \
}

#define THROW_BAD_SURFACE_EXCEPTION(theMassage) \
{ \
DEFINE_BAD_SURFACE_EXCEPTION(ExceptionName) \
ExceptionName BADSURFACE_EXCEPTION(theMassage); \
BADSURFACE_EXCEPTION.location_ = AutLib::getSource(__FILE__, __FUNCSIG__, __LINE__);\
BADSURFACE_EXCEPTION.name_ = GET_DOMAIN_NAME; \
BADSURFACE_EXCEPTION.date_ = AutLib::CurrentDateTime(); \
throw BADSURFACE_EXCEPTION; \
}

#define THROW_NONCONVERGENCY_ITERATION_EXCEPTION(theMassage) \
{ \
DEFINE_NONCONVERGENCY_ITERATION_EXCEPTION(ExceptionName) \
ExceptionName NONCONVERGENCYException(theMassage); \
NONCONVERGENCYException.location_ = AutLib::getSource(__FILE__, __FUNCSIG__, __LINE__);\
NONCONVERGENCYException.maxNbIters_ = GET_MAXITERS;  \
NONCONVERGENCYException.resolution_ = GET_CURRENT_TOLERANCE;  \
throw NONCONVERGENCYException; \
}
#else
#define THROW_STANDARD_EXCEPTION(theMessage) {CloseProgram(theMessage);}
#define THROW_BADBOUNDARY_EXCEPTION(theMassage) {CloseProgram(theMessage);}
#define THROW_NONCONVERGENCY_ITERATION_EXCEPTION(theMassage) {CloseProgram(theMessage);}
#endif // USE_EXCEPTION

#ifdef USE_EXCEPTION
#define THROW_STANDARD_EXCEPTION_IF(CONDITION, theMassage) \
if (CONDITION) {THROW_STANDARD_EXCEPTION(theMassage)}
#elif !defined USE_EXCEPTION && defined FULLDEBUG
#define THROW_STANDARD_EXCEPTION_IF(CONDITION, theMassage) \
if (CONDITION) CloseProgram(theMessage);
#else
#define THROW_STANDARD_EXCEPTION_IF(CONDITION, MESSEGE) ((void)0)
#endif // USE_EXCEPTION

#define Error_Location_  \
    __FILE__, __FUNCSIG__, __LINE__

#define Write_Error_Location_(Stream)  \
    Stream << AutLib::Implimented(Error_Location_)

#define Write_Error_Location_GetNewLine(Stream)  \
    Stream << AutLib::Implimented(Error_Location_) _NEWLINE_

#define Exception_Handle_Exit(ExceptionObject)             \
    Open_OutputFile_txt(ExceptionOut, "Exceptions");       \
    x.What(ExceptionOut);                                  \
    _GET_NEWLINE_(ExceptionOut);                           \
    Write_Error_Location_GetNewLine(ExceptionOut);         \
    AutLib::CloseProgram(" Fatal Error")

#define Exception_Handle_BadBoundary(ExceptionObject, APP_FILENAME, PATH)                                         \
    HANDLE_CREATE_DIRECTORY                                                                                       \
    fstream ExceptionPlot3d, ExceptionPlot2d, ExceptionOut;                                                       \
    Standard_String ExceptionPlot3d_FILE_NAME, ExceptionPlot2d_FILE_NAME, ExceptionOut_FILE_NAME;                 \
    ExceptionPlot3d_FILE_NAME = PATH + "/~Exception_BadBoundary_SurfacePlot_" + APP_FILENAME + ".PLOT";           \
    ExceptionPlot2d_FILE_NAME = PATH + "/~Exception_BadBoundary_ParametericPlot_" + APP_FILENAME + ".PLOT";       \
    ExceptionOut_FILE_NAME = PATH + "/~Exception_BadBoundaryReport_" + APP_FILENAME + ".REPORT";                  \
    ExceptionPlot3d.open(ExceptionPlot3d_FILE_NAME, ios::out);                                                    \
    ExceptionPlot2d.open(ExceptionPlot2d_FILE_NAME, ios::out);                                                    \
    ExceptionOut.open(ExceptionOut_FILE_NAME, ios::out);                                                          \
    x.What(ExceptionOut);                                                                                         \
    _GET_NEWLINE_(ExceptionOut);                                                                                  \
    Write_Error_Location_GetNewLine(ExceptionOut);                                                                \
    AutLib::WarningProgram(" Invalid Boundary has been detected");                                                \
    HANDLE_BAD_BOUNDARY

#define Exception_Handle_BadSurface(ExceptionObject, APP_FILENAME, PATH)                                          \
    HANDLE_BADSURFACE_DIRECTORY                                                                                   \
    fstream BadSurfacePlot3d, BadSurfacePlot2d, BadSurfaceOut;                                                    \
    Standard_String BadSurfacePlot3d_FILE_NAME, BadSurfacePlot2d_FILE_NAME, BadSurfaceOut_FILE_NAME;              \
    BadSurfacePlot3d_FILE_NAME = PATH + "/~Exception_BadSurface_SurfacePlot_" + APP_FILENAME + ".PLOT";           \
    BadSurfacePlot2d_FILE_NAME = PATH + "/~Exception_BadSurface_ParametericPlot_" + APP_FILENAME + ".PLOT";       \
    BadSurfaceOut_FILE_NAME = PATH + "/~Exception_BadSurfaceReport_" + APP_FILENAME + ".REPORT";                  \
    BadSurfacePlot3d.open(BadSurfacePlot3d_FILE_NAME, ios::out);                                                  \
    BadSurfacePlot2d.open(BadSurfacePlot2d_FILE_NAME, ios::out);                                                  \
    BadSurfaceOut.open(BadSurfaceOut_FILE_NAME, ios::out);                                                        \
    x.What(BadSurfaceOut);                                                                                        \
    _GET_NEWLINE_(BadSurfaceOut);                                                                                 \
    Write_Error_Location_GetNewLine(BadSurfaceOut);                                                               \
    AutLib::WarningProgram(" Invalid Surface has been detected");                                                 \
    HANDLE_BAD_SURFACE

#define Exception_Handle_NONCONVERGENCY_ITERATION(ExceptionObject) \
    HANDLE_NONCONVERGENCY_ITERATION

#ifdef USE_EXCEPTION
#define Try_Exception_Handle_Exit(Expression)  \
    try {Expression;} catch(AutLib::Global_Failure &x) {Exception_Handle_Exit(x);}

#define Try_Exception_Handle_Continue(Expression)  \
    try {Expression;} catch(AutLib::Global_Failure &x) {CONTINE_EXPRESSION;}

#define Try_Exception_Handle_Bad_Boundary(Expression, APP_FILENAME, PATH)  \
    try {Expression;}  \
    catch(AutLib::Bad_Boundary_Failure &x) {Exception_Handle_BadBoundary(x, APP_FILENAME, PATH);} \
    catch(AutLib::Global_Failure &x) {Exception_Handle_Exit(x);}

#define Try_Exception_Handle_Bad_Surface(Expression, APP_FILENAME, PATH)  \
    try {Expression;}  \
    catch(AutLib::Bad_Surface_Failure &x) {Exception_Handle_BadSurface(x, APP_FILENAME, PATH);} \
    catch(AutLib::Global_Failure &x) {Exception_Handle_Exit(x);}

#define Try_Exception_Handle_Non_Convergency_Iteration(Expression)  \
   try {Expression;}  \
   catch(AutLib::NonConvergency_Iteration_Failure &x) {Exception_Handle_NONCONVERGENCY_ITERATION(x);}  \
   catch(AutLib::Global_Failure &x) {Exception_Handle_Exit(x);}
#else
#define Try_Exception_Handle_Exit(Expression) Expression;
#define Try_Exception_Handle_Bad_Boundary(Expression, APP_FILENAME) Expression;
#define Try_Exception_Handle_Non_Convergency_Iteration(Expression) Expression;
#define Try_Exception_Handle_Bad_Surface(Expression, APP_FILENAME, PATH) Expression;
#endif // USE_EXCEPTION

#ifdef USE_EXCEPTION
#define Try_Exception_Handle_ReThrow(Expression)  \
    try {Expression;} catch(AutLib::Global_Failure) {throw;} catch(AutLib::Bad_Boundary_Failure) {throw;} catch(AutLib::Bad_Surface_Failure) {throw;} catch(AutLib::NonConvergency_Iteration_Failure) {throw;}
#else
#define Try_Exception_Handle_ReThrow(Expression) Expression;
#endif // USE_EXCEPTION

#endif // !_Global_DefineException_Header
