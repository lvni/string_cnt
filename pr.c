#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define  HASHSIZE 67
typedef struct HaseNote {
	char * string;
	int count;
	struct HaseNote * next;
}HaseNote,*HN_ptr;
/* 定义哈希指针数组*/
HN_ptr HashList[HASHSIZE] = {0};

int haseKey(char *key){
	unsigned int cnt = 0;
	char ch;
	while((ch=*key++)){
		cnt += ch;
	}
	return cnt % HASHSIZE;
}
void set(char *key){
	/* 获取key的下标索引 */
	int index  = haseKey(key);
	HN_ptr head = HashList[index];
	HN_ptr ptr = head;
	HN_ptr current = NULL ;
	while(ptr!= NULL){
		if(strcmp(ptr->string,key) == 0){
			ptr->count += 1;
			return ;
		}
		current = ptr;
		ptr = ptr->next;

	}
	if( ptr == NULL){
		// new 
		HN_ptr note_ptr = (HN_ptr)malloc(sizeof(HaseNote));
		note_ptr->count = 1;
		note_ptr->string = (char*)malloc(sizeof(char) * strlen(key));
		strcpy(note_ptr->string,key);
		if(current){
			current->next = note_ptr;
		}else{
			head = note_ptr;
			HashList[index] = head;
		}
	}
	
}
int get(char *key){
	int index  = haseKey(key);
	HN_ptr head = HashList[index];
	int result = -1;
	while(head){
		if(strcmp(head->string,key) == 0){
			return head->count;
		}
		head = head->next;
	}
	return result;
}
int main(){
	// HN_ptr note_ptr = (HN_ptr)malloc(sizeof(HaseNote));
	// note_ptr->count = 1;
	// note_ptr->string = (char*)malloc(sizeof(char) * 25);
	// strcpy(note_ptr->string,"china");
	// printf("HaseNote info is %d : %s \n",note_ptr->count,note_ptr->string);
	// printf("hase key is %d",haseKey(note_ptr->string));
	FILE * fp;
	fp = fopen("orc.txt","r");
	assert(fp);
	char line[25] ;
	char c;
	while(fgets(line,25,fp)){
		int i,j;
		i = j = 0;
		c = line[i];
		while(c){
			/* 去掉换行符 */
			if(c == '\n' || c == '\r'){
				line[i++] = '\0';
				break;
			}
			c = line[++i];
		}
		set(line);
	}
	
	fclose(fp);
	int  i = 0;
	for(i= 0 ; i < HASHSIZE; i++){
		HN_ptr head = HashList[i];
		while(head != NULL){
			printf(" index %d : %s -> %d \n",i,head->string,head->count);
			head = head->next;
		}
	}
	return 1;	
}

