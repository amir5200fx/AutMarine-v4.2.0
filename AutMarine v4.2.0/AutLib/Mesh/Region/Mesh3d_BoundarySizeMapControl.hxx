#pragma once
#ifndef _Mesh3d_BoundarySizeMapControl_Header
#define _Mesh3d_BoundarySizeMapControl_Header

#include <Mesh3d_SizeMapControl.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_UniformSurfacesSizeMapTool;

		class Mesh3d_BoundarySizeMapControl : public Mesh3d_SizeMapControl
		{

		public:

			Mesh3d_BoundarySizeMapControl(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad3d_Solid) theSolid);

			~Mesh3d_BoundarySizeMapControl();

			virtual void CreateNewMap(const Standard_String& theName);

			Global_Handle(SizeMap3d_UniformSurfacesSizeMapTool) SelectMap(const Standard_String& theName) const;
		};
	}
}

#endif // !_Mesh3d_BoundarySizeMapControl_Header
