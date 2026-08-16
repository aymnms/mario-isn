#ifndef DOMAIN_LEVEL_H
#define DOMAIN_LEVEL_H

typedef enum {
    DOMAIN_LEVEL_OK,
    DOMAIN_LEVEL_MARKER_NOT_FOUND,  /* no `#<level_digit>` marker anywhere in data */
    DOMAIN_LEVEL_UNEXPECTED_END     /* marker found, but data ran out while reading the grid */
} domain_level_status_t;

typedef struct {
    domain_level_status_t status;
    int end_offset;    /* bytes of `data` consumed -- up to the failure point on
                         * error, or through the trailer on success. Lets the
                         * caller echo exactly the prefix niveau.lvl's original
                         * fgetc()-driven reader used to print character by
                         * character. */
    int trailer_valid; /* only meaningful when status == DOMAIN_LEVEL_OK: whether
                         * the 2nd byte right after the grid was '@', as the
                         * niveau.lvl format expects. A bad trailer doesn't fail
                         * the parse (out_grid is still valid) -- mirrors the
                         * original, which only printed a warning for this. */
} domain_level_parse_result_t;

/* Parses one level block out of `data` (`data_len` bytes: the full contents
 * of niveau.lvl), searching for a `#<level_digit>` marker from the very
 * start of `data` -- mirrors the original niveauSelect(), which re-opened
 * and re-scanned the file from byte 0 on every call rather than remembering
 * a position. After the marker, reads `rows*cols` grid characters into
 * `out_grid` (caller-owned, row-major, `rows*cols` bytes) row by row; a '\n'
 * encountered where a grid character is expected is skipped by reading one
 * further byte in its place (mirrors the level file's line-wrapped rows).
 * Finally consumes 2 trailer bytes, expecting the 2nd to be '@'.
 *
 * `out_grid` is only written to when the return status is
 * DOMAIN_LEVEL_OK. */
domain_level_parse_result_t domain_parse_level(const char *data, int data_len, char level_digit, int rows,
                                                int cols, char *out_grid);

#endif
