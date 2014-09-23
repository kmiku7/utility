#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace km{
namespace utility{
void init_random_seed()
{
#if defined(__APPLE__)
	sranddev();
    return;
#elif defined(__linux__)
    unsigned int seed = 0;
    int ret = 0;
    int randdev_fd = open("/dev/random", O_RDONLY);
    if (randdev_fd == -1) {
        goto error;
    }
    ret = read(randdev_fd, &seed, sizeof(seed));
    close(randdev_fd);
    if (ret > 0) {
        srand(seed);
    }
    return;
#endif
error:
    srand(time(NULL));
}
} // end namespace utility
} // end namespace km
