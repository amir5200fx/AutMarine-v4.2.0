#include <Compound_Ship.hxx>

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepBuilderAPI_Transform.hxx>

AutLib::CadLib::Compound_Ship::Compound_Ship()
{
	DefaultParameters();
}

void AutLib::CadLib::Compound_Ship::Make()
{
	//theShip_.SetToDiscreteMyModel();
	theShip_.SetToMakeAsSolid();
	theShip_.Make();

	//theRudder_.SetToDiscreteMyModel();
	theRudder_.SetToMakeShaft();
	theRudder_.SetToMakeAsSolid();
	theRudder_.Make();

	thePropeller_.SetToMakeAsSolid();
	thePropeller_.Make();

	theSystems_.Init(theShip_.CoordinateSystem(), theRudder_.CoordinateSystem(), thePropeller_.CoordinateSystem());

	CalcSystems();
	
	theRudder_.TransformTo(theSystems_.RudderSystem());
	thePropeller_.TransformTo(theSystems_.PropellerSystem());

	MakeSolid();

	/*theShip_.DiscreteMyModel();
	theRudder_.DiscreteMyModel();
	thePropeller_.DiscreteMyModel(0.2);*/

	DiscreteMyModel();
}

void AutLib::CadLib::Compound_Ship::ExportToPlt(fstream & File) const
{
	theShip_.ExportMyModelToPlt(File);

	theRudder_.ExportMyModelToPlt(File);

	thePropeller_.ExportMyModelToPlt(File);
}

void AutLib::CadLib::Compound_Ship::DefaultParameters()
{
	theRudderParameters_.SetX(11);
	theRudderParameters_.SetY(6);
	theRudderParameters_.SetZ(6);
	theRudderParameters_.SetShaftInclination(0);

	thePropellerParameters_.SetX(14);
	thePropellerParameters_.SetY(6);
	thePropellerParameters_.SetZ(3);
	thePropellerParameters_.SetShaftInclination(5);
}

void AutLib::CadLib::Compound_Ship::CalcSystems()
{
	theSystems_.SetRudderSystem(theRudderParameters_);

	theSystems_.SetPropellerSystem(thePropellerParameters_);
}

void AutLib::CadLib::Compound_Ship::MakeSolid()
{
	gp_Trsf Mirror;
	Mirror.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));

	BRepBuilderAPI_Transform Transform(Mirror);
	Transform.Perform(thePropeller_.Shape(), Standard_True);
	TopoDS_Shape MirroredProp = Transform.Shape();

	gp_Trsf Trsf;
	Trsf.SetTranslation(gp_Vec(0, -2*theRudderParameters_.Y(), 0));

	BRepBuilderAPI_Transform Transform1(Trsf);
	Transform1.Perform(theRudder_.Shape(), Standard_True);
	TopoDS_Shape MirroredRudder = Transform1.Shape();

	myModel_ = BRepAlgoAPI_Common(theShip_.Shape(), theRudder_.Shape());
	myModel_ = BRepAlgoAPI_Common(myModel_, MirroredRudder);
	myModel_ = BRepAlgoAPI_Common(myModel_, thePropeller_.Shape());
	myModel_ = BRepAlgoAPI_Common(myModel_, MirroredProp);
}