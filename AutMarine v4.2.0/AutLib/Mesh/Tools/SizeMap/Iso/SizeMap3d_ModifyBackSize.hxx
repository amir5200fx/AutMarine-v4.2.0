#pragma once
#ifndef _SizeMap3d_ModifyBackSize_Header
#define _SizeMap3d_ModifyBackSize_Header

#include <SizeMap3d_StdBackSize.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_ModifyBackSize : public SizeMap3d_StdBackSize
		{

		protected:

			Standard_Real theCoeff_;
			Standard_Real theDelta_;

		public:

			SizeMap3d_ModifyBackSize(const Standard_Real theBaseSize, const M_GEO GeoMesh_BackGroundMesh3d& theBackGround);

			virtual Standard_Real ElementSize(const Mesh3d_Facet& theFacet) const;

		};
	}
}

#include <SizeMap3d_ModifyBackSizeI.hxx>

#endif // !_SizeMap3d_ModifyBackSize_Header
