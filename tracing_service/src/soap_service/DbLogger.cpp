#include <soap_service/DbLogger.h>
#include <soap_service/DataAccessException.h>

#include <sqlite3/sqlite3.h>

#include <iostream>

using namespace std;

namespace ImTrcr {
namespace SoapService {

    DbLogger::DbLogger(const string& dbPath)
        : dbPath(dbPath) {}

    void DbLogger::LogMessage(const string& msg) const {
        sqlite3* pDb = NULL;

        int openResult = sqlite3_open(dbPath.c_str(), &pDb);
        
        if (openResult != SQLITE_OK) {
            cout << "openResult != SQLITE_OK" << endl;
            return;
        }

        string statementText =
           "INSERT INTO events \
            (time, description) \
            VALUES \
            (datetime('now'), '" + msg + "')";

        sqlite3_stmt* pStmt;

        int prepareResult = sqlite3_prepare_v2(pDb, statementText.c_str(), statementText.size() + 1, &pStmt, NULL);

        if (prepareResult != SQLITE_OK) {
            cout << "prepareResult != SQLITE_OK" << endl;
            sqlite3_close(pDb);
            return;
        }
        
        sqlite3_step(pStmt);

        sqlite3_finalize(pStmt);
        sqlite3_close(pDb);
    }

}
}
