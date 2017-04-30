#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        fprintf(stderr, "Usage: %s HOST PORT", argv[0]);
    }

    char* HOST = argv[1];
    char* PORT = argv[2];

    /* Lookup address info of remote host */
    struct addrinfo* results;
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
    };
    int status;
    if ((status = getaddrinfo(HOST, PORT, &hints, &results)) != 0 ) {
        fprintf (stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
        return status;
    }
    
    /* create netwrok file descriptor */
    int socket_fd = -1;
    for (struct addrinfo* p =results; p != NULL && socket_fd < 0; p = p->ai_next) {
        /* allocate socket */
        if ((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
            fprintf(stderr, "Unable to make socket: %s\n", strerror(errno));
            continue;
        }
        /* Connect to host */
        if (connect(socket_fd, p->ai_addr, p->ai_addrlen) < 0) {
            fprintf(stderr, "Unable to connect to %s:%s: %s\n", HOST, PORT, strerror(errno));
            close(socket_fd);
            socket_fd = -1;
            continue;
        }
    }
   
    freeaddrinfo(results);

    if (socket_fd < 0) {
        return EXIT_FAILURE;
    }

    /* Open socket stream */
    FILE* stream = fdopen(socket_fd, "w+");
    if (stream == NULL) {
        fprintf (stderr, "Unable to fdopen: %s\n", strerror(errno));
        return errno;
    }
    
    /* write from stdin to stream */
    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, stdin)) {
        fputs(buf, stream);
        fflush(stream);
    }

    shutdown(socket_fd, SHUT_RDWR);
    fclose(stream);
    close(socket_fd);
    return 0;
}
