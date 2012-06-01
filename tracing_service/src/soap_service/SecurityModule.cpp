#include <soap_service/SecurityModule.h>
#include <soap_service/DataAccessException.h>

#include <sqlite3/sqlite3.h>

using namespace std;

namespace ImTrcr {
namespace SoapService {

    SecurityModule::SecurityModule(const string& dbPath)
        : dbPath(dbPath) {}

    bool SecurityModule::CheckSystemID(const string& systemID) const {

        sqlite3* pDb = NULL;

        int openResult = sqlite3_open(dbPath.c_str(), &pDb);
        
        if (openResult != SQLITE_OK) {
            throw DataAccessException("Cannot open users database");
        }

        string statementText =
           "SELECT * \
            FROM \
                external_systems \
            WHERE \
                authToken = '" + systemID + "'";

        sqlite3_stmt* pStmt;

        int prepareResult = sqlite3_prepare_v2(pDb, statementText.c_str(), statementText.size() + 1, &pStmt, NULL);

        if (prepareResult != SQLITE_OK) {
            throw DataAccessException("Error while preparing SQL statement");
        }

        bool found = false;
        int stepResult;

        if ((stepResult = sqlite3_step(pStmt)) == SQLITE_ROW) {
            found = true;
        }

        sqlite3_finalize(pStmt);
        sqlite3_close(pDb);

        return found;
    }

}
}