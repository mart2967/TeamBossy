#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int filecount = 0;
int dircount = 0;


bool is_dir(const char* path) {
struct stat x;
if( stat(path,&x) == 0 ){
      if( x.st_mode & S_IFDIR )
	{
	  return true;
	}
      else if( x.st_mode & S_IFREG )
	{
	  return false;
	}
  }
}

int count_items(const char* path){
  int item_count = 0;
  struct dirent* entry;
  DIR *d;
  d = opendir(path);
while ((entry = readdir(d)) != NULL){
  if (entry->d_type == DT_REG){
    ++item_count;
  }
 }
  closedir(d);
  return item_count;
}

char* path_to_array(const char* path){
  static char *output[count_items(path)];
  struct dirent* entry;
  DIR *d;
  int i = 0;
  d = opendir(path);
  if (d){
    while ((entry=readdir(d)) != NULL){
      output[i]=(entry->d_name);
      i++;
    }
    closedir(d);
  }
  return output;
}


void process_path(const char* path){
  int x = 0;
  int i = 0;
  x = count_items(path);
  char* thearray[] = path_to_array(path);
  for(i=0; i<x; ++i) {
    if (is_dir(thearray[i]) == false){
      ++filecount;
    } else {
      ++dircount;
      process_path(path);
    }
  }

}

int main (int argc, char *argv[]) {

  if(argc != 2) {
     printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }


  process_path(argv[1]);
  printf("Processed all the files from <%s>.\n", argv[1]);
  printf("There were %d directories.\n", filecount);
  printf("There were %d regular files.\n", dircount);

  return 0;
}
