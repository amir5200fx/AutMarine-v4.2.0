#include <FvDiscreteDdt2d_Euler.hxx>

#include <Global_Macros.hxx>
#include <FvMesh2d.hxx>
#include <FvEntity_Element2d.hxx>
#include <FvMaterial_Density.hxx>
#include <FvParameters_TimeConfig.hxx>
#include <FvMatrix.hxx>
#include <FvVector.hxx>
#include <FvVectorField_Vector2d.hxx>

using namespace AutLib;
using namespace FvLib;

AutLib::FvLib::FvDiscreteDdt2d_Euler::FvDiscreteDdt2d_Euler
(
	FvMatrix & theAssembly,
	FvVectorField & theSources,
	FvVectorField & theX,
	const FvMesh2d & theMesh,
	const FvParameters_TimeConfig & theTimeConfig
)
	: FvDiscreteDdt2d(theAssembly, theSources, theX, theMesh)
	, theTimeConfig_(theTimeConfig)
{
}

namespace AutLib
{
	namespace FvLib
	{
		static void Assemble(FvMatrix & theMatrix, FvVectorField_Vector2d & theVector, const FvVectorField_Vector2d & theVector0, const Scalar Unsteady, const FvMesh2d& theMesh)
		{
			Get_Object(xSource) = theVector.xSource();
			Get_Object(ySource) = theVector.ySource();

			Get_Object(xSource0) = theVector0.xSource();
			Get_Object(ySource0) = theVector0.ySource();

			forThose
			(
				Index,
				0, 
				theMesh.NbElements() - 1
			)
			{
				Debug_Null_Pointer(Mesh.Element(Index));

				Get_Const_Object(Element) = *theMesh.Element(Index);

				theMatrix.AddValue(Element.Index(), 0, Unsteady);

				xSource.AddValue(Element.Index(), Unsteady*xSource0[Element.Index()]);
				ySource.AddValue(Element.Index(), Unsteady*ySource0[Element.Index()]);
			}
		}

		static void Assemble(FvMatrix & theMatrix, FvVectorField & theVector, const FvVectorField & theVector0, const Scalar Unsteady, const FvMesh2d& theMesh)
		{
			Global_Handle(FvVectorField_Vector2d) VectorField = Global_DownCast(FvVectorField_Vector2d, &theVector);
			Global_Handle(FvVectorField_Vector2d) VectorField0 = Global_DownCast(FvVectorField_Vector2d, (Global_Handle(FvVectorField_Vector2d))&theVector0);

			if (VectorField)
			{
				if (NOT VectorField0) { THROW_STANDARD_EXCEPTION("the fileds are not the same type"); }
				Assemble(theMatrix, *VectorField, *VectorField0, Unsteady, theMesh);
				return;
			}

			THROW_STANDARD_EXCEPTION("This VectorField not supported yet!");
		}
	}
}

void AutLib::FvLib::FvDiscreteDdt2d_Euler::Assemble
(
	const FvMaterial_Density & theDensity,
	const FvVectorField& theVector0
)
{
	Get_Const_Object(Mesh) = FvDiscrete2d::Mesh();

	const Scalar Density = theDensity.Value();
	const Scalar dt = TimeConfig().Step();
	const Scalar Unsteady = Density / dt;

	::Assemble(FvDiscrete2d::Assembly(), FvDiscrete2d::Source(), theVector0, Unsteady, Mesh);
}