#pragma once
#ifndef _SizeMap2d_CorrectSizeMapTool_Header
#define _SizeMap2d_CorrectSizeMapTool_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Stream.hxx>

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

		class Mesh2d_SizeMap;
		class Mesh2d_Domain;
		class Mesh_Values;

		class SizeMap2d_CorrectSizeMapTool
		{

		private:

			const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack_;

			const Global_Handle(M_CAD Cad2d_Plane) thePlane_;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theModified_;

			Standard_Integer theBucketSize_;
			Standard_Integer theMaxLevels_;

			Standard_Real theMaxDeviation_;

		public:

			SizeMap2d_CorrectSizeMapTool();

			SizeMap2d_CorrectSizeMapTool(const Global_Handle(M_CAD Cad2d_Plane) thePlane, const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack);

			~SizeMap2d_CorrectSizeMapTool();

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) Modified() const;

			void Init(const Global_Handle(M_CAD Cad2d_Plane) thePlane, const Global_Handle(Mesh_Values) theValues, const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack);

			void SetPlane(const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			void SetBackMesh(const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack);

			void SetBucketSize(const Standard_Integer theBucketSize);

			void SetMaxLevelCorrection(const Standard_Integer theMaxLevel);

			void Perform();

			void ExportToPlt(fstream& File) const;

		private:

			Standard_Boolean OneLevelModify(const Mesh2d_Domain& theDomain);
		};
	}
}

#include <SizeMap2d_CorrectSizeMapToolI.hxx>

#endif // !_SizeMap2d_CorrectSizeMapTool_Header
