#include <loxVM.h>
#include <loxCLI.h>
#include <loxScanner.h>
#include <loxCompiler.h>
#include <oneFileSTD.h>

LoxResult lox_Repl() {
    LoxCompiler compiler;
    LoxCompiler_init(&compiler);
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
        LoxCompiler_compile(&compiler, line, NULL);
        // loxInterpret
        // lox_runFile(buf);
    }
    LoxCompiler_free(&compiler);
    LoxVM_free(&vm);
}

LoxResult lox_runFile(const char* filename) {
    char* source = readFile(filename);
    if (!source) 
        return LOX_INTERPRET_COMPILE_ERROR;
    // execute
    LoxCompiler compiler;
    LoxCompiler_init(&compiler);
    LoxCompiler_compile(&compiler, source, NULL);
    LoxVM vm;
    LoxVM_init(&vm);
    // loxInterpret
    LoxCompiler_free(&compiler);
    LoxVM_free(&vm);
    free(source);
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

