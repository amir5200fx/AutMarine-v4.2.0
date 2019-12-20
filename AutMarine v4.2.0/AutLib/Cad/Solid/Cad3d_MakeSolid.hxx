#pragma once
#ifndef _Cad3d_MakeSolid_Header
#define _Cad3d_MakeSolid_Header

#include <Geom_Pnt3d.hxx>

class gp_Ax2;
class TopoDS_Shape;

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_MakeSolid
		{

		public:

			//! Make a box with a corner at P and size dx, dy, dz.
			static TopoDS_Shape Box(const Geom_Pnt3d& P, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz);

			//! Make a box with corners P1,P2.
			static TopoDS_Shape Box(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			//! Ax2 is the left corner and the axis.
			//! Constructs a box such that its sides are parallel to the axes of
			//! -   the global coordinate system, or
			//! -   the local coordinate system Axis. and
			//! -   with a corner at (0, 0, 0) and of size (dx, dy, dz), or
			//! -   with a corner at point P and of size (dx, dy, dz), or
			//! -   with corners at points P1 and P2.
			//! Exceptions
			//! Standard_DomainError if: dx, dy, dz are less than or equal to
			//! Precision::Confusion(), or
			//! -   the vector joining the points P1 and P2 has a
			//! component projected onto the global coordinate
			//! system less than or equal to Precision::Confusion().
			//! In these cases, the box would be flat.
			static TopoDS_Shape Box(const gp_Ax2& Axes, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz);

			//! Make a cone of height H radius R1 in the plane z =
			//! 0, R2 in the plane Z = H. R1 and R2 may be null.
			static TopoDS_Shape Cone(const Standard_Real R1, const Standard_Real R2, const Standard_Real H);

			static TopoDS_Shape Cone(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2, const Standard_Real H);

			//! Make a cone of height H radius R1 in the plane z =
			//! 0, R2 in the plane Z = H. R1 and R2 may be null.
			//! Take a section of <angle>
			//! Constructs a cone, or a portion of a cone, of height H,
			//! and radius R1 in the plane z = 0 and R2 in the plane
			//! z = H. The result is a sharp cone if R1 or R2 is equal to 0.
			//! The cone is constructed about the "Z Axis" of either:
			//! -   the global coordinate system, or
			//! -   the local coordinate system Axes.
			//! It is limited in these coordinate systems as follows:
			//! -   in the v parametric direction (the Z coordinate), by
			//! the two parameter values 0 and H,
			//! -   and in the u parametric direction (defined by the
			//! angle of rotation around the Z axis), in the case of a
			//! portion of a cone, by the two parameter values 0 and
			//! angle. Angle is given in radians.
			//! The resulting shape is composed of:
			//! -   a lateral conical face
			//! -   two planar faces in the planes z = 0 and z = H,
			//! or only one planar face in one of these two planes if a
			//! radius value is null (in the case of a complete cone,
			//! these faces are circles), and
			//! -   and in the case of a portion of a cone, two planar
			//! faces to close the shape. (either two parallelograms or
			//! two triangles, in the planes u = 0 and u = angle).
			//! Exceptions
			//! Standard_DomainError if:
			//! -   H is less than or equal to Precision::Confusion(), or
			//! -   the half-angle at the apex of the cone, defined by
			//! R1, R2 and H, is less than Precision::Confusion()/H, or greater than
			//! (Pi/2)-Precision::Confusion()/H.f
			static TopoDS_Shape Cone(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2, const Standard_Real H, const Standard_Real angle);

			//! Make a sphere of radius R.
			static TopoDS_Shape Sphere(const Geom_Pnt3d& Center, const Standard_Real R);

			//! Make a sphere of radius R.
			static TopoDS_Shape Sphere(const Geom_Pnt3d& Center, const Standard_Real R, const Standard_Real angle);

			//! Make a sphere of radius R.
			static TopoDS_Shape Sphere(const Geom_Pnt3d& Center, const Standard_Real R, const Standard_Real angle1, const Standard_Real angle2);

			//! Make a sphere of radius R.
			static TopoDS_Shape Sphere(const Geom_Pnt3d& Center, const Standard_Real R, const Standard_Real angle1, const Standard_Real angle2, const Standard_Real angle3);

			static TopoDS_Shape Sphere(const gp_Ax2& Axis, const Standard_Real R);

			static TopoDS_Shape Sphere(const gp_Ax2& Axis, const Standard_Real R, const Standard_Real angle);

			static TopoDS_Shape Sphere(const gp_Ax2& Axis, const Standard_Real R, const Standard_Real angle1, const Standard_Real angle2);

			//! Make a sphere of radius R.
			//! For all algorithms The resulting shape is composed of
			//! -   a lateral spherical face,
			//! -   two planar faces parallel to the plane z = 0 if the
			//! sphere is truncated in the v parametric direction, or
			//! only one planar face if angle1 is equal to -p/2 or if
			//! angle2 is equal to p/2 (these faces are circles in
			//! case of a complete truncated sphere),
			//! -   and in case of a portion of sphere, two planar faces
			//! to shut the shape.(in the planes u = 0 and u = angle).
			static TopoDS_Shape Sphere(const gp_Ax2& Axis, const Standard_Real R, const Standard_Real angle1, const Standard_Real angle2, const Standard_Real angle3);

			//! Make a cylinder of radius R and length H.
			static TopoDS_Shape Cylinder(const Standard_Real R, const Standard_Real H);

			static TopoDS_Shape Cylinder(const Standard_Real R, const Standard_Real H, const Standard_Real Angle);

			static TopoDS_Shape Cylinder(const gp_Ax2& Axes, const Standard_Real R, const Standard_Real H);

			//! Make a cylinder   of  radius R  and  length H with
			//! angle  H.
			//! Constructs
			//! -   a cylinder of radius R and height H, or
			//! -   a portion of cylinder of radius R and height H, and of
			//! the angle Angle defining the missing portion of the cylinder.
			//! The cylinder is constructed about the "Z Axis" of either:
			//! -   the global coordinate system, or
			//! -   the local coordinate system Axes.
			//! It is limited in this coordinate system as follows:
			//! -   in the v parametric direction (the Z axis), by the two
			//! parameter values 0 and H,
			//! -   and in the u parametric direction (the rotation angle
			//! around the Z Axis), in the case of a portion of a
			//! cylinder, by the two parameter values 0 and Angle.
			//! Angle is given in radians.
			//! The resulting shape is composed of:
			//! -   a lateral cylindrical face,
			//! -   two planar faces in the planes z = 0 and z = H
			//! (in the case of a complete cylinder, these faces are circles), and
			//! -   in case of a portion of a cylinder, two additional
			//! planar faces to close the shape.(two rectangles in the
			//! planes u = 0 and u = Angle).
			//! Exceptions Standard_DomainError if:
			//! -   R is less than or equal to Precision::Confusion(), or
			//! -   H is less than or equal to Precision::Confusion().
			static TopoDS_Shape Cylinder(const gp_Ax2& Axes, const Standard_Real R, const Standard_Real H, const Standard_Real Angle);

			//! Make a torus of radii R1 R2.
			static TopoDS_Shape Torus(const Standard_Real R1, const Standard_Real R2);

			//! Make a section of a torus of radii R1 R2.
			static TopoDS_Shape Torus(const Standard_Real R1, const Standard_Real R2, const Standard_Real angle);

			//! Make  a torus of  radii R2, R2  with angles on the
			//! small circle.
			static TopoDS_Shape Torus(const Standard_Real R1, const Standard_Real R2, const Standard_Real angle1, const Standard_Real angle2);

			//! Make  a torus of  radii R2, R2  with angles on the
			//! small circle.
			static TopoDS_Shape Torus(const Standard_Real R1, const Standard_Real R2, const Standard_Real angle1, const Standard_Real angle2, const Standard_Real angle);

			//! Make a torus of radii R1 R2.
			static TopoDS_Shape Torus(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2);

			//! Make a section of a torus of radii R1 R2.
			static TopoDS_Shape Torus(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2, const Standard_Real angle);

			//! Make a torus of radii R1 R2.
			static TopoDS_Shape Torus(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2, const Standard_Real angle1, const Standard_Real angle2);

			//! Make a section of a torus of radii R1 R2.
			//! For all algorithms The resulting shape is composed of
			//! -      a lateral toroidal face,
			//! -      two conical faces (defined  by the equation v = angle1 and
			//! v = angle2) if the sphere is truncated in the v parametric
			//! direction (they may be cylindrical faces in some
			//! particular conditions), and in case of a portion
			//! of torus, two planar faces to close the shape.(in the planes
			//! u = 0 and u = angle).
			//! Notes:
			//! -      The u parameter corresponds to a rotation angle around the Z axis.
			//! -      The circle whose radius is equal to the minor radius,
			//! located in the plane defined by the X axis and the Z axis,
			//! centered on the X axis, on its positive side, and positioned
			//! at a distance from the origin equal to the major radius, is
			//! the reference circle of the torus. The rotation around an
			//! axis parallel to the Y axis and passing through the center
			//! of the reference circle gives the v parameter on the
			//! reference circle. The X axis gives the origin of the v
			//! parameter. Near 0, as v increases, the Z coordinate decreases.
			static TopoDS_Shape Torus(const gp_Ax2& Axes, const Standard_Real R1, const Standard_Real R2, const Standard_Real angle1, const Standard_Real angle2, const Standard_Real angle);
		};
	}
}

#endif // !_Cad3d_MakeSolid_Header
