#pragma once
#ifndef _Prop_PropellerParameters_Header
#define _Prop_PropellerParameters_Header

#include <Prop_HubForm.hxx>
#include <Prop_BladeForm.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_PropellerParameters
		{

		private:

			Prop_BladeForm theBlade_;

			Prop_HubForm theHub_;

			Standard_Real theDiameter_;
			Standard_Real theHubRadius_;

			Standard_Integer theNbBlades_;
			Standard_Integer theNbSections_;
			Standard_Integer theNbSpans_;

			Standard_Real theTipGap_;
			Standard_Real theTEGap_;

			Standard_Boolean RemoveHubApex_;

		public:

			Prop_PropellerParameters();

			const Prop_BladeForm& BladeParameters() const;

			const Prop_HubForm& HubParameters() const;

			Prop_BladeForm& BladeParameters();

			Prop_HubForm& HubParameters();

			Standard_Boolean RemoveHubApex() const;

			Standard_Integer NbBlades() const;

			Standard_Integer NbSections() const;

			Standard_Integer NbSpans() const;

			Standard_Real Diameter() const;

			Standard_Real HubRadius() const;

			Standard_Real TipGap() const;

			Standard_Real TEGap() const;

			void SetToRemoveHubApex();

			void SetNbBlades(const Standard_Integer theValue);

			void SetNbSections(const Standard_Integer theValue);

			void SetNbSpans(const Standard_Integer theValue);

			void SetDiameter(const Standard_Real theValue);

			void SetHubRadius(const Standard_Real theValue);

			void Report(Standard_OStream& theOstream) const;

			void Import(fstream& File);
		};
	}
}

#include <Prop_PropellerParametersI.hxx>

#endif // !_Prop_PropellerParameters_Header
