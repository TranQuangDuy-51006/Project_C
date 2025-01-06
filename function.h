#include "datatype.h"
#include <string.h>


void printMenuHome();
void printMenu();
void inputMenu();
void printMenu();
void printStudentMenu();
void printExit();
void printStudent(struct Student user[], int n);
void addStudent(struct Student user[], int *n);
void editStudent(struct Student user[], int n);
void deleteStudent(struct Student user[], int *n);
const char* getLastName(const char *fullName);
void sortStudent(struct Student user[], int n);
void saveStudentsToFile(const char *fileName, struct Student *list, int size);
int loadStudentFormFile(const char *fileName, struct Student *user);
void searchStudent(struct Student user[], int n);
void inputTeacherMenu();
void printTeachertMenu();
void printTeacher(struct Teacher teacher[], int n);
void addTeacher(struct Teacher teacher[], int *n);
void editTeacher(struct Teacher teacher[], int n);
void deleteTeacher(struct Teacher teacher[], int *n);
void searchTeacher(struct Teacher teacher[], int n);
void saveTeachersToFile(const char *fileName, struct Teacher *list, int size);
int loadTeachersFormFile(const char *fileName, struct Teacher *teacher);
