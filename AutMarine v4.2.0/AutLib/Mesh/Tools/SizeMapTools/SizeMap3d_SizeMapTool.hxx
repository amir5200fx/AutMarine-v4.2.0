#pragma once
#ifndef _SizeMap3d_SizeMapTool_Header
#define _SizeMap3d_SizeMapTool_Header

#include <Global_Memory.hxx>
#include <Standard_String.hxx>
#include <Geom_Pnt3d.hxx>
#include <Mesh_Values.hxx>
#include <Mesh_Conditions.hxx>

namespace AutLib
{
	namespace CadLib
	{
		class Cad3d_Solid;
	}

	namespace GeoLib
	{
		class Entity_Box3d;
		class GeoMesh_BackGroundMesh3d;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;

		class SizeMap3d_SizeMapTool
		{

		protected:

			Mesh_Conditions theConditions_;

			Mesh_Values theValues_;

			const Global_Handle(Mesh_ReferenceValues) theReference_;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) theBackMesh_;

			const Global_Handle(M_CAD Cad3d_Solid) theSolid_;

		public:

			virtual ~SizeMap3d_SizeMapTool();

			const Mesh_Values& MeshValues() const;

			const Mesh_Conditions& MeshConditions() const;

			const Global_Handle(M_CAD Cad3d_Solid) Solid() const;

			Mesh_Values& MeshValues();

			Mesh_Conditions& MeshConditions();

			Standard_Real ElementSize(const Geom_Pnt3d& Coord) const;

			M_GEO Entity_Box3d BoundingBox(const Standard_Real theOffset = 0) const;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) BackGroundMesh() const;

			//void SetName(const Standard_String& theName);

			void SpecifyValues(Standard_Real& theElementSize, Standard_Real& theMinElementSize, Standard_Real& theSpanAngle) const;

			void ExportMeshToPlt(fstream& File) const;

			void ExportContourToPlt(fstream& File) const;

			Standard_Real RetrieveTargetSize() const;

			Standard_Real GetBaseSize() const;

			Standard_Real GetTargetSurfaceSize() const;

			Standard_Real GetBoundaryGrowthRate() const;

		protected:

			SizeMap3d_SizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad3d_Solid) theSolid);
		};
	}
}

#include <SizeMap3d_SizeMapToolI.hxx>

#endif // !_SizeMap3d_SizeMapTool_Header
