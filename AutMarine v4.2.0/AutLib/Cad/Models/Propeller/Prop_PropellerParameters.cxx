#include <Prop_PropellerParameters.hxx>

#include <Standard_String.hxx>

static const Standard_Real DEFAULT_TIP_GAP = 0.002;
static const Standard_Real DEFAULT_TE_GAP = 0.005;

AutLib::CadLib::Prop_PropellerParameters::Prop_PropellerParameters()
	: theTipGap_(DEFAULT_TIP_GAP)
	, theTEGap_(DEFAULT_TE_GAP)
	, RemoveHubApex_(Standard_False)
{
}

void AutLib::CadLib::Prop_PropellerParameters::SetToRemoveHubApex()
{
	RemoveHubApex_ = Standard_True;
}

void AutLib::CadLib::Prop_PropellerParameters::SetNbBlades(const Standard_Integer theValue)
{
	theNbBlades_ = theValue;
}

void AutLib::CadLib::Prop_PropellerParameters::SetNbSections(const Standard_Integer theValue)
{
	theNbSections_ = theValue;
}

void AutLib::CadLib::Prop_PropellerParameters::SetNbSpans(const Standard_Integer theValue)
{
	theNbSpans_ = theValue;
}

void AutLib::CadLib::Prop_PropellerParameters::SetDiameter(const Standard_Real theValue)
{
	theDiameter_ = theValue;
}

void AutLib::CadLib::Prop_PropellerParameters::SetHubRadius(const Standard_Real theValue)
{
	theHubRadius_ = theValue;
}

void AutLib::CadLib::Prop_PropellerParameters::Import(fstream & File)
{
	Standard_String Temp;
	File >> Temp >> theNbBlades_;
	File >> Temp >> theDiameter_;
	File >> Temp >> theHubRadius_;
	File >> Temp >> theNbSections_;
	File >> Temp >> theNbSpans_;

	Get_Object(Blade) = BladeParameters();
	Get_Object(Pitch) = Blade.PitchForm();

	Standard_Real X;
	File >> Temp >> X;
	Pitch.SetRootPitch(X);

	File >> Temp >> X;
	Pitch.SetTipPitch(X);

	File >> Temp >> X;
	Pitch.SetRootSteep(X);

	File >> Temp >> X;
	Pitch.SetTipSteep(X);

	Get_Object(Skew) = Blade.SkewForm();
	File >> Temp >> X;
	Skew.SetTipSkew(X);

	File >> Temp >> X;
	Skew.SetRootSteep(X);

	File >> Temp >> X;
	Skew.SetTipSteep(X);

	Get_Object(Chord) = Blade.ChordForm();
	File >> Temp >> X;
	Chord.SetMaxChordLocation(X);

	File >> Temp >> X;
	Chord.SetMaxChord(X);

	File >> Temp >> X;
	Chord.SetRootChord(X);

	File >> Temp >> X;
	Chord.SetTipChord(X);  // 0

	File >> Temp >> X;
	Chord.SetRootWeight(X);

	File >> Temp >> X;
	Chord.SetTipWeight(X);

	Get_Object(Camber) = Blade.CamberForm();
	File >> Temp >> X;
	Camber.SetMaxCamberLocation(X);

	File >> Temp >> X;
	Camber.SetMaxCamber(X);

	File >> Temp >> X;
	Camber.SetRootCamber(X);

	File >> Temp >> X;
	Camber.SetTipCamber(X);

	File >> Temp >> X;
	Camber.SetRootWeight(X);

	File >> Temp >> X;
	Camber.SetTipWeight(X);

	Get_Object(Thickness) = Blade.ThicknessForm();
	File >> Temp >> X;
	Thickness.SetRootThickness(X);

	File >> Temp >> X;
	Thickness.SetTipThickness(X);

	File >> Temp >> X;
	Thickness.SetRootSteep(X);

	File >> Temp >> X;
	Thickness.SetTipSteep(X);

	Get_Object(Rake) = Blade.RakeForm();

	File >> Temp >> X;
	Rake.SetTipRake(X);

	Get_Object(Hub) = HubParameters();
	File >> Temp >> X;
	Hub.SetHubLength(X);

	File >> Temp >> X;
	Hub.SetHubWeight(X);

	File >> Temp >> X;
	Hub.SetShaftLength(X);

	File >> Temp >> X;
	Hub.SetShaftOffset(X);

	File >> Temp >> X;
	Hub.SetShaftRadius(X);
}