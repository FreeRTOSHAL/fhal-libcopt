#ifndef AUTOCOPT_H_
#define AUTOCOPT_H_
#include <stdint.h>
#include <sys/ioctl.h>
#ifdef __cplusplus
extern "C" {
#endif

#define AUTOCOPT_MSG_SIZE 31

#define AUTOCOPT_TYPE_ACT 0x0
#define AUTOCOPT_TYPE_FAILT 0x1
#define AUTOCOPT_TYPE_PID 0x2
#define AUTOCOPT_TYPE_SELECT 0x3
#define AUTOCOPT_TYPE_CONTROL 0x4
#define AUTOCOPT_TYPE_EMERGENCY 0x5

#define AUTOCOPT_COUNT (AUTOCOPT_TYPE_CONTROL + 1)
#define AUTOCOPT_BUFFER_SIZE 8

struct autocopt_msg {
	uint8_t type;
	uint8_t data[AUTOCOPT_MSG_SIZE];
} __attribute__ ((__packed__));

#define AUTOCOPT_IOCTL_MAGIC 0x42
#define AUTOCOPT_IOCTL_EMERGENCY_SHUTDOWN _IO(AUTOCOPT_IOCTL_MAGIC, 0x42)
#define AUTOCOPT_IOCTL_BOOTLOADER _IO(AUTOCOPT_IOCTL_MAGIC, 0x43)
#define AUTOCOPT_IOCTL_MIN 0x42
#define AUTOCOPT_IOCTL_MAX 0x43
#ifdef __cplusplus
}
#endif
#endif
