typedef struct keys{
	bool menu;

	bool A;
	bool B;
	bool C;
	bool D;
	bool E;
	bool F;
	bool G;
	bool H;
	bool I;
	bool J;
	bool K;
	bool L;
	bool M;
	bool N;
	bool O;
	bool P;
	bool Q;
	bool R;
	bool S;
	bool T;
	bool U;
	bool V;
	bool W;
	bool X;
	bool Y;
	bool Z;

	bool SHIFT;
} keys_t;

keys_t* init_keys(void);
void purge_keys(keys_t*);
void free_keys(keys_t*);
