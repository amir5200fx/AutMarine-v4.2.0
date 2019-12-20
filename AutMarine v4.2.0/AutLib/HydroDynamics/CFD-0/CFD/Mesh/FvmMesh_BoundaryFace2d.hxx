#pragma once
#ifndef _FvmMesh_BoundaryFace2d_Header
#define _FvmMesh_BoundaryFace2d_Header

#include <FvmMesh_Face2d.hxx>
#include <FvmBC_Type.hxx>

namespace AutLib
{
	namespace FvmLib
	{

		class FvmMesh_BoundaryFace2d : public FvmMesh_Face2d
		{

		private:

			FvmBC_Type theBondaryCondition_;
		};
	}
}

#endif // !_FvmMesh_BoundaryFace2d_Header
