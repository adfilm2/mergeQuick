//
//  main.c
//  MergeQuick
//
//  Created by subhin Lim on 20/05/2020.
//  B611233
//  Copyright © 2020 SB. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SWAP(x,y,temp) ( (temp)=(x), (x)=(y),(y)=(temp))

int sorted[3000];
int m_count = 0; // merge sort 비교횟수 저장
int m_worst = 0; // merge sort 최악 비교횟수
int q_count = 0; // quick sort 비교횟수 저장
int q_worst =0;  // quick sort 최악 비교횟수




void merge(int arr[],int m, int n, int mid){
    int a,b,c,d;
    a = m;      //첫번째
    b = mid +1;     //중간의 뒤
    c = m;      //첫번째
    
    //분할된 배열의 합병(merge)
    while(a<=mid && b<=n){
        if(arr[a]<= arr[b]){    //앞의 값이 작을때
            sorted[c] = arr[a]; //정렬완료 --> 배열에 저장
            a++;
            m_count++;        //비교횟수 증가
        }else{      //클때의 비교
            sorted[c] = arr[b]; //정렬완료 --> 배열에 저장
            b++;
            m_count++;        //비교횟수 증가
        }
        c++;
        
    }
    
    //남아있는 값들 sorted에 복사
    if(a>mid){
        for(d=b;d<=n;d++,c++){
            sorted[c]=arr[d];
        }
    }else{
        for(d=a;d<=mid;d++,c++){
            sorted[c]=arr[d];
        }
    }
    
    //배열 sorted[]를 arr[]로 재복사
    
//        for(d=m ; d<=n ; d++){
//            arr[d] = sorted[d];
//        }
}

void merge_sort(int arr[], int l, int r){    //merge sort 함수
    
    int mid;
    if(l<r){
        mid = (l+r)/2;  //중간값 설정
        merge_sort(arr, l, mid);    //왼쪽배열 merge sort 호출
        merge_sort(arr, mid+1, r);     //오른쪽배열 merge sort 호출
        merge(arr,l,r,mid);     //정렬을 위한 merge 함수 호출
    }
    
    
}

int partition(int arr[], int l, int r){
    int pivot = arr[l];     //pivot의 위치는 가장 왼쪽
    int low = l +1;     //pivot 다음이 low
    int high = r;       //가장 오른쪽이 high
    int temp;
    
    
    while(low <= high){ //low 와 high 가 겹치기 전까지 반복
        while((low <= r) && (pivot >= arr[low])){   //pivot보다 큰 값을 찾을때까지
            low ++; //pivot보다 작으면 low를 오른쪽으로 이동
            q_count++;
        }
        while(high>=(l+1) && pivot <= arr[high]){ //pivot보다 작은값 찾을때까지
            high--;//high 왼쪽으로 이동
            q_count++;
        }
        if(low<=high){ //교차되지 않은 상태면 스왑
            
            SWAP(arr[low],arr[high],temp);
            
        }
        
        
    }
    SWAP(arr[high],arr[l],temp); //pivot과 high를 교환
    return high;    //옮겨진 pivot의 위치를 반환
}

void quick_sort(int arr[],int l, int r){
    
    if(l<r){
        int pivot = partition (arr,l,r);
        quick_sort(arr, l, pivot -1); //왼쪽 부분 (left~pivot앞)정렬
        quick_sort(arr, pivot+1, r);    //오른쪽 부분 (pivot뒤 ~right) 정렬
    }
}

int* creat_random(int arr[],int n){       //랜덤배열 반환하는 함수
    
    srand((unsigned)time(NULL));
    for(int i = 0; i<n;i++){
        
        arr[i]= (rand() % 100) +1;
    }
    
    return arr;
}

int rand_Merge(int n, int length){  //merge sort의 n번 평균비교횟수 반환함수
    int sum=0;
    int data_list[length];
    for(int i = 0 ; i<n;i++){ //총 n 번실행
        m_count = 0; //매 실행마다 count 초기화

        int* randlist = creat_random(data_list,length);//랜덤 배열 받아옴
        merge_sort(randlist, 0, length -1);
        if(m_count > m_worst){ //m_count가 m_worst보다 크면 m_worst에 저장
            m_worst = m_count;
        }
        sum += m_count;
        sleep(1);   //계산속도가 너무 빨라 난수생성이 되지 않기때문에 1초씩 딜레이를 주었다.
    }
    
    
    return (sum/n);
}

int rand_Quick(int n, int length){
    int sum=0;
     int data_list[length];
       for(int i = 0 ; i<n;i++){//총 n 번실행
           q_count=0; //매 실행마다 count 초기화
           int* randlist = creat_random(data_list,length); //랜덤 배열 받아옴
           quick_sort(randlist, 0, length -1);
           if(q_count > q_worst){ //m_count가 m_worst보다 크면 m_worst에 저장
               q_worst = q_count;
           }
           sum += q_count;
           sleep(1);//계산속도가 너무 빨라 난수생성이 되지 않기때문에 1초씩 딜레이를 주었다.
       }
    
    return (sum/n);
}

int main(int argc, const char * argv[]) {
    FILE *fp;
    fp = fopen("/Users/dohan/Desktop/input.txt", "r"); //input파일 읽어옴.
    
    int exe_num;    //실행횟수
    int data[6];    //데이터 갯수
   
    
    
    fscanf(fp, "%d",&exe_num);  //첫줄은 실행횟수에 저장
    fscanf(fp, "%d",&data[0]);  //데이터갯수
    fscanf(fp, "%d",&data[1]);
    fscanf(fp, "%d",&data[2]);
    fscanf(fp, "%d",&data[3]);
    fscanf(fp, "%d",&data[4]);
    fscanf(fp, "%d",&data[5]);
    
    
    
    printf("\n* 난수 생성이 제대로 되지 않아 1초씩 딜레이를 주었습니다.\n* 10번 실행하는 데 10초가 걸립니다.\n* 총 120초 소요\n\n");
    printf("      rand_Merge      worst_Merge      rand_Quick      worst_Quick \n-------------------------------------------------------------------------\n");
    for(int i = 0 ; i<6; i++){
        printf("%d :",data[i]);
        printf("%8d",rand_Merge(exe_num, data[i]));
        printf("%17d",m_worst);
        printf("%17d",rand_Quick(exe_num, data[i]));
        printf("%17d\n",q_worst);
        
    }
   
    
    
    
}

