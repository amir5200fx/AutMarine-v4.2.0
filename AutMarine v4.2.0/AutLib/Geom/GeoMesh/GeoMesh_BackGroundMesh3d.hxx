#pragma once
#ifndef _GeoMesh_BackGroundMesh3d_Header
#define _GeoMesh_BackGroundMesh3d_Header

#include <Global_Memory.hxx>
#include <Geom_Pnt3d.hxx>
#include <GeoMesh_TetrahedronMesh.hxx>
#include <TColStd_Ary1dOfReal.hxx>

namespace AutLib
{
	class Primitive_Field;

	namespace GeoLib
	{

		class GeoMesh_TetrahedronMesh;
		class Entity_Element3d;
		class Entity_Box3d;

		class GeoMesh_BackGroundMesh3d
		{

		private:

			GeoMesh_TetrahedronMesh theMesh_;

			mutable TColStd_Ary1dOfReal theSources_;

			mutable Global_Handle(Entity_Element3d) theCurrentElement_;

			Global_Handle(Entity_Box3d) theBoundingBox_;

		public:

			GeoMesh_BackGroundMesh3d();

			//GeoMesh_BackGroundMesh3d(const GeoMesh_TetrahedronMesh& theStaticMesh);

			~GeoMesh_BackGroundMesh3d();

			//! Throw an exception.
			Standard_Real ElementSize(const Geom_Pnt3d& theCoord) const;

			Standard_Real ElementSize(const Geom_Pnt3d& theCoord, Standard_Boolean &Sense) const;

			Standard_Real Length(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2) const;

			//! Throw an exception.
			Primitive_Field Field() const;

			GeoMesh_TetrahedronMesh& Mesh();

			const GeoMesh_TetrahedronMesh& Mesh() const;

			const Global_Handle(Entity_Box3d) BoundingBox() const;

			TColStd_Ary1dOfReal& Sources() const;

			void SetBoundingBox(const Entity_Box3d& theBoundingBox);

			void InitiateCurrentElement() const;

			void HvCorrection(const Standard_Real Factor, const Standard_Integer MaxInnerIteration = 5) const;

			void LaplacianSmoothing(const Standard_Integer NbIterations = 3, const Standard_Real Factor = 0.3) const;

			void ExportToPlt(fstream & File) const;

			void ExportMeshToPlt(fstream& File) const;
		};
	}
}

#include <GeoMesh_BackGroundMesh3dI.hxx>

#endif // !_GeoMesh_BackGroundMesh3d_Header
