#pragma once
#ifndef _SizeMap3d_UnionSizeMaps_Header
#define _SizeMap3d_UnionSizeMaps_Header

#include <Standard_Stream.hxx>
#include <TColGeoMesh_HBasicQueueOfBackGroundMesh3d.hxx>

namespace AutLib
{

	namespace MeshLib
	{

		class SizeMap3d_SizeMapTool;

		//! Warning: this class is not responsible for any memory management
		class SizeMap3d_UnionSizeMaps
		{

		private:

			TColGeoMesh_HBasicQueueOfBackGroundMesh3d theSizeMaps_;

			Standard_Real theTolerance_;

			Standard_Integer theMinSubdivision_;
			Standard_Integer theMaxSubdivision_;

			Standard_Boolean IsDone_;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) theBackMesh_;

		public:

			SizeMap3d_UnionSizeMaps();

			~SizeMap3d_UnionSizeMaps();

			void ImportSizeMap(const Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) theBack);

			void SetTolerance(const Standard_Real theTolerance);

			void SetMinSubdivide(const Standard_Integer theValue);

			void SetMaxSubdivide(const Standard_Integer theValue);

			void Perform();

			Standard_Boolean IsDone() const;

			Standard_Integer Size() const;

			//! Warning: not removed from memory automatically
			Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) BackGroundMesh() const;

			void ExportBackMeshToPlt(fstream& File) const;
		};
	}
}

#include <SizeMap3d_UnionSizeMapsI.hxx>

#endif // !_SizeMap3d_UnionSizeMaps_Header
