#pragma once
#ifndef _GeoMesh_BackGroundMesh2d_Header
#define _GeoMesh_BackGroundMesh2d_Header

#include <GeoMesh_TriangleMesh2d.hxx>
#include <TColStd_Ary1dOfReal.hxx>

namespace AutLib
{
	class Primitive_Field;

	namespace GeoLib
	{
		class Entity_Box2d;

		class GeoMesh_BackGroundMesh2d
		{

		private:

			GeoMesh_TriangleMesh2d theMesh_;

			mutable TColStd_Ary1dOfReal theSources_;

			mutable Global_Handle(Entity_Element2d) theCurrentElement_;

			Global_Handle(Entity_Box2d) theBoundingBox_;

		public:

			GeoMesh_BackGroundMesh2d();

			GeoMesh_BackGroundMesh2d(const GeoMesh_TriangleMesh2d& StaticMesh);

			~GeoMesh_BackGroundMesh2d();

			//! Throw an exception.
			Standard_Real ElementSize(const Geom_Pnt2d& theCoord) const;

			Standard_Real ElementSize(const Geom_Pnt2d& theCoord, Standard_Boolean &Sense) const;

			Standard_Real Length(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			//! Throw an exception.
			Primitive_Field Field() const;

			GeoMesh_TriangleMesh2d& Mesh();

			const GeoMesh_TriangleMesh2d& Mesh() const;

			const Global_Handle(Entity_Box2d) BoundingBox() const;

			TColStd_Ary1dOfReal& Sources() const;

			void SetBoundingBox(const Entity_Box2d& theBoundingBox);

			void InitiateCurrentElement() const;

			void SetCurrentElement(const Global_Handle(Entity_Element2d) theElement) const;

			void HvCorrection(const Standard_Real Factor, const Standard_Integer MaxInnerIteration = 5);

			void LaplacianSmoothing(const Standard_Integer NbIterations = 3, const Standard_Real Factor = 0.3);

			void ExportToPlt(fstream & File) const;

			void ExportMeshToPlt(fstream& File) const;

			//! Set Sources with interpolation of valued points.
			//! Throw an exception while atleast one node outside the Mesh (Sense) or there is no constructed Mesh
			void ExtractSourcesFrom(const TColGeom_Ary1dOfPnt2d& Coords, const TColStd_Ary1dOfReal& Values, const Standard_Boolean Sense = Standard_False);

		private:

			Global_Handle(Entity_Element2d) ElementLocation(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <GeoMesh_BackGroundMesh2dI.hxx>

#endif // !_GeoMesh_BackGroundMesh2d_Header
