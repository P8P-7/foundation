#include "console.h"

#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <boost/core/null_deleter.hpp>

#include "foundation_utilities.h"

using namespace goliath::util;

Console::Console(std::function<void(const boost::log::record_view&, boost::log::formatting_ostream&)> formatter,
                 std::string executableLocation, std::string projectTextFile)
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
    BOOST_LOG_TRIVIAL(fatal) << "Controller has been shut down";
    for (int i = 0; i < 57; ++i) {
        std::cout << "─";
    }

    std::cout << "┴";

    for (int i = 0; i < 57; ++i) {
        std::cout << "─";
    }
}

std::string goliath::util::getColor(const boost::log::trivial::severity_level& severityLevel) {
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

void goliath::util::colorConsoleFormatter(const boost::log::record_view& recordView, boost::log::formatting_ostream& formatStream) {
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
        formatStream << getColor(severity.get());
    } else {
        formatStream << "├ ";
    }

    formatStream << recordView[boost::log::expressions::smessage];

    if (severity) {
        formatStream << LOG_COLOR_DEFAULT << CONSOLE_STYLE_RESET;
    }
}
