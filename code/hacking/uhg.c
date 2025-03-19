#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>

#define BLK_SIZE 1024 

int
main (int argc, char *argv[]) {
  long          addr;
  size_t        size;
  pid_t         pid;
  int           piped = 1;
  unsigned char *buf;
  
  if (!isatty(1)) piped = 0;
  if (piped) {
    printf ("UHG! Utilidad para el Hackeo de Games!\n");
    printf ("%s", "Version 1.0 (c) Yvil Yenius\n");
  }
  if (argc != 4) {
    fprintf (stderr, "Usage:\n%s pid mem_addr mem_size\n",argv[0]);
    exit (1);
  }
  pid = atoi (argv[1]);
  addr = atol (argv[2]);
  size = atol (argv[3]);

  buf = malloc (size);
  struct iovec local[1];
  struct iovec remote[1];
  ssize_t      nread;

  local[0].iov_base = buf;
  local[0].iov_len = size;
  remote[0].iov_base = (void *)addr;
  remote[0].iov_len = size;
  if (piped) printf ("Reading %lx bytes from %p\n", size, (void*)addr);
  nread = process_vm_readv (pid, local, 1, remote, 1, 0);
  if (nread  != size) {
    perror ("process_vm_readv:");
    exit (EXIT_FAILURE);
  }
  // Output to std out
  int n;
  //fprintf (stderr,"Dumping 0x%lx bytes\n", size);
  for (int i = 0; i < size;) {
    n = size - i < BLK_SIZE ? size - i : BLK_SIZE;
    nread = write (1, buf+i, n);
    i +=nread;
    //fprintf (stderr, "Writed 0x%lx... 0x%lx to go\n", nread , size - i); 
  }
  return 0;
}
