#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */

  struct stat s;
  if( stat(path,&s) == 0 )
  {
    if( s.st_mode & S_IFDIR )
    {
      //printf("%s is dir\n", path);
      return true;
    } else if (s.st_mode & S_IFREG) {
      //printf("%s is not dir\n", path);
      return false;
    }
  } 
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
  struct dirent* entry;
  
  chdir(path);
  DIR *dir = opendir(".");
  num_dirs += 1;
  while((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }
    
    process_path(entry->d_name);
  }
  closedir(dir);
  chdir("..");
}

void process_file(const char* path) {
  /*
   * Update the number of regular files.
   */
  num_regular += 1;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    //printf("Processing %s: ", path);
    process_directory(path);
  } else {
    //printf("Processing %s: ", path);
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;
  //printf("%s", argv[1]);
  process_path(argv[1]);

  printf("Processed all the files from <%s>.\n", argv[1]);
  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
