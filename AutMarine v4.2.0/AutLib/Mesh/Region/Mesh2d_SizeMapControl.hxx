#pragma once
#ifndef _Mesh2d_SizeMapControl_Header
#define _Mesh2d_SizeMapControl_Header

#include <Standard_OStream.hxx>
#include <TColSizeMap2d_StringMapOfHSizeMapTool.hxx>
#include <TColSizeMap2d_HAry1dOfSizeMapTool.hxx>

namespace AutLib
{
	namespace CadLib
	{
		class Cad2d_Plane;
	}

	namespace GeoLib
	{
		class GeoMesh_BackGroundMesh2d;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;
		class Mesh2d_SizeMap;

		class Mesh2d_SizeMapControl
		{

		protected:

			const Global_Handle(Mesh_ReferenceValues) theReference_;

			const Global_Handle(M_CAD Cad2d_Plane) thePlane_;

			TColSizeMap2d_StringMapOfHSizeMapTool theBoundaries_;

		public:

			~Mesh2d_SizeMapControl();

			virtual void CreateNewMap(const Standard_String& theName);

			void Print(Standard_OStream& Ostream = cout) const;

			void Remove(const Standard_String& theName);

			void RetrieveSizeMapsTo(TColSizeMap2d_HAry1dOfSizeMapTool& theSizeMaps) const;

			void ReleaseMemory();

			Standard_Integer Size() const;

			const TColSizeMap2d_StringMapOfHSizeMapTool& Maps() const;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) CalcSizeMap() const;

		protected:

			Mesh2d_SizeMapControl(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			void ImportMap(const Global_Handle(SizeMap2d_SizeMapTool) theMap, const Standard_String theName);
		};
	}
}

#include <Mesh2d_SizeMapControlI.hxx>

#endif // !_Mesh2d_SizeMapControl_Header
