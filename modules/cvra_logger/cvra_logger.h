/*
 * cvra_logger.h
 *
 *  Created on: 21 mars 2012
 *      Author: Antoine Albertelli
 */

#ifndef CVRA_LOGGER_H_
#define CVRA_LOGGER_H_
/** @todo Tester le module */

/** Resets the log. */
void cvra_logger_reset();

/** Gets the content of the log */
const char *cvra_logger_get_log();

/** Appends a string to the logger */
void cvra_logger_log(const char *message);


#endif /* CVRA_LOGGER_H_ */
