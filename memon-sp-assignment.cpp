#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main()
{
    time_t start;
    time_t end;
    int original = open("/home/wuntap/Desktop/SP-CS-6/Linux System Programming - Robert Love.pdf", O_RDWR);
    if (original == -1)
    {
        perror("Something went wrong in opening original file");
    }
    int copied = open("/home/wuntap/Desktop/SP-CS-6/Copied Book.pdf", O_RDWR | O_CREAT, S_IRWXU);
    if (copied == -1)
    {
        perror("Something went wrong while opening new file");
    }
    char readStore[1000];
    int copiedBytes = -1;
    write(STDOUT_FILENO,"Program has started!", 20);
    write(STDOUT_FILENO,"\n", 1);
    start = time(0);
    while (copiedBytes != 0)
    {
        copiedBytes = read(original, readStore, 1000);
        write(copied, readStore, 1000);
        fsync(copied);
    }
    end = time(0);
    double elapsed = difftime(end, start);
    write(STDOUT_FILENO, "Using FSYNC (1 byte), it took: ", 34);
    char holder[10];
    int sizeOfArr = sprintf(holder, "%f", elapsed);
    write(STDOUT_FILENO, holder, sizeOfArr);
}