#include "repl.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  // dapatkan informasi pengguna
  struct passwd *user = getpwuid(getuid());
  if (user == NULL) {
    fprintf(stderr, "gagal mendapatkan informasi pengguna");
    exit(1);
  }

  // cetak pesan
  printf("Hello %s! Ini adalah bahasa pemograman COK\n", user->pw_name);
  printf("Feel free to type commands\n");

  start(stdin, stdout);
  return 0;
}
