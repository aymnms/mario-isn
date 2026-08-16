#include "domain/level.h"

static domain_level_parse_result_t fail(domain_level_status_t status, int end_offset) {
    domain_level_parse_result_t r;
    r.status = status;
    r.end_offset = end_offset;
    r.trailer_valid = 0;
    return r;
}

domain_level_parse_result_t domain_parse_level(const char *data, int data_len, char level_digit, int rows,
                                                int cols, char *out_grid) {
    int pos = 0;

    for (;;) {
        for (;;) {
            if (pos >= data_len) {
                return fail(DOMAIN_LEVEL_MARKER_NOT_FOUND, pos);
            }
            char c = data[pos++];
            if (c == '#') {
                break;
            }
        }
        if (pos >= data_len) {
            return fail(DOMAIN_LEVEL_MARKER_NOT_FOUND, pos);
        }
        char marker_digit = data[pos++];
        if (marker_digit == level_digit) {
            break;
        }
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (pos >= data_len) {
                return fail(DOMAIN_LEVEL_UNEXPECTED_END, pos);
            }
            char c = data[pos++];
            if (c == '\n') {
                if (pos >= data_len) {
                    return fail(DOMAIN_LEVEL_UNEXPECTED_END, pos);
                }
                c = data[pos++];
            }
            out_grid[row * cols + col] = c;
        }
    }

    domain_level_parse_result_t r;
    r.status = DOMAIN_LEVEL_OK;
    r.trailer_valid = 0;
    if (pos < data_len) {
        pos++; /* first trailer byte, unconditionally consumed and never checked -- mirrors the original */
    }
    if (pos < data_len) {
        r.trailer_valid = data[pos] == '@';
        pos++;
    }
    r.end_offset = pos;
    return r;
}
