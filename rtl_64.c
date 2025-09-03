#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

char * binsh = "/bin/sh";

int main(){

void * handle = dlopen("/lib/i386-linux-gnu/libc.so.6",1);
int (*system_addr) (const char* str) = dlsym(handle, "system");

char buf[100];

printf("system : %p\n", system_addr);
printf("binsh : %p\n",binsh);

gets(buf);

return 0;