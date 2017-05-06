/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 Chris Gregory czipperz@gmail.com
 */

#ifndef HEADER_GUARD_TERMINAL_H
#define HEADER_GUARD_TERMINAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum terminal_color {
    terminal_black         = 0,
    terminal_red           = 1,
    terminal_green         = 2,
    terminal_yellow        = 3,
    terminal_blue          = 4,
    terminal_magenta       = 5,
    terminal_cyan          = 6,
    terminal_white         = 7,
    terminal_default_color = 9
} terminal_color;

/*** stderr functions ***/

/*! \brief Tells stderr to output characters with a given foreground
 * color. */
void terminal_stderr_set_foreground(terminal_color);

/*! \brief Tells stderr to output characters with a given background
 * color. */
void terminal_stderr_set_background(terminal_color);

/*! \brief Tells stderr to output bold characters */
void terminal_stderr_set_bold(void);

/*! \brief Tells stderr to output non-bold characters */
void terminal_stderr_unset_bold(void);

/*! \brief Resets stderr's colors and output non-bold characters */
void terminal_stderr_reset(void);

/*** stdout functions ***/

/*! \brief Tells stdout to output characters with a given foreground
 * color. */
void terminal_stdout_set_foreground(terminal_color);

/*! \brief Tells stdout to output characters with a given background
 * color. */
void terminal_stdout_set_background(terminal_color);

/*! \brief Tells stdout to output bold characters */
void terminal_stdout_set_bold(void);

/*! \brief Tells stdout to output non-bold characters */
void terminal_stdout_unset_bold(void);

/*! \brief Resets stdout's colors and output non-bold characters */
void terminal_stdout_reset(void);

#ifdef __cplusplus
}
#endif

#endif
