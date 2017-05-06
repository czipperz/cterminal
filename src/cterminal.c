/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 Chris Gregory czipperz@gmail.com
 */

#include "cterminal.h"

#include <stdio.h>

/** First create functions to do the operations for WINDOWS / POSIX
 * and define out and err to the stdout and stderr streams of each
 * platform. **/

#ifdef _WIN32
#include <windows.h>

static void terminal_set_foreground(terminal_color color, HANDLE console) {
    CONSOLE_SCREEN_BUFFER_INFO console_info;
    WORD attributes;

    GetConsoleScreenBufferInfo(console, &console_info);

    attributes =
        console_info.wAttributes &
        ~(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    switch (color) {
    case terminal_red:
    case terminal_yellow:
    case terminal_magenta:
    case terminal_white:
        attributes |= FOREGROUND_RED;
    }
    switch (color) {
    case terminal_green:
    case terminal_yellow:
    case terminal_cyan:
    case terminal_white:
        attributes |= FOREGROUND_GREEN;
    }
    switch (color) {
    case terminal_blue:
    case terminal_cyan:
    case terminal_magenta:
    case terminal_white:
        attributes |= FOREGROUND_BLUE;
    }

    SetConsoleTextAttribute(console, attributes);
}

static void terminal_set_background(terminal_color color, HANDLE console) {
    CONSOLE_SCREEN_BUFFER_INFO console_info;
    WORD attributes;

    GetConsoleScreenBufferInfo(console, &console_info);

    attributes =
        console_info.wAttributes &
        ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

    switch (color) {
    case terminal_red:
    case terminal_yellow:
    case terminal_magenta:
    case terminal_white:
        attributes |= BACKGROUND_RED;
    }
    switch (color) {
    case terminal_green:
    case terminal_yellow:
    case terminal_cyan:
    case terminal_white:
        attributes |= BACKGROUND_GREEN;
    }
    switch (color) {
    case terminal_blue:
    case terminal_cyan:
    case terminal_magenta:
    case terminal_white:
        attributes |= BACKGROUND_BLUE;
    }

    SetConsoleTextAttribute(console, attributes);
}

static void terminal_set_bold(HANDLE console) {
    CONSOLE_SCREEN_BUFFER_INFO console_info;

    GetConsoleScreenBufferInfo(console, &console_info);

    SetConsoleTextAttribute(console, console_info.wAttributes |
                                         (FOREGROUND_INTENSITY |
                                          BACKGROUND_INTENSITY));
}

static void terminal_unset_bold(HANDLE console) {
    CONSOLE_SCREEN_BUFFER_INFO console_info;

    GetConsoleScreenBufferInfo(console, &console_info);

    SetConsoleTextAttribute(console, console_info.wAttributes &
                                         ~(FOREGROUND_INTENSITY |
                                           BACKGROUND_INTENSITY));
}

static void terminal_reset(HANDLE console) {
    CONSOLE_SCREEN_BUFFER_INFO console_info;

    GetConsoleScreenBufferInfo(console, &console_info);

    SetConsoleTextAttribute(console,
                            console_info.wAttributes &
                                ~(FOREGROUND_INTENSITY |
                                  BACKGROUND_INTENSITY |
                                  FOREGROUND_RED | FOREGROUND_BLUE |
                                  FOREGROUND_GREEN |
                                  BACKGROUND_RED | BACKGROUND_BLUE |
                                  BACKGROUND_GREEN));
}

#define out GetStdHandle(STD_OUTPUT_HANDLE)
#define err GetStdHandle(STD_ERROR_HANDLE)
#else

static void terminal_set_foreground(terminal_color color, FILE* f) {
    fprintf(f, "\033[%dm", 30 + color);
}

static void terminal_set_background(terminal_color color, FILE* f) {
    fprintf(f, "\033[%dm", 40 + color);
}

static void terminal_set_bold(FILE* f) {
    fputs("\033[1m", f);
}

static void terminal_unset_bold(FILE* f) {
    fputs("\033[22m", f);
}

static void terminal_reset(FILE* f) {
    fputs("\033[0m", f);
}

#define out stdout
#define err stderr
#endif

/** Then create functions that wrap them generically. **/

void terminal_stderr_set_foreground(terminal_color color) {
    terminal_set_foreground(color, err);
}
void terminal_stdout_set_foreground(terminal_color color) {
    terminal_set_foreground(color, out);
}

void terminal_stderr_set_background(terminal_color color) {
    terminal_set_background(color, err);
}
void terminal_stdout_set_background(terminal_color color) {
    terminal_set_background(color, out);
}

void terminal_stderr_set_bold(void) {
    terminal_set_bold(err);
}
void terminal_stdout_set_bold(void) {
    terminal_set_bold(out);
}

void terminal_stderr_unset_bold(void) {
    terminal_unset_bold(err);
}
void terminal_stdout_unset_bold(void) {
    terminal_unset_bold(out);
}

void terminal_stderr_reset(void) {
    terminal_reset(err);
}
void terminal_stdout_reset(void) {
    terminal_reset(out);
}
