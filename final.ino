#include <stdlib.h>
#define out_pin 12
#define in_pin 13
#define ir_in 7
#define ir_out 6
#define ctrl_pin_in 8
#define timeout 30000
#define dottime 4800
#define antierrortime 500
#define baudrate 1200


struct node{
	char ch;
	struct node *left, *right;

};
typedef struct node node_t;

int check;
int n;
int state;
node_t *root;
int ch;
int ch_in;
int count;
char buff[20];
int buff_index;


node_t *initialize()
{
	node_t *root = (node_t *) malloc(sizeof(node_t));
	root->ch = '/';

	//E
	root->left = (node_t *) malloc(sizeof(node_t));
	root->left->ch = 'E';

	//I
	root->left->left = (node_t *) malloc(sizeof(node_t));
	root->left->left->ch = 'I';

	//S
	root->left->left->left = (node_t *) malloc(sizeof(node_t));
	root->left->left->left->ch = 'S';


	//H
	root->left->left->left->left = (node_t *) malloc(sizeof(node_t));
	root->left->left->left->left->left = NULL;
	root->left->left->left->left->right = NULL;
	root->left->left->left->left->ch = 'H';

	//V
	root->left->left->left->right = (node_t *) malloc(sizeof(node_t));
	root->left->left->left->right->left = NULL;
	root->left->left->left->right->right = NULL;
	root->left->left->left->right->ch = 'V';


	//U
	root->left->left->right = (node_t *) malloc(sizeof(node_t));
	root->left->left->right->ch = 'U';
	root->left->left->right->right = NULL;



	//F
	root->left->left->right->left = (node_t *) malloc(sizeof(node_t));
	root->left->left->right->left->ch = 'F';
	root->left->left->right->left->right = NULL;
	root->left->left->right->left->left = NULL;

	//A
	root->left->right = (node_t *) malloc(sizeof(node_t));
	root->left->right->ch = 'A';



	//R
	root->left->right->left = (node_t *) malloc(sizeof(node_t));
	root->left->right->left->ch = 'R';
	root->left->right->left->right = NULL;


	//L
	root->left->right->left->left = (node_t *) malloc(sizeof(node_t));
	root->left->right->left->left->ch = 'L';
	root->left->right->left->left->left = NULL;
	root->left->right->left->left->right = NULL;

	//W
	root->left->right->right = (node_t *) malloc(sizeof(node_t));
	root->left->right->right->ch = 'W';


	//P
	root->left->right->right->left = (node_t *) malloc(sizeof(node_t));
	root->left->right->right->left->ch = 'P';
	root->left->right->right->left->left = NULL;
	root->left->right->right->left->right = NULL;

	//J
	root->left->right->right->right = (node_t *) malloc(sizeof(node_t));
	root->left->right->right->right->ch = 'J';
	root->left->right->right->right->left = NULL;
	root->left->right->right->right->right = NULL;



	//T
	root->right = (node_t *) malloc(sizeof(node_t));
	root->right->ch = 'T';


	//N
	root->right->left = (node_t *) malloc(sizeof(node_t));
	root->right->left->ch = 'N';


	//D
	root->right->left->left = (node_t *) malloc(sizeof(node_t));
	root->right->left->left->ch = 'D';

	//B
	root->right->left->left->left = (node_t *) malloc(sizeof(node_t));
	root->right->left->left->left->ch = 'B';
	root->right->left->left->left->left = NULL;
	root->right->left->left->left->right = NULL;

	//X
	root->right->left->left->right = (node_t *) malloc(sizeof(node_t));
	root->right->left->left->right->ch = 'X';
	root->right->left->left->right->left = NULL;
	root->right->left->left->right->right = NULL;

	//K
	root->right->left->right = (node_t *) malloc(sizeof(node_t));
	root->right->left->right->ch = 'K';

	//C
	root->right->left->right->left = (node_t *) malloc(sizeof(node_t));
	root->right->left->right->left->ch = 'C';
	root->right->left->right->left->left = NULL;
	root->right->left->right->left->right = NULL;

	//Y
	root->right->left->right->right = (node_t *) malloc(sizeof(node_t));
	root->right->left->right->right->ch = 'Y';
	root->right->left->right->right->left = NULL;
	root->right->left->right->right->right = NULL;

	//M
	root->right->right = (node_t *) malloc(sizeof(node_t));
	root->right->right->ch = 'M';

	//G
	root->right->right->left = (node_t *) malloc(sizeof(node_t));
	root->right->right->left->ch = 'G';

	//Z
	root->right->right->left->left = (node_t *) malloc(sizeof(node_t));
	root->right->right->left->left->ch = 'Z';
	root->right->right->left->left->left = NULL;
	root->right->right->left->left->right = NULL;


	//Q
	root->right->right->left->right = (node_t *) malloc(sizeof(node_t));
	root->right->right->left->right->ch = 'Q';
	root->right->right->left->right->left = NULL;
	root->right->right->left->right->right = NULL;

	//O
	root->right->right->right = (node_t *) malloc(sizeof(node_t));
	root->right->right->right->ch = 'O';
	root->right->right->right->left = NULL;
	root->right->right->right->right = NULL;

	return root;
}

void process_char()
{
	int i = 0;
	node_t *parent = root;
	node_t *tree = root;
	while (i < buff_index) 
	{
		if (tree != NULL) {
			parent = tree;
			if (buff[i] == '.')
				tree = tree->left;
			else 
				tree =  tree->right;
		} else {
			parent = tree = root;
			buff_index = 0;
			break;
		}
		++i;
	}
	if (tree == NULL) 
		Serial.print(parent->ch);
	else 
		Serial.print(tree->ch);

	buff_index = 0;

}

void preorder(node_t *root)
{
	if (root != NULL) {
		Serial.print(root->ch);
		preorder(root->left);
		preorder(root->right);
	}

}

void setup() {
	pinMode(ctrl_pin_in, INPUT_PULLUP);
	pinMode(out_pin, OUTPUT);
	pinMode(in_pin, OUTPUT);
	pinMode(ir_in,INPUT);
	pinMode(ir_out,OUTPUT);
	Serial.begin(baudrate);
	check = 0;
	n = 200;
	state = 0;
	buff_index = 0;
	root = initialize();
}

void loop() {

	digitalWrite(ir_out,digitalRead(ctrl_pin_in));
	ch = digitalRead(ir_in);


	switch (state) {
		case 0:
			if (ch == 1)
				state = count = 1;
			break;
		case 1:
			if (ch == 1)
				++count;
			else {
				state = 2;
				if ((count < dottime) && (count > antierrortime)) {
					buff[buff_index++] = '.';
				}
				else if(count > antierrortime){
					buff[buff_index++] = '-';
				} 
				count = 0;
			}
			break;
		case 2:
			if (ch == 0) {
				if (count < timeout) 
					++count;
				else {
					process_char();
					state = count = 0;
				}
			} else 
				state = count = 1;
			break;

	}


	if (digitalRead(ctrl_pin_in) == HIGH){
		if (micros()%n < 100){
			digitalWrite(out_pin, HIGH);
			digitalWrite(in_pin, LOW);
		}
		else if (micros()%n >= 100){
			digitalWrite(out_pin, LOW);
			digitalWrite(in_pin, HIGH);
		}

	}
}
