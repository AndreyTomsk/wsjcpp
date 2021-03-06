#ifndef ARGUMENT_PROCESSOR_PREPARE_H
#define ARGUMENT_PROCESSOR_PREPARE_H

#include <wsjcpp_arguments.h>

class ArgumentProcessorPrepare : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorPrepare();

        virtual bool applyParameterArgument(const std::string &sProgramName, const std::string &sArgumentName, const std::string &sValue);
        virtual bool applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName);
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorPrepareTravis : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorPrepareTravis();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorPrepareHomebrew : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorPrepareHomebrew();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
};

class ArgumentProcessorPrepareDockerfile : public WsjcppArgumentProcessor {
    public:
        ArgumentProcessorPrepareDockerfile();
        virtual int exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams);
};

#endif // ARGUMENT_PROCESSOR_PREPARE_H
