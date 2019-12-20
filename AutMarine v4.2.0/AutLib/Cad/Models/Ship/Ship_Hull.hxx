#pragma once
#ifndef _Ship_Hull_Header
#define _Ship_Hull_Header

#include <Cad3d_MarineModel.hxx>
#include <Ship_SectionList.hxx>
#include <Ship_XParameters.hxx>
#include <Ship_Parameters.hxx>
#include <Ship_Profiles.hxx>
#include <Ship_ShipParameterProfile.hxx>

#include <TColgp_Array2OfPnt.hxx>

class Geom_Surface;

namespace AutLib
{
	namespace GeoLib
	{
		class Geom_Pnt3d;
	}

	namespace CadLib
	{

		class Ship_Hull : public Cad3d_MarineModel
		{

		private:

			Ship_SectionList theSections_;

			Ship_XParameters theXParameters_;

			Ship_Parameters theParameters_;

			Ship_Profiles theProfiles_;

			Standard_Boolean Apply_Smoothing_;
			Standard_Boolean IsDone_;

			Handle(Geom_Surface) theHull_;
			Global_Handle(TColgp_Array2OfPnt) theControlNet_;

			TopoDS_Shape mySections_;

			Standard_String theIgesSectionFileName_;

		public:

			Ship_Hull();

			Ship_Hull(const Ship_Hull&) = delete;

			Ship_Hull& operator = (const Ship_Hull&) = delete;

			virtual ~Ship_Hull();

			virtual Global_Handle(Cad3d_Solid) GetSolid() const;

			const Ship_Profiles& Profiles() const;

			Ship_Parameters& Parameters();

			TopoDS_Shape GetStation(const Standard_Real theX) const;

			TopoDS_Shape GetButtock(const Standard_Real theY) const;

			TopoDS_Shape GetWater(const Standard_Real theZ) const;

			void CalcMyStations(const Standard_Integer theNbSections, const Standard_Real theXmin, const Standard_Real theXmax);

			void CalcMyButtocks(const Standard_Integer theNbSections, const Standard_Real theYmin, const Standard_Real theYmax);

			void CalcMyWaters(const Standard_Integer theNbSections, const Standard_Real theZmin, const Standard_Real theZmax);

			virtual void Make();

			void ExportMySectionsToPlt(fstream& File) const;

			void ExportMySectionsToIGES() const;

		private:

			void DefaultParameters();

			void AllocateMemory();

			/* Create Curves */

			void CreateDeckProfile();

			void CreateFlareProfile();

			void CreateFlareProfile(const Standard_Integer Section);

			/* Calculate parameters*/

			void CalcxXSections();

			//! Throw an exception
			void CalcxYSections();

			void CalcxZSections();

			void CalcxDepthSections();

			void CalcxDeadRise();

			void CalcxFlare();

			void CalcxSideSlope();

			void CalcxTightness();

			void CalcxRake();

			void CalcXSheer();  // Need to be modified

			void CalcxParameters();

			/* Apply parameters */

			void ApplyTightness();

			void ApplyFlare();

			void ApplyRake();

			void ApplyForeFootShape();

			void ApplyBowSmoothness();

			void ApplyParameters();

			void ApplyTightness(Ship_SectionControlPoints & Section, const Standard_Real Tightness);

			void ApplyFlare(Standard_Integer Section);

			void ApplyRake(Ship_SectionControlPoints & Section, const Standard_Real Rake);

			/* Section Constructors*/
			Global_Handle(Ship_SectionControlPoints) CreateRawSection(const Standard_Integer Section, const Standard_Integer nbWidth, const Standard_Integer nbHeight);

			Global_Handle(Ship_SectionControlPoints) CreateRawStem();

			Global_Handle(Ship_SectionControlPoints) CreateRawStemPaired();

			void CreateRawSections();

			/*Setup hull*/

			void SetupControlNet();

			void SetupPatch();

			void SetSection(const Standard_Integer Index, Global_Handle(Ship_SectionControlPoints) Section);

			void SetControlPoint(const Standard_Integer I, const Standard_Integer J, const GeoLib::Geom_Pnt3d & Coord);

			void MakeFace();

			void MakeSolid();
		};
	}
}

#include <Ship_HullI.hxx>

#endif // !_Ship_Hull_Header
