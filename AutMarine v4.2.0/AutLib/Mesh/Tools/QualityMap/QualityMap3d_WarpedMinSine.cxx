#include <QualityMap3d_WarpedMinSine.hxx>

#include <Mesh3d_QualityMap3dTools.hxx>
#include <Geom\Shewchuk\predicates.h>

using namespace AutLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_WARPEDMINSIZE = 1.03;

AutLib::MeshLib::QualityMap3d_WarpedMinSine::QualityMap3d_WarpedMinSine()
	: theSineWarpFactor_(DEFAULT_WARPEDMINSIZE)
{
}

Standard_Real AutLib::MeshLib::QualityMap3d_WarpedMinSine::GetInitialAlpha
(
	const TColMesh3d_HAry1dOfOptTetInfo & incidenttets, 
	const Geom_Pnt3d & d,
	const Standard_Real r, 
	const Standard_Real RateEpsilon,
	const Standard_Real theWorst
) const
{
	return Mesh3d_QualityMap3dTools::GetInitialAlpha(incidenttets, d, r, RateEpsilon, QualityMap3d_WARPEDMINSINE, theWorst);
}

void AutLib::MeshLib::QualityMap3d_WarpedMinSine::GetActiveSet
(
	const TColMesh3d_HAry1dOfOptTetInfo & incidenttets,
	const Standard_Real theActiveSetFactor,
	const Standard_Real theWorst, 
	TColGeom_Ary1dOfPnt3d & theActiveGrads
) const
{
	Mesh3d_QualityMap3dTools::GetActiveSet(incidenttets, theActiveSetFactor, theWorst, QualityMap3d_WARPEDMINSINE, theActiveGrads);
}

void AutLib::MeshLib::QualityMap3d_WarpedMinSine::CalcOptInfo(const Global_Handle(Mesh3d_Node) theNode, Mesh3d_OptTetInfo & theTet) const
{
	Mesh3d_QualityMap3dTools::CalcOptInfo(theNode, theTet, QualityMap3d_WARPEDMINSINE, theSineWarpFactor_);
}

Standard_Real AutLib::MeshLib::QualityMap3d_WarpedMinSine::CalcQuality
(
	const Geom_Pnt3d & theP0,
	const Geom_Pnt3d & theP1, 
	const Geom_Pnt3d & theP2, 
	const Geom_Pnt3d & theP3
) const
{
	Standard_Real point[4][3];      /* the vertices of the tet */
	Standard_Real edgelength[3][4]; /* the lengths of each of the edges of the tet */
	Standard_Real facenormal[4][3]; /* the normals of each face of the tet */
	Standard_Real dx, dy, dz;       /* intermediate values of edge lengths */
	Standard_Real facearea2[4];     /* areas of the faces of the tet */
	Standard_Real pyrvolume;        /* volume of tetrahedron */
	Standard_Real sine2, minsine2;  /* the sine (squared) of the dihedral angle */
	int i, j, k, l;          /* loop indices */

	point[0][0] = theP0.X();
	point[0][1] = theP0.Y();
	point[0][2] = theP0.Z();
	point[1][0] = theP2.X();
	point[1][1] = theP2.Y();
	point[1][2] = theP2.Z();
	point[2][0] = theP1.X();
	point[2][1] = theP1.Y();
	point[2][2] = theP1.Z();
	point[3][0] = theP3.X();
	point[3][1] = theP3.Y();
	point[3][2] = theP3.Z();

							 /* calculate the volume*6 of the tetrahedron */
	pyrvolume = orient3d(point[0], point[1], point[2], point[3]);

	/* if the volume is zero, the quality is zero, no reason to continue */
	if (pyrvolume == 0.0)
	{
		return 0.0;
	}

	/* for each vertex/face of the tetrahedron */
	for (i = 0; i < 4; i++) {
		j = (i + 1) & 3;
		if ((i & 1) == 0) {
			k = (i + 3) & 3;
			l = (i + 2) & 3;
		}
		else {
			k = (i + 2) & 3;
			l = (i + 3) & 3;
		}

		/* compute the normal for each face */
		facenormal[i][0] =
			(point[k][1] - point[j][1]) * (point[l][2] - point[j][2]) -
			(point[k][2] - point[j][2]) * (point[l][1] - point[j][1]);
		facenormal[i][1] =
			(point[k][2] - point[j][2]) * (point[l][0] - point[j][0]) -
			(point[k][0] - point[j][0]) * (point[l][2] - point[j][2]);
		facenormal[i][2] =
			(point[k][0] - point[j][0]) * (point[l][1] - point[j][1]) -
			(point[k][1] - point[j][1]) * (point[l][0] - point[j][0]);

		/* compute (2 *area)^2 for this face */
		facearea2[i] = facenormal[i][0] * facenormal[i][0] +
			facenormal[i][1] * facenormal[i][1] +
			facenormal[i][2] * facenormal[i][2];

		/* compute edge lengths (squared) */
		for (j = i + 1; j < 4; j++) {
			dx = point[i][0] - point[j][0];
			dy = point[i][1] - point[j][1];
			dz = point[i][2] - point[j][2];
			edgelength[i][j] = dx * dx + dy * dy + dz * dz;
		}
	}

	minsine2 = RealLast();     /* start with absurdly big value for sine */

							  /* for each edge in the tetrahedron */
	for (i = 0; i < 3; i++) {
		for (j = i + 1; j < 4; j++) {
			k = (i > 0) ? 0 : (j > 1) ? 1 : 2;
			l = 6 - i - j - k;

			/* compute the expression for minimum sine, squared, over 4
			The reason it's over 4 is because the area values we have
			are actually twice the area squared */
			/* if either face area is zero, the sine is zero */
			if (facearea2[k] > 0 && facearea2[l] > 0)
			{
				sine2 = edgelength[i][j] / (facearea2[k] * facearea2[l]);
			}
			else
			{
				sine2 = 0.0;
			}

			/* check whether this angle is obtuse */
			if (dot(facenormal[k], facenormal[l]) > 0)
			{
				/* if so, warp it down */
				sine2 = sqrt(sine2)*theSineWarpFactor_;
				sine2 *= sine2;
			}

			/* update minimum sine */
			if (sine2 < minsine2)
			{
				minsine2 = sine2;
			}
		}
	}

	return sqrt(minsine2) * pyrvolume;
}