#include "logger.h"
#include <iostream>
#include <iomanip>
#include <execinfo.h>


namespace Util
{

namespace
{
    auto startTimestamp = std::chrono::system_clock::now();

    class StreamPrefsReturner
    {
    private:
        std::ostream& stream;

        std::ios_base::fmtflags flags;
        std::streamsize prec;
        std::streamsize width;
    public:
        StreamPrefsReturner(std::ostream& str) : stream(str)
        {
            flags = stream.flags();
            prec = stream.precision();
            width = stream.width();
        }
        ~StreamPrefsReturner()
        {
            stream.flags(flags);
            stream.precision(prec);
            stream.width(width);
        }
    };
}


Logger::~Logger()
{
    // TODO: feed into a proper log
    std::chrono::duration<double> relTimestamp = timestamp - startTimestamp;
    if (severity < Severity::S_ERROR)
    {
        StreamPrefsReturner ret(std::cout);
        std::cout << "[" << std::fixed << std::setw(14)
                  << std::setprecision(6) << relTimestamp.count()
                  << "] " << sevStr() << " " << ss.str()
                  << std::endl;
    }
    else
    {
        StreamPrefsReturner ret(std::cerr);
        std::cerr << "[" << std::fixed << std::setw(14)
                  << std::setprecision(6) << relTimestamp.count()
                  << "] " << sevStr() << " " << ss.str()
                  << std::endl;
    }

    if (severity == Severity::S_FATAL)
    {
        std::cerr << "Stack trace: " << std::endl;
        const int MAX_NUM_FRAMES = 1000;
        void *buffer[MAX_NUM_FRAMES];
        char **strings;
        int numFrames = backtrace(buffer, MAX_NUM_FRAMES);
        strings = backtrace_symbols(buffer, numFrames);
        if (!strings)
        {
            std::cerr << "Could not get stack trace!" << std::endl;
        }
        else
        {
            for(int i = 0; i < numFrames; ++i)
            {
                std::cerr << "[ " << i << "]" << strings[i] << std::endl;
            }
            free(strings);
        }
        exit(1);
    }
}

}