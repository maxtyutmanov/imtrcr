#ifndef SOAP_SERVICE_STATUS_CODES_H
#define SOAP_SERVICE_STATUS_CODES_H

struct StatusCodes {
    static const char OK[];
    static const char DECODING_ERROR[];
    static const char WRONG_FORMAT_ERROR[];
    static const char TRACING_ERROR[];
    static const char UNKNOWN_ERROR[];
};

#endif