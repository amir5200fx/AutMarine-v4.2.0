#pragma once
#ifndef _Cad2d_WireOnPlane_Header
#define _Cad2d_WireOnPlane_Header

#include <Entity_Box2d.hxx>
#include <Cad2d_WireOnPlaneOrientationInfo.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>

namespace AutLib
{

	namespace GeoLib
	{
		class Entity_Box2d;
	}

	namespace CadLib
	{

		class Cad2d_WireOnPlane
		{

		protected:

			TColCad2d_HAry1dOfEdgeOnPlane theEdges_;

			Standard_Integer theIndex_;

			Cad2d_WireOnPlaneOrientationInfo theOrientation_;

			M_GEO Entity_Box2d theBox_;

		public:

			Cad2d_WireOnPlane();

			Cad2d_WireOnPlane(const Standard_Integer theIndex, const Global_Handle(Cad2d_EdgeOnPlane) theEdge);

			Cad2d_WireOnPlane(const Standard_Integer theIndex, const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);

			virtual ~Cad2d_WireOnPlane();

			void Init(const Standard_Integer theIndex, const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);

			void SetIndex(const Standard_Integer theIndex);

			void SetOrientation(const Cad2d_WireOnPlaneOrientationInfo& theOrientation);

			void Reverse();

			Standard_Integer Index() const;

			Standard_Integer MaxEdgeIndex() const;

			Standard_Integer MaxPointIndex() const;

			Cad2d_WireOnPlaneOrientationInfo Orientation() const;

			const TColCad2d_HAry1dOfEdgeOnPlane& Edges() const;

			const M_GEO Entity_Box2d& BoundingBox() const;

			void RetrievePointsTo(TColCad2d_HAry1dOfPointOnPlane& thePoints) const;

			void ExportToPlt(fstream& File) const;

			virtual Global_Handle(Cad2d_WireOnPlane) Copy() const;

		private:

			void CalcBoundingBox();
		};
	}
}

#include <Cad2d_WireOnPlaneI.hxx>

#endif // !_Cad2d_WireOnPlane_Header
