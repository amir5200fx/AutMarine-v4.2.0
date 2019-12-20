#pragma once
#ifndef _Mesh3d_QualityMap3dTools_Header
#define _Mesh3d_QualityMap3dTools_Header

#include <Standard_Real.hxx>
#include <Global_Macros.hxx>
#include <QualityMap3d_TypesInfo.hxx>
#include <TColMesh3d_HAry1dOfOptTetInfo.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

namespace AutLib
{
	/* compute the dot product of two vectors u and v */
	inline Standard_Real dot(Standard_Real u[3],
		Standard_Real v[3])
	{
		return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
	}

	/* compute the cross product of two vectors u and v */
	inline void cross(Standard_Real u[3],
		Standard_Real v[3],
		Standard_Real prod[3])
	{
		prod[0] = u[1] * v[2] - u[2] * v[1];
		prod[1] = u[2] * v[0] - u[0] * v[2];
		prod[2] = u[0] * v[1] - u[1] * v[0];
	}

	/* scale a vector by a constant */
	inline void vscale(Standard_Real scale,
		Standard_Real v[3],
		Standard_Real scaled[3])
	{
		scaled[0] = v[0] * scale;
		scaled[1] = v[1] * scale;
		scaled[2] = v[2] * scale;
	}

	/* add two vectors u and v */
	inline void vadd(Standard_Real u[3],
		Standard_Real v[3],
		Standard_Real sum[3])
	{
		sum[0] = u[0] + v[0];
		sum[1] = u[1] + v[1];
		sum[2] = u[2] + v[2];
	}

	/* subtract two vectors u and v */
	inline void vsub(const Standard_Real u[3],
		const Standard_Real v[3],
		Standard_Real sum[3])
	{
		sum[0] = u[0] - v[0];
		sum[1] = u[1] - v[1];
		sum[2] = u[2] - v[2];
	}

	/* copy one vector's values into another */
	inline void vcopy(Standard_Real u[3],
		Standard_Real v[3])
	{
		v[0] = u[0];
		v[1] = u[1];
		v[2] = u[2];
	}

	/* return the length of a vector */
	inline Standard_Real vlength(Standard_Real u[3])
	{
		return sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
	}

	/* return if u and v are the same vector, false otherwise */
	inline bool vequal(Standard_Real u[3],
		Standard_Real v[3])
	{
		return (u[0] == v[0]) && (u[1] == v[1]) && (u[2] == v[2]);
	}

	/* compute the euclidean distance between two points u and v */
	inline Standard_Real vdist(Standard_Real u[3],
		Standard_Real v[3])
	{
		Standard_Real diff[3];
		vsub(u, v, diff);
		return vlength(diff);
	}

	/* project the vector u onto the vector v */
	inline void vproject(Standard_Real u[3],
		Standard_Real v[3],
		Standard_Real vout[3])
	{
		Standard_Real dotprod = dot(u, v);
		Standard_Real length = vlength(v);
		if (length > 0)
		{
			vscale(dotprod / length, v, vout);
		}
		else
		{
			vscale(0.0, v, vout);
		}
	}

	/* project the vector v onto the plane through the origin with normal n */
	inline void vprojecttoplane(Standard_Real v[3],
		Standard_Real n[3],
		Standard_Real vout[3])
	{
		Standard_Real proj[3];
		vproject(v, n, proj);
		vsub(v, proj, vout);
	}

	inline Standard_Real radtodeg(Standard_Real inangle)
	{
		return (inangle * 180) / PI;
	}

	inline void gradproduct(Standard_Real a,
		Standard_Real b,
		Standard_Real grada[3],
		Standard_Real gradb[3],
		Standard_Real prod[3])
	{
		prod[0] = grada[0] * b + gradb[0] * a;
		prod[1] = grada[1] * b + gradb[1] * a;
		prod[2] = grada[2] * b + gradb[2] * a;
	}

	inline void gradquotient(Standard_Real top,
		Standard_Real bot,
		Standard_Real gradtop[3],
		Standard_Real gradbot[3],
		Standard_Real quot[3])
	{
		Standard_Real denom = bot * bot;
		quot[0] = (bot * gradtop[0] - top * gradbot[0]) / denom;
		quot[1] = (bot * gradtop[1] - top * gradbot[1]) / denom;
		quot[2] = (bot * gradtop[2] - top * gradbot[2]) / denom;
	}

	/* compute Z, a quantity associated with circumradius computation
	TODO this code is lifted from Jonathan's tetcircumcenter computation
	in primitives.c */
	inline Standard_Real getZ(Standard_Real *tetorg, Standard_Real *tetdest, Standard_Real *tetfapex, Standard_Real *tettapex)
	{
		Standard_Real xot, yot, zot, xdt, ydt, zdt, xft, yft, zft;
		Standard_Real otlength, dtlength, ftlength;
		Standard_Real xcrossdf, ycrossdf, zcrossdf;
		Standard_Real xcrossfo, ycrossfo, zcrossfo;
		Standard_Real xcrossod, ycrossod, zcrossod;
		Standard_Real xct, yct, zct;

		/* Use coordinates relative to the apex of the tetrahedron. */
		xot = tetorg[0] - tettapex[0];
		yot = tetorg[1] - tettapex[1];
		zot = tetorg[2] - tettapex[2];
		xdt = tetdest[0] - tettapex[0];
		ydt = tetdest[1] - tettapex[1];
		zdt = tetdest[2] - tettapex[2];
		xft = tetfapex[0] - tettapex[0];
		yft = tetfapex[1] - tettapex[1];
		zft = tetfapex[2] - tettapex[2];
		/* Squares of lengths of the origin, destination, and face apex edges. */
		otlength = xot * xot + yot * yot + zot * zot;
		dtlength = xdt * xdt + ydt * ydt + zdt * zdt;
		ftlength = xft * xft + yft * yft + zft * zft;
		/* Cross products of the origin, destination, and face apex vectors. */
		xcrossdf = ydt * zft - yft * zdt;
		ycrossdf = zdt * xft - zft * xdt;
		zcrossdf = xdt * yft - xft * ydt;
		xcrossfo = yft * zot - yot * zft;
		ycrossfo = zft * xot - zot * xft;
		zcrossfo = xft * yot - xot * yft;
		xcrossod = yot * zdt - ydt * zot;
		ycrossod = zot * xdt - zdt * xot;
		zcrossod = xot * ydt - xdt * yot;

		/* Calculate offset (from apex) of circumcenter. */
		xct = (otlength * xcrossdf + dtlength * xcrossfo + ftlength * xcrossod);
		yct = (otlength * ycrossdf + dtlength * ycrossfo + ftlength * ycrossod);
		zct = (otlength * zcrossdf + dtlength * zcrossfo + ftlength * zcrossod);

		/* Calculate the length of this vector, which is Z */
		return sqrt(xct * xct + yct * yct + zct * zct);
	}

	inline Geom_Pnt3d getPoint(Standard_Real* x)
	{
		return Geom_Pnt3d(x[0], x[1], x[2]);
	}

	inline void getPoint(const Geom_Pnt3d& theP, Standard_Real* x)
	{
		x[0] = theP.X();
		x[1] = theP.Y();
		x[2] = theP.Z();
	}

	namespace MeshLib
	{

		class Mesh3d_OptTetInfo;
		class Mesh3d_Node;

		class Mesh3d_QualityMap3dTools
		{

		public:

			static void CalcOptInfo(const Global_Handle(Mesh3d_Node) theNode, Mesh3d_OptTetInfo& theTet, const QualityMap3d_TypesInfo theType, const Standard_Real theSineWarpFactor);

			static void GetActiveSet(const TColMesh3d_HAry1dOfOptTetInfo& incidenttets, const Standard_Real theActiveSetFactor, const Standard_Real theWorst, const QualityMap3d_TypesInfo theType, TColGeom_Ary1dOfPnt3d& theActiveGrads);

			static Standard_Real GetInitialAlpha(const TColMesh3d_HAry1dOfOptTetInfo& incidenttets, const Geom_Pnt3d& d, const Standard_Real r, const Standard_Real RateEpsilon, const QualityMap3d_TypesInfo theType, const Standard_Real theWorst);
		};
	}
}

#endif // !_Mesh3d_QualityMap3dTools_Header
