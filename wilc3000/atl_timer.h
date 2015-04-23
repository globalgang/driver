#ifndef __ATL_TIMER_H__
#define __ATL_TIMER_H__

/*!  
*  @file	atl_timer.h
*  @brief	Timer (One Shot and Periodic) OS wrapper functionality
*  @author	syounan
*  @sa		ATWILC_OSWrapper.h top level OS wrapper file
*  @date	16 Aug 2010
*  @version	1.0
*/

#ifndef CONFIG_ATL_TIMER_FEATURE
#error the feature CONFIG_ATL_TIMER_FEATURE must be supported to include this file
#endif

typedef void (*tpfATL_TimerFunction)(void*);

/*!
*  @struct 		tstrATL_TimerAttrs
*  @brief		Timer API options 
*  @author		syounan
*  @date		16 Aug 2010
*  @version		1.0
*/
typedef struct
{
	/*!< if set to ATL_TRUE the callback function will be called 
	periodically. */
	#ifdef CONFIG_ATL_TIMER_PERIODIC
	ATL_Bool bPeriodicTimer;
	#endif
	
	/* a dummy member to avoid compiler errors*/
	ATL_Uint8 dummy;
}tstrATL_TimerAttrs;

/*!
*  @brief	Fills the ATL_TimerAttrs with default parameters
*  @param[out]	pstrAttrs structure to be filled
*  @sa		ATL_TimerAttrs
*  @author	syounan
*  @date	16 Aug 2010
*  @version	1.0
*/

static void ATL_TimerFillDefault(tstrATL_TimerAttrs* pstrAttrs)
{
	#ifdef CONFIG_ATL_TIMER_PERIODIC
	pstrAttrs->bPeriodicTimer = ATL_FALSE;
	#endif
}


/*!
*  @brief	Creates a new timer
*  @details	Timers are a useful utility to execute some callback function
		in the future.
		A timer object has 3 states : IDLE, PENDING and EXECUTING
		IDLE : initial timer state after creation, no execution for the
		callback function is planned
		PENDING : a request to execute the callback function is made 
		using ATL_TimerStart.
		EXECUTING : the timer has expired and its callback is now 
		executing, when execution is done the timer returns to PENDING 
		if the feature CONFIG_ATL_TIMER_PERIODIC is enabled and 
		the flag tstrATL_TimerAttrs.bPeriodicTimer is set. otherwise the
		timer will return to IDLE
*  @param[out]	pHandle handle to the newly created timer object
*  @param[in]	pfEntry pointer to the callback function to be called when the
		timer expires
		the underlaying OS may put many restrictions on what can be 
		called inside a timer's callback, as a general rule no blocking
		operations (IO or semaphore Acquision) should be perfomred
		It is recommended that the callback will be as short as possible
		and only flags other threads to do the actual work
		also it should be noted that the underlaying OS maynot give any
		guarentees on which contect this callback will execute in
*  @param[in]	pstrAttrs Optional attributes, NULL for default
*  @return	Error code indicating sucess/failure
*  @sa		ATL_TimerAttrs
*  @author	syounan
*  @date	16 Aug 2010
*  @version	1.0
*/
ATL_ErrNo ATL_TimerCreate(ATL_TimerHandle* pHandle, 
	tpfATL_TimerFunction pfCallback, tstrATL_TimerAttrs* pstrAttrs);


/*!
*  @brief	Destroys a given timer
*  @details	This will destroy a given timer freeing any resources used by it
		if the timer was PENDING Then must be cancelled as well(i.e. 
		goes to	IDLE, same effect as calling ATL_TimerCancel first)
		if the timer was EXECUTING then the callback will be allowed to 
		finish first then all resources are freed
*  @param[in]	pHandle handle to the timer object
*  @param[in]	pstrAttrs Optional attributes, NULL for default
*  @return	Error code indicating sucess/failure
*  @sa		ATL_TimerAttrs
*  @author	syounan
*  @date	16 Aug 2010
*  @version	1.0
*/
ATL_ErrNo ATL_TimerDestroy(ATL_TimerHandle* pHandle, 
	tstrATL_TimerAttrs* pstrAttrs);

/*!
*  @brief	Starts a given timer
*  @details	This function will move the timer to the PENDING state until the
		given time expires (in msec) then the callback function will be 
		executed (timer in EXECUTING state) after execution is dene the
		timer either goes to IDLE (if bPeriodicTimer==ATL_FALSE) or
		PENDING with same timeout value (if bPeriodicTimer==ATL_TRUE)
*  @param[in]	pHandle handle to the timer object
*  @param[in]	u32Timeout timeout value in msec after witch the callback 
		function will be executed. Timeout value of 0 is not allowed for 
		periodic timers
*  @param[in]	pstrAttrs Optional attributes, NULL for default, 
		set bPeriodicTimer to run this timer as a periodic timer
*  @return	Error code indicating sucess/failure
*  @sa		ATL_TimerAttrs
*  @author	syounan
*  @date	16 Aug 2010
*  @version	1.0
*/
ATL_ErrNo ATL_TimerStart(ATL_TimerHandle* pHandle, ATL_Uint32 u32Timeout, void* pvArg,
	tstrATL_TimerAttrs* pstrAttrs);


/*!
*  @brief	Stops a given timer
*  @details	This function will move the timer to the IDLE state cancelling 
		any sheduled callback execution.
		if this function is called on a timer already in the IDLE state 
		it will have no effect.
		if this function is called on a timer in EXECUTING state 
		(callback has already started) it will wait until executing is 
		done then move the timer to the IDLE state (which is trivial 
		work if the timer is non periodic)
*  @param[in]	pHandle handle to the timer object
*  @param[in]	pstrAttrs Optional attributes, NULL for default, 
*  @return	Error code indicating sucess/failure
*  @sa		ATL_TimerAttrs
*  @author	syounan
*  @date	16 Aug 2010
*  @version	1.0
*/
ATL_ErrNo ATL_TimerStop(ATL_TimerHandle* pHandle, 
	tstrATL_TimerAttrs* pstrAttrs);



#endif
