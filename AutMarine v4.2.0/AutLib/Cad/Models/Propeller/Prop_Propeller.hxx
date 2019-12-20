#pragma once
#ifndef _Prop_Propeller_Header
#define _Prop_Propeller_Header

#include <Cad3d_MarineModel.hxx>
#include <Prop_XParameters.hxx>
#include <Prop_PropellerParameters.hxx>
#include <Prop_BladeProfiles.hxx>
#include <Prop_PropView.hxx>
#include <TColProp_HAry1dOfBladeFaces.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

#include <TopoDS_Shape.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_Propeller : public Cad3d_MarineModel
		{

		private:

			Prop_PropellerParameters theParameters_;

			Prop_XParameters theXParameters_;

			Prop_BladeProfiles theProfiles_;

			Prop_PropView thePropView_;

			TColProp_HAry1dOfBladeFaces theBlades_;

			TopoDS_Shape myBlades_;
			TopoDS_Shape myHub_;

		public:

			Prop_Propeller();

			const Prop_BladeProfiles& Profiles() const;

			const Prop_PropellerParameters& Parameters() const;

			Prop_PropellerParameters& Parameters();

			void Make();

			void ExportMyBladesToPlt(fstream& File) const;

			void ExportMyHubToPlt(fstream& File) const;

		private:

			void AllocateMemory();

			void DefaultParameters();

			/* Make Solid */

			void MakeClosedBlade();

			void MakeMyBlades();

			void MakeMyHub();

			void MakeMyProp();

			void DiscreteMyBlades(const Standard_Real Deflection = 0.05, const Standard_Real Angle = 0.1);

			void DiscreteMyHub(const Standard_Real Deflection = 0.05, const Standard_Real Angle = 0.1);

			void DiscreteMyProp(const Standard_Real Deflection = 0.2, const Standard_Real Angle = 0.2);

			/* Create Profiles*/

			void CreatePitchProfile();

			void CreateChordProfile();

			void CreateSkewProfile();

			void CreateCamberProfile();

			void CreateThicknessProfile();

			void CreateRakeProfile();

			void CreateProfiles();

			/* Calculate Parameters */

			void CalcXSections();

			void CalcXPitch();

			void CalcXSkew();

			void CalcXChord();

			void CalcXCamber();

			void CalcXThickness();

			void CalcXRake();

			void CalcXParameters();

			/* Create Sections */

			void CreateSections_NACA4Digits();

			void CreateSectionProfiles_NACA4Digits(int section);

			void CreateExpandedView(const Standard_Integer Section, const TColGeom_Ary1dOfPnt2d& theTF, const TColGeom_Ary1dOfPnt2d& theTB);

			void CreateUnWrappedView();

			void CreateWrappedView();

			void CreateBladeFaces();
		};
	}
}

#include <Prop_PropellerI.hxx>

#endif // !_Prop_Propeller_Header
