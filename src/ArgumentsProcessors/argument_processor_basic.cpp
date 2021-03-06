#include "argument_processor_basic.h"
#include <wsjcpp_package_manager.h>
#include <wsjcpp_core.h>

ArgumentProcessorInfo::ArgumentProcessorInfo() 
: WsjcppArgumentProcessor({"info"}, "information about package") {
      
}

// ---------------------------------------------------------------------

int ArgumentProcessorInfo::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        WsjcppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    std::cout << std::endl 
        << "===== begin: wsjcpp info =====" << std::endl
        << "Name: " << pkg.getName() << std::endl
        << "Version: " << pkg.getVersion() << std::endl
        << "Description: " << pkg.getDescription()
        << std::endl;

    if (pkg.isHolded()) {
        std::cout << "Package is holded" << std::endl;
    }
    std::cout << "Directory: " << pkg.getDir() << std::endl;
    std::cout << "wsjcpp.version = " << pkg.getWsjcppVersion() << std::endl;
    // print keywords
    std::vector<std::string> vKeywords = pkg.getListOfKeywords();
    if (vKeywords.size() > 0) {
        std::cout << "Keywords: " << std::endl;
        for (unsigned int i = 0; i < vKeywords.size(); i++) {
            std::cout << " - " << vKeywords[i] << std::endl;
        }
    }

    std::vector<WsjcppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
    if (vFiles.size() > 0) {
        std::cout << std::endl << "Distribution-Files: " << std::endl;
        for (unsigned int i = 0; i < vFiles.size(); i++) {
            WsjcppPackageManagerDistributionFile source = vFiles[i];
            std::cout << " - " << source.getSourceFile() << " -> " << source.getTargetFile() << "[" << source.getType() << "]" << std::endl;
        }
    }
    
    std::vector<WsjcppPackageManagerAuthor> vAuthors = pkg.getListOfAuthors();
    if (vAuthors.size() > 0) { 
        std::cout << std::endl << "Authors: " << std::endl;
        for (unsigned int i = 0; i < vAuthors.size(); i++) {
            WsjcppPackageManagerAuthor author = vAuthors[i];
            std::cout << " - " << author.getName() << " <" << author.getEmail() << ">" << std::endl;
        }
    }
    
    std::vector<WsjcppPackageManagerDependence> vDeps = pkg.getListOfDependencies();
    if (vDeps.size() > 0) { 
        std::cout << std::endl << "Dependencies: " << std::endl;
        for (unsigned int i = 0; i < vDeps.size(); i++) {
            WsjcppPackageManagerDependence dep = vDeps[i];
            std::cout << " - " << dep.getName() << ":" << dep.getVersion() << std::endl;
        }
    }
    

    std::cout << "===== end: wsjcpp info =====" << std::endl
        << std::endl;
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorInit::ArgumentProcessorInit() 
: WsjcppArgumentProcessor({"init"}, "Init package in current directory") {
      
}

// ---------------------------------------------------------------------

int ArgumentProcessorInit::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {

    if (vSubParams.size() != 1) {
        WsjcppLog::err(TAG, "Expected path to project");
        // printHelp(vArgs);
        return -1;
    }
    std::string sPath = vSubParams[0];
    WsjcppPackageManager pkg(sPath);
    if (!pkg.init()) {
        WsjcppLog::err(TAG, "Could not init package in current directory");
        return -1;
    }
    pkg.save();
    std::string sError;
    if (pkg.install("https://github.com/wsjcpp/wsjcpp-core:master", sError)) {
        pkg.save();
    }
    std::string sBuildSimplaShPath = sPath + "/build_simple.sh";
    pkg.updateAutogeneratedFiles();

    if (!WsjcppCore::fileExists(sBuildSimplaShPath)) {
        WsjcppCore::writeFile(sBuildSimplaShPath, pkg.getSampleForBuildSimpleSh());
    }

    std::string sSrcPath = sPath + "/src";
    if (!WsjcppCore::dirExists(sSrcPath)) {
        WsjcppCore::makeDir(sSrcPath);
    }

    std::string sMainCpp = sPath + "/src/main.cpp";
    if (!WsjcppCore::fileExists(sMainCpp)) {
        WsjcppCore::writeFile(sMainCpp, 
            "#include <string.h>\n"
            "#include <iostream>\n"
            "#include <algorithm>\n"
            "#include <wsjcpp_core.h>\n"
            "\n"
            "int main(int argc, const char* argv[]) {\n"
            "    std::string TAG = \"MAIN\";\n"
            "    std::string appName = std::string(WSJCPP_NAME);\n"
            "    std::string appVersion = std::string(WSJCPP_APP_VERSION);\n"
            "    if (!WsjcppCore::dirExists(\".logs\")) {\n"
            "        WsjcppCore::makeDir(\".logs\");\n"
            "    }\n"
            "    WsjcppLog::setPrefixLogFile(\"wsjcpp\");\n"
            "    WsjcppLog::setLogDirectory(\".logs\");\n"
            "    // TODO your code here\n"
            "    return 0;\n"
            "}\n"
        );
    }

    std::string sCMakeListsTXT = sPath + "/CMakeLists.txt";
    if (!WsjcppCore::fileExists(sCMakeListsTXT)) {
        WsjcppCore::writeFile(sCMakeListsTXT, 
            "cmake_minimum_required(VERSION " + pkg.getCMakeMinimumRequired() + ")\n"
            "\n"
            "project(" + pkg.getName() + " C CXX)\n"
            "\n"
            "include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)\n"
            "\n"
            "set(CMAKE_CXX_STANDARD " + pkg.getCMakeCxxStandard() + ")\n"
            "set(EXECUTABLE_OUTPUT_PATH ${" + pkg.getName() + "_SOURCE_DIR})\n"
            "\n"
            "# include header dirs\n"
            "list (APPEND WSJCPP_INCLUDE_DIRS \"src\")\n"
            "\n"
            "list (APPEND WSJCPP_SOURCES \"src/main.cpp\")\n"
            "\n"
            "#### BEGIN_WSJCPP_APPEND\n"
            "#### END_WSJCPP_APPEND\n"
            "\n"
            "include_directories(${WSJCPP_INCLUDE_DIRS})\n"
            "\n"
            "add_executable (" + pkg.getName() + " ${WSJCPP_SOURCES})\n"
            "\n"
            "target_link_libraries(" + pkg.getName() + " ${WSJCPP_LIBRARIES})\n"
            "\n"
            "install(\n"
            "    TARGETS\n"
            "        " + pkg.getName() + "\n"
            "    RUNTIME DESTINATION\n"
            "        /usr/bin\n"
            ")\n"
        );
    }

    return 0;
}


// ---------------------------------------------------------------------

ArgumentProcessorClean::ArgumentProcessorClean() 
: WsjcppArgumentProcessor({"clean"}, "Clean all packages and files for wsjcpp") {
      
}

// ---------------------------------------------------------------------

int ArgumentProcessorClean::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    std::vector<std::string> vRemoveFiles;
    vRemoveFiles.push_back("wsjcpp.yml");
    std::vector<std::string> vRemoveFolders;

    std::vector<std::string> vScanToRemoveFolders;
    vScanToRemoveFolders.push_back("src.wsjcpp");
    vScanToRemoveFolders.push_back(".wsjcpp");
    vScanToRemoveFolders.push_back("unit-tests.wsjcpp");

    while (vScanToRemoveFolders.size() > 0) {
        std::string sFolder = vScanToRemoveFolders.back();
        vScanToRemoveFolders.pop_back();
        if (WsjcppCore::dirExists(sFolder)) {
            WsjcppLog::info(TAG, "'" + sFolder + "' - scan folder");
            vRemoveFolders.push_back(sFolder);
            std::vector<std::string> vFiles = WsjcppCore::listOfFiles(sFolder);
            for (int i = 0; i < vFiles.size(); i++) {
                vRemoveFiles.push_back( sFolder + "/" + vFiles[i]);
            }
            std::vector<std::string> vFolders = WsjcppCore::listOfDirs(sFolder);
            for (int i = 0; i < vFolders.size(); i++) {
                vScanToRemoveFolders.push_back( sFolder + "/" + vFolders[i]);
            }
        }
    }
    
    while (vRemoveFiles.size() > 0) {
        std::string sFileName = vRemoveFiles.back();
        vRemoveFiles.pop_back();
        if (WsjcppCore::fileExists(sFileName)) {
            if (WsjcppCore::removeFile(sFileName)) {
                WsjcppLog::info(TAG, "'" + sFileName + "' - file removed");
            } else {
                WsjcppLog::err(TAG, "'" + sFileName + "' - file could not remove");
            }
        } else {
            WsjcppLog::info(TAG, "'" + sFileName + "' - file not found");
        }
    }

    while (vRemoveFolders.size() > 0) {
        std::string sFolder = vRemoveFolders.back();
        vRemoveFolders.pop_back();
        if (WsjcppCore::dirExists(sFolder)) {
            if (WsjcppCore::removeFile(sFolder)) {
                WsjcppLog::info(TAG, "'" + sFolder + "' - folder removed");
            } else {
                WsjcppLog::err(TAG, "'" + sFolder + "' - folder could not remove");
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorVersion

ArgumentProcessorVersion::ArgumentProcessorVersion() 
: WsjcppArgumentProcessor({"version"}, "Current version of wsjcpp") {
      
}

// ---------------------------------------------------------------------

int ArgumentProcessorVersion::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    // TODO move to default arguments
    std::cout << "Application: " << std::string(WSJCPP_APP_NAME) << std::endl;
    std::cout << "Version: " << std::string(WSJCPP_APP_VERSION) << std::endl;
    return 0;
}

// ---------------------------------------------------------------------