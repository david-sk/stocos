///
/// @file unitTest_messages.cpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2020-10
/// @brief g++ tests-unitaires/filtering/test.cpp -I sources/ -Iinclude -lcppunit -lpthread
/// -lboost_log -lboost_system -ljsoncpp
///

#include "../unitTest.h"

#ifndef UNITTEST_MESSAGES_H
#define UNITTEST_MESSAGES_H

#include "messages/french.h"

using namespace stocos;

class UnitTest_messages : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_messages);
    CPPUNIT_TEST(show_message);
    CPPUNIT_TEST_SUITE_END();

  public:
    void show_message(void) {
        Messages* messages = new French();
        CPPUNIT_ASSERT((*messages)("STOChastic Optimization Solver") ==
                       "STOChastic Optimization Solver");
        CPPUNIT_ASSERT((*messages)("STOChastic Optimization Solver") !=
                       "XTOChastic Optimization Solver");

        (*messages)("TEST", {"my$0", "my$1"});
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_messages);

#endif