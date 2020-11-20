#ifndef DARK_FORCE_STRINGS_H
#define DARK_FORCE_STRINGS_H


typedef struct _monoString {
    void *klass;
    void *monitor;
    int length;
    char chars[1];

    int getLength() {
        return length;
    }

    char *getChars() {
        return chars;
    }
} monoString;

monoString *CreateMonoString(const char *str) {
    monoString *(*String_CreateString)(void *instance, const char *str) = (monoString *(*)(void *, const char *))getAbsoluteAddress(0x11D1158); //private unsafe string CreateString(sbyte* value)

    return String_CreateString(NULL, str);
}
