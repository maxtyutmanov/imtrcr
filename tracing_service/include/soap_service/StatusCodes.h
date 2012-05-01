#pragma once

struct StatusCodes {
    static const char OK[];
    static const char DECODING_ERROR[];
    static const char WRONG_FORMAT_ERROR[];
    static const char TRACING_ERROR[];
};
const char StatusCodes::OK[] = "0";
const char StatusCodes::DECODING_ERROR[] = "1";
const char StatusCodes::WRONG_FORMAT_ERROR[] = "2";
const char StatusCodes::TRACING_ERROR[] = "3";