#pragma once
#ifndef _Mesh2d_StdBackSize_Header
#define _Mesh2d_StdBackSize_Header

#include <SizeMap2d_UniSize.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_StdBackSize : public SizeMap2d_UniSize
		{

		private:

			const M_GEO GeoMesh_BackGroundMesh2d& theMesh_;

		public:

			SizeMap2d_StdBackSize(const Standard_Real BaseSize, const M_GEO GeoMesh_BackGroundMesh2d& BackGround);

			virtual Standard_Real ElementSize(const Geom_Pnt2d& Coord) const;

			virtual Standard_Real ElementSize(const Mesh2d_Edge& Edge) const;

			virtual Standard_Real CalcUnitDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual Standard_Real Integrand(const Geom_Pnt2d& Point, const Geom_Pnt2d& Vector) const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <SizeMap2d_StdBackSizeI.hxx>

#endif // !_Mesh2d_StdBackSize_Header
