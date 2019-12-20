#pragma once
#ifndef _SizeMap2d_UnionSizeMaps_Header
#define _SizeMap2d_UnionSizeMaps_Header

#include <Standard_Stream.hxx>
#include <TColGeoMesh_HBasicQueueOfBackGroundMesh2d.hxx>

namespace AutLib
{

	namespace GeoLib
	{
		class GeoMesh_BackGroundMesh2d;
	}

	namespace MeshLib
	{

		class SizeMap2d_SizeMapTool;

		//! Warning: this class is not responsible for any memory management
		class SizeMap2d_UnionSizeMaps
		{

		private:

			TColGeoMesh_HBasicQueueOfBackGroundMesh2d theSizeMaps_;

			Standard_Real theTolerance_;

			Standard_Integer theMinSubdivision_;
			Standard_Integer theMaxSubdivision_;

			Standard_Boolean IsDone_;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBackMesh_;

		public:

			SizeMap2d_UnionSizeMaps();

			~SizeMap2d_UnionSizeMaps();

			void ImportSizeMap(const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack);

			void SetTolerance(const Standard_Real theTolerance);

			void SetMinSubdivide(const Standard_Integer theValue);

			void SetMaxSubdivide(const Standard_Integer theValue);

			void Perform();

			Standard_Boolean IsDone() const;

			//! Warning: not removed from memory automatically
			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) BackGroundMesh() const;

			void ExportBackMeshToPlt(fstream& File) const;
		};
	}
}

#include <SizeMap2d_UnionSizeMapsI.hxx>

#endif // !_SizeMap2d_UnionSizeMaps_Header
