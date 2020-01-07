///
/// @file unitTest_domain.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief 
///

#ifndef UNITTEST_DOMAIN_H
#define UNITTEST_DOMAIN_H

#include <memory>
#include <unordered_set>

#include "solution/domain.hpp"

using namespace CppUnit;
using namespace stocos;

class UnitTest_domain : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UnitTest_domain);
    CPPUNIT_TEST(constructor);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void constructor(void) {
        std::shared_ptr<std::unordered_set<double>> definition_dom = std::make_shared<std::unordered_set<double>>();
        definition_dom->insert(5.5);
        definition_dom->insert(7.2);
        definition_dom->insert(9.2);

        // <TYPE_CELL>
        Domain<double> sol(definition_dom);

        sol.remove_element(5, 5.5);
        sol.add_element(2, 42);
        sol.show();
        const std::shared_ptr<const std::unordered_set<double>> x = sol.get_domain(5);
        const std::shared_ptr<const std::unordered_set<double>> x1 = sol.get_domain(5);
        
        for (auto it = x->begin(); it!= x->end(); ++it) {
            std::cout<<(*it)<<std::endl;
        }

        double v = sol.pick(5, 1);
        for (unsigned int i = 0 ; i < sol.size_domain(2) ; i++) {
            std::cout<<sol.pick(2, i)<<std::endl;
        }
        
    }

    private:

};

#endif