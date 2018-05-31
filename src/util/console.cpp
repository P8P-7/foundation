#include <goliath/foundation/util/console.h>
#include <goliath/foundation/util/foundation_utilities.h>

#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <boost/core/null_deleter.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/core.hpp>
#include <boost/algorithm/string.hpp>

using namespace goliath::util;

Console::Console(std::function<void(const boost::log::record_view &, boost::log::formatting_ostream &)> formatter,
                 std::string executableLocation, std::string projectTextFile,
                 boost::log::trivial::severity_level severityLevel = boost::log::trivial::severity_level::info)
        : formatter(formatter) {

    std::string logoLine;
    std::ifstream logo(FoundationUtilities::executableToFile(executableLocation, "logo.txt"));
    std::string organizationLine;
    std::ifstream organizationText(FoundationUtilities::executableToFile(executableLocation, "organization_name.txt"));
    std::string projectLine;
    std::ifstream projectText;

    bool hasProjectText = !projectTextFile.empty();
    if (hasProjectText) {
        projectText.open(FoundationUtilities::executableToFile(executableLocation, projectTextFile));
        hasProjectText = projectText.is_open();
    }

    if (logo.is_open()) {
        while (std::getline(logo, logoLine)) {
            if (std::getline(organizationText, organizationLine)) {
                std::cout << logoLine << organizationLine << std::endl;
            } else if (std::getline(projectText, projectLine)) {
                std::cout << logoLine << projectLine << std::endl;
            } else {
                std::cout << logoLine << std::endl;
            }
        }
        logo.close();
        organizationText.close();

        if (hasProjectText) {
            projectText.close();
        }
    }

    auto sink = boost::make_shared<boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend>>();
    sink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::cout, boost::null_deleter()));

    sink->set_formatter(this->formatter);
    sink->set_filter(boost::log::trivial::severity >= severityLevel);

    boost::log::core::get()->add_sink(sink);

    for (int i = 0; i < 57; ++i) {
        std::cout << "─";
    }

    std::cout << "┬";

    for (int i = 0; i < 57; ++i) {
        std::cout << "─";
    }

    std::cout << std::endl;
}

Console::~Console() {
    for (int i = 0; i < 57; ++i) {
        std::cout << "─";
    }

    std::cout << "┴";

    for (int i = 0; i < 57; ++i) {
        std::cout << "─";
    }
}

boost::log::trivial::severity_level goliath::util::parseSeverityLevel(const std::string &input,
                                                                      boost::log::trivial::severity_level defaultSeverity) {
    if (input.empty()) {
        return defaultSeverity;
    }

    const std::string value = boost::algorithm::to_lower_copy(input);

    if (value == "trace" || value[0] == 't') {
        return boost::log::trivial::trace;
    }
    if (value == "debug" || value[0] == 'd') {
        return boost::log::trivial::debug;
    }
    if (value == "info" || value[0] == 'i') {
        return boost::log::trivial::info;
    }
    if (value == "warning" || value[0] == 'w') {
        return boost::log::trivial::warning;
    }
    if (value == "error" || value[0] == 'e') {
        return boost::log::trivial::error;
    }
    if (value == "fatal" || value[0] == 'f') {
        return boost::log::trivial::fatal;
    }


    return defaultSeverity;
}

std::string goliath::util::getColor(const boost::log::trivial::severity_level &severityLevel) {
    switch (severityLevel) {
        case boost::log::trivial::trace:
            return LOG_COLOR_TRACE;
        case boost::log::trivial::debug:
            return LOG_COLOR_DEBUG;
        case boost::log::trivial::info:
            return LOG_COLOR_INFO;
        case boost::log::trivial::warning:
            return LOG_COLOR_WARNING;
        case boost::log::trivial::error:
            return LOG_COLOR_ERROR;
        case boost::log::trivial::fatal:
            return LOG_COLOR_FATAL;
        default:
            return LOG_COLOR_DEFAULT;
    }
}

void goliath::util::colorConsoleFormatter(const boost::log::record_view &recordView,
                                          boost::log::formatting_ostream &formatStream) {
    auto now = std::chrono::high_resolution_clock::now();
    auto mil = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto mic = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000;
    auto nowC = std::chrono::high_resolution_clock::to_time_t(now);

    std::stringstream timeStream;
    timeStream << std::put_time(std::localtime(&nowC), "%F %T") << ':' << mil.count() << ':' << mic.count();

    formatStream << '[' << CONSOLE_COLOR_GREEN << std::left << std::setw(27) << timeStream.str() << LOG_COLOR_DEFAULT
                 << "] ";
    formatStream << '<' << CONSOLE_COLOR_CYAN << std::this_thread::get_id() << LOG_COLOR_DEFAULT << "> ";

    auto severity = recordView.attribute_values()["Severity"].extract<boost::log::trivial::severity_level>();
    if (severity) {
        std::stringstream severityStream;
        severityStream << '(' << severity << ')';

        formatStream << std::left << std::setw(9) << severityStream.str() << "├ ";
        formatStream << goliath::util::getColor(severity.get());
    } else {
        formatStream << "├ ";
    }

    formatStream << recordView[boost::log::expressions::smessage];

    if (severity) {
        formatStream << LOG_COLOR_DEFAULT << CONSOLE_STYLE_RESET;
    }
}
