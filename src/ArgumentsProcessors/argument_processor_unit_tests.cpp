#include "argument_processor_unit_tests.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>

ArgumentProcessorUnitTests::ArgumentProcessorUnitTests() 
: WsjcppArgumentProcessor({"unit-tests", "ut"}, "manage unit-tests in package") {
    registryProcessor(new ArgumentProcessorUnitTestsCreate());
    registryProcessor(new ArgumentProcessorUnitTestsDelete());
    registryProcessor(new ArgumentProcessorUnitTestsEnable());
    registryProcessor(new ArgumentProcessorUnitTestsDisable());
    registryProcessor(new ArgumentProcessorUnitTestsList());
}

// ---------------------------------------------------------------------

ArgumentProcessorUnitTestsCreate::ArgumentProcessorUnitTestsCreate() 
: WsjcppArgumentProcessor({"create"}, "create a new unit-test") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsCreate::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() != 2) {
        WsjcppLog::err(TAG, "Usage: <Name> <Description>");
        return -1;
    }
    if (pkg.createUnitTest(vSubParams[0], vSubParams[1])) {
      pkg.save();
      return 0;
    }

    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorUnitTestsEnable::ArgumentProcessorUnitTestsEnable() 
: WsjcppArgumentProcessor({"enable"}, "Enable unit-test") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsEnable::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }
    if (vSubParams.size() != 1) {
        WsjcppLog::err(TAG, "Usage: <Name>");
        return -1;
    }
    
    if (pkg.enableUnitTest(vSubParams[0], true)) {
      pkg.save();
      pkg.updateAutogeneratedFiles();
      return 0;
    }
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorUnitTestsDisable::ArgumentProcessorUnitTestsDisable() 
: WsjcppArgumentProcessor({"disable"}, "Disable unit-test") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsDisable::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }
    
    if (vSubParams.size() != 1) {
        WsjcppLog::err(TAG, "Usage: <Name>");
        return -1;
    }

    if (pkg.enableUnitTest(vSubParams[0], false)) {
      pkg.save();
      pkg.updateAutogeneratedFiles();
      return 0;
    }
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorUnitTestsDelete::ArgumentProcessorUnitTestsDelete() 
: WsjcppArgumentProcessor({"delete"}, "Delete unit-test by name") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsDelete::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() != 1) {
        WsjcppLog::err(TAG, "Usage: <Name>");
        return -1;
    }
    std::string sUnitTestName = vSubParams[0];
    std::vector<WsjcppPackageManagerUnitTest> vUnitTests = pkg.getListOfUnitTests();
    for (int i = 0; i < vUnitTests.size(); i++) {
        WsjcppPackageManagerUnitTest ut = vUnitTests[i];
        if (ut.getName() == sUnitTestName) {
            if (pkg.deleteUnitTest(vSubParams[0])) {
                pkg.save();
                WsjcppLog::ok(TAG, "Unit Test '" + sUnitTestName + "' removed successfully.");
                return 0;
            } else {
                WsjcppLog::err(TAG, "Could not delete unit-test with name '" + sUnitTestName + "'");
                return -1;
            }
        }
    }
    WsjcppLog::err(TAG, "Unit test with name '" + sUnitTestName + "' did not found");
    return -1;
}

// ---------------------------------------------------------------------
// ArgumentProcessorUnitTestsList

ArgumentProcessorUnitTestsList::ArgumentProcessorUnitTestsList() 
: WsjcppArgumentProcessor({"list"}, "list of unit-test") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }
    std::string sRes = "\nUnit Tests Cases:\n";
    std::vector<WsjcppPackageManagerUnitTest> vUnitTests = pkg.getListOfUnitTests();
    for (int i = 0; i < vUnitTests.size(); i++) {
      WsjcppPackageManagerUnitTest ut = vUnitTests[i];
      sRes += "* " + ut.getName() + " - " + ut.getDescription() + "\n";
    }
    WsjcppLog::info(TAG, sRes);
    return 0;
}

// ---------------------------------------------------------------------
