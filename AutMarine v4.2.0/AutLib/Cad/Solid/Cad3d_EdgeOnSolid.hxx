#pragma once
#ifndef _Cad3d_EdgeOnSolid_Header
#define _Cad3d_EdgeOnSolid_Header

#include <Global_Memory.hxx>
#include <Standard_Type.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_PointOnSolid;
		class Cad3d_CurveOnPlane;
		class Cad3d_CurveOnSurface;
		class Cad3d_SurfaceOnSolid;
		class Cad3d_PairedOnSolid;

		class Cad3d_EdgeOnSolid
		{

		private:

			Global_Handle(Cad3d_CurveOnPlane) theCurveOnPlane_;

			Global_Handle(Cad3d_CurveOnSurface) theCurveOnSurface_;

			Standard_Integer theIndex_;

			const Global_Handle(Cad3d_SurfaceOnSolid) theSurface_;

			const Global_Handle(Cad3d_EdgeOnSolid) thePaired_;

			const Global_Handle(Cad3d_PointOnSolid) theP0_;
			const Global_Handle(Cad3d_PointOnSolid) theP1_;

			const Global_Handle(Cad3d_PairedOnSolid) thePairedOnSolid_;

		public:

			Cad3d_EdgeOnSolid();

			Cad3d_EdgeOnSolid(const Standard_Integer Index, Global_Handle(Cad3d_CurveOnPlane) theCurveOnPlane, Global_Handle(Cad3d_CurveOnSurface) theCurveOnSurface, const Global_Handle(Cad3d_SurfaceOnSolid) theSurface);

			~Cad3d_EdgeOnSolid();

			Standard_Boolean IsDegenerate() const;

			Standard_Integer Index() const;

			const Global_Handle(Cad3d_CurveOnPlane) CurveOnPlane() const;

			const Global_Handle(Cad3d_CurveOnSurface) CurveOnSurface() const;

			const Global_Handle(Cad3d_SurfaceOnSolid) Surface() const;

			const Global_Handle(Cad3d_EdgeOnSolid) Paired() const;

			const Global_Handle(Cad3d_PairedOnSolid) PairedOnSolid() const;

			const Global_Handle(Cad3d_PointOnSolid) StartPoint() const;

			const Global_Handle(Cad3d_PointOnSolid) LastPoint() const;

			void Init(const Standard_Integer Index, Global_Handle(Cad3d_CurveOnPlane) theCurveOnPlane, Global_Handle(Cad3d_CurveOnSurface) theCurveOnSurface, const Global_Handle(Cad3d_SurfaceOnSolid) theSurface);

			void SetIndex(const Standard_Integer Index);

			void SetStart(const Global_Handle(Cad3d_PointOnSolid) theStartPoint);

			void SetLast(const Global_Handle(Cad3d_PointOnSolid) theLastPoint);

			void SetEdgeOnPlane(Global_Handle(Cad3d_CurveOnPlane) theCurveOnPlane);

			void SetEdgeOnSurface(Global_Handle(Cad3d_CurveOnSurface) theCurveOnSurface);

			void SetSurface(const Global_Handle(Cad3d_SurfaceOnSolid) theSurface);

			void SetPaired(const Global_Handle(Cad3d_EdgeOnSolid) thePaired);

			void SetPairedOnSolid(const Global_Handle(Cad3d_PairedOnSolid) thePairedOnSolid);

			void Reverse();

			void ExportParametricCurvesToPlt(fstream& File) const;

			void ExportToPlt(fstream& File) const;

			void PrintEnds(Standard_OStream& Ostream = cout) const;

		private:

			void ReleaseMemory();
		};
	}
}

#include <Cad3d_EdgeOnSolidI.hxx>

#endif // !_Cad3d_EdgeOnSolid_Header
