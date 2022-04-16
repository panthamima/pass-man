#ifndef VALIDATION_H
#define VALIDATION_H

#define TCOLOR_R     "\x1b[31;1m"
#define TCOLOR_G     "\x1b[32m"
#define TCOLOR_RESET "\x1b[0m"
#define INCORRECT_FLAG 1

void validate_flags (const int const lenth, const char * const flags[]);
void invoke_commands(const unsigned int count, const char* const commands[]);

#endif