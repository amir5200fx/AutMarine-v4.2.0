#pragma once
#ifndef _SizeMap3d_StdBackSize_Header
#define _SizeMap3d_StdBackSize_Header

#include <SizeMap3d_UniSize.hxx>
#include <GeoMesh_BackGroundMesh3d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_StdBackSize : public SizeMap3d_UniSize
		{

		protected:

			const M_GEO GeoMesh_BackGroundMesh3d& theMesh_;

		public:

			SizeMap3d_StdBackSize(const Standard_Real BaseSize, const M_GEO GeoMesh_BackGroundMesh3d& BackGround);

			virtual Standard_Real ElementSize(const Geom_Pnt3d& Coord) const;

			virtual Standard_Real ElementSize(const Mesh3d_Facet& Facet) const;

			virtual Standard_Real CalcUnitDistance(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2) const;

			virtual Standard_Real Integrand(const Geom_Pnt3d& Point, const Geom_Pnt3d& Vector) const;

			void ExportToPlt(fstream& File) const;

			void ExportSizeMapToPlt(fstream& File) const;

		};
	}
}

#include <SizeMap3d_StdBackSizeI.hxx>

#endif // !_SizeMap3d_BackSize_Header
