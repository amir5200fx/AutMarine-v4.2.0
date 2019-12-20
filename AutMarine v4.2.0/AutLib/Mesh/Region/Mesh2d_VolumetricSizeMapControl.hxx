#pragma once
#ifndef _Mesh2d_VolumetricSizeMapControl_Header
#define _Mesh2d_VolumetricSizeMapControl_Header

#include <Mesh2d_SizeMapControl.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_PrimitiveShapesSizeMapTool;

		class Mesh2d_VolumetricSizeMapControl : public Mesh2d_SizeMapControl
		{

		public:

			Mesh2d_VolumetricSizeMapControl(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			~Mesh2d_VolumetricSizeMapControl();

			Global_Handle(SizeMap2d_PrimitiveShapesSizeMapTool) SelectMap(const Standard_String& theName) const;

			virtual void CreateNewMap(const Standard_String& theName);

		};
	}
}

#endif // !_Mesh2d_VolumetricSizeMapControl_Header
