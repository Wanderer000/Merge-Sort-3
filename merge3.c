#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct dynarray{

	int* data;
  	int size;
  	int capacity;
};

struct dynarray* arr;

void Array(char* input);
void print_dynarray(struct dynarray* d);
char* readf(void);
struct dynarray* dynarray_create();
void dynarray_insert(struct dynarray* da, int val);
void dynarray_set(struct dynarray* da, int idx, void* val);
void* dynarray_get(struct dynarray* da, int idx);
void merge(struct dynarray* da, int low, int mid1,int mid2, int high);
void print_dynarray(struct dynarray* d);
void merge_sort3(struct dynarray* da, int low, int high);  
void file_create(struct dynarray *d);

int main(int argc, char** argv){

	char *input = 0;
	int start = 1;
	int end = 0;

// Read file
  input = readf();
  //printf("%s [%d]",input, (int)strlen(input));
//Organize the data
  Array(input);
  //printf("[%s]size [%d]\n", __func__, arr->size);
  print_dynarray(arr);
//Sort
  for(int i = 0; i < arr->size; i++){
	  if(arr->data[i] == -1){
		end = i-1;
		merge_sort3(arr, start, end);
		start = i + 2;
	  }
  }
  printf("After Sort\n");
  print_dynarray(arr);

//Make a new file with sorted numbers
  file_create(arr);
  
}

void file_create(struct dynarray *d){
	FILE* file_data;
	// Create file for writting
	char* output;

	file_data = fopen("merge3.txt", "w");


	for(int i = 1; i < d->size; i++){
		//printf("[%s]i(%d) %d data(%d)\n",__func__, i, d->size, d->data[i]);
		if(d->data[i] == -1){
			//printf("in -1]n");
			fprintf(file_data,"\r\n");
			i++;
		}
		else{
			fprintf(file_data,"%d ",d->data[i]);
		}
	} 
	fclose(file_data);
}



void print_dynarray(struct dynarray* d){
	printf("====%s====\n", __func__);
	for(int i = 0; i < d->size; i++){
		if(d->data[i] == -1){
			printf("\n");
		}else{
			printf("%d ",d->data[i]);
		}
	}
}
		
char* readf(void){
	FILE* file_data;
	char buffer[20];
	char *input = 0;
	size_t cur_len = 0;


	// Open the file only for reading

	file_data = fopen("data.txt", "r");

	while (fgets(buffer, sizeof(buffer), file_data) != 0){

		size_t buf_len = strlen(buffer);
		char *extra = realloc(input, buf_len + cur_len + 1);
		if(!extra)
			break;
		input = extra;
		strcpy(input + cur_len, buffer);
		cur_len += buf_len;
	}

	fclose(file_data);
    	return (input);
}

void Array(char* input){

	int i;
	int tmp = 0;
	int flag = 0;
	char* data;
	int size = (int)strlen(input);

	arr = dynarray_create();
	for(i = 0; i < size; i++){
		//printf("[%s] size(%d), value(%d)\n", __func__, size, input[i]);
		if(input[i] == 13){

			if(flag == 1){
				dynarray_insert(arr, tmp);
				tmp = 0;
				flag = 0;
			}
		}
		else if(input[i]==10){
			dynarray_insert(arr,-1);
			flag = 0;
		}
		else if(input[i] == 32){

			if(flag==1){
				dynarray_insert(arr, tmp);
				tmp = 0;
				flag = 0;
			}
		}
		else if(input[i]>= 48 && input[i]<= 57){
				tmp = input[i]- 48 + tmp*10;
				flag = 1;		
		}
	}

	if(flag==1){
		dynarray_insert(arr, tmp);
		tmp = 0;
		flag = 0;
	}
}

struct dynarray* dynarray_create(){
  	
	struct dynarray *da = malloc(1* sizeof (struct dynarray));

	da->size = 0;
        da->capacity = 2;
	
	da->data =  malloc(2* sizeof(void*));

  return da;
}

// Inserting values to dynamic array.

void dynarray_insert(struct dynarray* da, int val){

	  	
	if (da != NULL){
	{
	int n;
	int i;
		if (da->size == da->capacity-1){
			n = da->capacity*2;
			da->data = realloc (da->data,n* sizeof(da->data));
			da->capacity = da->capacity*2;
			i = da->size;
			da->data[i] = val;
			da-> size++;
	
		}
		
		else{
			i = da->size;
			da->data[i] = val;
			da->size++;
		}
	}
 
	}
  return;
}

void merge(struct dynarray* da, int low, int mid1,int mid2, int high){

	int i = low;//count for the left part
	int j = mid1+1;//count for the middle part
	int k = mid2+1;//count for the right part
	int size = (high - low) + 1;  

	int* daf = malloc((size)*sizeof(da->data));//create temperary array
	//printf("[%s] size(%d) low(%d) mid1(%d) mid2(%d) high(%d)\n", __func__, size, low, mid1, mid2, high);
	for(int z = 0; z< (size); z++){
	//printf("[%s] i-j-k(%d-%d-%d) low(%d) mid1(%d) mid2(%d) high(%d)\n", __func__, i,j,k, low, mid1, mid2, high);
	// Choose the smallest in the three ranges
		if ((i <= mid1) && (j <= mid2) && (k <= high)){  
		//three parts do not exceed
			if(da->data[i] < da->data[j]){ 

				if(da->data[i] < da->data[k]){ 
					//the left part is the smallest
					daf[z] = da->data[i];
					i++;
				} 

				else{ 
					//right part is larger than left part, and left part is smaller than the middle part
					//we need to check whether middle part is larger than right part
					if(da->data[k] < da->data[j]){
						//right part is the smallest
						daf[z] = da->data[k];
						k++; 
					}else{
						//middle part is the smallest
						daf[z] = da->data[j];
						j++; 
					}
				} 
			} 

			else{
				//left part is larger than middle part
				if(da->data[j] < da->data[k]){
					//middle part is the smallest
					daf[z] = da->data[j];
					j++; 
				} 

				else{
					//right part is the smallest
					daf[z] = da->data[k]; 
					k++;
				} 
			} 
		} else if((i <= mid1) && (j <= mid2) && (k > high)){
		//left and middle part not exceed, but the right part is out of range
			if(da->data[i] < da->data[j]){
			//left part is the smallest
				daf[z] = da->data[i];
				i++; 
			} 

			else{ 
			//middle part is the smallest
				daf[z] = da->data[j];
				j++;
			} 
		} else if((i > mid1) && (j <= mid2) && (k <= high)){
		//middle part and the right part no exceed, but the left part is out of range
			if(da->data[j] < da->data[k]){ 
			//middle part is the smallest
				daf[z] = da->data[j];
				j++; 
			} 

			else{ 
			//right part is the smallest
				daf[z] = da->data[k];
				k++; 
			}  
		} else if((i <= mid1) && (j > mid2) && (k <= high)){
		//left part and right part not exceed, but middle part is out of range
			if(da->data[i] < da->data[k]){
			//left part is the smallest
				daf[z] = da->data[i];
				i++; 
			} 

			else{ 
			//right part is the smallest
				daf[z] = da->data[k]; 
				k++;
			}  
		} else {
			// only one part not exceed
			if (i <= mid1){
				//left part
				daf[z] = da->data[i];
				i++;  
			}else if (j <= mid2){  
				//middle part
				daf[z] = da->data[j];
				j++;  
			}else if (k <= high){  
				//right part
				daf[z] = da->data[k];
				k++;
			} 
		}
	}
	//printf("[%s] size(%d) low(%d) mid1(%d) mid2(%d) high(%d)\n", __func__, size, low, mid1, mid2, high);
	for(int z = 0; z< (size); z++){
		da->data[low + z] = daf[z];
	//	printf("daf(%d) ", daf[z]);
	}
	//	printf("\n ");
	free(daf);
}



void merge_sort3(struct dynarray* da, int low, int high){  

	int mid1;
	int mid2;
	// Split arrays
	mid1 = low + ((high - low) / 3);  
	mid2 = low + 2 * (high - low) / 3;  
//	printf("[%s] low(%d) mid1(%d) mid2(%d) high(%d)\n",__func__, low, mid1, mid2, high);
	if (high <= low){ 
		return;  
  	}
     
//	printf("[%s] low(%d) mid1(%d) mid2(%d) high(%d)\n",__func__, low, mid1, mid2, high);
	// Sorting arrays recursevly
	merge_sort3(da, low, mid1);  
	merge_sort3(da, mid1+1, mid2);  
	merge_sort3(da, mid2+1, high);  

	// Merge sorted arrays
	merge(da, low, mid1, mid2, high);

}





