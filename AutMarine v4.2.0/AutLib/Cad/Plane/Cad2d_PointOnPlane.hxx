#pragma once
#ifndef _Cad2d_PointOnPlane_Header
#define _Cad2d_PointOnPlane_Header

#include <Geom_Pnt2d.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad2d_HNumbAvlTreeOfEdgeOnPlane.hxx>

class gp_Pnt2d;
class gp_Vec2d;
class gp_Ax22d;
class gp_Ax2d;
class gp_Trsf2d;

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_EdgeOnPlane;
		class Cad2d_PointOnPlane
		{

		private:

			Geom_Pnt2d theCoord_;

			Standard_Integer theIndex_;

			TColCad2d_HNumbAvlTreeOfEdgeOnPlane theEdges_;

		public:

			Cad2d_PointOnPlane();

			Cad2d_PointOnPlane(const Standard_Integer theIndex, const Geom_Pnt2d& theCoord);

			~Cad2d_PointOnPlane();

			Standard_Integer NbEdges() const;

			Standard_Integer Index() const;

			Standard_Boolean IsFree() const;

			Standard_Boolean IsOrphan() const;

			Standard_Boolean IsRingPoint() const;

			Standard_Boolean IsManifold() const;

			Standard_Boolean IsSharp(const Standard_Real theRadianAngle) const;

			const Geom_Pnt2d& Coord() const;

			void RetrieveEdgesTo(TColCad2d_HAry1dOfEdgeOnPlane& theEdges) const;

			void ImportEdge(const Global_Handle(Cad2d_EdgeOnPlane) theEdge);

			void SetIndex(const Standard_Integer theIndex);

			void SetCoord(const Geom_Pnt2d& theCoord);

			void ExportToPlt(fstream& File) const;

			void Mirror(const gp_Pnt2d& P);

			void Mirror(const gp_Ax2d& A);

			void Rotate(const gp_Pnt2d& P, const Standard_Real Ang);

			void Scale(const gp_Pnt2d& P, const Standard_Real S);

			void Translate(const gp_Vec2d& V);

			void Translate(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

			void Transform(const gp_Trsf2d& T);

			Global_Handle(Cad2d_PointOnPlane) Copy() const;
		};
	}
}

#include <Cad2d_PointOnPlaneI.hxx>

#endif // !_Cad2d_PointOnPlane_Header
