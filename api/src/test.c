#include "Hector.h"
#include "socklib.h"

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <pthread.h>

#ifdef __linux__
int _getch()
{
  struct termios oldt, newt;
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

int _kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF)
    {
      ungetc(ch, stdin);
      return 1;
    }

  return 0;
}
#endif

int socketClient;

void *getAction(void *data) {
  char *action = (char*)data;
  while (1) {
    //*action = RecoieLigne(socketClient);
    strcpy(action, RecoieLigne(socketClient));
    printf("nouvelle action\n");
  }
}

int main()
{
  pthread_t thread;
  char action[50];
  openDevice();
  socketClient = CreeSocketClient("192.168.1.166", "8080");

  if (pthread_create(&thread, NULL, getAction, action) == 0) {
    printf("tout c bien passé\n");
  } else {
    printf("EROOOOOOOOR\n");
  }
  
  if (socketClient == -1) {
    fprintf(stderr, "error\n");
    exit(1);
  }

  char *left = "LEFT";
  char *right = "RIGHT";
  char *forward = "FORWARD";
  char *backward = "BACKWARD";
  
  while (1) {
    printf("%s\n", action);

    /* if (strcmp(action, left) == 0) */
    /*   moveTo(9, getPosition(8) - 5); */

    /* if (strcmp(action, right) == 0) */
    /*   moveTo(9, getPosition(8) + 5); */
    
    if (strcmp(action, forward) == 0)
      moveToWithSpeed(8, getPosition(8) + 5, 10);
    
    if (strcmp(action, backward) == 0)
      moveToWithSpeed(8, getPosition(8) - 5, 10);
  }
  closeDevice();
  return 0;
}
