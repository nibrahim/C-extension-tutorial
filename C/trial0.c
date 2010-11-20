#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"
#include "trial0.h"

struct csv_parser parser; /* Declare the parser */

void 
parse_field(void *data, size_t len, void * dummy) 
{
  char * t = data;
  printf("   %s\n",t);
}

void 
parse_row(int val, void *dummy)
{
  printf("--------------------------------------------------\n");
}
  
int
main()
{
  FILE *fp;
  char *data = NULL;
  size_t processed_len;
  data = (char *)malloc(sizeof(char) * FILE_SIZE);
  memset(data, '\0', FILE_SIZE);

  csv_init(&parser, CSV_APPEND_NULL);
  fp = fopen(SAMPLE_FILE, "r");
  fread(data, sizeof(char), FILE_SIZE, fp);

  processed_len = csv_parse(&parser, data, FILE_SIZE, 
			    parse_field,
			    parse_row,
			    NULL);
  printf("\nParsed %d bytes\n",(int)processed_len);

  return 0;
}
