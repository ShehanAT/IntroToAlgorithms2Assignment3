#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
void loadCourseInfo();
void addCourseInfo();
void displayCourseInfo();
void searchCourseID();
void searchCourseTerm();
void saveCourseInfo(const char *FileName);
void searchCourseName();
void searchCourseTerm();
struct CourseInfo{
    int courseID;
    char courseName[40];
    char courseCode[10];
    char Term[7];
    char courseSelection[10];
};
int courseCount;
struct CourseInfo arr[100];
char globalYear[100];
char globalSemester[100];
int newCourseIn = 0;
int selection = 0;
char firstCode[10];
char secondCode[10];
char thirdCode[10];
char firstSection[10];
char secondSection[10];
char thirdSection[10];
int main()
{
    char saveData[1] = " ";
    loadCourseInfo();
    while(1){
        printf("Assignment 3(MUST SAVE COURSE DATA AFTER ADDING COURSE)\n-------------------\n1.Add a new course\n2.Search for a course by course ID\n3.Search for a course by course Name\n4.Search for all courses by term\n5.Display course data\n6.Save course data\n7.Exit\n");
        printf("Enter selection(1-7 only)\n");
        scanf("%d", &selection);
        
        switch(selection){
            case 1:
                addCourseInfo();
                break;
            case 2:
                searchCourseID();
                break;
            case 3:
                searchCourseName();
                break;
            case 4:
                searchCourseTerm();
                break;
            case 5:
                displayCourseInfo();
                break;
            case 6:
                saveCourseInfo("./courseInfo.csv");
                break;
            case 7:
                printf("Do you want to save course data(Y/N):\n");
                scanf("%s", saveData);
                if(strcmp(saveData,"y") == 0){
                    saveCourseInfo("./courseInfo.csv");
                    printf("Goodbye\n");
                    break;
                }
                else{
                    printf("Goodbye\n");
                    break;}
            default:
                printf("Invalid Option!");      
        }
        if(selection == 7){
            break;
        }
    }
    return 0;
}
void loadCourseInfo(){
    FILE *inputfile = NULL;
    char currentCourses[300][300];
    inputfile = fopen("./courseInfo.csv", "r");
    if(inputfile == NULL){
        printf("Unable to open input file.\n");
    }
    courseCount = 0;
    while(fscanf(inputfile, "%s\n", currentCourses[courseCount]) != EOF){
        courseCount++;
    }
    for(int i = 0 ; i < courseCount;i++){
        char *newText;
        arr[i].courseID = i+1;
        newText = strtok(currentCourses[i], " ,");
        newText[0] = toupper(newText[0]);
        strcpy(arr[i].courseName, newText);
        newText = strtok(NULL, ",");
        strcpy(arr[i].courseCode, newText);
        newText = strtok(NULL, ",");
        strcat(arr[i].courseCode,newText);
        strcat(arr[i].courseCode, "-");
        newText = strtok(NULL, ",");
        strcat(arr[i].courseCode, newText);
        newText = strtok(NULL, ",");
        strcpy(arr[i].courseSelection, newText);
        newText = strtok(NULL, ",");
        strcat(arr[i].courseSelection, ",");
        strcat(arr[i].courseSelection, newText);
        newText = strtok(NULL, ",");
        strcat(arr[i].courseSelection, ",");
        strcat(arr[i].courseSelection, newText);
        newText = strtok(NULL, ",");
        strcpy(arr[i].Term, newText);
        newText = strtok(NULL, ",");
        strcat(arr[i].Term, newText);
    }
    newCourseIn = 0;
    fclose(inputfile);
};
void addCourseInfo(){
    char courseName[100];
    char courseCodes[100][100];
    int counter = 1;
    char name[100];
    int sections;
    char select[100][100];
    char semester[100];
    char faculty[100];
    char subject[100];
    char level[100];
    char year[100];
    char currentCourses[300];
    char strArr[100][100];
    int count = 0;
    int repeated = 0;
    int select_repeated = 0;
    arr[courseCount].courseID = courseCount + 1;
    printf("Enter course name:\n");
    scanf("%s", name);
    name[0] = toupper(name[0]);
    strcpy(arr[courseCount].courseName, name);
    do{
        repeated = 0;
        printf("Enter faculty code(format xx):\n");
        scanf("%s", faculty);
        strcpy(firstCode, faculty);
        printf("Enter subject code(format xx):\n");
        scanf("%s", subject);
        strcpy(secondCode, subject);
        printf("Enter level code(format xxx):\n");
        scanf("%s", level);
        strcpy(thirdCode, level);
        strcat(faculty, subject);
        strcat(faculty, "-");
        strcat(faculty, level);
        for(int i = 0 ; i < courseCount; i++){
            if(strcmp(faculty, arr[i].courseCode) == 0){
                printf("Invalid:repeated course code!\n");
                repeated = 1;
            }
        }
    }while(repeated);
    strcpy(arr[courseCount].courseCode, faculty);
    printf("Enter number of sections:(less than or equal to 3)\n");
    scanf("%d", &sections);
    do{
        select_repeated = 0;
        switch(sections){
        case 1:
            printf("Enter section code 1:\n");
            scanf("%s",select[0]);
            strcpy(firstSection, select[0]);
            strcpy(secondSection, "0");
            strcpy(thirdSection, "0");
            strcat(select[0],",0,0");
            break;
        case 2:
            for(int i = 0 ; i < 2; i++){
                printf("Enter section code %d:\n", i+1);
                scanf("%s", select[0+i]);
                }
            strcpy(firstSection, select[0]);
            strcpy(secondSection, select[1]);
            strcpy(thirdSection, "0");
            strcat(select[0],",");
            strcat(select[0],select[1]);
            strcat(select[0],",0");
            break;
        case 3:
            for(int i = 0 ; i < 3; i++){
                printf("Enter section code %d:\n", i+1);
                scanf("%s", select[0+i]); 
            }
            strcpy(firstSection, select[0]);
            strcpy(secondSection, select[1]);
            strcpy(thirdSection, select[2]);
            strcat(select[0],",");
            strcat(select[0],select[1]);
            strcat(select[0],",");
            strcat(select[0],select[2]);
            break;
    }
    for(int i = 0 ; i < courseCount; i++){
        if(strcmp(select[0], arr[i].courseSelection) == 0){
            printf("Invalid:repeated selection code\n");
            select_repeated = 1;
        }  
    }
    }while(select_repeated);
    strcpy(arr[courseCount].courseSelection, select[0]);
    printf("Enter semester code:\n");
    scanf("%s", arr[courseCount].Term);
    strcpy(globalSemester, arr[courseCount].Term);
    printf("Enter year(format yyyy):\n");
    scanf("%s", year);
    strcpy(globalYear, year);
    strcat(arr[courseCount].Term,year);
    newCourseIn = 1;
    printf("Course added, remember to save(selection 6 at menu)!");
};

void displayCourseInfo(){
    printf("ID\tName\tCode\t    Sections\tTerm\n");
    printf("--------------------------------------------\n");
    for(int i = 0 ; i < courseCount;i++){
        printf("%d %11s %11s%11s   %s\n",arr[i].courseID, arr[i].courseName,arr[i].courseCode,arr[i].courseSelection,arr[i].Term);
    }
    printf("          \n");
};
void searchCourseID(){
    int idSearch;
    printf("Enter the ID of the course to be searched:\n");
    scanf("%d",&idSearch);
    printf("ID\tName\tCode\t    Sections\tTerm\n");
    printf("--------------------------------------------\n");
    int found = 0;
    for(int i = 0; i < courseCount;i++){
        if (arr[i].courseID == idSearch){
            found = 1;
            printf("%d %11s %11s%11s   %s\n", arr[i].courseID, arr[i].courseName, arr[i].courseCode, arr[i].courseSelection, arr[i].Term);
        }
    }
    if(found == 0){
        printf("Course ID %d was not found.\n", idSearch);
    }
    printf("                 \n");
};
void searchCourseTerm(){
    char strTermLetter[100];
    char *strFind = strTermLetter;
    char strYear[4];
    int found = 0;
    printf("Enter semester(S, F, or W):\n");
    scanf("%s", strTermLetter);
    printf("Enter year(format yyyy):\n");
    scanf("%s", strYear);
    strcat(strTermLetter, strYear);
    printf("ID\tName\tCode\t    Sections\tTerm\n");
    printf("--------------------------------------------\n");
    for(int i = 0 ;i < 100;i++){
        if(strncmp(arr[i].Term, strTermLetter, 4) == 0){
            found = 1;
            printf("%d %11s %11s%11s   %s\n", arr[i].courseID, arr[i].courseName, arr[i].courseCode, arr[i].courseSelection,arr[i].Term);
        }
    }
    if(found == 0){
        printf("Course Term %s was not found.\n", strTermLetter);
    }
    printf("                 \n");
};
void searchCourseName(){
    char strCourseName[100];
    printf("Enter name of course to be searched:\n");
    scanf("%s", strCourseName);
    int found = 0;
    printf("ID\tName\tCode\t    Sections\tTerm\n");
    printf("--------------------------------------------\n");
    for(int i = 0 ; i < 100; i++){
        if(strcmp(arr[i].courseName, strCourseName) == 0){
            found = 1;
            printf("%d %11s %11s%11s   %s\n", arr[i].courseID, arr[i].courseName, arr[i].courseCode, arr[i].courseSelection,arr[i].Term);
        } 
    }
    if(found == 0){
        printf("Course Name %s was not found.\n", strCourseName);
    }
    printf("                 \n");
};
void saveCourseInfo(const char *FileName){
    if(newCourseIn == 1){
        char courseCode[100];
        FILE *newfile = NULL;
        newfile = fopen(FileName, "a+");
        char selectionArr[100][100];
        int count = 0;
        for(int i = 0; i < courseCount+1;i++){
            arr[i].courseName[0] = tolower(arr[i].courseName[0]);
        }
        fprintf(newfile, "%s", "\n");
        fprintf(newfile, "%s", arr[courseCount].courseName);
        fprintf(newfile, "%s", ",");
        fprintf(newfile, "%s", firstCode);
        fprintf(newfile, "%s", ",");
        fprintf(newfile, "%s", secondCode);
        fprintf(newfile, "%s", ",");
        fprintf(newfile, "%s", thirdCode);
        fprintf(newfile, "%s", ",");
        fprintf(newfile, "%s", firstSection);
        fprintf(newfile, "%s", ",");
        fprintf(newfile, "%s", secondSection);
        fprintf(newfile, "%s", ",");
        fprintf(newfile, "%s", thirdSection);
        fprintf(newfile, "%s", ",");
        fprintf(newfile, "%s", globalSemester);
        fprintf(newfile, "%s", ",");
        fprintf(newfile, "%s", globalYear);
        printf("All Course information is saved.\n");
        newCourseIn = 0;
        fclose(newfile);
        loadCourseInfo();
    }
    else{
        printf("Nothing to save, add course then call agian!\n");
    }
};