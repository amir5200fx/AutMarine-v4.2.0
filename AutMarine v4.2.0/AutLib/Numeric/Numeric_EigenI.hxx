#pragma once

inline M_AUT TColStd_Ary2dOfReal AutLib::NumLib::Numeric_Eigen::MatMul(const TColStd_Ary2dOfReal & A, const TColStd_Ary2dOfReal & B)
{
	Standard_Real Dot = 0;

	if (A.Size(1) NOT_EQUAL B.Size(0)) { CloseProgram(" Error in MatMul function"); }

	Standard_Integer m = A.Size(0);
	Standard_Integer n = A.Size(1);
	Standard_Integer p = B.Size(0);
	Standard_Integer q = B.Size(1);

	TColStd_Ary2dOfReal C(m, q);
	C.Init(0);

	for (Standard_Integer i = 0; i < m; i++)
		for (Standard_Integer j = 0; j < q; j++)
		{
			Dot = 0;
			for (Standard_Integer k = 0; k < n; k++)
				Dot += A[i][k] * B[k][j];
			C[i][j] = Dot;
		}

	MOVE(C);
}

inline M_AUT TColStd_Ary1dOfReal AutLib::NumLib::Numeric_Eigen::Diag(const TColStd_Ary2dOfReal & A)
{
	Standard_Integer n = A.Size(0);
	TColStd_Ary1dOfReal ary(n);
	ary.Init(0);
	for (Standard_Integer i = 0; i < n; i++)
		ary[i] = A[i][i];
	MOVE(ary);
}

inline M_AUT TColStd_Ary2dOfReal AutLib::NumLib::Numeric_Eigen::Iden(const Standard_Integer n)
{
	TColStd_Ary2dOfReal a(n, n);
	a.Init(0);
	for (Standard_Integer i = 0; i < n; i++)
		a[i][i] = 1;
	MOVE(a);
}

inline M_AUT TColStd_Ary2dOfReal AutLib::NumLib::Numeric_Eigen::tril(const TColStd_Ary2dOfReal & A)
{
	Standard_Integer n = A.Size(0);
	TColStd_Ary2dOfReal ary(n, n);
	ary.Init(0);

	for (Standard_Integer j = 0; j < n; j++)
		for (Standard_Integer i = j; i < n; i++)
			ary[i][j] = A[i][j];
	MOVE(ary);
}

inline M_AUT TColStd_Ary2dOfReal AutLib::NumLib::Numeric_Eigen::Transpose(const TColStd_Ary2dOfReal & a)
{
	Standard_Integer m = a.Size(0);
	Standard_Integer n = a.Size(1);

	TColStd_Ary2dOfReal b(n, m);
	b.Init(0);
	for (Standard_Integer i = 0; i < n; i++)
		for (Standard_Integer j = 0; j < m; j++)
			b[j][i] = a[i][j];
	MOVE(b);
}

inline M_AUT TColStd_Ary2dOfReal AutLib::NumLib::Numeric_Eigen::Invert_Low_Tri(const TColStd_Ary2dOfReal & l)
{
	TColStd_Ary2dOfReal L = l;
	Standard_Integer n = L.Size(0);
	Standard_Real dot = 0;

	for (Standard_Integer j = 0; j < n - 1; j++)
	{
		L[j][j] = 1.0 / L[j][j];
		for (Standard_Integer i = j + 1; i < n; i++)
		{
			dot = 0;
			for (Standard_Integer k = j; k <= i - 1; k++)
				dot += L[i][k] * L[k][j];
			L[i][j] = -dot / L[i][i];
		}
	}
	L[n - 1][n - 1] = 1.0 / L[n - 1][n - 1];
	MOVE(L);
}

inline void AutLib::NumLib::Numeric_Eigen::Choleski(TColStd_Ary2dOfReal & a)
{
	Standard_Integer n = a.Size(0);
	Standard_Real dot = 0;
	Standard_Real temp = 0;

	for (Standard_Integer j = 0; j < n; j++)
	{
		dot = 0;
		for (Standard_Integer k = 0; k < j; k++)
			dot += a[j][k] * a[j][k];
		temp = a[j][j] - dot;
		if (temp < 0.0) CloseProgram("Matrix is not positive definite");
		a[j][j] = sqrt(temp);
		for (Standard_Integer i = j + 1; i < n; i++)
		{
			dot = 0;
			for (Standard_Integer k = 0; k < j; k++)
				dot += a[i][k] * a[j][k];
			a[i][j] = (a[i][j] - dot) / a[j][j];
		}
	}
	a = tril(a);
}

inline void AutLib::NumLib::Numeric_Eigen::maxElem(const TColStd_Ary2dOfReal & a, Standard_Real & amax, Standard_Integer & k, Standard_Integer & l)
{
	Standard_Integer n = a.Size(0);
	amax = 0;
	for (Standard_Integer i = 0; i < n - 1; i++)
		for (Standard_Integer j = i + 1; j < n; j++)
			if (ABS(a[i][j]) >= amax)
			{
				amax = ABS(a[i][j]);
				k = i;
				l = j;
			}
}

inline void AutLib::NumLib::Numeric_Eigen::Rotate(Standard_Integer k, Standard_Integer l, TColStd_Ary2dOfReal & A, TColStd_Ary2dOfReal & P)
{
	Standard_Integer n = A.Size(0);
	Standard_Real diff = A[l][l] - A[k][k];
	Standard_Real t;
	Standard_Real phi;
	if (ABS(A[k][l]) < ABS(diff)*1.0e-36)
		t = A[k][l];
	else
	{
		phi = diff / (2 * A[k][l]);
		t = 1.0 / (ABS(phi) + sqrt(phi*phi + 1.0));
		if (phi < 0.0) t = -t;
	}
	Standard_Real c = 1.0 / sqrt(t*t + 1.0);
	Standard_Real s = t*c;
	Standard_Real tau = s / (1.0 + c);
	Standard_Real temp = A[k][l];
	A[k][l] = 0;
	A[k][k] -= t*temp;
	A[l][l] += t*temp;

	for (Standard_Integer i = 0; i < k; i++)
	{
		temp = A[i][k];
		A[i][k] = temp - s*(A[i][l] + tau*temp);
		A[i][l] += s*(temp - tau*A[i][l]);
	}

	for (Standard_Integer i = k + 1; i < l; i++)
	{
		temp = A[k][i];
		A[k][i] = temp - s*(A[i][l] + tau*A[k][i]);
		A[i][l] += s*(temp - tau*A[i][l]);
	}

	for (Standard_Integer i = l + 1; i < n; i++)
	{
		temp = A[k][i];
		A[k][i] = temp - s*(A[l][i] + tau*temp);
		A[l][i] += s*(temp - tau*A[l][i]);
	}

	for (Standard_Integer i = 0; i < n; i++)
	{
		temp = P[i][k];
		P[i][k] = temp - s*(P[i][l] + tau*P[i][k]);
		P[i][l] += s*(temp - tau*P[i][l]);
	}
}

inline void AutLib::NumLib::Numeric_Eigen::sortEigen(TColStd_Ary1dOfReal & eVals, TColStd_Ary2dOfReal & eVecs)
{
	Standard_Integer n = eVals.Size();
	Standard_Integer indx;
	Standard_Real val;
	Standard_Real temp;

	for (Standard_Integer i = 0; i < n - 1; i++)
	{
		indx = i;
		val = eVals[i];
		for (Standard_Integer j = i + 1; j < n; j++)
			if (eVals[j] < val)
			{
				indx = j;
				val = eVals[j];
			}
		if (indx != i)
		{
			temp = eVals[i];
			eVals[i] = eVals[indx];
			eVals[indx] = temp;
			swapCols(i, indx, eVecs);
		}
	}
}

inline void AutLib::NumLib::Numeric_Eigen::stdForm(const TColStd_Ary2dOfReal & A, const TColStd_Ary2dOfReal & B, TColStd_Ary2dOfReal & H, TColStd_Ary2dOfReal & T)
{
	TColStd_Ary2dOfReal L = B;
	Choleski(L);
	TColStd_Ary2dOfReal Linv = Invert_Low_Tri(L);
	T = Transpose(Linv);
	H = MatMul(Linv, MatMul(A, T));
}