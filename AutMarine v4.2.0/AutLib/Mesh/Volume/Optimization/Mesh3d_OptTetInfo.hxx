#pragma once
#ifndef _Mesh3d_OptTetInfo_Header
#define _Mesh3d_OptTetInfo_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Element;


		class Mesh3d_OptTetInfo
		{

		public:

			Mesh3d_OptTetInfo(const Mesh3d_Element& theElement) : theElement_(theElement) {}

			const Mesh3d_Element& theElement_;

			Standard_Real volume;            /* volume of tetrahedron */
			Standard_Real volumegrad[3];     /* the gradient of the volume of the tet wrt vtx1 */
			Standard_Real sine[6];           /* sine of each dihedral angle of the tet */
			Standard_Real sinegrad[6][3];    /* gradient of each sine */
			Standard_Real rnrr;              /* root normalized radius ratio */
			Standard_Real rnrrgrad[3];       /* gradient of root normalized radius ratio */
			Standard_Real vlrms3r;           /* V / lrms^3 ratio */
			Standard_Real vlrms3rgrad[3];    /* gradient thereof */
			Standard_Real edgelength[3][4];  /* the lengths of each of the edges of the tet */
			Standard_Real edgegrad[3][4][3]; /* the gradient of each edge length wrt vtx1 */
			Standard_Real facearea[4];       /* areas of the faces of the tet */
			Standard_Real facegrad[4][3];    /* the gradient of each of the face areas wrt vtx1 */
		};
	}
}

#endif // !_Mesh3d_OptTetInfo_Header
