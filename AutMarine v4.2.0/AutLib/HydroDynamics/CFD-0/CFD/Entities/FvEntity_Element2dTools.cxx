#include <FvEntity_Element2dTools.hxx>

#include <Geometry_Tools.hxx>
#include <FvEntity_Node2d.hxx>
#include <FvEntity_Element2d.hxx>
#include <FvEntity_TriElement2d.hxx>
#include <FvEntity_QuadElement2d.hxx>
#include <FvEntity_PolyElement2d.hxx>

using namespace AutLib;
using namespace FvLib;
using namespace GeoLib;

namespace AutLib
{
	namespace FvLib
	{

		static Standard_Real CalcVolume(const FvEntity_TriElement2d& theElement)
		{
			Get_Const_Object(Node0) = *theElement.Node(0);
			Get_Const_Object(Node1) = *theElement.Node(1);
			Get_Const_Object(Node2) = *theElement.Node(2);

			return Geometry_Tools::AreaOfTriangle(Node0.Coord(), Node1.Coord(), Node2.Coord());
		}

		static Standard_Real CalcVolume(const FvEntity_QuadElement2d& theElement)
		{
			Get_Const_Object(Node0) = *theElement.Node(0);
			Get_Const_Object(Node1) = *theElement.Node(1);
			Get_Const_Object(Node2) = *theElement.Node(2);
			Get_Const_Object(Node3) = *theElement.Node(3);

			Standard_Real Volume0 = Geometry_Tools::AreaOfTriangle(Node0.Coord(), Node1.Coord(), Node2.Coord());
			Standard_Real Volume1 = Geometry_Tools::AreaOfTriangle(Node2.Coord(), Node3.Coord(), Node0.Coord());

			return Volume0 + Volume1;
		}

		static Standard_Real CalcVolume(const FvEntity_PolyElement2d& theElement)
		{
			Standard_Real Sum = 0;
			forThose
			(
				Index,
				0, 
				theElement.NbNodes() - 3
			)
			{
				Standard_Integer V0 = 0;
				Standard_Integer V1 = Index + 1;
				Standard_Integer V2 = V1 + 1;

				Get_Const_Object(Node0) = *theElement.Node(V0);
				Get_Const_Object(Node1) = *theElement.Node(V1);
				Get_Const_Object(Node2) = *theElement.Node(V2);

				Sum += Geometry_Tools::AreaOfTriangle(Node0.Coord(), Node1.Coord(), Node2.Coord());
			}
			return Sum;
		}

		static Standard_Real CalcVolume(const FvEntity_Element2d& theElement)
		{
			Global_Handle(FvEntity_TriElement2d) TriElement = Global_DownCast(FvEntity_TriElement2d, (Global_Handle(FvEntity_Element2d))&theElement);
			if (TriElement) { return CalcVolume(*TriElement); }

			Global_Handle(FvEntity_QuadElement2d) QuadElement = Global_DownCast(FvEntity_QuadElement2d, (Global_Handle(FvEntity_Element2d))&theElement);
			if (QuadElement) { return CalcVolume(*QuadElement); }

			Global_Handle(FvEntity_PolyElement2d) PolyElement = Global_DownCast(FvEntity_PolyElement2d, (Global_Handle(FvEntity_Element2d))&theElement);
			if (PolyElement) { return CalcVolume(*PolyElement); }
		}

		static Geom_Pnt2d CalcCentre(const FvEntity_Element2d& theElement)
		{
			Geom_Pnt2d Centre(0, 0);
			forThose(Index, 0, theElement.NbNodes() - 1)
			{
				Debug_Null_Pointer(theElement.Node(Index));
				Centre += theElement.Node(Index)->Coord();
			}
			return Centre / (Standard_Real)theElement.NbNodes();
		}
	}
}

void AutLib::FvLib::FvEntity_Element2dTools::CalcGeometry(FvEntity_Element2d & theElement)
{
	theElement.SetVolume(CalcVolume(theElement));

	theElement.SetCentre(CalcCentre(theElement));
}