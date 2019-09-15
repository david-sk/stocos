///
/// @file unitTest_QAP.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_EVALQAP_H
#define UNITTEST_EVALQAP_H

#include "problem/QAP.hpp"

using namespace CppUnit;
using namespace stocos;

class UnitTest_QAP : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_QAP);
    CPPUNIT_TEST(evaluation);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void evaluation(void) {
        // DATA
        unsigned int n = 12;
        unsigned int A[12][12] = {{0, 90, 10, 23, 43, 0, 0, 0, 0, 0, 0, 0}, 
                        {90, 0, 0, 0, 0, 88, 0, 0, 0, 0, 0, 0},
                        {10, 0, 0, 0, 0, 0, 26, 16, 0, 0, 0, 0},  
                        {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    
                        {0, 88, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                        {0, 0, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0},   
                        {0, 0, 16, 0, 0, 0, 0, 0, 0, 96, 0, 0},
                        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 29, 0},
                        {0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0, 37},
                        {0, 0, 0, 0, 0, 0, 0, 0, 29, 0, 0, 0},    
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 0, 0}};

        unsigned int B[12][12] = {{0, 36, 54, 26, 59, 72, 9, 34, 79, 17, 46, 95},  
                        {36, 0, 73, 35, 90, 58, 30, 78, 35, 44, 79, 36},
                        {54, 73, 0, 21, 10, 97, 58, 66, 69, 61, 54, 63}, 
                        {26, 35, 21, 0, 93, 12, 46, 40, 37, 48, 68, 85},
                        {59, 90, 10, 93, 0, 64, 5, 29, 76, 16, 5, 76},   
                        {72, 58, 97, 12, 64, 0, 96, 55, 38, 54, 0, 34},
                        {9, 30, 58, 46, 5, 96, 0, 83, 35, 11, 56, 37},   
                        {34, 78, 66, 40, 29, 55, 83, 0, 44, 12, 15, 80},
                        {79, 35, 69, 37, 76, 38, 35, 44, 0, 64, 39, 33}, 
                        {17, 44, 61, 48, 16, 54, 11, 12, 64, 0, 70, 86},
                        {46, 79, 54, 68, 5, 0, 56, 15, 39, 70, 0, 18},
                        {95, 36, 63, 85, 76, 34, 37, 80, 33, 86, 18, 0}};
        unsigned int p[12] = {7,5,12,2,1,3,9,11,10,6,8,4};
        unsigned int fitness = 9552;


        // 
        unsigned int **_A = new unsigned int*[n];
        unsigned int **_B = new unsigned int*[n];

        for(unsigned int i = 0 ; i < n ; i++) {
            _A[i] = new unsigned int[n];
            _B[i] = new unsigned int[n];
            for(unsigned int j = 0 ; j < n ; j++) {
                _A[i][j] = A[i][j];
                _B[i][j] = B[i][j];
            }
        }
        
        //
        SOL_QAP s(1, n);
        for (unsigned int i = 0 ; i < n ; i++)
            s(i, p[i]);

        // 
        QAP eQAP(n, _A, _B);

       for (unsigned int i=0; i < n; i++){
            delete[] _A[i];
            delete[] _B[i];
        }
        delete[] _A;
        delete[] _B;
        
        eQAP.evaluation(s);



        CPPUNIT_ASSERT(s.getFitness() == fitness);
    }



    private:

};

#endif