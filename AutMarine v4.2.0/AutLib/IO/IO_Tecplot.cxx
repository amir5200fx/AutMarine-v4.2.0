#include <IO_Tecplot.hxx>

#include <Standard_String.hxx>
#include <Standard_SStream.hxx>
#include <Geom_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_Box3d.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Entity_Triangulation3d.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <Primitive_Field.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>

using namespace AutLib;
using namespace GeoLib;

#define XY_Variables     "X Y"
#define XYZ_Variables    "X Y Z"

#define WriteTriangleIndices_GetNewLine(v1,v2,v3,Stream) \
  Stream << v1 _SPACE_ v2 _SPACE_ v3 _NEWLINE_

#define WriteTetrahedraIndices_GetNewLine(v1,v2,v3,v4,Stream) \
  Stream << v1 _SPACE_ v2 _SPACE_ v3 _SPACE_ v4 _NEWLINE_

#define Check_PointList(PointList) \
  if (NOT PointList.Size()) return

#define WriteIorderedZone_GetNewLine(NbOfPoints, Stream) \
  Stream << WriteIorderedZone(NbOfPoints) _NEWLINE_

#define WriteVariable_GetNewLine(VariablesString, Stream) \
  Stream << WriteVariables(VariablesString) _NEWLINE_

#define WriteFeTriangleZone_GetNewLine(NbOfPoints, NbOfTriangles, Stream) \
  Stream << WriteFeTriangleZone(NbOfPoints, NbOfTriangles) _NEWLINE_

//#define WriteFeTetrahedralZone_GetNewLine(NbOfPoints, NbOfTetrahedrals, Stream) \
//  Stream << WriteFeTetrahedralZone(NbOfPoints, NbOfTetrahedrals) _NEWLINE_

#define WriteFeTetrahedralZone_GetNewLine(NbOfPoints, NbOfTets, Stream) \
  Stream << WriteFeTetrahedralZone(NbOfPoints, NbOfTets) _NEWLINE_

#define WriteCellCenteredFeTetrahedralZone_GetNewLine(NbOfPoints, NbOfTets, NbOfVars, Stream) \
  Stream << WriteCellCenteredFeTetrahedralZone(NbOfPoints, NbOfTets, NbOfVars) _NEWLINE_

#define WriteCellCenteredFeTriangularZone_GetNewLine(NbOfPoints, NbOfTris, NbOfVars, Stream) \
  Stream << WriteCellCenteredFeTriangularZone(NbOfPoints, NbOfTris, NbOfVars) _NEWLINE_

#define WriteCellCenteredFeTriangular3DZone_GetNewLine(NbOfPoints, NbOfTris, NbOfVars, Stream) \
  Stream << WriteCellCenteredFeTriangular3DZone(NbOfPoints, NbOfTris, NbOfVars) _NEWLINE_

#define WriteFeBrickZone_GetNewLine(NbOfPoints, NbOfBricks, Stream) \
  Stream << WriteFeBrickZone(NbOfPoints, NbOfBricks) _NEWLINE_


#define WriteMapName_GetNewLine(String, Stream) \
  Stream << ", T= " << String _NEWLINE_

namespace AutLib
{
	namespace IoLib
	{

		static Standard_String WriteVariables(const Standard_String& VarString)
		{
			Standard_SStream Stream;
			Stream
				<< "VARIABLES = "
				<< VarString;

			return Stream.str();
		}

		static Standard_String WriteFeTriangleZone(const Standard_Integer NbNodes, const Standard_Integer NbTriangles)
		{
			Standard_SStream Stream;
			Stream
				<< "ZONE N= "
				<< NbNodes
				<< ", E = "
				<< NbTriangles
				<< ", DATAPACKING=POINT, ZONETYPE=FETRIANGLE";

			return Stream.str();
		}

		static Standard_String WriteFeTetrahedralZone(const Standard_Integer NbNodes, const Standard_Integer NbTets)
		{
			Standard_SStream Stream;
			Stream
				<< "ZONE N= "
				<< NbNodes
				<< ", E = "
				<< NbTets
				<< ", DATAPACKING=POINT, ZONETYPE=FETETRAHEDRON";

			return Stream.str();
		}

		static Standard_String WriteCellCenteredFeTetrahedralZone(const Standard_Integer NbNodes, const Standard_Integer NbTets, const Standard_Integer NbVar)
		{
			Standard_SStream Stream;
			Stream
				<< "ZONE N= "
				<< NbNodes
				<< ", E = "
				<< NbTets
				<< ", DATAPACKING=BLOCK, ZONETYPE=FETETRAHEDRON, VARLOCATION=([1,2,3]=NODAL, [";
			Standard_Integer K = 0;
			while (Standard_True)
			{
				Stream << 4 + K;
				++K;
				if (K >= NbVar) break;
				Stream << "  ";
			}
			Stream << "]=CELLCENTERED)\n";

			return Stream.str();
		}

		static Standard_String WriteCellCenteredFeTriangularZone(const Standard_Integer NbNodes, const Standard_Integer NbTris, const Standard_Integer NbVar)
		{
			Standard_SStream Stream;
			Stream
				<< "ZONE N= "
				<< NbNodes
				<< ", E = "
				<< NbTris
				<< ", DATAPACKING=BLOCK, ZONETYPE=FETRIANGLE, VARLOCATION=([1,2]=NODAL, [";
			Standard_Integer K = 0;
			while (Standard_True)
			{
				Stream << 3 + K;
				++K;
				if (K >= NbVar) break;
				Stream << "  ";
			}
			Stream << "]=CELLCENTERED)\n";

			return Stream.str();
		}

		static Standard_String WriteCellCenteredFeTriangular3DZone(const Standard_Integer NbNodes, const Standard_Integer NbTris, const Standard_Integer NbVar)
		{
			Standard_SStream Stream;
			Stream
				<< "ZONE N= "
				<< NbNodes
				<< ", E = "
				<< NbTris
				<< ", DATAPACKING=BLOCK, ZONETYPE=FETRIANGLE, VARLOCATION=([1,2,3]=NODAL, [";
			Standard_Integer K = 0;
			while (Standard_True)
			{
				Stream << 4 + K;
				++K;
				if (K >= NbVar) break;
				Stream << "  ";
			}
			Stream << "]=CELLCENTERED)\n";

			return Stream.str();
		}

		static Standard_String WriteFeBrickZone(const Standard_Integer NbNodes, const Standard_Integer NbBricks)
		{
			Standard_SStream Stream;
			Stream
				<< "ZONE N= "
				<< NbNodes
				<< ", E = "
				<< NbBricks
				<< ", DATAPACKING=POINT, ZONETYPE=FEBRICK";

			return Stream.str();
		}

		static Standard_String WriteIorderedZone(const Standard_Integer NbNodes)
		{
			Standard_SStream Stream;
			Stream
				<< "ZONE I= "
				<< NbNodes
				<< ", DATAPACKING=BLOCK";

			return Stream.str();
		}

		static Standard_String WritePointZone(const Standard_Integer nI, const Standard_Integer nJ)
		{
			Standard_SStream Stream;
			Stream
				<< "ZONE I= "
				<< nI
				<< ", J= "
				<< nJ
				<< ", DATAPACKING=POINT";

			return Stream.str();
		}

		static void WritePoints(const TColGeom_Ary1dOfPnt2d& Points, fstream & File)
		{
			forThose
			(
				Index,
				0,
				MaxIndexOf(Points)
			)
			{
				File << Points[Index] _NEWLINE_;
			}
		}

		static void WritePoints(const TColGeom_Ary1dOfPnt3d& Points, fstream & File)
		{
			forThose
			(
				Index,
				0,
				MaxIndexOf(Points)
			)
			{
				File << Points[Index] _NEWLINE_;
			}
		}

		static void WritePointsVariables(const TColGeom_Ary1dOfPnt3d& Points, fstream & File)
		{
			TColStd_Ary1dOfReal X(Points.Size());
			TColStd_Ary1dOfReal Y(Points.Size());
			TColStd_Ary1dOfReal Z(Points.Size());
			forThose
			(
				Index,
				0,
				MaxIndexOf(Points)
			)
			{
				X[Index] = Points[Index].X();
				Y[Index] = Points[Index].Y();
				Z[Index] = Points[Index].Z();
			}

			X.Print(File);
			Y.Print(File);
			Z.Print(File);
		}

		static void WritePointsVariables(const TColGeom_Ary1dOfPnt2d& Points, fstream & File)
		{
			TColStd_Ary1dOfReal X(Points.Size());
			TColStd_Ary1dOfReal Y(Points.Size());
			forThose
			(
				Index,
				0,
				MaxIndexOf(Points)
			)
			{
				X[Index] = Points[Index].X();
				Y[Index] = Points[Index].Y();
			}

			X.Print(File);
			Y.Print(File);
		}

		static void WritePoints(const TColgp_Array1OfPnt& Points, fstream & File)
		{
			forThose
			(
				Index,
				Points.Lower(),
				Points.Upper()
			)
			{
				Geom_Pnt3d Point = Points.Value(Index);
				File << Point _NEWLINE_;
			}
		}

		static void WriteEdges(const TColEntity_Ary1dOfEdgeIndex & Edges, fstream & File)
		{
			forThose
			(
				Index,
				0,
				MaxIndexOf(Edges)
			)
			{
				Get_Const_Object(Edge) = Edges[Index];

				WriteTriangleIndices_GetNewLine(Edge.V0(), Edge.V1(), Edge.V0(), File);
			}
		}

		static void WriteTriangles(const TColEntity_Ary1dOfTriangleIndex& Triangles, fstream & File)
		{
			forThose
			(
				Index,
				0,
				MaxIndexOf(Triangles)
			)
			{
				File << Triangles[Index] _NEWLINE_;
			}
		}

		static void WriteTriangles(const Poly_Array1OfTriangle& Triangles, fstream & File)
		{
			
			forThose
			(
				Index,
				Triangles.Lower(),
				Triangles.Upper()
			)
			{
				Standard_Integer I1, I2, I3;
				Poly_Triangle TriangleIndex = Triangles.Value(Index);
				TriangleIndex.Get(I1, I2, I3);
				Entity_TriangleIndex Triangle(I1, I2, I3);
				File << Triangle _NEWLINE_;
			}
		}

		static void WriteTetrahedrons(const TColEntity_Ary1dOfTetrahedronIndex& Tets, fstream& File)
		{
			forThose
			(
				Index,
				0, 
				MaxIndexOf(Tets)
			)
			{
				File << Tets[Index] _NEWLINE_;
			}
		}

		static void WriteField(const TColGeom_Ary1dOfPnt2d & Points, const Primitive_Field & Field, fstream & File)
		{
			Get_Const_Object(VarList) = Field.Field();

			if (VarList.Size() NOT_EQUAL Points.Size())
			{
				THROW_STANDARD_EXCEPTION(" Filed size and Points size not equal");
			}

			forThose
			(
				Index,
				0,
				MaxIndexOf(Points)
			)
			{
				File
					<< Points[Index];

				Get_Const_Object(Variables) = VarList[Index];

				forThose
				(
					I,
					0,
					MaxIndexOf(Variables)
				)
				{
					File _SPACE_ Variables[I];
				}

				_GET_NEWLINE_(File);
			}
		}

		static void WriteField(const TColGeom_Ary1dOfPnt3d & Points, const Primitive_Field & Field, fstream & File)
		{
			Get_Const_Object(VarList) = Field.Field();

			if (VarList.Size() NOT_EQUAL Points.Size())
			{
				THROW_STANDARD_EXCEPTION(" Filed size and Points size not equal");
			}

			forThose
			(
				Index,
				0,
				MaxIndexOf(Points)
			)
			{
				File
					<< Points[Index];

				Get_Const_Object(Variables) = VarList[Index];

				forThose
				(
					I,
					0,
					MaxIndexOf(Variables)
				)
				{
					File _SPACE_ Variables[I];
				}

				_GET_NEWLINE_(File);
			}
		}

		static void WriteCellCenteredField(const TColEntity_Ary1dOfTetrahedronIndex& Tets, const Primitive_Field & Field, fstream & File)
		{
			Get_Const_Object(VarList) = Field.Field();

			if (VarList.Size() NOT_EQUAL Tets.Size())
			{
				THROW_STANDARD_EXCEPTION(" Filed size and Tets size not equal");
			}

			forThose(Index, 0, Field.NbVariables() - 1)
			{
				forThose(I, 0, Field.NbPoints() - 1)
				{
					File << VarList[I][Index] << "  " << endl;
				}
			}
			//File << endl;

			forThose
			(
				Index,
				0,
				MaxIndexOf(Tets)
			)
			{
				File
					<< Tets[Index];

				_GET_NEWLINE_(File);
			}
		}

		static void WriteCellCenteredField(const TColEntity_Ary1dOfTriangleIndex& Tris, const Primitive_Field & Field, fstream & File)
		{
			Get_Const_Object(VarList) = Field.Field();

			if (VarList.Size() NOT_EQUAL Tris.Size())
			{
				THROW_STANDARD_EXCEPTION(" Filed size and Tets size not equal");
			}

			forThose(Index, 0, Field.NbVariables() - 1)
			{
				forThose(I, 0, Field.NbPoints() - 1)
				{
					File << VarList[I][Index] << "  " << endl;
				}
			}
			//File << endl;

			forThose
			(
				Index,
				0,
				MaxIndexOf(Tris)
			)
			{
				File
					<< Tris[Index];

				_GET_NEWLINE_(File);
			}
		}
	}
}

void AutLib::IoLib::IO_TecPlot::ExportMetric
(
	const Standard_Real H1, 
	const Standard_Real H2, 
	const Geom_Pnt2d & E1,
	const Geom_Pnt2d & E2,
	const Geom_Pnt2d & Centre,
	fstream & File
)
{
	TColEntity_Ary1dOfTriangleIndex Elements(4);
	TColGeom_Ary1dOfPnt2d Coords(5);

	Coords[0] = Centre;
	Coords[1] = Centre + H1*E1;
	Coords[2] = Centre + H2*E2;
	Coords[3] = Centre - H1*E1;
	Coords[4] = Centre - H2*E2;

	Elements[0].SetValue(1, 2, 1);
	Elements[1].SetValue(1, 3, 1);
	Elements[2].SetValue(1, 4, 1);
	Elements[3].SetValue(1, 5, 1);

	ExportMesh(Coords, Elements, File);
}

void AutLib::IoLib::IO_TecPlot::ExportACircle
(
	const Standard_Real r, 
	const Geom_Pnt2d & Centre, 
	fstream & File
)
{
	ExportAnEllipse(r, r, Centre, File);
}

void AutLib::IoLib::IO_TecPlot::ExportAnEllipse
(
	const Standard_Real a,
	const Standard_Real b,
	const Geom_Pnt2d & Pt,
	fstream & File
)
{
	Standard_Integer n = 40;
	Standard_Real x0, y0;
	Standard_Real dt;

	x0 = Pt.X();
	y0 = Pt.Y();

	dt = 2.0*PI / (Standard_Real)n;

	TColGeom_Ary1dOfPnt2d Pts(n + 1);
	forThose(Index, 0, n)
	{
		Pts[Index].X() = x0 + a*cos(Index*dt);
		Pts[Index].Y() = y0 + b*sin(Index*dt);
	}

	ExportCurve(Pts, File);
}

void AutLib::IoLib::IO_TecPlot::Export_I_Ordered
(
	const TColStd_Ary1dOfReal & XCoords,
	const TColStd_Ary1dOfReal & YCoords, 
	const Standard_String Variables, 
	const Standard_String MapName, 
	fstream & File
)
{
	Check_PointList(XCoords);
	Check_PointList(YCoords);

	if (XCoords.Size() != YCoords.Size())
		return;

	WriteVariable_GetNewLine
	(
		Variables,
		File
	);

	WriteIorderedZone_GetNewLine
	(
		XCoords.Size(),
		File
	);

	WriteMapName_GetNewLine(MapName, File);

	forThose(Index, 0, MaxIndexOf(XCoords))
		File << XCoords[Index] << "  ";
	File << endl;
	forThose(Index, 0, MaxIndexOf(YCoords))
		File << YCoords[Index] << "  ";
}

void AutLib::IoLib::IO_TecPlot::ExportBox
(
	const TColEntity_HAry1dOfBox2d & Boxes,
	fstream & File
)
{
	WriteVariable_GetNewLine(XY_Variables, File);

	WriteFeTriangleZone_GetNewLine(4 * Boxes.Size(), 4 * Boxes.Size(), File);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Boxes)
	)
	{
		Get_Const_Object(Box) = *Boxes[Index];

		File << Box.GetSwPoint() << endl;
		File << Box.GetSePoint() << endl;
		File << Box.GetNePoint() << endl;
		File << Box.GetNwPoint() << endl;
	}

	forThose
	(
		Index,
		0,
		MaxIndexOf(Boxes)
	)
	{
		WriteTriangleIndices_GetNewLine(4 * Index + 1, 4 * Index + 2, 4 * Index + 1, File);
		WriteTriangleIndices_GetNewLine(4 * Index + 2, 4 * Index + 3, 4 * Index + 2, File);
		WriteTriangleIndices_GetNewLine(4 * Index + 3, 4 * Index + 4, 4 * Index + 3, File);
		WriteTriangleIndices_GetNewLine(4 * Index + 4, 4 * Index + 1, 4 * Index + 4, File);
	}
}

void AutLib::IoLib::IO_TecPlot::ExportBox
(
	const TColEntity_HAry1dOfBox3d & Boxes,
	fstream & File
)
{
	forThose(Index, 0, MaxIndexOf(Boxes))
		ExportBox(*Boxes[Index], File);
}

void AutLib::IoLib::IO_TecPlot::ExportBox
(
	const M_GEO Entity_Box2d & Box,
	fstream & File
)
{
	WriteVariable_GetNewLine(XY_Variables, File);

	WriteFeTriangleZone_GetNewLine(4, 4, File);

	File << Box.GetSwPoint() << endl;
	File << Box.GetSePoint() << endl;
	File << Box.GetNePoint() << endl;
	File << Box.GetNwPoint() << endl;

	WriteTriangleIndices_GetNewLine(1, 2, 1, File);
	WriteTriangleIndices_GetNewLine(2, 3, 2, File);
	WriteTriangleIndices_GetNewLine(3, 4, 3, File);
	WriteTriangleIndices_GetNewLine(4, 1, 4, File);
}

void AutLib::IoLib::IO_TecPlot::ExportBox
(
	const M_GEO Entity_Box3d & Box,
	fstream & File
)
{
	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeBrickZone_GetNewLine(8, 1, File);

	File << Box.Xmin() << "  " << Box.Ymin() << "  " << Box.Zmin() << endl;
	File << Box.Xmax() << "  " << Box.Ymin() << "  " << Box.Zmin() << endl;
	File << Box.Xmax() << "  " << Box.Ymax() << "  " << Box.Zmin() << endl;
	File << Box.Xmin() << "  " << Box.Ymax() << "  " << Box.Zmin() << endl;
	File << Box.Xmin() << "  " << Box.Ymin() << "  " << Box.Zmax() << endl;
	File << Box.Xmax() << "  " << Box.Ymin() << "  " << Box.Zmax() << endl;
	File << Box.Xmax() << "  " << Box.Ymax() << "  " << Box.Zmax() << endl;
	File << Box.Xmin() << "  " << Box.Ymax() << "  " << Box.Zmax() << endl;

	File << "  1  2  3  4   5  6   7   8\n";
}

void AutLib::IoLib::IO_TecPlot::ExportPoint
(
	const Geom_Pnt2d & Point,
	fstream & File
)
{
	WriteVariable_GetNewLine(XY_Variables, File);

	WriteFeTriangleZone_GetNewLine(1, 1, File);

	File << Point _NEWLINE_;

	WriteTriangleIndices_GetNewLine(1, 1, 1, File);
}

void AutLib::IoLib::IO_TecPlot::ExportPoint
(
	const Geom_Pnt3d & Point,
	fstream & File
)
{
	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeTriangleZone_GetNewLine(1, 1, File);

	File << Point _NEWLINE_;

	WriteTriangleIndices_GetNewLine(1, 1, 1, File);
}

void AutLib::IoLib::IO_TecPlot::ExportPoints
(
	const TColGeom_Ary1dOfPnt2d & Points,
	fstream & File
)
{
	Check_PointList(Points);

	WriteVariable_GetNewLine(XY_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Points.Size(), File);

	WritePoints(Points, File);

	forThose(Index, 1, Points.Size())
	{
		WriteTriangleIndices_GetNewLine(Index, Index, Index, File);
	}
}

void AutLib::IoLib::IO_TecPlot::ExportPoints
(
	const TColGeom_Ary1dOfPnt3d & Points, 
	fstream & File
)
{
	Check_PointList(Points);

	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Points.Size(), File);

	WritePoints(Points, File);

	forThose(Index, 1, Points.Size())
	{
		WriteTriangleIndices_GetNewLine(Index, Index, Index, File);
	}
}

void AutLib::IoLib::IO_TecPlot::ExportCurve
(
	const Geom_Pnt3d & theP0, 
	const Geom_Pnt3d & theP1,
	fstream & File
)
{
	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeTriangleZone_GetNewLine(2, 1, File);

	File << theP0 << endl;
	File << theP1 << endl;

	WriteTriangleIndices_GetNewLine(1, 2, 1, File);
}

void AutLib::IoLib::IO_TecPlot::ExportCurve
(
	const TColGeom_Ary1dOfPnt2d & Points,
	fstream & File
)
{
	Check_PointList(Points);

	WriteVariable_GetNewLine(XY_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Points.Size() - 1, File);

	WritePoints(Points, File);

	forThose(Index, 1, Points.Size() - 1)
	{
		WriteTriangleIndices_GetNewLine(Index, Index + 1, Index, File);
	}
}

void AutLib::IoLib::IO_TecPlot::ExportCurve
(
	const TColGeom_Ary1dOfPnt3d & Points, 
	fstream & File
)
{
	Check_PointList(Points);

	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Points.Size() - 1, File);

	WritePoints(Points, File);

	forThose(Index, 1, Points.Size() - 1)
	{
		WriteTriangleIndices_GetNewLine(Index, Index + 1, Index, File);
	}
}

void AutLib::IoLib::IO_TecPlot::ExportCurve
(
	const TopoDS_Edge & Curve, 
	const Standard_Integer NbSegmets, 
	fstream & File
)
{
	Standard_Real First, Last;
	Handle(Geom_Curve) gm_Curve = BRep_Tool::Curve(Curve, First, Last);

	if (NOT gm_Curve) return;

	ExportCurve(*gm_Curve, First, Last, NbSegmets, File);
}

void AutLib::IoLib::IO_TecPlot::ExportCurve
(
	const Geom_Curve & Curve,
	const Standard_Real First,
	const Standard_Real Last,
	const Standard_Integer NbSegmets,
	fstream & File
)
{
	Standard_Integer Nb = MAX(1, NbSegmets);

	TColGeom_Ary1dOfPnt3d Points(Nb + 1);

	Standard_Real Du = (Last - First) / (Standard_Real)(Nb);

	Curve.D0(First, Points[0]);

	forThose(Index, 1, Nb - 1)
	{
		Standard_Real Parameter = (Standard_Real)Index*Du + First;

		Curve.D0(Parameter, Points[Index]);
	}

	Curve.D0(Last, Points[Nb]);

	ExportCurve(Points, File);
}

void AutLib::IoLib::IO_TecPlot::ExportCurve
(
	const Geom2d_Curve & Curve,
	const Standard_Real First,
	const Standard_Real Last, 
	const Standard_Integer NbSegmets,
	fstream & File
)
{
	Standard_Integer Nb = MAX(1, NbSegmets);

	TColGeom_Ary1dOfPnt2d Points(Nb + 1);

	Standard_Real Du = (Last - First) / (Standard_Real)(Nb);

	Curve.D0(First, Points[0]);

	forThose(Index, 1, Nb - 1)
	{
		Standard_Real Parameter = (Standard_Real)Index*Du + First;

		Curve.D0(Parameter, Points[Index]);
	}

	Curve.D0(Last, Points[Nb]);

	ExportCurve(Points, File);
}

void AutLib::IoLib::IO_TecPlot::ExportCurve
(
	const TopoDS_Shape & Body,
	const Standard_Integer NbSegmets,
	fstream & File
)
{
	TopExp_Explorer anEdgeExplorer;
	anEdgeExplorer.Init(Body, TopAbs_EDGE);

	while (anEdgeExplorer.More())
	{
		TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
		ExportCurve(anEdge, NbSegmets, File);

		anEdgeExplorer.Next();
	}
}

void AutLib::IoLib::IO_TecPlot::ExportSurface(const TopoDS_Face & Surface, fstream & File)
{
	TopLoc_Location Loc;
	Handle(Poly_Triangulation) Triangulation = BRep_Tool::Triangulation(Surface, Loc);

	if (Triangulation.IsNull()) return;

	const Poly_Array1OfTriangle& Triangles = Triangulation->Triangles();
	const TColgp_Array1OfPnt& Nodes = Triangulation->Nodes();

	TColEntity_Ary1dOfTriangleIndex myTriangles(Triangles.Size());
	TColGeom_Ary1dOfPnt3d myPts(Nodes.Size());

	Standard_Integer K = 0;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(myTriangles)
	)
	{
		Poly_Triangle TriangleIndex = Triangles.Value(Index + Triangles.Lower());
		Standard_Integer I1, I2, I3;
		TriangleIndex.Get(I1, I2, I3);
		myTriangles[Index].SetValue(I1, I2, I3);
	}

	K = 0;
	forThose(Index, 0, MaxIndexOf(myPts))
	{
		myPts[Index] = Geom_Pnt3d(Nodes.Value(Index + Nodes.Lower()));
	}

	IoLib::IO_TecPlot::ExportMesh(myPts, myTriangles, File);
}

void AutLib::IoLib::IO_TecPlot::ExportSurface
(
	const Geom_Surface & theSurface, 
	const Standard_Real theUmin, 
	const Standard_Real theUmax, 
	const Standard_Real theVmin,
	const Standard_Real theVmax, 
	const Standard_Integer NbSegmetsU,
	const Standard_Integer NbSegmetsV,
	fstream & File
)
{
	Standard_Real dU = (theUmax - theUmin) / (Standard_Real)NbSegmetsU;
	Standard_Real dV = (theVmax - theVmin) / (Standard_Real)NbSegmetsV;

	File << "VARIABLES= X Y Z\n";
	File << "ZONE I= "
		<< NbSegmetsU + 1
		<< ", J= "
		<< NbSegmetsV + 1
		<< ",DATAPACKING=POINT\n";

	forThose(I, 0, NbSegmetsU)
	{
		Standard_Real U = I*dU + theUmin;
		forThose(J, 0, NbSegmetsV)
		{
			Standard_Real V = J*dV + theVmin;
			Geom_Pnt3d Point = theSurface.Value(U, V);
			File << Point << endl;
		}
	}
}

void AutLib::IoLib::IO_TecPlot::ExportMesh
(
	const TColGeom_Ary1dOfPnt2d & Points,
	const TColEntity_Ary1dOfTriangleIndex & Triangles, 
	fstream & File
)
{
	Check_PointList(Points);

	Check_PointList(Triangles);

	WriteVariable_GetNewLine(XY_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Triangles.Size(), File);

	WritePoints(Points, File);

	WriteTriangles(Triangles, File);
}

void AutLib::IoLib::IO_TecPlot::ExportMesh
(
	const TColGeom_Ary1dOfPnt3d & Points,
	const TColEntity_Ary1dOfTriangleIndex & Triangles,
	fstream & File
)
{
	Check_PointList(Points);

	Check_PointList(Triangles);

	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Triangles.Size(), File);

	WritePoints(Points, File);

	WriteTriangles(Triangles, File);
}

void AutLib::IoLib::IO_TecPlot::ExportMesh
(
	const TColgp_Array1OfPnt & Points,
	const Poly_Array1OfTriangle & Triangles,
	fstream & File
)
{
	Check_PointList(Points);

	Check_PointList(Triangles);

	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Triangles.Size(), File);

	WritePoints(Points, File);

	WriteTriangles(Triangles, File);
}

void AutLib::IoLib::IO_TecPlot::ExportMesh
(
	const TColGeom_Ary1dOfPnt2d & Points,
	const TColEntity_Ary1dOfEdgeIndex & Edges, 
	fstream & File
)
{
	Check_PointList(Points);

	Check_PointList(Edges);

	WriteVariable_GetNewLine(XY_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Edges.Size(), File);

	WritePoints(Points, File);

	WriteEdges(Edges, File);
}

void AutLib::IoLib::IO_TecPlot::ExportMesh
(
	const TColGeom_Ary1dOfPnt3d & Points,
	const TColEntity_Ary1dOfEdgeIndex & Edges,
	fstream & File
)
{
	Check_PointList(Points);

	Check_PointList(Edges);

	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeTriangleZone_GetNewLine(Points.Size(), Edges.Size(), File);

	WritePoints(Points, File);

	WriteEdges(Edges, File);
}

void AutLib::IoLib::IO_TecPlot::ExportMesh
(
	const TColGeom_Ary1dOfPnt3d & Points,
	const TColEntity_Ary1dOfTetrahedronIndex & Elements,
	fstream & File
)
{
	Check_PointList(Points);

	Check_PointList(Elements);

	WriteVariable_GetNewLine(XYZ_Variables, File);

	WriteFeTetrahedralZone_GetNewLine(Points.Size(), Elements.Size(), File);

	WritePoints(Points, File);

	WriteTetrahedrons(Elements, File);
}

void AutLib::IoLib::IO_TecPlot::ExportMesh
(
	const Handle(Poly_Triangulation)& theTriangulation,
	fstream & File
)
{
	if (theTriangulation.IsNull()) return;

	const Poly_Array1OfTriangle& Triangles = theTriangulation->Triangles();
	const TColgp_Array1OfPnt& Nodes = theTriangulation->Nodes();

	TColEntity_Ary1dOfTriangleIndex myTriangles(Triangles.Size());
	TColGeom_Ary1dOfPnt3d myPts(Nodes.Size());

	Standard_Integer K = 0;
	forThose
	(
		Index,
		0,
		MaxIndexOf(myTriangles)
	)
	{
		Poly_Triangle TriangleIndex = Triangles.Value(Index + Triangles.Lower());
		Standard_Integer I1, I2, I3;
		TriangleIndex.Get(I1, I2, I3);
		myTriangles[Index].SetValue(I1, I2, I3);
	}

	K = 0;
	forThose(Index, 0, MaxIndexOf(myPts))
	{
		myPts[Index] = Geom_Pnt3d(Nodes.Value(Index + Nodes.Lower()));
	}

	IoLib::IO_TecPlot::ExportMesh(myPts, myTriangles, File);
}

void AutLib::IoLib::IO_TecPlot::ExportShape
(
	const TopoDS_Shape & Shape,
	fstream & File
)
{
	for (TopExp_Explorer Explorer(Shape, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopLoc_Location Loc;
		Handle(Poly_Triangulation) Triangulation = BRep_Tool::Triangulation(TopoDS::Face(Explorer.Current()), Loc);
		
		if (Triangulation.IsNull()) continue;

		M_IO IO_TecPlot::ExportMesh(Triangulation->Nodes(), Triangulation->Triangles(), File);
	}
}

void AutLib::IoLib::IO_TecPlot::ExportField
(
	const M_GEO Entity_Triangulation2d & Mesh,
	const Primitive_Field & Field,
	fstream & File
)
{
	Standard_String Variables = XY_Variables;

	Variables += " ";
	Variables += Field.VariablesName();

	WriteVariable_GetNewLine(Variables, File);

	Get_Const_Object(Points) = Mesh.Points();
	Get_Const_Object(Triangles) = Mesh.Triangles();

	WriteFeTriangleZone_GetNewLine
	(
		Points.Size(),
		Triangles.Size(),
		File
	);

	WriteField
	(
		Points,
		Field,
		File
	);

	WriteTriangles
	(
		Triangles,
		File
	);
}

void AutLib::IoLib::IO_TecPlot::ExportField
(
	const M_GEO Entity_Tetrahedralization & Mesh,
	const Primitive_Field & Field,
	fstream & File
)
{
	Standard_String Variables = XYZ_Variables;

	Variables += " ";
	Variables += Field.VariablesName();

	WriteVariable_GetNewLine(Variables, File);

	Get_Const_Object(Points) = Mesh.Points();
	Get_Const_Object(Triangles) = Mesh.Tetrahedrons();

	WriteFeTetrahedralZone_GetNewLine
	(
		Points.Size(),
		Triangles.Size(),
		File
	);

	WriteField
	(
		Points,
		Field,
		File
	);

	WriteTetrahedrons(Triangles, File);
}

void AutLib::IoLib::IO_TecPlot::ExportCellCenteredField
(
	const M_GEO Entity_Tetrahedralization & Mesh, 
	const Primitive_Field & Field, 
	fstream & File
)
{
	Standard_String Variables = XYZ_Variables;

	Variables += " ";
	Variables += Field.VariablesName();

	WriteVariable_GetNewLine(Variables, File);

	Get_Const_Object(Points) = Mesh.Points();
	Get_Const_Object(Triangles) = Mesh.Tetrahedrons();

	WriteCellCenteredFeTetrahedralZone_GetNewLine
	(
		Points.Size(),
		Triangles.Size(),
		Field.NbVariables(),
		File
	);

	WritePointsVariables(Points, File);

	WriteCellCenteredField(Triangles, Field, File);
}

void AutLib::IoLib::IO_TecPlot::ExportCellCenteredField
(
	const M_GEO Entity_Triangulation2d & Mesh,
	const Primitive_Field & Field,
	fstream & File
)
{
	Standard_String Variables = XY_Variables;

	Variables += " ";
	Variables += Field.VariablesName();

	WriteVariable_GetNewLine(Variables, File);

	Get_Const_Object(Points) = Mesh.Points();
	Get_Const_Object(Triangles) = Mesh.Triangles();

	WriteCellCenteredFeTriangularZone_GetNewLine
	(
		Points.Size(),
		Triangles.Size(),
		Field.NbVariables(),
		File
	);

	WritePointsVariables(Points, File);

	WriteCellCenteredField(Triangles, Field, File);
}

void AutLib::IoLib::IO_TecPlot::ExportCellCenteredField
(
	const M_GEO Entity_Triangulation3d & Mesh,
	const Primitive_Field & Field,
	fstream & File
)
{
	Standard_String Variables = XYZ_Variables;

	Variables += " ";
	Variables += Field.VariablesName();

	WriteVariable_GetNewLine(Variables, File);

	Get_Const_Object(Points) = Mesh.Points();
	Get_Const_Object(Triangles) = Mesh.Triangles();

	WriteCellCenteredFeTriangular3DZone_GetNewLine
	(
		Points.Size(),
		Triangles.Size(),
		Field.NbVariables(),
		File
	);

	WritePointsVariables(Points, File);

	WriteCellCenteredField(Triangles, Field, File);
}