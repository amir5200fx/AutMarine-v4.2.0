#include <DelTri2d.hxx>

#include <ADT_BasicStack.hxx>
#include <IO_TecPlot.hxx>

AutLib::GeoLib::DelTri2d::DelTri2d(const TColGeom_Ary1dOfPnt2d & Points)
	: thePts_(Points.Size() + 30)
	, theV_(2* Points.Size() +10)
	, theE_(2* Points.Size() +10)
	, theNbPts_(Points.Size())
	, theNbTris_(0)
{
	forThose
	(
		Index,
		0,
		theNbPts_ - 1
	)
	{
		thePts_[Index] = Points[Index];
	}
}

void AutLib::GeoLib::DelTri2d::Perform()
{
	Standard_Real xmin = thePts_[0].X();
	Standard_Real xmax = xmin;
	Standard_Real ymin = thePts_[0].Y();
	Standard_Real ymax = ymin;

	for (int i = 1; i < theNbPts_; i++)
	{
		xmin = MIN(xmin, thePts_[i].X());
		xmax = MAX(xmax, thePts_[i].X());
		ymin = MIN(ymin, thePts_[i].Y());
		ymax = MAX(ymax, thePts_[i].Y());
	}

	Standard_Real dmax = MAX(xmax - xmin, ymax - ymin);

	// Normalise X-Y coords of points
	Standard_Real fact = 1.0 / dmax;
	for (int i = 0; i < theNbPts_; i++)
	{
		thePts_[i].X() = (thePts_[i].X() - xmin)*fact;
		thePts_[i].Y() = (thePts_[i].Y() - ymin)*fact;
	}

	// Compute DELAUNAY TRIANGULATION
	Delaunay();

	// Reset X-Y coords to original values
	for (int i = 0; i < theNbPts_; i++)
	{
		thePts_[i].X() = thePts_[i].X()*dmax + xmin;
		thePts_[i].Y() = thePts_[i].Y()*dmax + ymin;
	}
}

void AutLib::GeoLib::DelTri2d::Plot(fstream & File) const
{
	IoLib::IO_TecPlot::ExportMesh
	(
		thePts_,
		theV_,
		File
	);
}

void AutLib::GeoLib::DelTri2d::Delaunay()
{
	Standard_Integer v1 = theNbPts_ + 1;
	Standard_Integer v2 = theNbPts_ + 2;
	Standard_Integer v3 = theNbPts_ + 3;

	theV_[0].V0() = v1;
	theV_[0].V1() = v2;
	theV_[0].V2() = v3;
	theE_[0].V0() = 0;
	theE_[0].V1() = 0;
	theE_[0].V2() = 0;

	// Set coords of Supertriangle

	thePts_[v1 - 1].X() = -100;
	thePts_[v1 - 1].Y() = -100;
	thePts_[v2 - 1].X() = +100;
	thePts_[v2 - 1].Y() = -100;
	thePts_[v3 - 1].X() = 0;
	thePts_[v3 - 1].Y() = 100;

	theNbTris_ = 1;

	Geom_Pnt2d pt;
	ADT_BasicStack<Standard_Integer> STACK;

	Standard_Integer t, a, b, c, p;
	Standard_Integer l, r, erl, era, erb;

	for (Standard_Integer i = 0; i < theNbPts_; i++)
	{
		p = i + 1;
		pt = thePts_[i];

		// Locate triangle in which point lies
		t = TriLoc(pt);

		// Create new vertex and adjacency lists for triangle t
		a = theE_[t - 1].V0();
		b = theE_[t - 1].V1();
		c = theE_[t - 1].V2();

		v1 = theV_[t - 1].V0();
		v2 = theV_[t - 1].V1();
		v3 = theV_[t - 1].V2();

		theV_[t - 1].V0() = p;
		theV_[t - 1].V1() = v1;
		theV_[t - 1].V2() = v2;
		theE_[t - 1].V0() = theNbTris_ + 2;
		theE_[t - 1].V1() = a;
		theE_[t - 1].V2() = theNbTris_ + 1;

		// Create new triangle
		theNbTris_++;
		theV_[theNbTris_ - 1].V0() = p;
		theV_[theNbTris_ - 1].V1() = v2;
		theV_[theNbTris_ - 1].V2() = v3;
		theE_[theNbTris_ - 1].V0() = t;
		theE_[theNbTris_ - 1].V1() = b;
		theE_[theNbTris_ - 1].V2() = theNbTris_ + 1;

		theNbTris_++;
		theV_[theNbTris_ - 1].V0() = p;
		theV_[theNbTris_ - 1].V1() = v3;
		theV_[theNbTris_ - 1].V2() = v1;
		theE_[theNbTris_ - 1].V0() = theNbTris_ - 1;
		theE_[theNbTris_ - 1].V1() = c;
		theE_[theNbTris_ - 1].V2() = t;

		if (a != 0) STACK.Push(t);
		if (b != 0)
		{
			theE_[b - 1].Value(Edge(b, t)) = theNbTris_ - 1;
			STACK.Push(theNbTris_ - 1);
		}
		if (c != 0)
		{
			theE_[c - 1].Value(Edge(c, t)) = theNbTris_;
			STACK.Push(theNbTris_);
		}

		// Loop while stack is not empty
		while (!STACK.IsEmpty())
		{
			STACK.Pop(l);
			r = theE_[l - 1].V1();

			// Check if new point is in circumcircle for triangle R
			erl = Edge(r, l);
			era = (erl + 1) % 3;
			erb = (era + 1) % 3;
			v1 = theV_[r - 1].Value(erl);
			v2 = theV_[r - 1].Value(era);
			v3 = theV_[r - 1].Value(erb);

			if (Swap(thePts_[p - 1], thePts_[v1 - 1], thePts_[v2 - 1], thePts_[v3 - 1]))
			{
				// New point is inside circumcircle for triangle R
				// Swap diagonal for convex quad formed by p-v2-v3-v1

				a = theE_[r - 1].Value(era);
				b = theE_[r - 1].Value(erb);
				c = theE_[l - 1].Value(2);

				// Update vertex and adjacency list for triangle L

				theV_[l - 1].Value(2) = v3;
				theE_[l - 1].Value(1) = a;
				theE_[l - 1].Value(2) = r;

				// Update vertex and adjacency list for triangle R

				theV_[r - 1].V0() = p;
				theV_[r - 1].V1() = v3;
				theV_[r - 1].V2() = v1;
				theE_[r - 1].V0() = l;
				theE_[r - 1].V1() = b;
				theE_[r - 1].V2() = c;

				// Put edges L-A and R-B on stack
				// Update adjacency lists for triangles A and C

				if (a != 0)
				{
					theE_[a - 1].Value(Edge(a, r)) = l;
					STACK.Push(l);
				}
				if (b != 0) STACK.Push(r);
				if (c != 0) theE_[c - 1].Value(Edge(c, l)) = r;
			}
		}
	}

	// Check consistency of triangulation
	if (theNbTris_ != (2 * theNbPts_ + 1))
		CloseProgram("INCORRECT NUMBER OF TRIANGLES FORMED");

	// Remove all triangles containing supertriangle vertices
	// Find first triangle to be deleted (triangle T)
	// Update adjacency lists for triangle adjacent to T
	//cout << theNbPts_ << endl;
	for (t = 1; t <= theNbTris_; t++)
		if ((theV_[t - 1].Value(0) > theNbPts_) || (theV_[t - 1].Value(1) > theNbPts_) || (theV_[t - 1].Value(2) > theNbPts_))
		{
			//cout << theV_[t - 1][0] << "  " << theV_[t - 1][1] << "  " << theV_[t - 1][2] << endl;
			for (Standard_Integer i = 0; i < 3; i++)
			{
				a = theE_[t - 1].Value(i);
				if (a != 0) theE_[a - 1].Value(Edge(a, t)) = 0;
			}
			break;
		}

	Standard_Integer TSTRT = t + 1;
	Standard_Integer TSTOP = theNbTris_;
	theNbTris_ = t - 1;

	// Remove triangles
	for (Standard_Integer t = TSTRT; t <= TSTOP; t++)
	{
		if ((theV_[t - 1].Value(0) > theNbPts_) || (theV_[t - 1].Value(1) > theNbPts_) || (theV_[t - 1].Value(2) > theNbPts_))
			for (Standard_Integer i = 0; i < 3; i++)
			{
				a = theE_[t - 1].Value(i);
				if (a != 0) theE_[a - 1].Value(Edge(a, t)) = 0;
			}
		else
		{
			// Triangle T is not to be deleted
			// Put triangle T in place of triangle theNbTris_
			// Update adjacency lists for triangles adjacent to T

			theNbTris_++;

			for (Standard_Integer i = 0; i < 3; i++)
			{
				a = theE_[t - 1].Value(i);
				theE_[theNbTris_ - 1].Value(i) = a;
				theV_[theNbTris_ - 1].Value(i) = theV_[t - 1].Value(i);

				if (a != 0) theE_[a - 1].Value(Edge(a, t)) = theNbTris_;
			}
		}
	}

	thePts_.DynResize(theNbPts_);

	theV_.DynResize(theNbTris_);
	theE_.DynResize(theNbTris_);
}