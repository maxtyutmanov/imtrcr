#include <soap_service/DbLogger.h>

using namespace std;

namespace ImTrcr {
namespace SoapService {

    DbLogger::DbLogger(const string& dbPath)
        : dbPath(dbPath) {}

    void DbLogger::LogMessage(const string& msg) const {
        //TODO: implementation
    }

}
}