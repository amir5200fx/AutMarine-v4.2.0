#pragma once
#ifndef _Duct_Hull_Header
#define _Duct_Hull_Header

#include <Cad3d_MarineModel.hxx>
#include <Duct_SectionList.hxx>
#include <Duct_XParameters.hxx>
#include <Duct_Parameters.hxx>
#include <Duct_Profiles.hxx>

#include <TColStd_Array2OfReal.hxx>
#include <TColgp_Array2OfPnt.hxx>

class Geom_Surface;

namespace AutLib
{
	namespace CadLib
	{

		class Duct_Hull : public Cad3d_MarineModel
		{

		private:

			Duct_SectionList theSections_;

			Duct_XParameters theXParameters_;

			Duct_Parameters theParameters_;

			Duct_Profiles theProfiles_;

			Standard_Boolean Apply_Smoothing_;
			Standard_Boolean IsDone_;

			Handle(Geom_Surface) theHull_;
			Global_Handle(TColgp_Array2OfPnt) theControlNet_;
			Global_Handle(TColStd_Array2OfReal) theWeightNet_;

			Standard_String theIgesSectionFileName_;

		public:

			Duct_Hull();

			Duct_Hull(const Duct_Hull&) = delete;

			Duct_Hull& operator=(const Duct_Hull&) = delete;

			virtual ~Duct_Hull();

			Duct_Parameters& Parameters();

			const Duct_Parameters& Parameters() const;

			void Make();

		private:

			void DefaultParameters();

			void AllocateMemory();

			/* Create Profiles */

			void CreateBredthProfile();

			void CreateDepthProfile();

			void CreateProfiles();

			/* Calculate parameters*/

			void CalcxXSections();

			void CalcxYSections();

			void CalcxZSections();

			void CalcxDepth();

			void CalcxUpperTightness();

			void CalcxLowerTightness();

			void CalcxSideSlope();

			void CalcxWidth();

			void CalcxParameters();

			/* Section Constructors*/

			Global_Handle(Duct_SectionControlPoints) CreateSection(const Standard_Integer Section) const;

			void CreateSections();

			/*Setup hull*/

			void SetupControlNet();

			void SetupPatch();

			void MakeFace();
		};
	}
}

#include <Duct_HullI.hxx>

#endif // !_Duct_Hull_Header
