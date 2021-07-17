#include <stdio.h>

void add();
void display();
void search();
void del();
void update();
struct employee
{
    int id;
    char name[20];
    int age;
    float salary; 
} e;

int main()
{
    int ch;
    system("cls");

    while (ch != 6)
    {
        printf("\n\n\t---WELCOME TO EMPLOYEE MANAGEMENT PROGRAM---\n\n");

        printf("\t\t1. Add Record\n");
        printf("\t\t2. Display Record\n");
        printf("\t\t3. Search\n");
        printf("\t\t4. Delete Record\n");
        printf("\t\t5. Update\n");
        printf("\t\t6. Exit\n");
        printf("\n\t\tEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            system("cls");
            add();
            break;
        case 2:
            system("cls");
            display();
            break;
        case 3:
            system("cls");
            search();
            break;
        case 4:
            system("cls");
            del();
            break;
        case 5:
            system("cls");
            update();
            break;
        case 6:
            ch = 6;
            break;
        default:
            printf("Wrong Choice.");
            break;
        }
    }
    return 0;
}

void add()
{
    FILE *fp;
    fp = fopen("employee.txt", "ab+");
    printf("\n\n\t---Enter new employee data---\n\n");

    printf("\n\tEnter ID(ID must be unique): ");
    scanf("%d", &e.id);
    printf("\n\tEnter employee name: ");
    scanf("%s", e.name);
    printf("\n\tEnter age: ");
    scanf("%d", &e.age);
    printf("\n\tEnter salary: ");
    scanf("%f", &e.salary);
    fwrite(&e, sizeof(e), 1, fp);
    printf("\n\n\tEmployee Record Inserted Successfully.");
    fclose(fp);
}

void display()
{
    FILE *fp;
    fp = fopen("employee.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\tError: Cannot Open the file !\n");
        return;
    }
    printf("\n\n\t--- Employee Details Are As Follows ---\n");
    printf("\n\tID\tName\t\tAge\tSalary\n\n");
    while (fread(&e, sizeof(e), 1, fp) == 1)
    printf("\t%d\t%s\t\t%d\t%.2f\n",e.id, e.name, e.age, e.salary);
    fclose(fp);
}

void search()
{
    int n,x = 0;
    FILE *fp;
    fp = fopen("employee.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\tError: Cannot Open the file !\n");
        return;
    }
    printf("\n\tEnter employee ID to be search: ");
    scanf("%d",&n);
    while (fread(&e, sizeof(e), 1, fp) > 0 && x == 0)
    {
        if (e.id == n)
        {
            x = 1;
            printf("\n\n\tSEARCH SUCCESSFUL\n");
            printf("\n\tID\tNAME\t\tAGE\tSALARY\n");
            printf("\t%d\t%s\t\t%d\t%.2f",e.id, e.name, e.age, e.salary);
        }
    }
    if (x = 0)
    printf("\n\n\tNO SUCH RECORD FOUND !\n");
    fclose(fp);
}

void del()
{
    char name[20];
    int y = 0;
    FILE *fp, *ft;
    fp = fopen("employee.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\tError: Cannot Open the file !\n");
        return;
    }
    printf("\n\t--- Previous Stored Data ---");
    display();
    printf("\n\n\tEnter Employee name to delete: ");
    scanf("%s", name);
    ft = fopen("tempemployee.txt", "ab+");
    while (fread(&e, sizeof(e), 1, fp) == 1)
    {
        if (strcmp(name, e.name) != 0)
        {
            fwrite(&e, sizeof(e), 1, ft);
        }
        else
            y = 1;
    }
    if (y == 0)
        printf("\n\n\tNo Such Record Found !");
    fclose(fp);
    fclose(ft);
    remove("employee.txt");
    rename("tempemployee.txt", "employee.txt");
    display();
}

void update()
{
    display();
    FILE *fp;
    char n[20];
    fp=fopen("employee.txt","r+");
    if (fp==NULL)
    {
       printf("\n\t\tError: Cannot Open the file !\n");
        return;
        fclose(fp);
    }
    printf("\n\tEnter the name of the employee you want to modify: ");
    scanf("%s",&n);
    while (fread(&e,sizeof(e),1,fp)==1)
    {
        if(strcmp(e.name,n)==0){
            printf("\n\n\tEnter new data--> \n\n");
            printf("\n\t\tUpdated ID: ");
            scanf("%d", &e.id);
            fflush(stdin);
            printf("\n\t\tUpdated Name: ");
            scanf("%s", e.name);
            printf("\n\t\tUpdated Age: ");
            scanf("%d", &e.age);
            printf("\n\t\tUpdated Salary: ");
            scanf("%f", &e.salary);
            fseek(fp,-(long)sizeof(e),1);
            fwrite(&e,sizeof(e),1,fp);
            break;
        }
    }
    system("cls");
    fclose(fp);
}