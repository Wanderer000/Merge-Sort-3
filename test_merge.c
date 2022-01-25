#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct dynarray{

	int* data;
  	int size;
  	int capacity;
};

struct dynarray* arr;
struct dynarray* arr_rand;
int input_val[10]={
#if 0
2100000,
3250000,
4300000,
5450000,
6500000,
7650000,
8700000,
9850000,
10950000,
11970000
#else
11970000,
11970000,
11970000,
11970000,
11970000,
11970000,
11970000,
11970000,
11970000,
11970000
#endif
};

void Array(char* input);
void print_dynarray(int* d, int size);
char* readf(void);
struct dynarray* dynarray_create();
void dynarray_insert(struct dynarray* da, int val);
void dynarray_set(struct dynarray* da, int idx, void* val);
void* dynarray_get(struct dynarray* da, int idx);
void merge(int* da, int low, int mid1,int mid2, int high);
void merge_sort3(int* da, int low, int high);
void file_create(struct dynarray *d);


int main(int argc, char** argv){
	time_t t;
	clock_t c;
	
	srand((unsigned) time(&t));
        int* data_rand;
	for(int i = 0; i < 10; i++) {
		data_rand = malloc(input_val[i]* sizeof(int));
		for(int j = 0; j < input_val[i]; j++) {
			data_rand[j] = rand() % 10001;
			//printf("%d ", data_rand[j]);
		}
		//printf("\n");
		//record the time
		c = clock();
		
		//printf("Before Sort\n");
		//print_dynarray(data_rand, input_val[i]);
		
		merge_sort3(data_rand , 0, input_val[i]-1);
		//record the time
		c = clock() - c;
		
		//printf("After Sort\n");
		//print_dynarray(data_rand, input_val[i]);
		
		double time_taken = ((double) c )/CLOCKS_PER_SEC; // in seconds 
		printf("merge_sort() took %f seconds to execute \n", time_taken);
		printf("%d - Array size \n", input_val[i]);
		free(data_rand);
	}
 
}


void print_dynarray(int* d, int size){
	printf("====%s====\n", __func__);
	for(int i = 0; i < size; i++){
		printf("%d ",d[i]);
	}
	printf("\n====%s====\n", __func__);
}


void Array(char* input){

	int i;
	int tmp;
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
			tmp = -1;
			dynarray_insert(arr,tmp);
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




void merge(int* da, int low, int mid1,int mid2, int high){

	int i = low;//count for the left part
	int j = mid1+1;//count for the middle part
	int k = mid2+1;//count for the right part
	int size = (high - low) + 1;  

	int* daf = malloc((size)*sizeof(da));//create temperary array
	//printf("[%s] size(%d) low(%d) mid1(%d) mid2(%d) high(%d)\n", __func__, size, low, mid1, mid2, high);
	for(int z = 0; z< (size); z++){
	//printf("[%s] i-j-k(%d-%d-%d) low(%d) mid1(%d) mid2(%d) high(%d)\n", __func__, i,j,k, low, mid1, mid2, high);
	// Choose the smallest in the three ranges
		if ((i <= mid1) && (j <= mid2) && (k <= high)){  
		//three parts do not exceed
			if(da[i] < da[j]){ 

				if(da[i] < da[k]){ 
					//the left part is the smallest
					daf[z] = da[i];
					i++;
				} 

				else{ 
					//right part is larger than left part, and left part is smaller than the middle part
					//we need to check whether middle part is larger than right part
					if(da[k] < da[j]){
						//right part is the smallest
						daf[z] = da[k];
						k++; 
					}else{
						//middle part is the smallest
						daf[z] = da[j];
						j++; 
					}
				} 
			} 

			else{
				//left part is larger than middle part
				if(da[j] < da[k]){
					//middle part is the smallest
					daf[z] = da[j];
					j++; 
				} 

				else{
					//right part is the smallest
					daf[z] = da[k]; 
					k++;
				} 


			} 
		} 
	
		 else if((i <= mid1) && (j <= mid2) && (k > high)){
		//left and middle part not exceed, but the right part is out of range
			if(da[i] < da[j]){
			//left part is the smallest
				daf[z] = da[i];
				i++; 
			} 

			else{ 
			//middle part is the smallest
				daf[z] = da[j];
				j++;
			} 
		} else if((i > mid1) && (j <= mid2) && (k <= high)){
		//middle part and the right part no exceed, but the left part is out of range
			if(da[j] < da[k]){ 
			//middle part is the smallest
				daf[z] = da[j];
				j++; 
			} 

			else{ 
			//right part is the smallest
				daf[z] = da[k];
				k++; 
			}  
		} else if((i <= mid1) && (j > mid2) && (k <= high)){
		//left part and right part not exceed, but middle part is out of range
			if(da[i] < da[k]){
			//left part is the smallest
				daf[z] = da[i];
				i++; 
			} 

			else{ 
			//right part is the smallest
				daf[z] = da[k]; 
				k++;
			}  
		} else {
			// only one part not exceed
			if (i <= mid1){
				//left part
				daf[z] = da[i];
				i++;  
			}else if (j <= mid2){  
				//middle part
				daf[z] = da[j];
				j++;  
			}else if (k <= high){  
				//right part
				daf[z] = da[k];
				k++;
			} 
		}
	}
	//printf("[%s] size(%d) low(%d) mid1(%d) mid2(%d) high(%d)\n", __func__, size, low, mid1, mid2, high);
	for(int z = 0; z< (size); z++){
		da[low + z] = daf[z];
	//	printf("daf(%d) ", daf[z]);
	}
	//	printf("\n ");
	free(daf);
}



void merge_sort3(int* da, int low, int high){  

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





