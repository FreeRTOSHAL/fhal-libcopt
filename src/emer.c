#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <autocopt/autocopt.h>
#include <autocopt/emergency.h>

int main(int argc, char **argv) {
	int32_t ret;
	struct autocopt *copt = autocopt_init(AUTOCOPT_DEFAULT_DEV);
	if (copt == NULL) {
		fprintf(stderr, "Can't create autocopt\n");
		autocopt_deinit(copt);
		return EXIT_FAILURE;
	}
	ret = autocopt_emergencyLanding(copt);
	if (ret < 0) {
		fprintf(stderr, "Copter not resporn emergency Landing\n");
		fprintf(stderr, "Send reset");
		autocopt_reset(copt);
		autocopt_deinit(copt);
		return EXIT_FAILURE;
	}
	printf("Copter going to land\n");
	autocopt_deinit(copt);
	return EXIT_SUCCESS;
}
