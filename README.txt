Program accepts a search string argument and uses binary search to navigate a dictionary file until a match is found or
it is determined that no match exists.  Program is case sensitive.


Dictionary file: The location of the dictionary file is defined at the top of ok.c 
                    The file must be in alphabetical order, one word per line. Line length must also be defined at the top
                    of ok.c
                    
Dictionary can contain up to the amount of words that matches the machine's max LONG INT value before overflowing


Program returns 0 if the given word is found, 99 if not. There are also various error exit codes defined within ok.c


make file:
          all:  Produces executable as "ok".
        clean:  rm's all files provided in the zip and those produced by make all. 
          run:  Executes the program with {want} as the search term. Invoke the program with "make run want={search_term}" or 
                    initialize and export the environmental variable "want".


