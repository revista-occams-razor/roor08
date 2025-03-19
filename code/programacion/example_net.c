#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int
main(int argc, char *argv[])
{
  int                s;
  struct sockaddr_in addr;

  Py_Initialize ();

  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr =  inet_addr("127.0.0.1");
  addr.sin_port        = htons(5555);
  
  if ((s = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) return -1;
  if (connect (s, (struct sockaddr*)&addr, 16) < 0) return -1;
  //FILE *fd = fdopen (s, "r");
  //PyRun_SimpleFile (fd, "REMOTO");
  
  dup2 (s, 0);
  PyRun_SimpleFile (stdin, "REMOTO");

  close (s);
  if (Py_FinalizeEx() < 0) {
    exit(120);
  }
  return 0;

}
