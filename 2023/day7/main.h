
enum{
	A = 14,
	K = 13,
	Q = 12,
	J = 1,
	T = 10,
	five_kind = 6,
	four_kind = 5,
	full_house = 4,
	three_kind = 3,
	two_pair = 2,
	one_pair = 1,
	high_card = 0,
};

typedef struct _CARD{

	char* str;
	int type;
	int value;
}Card;

int char_to_int(char);
int compare(void*, void*);
void lhash(char*, int*);
int get_type(int*);
void insert(Card**, Card*);
