#include <IO_STEPRead.hxx>

#include <Global_Debug.hxx>

#include <TopoDS_Shape.hxx>
#include <TopoDS_TShape.hxx>
#include <TopExp_Explorer.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_Wireframe.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <IGESControl_Reader.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <STEPControl_Reader.hxx>

void AutLib::IoLib::IO_STEPRead::ReadFile
(
	const Standard_String & FileName,
	TopoDS_Shape & Shape,
	const Standard_Real Deflection,
	const Standard_Real Angle
)
{
	STEPControl_Reader Reader;
	Reader.ReadFile(FileName.c_str());

	Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("iges-faces");

	Standard_Integer nStepFaces, nTransFaces;
	nStepFaces = myList->Length();
	nTransFaces = Reader.TransferList(myList);

	cout << "STEP Faces: " << nStepFaces << "   Transferred:" << nTransFaces << endl;

	Shape = Reader.OneShape();

	if (Shape.IsNull())
	{
		CloseProgram("IGES Read has been Failed: IGES has no shape");
	}

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = Deflection;
	Params.Angle = Angle;

	Bnd_Box Box;
	BRepBndLib::Add(Shape, Box);

	BRepMesh_FastDiscret Mesh(Box, Params);

	Mesh.Perform(Shape);

	cout << " IGES File Imported Successfully" << endl;
}

void AutLib::IoLib::IO_STEPRead::ReadFileNonDiscretized
(
	const Standard_String & FileName, 
	TopoDS_Shape & Shape
)
{
	STEPControl_Reader Reader;
	Reader.ReadFile(FileName.c_str());

	Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("step-faces");

	Standard_Integer nStepFaces, nTransFaces;
	nStepFaces = myList->Length();
	nTransFaces = Reader.TransferList(myList);

	cout << "STEP Faces: " << nStepFaces << "   Transferred:" << nTransFaces << endl;

	Shape = Reader.OneShape();

	Handle(ShapeFix_Shape) FixShape = new ShapeFix_Shape;

	/*FixShape->Init(Shape);

	FixShape->SetPrecision(1.0E-6);
	FixShape->SetMaxTolerance(1.0E-4);
	FixShape->SetMinTolerance(1.0E-8);
	FixShape->Perform();*/

	if (Shape.IsNull())
	{
		CloseProgram("IGES Read has been Failed: IGES has no shape");
	}
}