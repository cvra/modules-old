/*  
 *  Copyright Droids Corporation (2007)
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Revision : $Id: scheduler.h,v 1.8.4.11 2009-05-18 12:30:36 zer0 Exp $
 *
 */

/* Olivier MATZ <zer0@droids-corp.org>
 * Interface of the SCHEDULER Module
 */

/** \file scheduler.h
 *
 * This module provides a function scheduler. You can call
 * scheduler_add_event for adding a function to the scheduler, and
 * specifying what interval between each call. During the execution of
 * the function, interrupts are masked !! So use this module with
 * caution (small functions) for avoiding problems.
 *
 * Functions with a high priority value will be call before others
 * (default is 128).
 *
 * @todo Study the implications of having ported it to FPGA regarding interuptions
 * masking.
 */


#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <aversive.h>

/** \addtogroup Scheduler
 * This is the multi tasking subsystem.
 * @{
 */
/* Config */
#define SCHEDULER_UNIT 1000         /**< The scheduler tick in us. */
#define SCHEDULER_NB_MAX_EVENT 10   /**< The size of the event table. */

/** The number of maximal stacking events. */
#define SCHEDULER_NB_STACKING_MAX SCHEDULER_NB_MAX_EVENT


#define SCHEDULER_PERIODICAL 0 /**< Flag for a periodical event. */
#define SCHEDULER_SINGLE 1 /**< Flag for a single fire event. */

/** Default priority of events. */
#define SCHEDULER_DEFAULT_PRIORITY 128

/** Initialisation of the module. */
void scheduler_init(void);

/** Dump all events. */
void scheduler_dump_events(void);

/** @brief Alloc an event.
 *
 * This function allocs an event, fill its fields and then mark it as active.
 *
 * @param [in] unicity SCHEDULER_PERIODICAL or SCHEDULER_SINGLE.
 * @param [in] *f The function to call. Its prototype must be void f(void *data).
 * @param [in] data This will be passed as the first argument to f.
 * @param [in] period The period, in number of scheduler ticks. 
 * @param [in] priority The priority of the task, higher number means higher priority.
 *
 * @return The index of the event in the table or -1 if no event is available.
 *
 * @sa scheduler_add_single_event_priority
 * @sa scheduler_add_periodical_event_priority
 * @sa scheduler_add_single_event
 * @sa scheduler_add_periodical_event
 */
int8_t scheduler_add_event(uint8_t unicity, void (*f)(void *), void * data, uint16_t period, uint8_t priority);


/** @brief Add a single event to the event table, specifying the priority.
 *
 * This function adds a single fire event with given priority to the table.
 * @param [in] *f The function to call. Its prototype must be void f(void *data).
 * @param [in] data This will be passed as the first argument to f.
 * @param [in] period The time before firing up, in number of scheduler ticks. 
 * @param [in] priority The priority of the task, higher number means higher priority.
 * @return The index of the event in the table or -1 if no event is available.
 */
static inline int8_t scheduler_add_single_event_priority(void (*f)(void *), void * data, uint16_t period, uint8_t priority)
{
	return scheduler_add_event(SCHEDULER_SINGLE, f, data, period, priority);
}

/** @brief Add a periodical event to the event table, specifying the priority.
 *
 * This function adds a single fire event with given priority to the table.
 * @param [in] *f The function to call. Its prototype must be void f(void *data).
 * @param [in] data This will be passed as the first argument to f.
 * @param [in] period The period of the task, in number of scheduler ticks. 
 * @param [in] priority The priority of the task, higher number means higher priority.
 * @return The index of the event in the table or -1 if no event is available.
 */
static inline int8_t scheduler_add_periodical_event_priority(void (*f)(void *), void * data, uint16_t period, uint8_t priority)
{
	return scheduler_add_event(SCHEDULER_PERIODICAL, f, data, period, priority);
}

/** @brief Add a single fire event to the event table with default priority.
 *
 * This function adds a single fire event with given priority to the table.
 * @param [in] *f The function to call. Its prototype must be void f(void *data).
 * @param [in] data This will be passed as the first argument to f.
 * @param [in] period The time before firing up, in number of scheduler ticks. 
 * @return The index of the event in the table or -1 if no event is available.
 */
static inline int8_t scheduler_add_single_event(void (*f)(void *), void * data, uint16_t period)
{
	return scheduler_add_event(SCHEDULER_SINGLE, f, data, period, SCHEDULER_DEFAULT_PRIORITY);
}

/** @brief Add a periodical event to the event table with default priority.
 *
 * This function adds a single fire event with given priority to the table.
 * @param [in] *f The function to call. Its prototype must be void f(void *data).
 * @param [in] data This will be passed as the first argument to f.
 * @param [in] period The period of the event, in number of scheduler ticks. 
 * @return The index of the event in the table or -1 if no event is available.
 */
static inline int8_t scheduler_add_periodical_event(void (*f)(void *), void * data, uint16_t period)
{
	return scheduler_add_event(SCHEDULER_PERIODICAL, f, data, period, SCHEDULER_DEFAULT_PRIORITY);
}

/** @brief Deletes an event.
 * 
 * Deletes the given event. If it was scheduled for execution, it will be
 * executed before deletion.
 *
 * @param [in] num The event ID to delete.
 */
void scheduler_del_event(int8_t num);

/** @brief Scheduler tick
 *
 * This function is responsible for all the scheduler work and will be called
 * periodically by a timer interrupt.
 */
void scheduler_interrupt(void);


/** @brief Disables the scheduler events.
 *
 * This function temporarily disables the scheduler events. While the scheduler
 * is disabled, all events are marked as "scheduled".
 *
 * @return Old priority of the scheduler, to be passed to scheduler_enable_restore().
 */
int8_t scheduler_disable_save(void);

/** @brief Re-enables scheduler events.
 *
 * Re-enable scheduler after a call to scheduler_disable_save().
 *
 * @param [in] old_prio The old priority returned by scheduler_disable_save(). 
 */
void scheduler_enable_restore(uint8_t old_prio);

/** @} */

#endif
