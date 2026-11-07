
#include <stdio.h>
#include <string.h>

struct Student {
    char name[100];
    char rollNumber[10];
    int score;
    char subject[20];
};

void showUserPanel();
void showAdminPanel();
void takeQuiz(struct Student* student);
void adminLogin();
void displayUserData();
void loadQuestions(char questions[][100], char subject[20]);
void clearBuffer();  
void saveToFile(struct Student* student); 

int main() {
    int choice;
    while (1) {
        printf("\n**** Welcome to Project Quiz ****\n");
        printf("1. User Panel\n");
        printf("2. Admin Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer(); 

        switch (choice) {
            case 1:
                showUserPanel();
                break;
            case 2:
                showAdminPanel();
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void showUserPanel() {
    struct Student student;
    char subjectChoice[20];
    printf("\nEnter your full name: ");
    fgets(student.name, 100, stdin);
    student.name[strlen(student.name) - 1] = '\0';  
    printf("Enter your roll number (xxK-yyyy format): ");
    fgets(student.rollNumber, 10, stdin);
    student.rollNumber[strlen(student.rollNumber) - 1] = '\0';  
    printf("\nSelect a subject (Maths, English, Science): ");
    while (1) {
        fgets(subjectChoice, 20, stdin);
        subjectChoice[strlen(subjectChoice) - 1] = '\0';  
        if (strcmp(subjectChoice, "Maths")== 0 || strcmp(subjectChoice, "English")==0 || strcmp(subjectChoice, "Science")== 0) {
            strcpy(student.subject, subjectChoice);
            break;
        } else {
            printf("Invalid subject. Please select either Maths, English, or Science: ");
        }
    }
    takeQuiz(&student);
    saveToFile(&student);
}

void takeQuiz(struct Student* student) {
    char questions[5][100];
    int correctAnswers[] = {2, 3, 1, 4, 1};  
    int userAnswers[5];
    int score = 0;
	loadQuestions(questions, student->subject);
    printf("\nStarting quiz for %s subject:\n", student->subject);
    for (int i=0; i<5; i++) {
        printf("\nQuestion %d: %s\n", i + 1, questions[i]);
        printf("Enter your answer (1-4): ");
        while (1) {
            scanf("%d", &userAnswers[i]);
            if (userAnswers[i] >= 1 && userAnswers[i] <= 4) {
                break;
            } else {
                printf("Invalid answer. Please enter a value between 1 and 4: ");
            }
        }
		if (userAnswers[i] == correctAnswers[i]) {
            score++;
        }
    }
student->score = score;
printf("\nYour score is: %d/5\n", score);
}

void loadQuestions(char questions[][100], char subject[20]) {
    if (strcmp(subject, "Maths") == 0) {
        strcpy(questions[0], "What is 2 + 2? (1) 3 (2) 4 (3) 5 (4) 6");
        strcpy(questions[1], "What is 5 * 6? (1) 28 (2) 32 (3) 30 (4) 35");
        strcpy(questions[2], "What is 9 / 3? (1) 3 (2) 4 (3) 5 (4) 6");
        strcpy(questions[3], "What is 7 - 3? (1) 6 (2) 3 (3) 5 (4) 4");
        strcpy(questions[4], "What is 12 * 4? (1) 48 (2) 50 (3) 45 (4) 40");
    } else if (strcmp(subject, "English") == 0) {
        strcpy(questions[0], "Which word is a noun? (1) run (2) house (3) quickly (4) jump");
        strcpy(questions[1], "Which word is a verb? (1) quickly (2) house (3) run (4) happiness");
        strcpy(questions[2], "Which word is an adjective? (1) blue (2) quickly (3) run (4) jump");
        strcpy(questions[3], "What is the past tense of 'go'? (1) going (2) goes (3) go (4) went");
        strcpy(questions[4], "What is the plural of 'child'? (1) children (2) childs (3) childs' (4) childrens");
    } else if (strcmp(subject, "Science") == 0) {
        strcpy(questions[0], "What is the chemical symbol for water? (1) CO2 (2) H2O (3) O2 (4) O3");
        strcpy(questions[1], "What planet is known as the Red Planet? (1) Earth (2) Venus (3) Mars (4) Jupiter");
        strcpy(questions[2], "What gas do plants absorb for photosynthesis? (1) Carbon Dioxide (2) Nitrogen (3) Oxygen (4) Helium");
        strcpy(questions[3], "What is the boiling point of water? (1) 90C (2) 80C (3) 110C (4) 100C");
        strcpy(questions[4], "Who developed the theory of relativity? (1) Einstein (2) Newton (3) Galileo (4) Darwin");
    }
}

void clearBuffer() {
    while (getchar() != '\n');  
}

void saveToFile(struct Student* student) {
    FILE *file = fopen("students.txt", "a");
    if (file) {
        fprintf(file, "%s\t%s\t%d\t%s\n", student->name, student->rollNumber, student->score, student->subject);
        fclose(file);
    } else {
        printf("Error saving user data.\n");
    }
}

void showAdminPanel() {
    char password[10];

    printf("\nEnter the admin password: ");       //the admin password is 1234
    fgets(password, 10, stdin);
    password[strlen(password) - 1] = '\0';  

    if (strcmp(password, "1234") == 0) {
        displayUserData();
    } else {
        printf("Incorrect password.\n");
    }
}

void displayUserData() {
FILE *file = fopen("students.txt", "r");
    if (file) {
        char line[256];
        int count = 0;
        printf("\n-----User Data-----\n");
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);  
            count++;
        }
        if (count == 0) {
            printf("No user data found.\n");
        }
        fclose(file);
    } else {
        printf("Error opening user data file.\n");
    }
}
