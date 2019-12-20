#include <Cad2d_SketchMaxCoords.hxx>

static const Standard_Real DEFAULT_MAXCOORD = 1.0E6;
static const Standard_Real DEFAULT_MINCOORD = -1.0E6;

Standard_Real AutLib::CadLib::Cad2d_SketchMaxCoords::MaxXCoord()
{
	return DEFAULT_MAXCOORD;
}

Standard_Real AutLib::CadLib::Cad2d_SketchMaxCoords::MaxYCoord()
{
	return DEFAULT_MAXCOORD;
}

Standard_Real AutLib::CadLib::Cad2d_SketchMaxCoords::MinXCoord()
{
	return DEFAULT_MINCOORD;
}

Standard_Real AutLib::CadLib::Cad2d_SketchMaxCoords::MinYCoord()
{
	return DEFAULT_MINCOORD;
}