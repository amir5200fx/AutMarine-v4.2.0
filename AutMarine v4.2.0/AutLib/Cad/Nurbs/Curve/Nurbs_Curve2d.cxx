#include <Nurbs_Curve2d.hxx>

#include <Geom_wPnt2d.hxx>
#include <Geometry_Tools.hxx>
#include <Geometry_Intersect.hxx>
#include <Entity_Box2d.hxx>
#include <NurbsCurveLib.hxx>
#include <TColGeom_Ary1dOfwPnt2d.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Nurbs_Curve2d::Nurbs_Curve2d()
	: theDeg_(0)
	, theMaxIndex_(0)
{
}

AutLib::CadLib::Nurbs_Curve2d::Nurbs_Curve2d
(
	const Standard_Integer Degree, 
	const Standard_Integer MaxIndex,
	const TColStd_Ary1dOfReal & Knots,
	const TColStd_Ary1dOfReal & Weights,
	const TColGeom_Ary1dOfPnt2d & Poles
)
	: theDeg_(Degree)
	, theMaxIndex_(MaxIndex)
	, theKnots_(Knots)
	, theWeights_(Weights)
	, thePoles_(Poles)
{
}

Geom_Pnt2d AutLib::CadLib::Nurbs_Curve2d::PointAt(const Standard_Real Parameter) const
{
	if (NOT INSIDE(Parameter, FirstParameter(), LastParameter()))
	{
		THROW_STANDARD_EXCEPTION(" Knot out of range");
	}

	Standard_Integer Span = NurbsCurveLib::FindSpan
	(
		Parameter,
		theDeg_,
		theMaxIndex_,
		theKnots_
	);

	TColStd_Ary1dOfReal N;

	NurbsCurveLib::BasisFuns
	(
		Span,
		Parameter,
		theDeg_,
		theKnots_,
		N
	);

	Geom_wPnt2d Cw;

	forThose
	(
		Index,
		0,
		theDeg_
	)
	{
		Try_Exception_Handle_Exit(Cw += N[Index] * Geom_wPnt2d(thePoles_[Span - theDeg_ + Index], theWeights_[Span - theDeg_ + Index]));
	}

	ReMove(Cw.TransToEuclidean());
}

Entity_Box2d AutLib::CadLib::Nurbs_Curve2d::BoundingBox() const
{
	Standard_Real
		Xmin,
		Xmax,
		Ymin,
		Ymax;

	if (NbPoles() < 2)
	{
		THROW_STANDARD_EXCEPTION(" Invalid Bspline Cuvre");
	}

	Geometry_Tools::CalcMinMax
	(
		Poles(),
		Xmin,
		Xmax,
		Ymin,
		Ymax
	);

	return Entity_Box2d(Xmin, Xmax, Ymin, Ymax);
}

TColGeom_Ary1dOfPnt2d AutLib::CadLib::Nurbs_Curve2d::DeriveAt(const Standard_Real Parameter, const Standard_Integer Nth) const
{
	if (NOT INSIDE(Parameter, FirstParameter(), LastParameter()))
	{
		THROW_STANDARD_EXCEPTION(" Knot out of range");
	}

	Standard_Integer Du = MIN(Nth, theDeg_);

	TColStd_Ary2dOfReal Nders(Du + 1, theDeg_ + 1);

	Standard_Integer Span = NurbsCurveLib::FindSpan
	(
		Parameter,
		theDeg_,
		theMaxIndex_,
		theKnots_
	);

	NurbsCurveLib::DersBasisFuns
	(
		Span,
		Parameter,
		theDeg_,
		Du,
		theKnots_,
		Nders
	);

	TColGeom_Ary1dOfPnt2d Aders(Nth + 1);
	TColStd_Ary1dOfReal Wders(Nth + 1);

	Aders.Init(Geom_Pnt2d(0, 0));
	Wders.Init(0.);

	forThose(k, 0, Du)
		forThose(j, 0, theDeg_)
	{
		Try_Exception_Handle_Exit(Aders[k] += Nders[k][j] * theWeights_[Span - theDeg_ + j] * thePoles_[Span - theDeg_ + j]);
		Try_Exception_Handle_Exit(Wders[k] += Nders[k][j] * theWeights_[Span - theDeg_ + j]);
	}

	TColGeom_Ary1dOfPnt2d Ders(Nth + 1);

	forThose(k, 0, Du)
	{
		Geom_Pnt2d V;

		Try_Exception_Handle_Exit(V = Aders[k]);
		Try_Exception_Handle_Exit(Ders[k] = 0);

		forThose(i, 1, k)
			Try_Exception_Handle_Exit(V -= NurbsCurveLib::Bin(k, i)*Wders[i] * Ders[k - i]);

		Try_Exception_Handle_Exit(Ders[k] = V / Wders[0]);
	}

	MOVE(Ders);
}

void AutLib::CadLib::Nurbs_Curve2d::IncreaseDegree(const Standard_Integer Degree)
{
	Nurbs_Curve2d BSplineCurve;

	Standard_Integer m = theMaxIndex_ + theDeg_ + 1;
	Standard_Integer ph = theDeg_ + Degree;

	BSplineCurve.theDeg_ = ph;

	Standard_Integer ph2 = ph / 2;

	TColStd_Ary2dOfReal bezalfs(theDeg_ + Degree + 1, theDeg_ + 1);

	TColGeom_Ary1dOfwPnt2d bpts(theDeg_ + 1);
	TColGeom_Ary1dOfwPnt2d ebpts(theDeg_ + Degree + 1);
	TColStd_Ary1dOfReal alfs(theDeg_ - 1);
	TColGeom_Ary1dOfwPnt2d nextbpts(theDeg_ - 1);

	Standard_Integer Degree2 = Degree + 1;

	TColGeom_Ary1dOfPnt2d BS_P(Degree2*theMaxIndex_ + Degree2);
	TColStd_Ary1dOfReal BS_W(Degree2*theMaxIndex_ + Degree2);
	TColStd_Ary1dOfReal BS_U(Degree2*theMaxIndex_ + Degree2 + ph + 2);

	// Compute Bezier degree elevation coefficients
	bezalfs[0][0] = bezalfs[ph][theDeg_] = (Standard_Real)1.0;

	forThose
	(
		i,
		1,
		ph2
	)
	{
		Standard_Real inv = (Standard_Real)1.0 / (Standard_Real)NurbsCurveLib::Bin(ph, i);

		Standard_Integer mpi = MIN(theDeg_, i);

		forThose
		(
			j,
			MAX(0, i - Degree),
			mpi
		)
			bezalfs[i][j] = inv*NurbsCurveLib::Bin(theDeg_, j)*NurbsCurveLib::Bin(Degree, i - j);
	}

	forThose
	(
		i,
		ph2 + 1,
		ph
	)
	{
		Standard_Integer mpi = MIN(theDeg_, i);

		forThose
		(
			j,
			MAX(0, i - Degree),
			mpi
		)
			bezalfs[i][j] = bezalfs[ph - i][theDeg_ - j];
	}

	Standard_Integer mh = ph;
	Standard_Integer kind = ph + 1;
	Standard_Integer r = -1;
	Standard_Integer a = theDeg_;
	Standard_Integer b = theDeg_ + 1;
	Standard_Integer cind = 1;

	Standard_Real ua = theKnots_[0];

	BS_P[0] = thePoles_[0];
	BS_W[0] = theWeights_[0];

	forThose
	(
		Index,
		0,
		ph
	)
		BS_U[Index] = ua;

	// Initialize first Bezier seg
	forThose
	(
		Index,
		0,
		theDeg_
	)
		bpts[Index] = Geom_wPnt2d(thePoles_[Index], theWeights_[Index]);

	while (b < m)
	{  // Big loop thru knot vector
		Standard_Integer i = b;

		while (b < m && theKnots_[b] >= theKnots_[b + 1])
			b++;

		Standard_Integer mul = b - i + 1;

		mh = mh + mul + Degree;

		Standard_Real ub = theKnots_[b];
		Standard_Integer oldr = r;
		r = theDeg_ - mul;

		// Insert knot u(b) r times
		Standard_Integer lbz;
		if (oldr > 0)
			lbz = (oldr + 2) / 2;
		else
			lbz = 1;

		Standard_Integer rbz;
		if (r > 0)
			rbz = ph - (r + 1) / 2;
		else
			rbz = ph;

		if (r > 0)
		{  // Insert knot to get Bezier segment
			Standard_Real numer = ub - ua;

			for (Standard_Integer k = theDeg_; k > mul; k--)
				alfs[k - mul - 1] = numer / (theKnots_[a + k] - ua);

			forThose
			(
				j,
				1,
				r
			)
			{
				Standard_Integer save = r - j;
				Standard_Integer s = mul + j;

				for (Standard_Integer k = theDeg_; k >= s; k--)
					bpts[k] = alfs[k - s] * bpts[k] + ((Standard_Real)1.0 - alfs[k - s])*bpts[k - 1];

				nextbpts[save] = bpts[theDeg_];
			}
		}   // End of "insert khot"

		forThose
		(
			i,
			lbz,
			ph
		) // Degree elevate Bezier
		{
			ebpts[i] = (Standard_Real)0.0;
			Standard_Integer mpi = MIN(theDeg_, i);

			forThose(j, MAX(0, i - Degree), mpi)
				ebpts[i] = ebpts[i] + bezalfs[i][j] * bpts[j];
		}  // End of degree elevating Bezier

		if (oldr > 1)
		{   // Must remove knot u = U[a] oldr times
			Standard_Integer first = kind - 2;
			Standard_Integer last = kind;

			Standard_Real den = ub - ua;
			Standard_Real bet = (ub - BS_U[kind - 1]) / den;

			forThose
			(
				tr,
				1,
				oldr - 1
			)
			{   // Loop and compute the new control points for one removal step
				Standard_Integer i = first;
				Standard_Integer j = last;
				Standard_Integer kj = j - kind + 1;

				while (j - i > tr)
				{
					if (i < cind)
					{
						Standard_Real alf = (ub - BS_U[i]) / (ua - BS_U[i]);

						GeoLib::Geom_Pnt2d tmp_P1 = BS_P[i];
						GeoLib::Geom_Pnt2d tmp_p2 = BS_P[i - 1];

						BS_P[i] = alf*tmp_P1 + ((Standard_Real)1.0 - alf)*tmp_p2;
						BS_W[i] = alf*BS_W[i] + ((Standard_Real)1.0 - alf)*BS_W[i - 1];
					}
					if (j >= lbz)
					{
						if (j - tr <= kind - ph + oldr)
						{
							Standard_Real gam = (ub - BS_U[j - tr]) / den;
							ebpts[kj] = gam*ebpts[kj] + ((Standard_Real)1.0 - gam)*ebpts[kj + 1];
						}
						else
							ebpts[kj] = bet*ebpts[kj] + ((Standard_Real)1.0 - bet)*ebpts[kj + 1];
					}
					++i;
					--j;
					--kj;
				}
				--first;
				++last;
			}
		}  // End of removing knot, u = U[a]
		if (a != theDeg_)
			forThose
			(
				i,
				0,
				ph - oldr - 1
			)
		{
			BS_U[kind] = ua;
			kind++;
		}

		forThose
		(
			j,
			lbz,
			rbz
		)
		{
			BS_P[cind] = ebpts[j].TransToEuclidean();
			BS_W[cind] = ebpts[j].W();
			cind++;
		}

		if (b < m)
		{
			forThose
			(
				j,
				0,
				r
			)
				bpts[j] = nextbpts[j];

			forThose
			(
				j,
				r,
				theDeg_
			)
				bpts[j] = Geom_wPnt2d(thePoles_[b - theDeg_ + j], theWeights_[b - theDeg_ + j]);

			a = b;
			b++;
			ua = ub;
		}
		else
			forThose
			(
				i,
				0,
				ph
			)
			BS_U[kind + i] = ub;
	}

	BSplineCurve.theMaxIndex_ = mh - ph - 1;
	BSplineCurve.thePoles_.Resize(BSplineCurve.theMaxIndex_ + 1);
	BSplineCurve.theWeights_.Resize(BSplineCurve.theMaxIndex_ + 1);

	forThose
	(
		Index,
		0,
		BSplineCurve.theMaxIndex_
	)
	{
		Try_Exception_Handle_Exit(BSplineCurve.thePoles_[Index] = BS_P[Index]);
		Try_Exception_Handle_Exit(BSplineCurve.theWeights_[Index] = BS_W[Index]);
	}

	BSplineCurve.theKnots_.Resize(BSplineCurve.theMaxIndex_ + ph + 2);

	forThose
	(
		Index,
		0,
		BSplineCurve.theMaxIndex_ + ph + 1
	)
		Try_Exception_Handle_Exit(BSplineCurve.theKnots_[Index] = BS_U[Index];);

	std::swap(BSplineCurve, *this);
}

void AutLib::CadLib::Nurbs_Curve2d::InsertKnot
(
	const Standard_Real Parameter,
	const Standard_Integer r,
	const Standard_Real ParametricTolerance
)
{
	Standard_Integer k = 0;
	Standard_Integer Mult = 0;
	Standard_Integer Deg = theDeg_;
	Standard_Integer rr = r;

	if (NOT INSIDE(Parameter, FirstParameter(), LastParameter()))
	{
		THROW_STANDARD_EXCEPTION(" The parametric value isn't inside a valid range");
	}

	forThose(Index, 0, MaxIndexOf(theKnots_))
	{
		if (theKnots_[Index] > Parameter)
		{
			k = Index - 1;
			break;
		}
	}

	if (Parameter <= theKnots_[k])
	{
		Mult = 1;
		for (Standard_Integer i = k; i > theDeg_; i--)
		{
			if (ABS(theKnots_[i] - theKnots_[i - 1]) <= ParametricTolerance)
				Mult++;
			else
				break;
		}
	}
	else
		Mult = 0;

	if ((r + Mult) > theDeg_ + 1)
		rr = theDeg_ + 1 - Mult;

	if (rr <= 0)
		return;

	Nurbs_Curve2d BSplineCurve;

	BSplineCurve.Allocate(theDeg_, theMaxIndex_ + rr);

	Standard_Integer mp = theMaxIndex_ + theDeg_ + 1;
	Standard_Integer nq = theMaxIndex_ + rr;

	forThose(Index, 0, k)
		Try_Exception_Handle_Exit(BSplineCurve.theKnots_[Index] = theKnots_[Index]);

	forThose(Index, 1, rr)
		Try_Exception_Handle_Exit(BSplineCurve.theKnots_[k + Index] = Parameter);

	forThose(Index, k + 1, mp)
		Try_Exception_Handle_Exit(BSplineCurve.theKnots_[Index + rr] = theKnots_[Index]);

	forThose(Index, 0, k - theDeg_)
	{
		Try_Exception_Handle_Exit(BSplineCurve.thePoles_[Index] = thePoles_[Index]);
		Try_Exception_Handle_Exit(BSplineCurve.theWeights_[Index] = theWeights_[Index]);
	}

	forThose(Index, k - Mult, theMaxIndex_)
	{
		Try_Exception_Handle_Exit(BSplineCurve.thePoles_[Index + rr] = thePoles_[Index]);
		Try_Exception_Handle_Exit(BSplineCurve.theWeights_[Index + rr] = theWeights_[Index]);
	}

	ADT_Ary1d<Geom_wPnt2d> R(theDeg_ + 1);

	forThose(Index, 0, theDeg_ - Mult)
		Try_Exception_Handle_Exit(R[Index] = Geom_wPnt2d(thePoles_[k - theDeg_ + Index], theWeights_[k - theDeg_ + Index]));

	Standard_Integer L = k - theDeg_ + r;

	forThose(j, 1, rr)
	{
		L = k - theDeg_ + j;

		forThose
		(
			Index,
			0,
			theDeg_ - j - Mult
		)
		{
			const Standard_Real alpha = (Parameter - theKnots_[L + Index]) / (theKnots_[Index + k + 1] - theKnots_[L + Index]);

			Try_Exception_Handle_Exit(R[Index] = alpha*R[Index + 1] + (1.0 - alpha)*R[Index]);
		}

		Try_Exception_Handle_Exit(BSplineCurve.thePoles_[L] = R[0].TransToEuclidean());  // new delete //
		Try_Exception_Handle_Exit(BSplineCurve.theWeights_[L] = R[0].W());

		if (theDeg_ - j - Mult > 0)
		{
			Try_Exception_Handle_Exit(BSplineCurve.thePoles_[k + r - j - Mult] = R[theDeg_ - j - Mult].TransToEuclidean(););  // new delete //
			Try_Exception_Handle_Exit(BSplineCurve.theWeights_[k + r - j - Mult] = R[theDeg_ - j - Mult].W(););
		}
	}

	forThose
	(
		Index,
		L + 1,
		k - Mult
	)
	{
		Try_Exception_Handle_Exit(BSplineCurve.thePoles_[Index] = R[Index - L].TransToEuclidean(););  // new //
		Try_Exception_Handle_Exit(BSplineCurve.theWeights_[Index] = R[Index - L].W(););
	}

	std::swap(BSplineCurve, *this);
}

void AutLib::CadLib::Nurbs_Curve2d::RemoveKnot
(
	const Standard_Integer r, 
	const Standard_Integer s,
	const Standard_Integer num
)
{
	if (num < 1) THROW_STANDARD_EXCEPTION(" A knot can only be removed a positive number of times!");

	Standard_Integer m = theKnots_.Size();
	Standard_Integer ord = theDeg_ + 1;
	Standard_Integer fout = (2 * r - s - theDeg_) / 2;
	Standard_Integer last = r - s;
	Standard_Integer first = r - theDeg_;

	Standard_Real
		alfi,
		alfj;

	Standard_Integer
		i,
		j,
		t,
		ii,
		jj,
		off;

	Standard_Real u = theKnots_[r];

	TColGeom_Ary1dOfPnt2d temp(2 * theDeg_ + 1);

	for (t = 0; t < num; t++)
	{
		off = first - 1;

		Try_Exception_Handle_Exit(temp[0] = thePoles_[off];);
		Try_Exception_Handle_Exit(temp[last + 1 - off] = thePoles_[last + 1];);

		i = first;
		j = last;

		ii = 1;
		jj = last - off;

		while (j - i > t)
		{
			Try_Exception_Handle_Exit(alfi = (u - theKnots_[i]) / (theKnots_[i + ord + t] - theKnots_[i]););
			Try_Exception_Handle_Exit(alfj = (u - theKnots_[j - t]) / (theKnots_[j + ord] - theKnots_[j - t]););

			Try_Exception_Handle_Exit(temp[ii] = (thePoles_[i] - (1.0 - alfi)*temp[ii - 1]) / alfi);
			Try_Exception_Handle_Exit(temp[jj] = (thePoles_[j] - alfj*temp[jj + 1]) / (1.0 - alfj));

			i++;
			j--;

			ii++;
			jj--;
		}

		i = first;
		j = last;

		while (j - i > t)
		{
			Try_Exception_Handle_Exit(thePoles_[i] = temp[i - off]);
			Try_Exception_Handle_Exit(thePoles_[j] = temp[j - off]);

			i++;
			j--;
		}

		first--;
		last++;
	}

	if (t == 0)
	{
		THROW_STANDARD_EXCEPTION(" Major error happening... t==0");
	}

	forThose
	(
		Index,
		r + 1,
		m - 1
	)
	{
		Try_Exception_Handle_Exit(theKnots_[Index - t] = theKnots_[Index];);
	}

	j = fout;
	i = j;

	forThose
	(
		Index,
		1,
		t - 1
	)
	{
		if ((Index % 2) == 1)
		{
			i++;
		}
		else
		{
			j--;
		}
	}

	forThose
	(
		Index,
		i + 1,
		MaxIndexOf(thePoles_)
	)
	{
		Try_Exception_Handle_Exit(thePoles_[j++] = thePoles_[Index];);
	}

	thePoles_.DynResize(thePoles_.Size() - t);

	theMaxIndex_ = thePoles_.Size() - 1;
}

void AutLib::CadLib::Nurbs_Curve2d::Reverse()
{
	TColStd_Ary1dOfReal S = Knots();

	Standard_Integer M = theMaxIndex_ + theDeg_ + 1;

	Standard_Real First = FirstParameter();
	Standard_Real Last = LastParameter();

	forThose(Index, 1, M - 2 * theDeg_ - 1)
	{
		//theKnots_[M - theDeg_ - Index] = ReversedParameter(S[theDeg_ + Index]);
		theKnots_[M - theDeg_ - Index] = -S[theDeg_ + Index] + First + Last;
	}

	TColGeom_Ary1dOfPnt2d Q = thePoles_;
	TColStd_Ary1dOfReal W = theWeights_;

	forThose(Index, 0, theMaxIndex_)
	{
		thePoles_[Index] = Q[theMaxIndex_ - Index];
		theWeights_[Index] = W[theMaxIndex_ - Index];
	}
}

void AutLib::CadLib::Nurbs_Curve2d::MakeLine(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2)
{
	Allocate(1, 1);

	thePoles_[0] = P1;
	thePoles_[1] = P2;

	theKnots_[0] = theKnots_[1] = 0;
	theKnots_[2] = theKnots_[3] = 1;
}

void AutLib::CadLib::Nurbs_Curve2d::MakeArc
(
	const Geom_Pnt2d & P0, 
	const Geom_Pnt2d & Tan0, 
	const Geom_Pnt2d & P2, 
	const Geom_Pnt2d & Tan2,
	const Geom_Pnt2d & ArbtPoint
)
{
	Allocate(2, 2);

	thePoles_[0] = P0;
	thePoles_[2] = P2;

	theKnots_[0] = theKnots_[1] = theKnots_[2] = 0.0;
	theKnots_[3] = theKnots_[4] = theKnots_[5] = 1.0;

	Geom_Pnt2d V02 = P2 - P0;

	Standard_Real alf0, alf2, dum1, dum2;

	Geom_Pnt2d P1(0, 0);

	Standard_Boolean IsIntersect = Geometry_Intersect::IsIntersect(P0, Tan0, P2, Tan2, dum1, dum2, P1);

	if (IsIntersect)
	{
		Geom_Pnt2d V1P = ArbtPoint - P1;
		Geom_Pnt2d dummy;

		Geometry_Intersect::IsIntersect(P1, V1P, P0, V02, alf0, alf2, dummy);

		Standard_Real a = sqrt(alf2 / (1.0 - alf2));
		Standard_Real u = a / (1.0 + a);
		Standard_Real num = (1.0 - u)*(1.0 - u)*DotProduct(ArbtPoint - P0, P1 - ArbtPoint)
			+ u*u*DotProduct(ArbtPoint - P2, P1 - ArbtPoint);
		Standard_Real den = 2.0*u*(1.0 - u)*DotProduct(P1 - ArbtPoint, P1 - ArbtPoint);
		Standard_Real w1 = num / den;

		thePoles_[1] = P1;
		theWeights_[1] = w1;
	}
	else
	{
		Geom_Pnt2d dummy;

		Geometry_Intersect::IsIntersect(ArbtPoint, Tan0, P0, V02, alf0, alf2, dummy);

		Standard_Real a = sqrt(alf2 / (1.0 - alf2));
		Standard_Real u = a / (1.0 + a);
		Standard_Real b = 2.0*u*(1.0 - u);
		b = -alf0*(1.0 - b) / b;
		P1 = P1 + b* Tan0;

		thePoles_[1] = P1;
		theWeights_[1] = 0.0;
	}
}

void AutLib::CadLib::Nurbs_Curve2d::MakeCircle
(
	const Standard_Real Radius,
	const Geom_Pnt2d & Centre, 
	Standard_Real Start_Degree, 
	Standard_Real End_Degree
)
{
	Geom_Pnt2d X(1.0, 0.0);
	Geom_Pnt2d Y(0.0, 1.0);

	if (End_Degree < Start_Degree) End_Degree = 360.0 + Start_Degree;
	Standard_Real theta = End_Degree - Start_Degree;
	Standard_Integer narcs;
	if (theta <= 90.0) narcs = 1;
	else
		if (theta <= 180.0) narcs = 2;
		else
			if (theta <= 270.0) narcs = 3;
			else
				narcs = 4;

	Standard_Real dtheta = Geometry_Tools::DegToRadian(theta) / narcs;

	theMaxIndex_ = 2 * narcs;  // n + 1 control points
	theDeg_ = 2;
	thePoles_.Resize(theMaxIndex_ + 1);
	theWeights_.Resize(theMaxIndex_ + 1);

	theWeights_.Init(1.0);

	Standard_Real w1 = cos(dtheta / 2.0);
	Start_Degree = Geometry_Tools::DegToRadian(Start_Degree);

	Geom_Pnt2d p0 = Centre + Radius*cos(Start_Degree)*X + Radius*sin(Start_Degree)*Y;
	Geom_Pnt2d t0 = -sin(Start_Degree)*X + cos(Start_Degree)*Y;

	thePoles_[0] = p0;
	Standard_Integer index = 0;
	Standard_Real angle = Start_Degree;

	forThose(i, 1, narcs)
	{
		angle += dtheta;
		Geom_Pnt2d p2 = Centre + Radius*cos(angle)*X + Radius*sin(angle)*Y;

		thePoles_[index + 2] = p2;
		Geom_Pnt2d t2 = -sin(angle)*X + cos(angle)*Y;

		Geom_Pnt2d p1 = Geometry_Intersect::IntersectionTwoLines(p0, t0, p2, t2);

		thePoles_[index + 1] = p1;
		theWeights_[index + 1] = w1;

		index += 2;

		if (i < narcs)
		{
			p0 = p2;
			t0 = t2;
		}
	}

	Standard_Integer j = 2 * narcs + 1;
	theKnots_.Resize(j + 3);
	theKnots_.Init(0);

	for (Standard_Integer i = 0; i < 3; i++)
		theKnots_[i + j] = 1.0;

	switch (narcs)
	{
	case 1: break;
	case 2:
		theKnots_[3] = theKnots_[4] = 0.5;
		break;
	case 3:
		theKnots_[3] = theKnots_[4] = 1.0 / 3.0;
		theKnots_[5] = theKnots_[6] = 2.0 / 3.0;
		break;
	case 4:
		theKnots_[3] = theKnots_[4] = 0.25;
		theKnots_[5] = theKnots_[6] = 0.5;
		theKnots_[7] = theKnots_[8] = 0.75;
		break;
	}
}

void AutLib::CadLib::Nurbs_Curve2d::Transform(const gp_Trsf2d & T)
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(thePoles_)
	)
	{
		thePoles_[Index].Transform(T);
	}
}

void AutLib::CadLib::Nurbs_Curve2d::Print(Standard_OStream & Ostream) const
{
	Ostream << " Number of Ctrl Points = " << theMaxIndex_ + 1 << "\n";
	Ostream << " Degree = " << theDeg_ << "\n";
	Ostream << " Control Points:\n";

	forThose(Index, 0, MaxIndexOf(thePoles_))
	{
		Ostream << thePoles_[Index] << "  " << theWeights_[Index] << endl;
	}

	Ostream << endl;
	Ostream << "Knots: \n";

	theKnots_.Print(Ostream);
}

void AutLib::CadLib::Nurbs_Curve2d::Allocate
(
	const Standard_Integer Degree, 
	const Standard_Integer MaxIndex
)
{
	theDeg_ = Degree;
	theMaxIndex_ = MaxIndex;

	thePoles_.Resize(theMaxIndex_ + 1);
	theWeights_.Resize(theMaxIndex_ + 1);

	theKnots_.Resize(theMaxIndex_ + theDeg_ + 2);

	theWeights_.Init(1.0);
	theKnots_.Init(0.0);
}