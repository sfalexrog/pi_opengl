#include <string>
#include <sstream>
#include <chrono>

namespace Util
{

class Logger
{
private:
    std::stringstream ss;

public:
    enum Severity
    {
        S_TRACE = 0,
        S_DEBUG,
        S_INFO,
        S_WARNING,
        S_ERROR,
        S_FATAL
    };

private:
    Severity severity;

    const char* sevStr()
    {
        switch(severity)
        {
            case S_TRACE:
                return "[TRACE]";
            case S_DEBUG:
                return "[DEBUG]";
            case S_INFO:
                return "[INFO]";
            case S_WARNING:
                return "[WARNING]";
            case S_ERROR:
                return "[ERROR]";
            case S_FATAL:
                return "[FATAL]";
        }
    }

    std::chrono::time_point<std::chrono::system_clock> timestamp;

public:
    Logger(Severity s) : severity(s), timestamp(std::chrono::system_clock::now()) {}
    ~Logger();

    std::stringstream& get() {return ss;}

    static Severity& minSeverity() {static Severity minSev = S_DEBUG; return minSev;}

};

}

#define Log(SEVERITY) if (Util::Logger::minSeverity() > Util::Logger::Severity::SEVERITY) {} else Util::Logger(Util::Logger::Severity::SEVERITY).get() << "(" << __FILE__ << "@" << __LINE__ << ") "
#define LogAssert(EXPRESSION) if (!(EXPRESSION)) {Log(S_FATAL) << "Assertion " << #EXPRESSION << " failed"; }
