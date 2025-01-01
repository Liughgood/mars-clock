#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "../include/clock.h"

#define DEG_TO_RAD (M_PI / 180.0)
#define SECONDS_IN_A_DAY 86400
#define MARS_SOL_IN_SECONDS 88775.244
#define MARS_SOL_IN_DAYS (MARS_SOL_IN_SECONDS / SECONDS_IN_A_DAY)
const double TT_UTC = 69.184;

/**
 * @brief 获取当前时间（地球时间）
 *
 * @return 返回当前时间的time_t类型值
 */
time_t time(time_t *t);

/**
 * @brief 将time_t类型的时间转换为UTC时间
 *
 * @param timep 指向time_t类型时间的指针
 * @return 返回指向tm结构的指针，表示UTC时间
 */
struct tm *gmtime(const time_t *timep);

/**
 * @brief 计算自 J2000 纪元以来的天数
 *
 * @param millis 当前时间的时间戳（毫秒）
 * @return 返回自 J2000 纪元以来的天数
 */
double getDeltraTj2000(long long millis);

// 处理度数的cos函数
double cos_deg(double degrees)
{
    return cos(degrees * DEG_TO_RAD);
}

// 处理度数的sin函数
double sin_deg(double degrees)
{
    return sin(degrees * DEG_TO_RAD);
}

/**
 * @brief 获取当前时间（地球时间）
 *
 * @return 返回当前时间的time_t类型值，毫秒级精度
 */
long long currentTimeMillis()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000;
}

/**
 * @brief 计算并输出当前火星时间
 *
 * 该函数获取当前地球时间，计算儒略日期，并将其转换为火星时间（MTC）。
 * 最后以HH:MM:SS格式输出火星时间。
 */
void calculate_mars_time()
{
    long long millis = currentTimeMillis();
    double JDut = getJDut(millis);
    double JDtt = getJDtt(JDut, TT_UTC);
    double DeltaTj2000 = getDeltaTj2000(JDtt);
    double M = calculateM(DeltaTj2000);
    double alphaFMS = calculateAlphaFMS(DeltaTj2000);
    double pbs = calculatePBS(DeltaTj2000);
    double v_M = calculateVM(M, pbs, DeltaTj2000);
    double Ls = calculateLs(alphaFMS, v_M);
    double EOT = calculateEOT(Ls, v_M);
    double MSD = calculateMSD(JDtt);
    double MST = calculateMST(MSD);
    double LMST = calculateLMST(MST, 0.0);
    double LTST = calculateLTST(LMST, EOT);

    // 输出火星时间 for debug
    /*
    printf("Current Earth Time: %lld\n", millis);
    printf("JDut: %lf\n", JDut);
    printf("JDtt: %lf\n", JDtt);
    printf("DeltaTj2000 %lf\n", DeltaTj2000);
    printf("M: %lf\n", M);
    printf("alphaFMS: %lf\n", alphaFMS);
    printf("pbs: %lf\n", pbs);
    printf("v_M: %lf\n", v_M);
    printf("Ls: %lf\n", Ls);
    printf("EOT: %lf\n", EOT);
    printf("MST: %lf\n", MST);
    printf("LMST: %lf\n", LMST);
    printf("LTST: %lf\n", LTST);
    */
    printf("Current Mars Sol Date: %lf %02d:%02d:%02d AMT \n", MSD / 24.0, (int)MST, (int)(MST * 60) % 60, (int)(MST * 3600) % 60);
}

double getJDut(long long millis)
{
    return (millis / 1000.0) / SECONDS_IN_A_DAY + 2440587.5;
}

double getJDtt(double JDut, double TT_UTC)
{
    return JDut + TT_UTC / SECONDS_IN_A_DAY;
}

double getDeltaTj2000(double JDtt)
{
    return JDtt - 2451545.0;
}

double calculateM(double DeltaTj2000)
{
    return fmod((19.3871 + 0.52402073 * DeltaTj2000), 360.0);
}

double calculateAlphaFMS(double DeltaTj2000)
{
    return fmod((270.3871 + 0.524038496 * DeltaTj2000), 360.0);
}

double calculatePBS(double DeltaTj2000)
{
    double A[] = {0.0071, 0.0057, 0.0039, 0.0037, 0.0021, 0.0020, 0.0018};
    double tau[] = {2.2353, 2.7543, 1.1177, 15.7866, 2.1354, 2.4694, 32.8493};
    double phi[] = {49.409, 168.173, 191.837, 21.736, 15.704, 95.528, 49.095};
    double pbs = 0.0;
    for (int i = 0; i < 7; i++)
    {
        pbs += A[i] * cos_deg(0.985626 * DeltaTj2000 / tau[i] + phi[i]);
    }
    return pbs;
}

double calculateVM(double M, double pbs, double DeltaTj2000)
{
    return (10.691 + 3.0e-7 * DeltaTj2000) * sin_deg(M) + 0.623 * sin_deg(2 * M) + 0.050 * sin_deg(3 * M) + 0.005 * sin_deg(4 * M) + 0.0005 * sin_deg(5 * M) + pbs;
}

double calculateLs(double alphaFMS, double v_M)
{
    return alphaFMS + v_M;
}

double calculateEOT(double Ls, double v_M)
{
    return 2.861 * sin_deg(2 * Ls) - 0.071 * sin_deg(4 * Ls) + 0.002 * sin_deg(6 * Ls) - v_M;
}

double calculateMSD(double JDtt)
{
    return 24.0 * ((JDtt - 2451549.5) / MARS_SOL_IN_DAYS + 44796.0 - 0.0009626);
}

double calculateMST(double msd)
{
    return fmod(msd, 24.0);
}

double calculateLMST(double MST, double L)
{
    return fmod((MST - L / 15), 24.0);
}

double calculateLTST(double LMTC, double EOT)
{
    return LMTC + EOT / 15;
}
