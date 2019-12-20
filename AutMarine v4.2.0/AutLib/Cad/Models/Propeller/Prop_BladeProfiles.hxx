#pragma once
#ifndef _Prop_BladeProfiles_Header
#define _Prop_BladeProfiles_Header

#include <Prop_ParameterProfile.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_BladeProfiles
		{

		private:

			Prop_ParameterProfile thePitch_;
			Prop_ParameterProfile theChord_;
			Prop_ParameterProfile theCamber_;
			Prop_ParameterProfile theSkew_;
			Prop_ParameterProfile theRake_;
			Prop_ParameterProfile theThickness_;

		public:

			Prop_BladeProfiles();

			const Prop_ParameterProfile& PitchProfile() const;

			const Prop_ParameterProfile& ChordProfile() const;

			const Prop_ParameterProfile& CamberProfile() const;

			const Prop_ParameterProfile& SkewProfile() const;

			const Prop_ParameterProfile& RakeProfile() const;

			const Prop_ParameterProfile& ThicknessProfile() const;

			void SetPitchProfile(const Prop_ParameterProfile& theProfile);

			void SetChordProfile(const Prop_ParameterProfile& theProfile);

			void SetCamberProfile(const Prop_ParameterProfile& theProfile);

			void SetSkewProfile(const Prop_ParameterProfile& theProfile);

			void SetRakeProfile(const Prop_ParameterProfile& theProfile);

			void SetThicknessProfile(const Prop_ParameterProfile& theProfile);

			void ExportPitchProfileToPlt(fstream& File) const;

			void ExportChordProfileToPlt(fstream& File) const;

			void ExportCamberProfileToPlt(fstream& File) const;

			void ExportSkewProfileToPlt(fstream& File) const;

			void ExportRakeProfileToPlt(fstream& File) const;

			void ExportThicknessProfileToPlt(fstream& File) const;
		};
	}
}

#include <Prop_BladeProfilesI.hxx>

#endif // !_Prop_BladeProfiles_Header
