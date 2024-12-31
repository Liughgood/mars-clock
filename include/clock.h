#ifndef CLOCK_H
#define CLOCK_H

double getJDut(long long millis);
double getJDtt(double JDut, double TT_UTC);
double getDeltaTj2000(double JDut);
double calculateM(double DeltaTj2000);
double calculateAlphaFMS(double DeltaTj2000);
double calculatePBS(double DeltaTj2000);
double calculateVM(double M, double pbs, double DeltaTj2000);
double calculateLs(double alphaFMS, double v_M);
double calculateEOT(double Ls, double v_M);
double calculateMSD(double JDtt);
double calculateMST(double msd);
double calculateLMST(double MST, double L);
double calculateLTST(double LMTC, double EOT);
double cos_deg(double degrees);
double sin_deg(double degrees);
long long currentTimeMillis();
void calculate_mars_time();
#endif // CLOCK_H
