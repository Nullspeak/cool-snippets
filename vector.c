/* vector.c - (c) sarah 2020 */
#include <stdio.h>
#include <stdlib.h>

typedef struct _vector_char vector_char;
struct _vector_char {
	int size;
	int capacity;
	char *data;
};

vector_char *new_vector_char(void) {
	vector_char *out = calloc(1, sizeof(vector_char));
	out->size = 0;
	out->capacity = 4;
	out->data = calloc(4, sizeof(char));
	return out;
}

void delete_vector_char(vector_char *this) {
	free(this);
}

char get_vector_char(vector_char *this, int index) {
	/* total invalidity */
	if(!this || index < 0)
		return -1;
	
	/* out-of-bounds */
	if(index > (this->size - 1))
		return -1;
	
	return this->data[index];
}

void set_vector_char(vector_char *this, int index, char val) {
	/* total invalidity */
	if(!this || index < 0)
		return;
	
	/* out-of-bounds */
	if(index > (this->size - 1))
		return;
	
	this->data[index] = val;
}

void push_vector_char(vector_char *this, char val) {
	/* invalid pointer */
	if(!this)
		return;

	/* double the size if we're at the max */
	if(this->size >= this->capacity) {
		this->capacity *= 2;
		this->data = realloc(this->data, this->capacity);
		
		/* error out if we get a bad alloc */
		if(!this->data) {
			printf("%s\n", "ERROR: vector realloc failed!\n");
			exit(-1);
		}
	}

	/* the vector is bigger with the new element */
	this->data[this->size] = val;
	this->size++;
}

/* returns the popped value */
char pop_vector_char(vector_char *this) {
	/* invalid pointer */
	if(!this)
		return -1;
	
	char out = this->data[this->size];
	/* the vector is smaller with the removed element */
	this->size--;

	/* half the size if we're small enough */
	/* if((this->size < (this->capacity / 2)) && (this->size > 0)) { */
	
	/* for now, never shrink */
	if(0) {
		this->capacity /= 2;
		this->data = realloc(this, this->capacity);
		
		/* error out if we get a bad alloc */
		if(!this->data) {
			printf("%s\n", "ERROR: vector realloc failed!\n");
			exit(-1);
		}
	}
	
	return out;
}

void print_vector_char(vector_char *this) {
	/* invalid pointer */
	if(!this)
		return;
	
	/* print a guard */
	printf("%s", "{ ");
	
	/* print each element */
	for(int i = 0; i < this->size; i++) {
		putchar('\'');
		putchar(get_vector_char(this, i));
		putchar('\'');
		putchar(',');
		putchar(' ');
	}
	
	/* print the second guard */
	putchar('}');
}

int main() {
	puts("spawning vector_char..");
	
	vector_char *test = new_vector_char();
	
	printf("test: %p\n", test);
	puts("pushing to vector_char..");
	
	push_vector_char(test, 'H');
	push_vector_char(test, 'e');
	push_vector_char(test, 'l');
	push_vector_char(test, 'l');
	push_vector_char(test, 'o');
	push_vector_char(test, ' ');
	push_vector_char(test, 'W');
	push_vector_char(test, 'o');
	push_vector_char(test, 'r');
	push_vector_char(test, 'l');
	push_vector_char(test, 'd');
	push_vector_char(test, '!');
	pop_vector_char(test);
	
	puts("printing vector_char..");
	
	printf("vector size and capacity: %d, %d, %p\n", test->size, test->capacity, test->data);
	print_vector_char(test);
	
	delete_vector_char(test);
	putchar('\n');
	puts("done");
	return 0;
}
