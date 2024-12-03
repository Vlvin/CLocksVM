#include <loxVM.h>
#include <loxCLI.h>
#include <loxScanner.h>
#include <loxCompiler.h>
#include <oneFileSTD.h>

LoxResult lox_Repl() {
    LoxVM vm;
    LoxVM_init(&vm);
    while (true) {
        // readline
        printf("%s", "clox >> ");
        char line[256] = {};
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        // execute
        LoxResult result = LoxVM_interpret(&vm, line);
        if (result != LOX_INTERPRET_OK) {
            Lox_VM_printResult(result);
        }
        // loxInterpret
        // lox_runFile(buf);
    }
    LoxVM_free(&vm);
}

LoxResult lox_runFile(const char* filename) {
    char* source = readFile(filename);
    if (!source) 
        return LOX_INTERPRET_COMPILE_ERROR;
    // execute
    LoxVM vm;
    LoxVM_init(&vm);

    LoxResult result = LoxVM_interpret(&vm, source);

    // loxInterpret
    LoxVM_free(&vm);
    free(source);
    return result;
}


/// @brief reads file at [filename]
/// @param filename is path to file
/// @return 
char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open \"%s\"\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    if (!size) {
        fprintf(stderr, "File \"%s\" is empty\n", filename);
        return NULL;
    }

    char *buffer = (char*)malloc(size+1);
    if (!buffer) {
        fprintf(stderr, "Not enough memory to read \"%s\"\n", filename);
        return NULL;
    }
    buffer[size] = '\0';
    size_t bytesRead = fread(buffer, 1, size, file);
    if (bytesRead < size) {
        fprintf(stderr, "Failed to read \"%s\"\n", filename);
        return NULL;
    }

    fclose(file);

    return buffer;
} 

