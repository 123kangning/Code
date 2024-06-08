#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int stdin_fd, stdout_fd, stderr_fd;
  // 打开/dev/stdin、/dev/stdout和/dev/stderr
  stdin_fd = open("/dev/stdin", O_RDONLY);
  stdout_fd = open("/dev/stdout", O_WRONLY);
  stderr_fd = open("/dev/stderr", O_WRONLY);

  // 将文件描述符分别赋值给0、1、2
  dup2(stdin_fd, 0);
  dup2(stdout_fd, 1);
  dup2(stderr_fd, 2);

  // 关闭原来的文件描述符
  close(stdin_fd);
  close(stdout_fd);
  close(stderr_fd);
  if (write(1, "here is some data\n", 18) != 18)
    write(2, "a write error has occurred", 26);
  exit(0);
}