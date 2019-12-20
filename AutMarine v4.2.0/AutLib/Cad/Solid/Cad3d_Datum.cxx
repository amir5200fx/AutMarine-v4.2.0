#include <Cad3d_Datum.hxx>

AutLib::CadLib::Cad3d_Datum::Cad3d_Datum()
{
}

AutLib::CadLib::Cad3d_Datum::Cad3d_Datum
(
	const Geom_Pnt3d & theCoord, 
	const Standard_String theName
)
	: theCoord_(theCoord)
	, theName_(theName)
{
}

void AutLib::CadLib::Cad3d_Datum::Init
(
	const Geom_Pnt3d & theCoord,
	const Standard_String theName
)
{
	theCoord_ = theCoord;
	theName_ = theName;
}

void AutLib::CadLib::Cad3d_Datum::SetCoord(const Geom_Pnt3d & theCoord)
{
	theCoord_ = theCoord;
}

void AutLib::CadLib::Cad3d_Datum::SetName(const Standard_String theName)
{
	theName_ = theName;
}

void AutLib::CadLib::Cad3d_Datum::Transform(const gp_Trsf & theTrsf)
{
	theCoord_.Transform(theTrsf);
}