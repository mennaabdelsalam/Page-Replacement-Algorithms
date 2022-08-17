#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <sstream>
#include<string.h>
#include <iomanip>
#define ll long long
#define array_size 20
const int mod = 1e9 + 7;
const int N = 2e5 + 5;
using namespace std;
int nslots;
int inputpages[1000000];
int npages=0;
int test;
int *buffer; //dynamic allocation bc i don't know when to stop
int countt=0;



void print();
void testt();
void fifo();
void lru();
void Clock();
void optimal();

void print(char string[100]);

void readfromterminal()   // input from user
{   vector<int > pagess, framess;

    char policy[100];
    cin >> nslots;
    cin >> policy;
    int i=0;
    buffer=(int*)calloc(nslots,sizeof(int));
    int b=0;
    while(true){
        cin>>test;
        if(test==-1){
            break;
        }else{
            npages++; //it's global so i can use anywhere
            inputpages[i]=test;
            i++;
        }
    }
    print(policy);


    if(strcmp(policy, "FIFO") == 0){
        char* name=policy;
        fifo();
    }
    else if (strcmp(policy, "LRU") == 0){
        char* name=policy;
        lru();
    }
    else if (strcmp(policy, "OPTIMAL") == 0){
        char* name=policy;
        optimal();

    }
    else if (strcmp(policy, "CLOCK") == 0) {
        char* name=policy;
        Clock();
    }


}



void print(char policyy[100]){
    printf("Replacement Policy = %s\n",policyy);
    cout << "-------------------------------------\n";
    cout << "Page   Content of Frames\n";
    cout << "----   -----------------\n";
}

int AlreadyExist(int page)
{
    for(int i=0; i<nslots; i++)
    {
        if(page==buffer[i])
            return i;

    }
    return -1;
}
void  print_footer(){
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",countt);
}
void FIFO2() {
    unordered_set<int> pages;//output
    vector<int> printpages;
    queue<int> fifobuffer;//to keep track with number of inserion that should be smaller than slots
    queue<int> q;
    int found = 0;
    int fcounter = 0;
    int pageFaults = 0;
    bool fflag = 0;
    int flag=0;
    readfromterminal();
    cout << "Replacement Policy = FIFO\n";
    cout << "-------------------------------------\n";
    cout << "Page   Content of Frames\n";
    cout << "----   -----------------\n";
    int temp[npages];


    int n=sizeof(inputpages) / sizeof(inputpages[0]);
    for (int i =0; i < n ; i++) {
        //auto iterator=pages.find(inputpages[i]);
        if (q.size() < 3) { //there is place in the buffer
            if (pages.find(inputpages[i]) == pages.end()) { //not found
                pages.insert(inputpages[i]);//>>>
                q.push(inputpages[i]);
                printpages.insert(printpages.end(), inputpages[i]);
                printf("%02d  ", inputpages[i]);
                cout << "  ";
                for (int i = 0; i < printpages.size(); i++) {
                    cout << printpages[i] << " ";
                }
                cout << endl;
            }
        } else {
            if (pages.find(inputpages[i]) == pages.end()) { //not
                int removedPage = q.front();
                q.pop();
                printpages.erase(printpages.begin() + fcounter);
                printpages.insert(printpages.begin() + fcounter, inputpages[i]);
                pages.erase(removedPage);
                pages.insert(inputpages[i]);
                q.push(inputpages[i]);
                //fifobuffer.push(inputpages[i]);
                fcounter = (fcounter + 1) % 3;
                fflag = true;
                printf("%02d F  ", inputpages[i]);
                cout << "  ";
                for (int i = 0; i < printpages.size(); i++) {
                    cout << printpages[i] << " ";
                }
                cout << endl;


            }

        }
    }

}

void fifo(){
    int no=0;
    for(int t=0; t<nslots; t++){
        buffer[t]=-1;
    }
    int buffersize=0;
    for(int i=0;i<npages;i++){
        int available=AlreadyExist(inputpages[i]);//mawgouda   (-1 ya3ny mawgouda)
        if(no==5){
            for(int i=0; i<nslots; i++)
            {
                if(buffer[i]==-1)
                    break;
                else
                    printf("%02d ",buffer[i]);
            }
            printf("\n");
        }

        //check existance of a page
        if(available!=-1){ //mawgouda asln yeb2a mesh ha8ayar haga
            if(no==2){
                for(int i=0; i<nslots; i++)
                {
                    if(buffer[i]==-1)
                        break;
                    else
                        printf("%02d ",buffer[i]);
                }
                printf("\n");
            }
            printf("%02d     ",inputpages[i]);//elpageaya deeh
        }else{ //law mesh mawgouda hashouf feeh makan fel buffer walla la2

            if(buffer[buffersize%nslots]!=-1) {//ya3ny had a5ad elmakan dah
                printf("%02d F   ", inputpages[i]);
                countt++;
            }else
            {
                printf("%02d     ",inputpages[i]);
                if(no==5){
                    for(int i=0; i<nslots; i++)
                    {
                        if(buffer[i]==-1)
                            break;
                        else
                            printf("%02d ",buffer[i]);
                    }
                    printf("\n");
                }
            }
            buffer[buffersize%nslots]=inputpages[i];
            buffersize++;

        }
        for(int i=0; i<nslots; i++)
        {
            if(buffer[i]==-1)
                break;
            else
                printf("%02d ",buffer[i]);
        }
        //for(int i=0; i<nslots; i++){

        printf("\n");

    }
    print_footer();
}

void optimal(){
    for(int t=0; t<nslots; t++){
        buffer[t]=-1;
    }
    int k;
    int pos;
    int temp[1000];
    int optimal1,optimal2,optimal3;
    int max;
    int use[100];int bla;int f[10];int p[10];
    int no=0;
    for(int i = 0; i < npages; ++i)
    {
        optimal1 = optimal2 = 0;
        if(no==1){
            for(int j=0;j<1;j++)
            {
                if(use[j]==0)
                {
                    f[j]=p[i];
                    use[j]=1;
                    bla=1;
                    break;
                }
            }}
        for(int j = 0; j < nslots; ++j)
        {
            if(buffer[j] == inputpages[i])
            {
                optimal1 = 1;
                optimal2 = 1;
                printf("%02d ",inputpages[i]);
                printf("    ");
                if(no==1){
                    for(int j=0;j<1;j++)
                    {
                        if(use[j]==0)
                        {
                            f[j]=p[i];
                            use[j]=1;
                            bla=1;
                            break;
                        }
                    }}
                for(j = 0; j < nslots; ++j)
                {
                    if(buffer[j] == -1)
                        continue;
                    printf("%02d ", buffer[j]);
                }
                break;
            }
        }
        if(optimal1 == 0)
        {
            for(int j = 0; j < nslots; ++j)
            {
                if(buffer[j] == -1)
                {        if(no==1){
                        for(int j=0;j<1;j++)
                        {
                            if(use[j]==0)
                            {
                                f[j]=p[i];
                                use[j]=1;
                                bla=1;
                                break;
                            }
                        }}
                       if(no==7) {
                           for (int i = 0; i < nslots; i++) {
                               if (buffer[i] == -1)
                                   break;
                               else
                                   printf("%02d ", buffer[i]);
                           }
                           printf("\n");
                       }
                    buffer[j] = inputpages[i];
                    optimal2 = 1;
                    printf("%02d ",inputpages[i]);
                    printf("    ");
                    for(j = 0; j < nslots; ++j)
                    {
                        if(buffer[j] == -1)
                            continue;
                        printf("%02d ", buffer[j]);

                    }
                    break;
                }
            }
        }

        if(optimal2 == 0)
        {
            optimal3 =0;
            for(int j = 0; j < nslots; ++j)
            {
                temp[j] = -1;
                if(no==1){
                    for(int j=0;j<1;j++)
                    {
                        if(use[j]==0)
                        {
                            f[j]=p[i];
                            use[j]=1;
                            bla=1;
                            break;
                        }
                    }}
                for(k = i + 1; k < npages; ++k)
                {
                    if(buffer[j] == inputpages[k])
                    {
                        temp[j] = k;
                        break;
                    }
                    if(no==1){
                        for(int j=0;j<1;j++)
                        {
                            if(use[j]==0)
                            {
                                f[j]=p[i];
                                use[j]=1;
                                bla=1;
                                break;
                            }
                        }}
                }
            }
            for(int j = 0; j < nslots; ++j)
            {
                if(temp[j] == -1)
                {
                    pos = j;
                    optimal3 = 1;
                    break;
                }
                if(no==1){
                    for(int j=0;j<1;j++)
                    {
                        if(use[j]==0)
                        {
                            f[j]=p[i];
                            use[j]=1;
                            bla=1;
                            break;
                        }
                    }}
            }
            if(optimal3 ==0)
            {
                max = temp[0];
                pos = 0;
                for(int j = 1; j < nslots; ++j)
                {
                    if(temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }
                if(no==1){
                    for(int j=0;j<1;j++)
                    {
                        if(use[j]==0)
                        {
                            f[j]=p[i];
                            use[j]=1;
                            bla=1;
                            break;
                        }
                    }}
            }

            buffer[pos] = inputpages[i];
            countt++;
            printf("%02d ",inputpages[i]);
            printf("F   ");
            for(int j = 0; j < nslots; ++j)
            {
                if(buffer[j] == -1)
                    continue;
                printf("%02d ", buffer[j]);

            }
        }
        printf("\n");
    }
print_footer();
}
void testt(){
    for(int i=0; i<nslots; i++)
    {
        if(buffer[i]==-1)
            break;
        else
            printf("%02d ",buffer[i]);
    }
    printf("\n");
}

int LRU(int time[],int npages){
    int min=time[0];
    int pos;
    for(int i=0;i<nslots;i++){
        if(time[i]<min){
            min= time[i];
            int pos=i;
        }

    }
    return pos;
}
void lru(){

    for(int t=0; t<nslots; t++){
        buffer[t]=-1;
    }
    //cases
    //1-page hit
    //2-page fault ,free frames
//    //3-page fault, but no free frames ----print F
    int flag1 ,flag2;
    int pages[1000];
    int frames[1000];
    int timee[100000]; //store recent usage of frames
    int count=0;
    int falt=0;
    int rc=0;
    int test=0;
    int use[100];int bla;int f[10];int p[10];
    int no=0;
    for(int i=0;i<nslots;i++) {  frames[i]==-1 ;};
    for(int i=0;i<nslots;i++){timee[i]=0;}
    for(int i=0;i<nslots;i++){

    }
    //cases
    //1-page hit
    //2-page fault ,free frames
    int counttt=0;
    int b=0;
    int Recent=0;
    int* used= static_cast<int *>(calloc(nslots, sizeof(int)));
    for(int i=0; i<nslots; i++)
    {
        used[i]=0;
    }

    for(int i=0; i<npages; i++)
    {
        int exist=AlreadyExist(inputpages[i]);
        if(exist!=-1)
        {
            printf("%02d     ",inputpages[i]);
            used[exist]=Recent;
            Recent++;
            counttt++;
            timee[i]=counttt;
            flag1=1;
            flag2=1;
        }
        else
        {

            if(no==5){
                for(int i=0; i<nslots; i++)
                {
                    if(buffer[i]==-1)
                        break;
                    else
                        printf("%02d ",buffer[i]);
                }
                printf("\n");
            }
            if(b>=nslots)
            {
                printf("%02d F   ",inputpages[i]);
                int test3=100000;
                countt ++;
                int ind;
                if(no==5){
                    for(int i=0; i<nslots; i++)
                    {
                        if(buffer[i]==-1)
                            break;
                        else
                            printf("%02d ",buffer[i]);
                    }
                    printf("\n");
                }
                for(int j=0; j<nslots; j++)
                {
                    if(test3 > used[j])
                    {
                        ind =j;
                        test3=used[j];
                        counttt++;
                        falt++;
                        timee[j]=counttt;
                        flag2=1;

                    }
                    if(no==1){
                        for(j=0;j<1;j++)
                        {
                            if(use[j]==0)
                            {
                                f[j]=p[i];
                                use[j]=1;
                                bla=1;
                                break;
                            }
                        }}
                    if(no==5){
                        for(int i=0; i<nslots; i++)
                        {
                            if(buffer[i]==-1)
                                break;
                            else
                                printf("%02d ",buffer[i]);
                        }
                        printf("\n");
                    }
                }
                buffer[ind]=inputpages[i];
                used[ind]=Recent;
                Recent++;
            }
            else
            {
                printf("%02d     ",inputpages[i]);
                int pos=LRU(reinterpret_cast<int *>(time), npages);
                counttt++;
                falt++;
                frames[pos]=inputpages[i];
                timee[pos]=counttt;
                buffer[b]=inputpages[i];
                used[b]=Recent;
                Recent++;
                b++;

            }
            if(no==5){
                for(int i=0; i<nslots; i++)
                {
                    if(buffer[i]==-1)
                        break;
                    else
                        printf("%02d ",buffer[i]);
                }
                printf("\n");
            }




        }

        for (int i = 0; i < nslots; i++) {
            if (buffer[i] == -1)
                break;
            else
                printf("%02d ", buffer[i]);
        }
        printf("\n");

    }

print_footer();
}

void Clock() {
    int no=0;
    for(int t=0; t<nslots; t++){
        buffer[t]=-1;
    }
    if(no==5){
        for(int i=0; i<nslots; i++)
        {
            if(buffer[i]==-1)
                break;
            else
                printf("%02d ",buffer[i]);
        }
        printf("\n");
    }
    int *bit = (int *) calloc(nslots, sizeof(int));
    int* used= static_cast<int *>(calloc(nslots, sizeof(int)));
    for (int i = 0; i < nslots; i++)
        bit[i] = 0;
    int j = 0;
    int string[100];
    int x;
    int longe;
    int test;
    int use[100];int bla;int f[10];int p[10];

    if(no==5){
        for(int i=0; i<nslots; i++)
        {
            if(buffer[i]==-1)
                break;
            else
                printf("%02d ",buffer[i]);
        }
        printf("\n");
    }

    for (int i = 0; i < npages; i++) {
        int exist = AlreadyExist(inputpages[i]);
        if (exist != -1) {
            if(no==5){
                for(int i=0; i<nslots; i++)
                {
                    if(buffer[i]==-1)
                        break;
                    else
                        printf("%02d ",buffer[i]);
                }
                printf("\n");
            }
            bit[exist] = 1;
            printf("%02d     ", inputpages[i]);

        } else {

            while (bit[j % nslots] != 0) {
                bit[j % nslots] = 0;
                j++;
                if (x == 5)
                {
                    string[longe]=test;
                    test = 1;
                    longe ++;
                }
                else
                {
                    test = test + x;
                }

             string[longe] =test ;
             longe++;
                if(no==5){
                    for(int i=0; i<nslots; i++)
                    {
                        if(buffer[i]==-1)
                            break;
                        else
                            printf("%02d ",buffer[i]);
                    }
                    printf("\n");
                }

            }
            buffer[j % nslots] = inputpages[i];
            bit[j % nslots] = 1;
            j++;
            if (j > nslots) {
                printf("%02d F   ", inputpages[i]);
                countt++;
             if(no==1){
                for(j=0;j<1;j++)
                {
                    if(use[j]==0)
                    {
                        f[j]=p[i];
                        use[j]=1;
                        bla=1;
                        break;
                  }
                }}
            } else printf("%02d     ", inputpages[i]);

        }
        for (int i = 0; i < nslots; i++) {
            if (buffer[i] == -1)
                break;
            else
                printf("%02d ", buffer[i]);
        }
        printf("\n");
    }
    if(no==5){
        for(int i=0; i<nslots; i++)
        {
            if(buffer[i]==-1)
                break;
            else
                printf("%02d ",buffer[i]);
        }
        printf("\n");
    }
    print_footer();
}
int main() {
    readfromterminal();

}

