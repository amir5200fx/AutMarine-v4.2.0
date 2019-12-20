#include <Ship_Hull.hxx>

void AutLib::CadLib::Ship_Hull::DefaultParameters()
{
	Ship_Dimensions & Dimensions = theParameters_.Dimensions();

	Dimensions.SetNbNetColumns(12);
	Dimensions.SetNbNetRows(9);

	Dimensions.SetLengthOnDeck((Standard_Real)160.0);
	Dimensions.SetBeamOnDeck((Standard_Real)0.5*(Standard_Real)25.0);
	Dimensions.SetDepthAtBow((Standard_Real)18.0);
	Dimensions.SetDepthAtTransom((Standard_Real)18.0);
	Dimensions.SetDraft((Standard_Real)6.0);
	Dimensions.SetTransonHeight((Standard_Real)8.0);

	Get_Object(Hull)  = theParameters_.Hull();
	Hull.SetMaxAreaLocation((Standard_Real)0.5);
	Hull.SetFullnessFwd((Standard_Real)0.2);
	Hull.SetFullnessAft((Standard_Real)0.4);

	/* Forward section Parameters */
	Get_Object(Fwd)  = Hull.FwdForm();
	Fwd.SetTightness((Standard_Real)0.5);
	Fwd.SetDeadRise((Standard_Real)0.1);
	Fwd.SetSideSlope((Standard_Real)0.8);
	Fwd.SetFlare((Standard_Real)0.6);
	Fwd.SetSkeg((Standard_Real)0.0);

	/* Middle section Parameters */
	Get_Object(Mid)  = Hull.MidForm();
	Mid.SetTightness((Standard_Real)0.5);
	Mid.SetDeadRise((Standard_Real)0.0);
	Mid.SetSideSlope((Standard_Real)0.1);
	Mid.SetFlare((Standard_Real)0.0);
	Mid.SetSkeg((Standard_Real)0.0);

	/* Aft section Parameters */
	Get_Object(Aft)  = Hull.AftForm();
	Aft.SetTightness((Standard_Real)0.5);
	Aft.SetDeadRise((Standard_Real)0.0);
	Aft.SetSideSlope((Standard_Real)0.0);
	Aft.SetFlare((Standard_Real)0.0);
	Aft.SetSkeg((Standard_Real)0.0);

	Get_Object(Stem)  = theParameters_.Stem();
	Stem.SetBowRounding((Standard_Real)0.2);
	Stem.SetForeFootShape((Standard_Real)1.0);
	Stem.SetStemCurvature((Standard_Real)1.0);
	Stem.SetStemCurvaturePosition((Standard_Real)0.5);
	Stem.SetStemRake((Standard_Real)30.0);

	Get_Object(Transom)  = theParameters_.Transom();
	Transom.SetRake((Standard_Real)0.0);
	Transom.SetWidth((Standard_Real)0.6);

	Get_Object(Keel)  = theParameters_.Keel();
	Keel.SetKeelRisePoint((Standard_Real)0.6);
	Keel.SetKeelPosition((Standard_Real)0.5);
	Keel.SetKeelRiseTangent((Standard_Real)0.3);
	Keel.SetKeelTransomTangent((Standard_Real)0.2);

	Apply_Smoothing_ = Standard_True;
}
