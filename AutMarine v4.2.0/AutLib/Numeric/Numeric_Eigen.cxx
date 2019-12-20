#include <Numeric_Eigen.hxx>

void AutLib::NumLib::Numeric_Eigen::CalcEigen
(
	const TColStd_Ary2dOfReal & A,
	TColStd_Ary1dOfReal & eVals,
	TColStd_Ary2dOfReal & eVecs,
	const Standard_Real tol
)
{
	TColStd_Ary2dOfReal a = A;

	Standard_Integer n = a.Size(0);
	Standard_Integer maxRot = 5 * n*n;  // Limit number of rotations

	TColStd_Ary2dOfReal P = Iden(n);  // Initialize rotation matrix

	Standard_Integer k, l;
	Standard_Real amax;

	for (Standard_Integer i = 1; i <= maxRot; i++)  // Begin Jacobi rotations
	{
		maxElem(a, amax, k, l);
		if (amax < tol)
		{
			eVals = Diag(a);
			eVecs = P;
			return;
		}
		Rotate(k, l, a, P);
	}

	CloseProgram("Too many Jacobi rotations");
}

void AutLib::NumLib::Numeric_Eigen::CalcGenEigen
(
	const TColStd_Ary2dOfReal & A,
	const TColStd_Ary2dOfReal & B, 
	TColStd_Ary1dOfReal & eVals, 
	TColStd_Ary2dOfReal & eVecs, 
	const Standard_Real eps
)
{
	Standard_Integer n = A.Size(0);
	TColStd_Ary2dOfReal H(n, n), T(n, n);
	TColStd_Ary2dOfReal Z(n, n);

	H.Init(0);
	T.Init(0);
	Z.Init(0);

	stdForm(A, B, H, T);
	CalcEigen(H, eVals, Z, eps);
	eVecs = MatMul(T, Z);
	Standard_Real dot;
	Standard_Real xMag;
	for (Standard_Integer i = 0; i < n; i++)
	{
		dot = 0;
		for (Standard_Integer k = 0; k < n; k++)
			dot += eVecs[k][i] * eVecs[k][i];
		xMag = sqrt(dot);
		for (Standard_Integer k = 0; k < n; k++)
			eVecs[k][i] /= xMag;
	}
	sortEigen(eVals, eVecs);
}