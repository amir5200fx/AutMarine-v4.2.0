#pragma once
#ifndef _Cad3d_WireOnPlane_Header
#define _Cad3d_WireOnPlane_Header

#include <Entity_Box2d.hxx>
#include <Cad3d_WireOnPlaneOrientationInfo.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad3d_HAry1dOfPointOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_WireOnPlane
		{

		private:

			TColCad3d_HAry1dOfEdgeOnPlane theEdges_;

			Standard_Integer theIndex_;

			Cad3d_WireOnPlaneOrientationInfo theOrientation_;

			M_GEO Entity_Box2d theBox_;

		public:

			Cad3d_WireOnPlane();

			Cad3d_WireOnPlane(const Standard_Integer theIndex, const Global_Handle(Cad3d_EdgeOnPlane) theEdge);

			Cad3d_WireOnPlane(const Standard_Integer theIndex, const TColCad3d_HAry1dOfEdgeOnPlane& theEdges);

			virtual ~Cad3d_WireOnPlane();

			void Init(const Standard_Integer theIndex, const TColCad3d_HAry1dOfEdgeOnPlane& theEdges);

			void SetIndex(const Standard_Integer theIndex);

			void SetOrientation(const Cad3d_WireOnPlaneOrientationInfo& theOrientation);

			void Reverse();

			Standard_Integer Index() const;

			Standard_Integer MaxEdgeIndex() const;

			Standard_Integer MaxPointIndex() const;

			Cad3d_WireOnPlaneOrientationInfo Orientation() const;

			const TColCad3d_HAry1dOfEdgeOnPlane& Edges() const;

			const M_GEO Entity_Box2d& BoundingBox() const;

			void RetrievePointsTo(TColCad3d_HAry1dOfPointOnPlane& thePoints) const;

			void ExportToPlt(fstream& File) const;

			//virtual Global_Handle(Cad3d_WireOnPlane) Copy() const;

		private:

			void CalcBoundingBox();
		};
	}
}

#include <Cad3d_WireOnPlaneI.hxx>

#endif // !_Cad3d_WireOnPlane_Header
