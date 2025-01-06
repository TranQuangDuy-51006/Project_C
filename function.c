#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"


void printMenuHome(){
	printf("\n");
	printf("\t   CHOOSE YOUR ROLE\n");
	printf("\t======================\n");
	printf("\t[1] Admin.\n");
	printf("\t[0] Exit the program.\n");
	printf("\t======================\n");
}
void printMenu(){
	printf("\n");
	printf("\t\tMENU\n");
	printf("\t======================\n");
	printf("\t[1] Student management.\n");
	printf("\t[2] Teacher management.\n");
	printf("\t[0] Exit the menu.\n");
	printf("\t======================\n");
}
void inputMenu(){
	int choice;
	do{
		printMenu();
		printf("\tEnter the choice: ");
		scanf("%d", &choice);
		printf("\n");
		fflush(stdin);
		switch(choice){
			case 1:
				system("cls");
				inputStudentMenu();
				break;
			case 2:
				system("cls");
				inputTeacherMenu();
				break;
			case 0:
				system("cls");
				break;
			default:
				system("cls");
				printf("\tError: Wrong syntax!\n");
		}
	}while(choice != 0);
}
void inputStudentMenu(){
	struct Student user[1000];
	const char *file = "students.dat";
	int n = 0;
	int choice;
	do{
		n = loadStudentFormFile(file,user);
		printStudentMenu();
		printf("\tEnter the choice: ");
		scanf("%d", &choice);
		printf("\n");
		fflush(stdin);
		switch(choice){
			case 1:
				system("cls");
				addStudent(user,&n);
				break;
			case 2:
				system("cls");
				n = loadStudentFormFile(file,user);
				printStudent(user,n);
				break;
			case 3:
				system("cls");
				searchStudent(user, n);
				break;
			case 4:
				system("cls");
				editStudent(user, n);
				break;
			case 5:
				system("cls");
				deleteStudent(user,&n);
				break;
			case 6:
				system("cls");
				sortStudent(user,n);
				break;
			case 0:
				system("cls");
				break;
			default:
				system("cls");
				printf("\tError: Wrong syntax!\n");
		}
	}while(choice != 0);
}
void printStudentMenu(){
	printf("\n");
	printf("\t   STUDENT MENU\n");
	printf("\t======================\n");
	printf("\t[1] Add a new student.\n");
	printf("\t[2] Show all student.\n");
	printf("\t[3] Search a student.\n");
	printf("\t[4] Edit a student.\n");
	printf("\t[5] Delete a student.\n");
	printf("\t[6] Sort all students by name.\n");
	printf("\t[0] Exit the menu student.\n");
	printf("\t======================\n");
}
void printExit(){
	printf("\t====Thank You======\n");
	printf("\t====See You Soon===");
	printf("\n");
}
void printStudent(struct Student user[], int n){
	char choice[1];
	int i;
	printf("\t\t\t\t\t\t\t\t\t**All student**\n\n");
	printf("\t|=================|=====================================|=====================================|===========================|\n");
    printf("\t| %-15s | %-35s | %-35s | %-25s |\n", "ID", "Name", "Email", "Phone");
    printf("\t|=================|=====================================|=====================================|===========================|\n");
    for (i = 0; i < n; i++) {
        printf("\t| %-15d | %-35s | %-35s | %-25s |\n",
		user[i].id,
		user[i].name,
		user[i].email,
		user[i].phone);
        printf("\t|-----------------|-------------------------------------|-------------------------------------|---------------------------|\n");
    }
    end:
	printf("\tGo back(b)? or Exit(0)?:");
	scanf("%s", &choice);
	fflush(stdin);
	if(strcmp(choice,"b")==0){
		system("cls");
	}else if(strcmp(choice,"0")==0){
		printExit();
		exit(0);
	}else{
		goto end;
	}

}
void addStudent(struct Student user[], int *n){
	int same = 0;
	const char *file = "students.dat";
	int add = *n;
	char choice[1];
	int i;
	char afterGmail[] = "@gmail.com";
	printf("\t\t**Add a new student**\n");
	addStudent:
	printf("\tEnter the ID: ");
	int check = 0;
	scanf("%d", &user[add].id);
	fflush(stdin);
	for(i = 0; i < *n; i++){
		if(user[add].id == user[i].id||user[add].id < 1||user[add].id > 1000){
			check = 1;
		}
	}
	if(check != 1){
		addName:
		printf("\tEnter the Name: ");
		fgets(user[add].name, sizeof(user[add].name), stdin);
		user[add].name[strcspn(user[add].name,"\n")] = '\0';
		for(i=0;i<strlen(user[add].name);i++){		
			if(user[add].name[i]== 32&&user[add].name[i+1]==32){
				printf("\tError: This Name is not valid.\n");
				goto addName;	
			}
			if((user[add].name[i] < 65 ||user[add].name[i] > 122)&&user[add].name[i]!= 32){
				printf("\tError: This Name is not valid.\n");
				goto addName;
			}
		}
		if(user[add].name[0]== 32||strlen(user[add].name) < 1){
			printf("\tError: This Name is not valid.\n");
			goto addName;	
		}
		saveStudentsToFile(file, user, *n);
		addMail:
		printf("\tEnter the Email: ");
		fgets(user[add].email, sizeof(user[add].email), stdin);
		user[add].email[strcspn(user[add].email,"\n")] = '\0';
		int same = 0;
		for(i = 0; i < *n; i++){
			if(strcmp(user[add].email, user[i].email) == 0){
				same = 1;
			}
		}
		if(same == 1){
			printf("\tError: This Email is already exists.\n");
			goto addMail;
		}
		for(i=0;i<strlen(user[add].email);i++){		
			if(user[add].email[i]== 32){
				printf("\tError: This Email is not valid.\n");
				goto addMail;		
			}
		}
		int len = strlen(user[add].email);
		int emailLen = strlen(afterGmail);
		if (len <= emailLen){
			printf("\tError: This Email is not valid.\n");
			goto addMail;
		}
		if (strcmp(user[add].email + len - emailLen, afterGmail) != 0){
			printf("\tError: This Email is not valid.\n");
			goto addMail;
		}
		addPhone:
		printf("\tEnter the Phone: ");
		same = 0;
		fgets(user[add].phone, sizeof(user[add].phone), stdin);
		user[add].phone[strcspn(user[add].phone,"\n")] = '\0';
		for(i = 0; i < *n; i++){
			if(strcmp(user[add].phone, user[i].phone) == 0){
				same = 1;
			}
		}
		if(same == 1){
			printf("\tError: This Phone is already exists.\n");
			goto addPhone;
		}
		for(i=0;i<strlen(user[add].phone);i++){		
			if(user[add].phone[i]== 32) {
				printf("\tError: This Phone is not valid.\n");
				goto addPhone;		
			}
		}
		if (strlen(user[add].phone)!=10) {
			printf("\tError: This Phone is not valid.\n");
	        goto addPhone;
	    }
	    for (i = 0; i < strlen(user[add].phone); i++){
	        if (user[add].phone[i] < '0' || user[add].phone[i] > '9'){
	        	printf("\tError: This Phone is not valid.\n");
	            goto addPhone;
	        }
	    }
		(*n)++;
		printf("\tAdded successfully!!\n");
		saveStudentsToFile(file, user, *n);
		end:
		printf("\tGo back(b)? or Exit(0)?:");
		scanf("%s", &choice);
		fflush(stdin);
		if(strcmp(choice,"b")==0){
			system("cls");
		}else if(strcmp(choice,"0")==0){
			printExit();
			exit(0);
		}else{
			goto end;
		}
	}else{
		printf("\tError: This ID is not valid.\n");
		goto addStudent;
	}
}
void editStudent(struct Student user[], int n){
	const char *file = "students.dat";
	char afterGmail[] = "@gmail.com";
	int i, edit; 
	char choice[1];
	editStudent:
	printf("\t\t**Edit student**\n");
	int searchId;
	printf("\tEnter the ID student: ");
	scanf("%d", &searchId);
	int check = 0;
	fflush(stdin);
	printf("\tStudent Infomations\n");
	printf("\t----------------------\n");
	for(i = 0; i < n; i++){
		if(searchId == user[i].id){
			check = 1;
			edit = i;
			printf("\tID: %d\n", user[i].id);
			printf("\tName: %s\n", user[i].name);
			printf("\tEmail: %s\n", user[i].email);
			printf("\tPhone: %s\n", user[i].phone);
		}
	}
	if(check == 1){
		printf("\t\t**Update The New Student**\n");
		char temp[100];
		editName:
		printf("\tEnter the new name(0 for skip): ");
		strcpy(temp, user[edit].name);
		fgets(user[edit].name, sizeof(user[edit].name), stdin);
		user[edit].name[strcspn(user[edit].name,"\n")] = '\0';
		if(strcmp(user[edit].name, "0") == 0&&strlen(user[edit].name)==1){
			strcpy(user[edit].name, temp);
		}
		for(i=0;i<strlen(user[edit].name);i++){
			if(user[edit].name[i]== 32&&user[edit].name[i+1]==32){
				printf("\tError: This Name is not valid.\n");
				goto editName;	
			}
			if((user[edit].name[i] < 65 ||user[edit].name[i] > 122)&&user[edit].name[i]!= 32){
				printf("\tError: This Name is not valid.\n");
				goto editName;
			}
		}
		if(user[edit].name[0]== 32||strlen(user[edit].name) < 1){
			printf("\tError: This Name is not valid.\n");
			goto editName;	
		}
		saveStudentsToFile(file, user, n);
		editMail:
		printf("\tEnter the new email(0 for skip): ");
		strcpy(temp, user[edit].email);
		fgets(user[edit].email, sizeof(user[edit].email), stdin);
		user[edit].email[strcspn(user[edit].email,"\n")] = '\0';
		if(strcmp(user[edit].email, "0") == 0&&strlen(user[edit].email)==1){
			strcpy(user[edit].email, temp);
		}
		int same = 0;
		for(i = 0; i < n; i++){
			if(strcmp(user[edit].email, user[i].email) == 0&&edit != i){
				same = 1;
			}
		}
		if(same == 1){
			printf("\tError: This Email is already exists.\n");
			strcpy(user[edit].email, temp);
			goto editMail;
		}
		for(i=0;i<strlen(user[edit].email);i++){		
			if(user[edit].email[i]== 32){
				strcpy(user[edit].email, temp);
				goto editMail;		
			}
		}
		int len = strlen(user[edit].email);
		int emailLen = strlen(afterGmail);
		if (len <= emailLen){
			strcpy(user[edit].email, temp);
			goto editMail;
		}
		if (strcmp(user[edit].email + len - emailLen, afterGmail) != 0){
			strcpy(user[edit].email, temp);
			goto editMail;
		}
		editPhone:
		same = 0;
		printf("\tEnter the new phone(0 for skip): ");
		strcpy(temp, user[edit].phone);
		fgets(user[edit].phone, sizeof(user[edit].phone), stdin);
		user[edit].phone[strcspn(user[edit].phone,"\n")] = '\0';
		if(strcmp(user[edit].phone, "0") == 0){
			strcpy(user[edit].phone, temp);
			goto end;
		}
		for(i = 0; i < n; i++){
			if(strcmp(user[edit].phone, user[i].phone) == 0&&edit != i){
				same = 1;
			}
		}
		if(same == 1){
			printf("\tError: This Phone is already exists.\n");
			goto editPhone;
		}
		for(i = 0;i<strlen(user[edit].phone);i++){		
			if(user[edit].phone[i]== 32) {
				strcpy(user[edit].phone, temp);
				goto editPhone;		
			}
		}
		if (strlen(user[edit].phone)!=10) {
			strcpy(user[edit].phone, temp);
	        goto editPhone;
	    }
	    for (i = 0; i < strlen(user[edit].phone); i++){
	        if (user[edit].phone[i] < '0' || user[edit].phone[i] > '9'){
	        	strcpy(user[edit].phone, temp);
	            goto editPhone;
	        }
	    }
		saveStudentsToFile(file, user, n);
		printf("\tUpdate successfully!!\n\n");
		end:
		printf("\tGo back(b)? or Exit(0)?:");
		scanf("%s", &choice);
		fflush(stdin);
		if(strcmp(choice,"b")==0){
			system("cls");
		}else if(strcmp(choice,"0")==0){
			printExit();
			exit(0);
		}else{
			goto end;
		}
	}else{
		printf("\tError: This ID is not valid.\n\n");
		goto editStudent;
	}
}
void deleteStudent(struct Student user[], int *n){
	const char *file = "students.dat";
	char choice[1];
	char YN[1];
	int dlt = *n;
	int i, searchId, location;
	printf("\t\t**Delete a new student**\n");
	deleteStudent:
	printf("\tEnter the ID: ");
	int check = 0;
	scanf("%d", &searchId);
	fflush(stdin);
	printf("\tStudent Infomations\n");
	printf("\t----------------------\n");
	for(i = 0; i < *n; i++){
		if(searchId == user[i].id){
			check = 1;
			location = i;
			printf("\tID: %d\n", user[i].id);
			printf("\tName: %s\n", user[i].name);
			printf("\tEmail: %s\n", user[i].email);
			printf("\tPhone: %s\n", user[i].phone);
		}
	}
	if(check == 1){
		goBackDelete:
		printf("\tAre you sure want to delete this student? (Y/N): ");
		scanf("%s", &YN);
		strupr(YN);
		if(strcmp(YN, "Y")==0){
			for(i = location; i < *n; i++){
				user[i] = user[i + 1];
			}
			(*n)--;
			printf("\tSuccessfully deleted student information!!\n");
		}else if(strcmp(YN, "N")==0){
			printf("\tDeleting student information failed!!\n");
		}else{
			goto goBackDelete;
		}
		saveStudentsToFile(file, user, *n);
		end:
		printf("\tGo back(b)? or Exit(0)?:");
		scanf("%s", &choice);
		fflush(stdin);
		if(strcmp(choice,"b")==0){
			system("cls");
		}else if(strcmp(choice,"0")==0){
			printExit();
			exit(0);
		}else{
			goto end;
		}		
	}else{
		printf("\tError: This ID is not valid.\n");
		goto deleteStudent;
	}
}
const char* getLastName(const char *fullName){
    const char *lastName = strrchr(fullName, ' ');
    if(lastName == NULL){
    	return fullName;
	}else{
		return lastName + 1;
	}
}
void sortStudent(struct Student user[], int n){
	int i;
	int j;
	char choice[1];
	char YN[1];
	goBackSort:
	printf("\t\t**Sort all student**\n");
	printf("\tAre you sure you want to sort all students? (Y/N): ");
	scanf("%s", &YN);
	strupr(YN);
	if(strcmp(YN, "Y")==0){
		for (i = 0; i < n - 1; i++) {
	        for (j = 0; j < n - i - 1; j++) {
	            if (strcmp(getLastName(user[j].name), getLastName(user[j + 1].name)) > 0) {
	                struct Student temp = user[j];
	                user[j] = user[j + 1];
	                user[j + 1] = temp;
	            }
	        }
	    }
		printf("\tSuccessfully!!\n");
		printf("\t|=================|=====================================|=====================================|===========================|=================|\n");
	    printf("\t| %-15s | %-35s | %-35s | %-25s | %-15s |\n", "ID", "Name", "Email", "Phone", "NO.Course");
	    printf("\t|=================|=====================================|=====================================|===========================|=================|\n");
	    for (i = 0; i < n; i++) {
	        printf("\t| %-15d | %-35s | %-35s | %-25s | %-15d |\n",
			user[i].id,
			user[i].name,
			user[i].email,
			user[i].phone,
			user[i].no_course);
	        printf("\t|-----------------|-------------------------------------|-------------------------------------|---------------------------|-----------------|\n");
	    }
	}else if(strcmp(YN, "N")==0){
		printf("\tFailed!!\n");
	}else{
		goto goBackSort;
	}
    end:
	printf("\tGo back(b)? or Exit(0)?:");
	scanf("%s", &choice);
	fflush(stdin);
	if(strcmp(choice,"b")==0){
		system("cls");
	}else if(strcmp(choice,"0")==0){
		printExit();
		exit(0);
	}else{
		goto end;
	}		
}
void saveStudentsToFile(const char *fileName, struct Student *list, int size){
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        exit(1);
    }
    fwrite(list, sizeof(struct Student), size, file);
    fclose(file);
}
int loadStudentFormFile(const char *fileName, struct Student *user){
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        return 0;
    }
    int n = 0;
    while (fread(&user[n], sizeof(struct Student), 1, file) == 1) {
        n++;
    }
    fclose(file);
    return n;
}
void searchStudent(struct Student user[], int n){
	char choice[1];
    int check = 0;
	int i;
    char search[100];
    printf("\t\t**Search student**\n");
    printf("\tName:");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search,"\n")] = '\0';
    printf("\t|=================|=====================================|=====================================|===========================|=================|\n");
    printf("\t| %-15s | %-35s | %-35s | %-25s | %-15s |\n", "ID", "Name", "Email", "Phone", "NO.Course");
    printf("\t|=================|=====================================|=====================================|===========================|=================|\n");
    for (i = 0; i < n; i++) {
        if(strstr(user[i].name, search) != NULL) {
        	printf("\t| %-15d | %-35s | %-35s | %-25s | %-15d |\n",
			user[i].id,
			user[i].name,
			user[i].email,
			user[i].phone,
			user[i].no_course);
			printf("\t|-----------------|-------------------------------------|-------------------------------------|---------------------------|-----------------|\n");
            check = 1;
        }
    }
    if (check==0) {
        printf("\tNot found\n");
    }
    end:
	printf("\tGo back(b)? or Exit(0)?:");
	scanf("%s", &choice);
	fflush(stdin);
	if(strcmp(choice,"b")==0){
		system("cls");
	}else if(strcmp(choice,"0")==0){
		printExit();
		exit(0);
	}else{
		goto end;
	}	
}
void inputTeacherMenu(){
	struct Teacher teacher[1000];
	const char *file = "teachers.dat";
	int n = 0;
	int choice;
	do{
		n = loadTeachersFormFile(file, teacher);
		printTeachertMenu();
		printf("\tEnter the choice: ");
		scanf("%d", &choice);
		printf("\n");
		fflush(stdin);
		switch(choice){
			case 1:
				system("cls");
				addTeacher(teacher, &n);
				break;
			case 2:
				system("cls");
				n = loadTeachersFormFile(file, teacher);
				printTeacher(teacher, n);
				break;
			case 3:
				system("cls");
				editTeacher(teacher, n);
				break;
			case 4:
				system("cls");
				deleteTeacher(teacher, &n);
				break;
			case 5:
				system("cls");
				searchTeacher(teacher, n);
				break;
			case 0:
				system("cls");
				break;
			default:
				system("cls");
				printf("\tError: Wrong syntax!\n");
		}
	}while(choice != 0);
}
void printTeachertMenu(){
	printf("\n");
	printf("\t   TEACHER MENU\n");
	printf("\t======================\n");
	printf("\t[1] Add a teacher.\n");
	printf("\t[2] Show all teacher.\n");
	printf("\t[3] Edit a teacher.\n");
	printf("\t[4] Delete a teacher.\n");
	printf("\t[5] Search a teacher.\n");
	printf("\t[0] Exit the menu teacher.\n");
	printf("\t======================\n");
}
void printTeacher(struct Teacher teacher[], int n){
	char choice[1];
	int i;
	printf("\t\t\t\t\t\t\t\t**All teacher**\n\n");
	printf("\t|=================|=====================================|=====================================|===========================|\n");
    printf("\t| %-15s | %-35s | %-35s | %-25s |\n", "ID", "Name", "Email", "Phone");
    printf("\t|=================|=====================================|=====================================|===========================|\n");
    for (i = 0; i < n; i++) {
        printf("\t| %-15d | %-35s | %-35s | %-25s |\n",
		teacher[i].id,
		teacher[i].name,
		teacher[i].email,
		teacher[i].phone);
        printf("\t|-----------------|-------------------------------------|-------------------------------------|---------------------------|\n");
    }
    end:
	printf("\tGo back(b)? or Exit(0)?:");
	scanf("%s", &choice);
	fflush(stdin);
	if(strcmp(choice,"b")==0){
		system("cls");
	}else if(strcmp(choice,"0")==0){
		printExit();
		exit(0);
	}else{
		goto end;
	}
}
void addTeacher(struct Teacher teacher[], int *n){
	const char *file = "teachers.dat";
	int add = *n;
	char choice[1];
	int i;
	char afterGmail[] = "@gmail.com";
	printf("\t\t**Add a new teacher**\n");
	addTeacher:
	printf("\tEnter the ID: ");
	int check = 0;
	scanf("%d", &teacher[add].id);
	fflush(stdin);
	for(i = 0; i < *n; i++){
		if(teacher[add].id == teacher[i].id||teacher[add].id < 1||teacher[add].id > 1000){
			check = 1;
		}
	}
	if(check != 1){
		addName:
		printf("\tEnter the Name: ");
		fgets(teacher[add].name, sizeof(teacher[add].name), stdin);
		teacher[add].name[strcspn(teacher[add].name,"\n")] = '\0';
		for(i=0;i<strlen(teacher[add].name);i++){		
			if(teacher[add].name[i]== 32&&teacher[add].name[i+1]==32){
				printf("\tError: This Name is not valid.\n");
				goto addName;	
			}
			if((teacher[add].name[i] < 65 ||teacher[add].name[i] > 122)&&teacher[add].name[i]!= 32){
				printf("\tError: This Name is not valid.\n");
				goto addName;
			}
		}
		if(teacher[add].name[0]== 32||strlen(teacher[add].name) < 1){
			printf("\tError: This Name is not valid.\n");
			goto addName;	
		}
		addMail:
		printf("\tEnter the Email: ");
		fgets(teacher[add].email, sizeof(teacher[add].email), stdin);
		teacher[add].email[strcspn(teacher[add].email,"\n")] = '\0';
		int same = 0;
		for(i = 0; i < *n; i++){
			if(strcmp(teacher[add].email, teacher[i].email) == 0){
				same = 1;
			}
		}
		if(same == 1){
			printf("\tError: This Email is already exists.\n");
			goto addMail;
		}
		for(i=0;i<strlen(teacher[add].email);i++){		
			if(teacher[add].email[i]== 32){
				printf("\tError: This Email is not valid.\n");
				goto addMail;		
			}
		}
		int len = strlen(teacher[add].email);
		int emailLen = strlen(afterGmail);
		if (len <= emailLen){
			printf("\tError: This Email is not valid.\n");
			goto addMail;
		}
		if (strcmp(teacher[add].email + len - emailLen, afterGmail) != 0){
			printf("\tError: This Email is not valid.\n");
			goto addMail;
		}
		addPhone:
		printf("\tEnter the Phone: ");
		same = 0;
		fgets(teacher[add].phone, sizeof(teacher[add].phone), stdin);
		teacher[add].phone[strcspn(teacher[add].phone,"\n")] = '\0';
		for(i = 0; i < *n; i++){
			if(strcmp(teacher[add].phone, teacher[i].phone) == 0){
				same = 1;
			}
		}
		if(same == 1){
			printf("\tError: This Phone is already exists.\n");
			goto addPhone;
		}
		for(i=0;i<strlen(teacher[add].phone);i++){		
			if(teacher[add].phone[i]== 32) {
				printf("\tError: This Phone is not valid.\n");
				goto addPhone;		
			}
		}
		if (strlen(teacher[add].phone)!=10) {
			printf("\tError: This Phone is not valid.\n");
	        goto addPhone;
	    }
	    for (i = 0; i < strlen(teacher[add].phone); i++){
	        if (teacher[add].phone[i] < '0' || teacher[add].phone[i] > '9'){
	        	printf("\tError: This Phone is not valid.\n");
	            goto addPhone;
	        }
	    }
		(*n)++;
		printf("\tAdded successfully!!\n");
		saveTeachersToFile(file, teacher, *n);
		end:
		printf("\tGo back(b)? or Exit(0)?:");
		scanf("%s", &choice);
		fflush(stdin);
		if(strcmp(choice,"b")==0){
			system("cls");
		}else if(strcmp(choice,"0")==0){
			printExit();
			exit(0);
		}else{
			goto end;
		}
	}else{
		printf("\tError: This ID is not valid.\n");
		goto addTeacher;
	}
}
void editTeacher(struct Teacher teacher[], int n){
    const char *file = "teachers.dat";
    char afterGmail[] = "@gmail.com";
    int i, edit; 
    char choice[1];
    editTeacher:
    printf("\t\t**Edit teacher**\n");
    int searchId;
    printf("\tEnter the ID teacher: ");
    scanf("%d", &searchId);
    int check = 0;
    fflush(stdin);
    printf("\tTeacher Infomations\n");
    printf("\t----------------------\n");
    for(i = 0; i < n; i++){
        if(searchId == teacher[i].id){
            check = 1;
            edit = i;
            printf("\tID: %d\n", teacher[i].id);
            printf("\tName: %s\n", teacher[i].name);
            printf("\tEmail: %s\n", teacher[i].email);
            printf("\tPhone: %s\n", teacher[i].phone);
        }
    }
    if(check == 1){
        printf("\t\t**Update The New Teacher**\n");
        char temp[100];
        editName:
        printf("\tEnter the new name(0 for skip): ");
        strcpy(temp, teacher[edit].name);
        fgets(teacher[edit].name, sizeof(teacher[edit].name), stdin);
        teacher[edit].name[strcspn(teacher[edit].name,"\n")] = '\0';
        if(strcmp(teacher[edit].name, "0") == 0){
            strcpy(teacher[edit].name, temp);
        }
        for(i=0;i<strlen(teacher[edit].name);i++){        
            if(teacher[edit].name[i]== 32 && teacher[edit].name[i+1]==32){
                printf("\tError: This Name is not valid.\n");
                goto editName;    
            }
            if((teacher[edit].name[i] < 65 || teacher[edit].name[i] > 122) && teacher[edit].name[i]!= 32){
                printf("\tError: This Name is not valid.\n");
                goto editName;
            }
        }
        if(teacher[edit].name[0]== 32 || strlen(teacher[edit].name) < 1){
            printf("\tError: This Name is not valid.\n");
            goto editName;    
        }
        saveTeachersToFile(file, teacher, n);
        editMail:
        printf("\tEnter the new email(0 for skip): ");
        strcpy(temp, teacher[edit].email);
        fgets(teacher[edit].email, sizeof(teacher[edit].email), stdin);
        teacher[edit].email[strcspn(teacher[edit].email,"\n")] = '\0';
        if(strcmp(teacher[edit].email, "0") == 0 && strlen(teacher[edit].email)==1){
            strcpy(teacher[edit].email, temp);
        }
        int same = 0;
        for(i = 0; i < n; i++){
            if(strcmp(teacher[edit].email, teacher[i].email) == 0 && edit != i){
                same = 1;
            }
        }
        if(same == 1){
            printf("\tError: This Email is already exists.\n");
            strcpy(teacher[edit].email, temp);
            goto editMail;
        }
        for(i=0;i<strlen(teacher[edit].email);i++){        
            if(teacher[edit].email[i]== 32){
                strcpy(teacher[edit].email, temp);
                goto editMail;        
            }
        }
        int len = strlen(teacher[edit].email);
        int emailLen = strlen(afterGmail);
        if (len <= emailLen){
            strcpy(teacher[edit].email, temp);
            goto editMail;
        }
        if (strcmp(teacher[edit].email + len - emailLen, afterGmail) != 0){
            strcpy(teacher[edit].email, temp);
            goto editMail;
        }
        editPhone:
        printf("\tEnter the new phone(0 for skip): ");
        strcpy(temp, teacher[edit].phone);
        fgets(teacher[edit].phone, sizeof(teacher[edit].phone), stdin);
        teacher[edit].phone[strcspn(teacher[edit].phone,"\n")] = '\0';
        if(strcmp(teacher[edit].phone, "0") == 0){
            strcpy(teacher[edit].phone, temp);
            goto end;
        }
        same = 0;
        for(i = 0; i < n; i++){
            if(strcmp(teacher[edit].phone, teacher[i].phone) == 0 && edit != i){
                same = 1;
            }
        }
        if(same == 1){
            printf("\tError: This Phone is already exists.\n");
            strcpy(teacher[edit].phone, temp);
            goto editPhone;
        }
        for(i = 0;i<strlen(teacher[edit].phone);i++){        
            if(teacher[edit].phone[i]== 32) {
                strcpy(teacher[edit].phone, temp);
                goto editPhone;        
            }
        }
        if (strlen(teacher[edit].phone)!=10) {
            strcpy(teacher[edit].phone, temp);
            goto editPhone;
        }
        for (i = 0; i < strlen(teacher[edit].phone); i++){
            if (teacher[edit].phone[i] < '0' || teacher[edit].phone[i] > '9'){
                strcpy(teacher[edit].phone, temp);
                goto editPhone;
            }
        }
        printf("\tUpdate successfully!!\n\n");
        saveTeachersToFile(file, teacher, n);
        end:
        printf("\tGo back(b)? or Exit(0)?:");
        scanf("%s", &choice);
        fflush(stdin);
        if(strcmp(choice,"b")==0){
            system("cls");
        }else if(strcmp(choice,"0")==0){
            printExit();
            exit(0);
        }else{
            goto end;
        }
    }else{
        printf("\tError: This ID is not valid.\n\n");
        goto editTeacher;
    }
}
void deleteTeacher(struct Teacher teacher[], int *n){
    const char *file = "teachers.dat";
    char choice[1];
    char YN[1];
    int dlt = *n;
    int i, searchId, location;
    printf("\t\t**Delete a new teacher**\n");
    deleteTeacher:
    printf("\tEnter the ID: ");
    int check = 0;
    scanf("%d", &searchId);
    fflush(stdin);
    printf("\tTeacher Infomations\n");
    printf("\t----------------------\n");
    for(i = 0; i < *n; i++){
        if(searchId == teacher[i].id){
            check = 1;
            location = i;
            printf("\tID: %d\n", teacher[i].id);
            printf("\tName: %s\n", teacher[i].name);
            printf("\tEmail: %s\n", teacher[i].email);
            printf("\tPhone: %s\n", teacher[i].phone);
        }
    }
    if(check == 1){
        goBackDelete:
        printf("\tAre you sure want to delete this teacher? (Y/N): ");
        scanf("%s", &YN);
        strupr(YN);
        if(strcmp(YN, "Y") == 0){
            for(i = location; i < *n; i++){
                teacher[i] = teacher[i + 1];
            }
            (*n)--;
            printf("\tSuccessfully deleted teacher information!!\n");
        }else if(strcmp(YN, "N") == 0){
            printf("\tDeleting teacher information failed!!\n");
        }else{
            goto goBackDelete;
        }
        saveTeachersToFile(file, teacher, *n);
        end:
        printf("\tGo back(b)? or Exit(0)?:");
        scanf("%s", &choice);
        fflush(stdin);
        if(strcmp(choice,"b") == 0){
            system("cls");
        }else if(strcmp(choice,"0") == 0){
            printExit();
            exit(0);
        }else{
            goto end;
        }        
    }else{
        printf("\tError: This ID is not valid.\n");
        goto deleteTeacher;
    }
}
void searchTeacher(struct Teacher teacher[], int n){
	char choice[1];
    int check = 0;
	int i;
    char search[100];
    printf("\t\t**Search teacher**\n");
    printf("\tName:");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search,"\n")] = '\0';
    printf("\t|=================|=====================================|=====================================|===========================|\n");
    printf("\t| %-15s | %-35s | %-35s | %-25s |\n", "ID", "Name", "Email", "Phone");
    printf("\t|=================|=====================================|=====================================|===========================|\n");
    for (i = 0; i < n; i++) {
        if(strstr(teacher[i].name, search) != NULL) {
        	printf("\t| %-15d | %-35s | %-35s | %-25s |\n",
			teacher[i].id,
			teacher[i].name,
			teacher[i].email,
			teacher[i].phone);
			printf("\t|-----------------|-------------------------------------|-------------------------------------|---------------------------|\n");
            check = 1;
        }
    }
    if (check==0) {
        printf("\tNot found\n");
    }
    end:
	printf("\tGo back(b)? or Exit(0)?:");
	scanf("%s", &choice);
	fflush(stdin);
	if(strcmp(choice,"b")==0){
		system("cls");
	}else if(strcmp(choice,"0")==0){
		printExit();
		exit(0);
	}else{
		goto end;
	}	
}
void saveTeachersToFile(const char *fileName, struct Teacher *list, int size){
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        exit(1);
    }
    fwrite(list, sizeof(struct Teacher), size, file);
    fclose(file);
}
int loadTeachersFormFile(const char *fileName, struct Teacher *teacher){
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        return 0;
    }
    int n = 0;
    while (fread(&teacher[n], sizeof(struct Teacher), 1, file) == 1) {
        n++;
    }
    fclose(file);
    return n;
}
