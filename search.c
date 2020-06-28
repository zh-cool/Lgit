#include <stdio.h>
#include <stdlib.h>

int b_search(int data[], int begin, int end, int key)
{
        while(begin <= end){        
                int mid = (begin+end)/2;
                int val = data[mid];

                if(val == key){
                        return mid;
                }else if(val < key){
                        begin = mid + 1;
                }else{
                        end = mid - 1;
                }
        }
        return -1;
}

int b_rsearch(int data[], int begin, int end, int key)
{
        if(begin > end){
                return -1;
        }

        int mid = (begin+end)/2;
        int val = data[mid];

        if(val == key){
                return mid;
        }else if(val < key){
                return b_search(data, mid+1, end, key);
        }else if(val > key){
                return b_search(data, begin, mid-1, key);
        }
}

void swap(int *s, int *q)
{
        int tmp;

        tmp = *s;
        *s = *q;
        *q = tmp;
}

int partion(int data[], int p, int q)
{
        int key=data[q];
        int i=p-1;

        for(int j=p; j<q; j++){
                if(key >= data[j]){
                        i++;
                        swap(&data[i], &data[j]);
                }
        }
        swap(&data[i+1], &data[q]);
        return i+1;
}

int quick_sort(int data[], int p, int q)
{
        if(p < q){
                int r = partion(data, p, q);
                quick_sort(data, p, r-1);
                quick_sort(data, r+1, q);
        }
        return 0;
}

int insert_sort(int data[], int p, int q)
{
        for(int i=1; i<=q; i++){
                int j = i-1;
                int key = data[i];
                while(j>=0 && data[j] > key){
                        data[j+1] = data[j];
                        j--;
                }
                data[j+1] = key;
        }
}

int search()
{
}

int main(int argc, char **argv)
{
        int data[] = {1,4,6,8,11,12,16};
        int dat[] = {9,4,6,2,4,1,0,7};

        int idx = b_rsearch(data, 0, 6, atoi(argv[1]));
        printf("idx=%d, data[%d]=%d\n", idx, idx, data[idx]);

        //quick_sort(dat, 0, 7);
        insert_sort(dat, 0, 7);
        for(int i=0; i<8; i++){
                printf("%d ", dat[i]);
        }
        printf("\n");
        return 0;

}
