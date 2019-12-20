#include <FvGeom_Element2d.hxx>

#include <Global_Debug.hxx>
#include <FvGeom_TriConnectivity2d.hxx>
#include <FvGeom_QuadConnectivity2d.hxx>
#include <FvGeom_GeneralConnectivity2d.hxx>

AutLib::FvLib::FvGeom_Element2d::FvGeom_Element2d()
{
}

AutLib::FvLib::FvGeom_Element2d::~FvGeom_Element2d()
{
	FreePointer(theConnectivity_);
}

namespace AutLib
{
	namespace FvLib
	{

		static Global_Handle(FvGeom_ElementConnectivity2d) ReadConnectivity(const FvGeom_ElementType theType, fstream& File)
		{
			Global_Handle(FvGeom_ElementConnectivity2d) newElement;
			switch (theType)
			{
			case FvGeom_ElementType_Triangle:
			{
				newElement = new FvGeom_TriConnectivity2d;
				newElement->Import(File);
				return newElement;
			}
			case FvGeom_ElementType_Quadrangle:
			{
				newElement = new FvGeom_QuadConnectivity2d;
				newElement->Import(File);
				return newElement;
			}
			case FvGeom_ElementType_Polygon:
			{
				newElement = new FvGeom_GeneralConnectivity2d;
				newElement->Import(File);
				return newElement;
			}
			default: THROW_STANDARD_EXCEPTION("The Element Type not implemented yet.");
			}
		}
	}
}

void AutLib::FvLib::FvGeom_Element2d::Import(fstream & File)
{
	Standard_Integer type;

	File >> theIndex_ >> type;

	switch (type)
	{
	case FvGeom_ElementType_Line: {theType_ = FvGeom_ElementType_Line; break; }
	case FvGeom_ElementType_Hexahedron: {theType_ = FvGeom_ElementType_Hexahedron; break; }
	case FvGeom_ElementType_Point: {theType_ = FvGeom_ElementType_Point; break; }
	case FvGeom_ElementType_Polygon: {theType_ = FvGeom_ElementType_Polygon; break; }
	case FvGeom_ElementType_Polyhedral: {theType_ = FvGeom_ElementType_Polyhedral; break; }
	case FvGeom_ElementType_Prism: {theType_ = FvGeom_ElementType_Prism; break; }
	case FvGeom_ElementType_Pyramid: {theType_ = FvGeom_ElementType_Pyramid; break; }
	case FvGeom_ElementType_Quadrangle: {theType_ = FvGeom_ElementType_Quadrangle; break; }
	case FvGeom_ElementType_Second_Line: {theType_ = FvGeom_ElementType_Second_Line; break; }
	case FvGeom_ElementType_Second_Tetrahedron: {theType_ = FvGeom_ElementType_Second_Tetrahedron; break; }
	case FvGeom_ElementType_Second_Triangle: {theType_ = FvGeom_ElementType_Second_Triangle; break; }
	case FvGeom_ElementType_Tetrahedron: {theType_ = FvGeom_ElementType_Tetrahedron; break; }
	case FvGeom_ElementType_Triangle: {theType_ = FvGeom_ElementType_Triangle; break; }
	default: {THROW_STANDARD_EXCEPTION("Unknown Element Type"); }
	}

	theConnectivity_ = ReadConnectivity(theType_, File);

	File >> thePhysics_;
}