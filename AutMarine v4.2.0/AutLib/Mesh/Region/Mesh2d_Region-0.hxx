#pragma once
#ifndef _Mesh2d_Region_Header
#define _Mesh2d_Region_Header

#include <TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool.hxx>
#include <TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool.hxx>
#include <TColSizeMap2d_HAry1dOfAdaptiveCurvesSizeMapTool.hxx>
#include <TColSizeMap2d_HAry1dOfSharpCornersSizeMapTool.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class GeoMesh_BackGroundMesh2d;
	}

	namespace CadLib
	{
		class Cad2d_Plane;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;
		class SizeMap2d_BoundarySizeMapTool;

		class Mesh2d_Region
		{

		private:

			const Global_Handle(M_CAD Cad2d_Plane) thePlane_;

			const Global_Handle(Mesh_ReferenceValues) theReference_;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBackMesh_;

			Standard_Real theTolerance_;

			TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool theFeaturePoints_;
			TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool thePointToFeature_;

			TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool theBoundaries_;
			TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool thePatchToBoundary_;

			mutable TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::iterator theBoundarySelected_;
			mutable TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::iterator theFeatureSelected_;

		public:

			Mesh2d_Region();

			~Mesh2d_Region();

			Standard_Integer NbBoundaries() const;

			Standard_Integer NbFeatures() const;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) BackGroundMesh() const;

			void CreateBoundary(const Standard_String Name);

			void CreateFeaturePoint(const Standard_String Name);

			void DeleteBoundary(const Standard_String Name);

			void DeleteFeaturePoint(const Standard_String Name);

			Global_Handle(SizeMap2d_BoundarySizeMapTool) SelectBoundary(const Standard_String Name);

			Global_Handle(SizeMap2d_BoundarySizeMapTool) SelectFeature(const Standard_String Name);

			void ImportPart(const Standard_String Name);

			void ImportFeature(const Standard_String Name);

			void UnSelectPart(const Standard_String Name);

			void UnSelectFeature(const Standard_String Name);

			void PrintBoundaries(Standard_OStream& Ostream = cout) const;

			void PrintFeatures(Standard_OStream& Ostream = cout) const;

			void Perform();

			void ExportBoundaryMapsToPlt(fstream& File) const;

			void ExportFeatureMapsToPlt(fstream& File) const;

			void ExportUnionMapToPlt(fstream& File) const;

		private:

			void Clear();

			void Init();

			void ImportBoundary(const Standard_String Name, Global_Handle(SizeMap2d_AdaptiveCurvesSizeMapTool) SizeControl);

			void ImportFeature(const Standard_String Name, Global_Handle(SizeMap2d_SharpCornersSizeMapTool) SizeControl);

			void RetrieveTo(TColSizeMap2d_HAry1dOfAdaptiveCurvesSizeMapTool& Maps) const;

			void RetrieveTo(TColSizeMap2d_HAry1dOfSharpCornersSizeMapTool& Maps) const;

			void UnionMaps();
		};
	}
}

#endif // !_Mesh2d_Region_Header
