#include <Model2d_Naca4DigitParameters.hxx>

#include <Global_Macros.hxx>
#include <Global_DefineException.hxx>

static const Standard_Real DEFAULT_CHORD = 1.0;
static const Standard_Real DEFAULT_MAX_CAMBER = 0.0;
static const Standard_Real DEFAULT_MAX_CAMBER_POSITION = 40.0;
static const Standard_Real DEFAULT_MAX_THICKNESS = 10.0;

static const Standard_Real UPPER_MAX_CAMBER = 9.5;
static const Standard_Real LOWER_MAX_CAMBER = 0.0;
static const Standard_Real UPPER_MAX_CAMBER_POSITION = 90.0;
static const Standard_Real LOWER_MAX_CAMBER_POSITION = 0.0;
static const Standard_Real UPPER_MAX_THICKNESS = 40.0;
static const Standard_Real LOWER_MAX_THICKNESS = 1.0;

AutLib::CadLib::Model2d_Naca4DigitParameters::Model2d_Naca4DigitParameters()
	: theChord_(DEFAULT_CHORD)
	, theMaxCamber_(DEFAULT_MAX_CAMBER)
	, theMaxCamberPosition_(DEFAULT_MAX_CAMBER_POSITION)
	, theMaxThickness_(DEFAULT_MAX_THICKNESS)
{
}

void AutLib::CadLib::Model2d_Naca4DigitParameters::Init
(
	const Standard_Real Chord,
	const Standard_Real MaxCamber,
	const Standard_Real MaxCamberPosition,
	const Standard_Real MaxThickness
)
{
	if (Chord <= 0.0) THROW_STANDARD_EXCEPTION(" Invalid chord length");
	if (NOT INSIDE(MaxCamber, LOWER_MAX_CAMBER, UPPER_MAX_CAMBER)) THROW_STANDARD_EXCEPTION(" Invalid MaxCamber");
	if (NOT INSIDE(MaxCamberPosition, LOWER_MAX_CAMBER_POSITION, UPPER_MAX_CAMBER_POSITION)) THROW_STANDARD_EXCEPTION(" Invalid MaxCamber_Position");
	if (NOT INSIDE(MaxThickness, LOWER_MAX_THICKNESS, UPPER_MAX_THICKNESS)) THROW_STANDARD_EXCEPTION(" Invalid MaxThickness");

	theChord_ = Chord;
	theMaxCamber_ = MaxCamber;
	theMaxCamberPosition_ = MaxCamberPosition;
	theMaxThickness_ = MaxThickness;
}

void AutLib::CadLib::Model2d_Naca4DigitParameters::SetChord(const Standard_Real Chord)
{
	if (Chord <= 0.0) THROW_STANDARD_EXCEPTION(" Invalid chord length");
	theChord_ = Chord;
}

void AutLib::CadLib::Model2d_Naca4DigitParameters::SetMaxCamber(const Standard_Real MaxCamber)
{
	if (NOT INSIDE(MaxCamber, LOWER_MAX_CAMBER, UPPER_MAX_CAMBER)) THROW_STANDARD_EXCEPTION(" Invalid MaxCamber");
	theMaxCamber_ = MaxCamber;
}

void AutLib::CadLib::Model2d_Naca4DigitParameters::SetMaxCamberPosition(const Standard_Real MaxCamberPosition)
{
	if (NOT INSIDE(MaxCamberPosition, LOWER_MAX_CAMBER_POSITION, UPPER_MAX_CAMBER_POSITION)) THROW_STANDARD_EXCEPTION(" Invalid MaxCamber_Position");
	theMaxCamberPosition_ = MaxCamberPosition;
}

void AutLib::CadLib::Model2d_Naca4DigitParameters::SetMaxThickness(const Standard_Real MaxThickness)
{
	if (NOT INSIDE(MaxThickness, LOWER_MAX_THICKNESS, UPPER_MAX_THICKNESS)) THROW_STANDARD_EXCEPTION(" Invalid MaxThickness");
	theMaxThickness_ = MaxThickness;
}