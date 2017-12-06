#include<bits/stdc++.h>
using namespace std;


#define oo 1000007

int n;          //n-queen
int GENERATION, POPULATION;
double cross_rate;

struct Data
{

    vector<int> queen;        //queen¦ì¸m
    int attack;             //queenªºattack¼Æ
    void init()
    {
        queen.clear();
        for(int i = 0 ; i < n ; i++)
            queen.push_back(i);
        random_shuffle(queen.begin(), queen.end());
        countAttack();
        //printQueen();
    }
    void countAttack()
    {
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
        attack = cnt;
    }

    bool operator < (Data x) const
    {
        return attack < x.attack;
    }

    void printQueen()const
    {
        cout << "!";
        for(int i = 0 ; i < n ; i++)
            printf("(%d):%d ", i,queen.at(i));
        cout << endl;
    }

};

void initialization(vector<Data>& q)
{
    for(int i = 0 ; i < POPULATION ; i++)
    {
        Data tmp;
        tmp.init();

        q.push_back(tmp);
    }
}


Data cross(const Data& a, const Data& b)
{///O((n / 2) ^ 2)
    int crosspoint1 = rand() % (n / 2) + n / 2 ;
    int maplist[n + 1];
    Data chi;

    for(int i = 0 ; i < n ; i++)
        maplist[i] = -1;


    ///list the map list
    for(int i = crosspoint1 ; i < n ; i++)
        maplist[a.queen[i]] = b.queen[i];


    chi.queen.clear();


    for(int i = 0 ; i < crosspoint1 ; i++)
    {
        int tmp1 = b.queen[i];
        while(maplist[tmp1] != -1)
        {
            //find it map value;
            tmp1 = maplist[tmp1];
        }

        chi.queen.push_back(tmp1);

    }
    for(int i = crosspoint1 ; i < n ; i++)
        chi.queen.push_back(a.queen[i]);

    return chi;
}

void crossover(vector<Data>& parent)
{///O( n * n * POPULATION * cross_rate)
    long long ch_size = (long long ) POPULATION * cross_rate;

    for(int i = 0 ; i < ch_size ; i++)
    {
        Data tmp, p1, p2;

        for(int j = 0 ; j < 2 ; j++)
        {
            int l = rand() % parent.size();
            int k = rand() % parent.size();
            if(j) p2 = parent[l].attack  < parent[k].attack ? parent[l] : parent[k];
            else p1 = parent[l].attack  < parent[k].attack ? parent[l] : parent[k];
        }


        tmp = cross(p1, p2);
        tmp.countAttack();
        parent.push_back(tmp);

    }
}


void mutation(vector<Data>& child)
{///O(POPULATION * crossrate * n ^ 2)

    for(int i = POPULATION ; i < child.size() ; i++)
    {
        //mutation is swap random index x and y;
        int x, y;
        x = rand() % n;
        y = rand() % n;
        while(y == x) y = rand() % n;

        child[i].queen[x] ^= child[i].queen[y] ^= child[i].queen[x] ^= child[i].queen[y];

        child[i].countAttack();
    }

}

int geneAlgorithm()
{
    int iter(0);
    vector<Data> q;
    initialization(q);
    srand(time(NULL) + rand() % n);
    while(iter < GENERATION)
    {

        crossover(q);
        mutation(q);
        sort(q.begin(), q.end());

        //select next population
        q.erase(q.begin() + POPULATION, q.end());


        if(q[0].attack == 0)
            break;
        iter++;
    }

    return q[0].attack;
}

int main()
{
    int curAttack, run, success(0);
    long double avgAttack(0), avgTime(0), t;
    clock_t t1, t2;
    cin >> n >> POPULATION >> cross_rate >> GENERATION >> run;
    for(int i = 0 ;  i < run ; i++)
    {
        t1 = clock();
        curAttack = geneAlgorithm();
        t2 = clock();
        t = ((long double) t2 - t1) / CLOCKS_PER_SEC;
        avgAttack += curAttack;
        avgTime += t;

        if(!curAttack) success++;
        cout << "The " << i + 1 << " run , the number of attack queen is " << curAttack << " cost " << t << " seconds.\n";

    }
    cout << "Average attack : " << avgAttack / run << "\nAverage Time to find a solution : " << avgTime / run << "s\n";
    cout << "Success rate : " << success << "/" << run << endl;

    system("pause");
    return 0;
}
