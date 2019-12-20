#pragma once
#ifndef _Mesh2d_BackSize_Header
#define _Mesh2d_BackSize_Header

#include <SizeMap2d_StdBackSize.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_ModifyBackSize : public SizeMap2d_StdBackSize
		{

		protected:

			Standard_Real theCoeff_;
			Standard_Real theDelta_;

		public:

			SizeMap2d_ModifyBackSize(const Standard_Real BaseSize, const M_GEO GeoMesh_BackGroundMesh2d& BackGround);

			virtual Standard_Real ElementSize(const Mesh2d_Edge& Edge) const;

		};
	}
}

#include <SizeMap2d_ModifyBackSizeI.hxx>

#endif // !_Mesh2d_BackSize_Header
