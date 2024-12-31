#ifndef TEST_H
#define TEST_H

typedef struct
{
    long long millis;
    double JDut;
    double JDtt;
    double DeltaTj2000;
    double M;
    double alphaFMS;
    double pbs;
    double v_M;
    double Ls;
    double EOT;
    double MSD;
    double MST;
    double L;
    double LMST;
    double LTST;
} TestParams;

extern TestParams params;

void test_currentTimeMillis();
void test_getJDut();
void test_getJDtt();
void test_getDeltaTj2000();
void test_calculateM();
void test_calculateAlphaFMS();
void test_calculatePBS();
void test_calculateVM();
void test_calculateLs();
void test_calculateEOT();
void test_calculateMST();
void test_calculateLMST();
void test_calculateLTST();

#endif // TEST_H
