#pragma once
#ifndef _Cad3d_SolidTools_Header
#define _Cad3d_SolidTools_Header

#include <Standard_String.hxx>
#include <Standard_Stream.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>
#include <TColEntity_HAry1dOfTriangulation3d.hxx>

class TopoDS_Shape;
class TopoDS_Face;
class TopoDS_Solid;

#include <TopAbs_Orientation.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_Solid;
		class Cad3d_SolidTools
		{

		public:

			static Standard_Integer NbOfSurfaces(const TopoDS_Shape& theShape);

			static TColCad3d_HAry1dOfSurfaceOnSolid GetSurfaces(const TopoDS_Shape& theShape);

			static TColEntity_HAry1dOfTriangulation3d GetTriangulations(const TopoDS_Shape& theShape);

			static TopoDS_Shape Make_TopoDS_Shape(const Cad3d_Solid& theSolid, const Standard_Real theTolerance);

			static TopoDS_Shape GetSolid(const TopoDS_Shape& theShape, const TopAbs_Orientation theOrientation);

			static TopoDS_Shape ReplaceFace(const TopoDS_Shape& Shape, const TopoDS_Face& Face);

			static TopoDS_Shape CheckOrientation(const TopoDS_Shape & theShape);

			static TopoDS_Shape RepairWithIGES(const TopoDS_Shape & theShape);

			static void MakeSolid(const TopoDS_Shape& theShape, Cad3d_Solid& theSolid);

			static void ConformBoundaries(const Cad3d_Solid& theUnConformed, Cad3d_Solid& theConformed, const Standard_Real theTolerance = 1.0E-4);

			static void ExportToPlt(const TopoDS_Shape& theShape, fstream& File);

			static void ExportToIGES(const TopoDS_Shape& theShape, const Standard_String FileName);

			static void Triangulation(const TopoDS_Shape& theShape, const Standard_Real theDeflection = 0.1, const Standard_Real theAngle = 1.0);
		};
	}
}

#endif // !_Cad3d_SolidTools_Header
