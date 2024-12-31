#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/clock.h"
#include "../include/test.h"

TestParams params;

void test_currentTimeMillis()
{
    CU_ASSERT(currentTimeMillis() > 0);
}

void test_getJDut()
{
    CU_ASSERT_DOUBLE_EQUAL(getJDut(params.millis), params.JDut, 0.1);
}

void test_getJDtt()
{
    CU_ASSERT_DOUBLE_EQUAL(getJDtt(params.JDut, 64.184), params.JDtt, 0.00001);
}

void test_getDeltaTj2000()
{
    CU_ASSERT_DOUBLE_EQUAL(getDeltaTj2000(params.JDtt), params.DeltaTj2000, 0.00001);
}

void test_calculateM()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateM(params.DeltaTj2000), params.M, 0.00001);
}

void test_calculateAlphaFMS()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateAlphaFMS(params.DeltaTj2000), params.alphaFMS, 0.00001);
}

void test_calculatePBS()
{
    CU_ASSERT_DOUBLE_EQUAL(calculatePBS(params.DeltaTj2000), params.pbs, 0.00001);
}

void test_calculateVM()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateVM(params.M, params.pbs, params.DeltaTj2000), params.v_M, 0.00001);
}

void test_calculateLs()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateLs(params.alphaFMS, params.v_M), params.Ls, 0.00001);
}

void test_calculateEOT()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateEOT(params.Ls, params.v_M), params.EOT, 0.00001);
}

void test_calculateMSD()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateMSD(params.JDtt), params.MSD, 0.00001);
}

void test_calculateMST()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateMST(params.MSD), params.MST, 0.00001);
}

void test_calculateLMST()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateLMST(params.MST, params.L), params.LMST, 0.0001);
}

void test_calculateLTST()
{
    CU_ASSERT_DOUBLE_EQUAL(calculateLTST(params.LMST, params.EOT), params.LTST, 0.00001);
}

int test_by_benchmark()
{
    // 设置测试参数
    params = (TestParams){
        .millis = 947116800000,
        .JDut = 2451549.500000,
        .JDtt = 2451549.500743,
        .DeltaTj2000 = 4.500743,
        .M = 21.745583,
        .alphaFMS = 272.745663,
        .pbs = 0.001418,
        .v_M = 4.441927,
        .Ls = 277.187589,
        .EOT = -5.187746,
        .MSD = 1075103.99425,
        .MST = 23.994249,
        .L = 0.0,
        .LMST = 23.994249,
        .LTST = 23.648400};

    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("SuiteName", 0, 0);
    CU_add_test(suite, "test of getJDut", test_getJDut);
    CU_add_test(suite, "test of getJDtt", test_getJDtt);
    CU_add_test(suite, "test of getDeltaTj2000", test_getDeltaTj2000);
    CU_add_test(suite, "test of calculateM", test_calculateM);
    CU_add_test(suite, "test of calculateAlphaFMS", test_calculateAlphaFMS);
    CU_add_test(suite, "test of calculatePBS", test_calculatePBS);
    CU_add_test(suite, "test of calculateVM", test_calculateVM);
    CU_add_test(suite, "test of calculateLs", test_calculateLs);
    CU_add_test(suite, "test of calculateEOT", test_calculateEOT);
    CU_add_test(suite, "test of calculateMST", test_calculateMST);
    CU_add_test(suite, "test of calculateLMTC", test_calculateLMST);
    CU_add_test(suite, "test of calculateLTST", test_calculateLTST);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

int test_by_MER_A_data()
{
    // 设置测试参数
    params = (TestParams){
        .millis = 1073137591000,
        .JDut = 2453008.07397,
        .JDtt = 2453008.074713,
        .DeltaTj2000 = 1463.07471,
        .M = 66.06858,
        .alphaFMS = 317.09457,
        .pbs = 0.01614,
        .v_M = 10.22959,
        .Ls = 327.32416,
        .EOT = -12.77553,
        .MSD = 1109173.16537,
        .MST = 13.165369,
        .L = 184.702,
        .LMST = 0.85190,
        // TODO 修正LTST的值
        .LTST = 0.00020};

    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("SuiteName2", 0, 0);
    CU_add_test(suite, "test of currentTimeMillis", test_currentTimeMillis);
    CU_add_test(suite, "test of getJDut", test_getJDut);
    double mst = calculateMST(params.JDtt);
    CU_add_test(suite, "test of getJDtt", test_getJDtt);
    CU_add_test(suite, "test of getDeltaTj2000", test_getDeltaTj2000);
    CU_add_test(suite, "test of calculateM", test_calculateM);
    CU_add_test(suite, "test of calculateAlphaFMS", test_calculateAlphaFMS);
    CU_add_test(suite, "test of calculatePBS", test_calculatePBS);
    CU_add_test(suite, "test of calculateVM", test_calculateVM);
    CU_add_test(suite, "test of calculateLs", test_calculateLs);
    CU_add_test(suite, "test of calculateEOT", test_calculateEOT);
    CU_add_test(suite, "test of calculateMST", test_calculateMST);
    CU_add_test(suite, "test of calculateLMTC", test_calculateLMST);
    CU_add_test(suite, "test of calculateLTST", test_calculateLTST);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

int main()
{
    test_by_benchmark();
    test_by_MER_A_data();
    return 0;
}