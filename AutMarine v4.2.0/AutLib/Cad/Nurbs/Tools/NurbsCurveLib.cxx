#include <NurbsCurveLib.hxx>

Standard_Integer AutLib::CadLib::NurbsCurveLib::Bin
(
	const Standard_Integer K, 
	const Standard_Integer I
)
{
	Standard_Integer Numerator = Factorial(K);
	Standard_Integer Denominator = Factorial(K - I)*Factorial(I);

	return Numerator / Denominator;
}

Standard_Integer AutLib::CadLib::NurbsCurveLib::FindSpan
(
	const Standard_Real U, 
	const Standard_Integer Degree,
	const Standard_Integer MaxIndex, 
	const TColStd_Ary1dOfReal & Knots
)
{
	Debug_If_Condition_Message(U < Knots.First() OR U > Knots.Last(), " Invalid Para");

	if (U == Knots[Degree])
		return Degree;

	if (U == Knots[MaxIndex + 1])
		return MaxIndex;

	Standard_Integer Low = Degree;
	Standard_Integer High = MaxIndex + 1;
	Standard_Integer Mid = (Low + High) >> 1;

	while (U < Knots[Mid] OR U >= Knots[Mid + 1])
	{
		if (U < Knots[Mid])
			High = Mid;
		else
			Low = Mid;

		Mid = (Low + High) >> 1;
	}

	return Mid;
}

Standard_Real AutLib::CadLib::NurbsCurveLib::BasisFun
(
	const Standard_Integer Span,
	const Standard_Real Parameter,
	const Standard_Integer Degree,
	const TColStd_Ary1dOfReal & Knots
)
{
	Standard_Integer m = Knots.Size() - 1;

	if ((Span EQUAL 0 AND Parameter EQUAL Knots.First()) OR(Span EQUAL m - Degree - 1 AND Parameter EQUAL Knots.Last()))
	{
		return 1.0;
	}

	if (Parameter < Knots[Span] OR Parameter >= Knots[Span + Degree + 1])
	{
		return 0.0;
	}

	TColStd_Ary1dOfReal N(Degree + 1);

	forThose(Index, 0, Degree)
	{
		if (Parameter >= Knots[Span + Index] AND Parameter < Knots[Span + Index + 1])
			N[Index] = 1.0;
		else
			N[Index] = 0.0;
	}

	Standard_Real
		Saved,
		Temp,
		Uleft,
		Uright;

	forThose(Index, 1, Degree)
	{
		if (N[0] EQUAL 0.0)
			Saved = 0.0;
		else
			Saved = ((Parameter - Knots[Span])*N[0]) / (Knots[Span + Index] - Knots[Span]);

		forThose(Index2, 0, Degree - Index)
		{
			Uleft = Knots[Span + Index2 + 1];
			Uright = Knots[Span + Index2 + Index + 1];

			if (Knots[Index2 + 1] EQUAL 0.0)
			{
				N[Index2] = Saved;
				Saved = 0.0;
			}
			else
			{
				Temp = N[Index2 + 1] / (Uright - Uleft);
				N[Index2] = Saved + (Uright - Parameter)*Temp;
				Saved = (Parameter - Uleft)*Temp;
			}
		}
	}

	return N[0];
}

void AutLib::CadLib::NurbsCurveLib::BasisFuns
(
	const Standard_Integer Span,
	const Standard_Real Parameter, 
	const Standard_Integer Degree,
	const TColStd_Ary1dOfReal & Knots,
	TColStd_Ary1dOfReal & Basis
)
{
	RESIZE_ARRAY1(Basis, Degree + 1);

	TColStd_Ary1dOfReal Left(Degree + 1);
	TColStd_Ary1dOfReal Right(Degree + 1);

	Basis[0] = 1.0;

	forThose(Index1, 1, Degree)
	{
		Left[Index1] = Parameter - Knots[Span + 1 - Index1];
		Right[Index1] = Knots[Span + Index1] - Parameter;

		Standard_Real Saved = 0.;

		forThose(Index2, 0, Index1 - 1)
		{
			Standard_Real Temp = Basis[Index2] / (Right[Index2 + 1] + Left[Index1 - Index2]);
			Basis[Index2] = Saved + Right[Index2 + 1] * Temp;
			Saved = Left[Index1 - Index2] * Temp;
		}

		Basis[Index1] = Saved;
	}
}

void AutLib::CadLib::NurbsCurveLib::DersBasisFuns
(
	const Standard_Integer Span,
	const Standard_Real Parameter,
	const Standard_Integer Degree,
	const Standard_Integer Nth,
	const TColStd_Ary1dOfReal & Knots,
	TColStd_Ary2dOfReal & Ders
)
{
	TColStd_Ary2dOfReal
		ndu(Degree + 1, Degree + 1),
		A(2, Degree + 1);

	TColStd_Ary1dOfReal
		Left(Degree + 1),
		Right(Degree + 1);

	if (Ders.Size(0) NOT_EQUAL Nth + 1 OR Ders.Size(1) NOT_EQUAL Degree + 1)
		Ders.Resize(Nth + 1, Degree + 1);

	ndu[0][0] = 1.0;

	forThose(J, 1, Degree)
	{
		Left[J] = Parameter - Knots[Span + 1 - J];
		Right[J] = Knots[Span + J] - Parameter;

		Standard_Real Saved = 0.0;

		forThose(R, 0, J - 1)
		{
			ndu[J][R] = Right[R + 1] + Left[J - R];
			Standard_Real Temp = ndu[R][J - 1] / ndu[J][R];

			ndu[R][J] = Saved + Right[R + 1] * Temp;
			Saved = Left[J - R] * Temp;
		}
		ndu[J][J] = Saved;
	}

	// Loads the basis functions
	forThose(J, 0, Degree)
		Ders[0][J] = ndu[J][Degree];

	forThose(r, 0, Degree)
	{
		Standard_Integer s1 = 0;
		Standard_Integer s2 = 1;

		A[0][0] = 1.0;

		forThose(k, 1, Nth)
		{
			Standard_Real d = 0;
			Standard_Integer rk = r - k;
			Standard_Integer pk = Degree - k;

			if (r >= k)
			{
				A[s2][0] = A[s1][0] / ndu[pk + 1][rk];
				d = A[s2][0] * ndu[rk][pk];
			}

			Standard_Integer j1, j2;

			if (rk >= -1)
				j1 = 1;
			else
				j1 = -rk;

			if (r - 1 <= pk)
				j2 = k - 1;
			else
				j2 = Degree - r;

			forThose(j, j1, j2)
			{
				A[s2][j] = (A[s1][j] - A[s1][j - 1]) / ndu[pk + 1][rk + 1];
				d += A[s2][j] * ndu[rk + j][pk];
			}

			if (r <= pk)
			{
				A[s2][k] = -A[s1][k - 1] / ndu[pk + 1][r];
				d += A[s2][k] * ndu[r][pk];
			}

			Ders[k][r] = d;

			std::swap(s1, s2);
		}
	}

	Standard_Integer r = Degree;
	forThose(k, 1, Nth)
	{
		forThose(j, 0, Degree) Ders[k][j] *= r;
		r *= (Degree - k);
	}
}

void AutLib::CadLib::NurbsCurveLib::FormU
(
	const Standard_Integer Degree,
	const Standard_Integer MaxIndex, 
	const TColStd_Ary1dOfReal & Parameters, 
	TColStd_Ary1dOfReal & Knots
)
{
	forThose(Index, 0, Degree)
	{
		Try_Exception_Handle_Exit(Knots[Index] = 0.);
	}

	Standard_Integer M = Degree + MaxIndex + 1;

	forThose(Index, M - Degree, M)
	{
		Try_Exception_Handle_Exit(Knots[Index] = 1.);
	}

	Standard_Real InvDegree = 1.0 / (Standard_Real)Degree;

	forThose
	(
		Index,
		1,
		MaxIndex - Degree
	)
	{
		Standard_Real Sigma = 0.;

		forThose(I, Index, Index + Degree - 1)
		{
			Sigma += Parameters[I];
		}

		Try_Exception_Handle_Exit(Knots[Index + Degree] = InvDegree*Sigma);
	}
}