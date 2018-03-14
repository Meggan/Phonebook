//Christopher Luong, Meggan Do
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

//define the node
typedef struct node{
	struct node *next;
	char phoneNumber[MAX];
	char firstName[MAX]; //this is the same as name[]?
	char lastName[MAX];
}Node, *NodePtr;

//put extern variables here
int choice = -1;
int loadCounter = 0;

//makeNode function
NodePtr makeNode(char *firstName, char *lastName, char *phoneNumber){
	//allocate memory for the node
	NodePtr np = (NodePtr) malloc(sizeof(Node));
	strcpy(np->firstName, firstName); //leave off the * infront of userInput, why?
	strcpy(np->lastName, lastName);
	strcpy(np->phoneNumber, phoneNumber);
	np -> next = NULL;
	return np;
}

//initialize methods here
	//probably dont need this as long as methods are before the main method
//end of initialization

//clears everything in the linkedList
NodePtr clearRecords(NodePtr head){
	struct node *nextNode;
	//before we load the file we should clear the linked list since it will already be preloaded
	//and we do not want duplicates
	while(head != NULL) {
		nextNode = head->next;
		free(head);
		head = nextNode;
	}
	return head;
}

//loads a txt file which contains data that will be inserted into a linked list
NodePtr load(char fileName[MAX], NodePtr head){
	char phoneNumber[MAX] = {0};
	char firstName[MAX] = {0};
	char lastName[MAX] = {0};
	char newfileName[MAX] = {0};
	struct node *temp;
	
	//clear the records
	head = clearRecords(head);

	//load the file
	FILE *input = fopen(fileName,"r+");
	
	//if this is a load from the menu, ask the user which file they want to load
	if(loadCounter != 0){ 
		printf("What file do you want to load (please enter the name and extension): ");
		scanf("%s", newfileName);
		input = fopen(newfileName, "r+");
	}
	//check if the file opened successfully
	if (input == NULL) {
		printf("Error: Cannot open the file\n");
	}
	else{
		while(!feof(input)){ //while it still returns 1 argument
		    fscanf(input, "%s", firstName);
			fscanf(input, "%s", lastName);			
			fscanf(input, "%s", phoneNumber);
			temp = makeNode(firstName,lastName,phoneNumber); //create a temp node that contains the record data	
			if(head == NULL){
				head = temp;
			}
			else{
				temp->next = head;
			}
			head = temp;
		}
		fclose(input); //close the file when we are done	
		printf("File loaded successfully\n");
		loadCounter++;
	}
	return head;
}

//add to linked list method
NodePtr add(NodePtr head){
	struct node *newEntry;
	char phoneNumber[MAX] = {0};
	char firstName[MAX] = {0};
	char lastName[MAX] = {0};

	printf("Please enter a First Name: ");
	scanf("%s", firstName);
	printf("Please enter a Last Name: ");
	scanf("%s", lastName);		
	printf("Please enter a Phone Number: ");
	scanf("%s", phoneNumber);

	newEntry = makeNode(firstName, lastName, phoneNumber);
	newEntry->next = head;
	head = newEntry;
	return head;
}

//write the data from the linked list into a txt file which can then be loaded later on
void saveContacts(NodePtr head){
	FILE *newSave = fopen("savedContacts.txt", "w");
	while(head != NULL){
		//\n must be in front otherwise it will mess up the EOF reader since there
		//will be a blank next line and it will repeat the last record
		fprintf(newSave, "\n%s %s %s", head->firstName, head->lastName, head->phoneNumber);
		head = head->next;
	}
	fclose(newSave);
}
void printRecord(NodePtr head){
	printf("%s %s %s\n", head->firstName, head->lastName, head->phoneNumber);
}
void search(NodePtr head){
	char sFirstName[MAX] = {0};
	char sLastName[MAX] = {0};
	char sPhoneNumber[MAX] = {0};
	int searchChoice = -1;
	while (searchChoice < 1 || searchChoice > 3){
		printf("1. First Name\n");
		printf("2. Last Name\n");
		printf("3. Phone\n");
		printf("How would you like to search: ");
		scanf("%d", &searchChoice);

		switch(searchChoice){
			case 1:	
				printf("Enter a First Name: ");
				scanf("%s", &sFirstName);
				printf("\n");
				while(head != NULL){
					if(strcmp(head->firstName,sFirstName) == 0){
						printf("Found a match!\n");
						printRecord(head);
					}
					head = head->next;
				}
				break;
			case 2:
				printf("Enter a Last Name: ");
				scanf("%s", &sLastName);
				printf("\n");
				while(head != NULL){
					if(strcmp(head->lastName,sLastName) == 0){
						printf("Found a match!\n");
						printRecord(head);
					}
					head = head->next;
				}

				break;
			case 3:
				printf("Enter a Phone Number: ");
				scanf("%s", &sPhoneNumber);
				printf("\n");
				while(head != NULL){
					if(strcmp(head->phoneNumber,sPhoneNumber) == 0){
						printf("Found a match!\n");
						printRecord(head);
					}
					head = head->next;
				}
				break;
			default:
				printf("Invalid option, please try again\n");
		}
	}
}

void deleteRecord(Node *head){
	//use the search function
	//put the result found into a temp NodePtr 
	//head's next should be temp's next
	//clear temp
	char sFirstName[MAX] = {0};
	char sLastName[MAX] = {0};
	char sPhoneNumber[MAX] = {0};
	int searchChoice = -1;

	while (searchChoice < 1 || searchChoice > 3){
		printf("1. First Name\n");
		printf("2. Last Name\n");
		printf("3. Phone\n");
		printf("How would you like to search: ");
		scanf("%d", &searchChoice);

		switch(searchChoice){
			case 1:	
				printf("Enter a First Name: ");
				scanf("%s", &sFirstName);
				printf("\n");
							
				break;
			case 2:
				printf("Enter a Last Name: ");
				scanf("%s", &sLastName);
				printf("\n");
				

				break;
			case 3:
				printf("Enter a Phone Number: ");
				scanf("%s", &sPhoneNumber);
				printf("\n");
				
				break;
			default:
				printf("Invalid option, please try again\n");
		}
	}
}


int main(){
	//switch statement for the options
	
	NodePtr head;
	head = NULL;
	head = load("contacts.txt", head); //on start up load the records
	//mergeSort(head, 0, findLength(head));

	while(choice != 6){
		printf("1. Add\n");
		printf("2. Retrieve\n");
		printf("3. Delete\n");
		printf("4. Load\n");
		printf("5. Save\n");
		printf("6. Exit\n");
		printf("Please select an option: ");
		scanf("%d", &choice);
		printf("\n");

		switch(choice){
			case 1:
				//add method
				head = add(head);
				//insertion sort method
			    break;
			case 2:
				search(head);
			    break;
			case 3:
				deleteRecord(head);
			    break;
			case 4:
				head = load("contacts.txt", head);
				//run quick sort method after the phonebook has been loaded
			    break;
			case 5:
				//printf("Save record has been selected\n");
			 	saveContacts(head);   
				break;
			case 6:
				printf("Shutting down...Bye\n");
			    break;
			default:
				printf("Pleases select a valid option from the list\n");
				break;
		}
	}
	while(head != NULL){
		printf("%s %s %s\n", head->firstName, head->lastName, head->phoneNumber);
		head=head->next;
	}
	

}
