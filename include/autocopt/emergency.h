#ifndef EMERGENCY_H_
#define EMERGENCY_H_
#include <autocopt/autocopt.h>
#ifdef __cplusplus
extern "C" {
#endif

#define AUTOCOPT_DEFAULT_ADDR 0x3f000000UL
#define AUTOCOPT_DEFAULT_ENTRYPOINT 0x3f000001UL

/**
 * Override Thrust Contol
 * 
 * This Funktion Override active Thrust and set Thrust to 40 % for 2 Sec and then shutdown Motor. 
 * After calling this Function Copter response to all messages. Thrust Control can't reset again, restart of Program is needed.
 * Call autocopt_reset() -> autocopt_setEntrypoint() -> autocopt_reset() for reset
 * Optional reload Application over autocopt_copyAppToMem
 */
int32_t autocopt_emergencyLanding(struct autocopt *copt);

/** 
 * Send Emergency Shutdown
 * 
 * Prozessor shutdown the motors and go offline. Restart of whole system is needed, to restart prozessor. 
 * 
 * \param copt Autcopt Handle
 * \return -1 on Error and 0 on Ok
 */
int32_t autocopt_shutdown(struct autocopt *copt);
/**
 * Reset M4 to Bootloader. Copter Shutdown all Motors first
 * \param copt Autcopt Handle
 * \return -1 on Error and 0 on Ok
 */
int32_t autocopt_reset(struct autocopt *copt);
/**
 * Set Entrypoint for Application
 * \param copt Autcopt Handle
 * \param entry Entry Address for Application. Address shall Odd!
 * \return -1 on Error and 0 on Ok
 */
int32_t autocopt_setEntrypoint(struct autocopt *copt, uint32_t entry);
/**
 * Copy App to Memmory
 * \param dest Destination Address
 * \param srcFD File FD 
 * \return -1 on Error and 0 on Ok
 */
int32_t autocopt_copyAppToMem(uint32_t dest, int srcFd);
#ifdef __cplusplus
}
#endif
#endif
