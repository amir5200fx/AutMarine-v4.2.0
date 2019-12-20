#pragma once
#ifndef _SizeMap2d_SharpCornersSizeMapTool_Header
#define _SizeMap2d_SharpCornersSizeMapTool_Header

#include <SizeMap2d_PointsSizeMapTool.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_SharpCornersSizeMapTool : public SizeMap2d_PointsSizeMapTool
		{

		private:

			Standard_Real theSharpAngle_;

		public:

			SizeMap2d_SharpCornersSizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			virtual ~SizeMap2d_SharpCornersSizeMapTool();

			void SetAngle(const Standard_Real theAngle);

			void CreateSizeMap();
		};
	}
}

#endif // !_SizeMap2d_SharpCornersSizeMapTool_Header
