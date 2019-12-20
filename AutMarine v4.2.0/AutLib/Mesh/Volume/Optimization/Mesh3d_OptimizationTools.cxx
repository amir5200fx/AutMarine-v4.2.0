#include <Mesh3d_OptimizationTools.hxx>

#include <Mesh3d_OptimizationTetInfo.hxx>
#include <Geometry_Tools.hxx>
#include <TColGeom_BasicQueueOfPnt3d.hxx>

using namespace AutLib;
using namespace GeoLib;

Standard_Real AutLib::MeshLib::Mesh3d_OptimizationTools::GetInitialAlpha
(
	const TColMesh3d_HAry1dOfOptimizationTetInfo & theElements,
	Geom_Pnt3d & d,
	const Standard_Real r,
	const Standard_Real theWorst
)
{
	Standard_Real alpha = RealLast();

	forThose(i, 0, MaxIndexOf(theElements))
	{
		Standard_Real rate = DotProduct(d, theElements[i]->QualityGradient());

		if (rate + EPS6 < r)
		{
			/* compute the approximation of when this
			function will become the objective */
			Standard_Real newalpha = (theElements[i]->Quality() - theWorst) / (r - rate);

			/* if this is smaller than our current step size,
			use it for the step size */
			if (newalpha < alpha)
			{
				alpha = newalpha;
			}
		}
	}

	if (alpha < 0)
	{
		alpha = 0;
	}

	return alpha;
}

Geom_Pnt3d AutLib::MeshLib::Mesh3d_OptimizationTools::MinConvexHullPoint(const TColGeom_Ary1dOfPnt3d & thePoints)
{
	TColGeom_Ary1dOfPnt3d B(4);
	TColGeom_Ary1dOfPnt3d empty(4);

	Standard_Integer sizeB = 0;

	Geom_Pnt3d p, q, r;
	Geom_Pnt3d pmq, nearest;

	Standard_Real c, d, l;

	Geom_Pnt3d s, t, s2, t2;
	Geom_Pnt3d sxt, sxr, rxt, temp;

	Standard_Integer sizeP = thePoints.Size();

	/* find a basis for the minimum point on the convex hull */
	FindBasis(empty, thePoints, B, 0, sizeP, sizeB);

	switch (sizeB)
	{
		/* if the basis is just a single point, return that point */
	case 1:

		return B[0];

		break;

		/* for two points, find the closest point to the origin on
		the line between the two points */
	case 2:
		p = B[0];
		q = B[1];

		pmq = p - q;

		/*
		nearest = q - dot(q,p-q)/(length(p-q)^2) * (p-q)
		*/
		l = pmq.TwoNorm();

		/* if these points are the same, just return one of them */
		if (l == 0.0)
		{
			return B[0];
		}

		c = GeoLib::DotProduct(q, pmq) / (l*l);

		nearest = c*pmq;
		nearest = q - nearest;

		return nearest;

		break;

		/* for three points, find the point closest to the origin
		on the triangle that the they form */
	case 3:
		p = B[0];
		q = B[1];
		r = B[2];

		s = p - r;
		t = q - r;

		sxt = GeoLib::CrossProduct(s, t);
		rxt = GeoLib::CrossProduct(r, t);
		sxr = GeoLib::CrossProduct(s, r);

		/* if any of these cross products is really tiny, give up
		and return the origin */

		if (sxt.TwoNorm() < EPS12 || rxt.TwoNorm() < EPS12 || sxr.TwoNorm() < EPS12)
		{
			nearest = 0;

			return nearest;
		}

		c = GeoLib::DotProduct(sxt, rxt) / GeoLib::DotProduct(sxt, sxt);
		d = GeoLib::DotProduct(sxt, sxr) / GeoLib::DotProduct(sxt, sxt);

		s2 = c*s;
		t2 = d*t;

		temp = r - s2;
		nearest = temp - t2;

		return nearest;
		break;

		/* if the basis has four points, they must enclose the origin
		so just return the origin. */
	case 4:
		nearest = 0;

		return nearest;

		break;

	default:
		CloseProgram("Error, basis size is bogus, dying\n");

		break;
	}
}

void AutLib::MeshLib::Mesh3d_OptimizationTools::FindBasis
(
	const TColGeom_Ary1dOfPnt3d & S,
	const TColGeom_Ary1dOfPnt3d & M,
	TColGeom_Ary1dOfPnt3d & B,
	const Standard_Integer SizeS,
	const Standard_Integer SizeM,
	Standard_Integer & SizeB
)
{
	Geom_Pnt3d p, q, r, s;
	Geom_Pnt3d s1, t1, d1, d2;
	Geom_Pnt3d origin;

	TColGeom_Ary1dOfPnt3d localS(4);
	TColGeom_Ary1dOfPnt3d localM(M.Size());

	/* we assume that M was passed to us shuffled, so that taking
	the last element is equivalent to removing a random one. */
	p = M[SizeM - 1];

	/* if M has only one element */
	if (SizeM == 1)
	{
		/* and S has no elements */
		if (SizeS == 0)
		{
			B[0] = M[0];
			SizeB = 1;

			return;
		}

		/* otherwise, because we assume the last element
		we just removed is not part of the basis, assign
		the basis to be the elements of S */
		for (Standard_Integer i = 0; i < SizeS; i++)
			B[i] = S[i];

		SizeB = SizeS;
	}
	/* M has more than one element. Throw one out (p), and look for the
	basis assuming p is not part of it. */
	else
	{
		/* make a new copy of M minus the last element */
		for (Standard_Integer i = 0; i < SizeM - 1; i++)
		{
			localM[i] = M[i];
		}

		for (Standard_Integer i = 0; i < SizeS; i++)
		{
			localS[i] = S[i];
		}

		FindBasis
		(
			localS,
			localM,
			B,
			SizeS,
			SizeM - 1,
			SizeB
		);
	}

	/* now the we have determined the basis without p, we need to
	go back and check whether p actually is part of the basis. */

	switch (SizeB)
	{
		/* if the returned basis has just one point q, we just need to check
		whether p is closer to the origin than q */
	case 1:
		/* fetch the actual coordinates from the mesh */
		q = B[0];

		/* compute the vector from q to p */
		d1 = p - q;

		/* check the sign of the dot product. >=0 means p doesn't
		improve the basis */
		if (GeoLib::DotProduct(q, d1) >= 0)
		{
			/* this is a good B, send it back!*/
			return;
		}

		break;

		/* check whether p improves the basis */
	case 2:
		/* fetch coordinates from the mesh */
		q = B[0];
		r = B[1];

		/* compute vector s from r to p */
		s1 = p - r;

		/* compute vector t from r to q */
		t1 = q - r;

		/* now a couple of cross products */
		d1 = GeoLib::CrossProduct(s1, t1);
		d2 = GeoLib::CrossProduct(r, t1);

		/* can p improve the basis? */
		if (GeoLib::DotProduct(d1, d2) >= 0)
		{
			/* nope! send back B as is. */
			return;
		}

		break;

	case 3:
		/* fetch coordinates from the mesh */
		q = B[0];
		r = B[1];
		s = B[2];

		/* does p improve the basis? */
		if (Geometry_Tools::Oriented(p, q, r, s)*Geometry_Tools::Oriented(origin, q, r, s) <= 0)
		{
			/* nope! send back B as is. */
			return;
		}

		break;

	default:
		/* B has size of 4, and any basis of this size is optimal */
		return;
		break;
	}

	/* if we have made it this far, we know that p actually is a part of
	any basis of S union M */

	/* if p was the last element of M, or if S already has three other basis
	points, we're done and just need to send back S union p. */
	if ((SizeM == 1) || (SizeS == 3))
	{
		/* the final size of B is the size of S + 1 */
		SizeB = SizeS + 1;

		/* copy S into B */
		for (Standard_Integer i = 0; i < SizeS; i++)
		{
			B[i] = S[i];
		}

		/* and add p at the end */
		B[SizeB - 1] = p;

		return;
	}
	/* there may be more basis points to find! move p from M to the known
	basis point set S, and go again */
	else
	{
		/* create the new S */
		for (Standard_Integer i = 0; i < SizeS; i++)
		{
			localS[i] = S[i];
		}

		/* add p to the end of it */
		localS[SizeS] = p;

		/* create the new M, leaving off the last element */
		for (Standard_Integer i = 0; i < SizeM - 1; i++)
		{
			localM[i] = M[i];
		}

		/* find any basis points remaining in M */
		FindBasis(localS, localM, B, SizeS + 1, SizeM - 1, SizeB);

		return;
	}
}

void AutLib::MeshLib::Mesh3d_OptimizationTools::GetActiveSet
(
	const TColMesh3d_HAry1dOfOptimizationTetInfo & theElements,
	const Standard_Real theActiveSetFactor,
	TColGeom_Ary1dOfPnt3d & theActiveGrads
)
{
	TColGeom_BasicQueueOfPnt3d QActives;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theElements)
	)
	{
		Debug_Null_Pointer(theElements[Index]);
		if (theElements[Index]->Quality() <= theActiveSetFactor) { QActives.EnQueue(theElements[Index]->QualityGradient()); }
	}
	QActives.RetrieveTo(theActiveGrads);
}
