#pragma once
#ifndef _Cad3d_PointOnPlane_Header
#define _Cad3d_PointOnPlane_Header

#include <Global_Memory.hxx>
#include <Geom_Pnt2d.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad3d_HNumbAvlTreeOfEdgeOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_EdgeOnPlane;

		class Cad3d_PointOnPlane
		{

		protected:

			Geom_Pnt2d theCoord_;

			Standard_Integer theIndex_;

			TColCad3d_HNumbAvlTreeOfEdgeOnPlane theEdges_;

		public:

			Cad3d_PointOnPlane();

			Cad3d_PointOnPlane(const Standard_Integer theIndex, const Geom_Pnt2d& theCoord);

			~Cad3d_PointOnPlane();

			Standard_Integer NbEdges() const;

			Standard_Integer Index() const;

			Standard_Boolean IsFree() const;

			Standard_Boolean IsOrphan() const;

			Standard_Boolean IsRingPoint() const;

			const Geom_Pnt2d& Coord() const;

			void ImportEdge(const Global_Handle(Cad3d_EdgeOnPlane) theEdge);

			void SetIndex(const Standard_Integer theIndex);

			void SetCoord(const Geom_Pnt2d& theCoord);

			void RetrieveEdgesTo(TColCad3d_HAry1dOfEdgeOnPlane& theEdges) const;

			void ExportToPlt(fstream& File) const;

			Global_Handle(Cad3d_PointOnPlane) Copy() const;
		};
	}
}

#include <Cad3d_PointOnPlaneI.hxx>

#endif // !_Cad3d_PointOnPlane_Header
