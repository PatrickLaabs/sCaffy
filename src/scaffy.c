#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "create_directory.h"
#include "create_file.h"

int create_project(const char *project_name) {
    char include_dir[256], src_dir[256], build_dir[256], doc_dir[256], test_dir[256], file_path[256];

    // Create directory structure
    sprintf(include_dir, "%s/include", project_name);
    sprintf(src_dir, "%s/src", project_name);
    sprintf(build_dir, "%s/build", project_name);
    sprintf(doc_dir, "%s/doc", project_name);
    sprintf(test_dir, "%s/test", project_name);

    if (create_directory(project_name) != 0) {
        printf("Project directory '%s' already exists.\n", project_name);
        return 1;
    }

    create_directory(project_name);
    create_directory(include_dir);
    create_directory(src_dir);
    create_directory(build_dir);
    create_directory(doc_dir);
    create_directory(test_dir);

    // Create hello.h
    sprintf(file_path, "%s/hello.h", include_dir);
    create_file(
        file_path,
        "#ifndef HELLO_H\n"
        "#define HELLO_H\n\n"
        "void hello(void);\n\n"
        "#endif\n"
    );

    // Create hello.c
    sprintf(file_path, "%s/hello.c", src_dir);
    create_file(
        file_path,
        "#include <stdio.h>\n"
        "#include \"hello.h\"\n\n"
        "void hello(void) {\n"
        "    printf(\"Hello, world!\\n\");\n"
        "}\n"
    );

    // Create main.c
    sprintf(file_path, "%s/main.c", src_dir);
    create_file(
        file_path,
        "#include \"hello.h\"\n\n"
        "int main() {\n"
        "    hello();\n"
        "    return 0;\n"
        "}\n"
    );

    // Create Makefile content
    char makefile_content[1024];
    sprintf(makefile_content,
        "# Makefile\n\n"
        "CC = gcc\n"
        "OPTIONS = -std=c11\n"
        "CFLAGS = -Wall -Iinclude\n"
        "SRC_DIR = src\n"
        "BUILD_DIR = build\n"
        "TARGET = $(BUILD_DIR)/%s\n\n"
        "all: $(TARGET)\n\n"
        "$(TARGET):\n"
        "	$(CC) $(OPTIONS) $(CFLAGS) $(SRC_DIR)/hello.c $(SRC_DIR)/main.c -o $(TARGET)\n\n"
        "$(SRC_DIR)/%%.o: $(SRC_DIR)/%%.c\n"
        "	$(CC) $(OPTIONS) $(CFLAGS) -c $< -o $%%.o\n\n"
        "clean:\n"
        "	rm -f $(TARGET)\n\n"
        ".PHONY: all clean\n",
        project_name
    );

    // Create Makefile
    sprintf(file_path, "%s/Makefile", project_name);
    create_file(file_path, makefile_content);

    printf("Project '%s' scaffold created successfully!\n", project_name);

    return 0;
}

int main(int args, char *argv[]) {
    if (args != 2) {
        fprintf(stderr, "Usage: %s <project_name>\n", argv[0]);
        return 1;
    }

    create_project(argv[1]);
    return 0;
}
