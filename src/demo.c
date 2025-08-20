#include "picotui.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* A trivial bottom UI: two lines with status. */
static void render_ui(pico_t *ui, void *ud) {
    (void)ud;

    pico_reset_colors(ui); // Better to do it

    /* Line 0: title */
    pico_ui_clear_line(ui, 0);
    pico_ui_puts(ui, 0, 0, "[libpicotui] bottom UI region (no alt-screen)");

    /* Line 1: dynamic time + terminal size */
    time_t now = time(NULL);
    struct tm tm;
    localtime_r(&now, &tm);
    int cols = pico_cols(ui);

    pico_ui_clear_line(ui, 1);
    pico_ui_printf(ui, 1, 0, "cols=%d | %04d-%02d-%02d %02d:%02d:%02d", cols,
                   tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
                   tm.tm_min, tm.tm_sec);
}

int main(void) {
    pico_t *ui = pico_init(3, render_ui, NULL);
    if (!ui)
        return 1;

    pico_attach(ui);
    pico_install_sigint_handler(ui);

    for (int i = 1; i <= 30; ++i) {
        pico_set_colors(ui, PICO_COLOR_BLUE, -1);
        pico_printfln(ui, "Log line %d: streaming above the UI...", i);
        usleep(200 * 1000); /* 200ms between lines */
    }

    pico_shutdown(ui);
    pico_free(ui);
    return 0;
}
