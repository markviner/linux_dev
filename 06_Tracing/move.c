#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return 1;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];

    struct stat st;
    if (stat(infile, &st) < 0) {
        perror("stat infile");
        return 2;
    }

    int fd_in = open(infile, O_RDONLY);
    if (fd_in < 0) {
        perror("open infile");
        return 3;
    }

    size_t size = (size_t)st.st_size;
    char *buf = NULL;
    if (size > 0) {
        buf = malloc(size);
        if (!buf) {
            perror("malloc");
            close(fd_in);
            return 4;
        }

        ssize_t rr = read(fd_in, buf, size);
        if (rr < 0 || (size_t)rr != size) {
            if (rr < 0) perror("read");
            else fprintf(stderr, "short read\n");
            free(buf);
            close(fd_in);
            return 5;
        }
    }
    close(fd_in);

    char tmpname[4096];
    const char *slash = strrchr(outfile, '/');
    if (slash) {
        size_t dirlen = (size_t)(slash - outfile + 1);
        if (dirlen + strlen(".moveXXXXXX") + 1 > sizeof(tmpname)) {
            fprintf(stderr, "path too long\n");
            free(buf);
            return 6;
        }
        strncpy(tmpname, outfile, dirlen);
        tmpname[dirlen] = '\0';
        strcat(tmpname, ".moveXXXXXX");
    } else {
        strcpy(tmpname, ".moveXXXXXX");
    }

    int fd_tmp = mkstemp(tmpname);
    if (fd_tmp < 0) {
        perror("mkstemp");
        free(buf);
        return 7;
    }

    if (size > 0) {
        ssize_t ww = write(fd_tmp, buf, size);
        if (ww < 0 || (size_t)ww != size) {
            if (ww < 0) perror("write");
            else fprintf(stderr, "short write\n");
            close(fd_tmp);
            unlink(tmpname);
            free(buf);
            return 8;
        }
    }

    free(buf);

    if (fsync(fd_tmp) < 0) {
        perror("fsync");
        close(fd_tmp);
        unlink(tmpname);
        return 9;
    }

    if (close(fd_tmp) < 0) {
        perror("close tmp");
        unlink(tmpname);
        return 10;
    }

    if (rename(tmpname, outfile) < 0) {
        perror("rename");
        unlink(tmpname);
        return 11;
    }

    if (unlink(infile) < 0) {
        perror("unlink infile");
        return 12;
    }

    return 0;
}

