#include "wsjcpp_package_manager.h"
#include <iostream>
#include <wsjcpp_core.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <curl/curl.h>
#include <wsjcpp_hashes.h>
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// WSJCppPackageManagerDistributionFile

WSJCppPackageManagerDistributionFile::WSJCppPackageManagerDistributionFile() {
    TAG = "WSJCppPackageManagerDistributionFile";
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerDistributionFile::fromYAML(WSJCppYAMLItem *pYamlDistributionFile) {
    m_pYamlDistributionFile = pYamlDistributionFile;
    if (!m_pYamlDistributionFile->hasElement("source-file")) {
        WSJCppLog::err(TAG, "Missing required field 'source-file' in " + m_pYamlDistributionFile->getForLogFormat());
        return false; 
    } else {
        m_sSourceFile = m_pYamlDistributionFile->getElement("source-file")->getValue();
    }

    if (!m_pYamlDistributionFile->hasElement("target-file")) {
        WSJCppLog::err(TAG, "Missing required field 'target-file' in " + m_pYamlDistributionFile->getForLogFormat());
        return false; 
    } else {
        m_sTargetFile = m_pYamlDistributionFile->getElement("target-file")->getValue();
    }

    if (!m_pYamlDistributionFile->hasElement("sha1")) {
        WSJCppLog::err(TAG, "Missing required field 'sha1' in " + m_pYamlDistributionFile->getForLogFormat());
        return false; 
    } else {
        m_sSha1 = m_pYamlDistributionFile->getElement("sha1")->getValue();
    }

    if (!m_pYamlDistributionFile->hasElement("type")) {
        WSJCppLog::err(TAG, "Missing required field 'type' in " + m_pYamlDistributionFile->getForLogFormat());
        return false; 
    } else {
        m_sType = m_pYamlDistributionFile->getElement("type")->getValue();
    }

    // TODO check possible formats

    return true;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerDistributionFile::toYAML() {
    m_pYamlDistributionFile->getElement("source-file")->setValue(m_sSourceFile, true);
    m_pYamlDistributionFile->getElement("target-file")->setValue(m_sTargetFile, true);
    m_pYamlDistributionFile->getElement("sha1")->setValue(m_sSha1, true);
    m_pYamlDistributionFile->getElement("type")->setValue(m_sType, true);
    return m_pYamlDistributionFile;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionFile::getSourceFile() {
    return m_sSourceFile;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionFile::getTargetFile() {
    return m_sTargetFile;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionFile::getSha1() {
    return m_sSha1;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDistributionFile::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDistributionFile::setSourceFile(const std::string &sSourceFile) {
    m_sSourceFile = sSourceFile;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDistributionFile::setTargetFile(const std::string &sTargetFile) {
    m_sTargetFile = sTargetFile;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDistributionFile::setSha1(const std::string &sSha1) {
    m_sSha1 = sSha1;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDistributionFile::setType(const std::string &sType) {
    m_sType = sType;
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerAuthor

WSJCppPackageManagerAuthor::WSJCppPackageManagerAuthor() {

}

// ---------------------------------------------------------------------

WSJCppPackageManagerAuthor::WSJCppPackageManagerAuthor(const std::string &sName, const std::string &sEmail) {
    TAG = "WSJCppPackageManagerAuthor";
    m_sName = sName;
    m_sEmail = sEmail;
    m_pYamlAuthor = nullptr;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerAuthor::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerAuthor::getEmail() {
    return m_sEmail;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerAuthor::getFullAuthor() {
    return m_sName + " <" + m_sEmail + ">";
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerAuthor::toYAML() {
    m_pYamlAuthor->getElement("name")->setValue(m_sName, true);
    m_pYamlAuthor->getElement("email")->setValue(m_sEmail, true);
    return m_pYamlAuthor;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerAuthor::fromYAML(WSJCppYAMLItem *pYamlAuthor) {
    m_pYamlAuthor = pYamlAuthor;
    if (!m_pYamlAuthor->hasElement("name")) {
        // TODO prepare in yaml getOriginalLineForError()
        WSJCppLog::err(TAG, "Missing required field 'name' in " + pYamlAuthor->getForLogFormat());
        return false; 
    } else {
        m_sName = m_pYamlAuthor->getElement("name")->getValue();
    }

    if (!m_pYamlAuthor->hasElement("email")) {
        WSJCppLog::err(TAG, "Missing required field 'email' in " + pYamlAuthor->getForLogFormat());
        return false; 
    } else {
        m_sEmail = m_pYamlAuthor->getElement("email")->getValue();
    }
    return true;
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerServer - server info class

WSJCppPackageManagerServer::WSJCppPackageManagerServer() {
    TAG = "WSJCppPackageManagerServer";
}

// ---------------------------------------------------------------------

WSJCppPackageManagerServer::WSJCppPackageManagerServer(const std::string &sAddress) {
    TAG = "WSJCppPackageManagerServer";
    m_sAddress = sAddress;
    m_pYamlServer = nullptr;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerServer::toYAML() {
    m_pYamlServer->setValue(m_sAddress, true);
    return m_pYamlServer;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerServer::fromYAML(WSJCppYAMLItem *pYaml) {
    m_pYamlServer = pYaml;
    m_sAddress = m_pYamlServer->getValue();
    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerServer::getAddress() {
    return m_sAddress;
}

// ---------------------------------------------------------------------
// WSJCppPackageManagerRepository - repository struct

WSJCppPackageManagerRepository::WSJCppPackageManagerRepository() {
    TAG = "WSJCppPackageManagerRepository";
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerRepository::toYAML() {
    m_pYamlRepository->getElement("url")->setValue(m_sUrl, true);
    m_pYamlRepository->getElement("type")->setValue(m_sType, true);
    return m_pYamlRepository;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerRepository::fromYAML(WSJCppYAMLItem *pYaml) {
    m_pYamlRepository = pYaml;
    if (!m_pYamlRepository->hasElement("type")) {
        WSJCppLog::err(TAG, "Missing required field 'type' in " + m_pYamlRepository->getForLogFormat());
        return false; 
    } else {
        m_sType = m_pYamlRepository->getElement("type")->getValue();
    }

    if (!m_pYamlRepository->hasElement("url")) {
        // TODO prepare in yaml getOriginalLineForError()
        WSJCppLog::err(TAG, "Missing required field 'url' in " + m_pYamlRepository->getForLogFormat());
        return false; 
    } else {
        m_sUrl = m_pYamlRepository->getElement("url")->getValue();
    }
    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerRepository::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerRepository::getUrl() {
    return m_sUrl;
}

// ---------------------------------------------------------------------
// WSJCppPackageManager - main class

WSJCppPackageManagerDependence::WSJCppPackageManagerDependence() {
    TAG = "WSJCppPackageManagerDependence";
    m_pYamlDependece = nullptr;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppPackageManagerDependence::toYAML() {
    m_pYamlDependece->getElement("url")->setValue(m_sUrl, true);
    m_pYamlDependece->getElement("name")->setValue(m_sName, true);
    m_pYamlDependece->getElement("version")->setValue(m_sVersion, true);
    m_pYamlDependece->getElement("origin")->setValue(m_sOrigin, true);
    m_pYamlDependece->getElement("installation-dir")->setValue(m_sInstallationDir, true);
    return m_pYamlDependece;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManagerDependence::fromYAML(WSJCppYAMLItem *pYaml) {
    m_pYamlDependece = pYaml;
    if (!m_pYamlDependece->hasElement("name")) {
        WSJCppLog::err(TAG, "Missing required field 'name' in " + m_pYamlDependece->getForLogFormat());
        return false;
    } else {
        m_sName = m_pYamlDependece->getElement("name")->getValue();
    }

    if (!m_pYamlDependece->hasElement("version")) {
        WSJCppLog::err(TAG, "Missing required field 'version' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sVersion = m_pYamlDependece->getElement("version")->getValue();
    }

    if (!m_pYamlDependece->hasElement("url")) {
        WSJCppLog::err(TAG, "Missing required field 'url' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sUrl = m_pYamlDependece->getElement("url")->getValue();
    }

    if (!m_pYamlDependece->hasElement("installation-dir")) {
        WSJCppLog::err(TAG, "Missing required field 'installation-dir' in " + m_pYamlDependece->getForLogFormat());
        return false; 
    } else {
        m_sInstallationDir = m_pYamlDependece->getElement("installation-dir")->getValue();
    }

    return true;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getInstallationDir() const {
    return m_sInstallationDir;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getUrl() const {
    return m_sUrl;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getName() const {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getVersion() const {
    return m_sVersion;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManagerDependence::getOrigin() const {
    return m_sOrigin;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setName(const std::string &sName) {
    m_sName = sName;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setVersion(const std::string &sVersion) {
    m_sVersion = sVersion;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setOrigin(const std::string &sOrigin) {
    m_sOrigin = sOrigin;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setUrl(const std::string &sUrl) {
    m_sUrl = sUrl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManagerDependence::setInstallationDir(const std::string &sInstallationDir) {
    m_sInstallationDir = sInstallationDir;
}

// ---------------------------------------------------------------------
// WSJCppPackageManager - main class

WSJCppPackageManager::WSJCppPackageManager(const std::string &sDir) {
    TAG = "WSJCppPackageManager";
    m_sDir = sDir;
    m_sDirWithSources = m_sDir + "/src.wsjcpp";
    m_sGithubPrefix = "https://github.com/";
    // TODO m_sGithubPrefix = "git@";  // try clone project to cache directory
    m_sBitbucketPrefix = "https://bitbucket.com/";
    m_sFilePrefix = "file:///"; // from file system
    m_sHttpPrefix = "http://"; // from some http://
    m_sHttpsPrefix = "https://";
    m_sYamlFilename = "wsjcpp.yml";
    m_sWSJCppCurrentVersion = "v0.0.1";
    m_sWSJCppVersion = m_sWSJCppCurrentVersion;
    m_bHolded = false;
    m_sIssues = "none";
}

// ---------------------------------------------------------------------

WSJCppPackageManager::WSJCppPackageManager(const std::string &sDir, const std::string &sParentDir, bool bHolded) 
: WSJCppPackageManager(sDir) {
    m_sDirWithSources = m_sDir + "/src.wsjcpp";
    m_sYamlFilename = "wsjcpp.hold.yml";
    m_bHolded = true;
    m_sParentDir = sParentDir;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::init() {

    if (!WSJCppCore::dirExists(m_sDir)) {
        std::cout << "Directory '" << m_sDir << "' did not exists... create the dir ? (y/n)" << std::endl;
        std::string sYN;
        std::cin >> sYN;
        if (sYN == "y" || sYN == "Y") {
            WSJCppCore::makeDir(m_sDir);
        }

        if (!WSJCppCore::dirExists(m_sDir)) {
            std::cout << "ERROR: Directory '" << m_sDir << "' did not exists." << std::endl;
            return false;
        }
    }

    std::cout << "Directory: " << m_sDir << std::endl; // Type a number and press enter
    std::cout << "Source Package Name: ";
    std::getline(std::cin, m_sName);
    std::cout << "Version: ";
    std::getline(std::cin, m_sVersion);
    std::cout << "Description: ";
    std::getline(std::cin, m_sDescription);
    
    std::string sAuthorName = "";
    std::cout << "Author's Name: ";
    std::getline(std::cin, sAuthorName);

    std::string sAuthorEmail = "";
    std::cout << "Author's Email: ";
    std::getline(std::cin, sAuthorEmail);

    WSJCppPackageManagerAuthor author(sAuthorName, sAuthorEmail);
    m_vAuthors.push_back(author);
    
    for (int i = 0; i < 10; i++) {
        std::string sKeyword = "";
        std::cout << "Keyword " << (i+1) << ": ";
        std::getline(std::cin, sKeyword);
        if (sKeyword == "") {
            break;
        }
        m_vKeywords.push_back(sKeyword);
    }

    std::string sDefaultServerAddress = "sea-kg.com";
    std::string sServerAddress = "sea-kg.com";
    std::cout << "Server Address (default '" << sDefaultServerAddress << "'): ";
    std::getline(std::cin, sServerAddress);
    if (sServerAddress == "") {
        sServerAddress = sDefaultServerAddress;
    }
    WSJCppPackageManagerServer server(sServerAddress);
    m_vServers.push_back(server);

    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::save() {
    if (m_bHolded) {
        WSJCppLog::throw_err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WSJCppCore::dirExists(m_sDirWithSources)) {
        WSJCppCore::makeDir(m_sDirWithSources);
    }

    std::string sGitkeepFile = m_sDirWithSources + "/.gitkeep";
    if (!WSJCppCore::fileExists(sGitkeepFile)) {
        WSJCppCore::writeFile(sGitkeepFile, ""); // TODO createEmptyFile
    }
    m_yamlPackageInfo.saveToFile(m_sYamlFullpath);

    /* 
    m_jsonPackageInfo["wsjcpp_version"] = m_sWSJCppVersion;
    m_jsonPackageInfo["name"] = m_sName;
    m_jsonPackageInfo["version"] = m_sVersion;
    m_jsonPackageInfo["description"] = m_sDescription;
    m_jsonPackageInfo["keywords"] = m_vKeywords;

    nlohmann::json jsonAuthors = nlohmann::json::array();
    for (int i = 0; i < m_vAuthors.size(); i++) {
        jsonAuthors.push_back(m_vAuthors[i].toJson());
    }
    // m_jsonPackageInfo["authors"] = jsonAuthors;

    nlohmann::json jsonServers = nlohmann::json::array();
    for (int i = 0; i < m_vServers.size(); i++) {
        jsonServers.push_back(m_vServers[i].toJson());
    }

    m_jsonPackageInfo["servers"] = jsonServers;

    nlohmann::json jsonDependencies = nlohmann::json::array();
    for (int i = 0; i < m_vDependencies.size(); i++) {
        jsonDependencies.push_back(m_vDependencies[i].toJson());
    }
    m_jsonPackageInfo["dependencies"] = jsonDependencies;

    nlohmann::json jsonRepositories = nlohmann::json::array();
    for (int i = 0; i < m_vRepositories.size(); i++) {
        jsonRepositories.push_back(m_vRepositories[i].toJson());
    }
    m_jsonPackageInfo["repositories"] = jsonRepositories;

    int indent = 4;
    std::ofstream wsjcppJson(m_sDir + "/" + m_sYamlFilename);
    wsjcppJson << std::setw(4) << m_jsonPackageInfo << std::endl;
    */
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::load() {
    m_sYamlFullpath = m_sDir + "/" + m_sYamlFilename;

    if (!WSJCppCore::fileExists(m_sYamlFullpath)) {
        std::cout << "ERROR: '" << m_sYamlFullpath << "' did not found" << std::endl;
        return false;
    }
    
    if (!m_yamlPackageInfo.loadFromFile(m_sYamlFullpath)) {
        return false;
    }

    std::vector<std::string> vKeys = m_yamlPackageInfo.getRoot()->getKeys();
    for (int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        // WSJCppLog::info(TAG, "Process option '" + sKey + "'");
        if (sKey == "version") {
            if (!readFieldVersion()) {
                return false;
            }
        } else if (sKey == "cmake_minimum_required") {
            if (!readFieldCMakeMinimumRequired()) {
                return false;
            }
        } else if (sKey == "cmake_cxx_standard") {
            if (!readFieldCMakeCxxStandard()) {
                return false;
            }
        } else if (sKey == "name") {
            if (!readFieldName()) {
                return false;
            }
        } else if (sKey == "description") {
            if (!readFieldDescription()) {
                return false;
            }
        } else if (sKey == "wsjcpp_version") {
            if (!readFieldWsjcppVersion()) {
                return false;
            }
        } else if (sKey == "issues") {
            if (!readFieldIssues()) {
                return false;
            }
        } else if (sKey == "keywords") {
            if (!readFieldKeywords()) {
                return false;
            }
        } else if (sKey == "authors") {
            if (!readFieldAuthors()) {
                return false;
            }
        } else if (sKey == "distribution") {
            if (!readFieldDistribution()) {
                return false;
            }
        } else if (sKey == "servers") {
            if (!readFieldServers()) {
                return false;
            }
        } else if (sKey == "dependencies") {
            if (!readFieldDependencies()) {
                return false;
            }
        } else if (sKey == "repositories") {
            if (!readFieldRepositories()) {
                return false;
            }
        } else if (sKey == "required-libraries") {
            if (!readFieldRequiredLibraries()) {
                return false;
            }
        } else {
            WSJCppLog::warn(TAG, "Ignored option '" + sKey + "' in " + m_yamlPackageInfo.getRoot()->getForLogFormat());
        }
    }

    // WSJCppLog::warn(TAG, "Loaded");
    // TODO required-libraries
    // TODO required-pkg-config
    // TODO replace-dependencies
    // TODO check requered fields

    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addSourceFile(const std::string &sSourceFile, const std::string &sTargetFile, const std::string &sType) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WSJCppCore::fileExists(sSourceFile)) {
        WSJCppLog::err(TAG, "'" + sSourceFile + "' file does not exists");
        return false;
    }
    std::vector<WSJCppPackageManagerDistributionFile>::iterator it;
    for (it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            WSJCppLog::err(TAG, "This package already contained file '" + sSourceFile + "'");
            return false;
        }
    }

    std::string sContent = "";
    if (!WSJCppCore::readTextFile(sSourceFile, sContent)) {
        return false;
    }
    std::string sSha1 = WSJCppHashes::sha1_calc_hex(sContent);

    WSJCppPackageManagerDistributionFile file;
    file.setSourceFile(sSourceFile);
    file.setTargetFile(sTargetFile);
    file.setType(sType);
    file.setSha1(sSha1);
    m_vDistributionFiles.push_back(file);
    
    WSJCppYAMLItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
    WSJCppYAMLPlaceInFile pl;
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(pDist, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_MAP);
    pItem->setElementValue("source-file", false, sSourceFile, true);
    pItem->setElementValue("target-file", false, sTargetFile, true);
    pItem->setElementValue("type", false, sType, true);
    pItem->setElementValue("sha1", false, sSha1, true);
    pDist->appendElement(pItem);

    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::removeSourceFile(const std::string &sSourceFile) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }
    bool bResult = false;
    for (auto it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            m_vDistributionFiles.erase(it);
            bResult = true;
        }
    }
    if (bResult) {
        bResult = false;
        WSJCppYAMLItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
        int nLen = pDist->getLength();
        for (int i = nLen-1; i >= 0; i--) {
            WSJCppYAMLItem *pItem = pDist->getElement(i);
            if (pItem->getElement("source-file")->getValue() == sSourceFile) {
                pDist->removeElement(i);
                bResult = true;
            }
        }
    }

    if (!bResult) {
        WSJCppLog::err(TAG, "Distribution file '" + sSourceFile + "' cound not found in this package");
    }
    return bResult;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateSourceFile(const std::string &sSourceFile) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WSJCppCore::fileExists(sSourceFile)) {
        WSJCppLog::err(TAG, "'" + sSourceFile + "' file does not exists");
        return false;
    }

    std::string sContent = "";
    if (!WSJCppCore::readTextFile(sSourceFile, sContent)) {
        return false;
    }
    std::string sSha1 = WSJCppHashes::sha1_calc_hex(sContent);

    WSJCppLog::info(TAG, "'" + sSourceFile + "' some");

    bool bFound = false;
    std::vector<WSJCppPackageManagerDistributionFile>::iterator it;
    for (it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            it->setSha1(sSha1);
            bFound = true;
        }
    }

    if (!bFound) {
        WSJCppLog::err(TAG, "'" + sSourceFile + "' file not found in list. Please add this before");
        return false;
    }

    if (bFound) {
        bFound = false;
        WSJCppYAMLItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
        int nLen = pDist->getLength();
        for (int i = nLen-1; i >= 0; i--) {
            WSJCppYAMLItem *pItem = pDist->getElement(i);
            if (pItem->getElement("source-file")->getValue() == sSourceFile) {
                pItem->getElement("sha1")->setValue(sSha1, true);
                bFound = true;
            }
        }
    }
    return bFound;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printServers() {
    for (auto it = m_vServers.begin(); it != m_vServers.end(); ++it) {
        std::cout << it->getAddress() << std::endl;
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addServer(const std::string &sServer) {
    if (m_bHolded) {
        std::cout << "ERROR: package is holded" << std::endl;
        return false;
    }

    for (auto it = m_vServers.begin(); it != m_vServers.end(); ++it) {
        if (it->getAddress() == sServer) {
            std::cout << "Error: Server '" << sServer << "' already defined." << std::endl;
            return false;
        }
    }

    WSJCppPackageManagerServer server(sServer);
    m_vServers.push_back(server);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::deleteServer(const std::string &sServer) {
    if (m_bHolded) {
        std::cout << "ERROR: wsjcpp is holded" << std::endl;
        return false;
    }

    for (auto it = m_vServers.begin(); it != m_vServers.end(); ++it) {
        if (it->getAddress() == sServer) {
            m_vServers.erase(it);
            return true;
        }
    }
    std::cout << "Error: Server '" << sServer << "' did not found." << std::endl;
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::updateDependencies() {
    if (m_bHolded) {
        std::cout << "ERROR: wsjcpp is holded" << std::endl;
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printDependencies(std::string sIntent) {
    std::string sNexIntent = sIntent + "  \\--";
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        std::cout << sIntent << " * " << it->getName() << ":" << it->getVersion() << "    (" << it->getUrl() << ":" << it->getInstallationDir() << ")" << std::endl;
        if (m_bHolded) {
            WSJCppPackageManager m(m_sParentDir + "/" + it->getName(), m_sParentDir, true);
            if (m.load()) {
                m.printDependencies(sNexIntent);
            }
        } else {
            WSJCppPackageManager m(m_sDirWithSources + "/" + it->getName(), m_sDirWithSources, true);
            if (m.load()) {
                m.printDependencies(sNexIntent);
            }
        }
        
    }
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::verify() {
    std::vector<std::string> m_vVerified;

    // HERE verify current package
    
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        if (m_bHolded) {
            WSJCppPackageManager m(m_sParentDir + "/" + it->getName(), m_sParentDir, true);
            if (m.load()) {
                m.verify();
            }
        } else {
            WSJCppPackageManager m(m_sDirWithSources + "/" + it->getName(), m_sDirWithSources, true);
            if (m.load()) {
                m.verify();
            }
        }
        
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::install(const std::string &sPackage) {
    if (m_bHolded) {
        WSJCppLog::err(TAG, "Could not install package when holded");
        return false;
    }

    if (isGitHubPackage(sPackage)) {
        if (isInstalled(sPackage)) {
            WSJCppLog::err(TAG, "Package '" + sPackage + "' already installed");
            return false;
        }
        WSJCppPackageManagerDependence dep;
        if (downloadFromGithubToCache(sPackage, dep)) {
            addDependency(dep);
            return installFromCache(sPackage, dep);
        } else {
            return false;
        }
    } else if (isBitbucketPackage(sPackage)) {
        // TODO
        WSJCppLog::err(TAG, "Could not install package from bitbucket - not implemented yet");
        return false;
    } else if (isFilePackage(sPackage)) {
        // TODO
        WSJCppLog::err(TAG, "Could not install package from file - not implemented yet");
        return false;
    } else if (isHttpPackage(sPackage) || isHttpsPackage(sPackage)) {
        // TODO try find on different servers
        WSJCppLog::err(TAG, "Could not install package from http(s) - not implemented yet");
        return false;
    }

    WSJCppLog::err(TAG, "Could not install package from unknown source");
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::reinstall(const std::string &sPackage) {
    if (m_bHolded) { // readonly
        return false;
    }

    if (m_bHolded) {
        WSJCppLog::err(TAG, "Could not install package when holded");
        return false;
    }

    if (isGitHubPackage(sPackage)) {
        if (!isInstalled(sPackage)) {
            WSJCppLog::err(TAG, "Package '" + sPackage + "' not installed");
            return false;
        }

        WSJCppPackageManagerDependence dep;
        if (downloadFromGithubToCache(sPackage, dep)) {
            updateDependency(dep);
            return installFromCache(sPackage, dep);
        } else {
            return false;
        }
    } else if (isBitbucketPackage(sPackage)) {
        // TODO
        WSJCppLog::err(TAG, "Could not reinstall package from bitbucket - not implemented yet");
        return false;
    } else if (isFilePackage(sPackage)) {
        // TODO
        WSJCppLog::err(TAG, "Could not reinstall package from file - not implemented yet");
        return false;
    } else if (isHttpPackage(sPackage) || isHttpsPackage(sPackage)) {
        // TODO try find on different servers
        WSJCppLog::err(TAG, "Could not reinstall package from http(s) - not implemented yet");
        return false;
    }

    WSJCppLog::err(TAG, "Could not install package from unknown source");
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::uninstall(const std::string &sPackageUrl) {
    WSJCppLog::err(TAG, "uninstall Not inplemented");
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isGitHubPackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sGithubPrefix.size(), m_sGithubPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isBitbucketPackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sBitbucketPrefix.size(), m_sBitbucketPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isFilePackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sFilePrefix.size(), m_sFilePrefix) == 0;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isHttpPackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sHttpPrefix.size(), m_sHttpPrefix) == 0;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isHttpsPackage(const std::string &sPackage) {
    return sPackage.compare(0, m_sHttpsPrefix.size(), m_sHttpsPrefix) == 0;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::addDependency(WSJCppPackageManagerDependence &dep) {
    m_vDependencies.push_back(dep);
    WSJCppYAMLItem *pDeps = m_yamlPackageInfo.getRoot()->getElement("dependencies");
    WSJCppYAMLPlaceInFile pl;
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(pDeps, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_MAP);
    // TODO add simplyfy method
    WSJCppYAMLItem *pItemName = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemName->setName("name", false);
    pItemName->setValue(dep.getName(), true);
    pItem->setElement("name", pItemName);
    WSJCppYAMLItem *pItemVersion = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemVersion->setName("version", false);
    pItemVersion->setValue(dep.getVersion(), true);
    pItem->setElement("version", pItemVersion);
    WSJCppYAMLItem *pItemURL = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemURL->setName("url", false);
    pItemURL->setValue(dep.getUrl(), true);
    pItem->setElement("url", pItemURL);
    WSJCppYAMLItem *pItemOrigin = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemOrigin->setName("origin", false);
    pItemOrigin->setValue(dep.getOrigin(), true);
    pItem->setElement("origin", pItemOrigin);
    WSJCppYAMLItem *pItemInstallationDir = new WSJCppYAMLItem(pItem, pl, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItemInstallationDir->setName("installation-dir", false);
    pItemInstallationDir->setValue(dep.getInstallationDir(), true);
    pItem->setElement("installation-dir", pItemInstallationDir);
    pDeps->appendElement(pItem);
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::updateDependency(WSJCppPackageManagerDependence &dep) {
    WSJCppYAMLItem *pDeps = m_yamlPackageInfo.getRoot()->getElement("dependencies");
    int nLen = pDeps->getLength();
    for (int i = 0; i < nLen; i++) {
        WSJCppYAMLItem *pItem = pDeps->getElement(i);
        std::string sUrl = pItem->getElement("url")->getValue();
        if (dep.getUrl() == sUrl) {
            pItem->getElement("version")->setValue(dep.getVersion(), true);
            pItem->getElement("name")->setValue(dep.getName(), true);
            // pItem->getElement("url")->setValue(dep.getUrl(), true);
            pItem->getElement("origin")->setValue(dep.getOrigin(), true);
            pItem->getElement("installation-dir")->setValue(dep.getInstallationDir(), true);
        }
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::downloadFromGithubToCache(const std::string &sPackage, WSJCppPackageManagerDependence &dep) {

    std::cout << "Download package from https://github.com/ ..." << std::endl;

    std::string sPackageGithubPath = sPackage.substr(m_sGithubPrefix.size());
    // std::cout << "sPackageGithubPath: " << sPackageGithubPath << std::endl;
    std::istringstream f(sPackageGithubPath);
    std::string packageName = "";
    std::string s;
    if (getline(f, s, ':')) {
        packageName = s;
    }
    std::string packageVersion = sPackageGithubPath.substr(packageName.size()+1);
    std::string sWsjcppBaseUrl = "https://raw.githubusercontent.com/" + packageName + "/" + packageVersion + "/";

    std::string sWsjcppUrl = sWsjcppBaseUrl + "/wsjcpp.yml";
    std::string sCacheDir = m_sDir + "/.wsjcpp-cache";
    if (!WSJCppCore::dirExists(sCacheDir)) {
        WSJCppCore::makeDir(sCacheDir);
    }

    std::string sCacheSubFolderName = sCacheDir + "/" + this->prepareCacheSubFolderName(sPackage);

    if (!WSJCppCore::dirExists(sCacheSubFolderName)) {
        WSJCppCore::makeDir(sCacheSubFolderName);
    }

    std::string sDownloadedWsjCppYml = sCacheSubFolderName + "/wsjcpp.hold.yml";

    if (!this->downloadFileOverHttps(sWsjcppBaseUrl + "/wsjcpp.yml", sDownloadedWsjCppYml)) {
        WSJCppLog::err(TAG, "Could not download " + sWsjcppBaseUrl);
        // TODO remove from cache
        return false;
    }

    WSJCppPackageManager pkg(sCacheSubFolderName, sCacheSubFolderName, true);
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load " + sCacheSubFolderName);
        return false;
    }

    // sources
    std::vector<WSJCppPackageManagerDistributionFile> vSources = pkg.getListOfDistributionFiles();
    for (int i = 0; i < vSources.size(); i++) {
        WSJCppPackageManagerDistributionFile src = vSources[i];
        std::string sDownloadedWsjCppSourceFrom = sWsjcppBaseUrl + "/" + src.getSourceFile();
        std::string sDownloadedWsjCppSourceTo = sCacheSubFolderName + "/" + src.getTargetFile();

        WSJCppLog::info(TAG, "\n\t" + sDownloadedWsjCppSourceFrom + " \n\t-> \n\t" + sDownloadedWsjCppSourceTo + "\n\t[sha1:" + src.getSha1() + "]");
        if (!this->downloadFileOverHttps(sDownloadedWsjCppSourceFrom, sDownloadedWsjCppSourceTo)) {
            WSJCppLog::err(TAG, "Could not download " + sDownloadedWsjCppSourceFrom);
            // TODO remove from cache
            return false;
        }
        std::string sContent = "";
        if (!WSJCppCore::readTextFile(sDownloadedWsjCppSourceTo, sContent)) {
            WSJCppLog::err(TAG, "Could not read file " + sDownloadedWsjCppSourceTo);
            return false;
        }
        // calculate sha1
        std::string sSha1 = WSJCppHashes::sha1_calc_hex(sContent);
        if (sSha1 != src.getSha1()) {
            WSJCppLog::warn(TAG, "Expected sha1 '" + sSha1 + "', but got '" + src.getSha1() + "'");
        }
    }

    std::string sInstallationDir = "./src.wsjcpp/" + this->prepareCacheSubFolderName(pkg.getName());

    // WSJCppPackageManagerDependence dep;
    dep.setName(pkg.getName());
    dep.setVersion(pkg.getVersion());
    dep.setUrl(sPackage);
    dep.setInstallationDir(sInstallationDir);
    dep.setOrigin("https://github.com/");
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::isInstalled(const std::string &sPackage) {
    // todo check in current dependencies
    for (int i = 0; i < m_vDependencies.size(); i++) {
        WSJCppPackageManagerDependence dep = m_vDependencies[i];
        if (dep.getUrl() == sPackage) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::installFromCache(const std::string &sPackage, const WSJCppPackageManagerDependence &dep) {
    std::string sInstallationDir = dep.getInstallationDir();
    // TODO check path
    if (!WSJCppCore::dirExists(sInstallationDir)) {
        WSJCppCore::makeDir(sInstallationDir);
    }
    
    std::string sCacheDir = m_sDir + "/.wsjcpp-cache"; // TODO sCacheDir must be init close with init m_sDir
    std::string sCacheSubFolderName = sCacheDir + "/" + this->prepareCacheSubFolderName(sPackage);

    // TODO redesign to WSJCppCore::recoursiveCopyFiles
    // copy sources to installation dir
    std::vector<std::string> vFiles = WSJCppCore::listOfFiles(sCacheSubFolderName);
    for (int i = 0; i < vFiles.size(); i++) {
        std::string sFrom = sCacheSubFolderName + "/" + vFiles[i];
        std::string sTo = sInstallationDir + "/" + vFiles[i];
        std::string sContent = "";
        if (!WSJCppCore::readTextFile(sFrom, sContent)) {
            WSJCppLog::err(TAG, "Could not read file " + sFrom);
            return false;
        }
        if (!WSJCppCore::writeFile(sTo, sContent)) {
            WSJCppLog::err(TAG, "Could not write to file '" + sTo + "'");
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printInfo() {
    
    std::cout << std::endl 
        << "===== begin: wsjcpp info =====" << std::endl
        << "Name: " << m_sName << std::endl
        << "Version: " << m_sVersion << std::endl
        << "Description: " << m_sDescription
        << std::endl;
    if (m_bHolded) {
        std::cout << "Package is holded" << std::endl;
    }
    std::cout << "Directory: " << m_sDir << std::endl;
    std::cout << "wsjcpp.version = " << m_sWSJCppVersion << std::endl;
    // print keywords
    std::cout << "Keywords: " << std::endl;
    for (unsigned int i = 0; i < m_vKeywords.size(); i++) {
        std::cout << " - " << m_vKeywords[i] << std::endl;
    }
    if (m_vDistributionFiles.size() > 0) {
        std::cout << std::endl << "Distribution-Files: " << std::endl;
        for (unsigned int i = 0; i < m_vDistributionFiles.size(); i++) {
            WSJCppPackageManagerDistributionFile source = m_vDistributionFiles[i];
            std::cout << " - " << source.getSourceFile() << " -> " << source.getTargetFile() << " [sha1:" << source.getSha1() << "]" << std::endl;
        }
    }
    
    // TODO: print authors
    // TODO: print deps

    std::cout << "===== end: wsjcpp info =====" << std::endl
        << std::endl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printPackages() {
    std::cout << "Dependencies: " << std::endl;
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        std::cout << " - " << it->getName() << ":" << it->getVersion() << "    (" << it->getUrl() << " -> " << it->getInstallationDir() << ")" << std::endl;
    }
    std::cout << std::endl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printAuthors() {
    std::cout << "Authors (" << m_sName << ":" << m_sVersion << "): " << std::endl;
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WSJCppPackageManagerAuthor author = m_vAuthors[i];
        std::cout << " - " << author.getFullAuthor() << std::endl;
    }
    std::cout << std::endl;
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::printAuthorsTree() {
    std::string sAuthors = "";
    for (int i = 0; i < m_vAuthors.size(); i++) {
        if (sAuthors.size() > 0) {
            sAuthors += ", ";
        }
        sAuthors += m_vAuthors[i].getFullAuthor();
    }
    std::cout << "Authors (" << m_sName << ":" << m_sVersion << "): " << sAuthors << std::endl;

    // TODO
    recursive_printAuthorsTree(m_vDependencies);
}

// ---------------------------------------------------------------------

void WSJCppPackageManager::recursive_printAuthorsTree(std::vector<WSJCppPackageManagerDependence> &vDependencies) {
    for (int i = 0; i < vDependencies.size(); i++) {
        WSJCppPackageManagerDependence dep = vDependencies[i];
        std::string sInstalledDir = dep.getInstallationDir(); 

        if (WSJCppCore::dirExists(dep.getInstallationDir())) {
            WSJCppPackageManager subpkg(sInstalledDir, m_sDir, true);
            WSJCppLog::info(TAG, "Loading package '" + sInstalledDir + "'");
            if (subpkg.load()) {
                subpkg.printAuthorsTree();
            } else {
                WSJCppLog::err(TAG, "Could not load package.");
            }
        } else {
            WSJCppLog::err(TAG, "Not found installed dir: '" + sInstalledDir + "' for package: " + dep.getName() + ":" + dep.getVersion());
        }
    }
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::addAuthor(const std::string &sName, const std::string &sEmail) {
    bool bFoundAuthor = false;
    std::string sFullAuthor = sName + " <" + sEmail + ">";
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WSJCppPackageManagerAuthor author = m_vAuthors[i];
        if (author.getFullAuthor() == sFullAuthor) {
            bFoundAuthor = true;
        }
    }
    if (bFoundAuthor) {
        WSJCppLog::err(TAG, "Author already exists");
        return false;
    }

    WSJCppPackageManagerAuthor newAuthor(sName, sEmail);
    m_vAuthors.push_back(newAuthor);
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::removeAuthor(const std::string &sFullAuthor) {
    std::vector<WSJCppPackageManagerAuthor> vNewAuthors;
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WSJCppPackageManagerAuthor author = m_vAuthors[i];
        if (author.getFullAuthor() != sFullAuthor) {
            vNewAuthors.push_back(author);
        }
    }
    if (vNewAuthors.size() != m_vAuthors.size()) {
        m_vAuthors.clear();
        for (int i = 0; i < vNewAuthors.size(); i++) {
            m_vAuthors.push_back(vNewAuthors[i]);
        }
        return true;
    }
    WSJCppLog::err(TAG, "Not found this author");
    return false;
}

// ---------------------------------------------------------------------

std::vector<WSJCppPackageManagerDistributionFile> WSJCppPackageManager::getListOfDistributionFiles() {
    return m_vDistributionFiles;
}

// ---------------------------------------------------------------------

std::vector<WSJCppPackageManagerDependence> WSJCppPackageManager::getListOfDependencies() {
    return m_vDependencies;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManager::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManager::getVersion() {
    return m_sVersion;
}

// ---------------------------------------------------------------------

std::string WSJCppPackageManager::prepareCacheSubFolderName(const std::string &sPackage) {
    std::string ret = sPackage;
    std::string illegalChars = "\\/:?\"<>|.-";
    std::string::iterator it;
    for (it = ret.begin(); it < ret.end() ; ++it) {
        if (illegalChars.find(*it) != std::string::npos) {
            *it = '_';
        }
    }
    return ret;
}

// ---------------------------------------------------------------------

size_t CurlWrite_CallbackFunc_DataToFile(void *ptr, size_t size, size_t nmemb, FILE *stream) { 
    size_t written = fwrite(ptr, size, nmemb, stream); 
    return written; 
}

bool WSJCppPackageManager::downloadFileOverHttps(const std::string &sUrl, const std::string &sPath) {
    WSJCppLog::info(TAG, "sUrl: '" + sUrl + "'");
    WSJCppLog::info(TAG, "sPath: '" + sPath + "'");
    std::string sUserAgent = "wsjcpp/" + m_sWSJCppCurrentVersion;
    CURL *curl;
    FILE *fp = fopen(sPath.c_str(),"wb"); 
    if (fp == NULL) { 
        WSJCppLog::err(TAG, "Could not open file for write '" + sPath + "'"); 
        return false;
    }

    CURLcode res;
    curl = curl_easy_init(); 
    if (curl) { 
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https
        curl_easy_setopt(curl, CURLOPT_URL, sUrl.c_str()); 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_DataToFile); 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, sUserAgent.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl); 
        if (res != CURLE_OK) {
            WSJCppLog::err(TAG, "Curl failed, reason  " + std::string(curl_easy_strerror(res))); 
            // TODO remove file
            curl_easy_cleanup(curl);
            return false;
        } else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code != 200) {
                WSJCppLog::info(TAG, "end " + std::to_string(response_code));
                // TODO remove file
                curl_easy_cleanup(curl);
                return false;
            }
        }

        // always cleanup
        curl_easy_cleanup(curl); 
        fclose(fp);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldVersion() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("version")) {
        WSJCppLog::err(TAG, "Missing required field 'version' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check version format
    m_sVersion = m_yamlPackageInfo["version"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldCMakeMinimumRequired() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("cmake_minimum_required")) {
        WSJCppLog::err(TAG, "Missing required field 'cmake_minimum_required' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check cmake_version format
    m_sCMakeMinimumRequired = m_yamlPackageInfo["cmake_minimum_required"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldCMakeCxxStandard() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("cmake_cxx_standard")) {
        WSJCppLog::err(TAG, "Missing required field 'cmake_cxx_standard' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check cmake_cxx_standard format
    m_sCMakeCxxStandard = m_yamlPackageInfo["cmake_cxx_standard"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldName() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("name")) {
        WSJCppLog::err(TAG, "Missing required field 'name' in " + m_yamlPackageInfo.getRoot()->getForLogFormat());
        return false;
    }
    // TODO: check name format
    m_sName = m_yamlPackageInfo["name"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldDescription() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("description")) {
        WSJCppLog::err(TAG, "Missing required field 'description' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sDescription = m_yamlPackageInfo["description"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldWsjcppVersion() {    
    if (!m_yamlPackageInfo.getRoot()->hasElement("wsjcpp_version")) {
        WSJCppLog::err(TAG, "Missing required field 'wsjcpp_version' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sWSJCppVersion = m_yamlPackageInfo["wsjcpp_version"].getValue();
    // TODO version comparator 
    // if (nWSJCppVersion > m_nWSJCppVersion) {
        //   std::cout << "WARN: Please update your 'wsjcpp' to " << nWSJCppVersion << std::endl;
    // }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldIssues() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("issues")) {
        WSJCppLog::err(TAG, "Missing required field 'issues' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sIssues = m_yamlPackageInfo["issues"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldKeywords() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("keywords")) {
        WSJCppLog::err(TAG, "Missing required field 'keywords' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemKeywords = m_yamlPackageInfo["keywords"];
    int nLength = itemKeywords.getLength();
    for (int i = 0; i < nLength; i++) {
        std::string sKeyword = itemKeywords[i].getValue();
        m_vKeywords.push_back(sKeyword);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldAuthors() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("authors")) {
        WSJCppLog::err(TAG, "Missing required field 'authors' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemAuthors = m_yamlPackageInfo["authors"];
    int nLength = itemAuthors.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlAuthor = itemAuthors.getElement(i);
        WSJCppPackageManagerAuthor author;
        author.fromYAML(pYamlAuthor);
        m_vAuthors.push_back(author);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldDistribution() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("distribution")) {
        WSJCppLog::err(TAG, "Missing required field 'distribution' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemDistribution = m_yamlPackageInfo["distribution"];
    int nLength = itemDistribution.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlSource = itemDistribution.getElement(i);
        WSJCppPackageManagerDistributionFile source;
        source.fromYAML(pYamlSource);
        m_vDistributionFiles.push_back(source);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldServers() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("servers")) {
        WSJCppLog::err(TAG, "Missing required field 'servers' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemServers = m_yamlPackageInfo["servers"];
    int nLength = itemServers.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlServer = itemServers.getElement(i);
        WSJCppPackageManagerServer server;
        server.fromYAML(pYamlServer);
        m_vServers.push_back(server);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldDependencies() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("dependencies")) {
        WSJCppLog::err(TAG, "Missing required field 'dependencies' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemDependencies = m_yamlPackageInfo["dependencies"];
    int nLength = itemDependencies.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlDependence = itemDependencies.getElement(i);
        WSJCppPackageManagerDependence dependence;
        dependence.fromYAML(pYamlDependence);
        m_vDependencies.push_back(dependence);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldRepositories() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("repositories")) {
        WSJCppLog::err(TAG, "Missing required field 'repositories' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemRepositories = m_yamlPackageInfo["repositories"];
    int nLength = itemRepositories.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlRepository = itemRepositories.getElement(i);
        WSJCppPackageManagerRepository repository;
        repository.fromYAML(pYamlRepository);
        m_vRepositories.push_back(repository);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppPackageManager::readFieldRequiredLibraries() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("required-libraries")) {
        WSJCppLog::err(TAG, "Missing required field 'required-libraries' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WSJCppYAMLItem itemRepositories = m_yamlPackageInfo["required-libraries"];
    int nLength = itemRepositories.getLength();
    for (int i = 0; i < nLength; i++) {
        WSJCppYAMLItem *pYamlRequredLibrary = itemRepositories.getElement(i);
        std::string sRequiredLibrary = pYamlRequredLibrary->getValue();
        m_sRequiredLibraries.push_back(sRequiredLibrary);
    }
    return true;
}

// ---------------------------------------------------------------------