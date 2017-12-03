#include<bits/stdc++.h>
#include<ctime>
using namespace std;
const int ROUND = 30;

int countAttack(const vector<int>& queen)
{
    int n = queen.size();
    int cnt(0);
    bool check[n + 1];

    memset(check, 0, sizeof(check));
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = i + 1 ; j < n ; j++)
        {
            //if(check[j]) continue;
            if(queen[i] == queen[j])
                cnt++, check[j] = true;
            if( abs(queen[i] - queen[j]) == abs(i - j))
                cnt++, check[j] =true;
        }
    }
    return cnt;
}


int hillclimbing(vector<int> queen)
{

    int n = queen.size(), curround(0);

    while(1)
    {
        curround++;
        //cout<< curround << " " << countAttack(queen) << endl;

        vector<int> neighbor[n + 1];
        int mini, atk;
        int informed[n + 1];

        atk = countAttack(queen);

        for(int i = 0 ; i < n ; i++)
        {
            vector<int> tmp(queen);
            int t = rand() % n;

            tmp[i] ^= tmp[t] ^= tmp[i] ^= tmp[t];

            neighbor[i] = tmp;
            //for(int j = 0 ; j < tmp.size() ; j++)
            //    cout << tmp[j];
            //cout << endl;
        }

        for(int i = 0 ; i < n ; i++)
        {
            informed[i] = countAttack(neighbor[i]);
        }
        mini = 0;
        for(int i = 1 ; i < n ; i++)
        {
            if(informed[i] < informed[mini])
                mini = i;
            if(informed[i] == informed[mini])
                if(rand() & 1)
                    mini = i;
        }

        if(countAttack(neighbor[mini]) > atk || atk == 0)
        {
             break ;
        }
        queen = neighbor[mini];
    }
    /*
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if(j == queen[i])
                printf("1");
            else printf("0");
        }
        printf("\n");
    }
    printf("\n");
    */
    //printf("After %d round. Attack : %d\n", curround, countAttack(queen));
    return countAttack(queen);
}


int main()
{
    int nqueen, round(0);
    long double avgAttack(0), avgTime(0);
    clock_t t1, t2;
    cin >> nqueen;

    srand(time(NULL));
    while(round < 30)
    {
        //cout << "Input two numbers, one is number of queen and the other one is number of round.\n";
        vector<int> q;
        bool check[nqueen + 1];
        int attack;
        long double t;


        q.clear();

        memset(check, 0, sizeof(check));
        for(int i = 0 ; i < nqueen ; i++)
        {
            int tmp;
            do
            {
                tmp = rand() % nqueen;
            }while(check[tmp]);
            check[tmp] = 1;
            q.push_back(tmp);
        }

        t1 = clock();
        attack = hillclimbing(q);
        t2 = clock();

        t = (((long double) (t2 - t1)) / CLOCKS_PER_SEC);

        avgAttack += (long double) attack;
        avgTime += t;

        cout << "The " << round + 1 << "run , the number of attack queen is " << attack << endl;
        round++;

    }
    cout << "Average attack : " << avgAttack / 30 << "\nAverage Time to find a solution : " << avgTime / 30 << "s\n";
    return 0;
}
