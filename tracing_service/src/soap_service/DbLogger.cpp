#include <soap_service/DbLogger.h>
#include <soap_service/DataAccessException.h>

#include <sqlite3/sqlite3.h>

using namespace std;

namespace ImTrcr {
namespace SoapService {

    DbLogger::DbLogger(const string& dbPath)
        : dbPath(dbPath) {}

    void DbLogger::LogMessage(const string& msg) const {
        sqlite3* pDb = NULL;

        int openResult = sqlite3_open(dbPath.c_str(), &pDb);
        
        if (openResult != SQLITE_OK) {
            return;
        }

        string statementText =
           "INSERT INTO events \
            (time, description) \
            VALUES \
            (date('now'), '" + msg + "')";

        sqlite3_stmt* pStmt;

        int prepareResult = sqlite3_prepare_v2(pDb, statementText.c_str(), statementText.size() + 1, &pStmt, NULL);

        if (prepareResult != SQLITE_OK) {
            sqlite3_close(pDb);
            return;
        }

        sqlite3_finalize(pStmt);
        sqlite3_close(pDb);
    }

}
}