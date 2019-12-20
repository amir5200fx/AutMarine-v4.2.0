#pragma once
#ifndef _SizeMap2d_SizeMapTool_Header
#define _SizeMap2d_SizeMapTool_Header

#include <Global_Memory.hxx>
#include <Standard_String.hxx>
#include <Geom_Pnt2d.hxx>
#include <Mesh_Values.hxx>
#include <Mesh_Conditions.hxx>

namespace AutLib
{
	namespace CadLib
	{
		class Cad2d_Plane;
	}

	namespace GeoLib
	{
		class Entity_Box2d;
		class GeoMesh_BackGroundMesh2d;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;

		class SizeMap2d_SizeMapTool
		{

		protected:

			Mesh_Conditions theConditions_;

			Mesh_Values theValues_;

			const Global_Handle(Mesh_ReferenceValues) theReference_;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBackMesh_;

			const Global_Handle(M_CAD Cad2d_Plane) thePlane_;

			//Standard_String theName_;

		public:

			virtual ~SizeMap2d_SizeMapTool();

			const Mesh_Values& MeshValues() const;

			const Mesh_Conditions& MeshConditions() const;

			const Global_Handle(M_CAD Cad2d_Plane) Plane() const;

			Mesh_Values& MeshValues();

			Mesh_Conditions& MeshConditions();

			Standard_Real ElementSize(const Geom_Pnt2d& Coord) const;

			M_GEO Entity_Box2d BoundingBox(const Standard_Real theOffset = 0) const;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) BackGroundMesh() const;

			//void SetName(const Standard_String& theName);

			void ExportMeshToPlt(fstream& File) const;

			void ExportContourToPlt(fstream& File) const;

			Standard_Real RetrieveTargetSize() const;

			Standard_Real GetBaseSize() const;

			Standard_Real GetTargetSurfaceSize() const;

			Standard_Real GetBoundaryGrowthRate() const;

			//Standard_String Name() const;

		protected:

			SizeMap2d_SizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			void SpecifyValues(Standard_Real& ElementSize, Standard_Real& MinElementSize, Standard_Real& SpanAngle) const;
		};
	}
}

#include <SizeMap2d_SizeMapToolI.hxx>

#endif // !_SizeMap2d_SizeMapTool_Header
