#pragma once
#ifndef _SizeMap3d_PrimitiveShapeSource_Header
#define _SizeMap3d_PrimitiveShapeSource_Header

#include <Entity_Box3d.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <GeoMesh_BackGroundMesh3d.hxx>
#include <Geom_Pnt3d.hxx>
#include <TopoDS_Shape.hxx>

class gp_Ax2;

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_PrimitiveShapeSource
		{

			friend class SizeMap3d_PrimitiveShapesSizeMapTool;

		private:

			Standard_Real theDeflection_;
			Standard_Real theAngle_;
			Standard_Real theSize_;  // Per BaseSize

			TopoDS_Shape theShape_;

			M_GEO Entity_Box3d theBoundingBox_;

			M_GEO GeoMesh_BackGroundMesh3d theSource_;

		public:

			SizeMap3d_PrimitiveShapeSource();

			Standard_Real ElementSize(const Geom_Pnt3d& theCoord) const;

			Standard_Real ElementSize(const Geom_Pnt3d& theCoord, Standard_Boolean& theSense) const;

			TopoDS_Shape Shape() const;

			const M_GEO Entity_Box3d& BoundingBox() const;

			const M_GEO GeoMesh_BackGroundMesh3d& Mesh() const;

			void SetDeflection(const Standard_Real theDeflection);

			void SetAngle(const Standard_Real theAngle);

			void SetSize(const Standard_Real theSize);

			void Box(const Geom_Pnt3d& P, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz);

			void Box(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			void Box(const gp_Ax2& Axes, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz);

			void Cone(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2, const Standard_Real H);

			void Cone(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2, const Standard_Real H, const Standard_Real angle);

			void Sphere(const Geom_Pnt3d& Center, const Standard_Real R);

			void Sphere(const gp_Ax2& Axis, const Standard_Real R);

			void Cylinder(const gp_Ax2& Axes, const Standard_Real R, const Standard_Real H);

			void Cylinder(const gp_Ax2& Axes, const Standard_Real R, const Standard_Real H, const Standard_Real Angle);

		private:

			void Construct();

		};
	}
}

#include <SizeMap3d_PrimitiveShapeSourceI.hxx>

#endif // !_SizeMap3d_PrimitiveShapes_Header
