/* callbacks.c - (c) sarah 2020 */
#include <stdio.h>

/* callback type, (eventtype, eventdata) */
typedef void (*callback_t)(int, void *);

void callback1(int event, void *data) {
	printf("callback1(%d, %p)\n", event, data);
}

void callback2(int event, void *data) {
	printf("callback2(%d, %p)\n", event, data);
}

void callback3(int event, void *data) {
	printf("callback3(%d, %p)\n", event, data);
}

void callback4(int event, void *data) {
	printf("callback4(%d, %p)\n", event, data);
}

/* list of callbacks */
static callback_t gsCallbacks[] = {
	callback1,
	callback2,
	callback3,
	callback4,
};

int main() {
	int dat = 0x10;
	for(int i = 0; i < 4; i++)
		gsCallbacks[i](i, &dat);

	return 0;
}
