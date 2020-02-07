#include "unit_test_normalize_unit_test_name.h"
#include <vector>
#include <wsjcpp_package_manager.h>

REGISTRY_UNIT_TEST(UnitTestNormalizeUnitTestName)

UnitTestNormalizeUnitTestName::UnitTestNormalizeUnitTestName()
    : UnitTestBase("UnitTestNormalizeUnitTestName") {
}// ---------------------------------------------------------------------

void UnitTestNormalizeUnitTestName::init() {
    // nothing
}

// ---------------------------------------------------------------------
bool UnitTestNormalizeUnitTestName::run() {
    bool bTestSuccess = true;
    WSJCppPackageManager pkg(".");
    std::vector<std::pair<std::string, std::string>> tests;
    tests.push_back(std::pair<std::string, std::string>("UnitTest1", "UnitTest1"));
    tests.push_back(std::pair<std::string, std::string>("UnitTest1%%%$", "UnitTest1"));
    tests.push_back(std::pair<std::string, std::string>("%%%%UnitT%&!±!#est1%%%$", "UnitTest1"));
    tests.push_back(std::pair<std::string, std::string>("%%%%UnitT%выафва#est1%%%$", "UnitTest1"));
    for (int i = 0; i < tests.size(); i++) {
        std::string sName = tests[i].first;
        std::string sExpectedName = tests[i].second;
        std::string sGotName = pkg.normalizeUnitTestName(sName, true);
        compareS(bTestSuccess, sName, sGotName, sExpectedName);
        std::string sData;
        
    }
    
    return bTestSuccess;
}
