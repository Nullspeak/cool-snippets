/* fake-class.c - (c) sarah 2020 */
#include <stdio.h>
#include <stdlib.h>

typedef struct fakeclass_ fakeclass;
struct fakeclass_ {
	const char *m_szName;
};

void fakeclass_print_name(fakeclass *this) {
	printf("%s\n", this->m_szName);
}

fakeclass *new_fakeclass(const char *newname) {
	fakeclass *out = calloc(1, sizeof(fakeclass));
	out->m_szName = newname;
	return out;
}

void delete_fakeclass(fakeclass *this) {
	free((void *)this);
}

int main() {
	fakeclass *test = new_fakeclass("potato harvester");
	fakeclass_print_name(test);
	delete_fakeclass(test);
	return 0;
}
