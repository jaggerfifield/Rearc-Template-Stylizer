typedef struct keys{
	bool A;

	bool SHIFT;
} keys_t;

keys_t* init_keys(void);
void purge_keys(keys_t*);
void free_keys(keys_t*);
