#include <FvVelocity2d.hxx>

#include <FvMaterial.hxx>
#include <FvEntity_BoundaryFace2d.hxx>
#include <FvEntity_Element2d.hxx>
#include <FvMesh2d.hxx>
#include <FvVariables2d.hxx>
#include <FvParameters.hxx>
#include <FvParameters_TimeConfig.hxx>
#include <FvSources2d_List.hxx>
#include <FvSources2d.hxx>
#include <FvSources2d_Pressure.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColStd_Ary1dOfInteger.hxx>

namespace AutLib
{
	namespace FvLib
	{
		static inline Geom_Pnt2d CalcSources(const FvEntity_Element2d& theElement, const FvSources2d_List& theSources, Geom_Pnt2d& SumMinusPressure)
		{
			Geom_Pnt2d Sum(0, 0);
			Geom_Pnt2d Pressure;
			forThose
			(
				Index,
				0, 
				MaxIndexOf(theSources)
			)
			{
				Debug_Null_Pointer(theSources[Index]);

				if (Global_DownCast(FvSources2d_Pressure, theSources[Index]))
				{
					Pressure = theSources[Index]->Value(theElement);
					continue;
				}

				Sum += theSources[Index]->Value(theElement);
			}

			SumMinusPressure = Sum;

			Sum += Pressure;

			MOVE(Sum);
		}

		static void BuildMatrix(const FvMesh2d& theMesh, const FvParameters& theParameters, const FvBC& theBoundaryCondition, const FvVariables2d& theVariables, const FvMaterial& theMaterial, const FvSources2d_List& theSources)
		{
			Standard_Real Density = theMaterial.Density().Value();
			Standard_Real Viscosity = theMaterial.Viscosity().Value();
			Standard_Real xsi;
			Standard_Real dt = theParameters.Time().Step();

			forThose(Ielm, 0, theMesh.NbElements() - 1)
			{
				Debug_Null_Pointer(theMesh.Element(Ielm));

				Get_Const_Object(Element) = *theMesh.Element(Ielm);

				TColStd_Ary1dOfReal aF(Element.NbFaces());
				TColStd_Ary1dOfInteger aFi(Element.NbFaces());
				Standard_Real aP = (Standard_Real)0.0;
				Standard_Integer n = 0;

				forThose(Iface, 0, Element.NbFaces() - 1)
				{
					Debug_Null_Pointer(Element.Face(Iface));

					Get_Const_Object(Face) = *Element.Face(Iface);

					const Global_Handle(FvEntity_BoundaryFace2d) Boundary = Global_DownCast(FvEntity_BoundaryFace2d, (Global_Handle(FvEntity_Face2d))&Face);
					if (NOT Boundary)
					{
						Debug_Null_Pointer(Face.Pair());
						Get_Const_Object(Pair) = *Face.Pair();

						Debug_Null_Pointer(Pair.Element());
						Get_Const_Object(Neighbor) = *Pair.Element();

						aFi.SetValue(Iface, Neighbor.Index());

						if (theVariables.Uf(Face.Index()) > 0) xsi = (Standard_Real)0.0;
						else xsi = (Standard_Real)1.0;

						aP += ((Standard_Real)1.0 - xsi)*Density*theVariables.Uf(Face.Index())*Face.Volume();
						aP += Viscosity*Face.Volume() / Face.d();

						aF[n] = xsi*Density*theVariables.Uf(Face.Index())*Face.Volume();
						aF[n] += -Viscosity*Face.Volume() / Face.d();

						++n;
					}
					else
					{

					}
				}

				aP += Density*Element.Volume() / dt;

				Geom_Pnt2d MinusPressure;
				Geom_Pnt2d B = CalcSources(Element, theSources, MinusPressure);

				Standard_Real bu = B.X();
				Standard_Real bv = B.Y();

				theVariables.SetHu(Element.Index(), MinusPressure.X());
				theVariables.SetHv(Element.Index(), MinusPressure.Y());

				theVariables.SetAp(Element.Index(), aP);

				theVariables.SetAmLength(Element.Index(), n + 1);
				theVariables.SetAm(Element.Index(), 0, Element.Index(), aP);

				forThose(Index, 0, n - 1)
				{
					theVariables.SetAm(Element.Index(), Index + 1, aFi[Index], aF[Index]);
				}

				theVariables.SetBu(Element.Index(), bu);
				theVariables.SetBv(Element.Index(), bv);
			}
		}
	}
}