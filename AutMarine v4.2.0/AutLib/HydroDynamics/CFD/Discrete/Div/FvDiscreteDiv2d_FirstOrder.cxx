#include <FvDiscreteDiv2d_FirstOrder.hxx>

#include <Global_Macros.hxx>
#include <FvMesh2d.hxx>
#include <FvEntity_Element2d.hxx>
#include <FvEntity_Face2d.hxx>
#include <FvEntity_BoundaryFace2d.hxx>
#include <FvMatrix.hxx>
#include <FvVectorField.hxx>
#include <FvVectorField_Vector2d.hxx>
#include <FvVector.hxx>
#include <FvList_Label.hxx>
#include <FvList_Scalar.hxx>

using namespace AutLib;
using namespace FvLib;

AutLib::FvLib::FvDiscreteDiv2d_FirstOrder::FvDiscreteDiv2d_FirstOrder
(
	FvMatrix & theAssembly,
	FvVectorField & theSources,
	FvVectorField & theX, 
	const FvMesh2d & theMesh, 
	const FvVectorField & thePathces
)
	: FvDiscreteDiv2d(theAssembly, theSources, theX, theMesh)
	, thePatches_(thePathces)
{
}

AutLib::FvLib::FvDiscreteDiv2d_FirstOrder::~FvDiscreteDiv2d_FirstOrder()
{
}

namespace AutLib
{
	namespace FvLib
	{

		static void Assemble(FvMatrix & theMatrix, FvVectorField_Vector2d & theVector, const FvVector & thePhif, const FvVectorField_Vector2d & thePatches, const FvMesh2d& theMesh)
		{
			Get_Const_Object(xuf) = thePatches.xSource();
			Get_Const_Object(xvf) = thePatches.ySource();

			Get_Object(bu) = theVector.xSource();
			Get_Object(bv) = theVector.ySource();

			Scalar xsi;
			forThose
			(
				Index, 
				0,
				theMesh.NbElements() - 1
			)
			{
				Debug_Null_Pointer(theMesh.Element(Index));

				Get_Const_Object(Element) = *theMesh.Element(Index);

				Scalar app = (Scalar)0.0;
				Scalar bpu = (Scalar)0.0;
				Scalar bpv = (Scalar)0.0;
				FvList_Label anf(Element.NbFaces());
				FvList_Scalar apn(Element.NbFaces());

				Label n = 0;

				forThose
				(
					Iface,
					0,
					Element.NbFaces() - 1
				)
				{
					Debug_Null_Pointer(Element.Face(Iface));

					Get_Const_Object(Face) = *Element.Face(Iface);

					const Global_Handle(FvEntity_BoundaryFace2d) BoundaryFace = Global_DownCast(FvEntity_BoundaryFace2d, (Global_Handle(FvEntity_Face2d))&Face);
					if (BoundaryFace)
					{
						if (thePhif[Face.Index()] > (Scalar)0.0)
						{
							app += thePhif[Face.Index()] * Face.Area() / Element.Volume();
						}
						else
						{
							bpu += -thePhif[Face.Index()] * Face.Area()*xuf[Face.Index()] / Element.Volume();
							bpv += -thePhif[Face.Index()] * Face.Area()*xvf[Face.Index()] / Element.Volume();
						}
					}
					else
					{
						if (thePhif[Face.Index()] > (Scalar)0.0)
							xsi = (Scalar)0.0;
						else
							xsi = (Scalar)1.0;

						app += ((Scalar)1.0 - xsi)*thePhif[Face.Index()] * Face.Area() / Element.Volume();

						apn[n] = xsi*thePhif[Face.Index()] * Face.Area() / Element.Volume();
						
						++n;
					}
				}

				theMatrix.AddValue(Element.Index(), 0, app);

				forThose(Iface, 0, n - 1)
				{
					theMatrix.AddValue(Element.Index(), Iface + 1, apn[Iface]);
				}

				bu.AddValue(Element.Index(), bpu);
				bv.AddValue(Element.Index(), bpv);
			}
		}

		static void Assemble(FvMatrix & theMatrix, FvVectorField & theVector, const FvVector & thePhif, const FvVectorField & thePatches, const FvMesh2d& theMesh)
		{
			Global_Handle(FvVectorField_Vector2d) VectorField = Global_DownCast(FvVectorField_Vector2d, &theVector);
			Global_Handle(FvVectorField_Vector2d) VectorFieldPatches = Global_DownCast(FvVectorField_Vector2d, (Global_Handle(FvVectorField_Vector2d))&thePatches);

			if (VectorField)
			{
				if (NOT VectorFieldPatches) { THROW_STANDARD_EXCEPTION("the fileds are not the same type"); }
				Assemble(theMatrix, *VectorField, thePhif, *VectorFieldPatches, theMesh);
				return;
			}

			THROW_STANDARD_EXCEPTION("This VectorField not supported yet!");
		}
	}
}

void AutLib::FvLib::FvDiscreteDiv2d_FirstOrder::Assemble
(
	const FvVector & thePhi,
	const FvVectorField & theVector0
)
{
	Get_Const_Object(Mesh) = FvDiscrete2d::Mesh();

	::Assemble(FvDiscrete2d::Assembly(), FvDiscrete2d::Source(), thePhi, thePatches_, Mesh);
}
