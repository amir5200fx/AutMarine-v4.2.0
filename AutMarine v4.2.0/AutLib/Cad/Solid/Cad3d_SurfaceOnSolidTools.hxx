#pragma once
#ifndef _Cad3d_SurfaceOnSolidTools_Header
#define _Cad3d_SurfaceOnSolidTools_Header

#include <Cad3d_SurfaceOnSolid.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>

class TopoDS_Face;

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box3d;
		class Entity_Triangulation3d;
	}

	namespace CadLib
	{

		class Cad3d_SurfaceOnSolidTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad3d_SurfaceOnSolid) const &theSurface1, Global_Handle(Cad3d_SurfaceOnSolid) const &theSurface2);

			//! Throw an exception if the surface list is empty
			static GeoLib::Entity_Box3d BoundingBoxOf(const TColCad3d_HAry1dOfSurfaceOnSolid& Surfaces, const Standard_Real Offset = 0.0);

			static Global_Handle(GeoLib::Entity_Triangulation3d) TriangulationOf(const TopoDS_Face& theFace);

			static Standard_Boolean CheckForConfomity(const Cad3d_SurfaceOnSolid& theSurface, const Standard_Real Tolerance);

			static Standard_Boolean CheckForConfomityWithDirection(const Cad3d_SurfaceOnSolid& theSurface, const Standard_Real Tolerance);

			static Global_Handle(Cad3d_SurfaceOnSolid) RepairNonConfomityOfBoundaries(const Cad3d_SurfaceOnSolid& theSurface, const Standard_Real Tolerance);

			static TopoDS_Face Make_TopoDS_Face(const Cad3d_SurfaceOnSolid& theSurface, const Standard_Real theTolerance = 1.0E-6);

			static Global_Handle(Cad3d_SurfaceOnSolid) GetSurfaceOnSolid(const TopoDS_Face& theFace);
		};
	}
}

#include <Cad3d_SurfaceOnSolidToolsI.hxx>

#endif // !_Cad3d_SurfaceOnSolidTools_Header
