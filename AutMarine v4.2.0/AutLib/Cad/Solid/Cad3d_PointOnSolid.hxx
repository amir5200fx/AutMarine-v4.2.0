#pragma once
#ifndef _Cad3d_PointOnSolid_Header
#define _Cad3d_PointOnSolid_Header

#include <Geom_Pnt3d.hxx>
#include <Cad3d_EntityOnSolid.hxx>
#include <TColCad3d_HNumbAvlTreeOfEdgeOnSolid.hxx>
#include <TColCad3d_HNumbAvlTreeOfSurfaceOnSolid.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSolid.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>

namespace AutLib
{
	namespace CadLib
	{
		class Cad3d_EdgeOnSolid;
		class Cad3d_SurfaceOnSolid;

		class Cad3d_PointOnSolid : public Cad3d_EntityOnSolid
		{

		private:

			Geom_Pnt3d theCoord_;

			TColCad3d_HNumbAvlTreeOfEdgeOnSolid theEdges_;

			TColCad3d_HNumbAvlTreeOfSurfaceOnSolid theSurfaces_;

		public:

			Cad3d_PointOnSolid();

			Cad3d_PointOnSolid(const Standard_Integer Index, const Geom_Pnt3d& Coord);

			virtual ~Cad3d_PointOnSolid();

			Standard_Integer NbEdges() const;

			Standard_Integer NbSurfaces() const;

			const Geom_Pnt3d& Coord() const;

			//! Throw an exception if duplicate data has been detected
			void InsertToEdges(Global_Handle(Cad3d_EdgeOnSolid) Edge);

			//! Throw an exception if duplicate data has been detected
			void InsertToSurfaces(Global_Handle(Cad3d_SurfaceOnSolid) Surface);

			void InsertToSurfacesIgnoreDup(Global_Handle(Cad3d_SurfaceOnSolid) Surface);

			void SetCoord(const Geom_Pnt3d& Coord);

			void RetrieveEdgesTo(TColCad3d_HAry1dOfEdgeOnSolid& Edges) const;

			void RetrieveSurfacesTo(TColCad3d_HAry1dOfSurfaceOnSolid& Surfaces) const;

			virtual void ExportToPlt(fstream& File) const {}
		};
	}
}

#include <Cad3d_PointOnSolidI.hxx>

#endif // !_Cad3d_PointOnSolid_Header
