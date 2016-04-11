#pragma once

typedef XXXX CriticalSection_t;

/**
 * Initialize a critical section object
 * \param pCS  Container for critical section object
 * \return    ERR_SUCCESS  Critical Section was initialized
 *            ERR_BUSY     Object was already initialized
 *            ERR_PARAM    The parameter was NULL
 */
ErrCode_t InitializeCriticalSection(CriticalSection_t* pCS);



/**
 * Attempt to take a critical section
 * \param pCS Initialized critical section object
 * \return    ERR_SUCCESS critical section is now owned by this thread
 *            ERR_ALREADY alredy owned by this thread
 *            ERR_BUSY    critical section is owned by another thread
 *            ERR_UNINIT  The critical section not ready
 *            ERR_PARAM   The parameter was NULL
 *            ERR_RESOURCES Out of resources
 */
ErrCode_t EnterCriticalSection(CriticalSection_t* pCS);


/**
 * Release a critical section that was previously taken
 * \param pCS Initialized and owned critical section object
 * \return    ERR_SUCCESS critical section was released
 *            ERR_BUSY    critical section is owned by another thread, cannot be release here
 *            ERR_UNINIT  The critical section not ready
 *            ERR_PARAM   The parameter was NULL
 */
ErrCode_t LeaveCriticalSection(CriticalSection_t* pCS);


/**
 * Release any resources
 * \param pCS The object to cleanup
 * \return ERR_SUCCESS resources released
 *         ERR_BUSY    The object is currently taken by another thread (Discuss: should this be an error?)
 *         ERR_PARAM   parameter was NULL
 */
ErrCode_t DeleteCriticalSection(CriticalSection_t* pCS);



