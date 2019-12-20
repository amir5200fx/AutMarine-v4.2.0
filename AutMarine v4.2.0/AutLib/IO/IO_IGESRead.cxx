#include <IO_IGESRead.hxx>

#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>

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
#include <Global_Debug.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::IoLib::IO_IGESRead::ReadFile
(
	const Standard_String& FileName, 
	TopoDS_Shape & Shape,
	const Standard_Real Deflection, 
	const Standard_Real Angle
)
{
	IGESControl_Reader myIgesReader;
	myIgesReader.ReadFile(FileName.c_str());

	Handle(TColStd_HSequenceOfTransient) myList = myIgesReader.GiveList("iges-faces");

	Standard_Integer nIgesFaces, nTransFaces;
	nIgesFaces = myList->Length();
	nTransFaces = myIgesReader.TransferList(myList);

	cout << "IGES Faces: " << nIgesFaces << "   Transferred:" << nTransFaces << endl;

	Shape = myIgesReader.OneShape();

	/*BRepBuilderAPI_Sewing Sewing(1.0e-3);
	Sewing.Add(Shape);

	Sewing.Perform();
	Shape = Sewing.SewedShape();

	cout << "  Nb. Of Free edges = " << Sewing.NbFreeEdges() << endl;*/
	

	/*cout << "Is Closed = " << Shape.Closed() << endl;
	PAUSE;*/

	if (Shape.IsNull())
	{
		CloseProgram("IGES Read has been Failed: IGES has no shape");
	}

	/*Handle(ShapeFix_Shape) FixShape = new ShapeFix_Shape;

	FixShape->Init(Shape);

	FixShape->SetPrecision(1.0E-4);
	FixShape->SetMaxTolerance(1.0E-4);
	FixShape->SetMinTolerance(1.0E-4);
	FixShape->Perform();*/

	/*cout << FixShape->Status(ShapeExtend_OK) << endl;
	cout << FixShape->Status(ShapeExtend_DONE1) << endl;
	cout << FixShape->Status(ShapeExtend_DONE2) << endl;
	cout << FixShape->Status(ShapeExtend_DONE3) << endl;
	cout << FixShape->Status(ShapeExtend_DONE4) << endl;
	cout << FixShape->Status(ShapeExtend_DONE5) << endl;
	cout << FixShape->Status(ShapeExtend_DONE6) << endl;
	cout << FixShape->Status(ShapeExtend_DONE7) << endl;
	cout << FixShape->Status(ShapeExtend_DONE8) << endl;
	PAUSE;*/

	//Shape = FixShape->Shape();

	/*Handle(ShapeFix_Wireframe) SFWF = new ShapeFix_Wireframe(Shape);
	SFWF->SetPrecision(1.0E-4);
	SFWF->SetMaxTolerance(1.0E-4);
	SFWF->SetMinTolerance(1.0E-4);

	SFWF->ModeDropSmallEdges() = Standard_True;
	SFWF->FixSmallEdges();

	SFWF->FixWireGaps();

	Shape = SFWF->Shape();*/

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = Deflection;
	Params.Angle = Angle;

	Bnd_Box Box;
	BRepBndLib::Add(Shape, Box);

	BRepMesh_FastDiscret Mesh(Box, Params);

	Mesh.Perform(Shape);

	cout << " IGES File Imported Successfully" << endl;
}

void AutLib::IoLib::IO_IGESRead::ReadFileNonDiscretized(const Standard_String & FileName, TopoDS_Shape & Shape)
{
	IGESControl_Reader myIgesReader;
	myIgesReader.ReadFile(FileName.c_str());

	Handle(TColStd_HSequenceOfTransient) myList = myIgesReader.GiveList("iges-faces");

	Standard_Integer nIgesFaces, nTransFaces;
	nIgesFaces = myList->Length();
	nTransFaces = myIgesReader.TransferList(myList);

	Shape = myIgesReader.OneShape();

	Handle(ShapeFix_Shape) FixShape = new ShapeFix_Shape;

	FixShape->Init(Shape);

	FixShape->SetPrecision(1.0E-6);
	FixShape->SetMaxTolerance(1.0E-2);
	FixShape->SetMinTolerance(1.0E-6);
	FixShape->Perform();

	Shape = FixShape->Shape();

	if (Shape.IsNull())
	{
		CloseProgram("IGES Read has been Failed: IGES has no shape");
	}
}

//void AutLib::IoLib::IO_IGESRead::ReadFile
//(
//	const Standard_String & FileName, 
//	CadLib::Cad3d_Solid & theSolid,
//	const Standard_Real Deflection, 
//	const Standard_Real Angle, 
//	const Standard_Real Tolerance,
//	const Standard_Real Discrete
//)
//{
//	IGESControl_Reader myIgesReader;
//	myIgesReader.ReadFile(FileName.c_str());
//
//	Handle(TColStd_HSequenceOfTransient) myList = myIgesReader.GiveList("iges-faces");
//
//	TopoDS_Shape Shape = myIgesReader.OneShape();
//
//	if (Shape.IsNull())
//	{
//		CloseProgram("IGES Read has been Failed: IGES has no shape");
//	}
//
//	BRepMesh_FastDiscret::Parameters Params;
//	Params.Deflection = Deflection;
//	Params.Angle = Angle;
//
//	if (Discrete)
//	{
//		Bnd_Box Box;
//		BRepBndLib::Add(Shape, Box);
//
//		BRepMesh_FastDiscret Mesh(Box, Params);
//
//		Mesh.Perform(Shape);
//	}
//
//	Cad3d_SolidTools::MakeSolid(Shape, theSolid);
//}