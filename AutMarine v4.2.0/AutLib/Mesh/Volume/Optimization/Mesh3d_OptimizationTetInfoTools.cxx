#include <Mesh3d_OptimizationTetInfoTools.hxx>

#include <Geometry_Tools.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_OptimizationTetInfo.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColStd_Ary1dOfReal.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

void AutLib::MeshLib::Mesh3d_OptimizationTetInfoTools::CalcInfo(Mesh3d_OptimizationTetInfo & theTet)
{
	static TColGeom_Ary1dOfPnt3d point(4);
	static TColGeom_Ary1dOfPnt3d facenormal(4);
	static TColStd_Ary1dOfReal facearea(4);
	static TColGeom_Ary1dOfPnt3d facegrad(4);

	Geom_Pnt3d volumegrad;

	Get_Const_Object(Element) = theTet.Element();

	point[0] = Element.Node(0)->Coord();
	point[1] = Element.Node(1)->Coord();
	point[2] = Element.Node(2)->Coord();
	point[3] = Element.Node(3)->Coord();

	Geom_Pnt3d t = point[1] - point[0];
	Geom_Pnt3d v = point[2] - point[0];
	Geom_Pnt3d u = point[3] - point[0];

	/* calculate the volume*6 of the tetrahedron using orientation */
	Standard_Real volume = Geometry_Tools::Oriented
	(
		point[0],
		point[1],
		point[2],
		point[3]
	);

	theTet.SetVolume(volume);

	Standard_Integer j, k, l;

	/* for each vertex/face of the tetrahedron */
	for (Standard_Integer i = 0; i < 4; i++)
	{
		j = (i + 1) & 3;

		if ((i & 1) == 0)
		{
			k = (i + 3) & 3;
			l = (i + 2) & 3;
		}
		else
		{
			k = (i + 2) & 3;
			l = (i + 3) & 3;
		}

		/* compute the normal for each face */
		/* for each vertex i in the loop, the ith face is the face
		opposite i, so that face's normal is found by taking the
		cross product of two edges of the opposite face */

		/* one edge on opposite face */
		Geom_Pnt3d ejk = point[k] - point[j];

		/* another edge originating from the same vertex */
		Geom_Pnt3d ejl = point[l] - point[j];

		/* compute a normal vector to this face */
		facenormal[i] = GeoLib::CrossProduct(ejk, ejl);

		/* if i=0, this is also the gradient of the volume * 6
		with respect to vertex 0 */

		if (i == 0)
		{
			volumegrad = -facenormal[i] / 6.0;
			theTet.SetVolumeGradient(volumegrad);
		}

		/* compute (2 *area)^2 for this face */
		facearea[i] = facenormal[i].TwoNormSQ();

		/* now get the real area */
		facearea[i] = sqrt(facearea[i]) / 2.0;
		theTet.SetFaceArea(i, facearea[i]);

		/* compute the gradient of the area for this face */
		if (i == 0)
		{
			/* this face doesn't include vtx1, gradient is zero */
			facegrad[i] = 0;
			theTet.SetFaceAreaGradient(i, facegrad[i]);
		}
		else
		{
			/* gradient scaled by the face's area */
			Standard_Real factor = 1.0 / (4.0 * facearea[i]);

			Geom_Pnt3d e1, e2;

			/* handle each face separately */
			switch (i)
			{
			case 1:
				e1 = u;
				e2 = v;

				break;

			case 2:
				e1 = t;
				e2 = u;

				break;

			case 3:
				e1 = v;
				e2 = t;

				break;
			}

			/* find the vector from elk to elj */
			Geom_Pnt3d diff = e1 - e2;

			/* compute first term of gradient */
			Standard_Real c = DotProduct(e2, diff);

			Geom_Pnt3d term1 = c*e1;

			/* compute the second term */
			c = DotProduct(e1, diff);

			Geom_Pnt3d term2 = c*e2;

			/* now, combine the terms, scaled with the 1/4A */
			facegrad[i] = factor*(term1 - term2);
			theTet.SetFaceAreaGradient(i, facegrad[i]);
		}
	}

	Standard_Real l1 = DistanceSQ(point[0], point[1]);
	Standard_Real l2 = DistanceSQ(point[1], point[2]);
	Standard_Real l3 = DistanceSQ(point[2], point[0]);
	Standard_Real l4 = DistanceSQ(point[0], point[3]);
	Standard_Real l5 = DistanceSQ(point[1], point[3]);
	Standard_Real l6 = DistanceSQ(point[2], point[3]);

	Standard_Real lrms = sqrt((1.0 / 6.0)*(l1 + l2 + l3 + l4 + l5 + l6));

	Standard_Real normfac = 6.0*SQRT2;

	theTet.SetQuality((normfac * volume) / (lrms * lrms * lrms));

	/* compute gradient of lrms */
	Geom_Pnt3d gradlrms = t + u;
	gradlrms += v;

	gradlrms *= (-1.0 / (6.0*lrms));

	/* compute the terms of the gradient of the ratio */
	Geom_Pnt3d vlrmsterm1 = (1.0 / (lrms*lrms*lrms))*volumegrad;
	Geom_Pnt3d vlrmsterm2 = (3.0*volume) / (lrms*lrms*lrms*lrms)*gradlrms;

	/* add terms and normalize */
	theTet.SetQualityGradient((vlrmsterm1 - vlrmsterm2)*normfac);
}