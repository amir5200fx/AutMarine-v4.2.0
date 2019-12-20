#include <Mesh3d_QualityMap3dTools.hxx>

#include <Mesh3d_Element.hxx>
#include <Mesh3d_OptTetInfo.hxx>
#include <TColGeom_BasicQueueOfPnt3d.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>

#include <Geom\Shewchuk\predicates.h>
#include <assert.h>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

namespace AutLib
{
	namespace MeshLib
	{

		static void ArrangeNodes(const Global_Handle(Mesh3d_Node) theNode, Global_Handle(Mesh3d_Node)& Node0, Global_Handle(Mesh3d_Node)& Node1, Global_Handle(Mesh3d_Node)& Node2, Global_Handle(Mesh3d_Node)& Node3)
		{
			TColMesh3d_HAry1dOfNode Nodes(4);
			Nodes[0] = Node0;
			Nodes[1] = Node1;
			Nodes[2] = Node2;
			Nodes[3] = Node3;

			Standard_Integer I3;
			if (theNode EQUAL Node0) I3 = 0;
			else if (theNode EQUAL Node1) I3 = 1;
			else if (theNode EQUAL Node2) I3 = 2;
			else if (theNode EQUAL Node3) I3 = 3;
			else THROW_STANDARD_EXCEPTION("Contradictory data");

			Standard_Integer I0 = (I3 + 1) % 4;
			Standard_Integer I1 = (I0 + 1) % 4;
			Standard_Integer I2 = (I1 + 1) % 4;

			Node0 = Nodes[I0];
			Node1 = Nodes[I1];
			Node2 = Nodes[I2];
			Node3 = Nodes[I3];
		}
	}
}

void AutLib::MeshLib::Mesh3d_QualityMap3dTools::CalcOptInfo
(
	const Global_Handle(Mesh3d_Node) theNode,
	Mesh3d_OptTetInfo & opttet,
	const QualityMap3d_TypesInfo theType,
	const Standard_Real theSineWarpFactor
)
{
	Standard_Real point[4][3];       /* the vertices of the tet */
	Standard_Real edgelength[3][4];  /* the lengths of each of the edges of the tet */
	Standard_Real edgegrad[3][4][3]; /* the gradient of each edge length wrt vtx1 */
	Standard_Real facenormal[4][3];  /* the normals of each face of the tet */
	Standard_Real facearea[4];       /* areas of the faces of the tet */
	Standard_Real facegrad[4][3];    /* the gradient of each of the face areas wrt vtx1 */
	Standard_Real volume;            /* volume of tetrahedron */
	Standard_Real volumegrad[3] = { 0.0, 0.0, 0.0 };     /* the gradient of the volume of the tet wrt vtx1 */
	int i, j, k, l;           /* loop indices */
	int edgecount = 0;          /* keep track of current edge */
	Standard_Real ejk[3];            /* vector representing edge from j to k */
	Standard_Real ejl[3];            /* vector representing edge from j to l */
	Standard_Real t[3];
	Standard_Real u[3];
	Standard_Real v[3];
	Standard_Real e1[3] = { 0.0, 0.0, 0.0 };
	Standard_Real e2[3] = { 0.0, 0.0, 0.0 };

	/* temporary variables */
	Standard_Real diff[3];
	Standard_Real term1[3];
	Standard_Real term2[3];
	Standard_Real factor;
	Standard_Real c;
	Standard_Real top, bot;
	Standard_Real gradtop[3];
	Standard_Real gradbot[3];
	Standard_Real gradquot[3];

	/* radius ratio vars */
	Standard_Real Z;
	Standard_Real twooverZ;
	Standard_Real gradZtfac, gradZufac, gradZvfac;
	Standard_Real gradZt[3];
	Standard_Real gradZu[3];
	Standard_Real gradZv[3];
	Standard_Real gradZ[3];
	Standard_Real faceareasum;
	Standard_Real rootZareasum;
	Standard_Real facegradsum[3];
	Standard_Real vdott;
	Standard_Real tdotu;
	Standard_Real udotv;
	Standard_Real tlen2;
	Standard_Real ulen2;
	Standard_Real vlen2;
	Standard_Real uminusv[3];
	Standard_Real vminust[3];
	Standard_Real tminusu[3];
	Standard_Real umvlen2;
	Standard_Real vmtlen2;
	Standard_Real tmulen2;
	Standard_Real normfac = sqrt(3.0) * 6.0;
	Standard_Real rnrrgradterm1[3], rnrrgradterm2[3];

	/* V / lrms^3 ratio vars */
	Standard_Real edgelengthsum = 0.0;
	Standard_Real lrms;
	Standard_Real gradlrms[3];
	Standard_Real vlrmsterm1[3];
	Standard_Real vlrmsterm2[3];

	Get_Const_Object(Element) = opttet.theElement_;

	Get_Pointer(Node0) = Element.Node(0);
	Get_Pointer(Node1) = Element.Node(1);
	Get_Pointer(Node2) = Element.Node(2);
	Get_Pointer(Node3) = Element.Node(3);

	Debug_Null_Pointer(Node0);
	Debug_Null_Pointer(Node1);
	Debug_Null_Pointer(Node2);
	Debug_Null_Pointer(Node3);

	ArrangeNodes(theNode, Node0, Node1, Node2, Node3);

	Get_Const_Object(P0) = Node0->Coord();
	Get_Const_Object(P1) = Node1->Coord();
	Get_Const_Object(P2) = Node2->Coord();
	Get_Const_Object(P3) = Node3->Coord();

	point[0][0] = P0.X();
	point[0][1] = P0.Y();
	point[0][2] = P0.Z();
	point[1][0] = P2.X();
	point[1][1] = P2.Y();
	point[1][2] = P2.Z();
	point[2][0] = P1.X();
	point[2][1] = P1.Y();
	point[2][2] = P1.Z();
	point[3][0] = P3.X();
	point[3][1] = P3.Y();
	point[3][2] = P3.Z();

	volume = orient3d(point[0], point[1], point[2], point[3]);

	if (volume < 0)
	{
		point[1][0] = P1.X();
		point[1][1] = P1.Y();
		point[1][2] = P1.Z();
		point[2][0] = P2.X();
		point[2][1] = P2.Y();
		point[2][2] = P2.Z();

		volume = orient3d(point[0], point[1], point[2], point[3]);
	}

	/* set some vectors */
	vsub(point[1], point[0], t);
	vsub(point[2], point[0], v);
	vsub(point[3], point[0], u);

	/* calculate the volume*6 of the tetrahedron */
	volume /= 6;
	opttet.volume = volume;
	
	if (volume < 0) { THROW_STANDARD_EXCEPTION("Reverse Element: volume < 0"); }
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
		/* for each vertex i in the loop, the ith face is the face
		opposite i, so that face's normal is found by taking the
		cross product of two edges of the opposite face */
		/* TODO implement this cross product with Orient2D calls? */

		/* one edge on opposite face */
		vsub(point[k], point[j], ejk);

		/* another edge originating from the same vertex */
		vsub(point[l], point[j], ejl);

		/* compute a normal vector to this face */
		cross(ejk, ejl, facenormal[i]);

		/* if i=0, this is also the gradient of the volume * 6
		with respect to vertex 0 */
		if (i == 0)
		{
			opttet.volumegrad[0] = volumegrad[0] = -facenormal[i][0] / 6.0;
			opttet.volumegrad[1] = volumegrad[1] = -facenormal[i][1] / 6.0;
			opttet.volumegrad[2] = volumegrad[2] = -facenormal[i][2] / 6.0;
		}

		/* compute (2 *area)^2 for this face */
		facearea[i] = facenormal[i][0] * facenormal[i][0] +
			facenormal[i][1] * facenormal[i][1] +
			facenormal[i][2] * facenormal[i][2];
		/* now get the real area */
		opttet.facearea[i] = facearea[i] = sqrt(facearea[i]) / 2.0;

		/* compute the gradient of the area for this face */
		if (i == 0)
		{
			/* this face doesn't include vtx1, gradient is zero */
			opttet.facegrad[i][0] = facegrad[i][0] = 0.0;
			opttet.facegrad[i][1] = facegrad[i][1] = 0.0;
			opttet.facegrad[i][2] = facegrad[i][2] = 0.0;
		}
		else
		{

			assert(facearea[i] > 0);
			/* gradient scaled by the face's area */
			factor = 1.0 / (4.0 * facearea[i]);

			/* handle each face separately */
			switch (i)
			{
				/* compute the area of face 1 using u and v */
			case 1:
				vcopy(u, e1);
				vcopy(v, e2);
				break;
			case 2:
				vcopy(t, e1);
				vcopy(u, e2);
				break;
			case 3:
				vcopy(v, e1);
				vcopy(t, e2);
				break;
			}

			/* find the vector from elk to elj */
			vsub(e1, e2, diff);

			/* compute first term of gradient */
			c = dot(e2, diff);
			term1[0] = c * e1[0];
			term1[1] = c * e1[1];
			term1[2] = c * e1[2];

			/* compute the second term */
			c = dot(e1, diff);
			term2[0] = c * e2[0];
			term2[1] = c * e2[1];
			term2[2] = c * e2[2];

			/* now, combine the terms, scaled with the 1/4A */
			opttet.facegrad[i][0] = facegrad[i][0] = factor * (term1[0] - term2[0]);
			opttet.facegrad[i][1] = facegrad[i][1] = factor * (term1[1] - term2[1]);
			opttet.facegrad[i][2] = facegrad[i][2] = factor * (term1[2] - term2[2]);
		}


		/* compute edge lengths for quality measures that need them */
		if (theType == QualityMap3d_MINSINE ||
			theType == QualityMap3d_WARPEDMINSINE ||
			theType == QualityMap3d_VLRMS3RATIO)
		{
			for (j = i + 1; j < 4; j++) {

				/* e1 is edge from point i to point j */
				vsub(point[j], point[i], e1);
				opttet.edgelength[i][j] = edgelength[i][j] = vlength(e1);

				/* also compute the gradient of the length of this edge */

				/* if vtx1 isn't one of the edge's endpoints, the gradent is zero */
				if (i != 0)
				{
					opttet.edgegrad[i][j][0] = edgegrad[i][j][0] = 0.0;
					opttet.edgegrad[i][j][1] = edgegrad[i][j][1] = 0.0;
					opttet.edgegrad[i][j][2] = edgegrad[i][j][2] = 0.0;
				}
				/* otherwise, it's in the negative direction of this edge,
				and scaled by edge length */
				else
				{
					factor = -1.0 / edgelength[i][j];
					vscale(factor, e1, edgegrad[i][j]);
					vcopy(edgegrad[i][j], opttet.edgegrad[i][j]);
				}
			}
		}
	}

	/* if the quality measure is minimum sine */
	if ((theType == QualityMap3d_MINSINE) ||
		(theType == QualityMap3d_WARPEDMINSINE))
	{
		/* for each edge in the tetrahedron */
		for (i = 0; i < 3; i++) {
			for (j = i + 1; j < 4; j++) {
				k = (i > 0) ? 0 : (j > 1) ? 1 : 2;
				l = 6 - i - j - k;

				/* compute the sine of this dihedral angle */
				opttet.sine[edgecount] = (3 * volume * edgelength[i][j]) / (2 * facearea[k] * facearea[l]);

				/* if we are warping the minimum sine */
				if (theType == QualityMap3d_WARPEDMINSINE)
				{
					/* and this is an obtuse angle */
					if (dot(facenormal[k], facenormal[l]) > 0)
					{
						/* scale the sin down by WARPFACTOR */
						opttet.sine[edgecount] *= theSineWarpFactor;
					}
				}

				/* compute the gradient of the sine

				we need the gradient of this expression:

				3 * V * lij
				------------
				2 * Ak * Al

				so, find the gradient of the top product, the bottom product, then the quotient
				*/
				top = volume * edgelength[i][j];
				bot = facearea[k] * facearea[l];

				/* find gradient of top */
				gradproduct(volume, edgelength[i][j], volumegrad, edgegrad[i][j], gradtop);

				/* find gradient of bottom */
				gradproduct(facearea[k], facearea[l], facegrad[k], facegrad[l], gradbot);

				/* now, find the gradient of the quotient */
				gradquotient(top, bot, gradtop, gradbot, gradquot);

				/* now scale with constant factor */
				c = 3.0 / 2.0;
				opttet.sinegrad[edgecount][0] = c * gradquot[0];
				opttet.sinegrad[edgecount][1] = c * gradquot[1];
				opttet.sinegrad[edgecount][2] = c * gradquot[2];

				/* if this is a facet vertex, project gradient onto facet */
				/*
				if (vtxkind == FACETVERTEX || vtxkind == FIXEDVERTEX)
				*/

				edgecount++;
			}
		}
	}

	/* compute stuff for radius ratio */
	if (theType == QualityMap3d_RADIUSRATIO)
	{
		/* compute intermediate quantity Z */
		Z = getZ(point[0], point[1], point[2], point[3]);

		twooverZ = 2.0 / Z;

		/* some dot products */
		vdott = dot(v, t);
		tdotu = dot(t, u);
		udotv = dot(u, v);

		/* some vector lengths */
		vsub(u, v, uminusv);
		vsub(v, t, vminust);
		vsub(t, u, tminusu);
		tlen2 = (t[0] * t[0]) + (t[1] * t[1]) + (t[2] * t[2]);
		ulen2 = (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]);
		vlen2 = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
		umvlen2 = (uminusv[0] * uminusv[0]) + (uminusv[1] * uminusv[1]) + (uminusv[2] * uminusv[2]);
		vmtlen2 = (vminust[0] * vminust[0]) + (vminust[1] * vminust[1]) + (vminust[2] * vminust[2]);
		tmulen2 = (tminusu[0] * tminusu[0]) + (tminusu[1] * tminusu[1]) + (tminusu[2] * tminusu[2]);

		/* compute Z's gradient */
		gradZtfac = twooverZ *
			(
			(ulen2 * vdott - vlen2 * tdotu) * (ulen2 - vlen2) -
				(ulen2 * vlen2 + tlen2 * udotv) * (umvlen2)
				);
		gradZufac = twooverZ *
			(
			(vlen2 * tdotu - tlen2 * udotv) * (vlen2 - tlen2) -
				(vlen2 * tlen2 + ulen2 * vdott) * (vmtlen2)
				);
		gradZvfac = twooverZ *
			(
			(tlen2 * udotv - ulen2 * vdott) * (tlen2 - ulen2) -
				(tlen2 * ulen2 + vlen2 * tdotu) * (tmulen2)
				);

		/* compute t, u, v components of gradient */
		vscale(gradZtfac, t, gradZt);
		vscale(gradZufac, u, gradZu);
		vscale(gradZvfac, v, gradZv);

		/* add the components together to form grad(Z) */
		vadd(gradZt, gradZu, gradZ);
		vadd(gradZv, gradZ, gradZ);

		/* compute sqrt (Z * (sum of face areas)) */
		faceareasum = opttet.facearea[0] +
			opttet.facearea[1] +
			opttet.facearea[2] +
			opttet.facearea[3];
		rootZareasum = sqrt(Z * faceareasum);

		/* set the actual root normalized radius ratio */
		opttet.rnrr = (normfac * volume) / rootZareasum;

		assert(opttet.rnrr > 0.0);

		/* sum of face gradients */
		vadd(facegrad[0], facegrad[1], facegradsum);
		vadd(facegrad[2], facegradsum, facegradsum);
		vadd(facegrad[3], facegradsum, facegradsum);

		/* compute the first term */
		vscale((1.0 / rootZareasum), volumegrad, rnrrgradterm1);

		/* compute the second term */
		vscale(Z, facegradsum, facegradsum);
		vscale(faceareasum, gradZ, gradZ);
		vadd(facegradsum, gradZ, rnrrgradterm2);
		vscale(volume / (2 * (rootZareasum * rootZareasum * rootZareasum)), rnrrgradterm2, rnrrgradterm2);

		/* finally, compute the gradient of the radius ratio */
		vsub(rnrrgradterm1, rnrrgradterm2, opttet.rnrrgrad);
		vscale(normfac, opttet.rnrrgrad, opttet.rnrrgrad);
	}

	/* if the quality measure is volume to edge length ratio */
	if (theType == QualityMap3d_VLRMS3RATIO)
	{
		/* for each edge in the tetrahedron */
		for (i = 0; i < 3; i++)
		{
			for (j = i + 1; j < 4; j++)
			{
				k = (i > 0) ? 0 : (j > 1) ? 1 : 2;
				l = 6 - i - j - k;

				/* accumulate edge length sum */
				edgelengthsum += edgelength[i][j] * edgelength[i][j];
			}
		}

		/* compute the root mean square */
		lrms = sqrt((1.0 / 6.0) * edgelengthsum);

		normfac = 6.0 * sqrt(2.0);

		/* compute the raw ratio */
		opttet.vlrms3r = (normfac * volume) / (lrms * lrms * lrms);
		//cout << "Quality = " << opttet.vlrms3r << endl;

		/* compute gradient of lrms */
		vadd(t, u, gradlrms);
		vadd(v, gradlrms, gradlrms);
		vscale((-1.0 / (6.0 * lrms)), gradlrms, gradlrms);

		/* compute the terms of the gradient of the ratio */
		vscale((1.0 / (lrms * lrms * lrms)), volumegrad, vlrmsterm1);
		vscale((3.0 * volume) / (lrms * lrms * lrms * lrms), gradlrms, vlrmsterm2);

		/* add terms and normalize */
		vsub(vlrmsterm1, vlrmsterm2, opttet.vlrms3rgrad);
		vscale(normfac, opttet.vlrms3rgrad, opttet.vlrms3rgrad);
	}
}

void AutLib::MeshLib::Mesh3d_QualityMap3dTools::GetActiveSet
(
	const TColMesh3d_HAry1dOfOptTetInfo & incidenttets,
	const Standard_Real ACTIVESETFACTOR,
	const Standard_Real worstqual,
	const QualityMap3d_TypesInfo theType,
	TColGeom_Ary1dOfPnt3d & activegrads
)
{
	TColGeom_BasicQueueOfPnt3d QActives;
	forThose
	(
		Index,
		0,
		MaxIndexOf(incidenttets)
	)
	{
		Debug_Null_Pointer(incidenttets[Index]);
		switch (theType)
		{
		case QualityMap3d_WARPEDMINSINE:
		case QualityMap3d_MINSINE:
			forThose(j, 0, 5)
			{
				/* is this close enough to the worst? */
				if (incidenttets[Index]->sine[j] < (worstqual * ACTIVESETFACTOR))
				{
					/* get the actual gradient value */
					QActives.EnQueue(getPoint(incidenttets[Index]->sinegrad[j]));
				}
			}
			break;
		case QualityMap3d_RADIUSRATIO:
			if (incidenttets[Index]->rnrr <= (worstqual * ACTIVESETFACTOR))
			{
				/* get the actual gradient value */
				QActives.EnQueue(getPoint(incidenttets[Index]->rnrrgrad));
			}
			break;
		case QualityMap3d_VLRMS3RATIO:
			if (incidenttets[Index]->vlrms3r <= (worstqual * ACTIVESETFACTOR))
			{
				/* get the actual gradient value */
				QActives.EnQueue(getPoint(incidenttets[Index]->vlrms3rgrad));
			}
			break;
		default:
			CloseProgram("i don't know how to compute the active set for qual measure");
			break;
		}
	}
	QActives.RetrieveTo(activegrads);
}

Standard_Real AutLib::MeshLib::Mesh3d_QualityMap3dTools::GetInitialAlpha
(
	const TColMesh3d_HAry1dOfOptTetInfo & incidenttets,
	const Geom_Pnt3d & d, 
	const Standard_Real r,
	const Standard_Real RateEpsilon,
	const QualityMap3d_TypesInfo theType,
	const Standard_Real worstqual
)
{
	int i, j;
	Standard_Real alpha = RealLast();
	Standard_Real newalpha;
	Standard_Real rate;
	Standard_Real x[3];

	for (i = 0; i < incidenttets.Size(); i++)
	{
		switch (theType)
		{
		case QualityMap3d_WARPEDMINSINE:
		case QualityMap3d_MINSINE:
			for (j = 0; j<6; j++)
			{
				/* if this function improves more slowly
				than any in the active set, then it might
				end up as the objective. */
				getPoint(d, x);
				rate = dot(x, incidenttets[i]->sinegrad[j]);
				if (rate + RateEpsilon < r)
				{
					/* compute the approximation of when this
					function will become the objective */
					newalpha = (incidenttets[i]->sine[j] - worstqual) / (r - rate);

					/* if this is smaller than our current step size,
					use it for the step size */
					if (newalpha < alpha)
					{
						alpha = newalpha;
					}
				}
			}
			break;
		case QualityMap3d_RADIUSRATIO:
			/* if this function improves more slowly
			than any in the active set, then it might
			end up as the objective. */
			getPoint(d, x);
			rate = dot(x, incidenttets[i]->rnrrgrad);
			if (rate + RateEpsilon < r)
			{
				/* compute the approximation of when this
				function will become the objective */
				newalpha = (incidenttets[i]->rnrr - worstqual) / (r - rate);

				/* if this is smaller than our current step size,
				use it for the step size */
				if (newalpha < alpha)
				{
					alpha = newalpha;
				}
			}
			break;
		case QualityMap3d_VLRMS3RATIO:
			/* if this function improves more slowly
			than any in the active set, then it might
			end up as the objective. */
			getPoint(d, x);
			rate = dot(x, incidenttets[i]->vlrms3rgrad);
			if (rate + RateEpsilon < r)
			{
				/* compute the approximation of when this
				function will become the objective */
				newalpha = (incidenttets[i]->vlrms3r - worstqual) / (r - rate);

				/* if this is smaller than our current step size,
				use it for the step size */
				if (newalpha < alpha)
				{
					alpha = newalpha;
				}
			}
			break;
		default:
			CloseProgram("i don't know how to compute alpha for qual measure");
			break;
		}
	}

	if (alpha < 0.0)
	{
		alpha = 0.0;
	}
	return alpha;
}