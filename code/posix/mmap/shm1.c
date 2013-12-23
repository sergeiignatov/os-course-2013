#include <assert.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define NAME    ("/linuxquestions.org")

int main()
{
        int fd;

        assert((fd = shm_open(NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) >= 0);
        sleep(30);
        assert(close(fd) == 0);
        assert(shm_unlink(NAME) == 0);

        return 0;
}
