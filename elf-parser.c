#include <stdio.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>
#include <stdio.h>
#include <fcntl.h>








/*
int main(int argc, char *argv[]) {
  int fd;
  int val;
  FILE *fp;
  Elf64_Ehdr s;
  
  if (argc != 2) {
    printf("errir");
    return 0;

  }
  fp = fopen(argv[1], "r");
  fread(&s, 1, sizeof(s), fp);
  printf("%c",s. e_ident[EI_MAG1] );

}
*/




#include <stdio.h>

#define OFFSET 16
int magic(char* emagic) {
  int fd;
  int val;
  FILE *fp;
  Elf64_Ehdr s;
  fp = fopen(emagic, "r");
  fread(&s, 1, sizeof(s), fp);
  printf("magic number - %c%c%c\n",*(s.e_ident+1),*(s.e_ident+2),*(s.e_ident+3));
  
  return 0;


}











int hexdump(char* b) {

    char buff[OFFSET] = "";
    int re, addr = 0, i;
    FILE *fp = fopen (b, "rb");


    while ((re = fread(buff, 1, sizeof(buff), fp)) > 0) {
        

        printf("%08hhx ", addr);
        addr = addr + OFFSET;    //next line addr

        for (i = 0; i < OFFSET; i++)    
                printf("%02x ", (unsigned char)buff[i]);


        fputs ("| ", stdout); 

        for (i = 0; i < OFFSET; i++)    // print ascii values 
            printf("%c", (buff[i] >= ' ' && buff[i] <= '~' ? buff[i] : '.'));
        putchar ('\n'); 
    }
}

int print_shdr(const char *const fn) {
  int fd = open(fn, O_RDONLY);
  int N=5000;
  char *p = mmap(0,N*sizeof(int), PROT_READ, MAP_PRIVATE, fd, 0);

  Elf64_Ehdr *ehdr = (Elf64_Ehdr*)p;
  Elf64_Shdr *shdr = (Elf64_Shdr *)(p + ehdr->e_shoff);
  int shnum = ehdr->e_shnum;
//e_shoff hold sec header file  offset  in bytes.
//e_shtrndx This  member  holds  the section header table index of the entry
//
  Elf64_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
  const char *const sh_strtab_p = p + sh_strtab->sh_offset;
//total sec by shnum
  for (int i = 0; i < shnum; ++i) {
    printf("%2d: %4d '%s'\n", i, shdr[i].sh_name,
           sh_strtab_p + shdr[i].sh_name);
    // let header 64 than offset = i *64 +e_shoff and eshoff+offset +64 
  }

  return 0;
}








int main (int argc, char **argv) 
{
    char buff[OFFSET] = "";
    int read, address = 0, i;

//    if (!fp) {
  //      perror ("fopen");
    //    return 1;
    

    int input;
    printf("1- hex dump\n");
    printf("2 -sections\n");
    printf("magical number\n");
    
    scanf("%d", &input);

    switch (input) {
    case 1:

            hexdump(argv[1]);
            break;
    case 2:
            print_shdr(argv[1]);
            break;
    case 3:
            magic(argv[1]);
            break;


    }
// buffer and read  are 16 size
   
}
