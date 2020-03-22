/* object.c - (c) sarah 2020 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* list of types, as enums */
enum obtypelist_ {
	OB_TYPE_BOOL,
	OB_TYPE_INTEGER,
	OB_TYPE_FLOAT,
	OB_TYPE_DOUBLE,
	OB_TYPE_INVALID
};

/* list of types, as strings for io */
static const char *gszTypeList = {
	"bool",
	"int",
	"float",
	"object",
	"invalid",
};

/* a value container */
typedef struct obvalue_ obvalue;
struct obvalue_ {
	uint8_t	type;	/* numeral index of the data type */
	uint8_t	size;	/* size of the data in bytes */
	void   *data;	/* a pointer to the data itself */
};

/* list of types, as type sizes */
static const int *gszTypeSizeList = {
	sizeof(char),
	sizeof(int),
	sizeof(double),
	sizeof(obvalue),
	-1,
};

/* a hash map, this will unfortunately involve a lot of strcmps */
typedef struct obhash_ obhash;
struct obhash_ {
	char	*name;	/* the name of the hash, null ended */
	obvalue *data;	/* the data this hash points to */
};

/* the object struct itself */
typedef struct object_ object;
struct object_ {
	uint8_t size;	/* the num of values inside this object */
	uint8_t max;	/* the max num of values that could be in this object */
	obhash	*data;	/* the values inside this object, in a hashtable */
};

/* spawns a new obvalue */
obvalue *new_obvalue(uint8_t type) {
	if(type >= OB_TYPE_INVALID) {
		puts("ERROR: " __func__ ": Invalid type");
		return NULL;
	}
	obvalue out = calloc(1, sizeof(obvalue));
	out->type = type;
	out->size = gszTypeSizeList[type];
	out->data = calloc(1, out->size);
}

/* deletes an obvalue */
void delete_obvalue(obvalue *value) {
	if(!value) {
		puts("ERROR: " __func__ ": Invalid pointer");
		return;
	}
	
	free(value->data);
	value->data = NULL;
	free(value);
	value = NULL;
}

/* spawns a new obhash */
obhash *new_obhash(const char *name, obvalue *data) {
	obhash *out = calloc(1, sizeof(obhash));
	out->name = name;
	out->data = data;
	return out;
}

/* deletes an obhash */
void delete_obhash(obhash *hash) {
	if(!hash) {
		puts("ERROR: " __func__ ": Invalid pointer");
		return;
	}
	
	free(hash->name);
	hash->name = NULL;
	free(hash->data);
	hash->data = NULL;
	free(hash);
	hash = NULL;
}

/* pulls a value from an object by its hashtable name */
obvalue *get_from_object(object *obj, const char *property) {
	if(!obj || !property || !obj->data)
		puts("ERROR: " __func__ ": Invalid pointer");
		return;
	}
	
	/* nothing here, bail out */
	if(obj->size <= 0)
		return NULL;
	
	/* we're essentially trusting the size of the object is correct */
	for(int i = 0; i < obj->size; i++) {
		if(!strcmp(property, obj->data[i]))
			return obj->data[i];
	}
	
	/* nothing was found */
	return NULL;
}


