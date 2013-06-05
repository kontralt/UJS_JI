#include "TLE_Asympt2.h"

TLE_Asympt2::TLE_Asympt2(const std::wstring &options) {
	swscanf(options.c_str(), L"%d-%d %d-%d %d-%d %lf %lf %lf", 
		    &t[0], &x[0], &t[1], &x[1], &t[2], &x[2], &coeffLimit[2], &coeffLimit[1], &coeffLimit[0]);
	collected = 0;
}

JudgeModule *TLE_Asympt2::create(const std::wstring &options) { 
	return new TLE_Asympt2(options); 
}

std::wstring TLE_Asympt2::id() {
	return L"TLE_Asympt2";
}

std::wstring TLE_Asympt2::info() {
	return L"Time Limit Exceed check module (asymptotical, degree 2) v1.0 [Limit = " 
		   L"(" + std::to_wstring((long double)coeffLimit[2]) + L")*x^2 + "
		   L"(" + std::to_wstring((long double)coeffLimit[1]) + L")*x + "
		   L"("+ std::to_wstring((long double)coeffLimit[0]) + L")]";
}

void TLE_Asympt2::afterSolution(int testN, ShellCommands *shell) {
	for (int i = 0; i < 3; i++) {
		if (t[i] == testN) {
			y[i] = shell->execData.time;
			collected++;
			break;
		}
	}
}

void calculateCoeff(int *x, int *y, double *coeff) {
	double z[3];
	for (int i = 0; i < 3; i++) {
		z[i] = y[i];
		for (int j = 0; j < 3; j++) {
			if (j == i)
				continue;
			z[i] /= (double)(x[i] - x[j]);
		}
	}
	coeff[2] = z[0] + z[1] + z[2];
	coeff[1] = -(z[0] * (x[1] + x[2]) + z[1] * (x[0] + x[2]) + z[2] * (x[0] + x[1]));
	coeff[0] = z[0] * x[1] * x[2] + z[1] * x[0] * x[2] + z[2] * x[0] * x[1];
}

int compareCoeff(double *coeffA, double *coeffB) {
	for (int i = 2; i >= 0; i--)
		if (fabs(coeffA[i] - coeffB[i]) > 1e-9)
			return coeffA[i] > coeffB[i] ? 1 : -1;
	return 0;
}

std::pair<double, std::wstring> TLE_Asympt2::verdict() {
	if (collected < 3)
		return std::make_pair(0, L"Not enough data collected.");
	if (collected < 4) {
		calculateCoeff(x, y, coeff);
		collected = 4;
	}
	if (compareCoeff(coeff, coeffLimit) > 0) {
		return std::make_pair(0, L"Time Limit Exceeded: "
			                     L"(" + std::to_wstring((long double)coeff[2]) + L")*x^2 + "
		                         L"(" + std::to_wstring((long double)coeff[1]) + L")*x + "
		                         L"("+ std::to_wstring((long double)coeff[0]) + L")]");
	}
	return std::make_pair(1, L"OK: test passed (" 
		                     L"(" + std::to_wstring((long double)coeff[2]) + L")*x^2 + "
		                     L"(" + std::to_wstring((long double)coeff[1]) + L")*x + "
		                     L"("+ std::to_wstring((long double)coeff[0]) + L")]");
}