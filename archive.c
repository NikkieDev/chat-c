char **buffer[10];

typedef struct cache_entry
{
  char type[128];
  void *entry[128]; // generic pointer, then dereference for value. Dynamic
} cache_entry;

cache_entry cache[128];

cache_entry cnew_entry(char *type, char *entry) {

};

void writes_multiple(int sock_fd, cache_entry entry[])
{
  for (int i = 0; i < sizeof(entry) / sizeof(entry[0]); i++)
  {
    
  }
};

// make a buffer writing algorithm that cycles through the available rows each row containing both a type and an entry