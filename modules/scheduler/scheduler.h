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
 * This module uses Timer 0
 */


#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <aversive.h>

#warning "Cette valeur doit etre modifiee en fonction des timers"
#define SCHEDULER_UNIT 16 /* us */
#define SCHEDULER_NB_MAX_EVENT 5
#define SCHEDULER_NB_STACKING_MAX SCHEDULER_NB_MAX_EVENT


#define SCHEDULER_PERIODICAL 0
#define SCHEDULER_SINGLE 1

#define SCHEDULER_DEFAULT_PRIORITY 128


/** Initialisation of the module */
void scheduler_init(void);

/** dump all loaded events */
void scheduler_dump_events(void);

/** 
 * Add an event to the event table.
 * Return the id of the event on succes and -1 on error
 * You can use static inline funcs below for simpler use.
 */
int8_t scheduler_add_event(uint8_t unicity, void (*f)(void *), void * data, uint16_t period, uint8_t priority);


/** 
 * Add a single event to the event table, specifying the priority
 */
static inline int8_t scheduler_add_single_event_priority(void (*f)(void *), void * data, uint16_t period, uint8_t priority)
{
	return scheduler_add_event(SCHEDULER_SINGLE, f, data, period, priority);
}

/** 
 * Add a periodical event to the event table, specifying the priority
 */
static inline int8_t scheduler_add_periodical_event_priority(void (*f)(void *), void * data, uint16_t period, uint8_t priority)
{
	return scheduler_add_event(SCHEDULER_PERIODICAL, f, data, period, priority);
}

/** 
 * Add a single event to the event table, with the default priority
 */
static inline int8_t scheduler_add_single_event(void (*f)(void *), void * data, uint16_t period)
{
	return scheduler_add_event(SCHEDULER_SINGLE, f, data, period, SCHEDULER_DEFAULT_PRIORITY);
}

/** 
 * Add a periodical event to the event table, with the default priority
 */
static inline int8_t scheduler_add_periodical_event(void (*f)(void *), void * data, uint16_t period)
{
	return scheduler_add_event(SCHEDULER_PERIODICAL, f, data, period, SCHEDULER_DEFAULT_PRIORITY);
}

/**
 * Dels an event from the table by its ID. If there is no event,
 * nothing is done.
 */
int8_t scheduler_del_event(int8_t num);

/** Function called by the interruption. It is public in case of host
 *  version, because you have to call it by hand. In AVR version, you
 *  don't have to do anything with this function, it is called
 *  automatilcally by the timer interruption, except if
 *  CONFIG_MODULE_SCHEDULER_MANUAL is defined. In this case you have
 *  to call it manually too. */
void scheduler_interrupt(void);

/**
 * Temporarily disable scheduler events. You may loose precision in
 * events schedule. It returns the current priority of the scheduler.
 */
uint8_t scheduler_disable_save(void);

/**
 * Re-enable scheduler after a call to scheduler_disable_save().
 */
void scheduler_enable_restore(uint8_t old_prio);

#endif
