#pragma once
#ifndef _Mesh3d_SizeMapControl_Header
#define _Mesh3d_SizeMapControl_Header

#include <Standard_OStream.hxx>
#include <TColSizeMap3d_StringMapOfHSizeMapTool.hxx>
#include <TColSizeMap3d_HAry1dOfSizeMapTool.hxx>

namespace AutLib
{
	namespace CadLib
	{
		class Cad3d_Solid;
	}

	namespace GeoLib
	{
		class GeoMesh_BackGroundMesh3d;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;
		class Mesh3d_SizeMap;

		class Mesh3d_SizeMapControl
		{

		protected:

			const Global_Handle(Mesh_ReferenceValues) theReference_;

			const Global_Handle(M_CAD Cad3d_Solid) theSolid_;

			TColSizeMap3d_StringMapOfHSizeMapTool theBoundaries_;

		public:

			~Mesh3d_SizeMapControl();

			virtual void CreateNewMap(const Standard_String& theName);

			void Print(Standard_OStream& Ostream = cout) const;

			void Remove(const Standard_String& theName);

			void RetrieveSizeMapsTo(TColSizeMap3d_HAry1dOfSizeMapTool& theSizeMaps) const;

			void ReleaseMemory();

			Standard_Integer Size() const;

			const TColSizeMap3d_StringMapOfHSizeMapTool& Maps() const;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) CalcSizeMap() const;

		protected:

			Mesh3d_SizeMapControl(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad3d_Solid) theSolid);

			void ImportMap(const Global_Handle(SizeMap3d_SizeMapTool) theMap, const Standard_String theName);
		};
	}
}

#include <Mesh3d_SizeMapControlI.hxx>

#endif // !_Mesh3d_SizeMapControl_Header
